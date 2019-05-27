////#pragma once
//#include <iostream>
//#include <minmax.h>
//#include <SDL.h>
//#include <SDL_image.h>
//#include "SDL_SimpleApp.h"
//#include "Vector2D.h"
//#include "utils.h"
//#include "SteeringBehavior.h"

//class Obstacle
//{
//	friend class SteeringBehavior;
//private:
//	Vector2D position;
//
//	SDL_Color color;
//
//	SDL_Texture *sprite_texture;
//	bool draw_sprite;
//	int sprite_num_frames;
//	int sprite_w;
//	int sprite_h;
//
//public:
//	Obstacle();
//	~Obstacle();
//
//	Vector2D getPosition();
//	void setPosition(Vector2D position);
//	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
//	void update(Vector2D steering_force, float dtime, SDL_Event *event);
//	void draw();
//	bool Obstacle::loadSpriteTexture(char* filename, int num_frames = 1);
//	float orientation;
//	int currentTargetIndex = 0;
//};
//
