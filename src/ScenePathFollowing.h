#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class ScenePathFollowing :
	public Scene
{
public:
	ScenePathFollowing();
	~ScenePathFollowing();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	int GetParameter(Vector2D);
	struct Path
	{
		Vector2D pathArray[];
	};


	Path *path = new Path;
	int countPath = 0;
	int targetCount = 0;
	bool click = false;
private:
	std::vector<Agent*> agents;
	Vector2D target;
	
};
