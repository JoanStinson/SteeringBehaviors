#include "SceneCollisionAvoidance.h"
#include "Obstacle.h"
using namespace std;
using namespace Vector2DUtils;

SceneCollisionAvoidance::SceneCollisionAvoidance()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);


	Agent *obstacle = new Agent;
	obstacle->setPosition(Vector2D(300, 300));
	//obstacle->setTarget(Vector2D(640, 360));
	obstacle->loadSpriteTexture("../res/zombie1.png", 8);
	obstacles.push_back(obstacle);
	//target = Vector2D(640, 360);

	Agent *obstacle2 = new Agent;
	obstacle2->setPosition(Vector2D(600, 300));
	//obstacle->setTarget(Vector2D(640, 360));
	obstacle2->loadSpriteTexture("../res/zombie2.png", 8);
	obstacles.push_back(obstacle2);
	//target = Vector2D(640, 360);

	Agent *obstacle3 = new Agent;
	obstacle3->setPosition(Vector2D(900, 300));
	//obstacle->setTarget(Vector2D(640, 360));
	obstacle3->loadSpriteTexture("../res/zombie1.png", 8);
	obstacles.push_back(obstacle3);
	//target = Vector2D(640, 360);

	Agent *obstacle4 = new Agent;
	obstacle4->setPosition(Vector2D(300, 600));
	//obstacle->setTarget(Vector2D(640, 360));
	obstacle4->loadSpriteTexture("../res/zombie1.png", 8);
	obstacles.push_back(obstacle4);
	//target = Vector2D(640, 360);

	Agent *obstacle5 = new Agent;
	obstacle5->setPosition(Vector2D(600, 600));
	//obstacle->setTarget(Vector2D(640, 360));
	obstacle5->loadSpriteTexture("../res/zombie2.png", 8);
	obstacles.push_back(obstacle5);
	//target = Vector2D(640, 360);

	Agent *obstacle6 = new Agent;
	obstacle6->setPosition(Vector2D(900, 600));
	//obstacle->setTarget(Vector2D(640, 360));
	obstacle6->loadSpriteTexture("../res/zombie1.png", 8);
	obstacles.push_back(obstacle6);
	//target = Vector2D(640, 360);

}

SceneCollisionAvoidance::~SceneCollisionAvoidance()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	for (int i = 0; i < (int)obstacles.size(); i++)
	{
		delete obstacles[i];
	}
}

void SceneCollisionAvoidance::update(float dtime, SDL_Event *event)
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
	

	/*for each (Agent* x in obstacles)
	{
		Vector2D steering_force = x->Behavior()->Wander(x, dtime);
		x->update(steering_force, dtime, event);
	}*/
	
	float dymanic = agents[0]->getVelocity().Length() / agents[0]->getMaxVelocity();
	
	Vector2D raycastVector = agents[0]->getPosition();
	raycastVector += (agents[0]->getVelocity().Normalize() * 100)*dymanic;

	

	Vector2D raycastVector2 = agents[0]->getPosition();
	raycastVector2 += (agents[0]->getVelocity().Normalize() * 100) * dymanic *0.5;

	
	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0],agents[0]->getTarget(), dtime);
	Vector2D avoidance_force;
	
	for each (Agent* x in obstacles)
	{
		if (Vector2D().Distance(raycastVector, x->getPosition()) <= 40 || Vector2D().Distance(raycastVector2, x->getPosition()) <= 40) {
			avoidance_force = raycastVector - x->getPosition();
		}
	}
	steering_force += avoidance_force;
	agents[0]->update(steering_force, dtime, event);

	//for each (Agent* x in obstacles)
	//{
	//	if (IsInsideCone(x->getPosition(), agents[0]->getPosition(), agents[0]->getPosition() + (agents[0]->getVelocity().Normalize() * 200), 30)) {

	//		float currDist = Vector2D().Distance(agents[0]->getPosition(), x->getPosition());
	//		if (currDist < shortestDist) {
	//			nearestTarget = x;
	//			shortestDist = currDist;
	//			colDetec = true;
	//		}

	//	}
	//	else
	//	{
	//		colDetec = false;
	//	}
	//}
	//Vector2D flee_force;
	//Vector2D steering_force;
	//if (colDetec) {
	//	flee_force = agents[0]->Behavior()->Flee(agents[0], nearestTarget->getPosition(), dtime);
	//	//agents[0]->update(steering_force, dtime, event);
	//}
	//else {
	//	steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime);
	//	
	//}
	//steering_force += flee_force;
	//agents[0]->update(steering_force, dtime, event);

}
	
	

void SceneCollisionAvoidance::draw()
{
	float dymanic = agents[0]->getVelocity().Length() / agents[0]->getMaxVelocity();

	Vector2D raycastVector = agents[0]->getPosition();
	raycastVector += (agents[0]->getVelocity().Normalize() * 100)*dymanic;

	Vector2D raycastVector2 = agents[0]->getPosition();
	raycastVector2 += (agents[0]->getVelocity().Normalize() * 100)*dymanic*0.5;

	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);

	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), agents[0]->getPosition().x, agents[0]->getPosition().y, raycastVector.x, raycastVector.y);
	
	draw_circle(TheApp::Instance()->getRenderer(), raycastVector.x, raycastVector.y, 10, 0, 255, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), raycastVector2.x, raycastVector2.y, 10, 0, 255, 0, 255);

	agents[0]->draw();
	for each (Agent* x in obstacles)
	{
		x->draw();
		
	}
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 0, 255);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 100, 100, 700); //LEFT
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 100, 1200, 100); //TOP
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 1200, 100, 1200, 700); //RIGHT
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 700, 1200, 700); //BOTTOM
}

const char* SceneCollisionAvoidance::getTitle()
{
	return "SDL Steering Behaviors :: SceneCollisionAvoidance Demo";
}