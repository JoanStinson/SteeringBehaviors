#include "SceneWanderBehavior.h"

using namespace std;

SceneWanderBehavior::SceneWanderBehavior()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
}

SceneWanderBehavior::~SceneWanderBehavior()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneWanderBehavior::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		/*if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}*/
		break;

	default:
		break;
	}
	Vector2D steering_force = agents[0]->Behavior()->Wander(agents[0], dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneWanderBehavior::draw()
{
	//draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);

	draw_circle(TheApp::Instance()->getRenderer(),agents[0]->getPosition().x + 750 * cos(agents[0]->orientation*DEG2RAD), agents[0]->getPosition().y + 750 * sin(agents[0]->orientation*DEG2RAD), 250, 0, 0, 200, 255);
	agents[0]->draw();

	//(int)(position.x + 15 * cos(orientation*DEG2RAD)), (int)(position.y + 15 * sin(orientation*DEG2RAD)));
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 0, 255);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 100, 100, 700); //LEFT
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 100, 1200, 100); //TOP
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 1200, 100, 1200, 700); //RIGHT
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 700, 1200, 700); //BOTTOM

}

const char* SceneWanderBehavior::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}