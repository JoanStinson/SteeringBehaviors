#include "ScenePathFinding.h"

using namespace std;
#include <iostream>
#include <iterator>
#include <vector>
ScenePathFinding::ScenePathFinding()
{
	Agent *agent = new Agent;
	Agent *agent2 = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	currentTargetIndex = 0;
	distances = {};
	targets = {};
}

ScenePathFinding::~ScenePathFinding()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

//SEEK IS COMPLETE
void ScenePathFinding::update(float dtime, SDL_Event *event)
{
	Vector2D steering_force;
	Vector2D targetPosition;
	Vector2D masCercaTarget = 0;
	float x;
	/* Keyboard & Mouse events */
	switch (event->type) {

	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{

			target = Vector2D((float)(event->button.x), (float)(event->button.y));
		
			targets.push_back(target);
		}
		break;
	default:
		break;
	}
	Vector2D min = 0;
	float shortest = 1000;
	int bestIndex;
	if (targets.size() != NULL) {

		Vector2D dist = agents[0]->getPosition() - targets[currentTargetIndex];
		
		if (dist.Length() < 5)
		{
			currentTargetIndex += 1;
		}
		if (currentTargetIndex == targets.size()) {
			currentTargetIndex = 0;
		}
		
		steering_force = agents[0]->Behavior()->Seek(agents[0], targets[currentTargetIndex], dtime);

		for (int i = 0; i < targets.size(); ++i) {
			draw_circle(TheApp::Instance()->getRenderer(), targets[i].x, targets[i].y, 15, 255, 255, 255, 255);
		}

	
	for (int i = 0; i < targets.size()-1; ++i){
		float distance = (float)(agents[0]->getPosition() - targets[i]).Length();
		if (distance < shortest)
		{
			shortest = distance;
			currentTargetIndex = i;
		}
	}


	}
	
	agents[0]->update(steering_force, dtime, event);

}

void ScenePathFinding::draw()
{
	
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();

}

const char* ScenePathFinding::getTitle()
{
	return "SDL Steering Behaviors :: KinematicPathFinding Demo";
}