#ifndef _UIELEMENT_
#define _UIELEMENT_

#include "SDL/include/SDL.h"
#include "p2Defs.h"
#include "p2Point.h"
#include "j1Textures.h"

class j1Module;

enum ElementType
{
	NoTypeElement,
	LabelElement,
	ImageElement,
};


class UIElement
{
public:
	UIElement(iPoint, SDL_Rect, j1Module*, bool);

	virtual void Update(float);
	virtual void Draw(SDL_Texture*);
	void SetParent(UIElement*);
	void SetLocalPosition(iPoint);
	virtual ~UIElement();

	ElementType type = ElementType::NoTypeElement;
	uint positionToDraw = 0;
	iPoint positionUi = { 0,0 };
	bool toDelete = false;
	iPoint localPosition = { 0,0 };
protected:
	UIElement* parent = nullptr;
	//SDL_Texture* texture = nullptr;
	SDL_Rect rectUi;

};

#endif


