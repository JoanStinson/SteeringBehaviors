#include "SceneKinematicArrive.h"

using namespace std;

SceneKinematicArrive::SceneKinematicArrive()
{
	Agent *agent = new Agent;
	Agent *agent2 = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/cat.png", 3);

	agents.push_back(agent);

	target = Vector2D(640, 360);
	r = 150;

	Agent *bg = new Agent;
	bg->setPosition(Vector2D(0, 383));
	bg->loadSpriteTexture("../res/bg.jpg", 2);
	agents.push_back(bg);

	Agent *text = new Agent;
	text->setPosition(Vector2D(635, -80));
	text->loadSpriteTexture("../res/arrive.png", 2);
	agents.push_back(text);
}

SceneKinematicArrive::~SceneKinematicArrive()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}


void SceneKinematicArrive::update(float dtime, SDL_Event *event)
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

	Vector2D steering_force = agents[0]->Behavior()->Arrive(agents[0], target, r, dtime);
	agents[0]->update(steering_force, dtime, event);


}

void SceneKinematicArrive::draw()
{
	agents[1]->draw();

	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	if (dist.Length() >= r) {
		draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, r, 0, 0, 255, 1);
	}
	else {
		draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, r, 0, 255, 0, 1);
	}
	agents[0]->draw();
	agents[2]->draw();
}

const char* SceneKinematicArrive::getTitle()
{
	return "SDL Steering Behaviors :: KinematicArrive Demo";
}
