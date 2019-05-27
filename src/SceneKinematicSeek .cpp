
#include "SceneKinematicSeek.h"
#include "SteeringBehavior.h"
using namespace std;

SceneKinematicSeek::SceneKinematicSeek()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
}

SceneKinematicSeek::~SceneKinematicSeek()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneKinematicSeek::update(float dtime, SDL_Event *event)
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
	case SDL_KEYDOWN:
	
		/*if (event->key.keysym.scancode == SDL_SCANCODE_6) {
			pursue = false;

			agents.pop_back();
			Agent *agent = new Agent;
			agent->setPosition(Vector2D(640, 360));
			agent->setTarget(Vector2D(640, 360));
			agent->loadSpriteTexture("../res/soldier.png", 4);
			agents.push_back(agent);
			target = Vector2D(640, 360);

			
			Agent *zombie2 = new Agent;
			zombie2->setPosition(Vector2D(100, 100));
			zombie2->setMass(0.5);
			zombie2->setTarget(Vector2D(100, 100));
			zombie2->loadSpriteTexture("../res/zombie2.png", 8);
			//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 10,10, 300, 300);
			agents.push_back(zombie2);
			evade = true;
			//target = Vector2D(100, 100);
		}*/
	default:
		break;
	}
	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);
	if (pursue) {
		Vector2D steering_force = agents[1]->Behavior()->Pursue(agents[1], agents[0], dtime);
		agents[1]->update(steering_force, dtime, event);
	}
	else if (evade) {
		Vector2D steering_force = agents[2]->Behavior()->Evade(agents[2], agents[0], dtime);
		agents[2]->update(steering_force, dtime, event);
	}
}

void SceneKinematicSeek::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 200, 0, 255, 0, 255);
	
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), agents[0]->getPosition().x, agents[0]->getPosition().y, agents[0]->getTarget().x, agents[0]->getTarget().y);
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 0, 255, 255);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), agents[0]->getPosition().x, agents[0]->getPosition().y, ((agents[0]->getTarget().x - agents[0]->getPosition().x) - agents[0]->getVelocity().x)+ agents[0]->getTarget().x, ((agents[0]->getTarget().y - agents[0]->getPosition().y) - agents[0]->getVelocity().y) + agents[0]->getTarget().y);
	
	//BORDERS
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 0, 255);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 100, 100, 700); //LEFT
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 100, 1200, 100); //TOP
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 1200, 100, 1200, 700); //RIGHT
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 700, 1200, 700); //BOTTOM

	agents[0]->draw();
	if (pursue) {
		agents[1]->draw();
	}
	else if (evade) {
		agents[2]->draw();
	}
}

const char* SceneKinematicSeek::getTitle()
{
	return "SDL Steering Behaviors :: Seek Demo";
}