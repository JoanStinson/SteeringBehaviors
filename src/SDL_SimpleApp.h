#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Scene.h"
#include "Vector2D.h"

class SDL_SimpleApp
{
private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	static SDL_SimpleApp * s_pInstance;
	
	int win_width;
	int win_height;
	SDL_Color bg_color;
	bool win_fullscreen;
	float last_update;

public:
	SDL_SimpleApp();
	~SDL_SimpleApp();
	static SDL_SimpleApp* Instance();
	SDL_Event run(Scene *scene);
	SDL_Renderer * getRenderer() const { return renderer; }
	Vector2D getWinSize();
	void setWindowTitle(const char* title);
	void setFullScreen();
};

typedef SDL_SimpleApp TheApp;