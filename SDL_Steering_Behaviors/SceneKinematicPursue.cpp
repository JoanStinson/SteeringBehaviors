#include "../src/SceneKinematicPursue.h"

using namespace std;

SceneKinematicPursue::SceneKinematicPursue()
{
	Agent *z1 = new Agent;
	Agent *agent = new Agent;

	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	z1->setPosition(Vector2D(100, 100));
	z1->loadSpriteTexture("../res/zombie1.png", 8);
	z1->setMass(0.2);
	agents.push_back(z1);

	t = 1;

	Agent *bg = new Agent;
	bg->setPosition(Vector2D(0, 383));
	bg->loadSpriteTexture("../res/bg.jpg", 2);
	agents.push_back(bg);

	Agent *text = new Agent;
	text->setPosition(Vector2D(635, 580));
	text->loadSpriteTexture("../res/controls.png", 2);
	agents.push_back(text);
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
	dist = agents[0]->getPosition() - agents[1]->getPosition();
	if (agents[0]->getVelocity().Length() == 0)
		t = 2;
	else
		t = dist.Length() / agents[0]->getVelocity().Length();


	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], target, dtime);
	agents[0]->update(steering_force, dtime, event);
	steering_force = agents[0]->Behavior()->Pursue(agents[1], agents[0]->getPosition() + agents[0]->getVelocity()*t, 200, dtime);
	agents[1]->update(steering_force, dtime, event);


}

void SceneKinematicPursue::draw()
{
	agents[2]->draw();
	agents[3]->draw();
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	agents[1]->draw();
}

const char* SceneKinematicPursue::getTitle()
{
	return "SDL Steering Behaviors :: KinematicPursue Demo";
}