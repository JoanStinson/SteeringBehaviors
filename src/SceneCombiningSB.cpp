#include "SceneCombiningSB.h"
#include "SceneKinematicPursue.h"
#include "SceneCollisionAvoidance.h"
using namespace std;

SceneCombiningSB::SceneCombiningSB()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	Zombie*zombie = new Zombie;
	
	Agent *bg = new Agent;
	bg->setPosition(Vector2D(0, 383));
	bg->loadSpriteTexture("../res/bg.jpg", 2);
	agents.push_back(bg);

	Agent *text = new Agent;
	text->setPosition(Vector2D(635, 580));
	text->loadSpriteTexture("../res/controls.png", 2);
	agents.push_back(text);
}

SceneCombiningSB::~SceneCombiningSB()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	for (int i = 0; i < (int)zombies.size(); i++)
	{
		delete zombies[i];
	}

}

//SEEK IS COMPLETE
void SceneCombiningSB::update(float dtime, SDL_Event *event)
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
		break;//
		//
	default:
		break;
	}

	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime);
	Vector2D steering_force2 = agents[0]->Behavior()->CollisionAvoidance(agents[0], agents[0]->getTarget(), dtime);
	Vector2D steering_force3 = agents[0]->Behavior()->Pursue(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);

}

void SceneCombiningSB::draw()
{
	agents[1]->draw();
	agents[2]->draw();
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
}

const char* SceneCombiningSB::getTitle()
{
	return "SDL Steering Behaviors :: KinematicSeek Demo";
}