#ifndef _UILABEL_
#define _UILABEL_

#include "UIElement.h"

class UILabel : public UIElement
{
public:
	UILabel(iPoint, SDL_Texture *, SDL_Rect, ElementType, j1Module*, bool);
	void Draw(SDL_Texture*);
private:
	SDL_Texture* texture;
};

#endif

