#include "SceneKinematicEvade.h"

using namespace std;

SceneKinematicEvade::SceneKinematicEvade()
{
	Agent *agent = new Agent;
	Zombie *zombie = new Zombie;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	zombie->setPosition(Vector2D(300, 300));

	agent->loadSpriteTexture("../res/soldier.png", 4);
	zombie->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent);
	zombies.push_back(zombie);
	target = Vector2D(640, 360);
}

SceneKinematicEvade::~SceneKinematicEvade()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}


}

//SEEK IS COMPLETE
void SceneKinematicEvade::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}break;
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_8)
		{
			agents[0]->setPosition(Vector2D(500,500));
		}
		break;
	default:
		break;
	}

	/*if (agents[0]->getPosition().x < perimeterBorder)
		desiredVelocity.x = agentMaxSpeed;
	elif(agentPosition.x > perimeterWidth - perimeterBorder)
		desiredVelocity.x = -agentMaxSpeed;
	if (agentPosition.y < perimeterBorder)
		desiredVelocity.y = agentMaxSpeed;
	elif(agentPosition.y > perimeterHeight - perimeterBorder)
		desiredVelocity.y = -agentMaxSpeed;
	if (desiredVelocity.Length() > 0.0f) {
		steeringForce = desiredVelocity - agentSpeed;
		steeringForce /= agentMaxSpeed;
		steeringForce *= agentMaxForce;
	}*/
	Vector2D dist = agents[0]->getPosition() - zombies[0]->getPosition();
	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);
	if (dist.Length() <= 200) {
	
	Vector2D steering_force2 = zombies[0]->Behavior()->Flee(agents[0], zombies[0]->getTarget(), dtime);
	
	zombies[0]->update(steering_force2, dtime, event);
	}
}

void SceneKinematicEvade::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)zombies[0]->getPosition().x, (int)zombies[0]->getPosition().y, 205, 255, 0, 0, 255);
	agents[0]->draw();
	zombies[0]->draw();
}

const char* SceneKinematicEvade::getTitle()
{
	return "SDL Steering Behaviors :: KinematicSeek Demo";
}