#include "SceneCollisionAvoidance.h"

using namespace std;

SceneCollisionAvoidance::SceneCollisionAvoidance()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	MAX_AHEAD = 200;
	test = Vector2D(200, 200);
	obstacles.push_back(test);
	avoidForce = Vector2D(0, 0);
	MAX_AVOID_FORCE = 200;
	dynamicVelocity = 0;
	
		
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

	
	Vector2D steering_force = agents[0]->Behavior()->CollisionAvoidance(agents[0], agents[0]->getTarget(),avoidForce, obstacles, distances, subdistances, dtime, MAX_AHEAD, MAX_AVOID_FORCE, dynamicVelocity);
	agents[0]->update(steering_force, dtime, event);
}

void SceneCollisionAvoidance::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), test.x, test.y, 50, 255, 0, 255, 255);

	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();

}

const char* SceneCollisionAvoidance::getTitle()
{
	return "SDL Steering Behaviors :: Collision Avoidance Demo";
}