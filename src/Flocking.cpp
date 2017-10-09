#include "Flocking.h"
#include <time.h>
using namespace std;

Separation::Separation()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/cat.png", 3);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	srand(time(NULL));

	Agent *bg = new Agent;
	bg->setPosition(Vector2D(0, 383));
	bg->loadSpriteTexture("../res/bg.jpg", 2);
	agents.push_back(bg);

	Agent *text = new Agent;
	text->setPosition(Vector2D(635, -80));
	text->loadSpriteTexture("../res/combiningsb.png", 2);
	agents.push_back(text);
	for (int i = 0; i < rand() % 10 + 4; i++) {

		Agent *z = new Agent;
		z->setPosition(Vector2D(200 + rand() % 50, 200 + rand() % 50));
		z->setMaxVelocity(Vector2D(100, 100));
		z->loadSpriteTexture("../res/dog.png", 3);
		agents.push_back(z);
		r = 50;
		neighbourCount = 0;
	}
	separation = 0;
}

Separation::~Separation()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}


}

void Separation::update(float dtime, SDL_Event *event)
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


	for (int i = 3; i < agents.size(); i++) {
		obstacles.push_back(agents[i]->getPosition());
		neighbourCount++;

	}
	
	float t;
	dist = agents[0]->getPosition() - agents[3]->getPosition();
	if (agents[0]->getVelocity().Length() == 0)
		t = 2;
	else
		t = dist.Length() / agents[0]->getVelocity().Length();

	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);

	for (int i = 3; i < agents.size(); i++) {
		steering_force = agents[i]->Behavior()->Pursue(agents[i], agents[0]->getPosition() + agents[0]->getVelocity()*t, 100, dtime);

		for (int j = 4; j < agents.size(); j++) {
			Vector2D farness = farness.Distance(agents[i]->getPosition(), agents[j]->getPosition());
			if (farness.Length()  <= r) {
				alignment += (agents[j]->getVelocity());
				cohesion += agents[j]->getPosition();
				separation += agents[j]->getPosition() - agents[i]->getPosition();

			}
		}
		alignment /= neighbourCount;
		alignment = alignment.Normalize();		
		
		cohesion /= neighbourCount;
		cohesion = Vector2D(cohesion.x - agents[i]->getPosition().x, cohesion.y - agents[i]->getPosition().y);
		cohesion = cohesion.Normalize();

		separation /= neighbourCount;
		separation *= -1;
		separation = separation.Normalize();

		agents[i]->update(steering_force + separation*60 + cohesion * 25 + alignment*20, dtime, event);
		separation = 0;
	}

	obstacles.clear();
}

void Separation::draw()
{
	agents[1]->draw();
	for (int i = 1; i < agents.size(); i++)
		agents[i]->draw();

	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	agents[2]->draw();
}

const char* Separation::getTitle()
{
	return "SDL Steering Behaviors :: KinematicSeek Demo";
}