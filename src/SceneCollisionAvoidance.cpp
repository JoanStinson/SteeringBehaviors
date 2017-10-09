#include "SceneCollisionAvoidance.h"
#include <time.h>

using namespace std;

SceneCollisionAvoidance::SceneCollisionAvoidance()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/cat.png", 3);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	MAX_AHEAD = 200;
	srand(time(NULL));
	Vector2D pos(rand() % 1000 + 100, rand() % 500 + 200);
	obstacles.push_back(pos);
	
	//avoidForce = Vector2D(0, 0);
	MAX_AVOID_FORCE = 200;
	dynamicVelocity = 0;
	
	Agent *bg = new Agent;
	bg->setPosition(Vector2D(0, 383));
	bg->loadSpriteTexture("../res/bg.jpg", 2);
	agents.push_back(bg);

	Agent *text = new Agent;
	text->setPosition(Vector2D(635, -80));
	text->loadSpriteTexture("../res/collisionavoidance.png", 2);
	agents.push_back(text);

	Agent *water = new Agent;
	water->setPosition(pos);
	water->loadSpriteTexture("../res/circle.png", 2);
	agents.push_back(water);
	//obstacles.push_back(Vector2D(rand() % 1280, rand() % 768 + 200));
	//water->draw();
}

SceneCollisionAvoidance::~SceneCollisionAvoidance()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneCollisionAvoidance::update(float dtime, SDL_Event *event)
{
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
	Vector2D steering_force = agents[0]->Behavior()->CollisionAvoidance(agents[0], agents[0]->getTarget(),obstacles, dtime, MAX_AHEAD, MAX_AVOID_FORCE);
	agents[0]->update(steering_force, dtime, event);
}

void SceneCollisionAvoidance::draw()
{
	agents[1]->draw();
	agents[3]->draw();
	/*for (int i = 0; i < obstacles.size(); i++) {
		draw_circle(TheApp::Instance()->getRenderer(), obstacles[i].x, obstacles[i].y, 50, 255, 0, 255, 255);
	}*/
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	agents[2]->draw();
}

const char* SceneCollisionAvoidance::getTitle()
{
	return "SDL Steering Behaviors :: Collision Avoidance Demo";
}