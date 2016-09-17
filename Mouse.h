#ifndef MOUSE_H
#define MOUSE_H
#include "Shape.h"
//The mouse button


class LButton
{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Shows button sprite
	//void render();
	//Point mClick(SDL_Event* e, SDL_Renderer *rdr);
private:
	//Top left position
	SDL_Point mPosition;

	//Currently used global sprite
	//LButtonSprite mCurrentSprite;
};


LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	//mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}
void LButton::handleEvent(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
	}
}

#endif // !MOUSE_H