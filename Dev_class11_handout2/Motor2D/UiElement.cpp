#include "UIElement.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Gui.h"



UIElement::UIElement(iPoint position, SDL_Rect rect, j1Module* listener, bool drag) : localPosition(position),rectUi(rect)
{
	texture = App->gui->GetAtlas();
}

UIElement::~UIElement()
{
	App->tex->UnLoad((SDL_Texture*)texture);
}

void UIElement::Update(float dt)
{
	//set the position for all childs
	if (parent != nullptr)
		positionUi = { localPosition.x + parent->positionUi.x,localPosition.y + parent->positionUi.y };
	else
		positionUi = { localPosition.x, localPosition.y };

}

void UIElement::Draw(SDL_Texture* sprite)
{
	App->render->Blit(texture, positionUi.x, positionUi.y, &rectUi, 0.0f);
}


void UIElement::SetParent(UIElement* parent)
{
	this->parent = parent;
	positionToDraw = parent->positionToDraw + 1;
}

void UIElement::SetLocalPosition(iPoint p)
{
	localPosition.x = p.x;
	localPosition.y = p.y;
}