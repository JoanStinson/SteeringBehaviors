#include "ScenePathFollowing.h"

using namespace std;

ScenePathFollowing::ScenePathFollowing()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	//agent->setTarget(Vector2D(200, 200));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	//target = Vector2D(640, 360);
	//path->pathArray[0] = Vector2D(640, 360);
	
}

ScenePathFollowing::~ScenePathFollowing()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	
}

void ScenePathFollowing::update(float dtime, SDL_Event *event)
{
	
	/* Keyboard & Mouse events */
	switch (event->type) {

	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			if (countPath < 25) {
				path->pathArray[countPath] = Vector2D(event->button.x, event->button.y);
				//draw_circle(TheApp::Instance()->getRenderer(), (int)event->button.x, (int)event->button.y, 15, 255, 0, 0, 255);
				countPath += 1;
				click = true;
			}
			//target = Vector2D((float)(event->button.x), (float)(event->button.y));
			//agents[0]->setTarget(target);
		}
		break;

	default:
		break;
	}
	if (click) {
		agents[0]->setTarget(path->pathArray[targetCount]);
		Vector2D dist = agents[0]->getTarget() - agents[0]->getPosition();
		if (dist.Length() < 6) {
		
			float min = 10000;
			Vector2D vec;
			int iPos = 0;

			for (int i = targetCount + 1; i < countPath; i++)
			{
				//buscar punt mes proper
				vec = path->pathArray[i] - agents[0]->getPosition();
				if (vec.Length() < min) {
					min = vec.Length();
					targetCount = i;
				}
			}
			
		}
		
		Vector2D steering_force = agents[0]->Behavior()->SeekPath(agents[0], agents[0]->getTarget(), dtime);
		
		agents[0]->update(steering_force, dtime, event);
	}
}

void ScenePathFollowing::draw()
{
	
	//int lol = path->pathArray->Length();
		for (int i = 0; i < countPath; i++) {
			draw_circle(TheApp::Instance()->getRenderer(), (int)path->pathArray[i].x, (int)path->pathArray[i].y, 15, 255, 0, 0, 255);
		}
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(),255,255,255,255);
		if (countPath > 1) {
			for (int i = 0; i < countPath -1; i++) {
				//draw_circle(TheApp::Instance()->getRenderer(), (int)path->pathArray[i].x, (int)path->pathArray[i].y, 15, 255, 0, 0, 255);
				SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)path->pathArray[i].x, (int)path->pathArray[i].y, (int)path->pathArray[i + 1].x, (int)path->pathArray[i + 1].y);
			}
		}
		
	
	//draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
}

const char* ScenePathFollowing::getTitle()
{
	return "SDL Steering Behaviors :: Path Following Demo";
}

int ScenePathFollowing::GetParameter(Vector2D pos) {
	float min = 100000000;
	Vector2D vec;
	int iPos = 0;
	
		for (int i = targetCount + 1; i < countPath; i++)
		{
			//buscar punt mes proper
			vec = path->pathArray[i] - pos;
			if (vec.Length() < min) {
				min = vec.Length();
				iPos = i;
			}
		}
		return iPos;
	
}