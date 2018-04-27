#ifndef _UIIMAGE_
#define _UIIMAGE_

#include "UiElement.h"


class UIImage : public UIElement
{
public:

	UIImage(iPoint, SDL_Rect, SDL_Texture*, ElementType, j1Module*, bool);

private:
	SDL_Texture* texture;
};


#endif