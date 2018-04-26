#include "UILabel.h"
#include "j1App.h"
#include "j1Render.h"



UILabel::UILabel(iPoint position, SDL_Texture* texture, SDL_Rect rect, ElementType type, j1Module* listener, bool dragable) : UIElement(position,rect, listener, dragable)
{
	this->type = type;
	this->texture = texture;
}

void UILabel::Draw(SDL_Texture * sprites) {

	App->render->Blit(texture, positionUi.x, positionUi.y, &rectUi, 0.0f);

}