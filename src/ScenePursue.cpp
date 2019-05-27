#include "ScenePursue.h"

using namespace std;

ScenePursue::ScenePursue()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	Agent *zombie = new Agent;
	zombie->setPosition(Vector2D(100, 100));
	zombie->setMass(0.5);
	zombie->setTarget(Vector2D(100,100));
	zombie->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(zombie);
}

ScenePursue::~ScenePursue()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePursue::update(float dtime, SDL_Event *event)
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
	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);

	Vector2D steering_force2 = agents[1]->Behavior()->Pursue(agents[1], agents[0], dtime);
	agents[1]->update(steering_force2, dtime, event);

}

void ScenePursue::draw()
{
	
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 200, 0, 255, 0, 255);

	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), agents[0]->getPosition().x, agents[0]->getPosition().y, agents[0]->getTarget().x, agents[0]->getTarget().y);
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 0, 255, 255);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), agents[0]->getPosition().x, agents[0]->getPosition().y, ((agents[0]->getTarget().x - agents[0]->getPosition().x) - agents[0]->getVelocity().x) + agents[0]->getTarget().x, ((agents[0]->getTarget().y - agents[0]->getPosition().y) - agents[0]->getVelocity().y) + agents[0]->getTarget().y);
	agents[0]->draw();
	agents[1]->draw();

	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 0, 255);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 100, 100, 700); //LEFT
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 100, 1200, 100); //TOP
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 1200, 100, 1200, 700); //RIGHT
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 700, 1200, 700); //BOTTOM
}

const char* ScenePursue::getTitle()
{
	return "SDL Steering Behaviors :: Pursue Demo";
}