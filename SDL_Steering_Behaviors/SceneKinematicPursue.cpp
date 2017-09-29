#include "../src/SceneKinematicPursue.h"

using namespace std;

SceneKinematicPursue::SceneKinematicPursue()
{
	Agent *agent = new Agent;
	Agent *z1 = new Agent;

	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 640));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	z1->setPosition(Vector2D(100, 100));
	z1->loadSpriteTexture("../res/zombie1.png", 8);
	z1->setVelocity(100);

	agents.push_back(z1);
}

SceneKinematicPursue::~SceneKinematicPursue()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}


}

void SceneKinematicPursue::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}

	agents[1]->setTarget(agents[0]->getPosition());


	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime); //SEGUIR AQUEST EXEMPLE
	agents[0]->update(steering_force, dtime, event);
	steering_force = agents[0]->Behavior()->Pursue(agents[1], agents[0], agents[0]->getTarget(), dtime);
	agents[1]->update(steering_force, dtime, event);

	//TO DO --> Programar moviment des zombie	
	/*t = dist.Length() / agents[0]->getVelocity().Length();

	
	agents[1]->setTarget(agents[0]->getPosition());
	Vector2D DesiredVelocity = agents[1]->getPosition() -agents[1]->getTarget();
	DesiredVelocity = DesiredVelocity.Normalize();
	DesiredVelocity *= agents[1]->getMaxVelocity();
	Vector2D zombieForce = (DesiredVelocity - agents[1]->getVelocity());
	zombieForce /= agents[1]->getMaxVelocity();
	zombieForce * agents[1]->getMaxForce();
	agents[1]->update(zombieForce, dtime, event);*/

}

void SceneKinematicPursue::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	agents[1]->draw();
}

const char* SceneKinematicPursue::getTitle()
{
	return "SDL Steering Behaviors :: KinematicPursue Demo";
}