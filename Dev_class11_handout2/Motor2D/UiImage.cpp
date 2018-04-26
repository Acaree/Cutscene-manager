#include "UiImage.h"


UIImage::UIImage(iPoint position, SDL_Rect rect, SDL_Texture* texture, ElementType type, j1Module* listener, bool dragable) : UIElement(position, rect, listener, dragable)
{
	this->type = type;
}