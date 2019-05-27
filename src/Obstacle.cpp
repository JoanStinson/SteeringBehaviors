//#include "Obstacle.h"
//
//using namespace std;
//
//Obstacle::Obstacle():
//		sprite_texture(0),
//		position(Vector2D(100, 100)),
//		orientation(0),
//		color({ 255,255,255,255 }),
//		sprite_num_frames(0),
//		sprite_w(0),
//		sprite_h(0),
//		draw_sprite(false)
//{
//}
//
//
//Obstacle::~Obstacle()
//{
//	if (sprite_texture)
//		SDL_DestroyTexture(sprite_texture);
//}
//
//Vector2D Obstacle::getPosition()
//{
//	return position;
//}
//
//void Obstacle::setPosition(Vector2D _position)
//{
//	position = _position;
//}
//void Obstacle::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
//{
//	color = { r, g, b, a };
//}
//
//void Obstacle::update(Vector2D steering_force, float dtime, SDL_Event *event)
//{
//
//	//cout << "Obstacle update:" << endl;
//
//	switch (event->type) {
//		/* Keyboard & Mouse events */
//	case SDL_KEYDOWN:
//		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
//			draw_sprite = !draw_sprite;
//		break;
//	default:
//		break;
//	}
//
//
//	// Trim position values to window size
//	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
//	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
//	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
//	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
//}
//
//void Obstacle::draw()
//{
//	if (draw_sprite)
//	{
//		Uint32 sprite;
//
//		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
//		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
//		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
//		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation + 90, &center, SDL_FLIP_NONE);
//	}
//	else
//	{
//		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, color.r, color.g, color.b, color.a);
//		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x + 15 * cos(orientation*DEG2RAD)), (int)(position.y + 15 * sin(orientation*DEG2RAD)));
//	}
//}
//
//bool Obstacle::loadSpriteTexture(char* filename, int _num_frames)
//{
//	if (_num_frames < 1) return false;
//
//	SDL_Surface *image = IMG_Load(filename);
//	if (!image) {
//		cout << "IMG_Load: " << IMG_GetError() << endl;
//		return false;
//	}
//	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);
//
//	sprite_num_frames = _num_frames;
//	sprite_w = image->w / sprite_num_frames;
//	sprite_h = image->h;
//	draw_sprite = true;
//
//	if (image)
//		SDL_FreeSurface(image);
//
//	return true;
//}
