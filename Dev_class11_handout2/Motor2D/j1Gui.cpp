#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load("gui/atlas.png");

	return true;
}


bool j1Gui::Update(float dt)
{
	for (uint i = 0; i < UiElement.size(); i++)
	{
		if (UiElement[i] != nullptr)
		{
			UiElement[i]->Update(dt);
			UiElement[i]->Draw(atlas);
		}
	}



	return true;

}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

UIImage* j1Gui::AddImage(iPoint position, SDL_Rect rect, SDL_Texture* texture, j1Module* listener, bool dragable)
{
	UIImage* newImage = new UIImage(position, rect, texture, ElementType::ImageElement, listener, dragable);
	UiElement.push_back((UIElement*)newImage);
	return newImage;
}

UILabel* j1Gui::AddLabel(iPoint position, char* text, SDL_Color color, _TTF_Font* font, j1Module* listener, bool dragable, uint wrap_length)
{
	SDL_Texture* tex = App->font->Print(text, color, font);
	uint width = 0,height = 0;
	App->tex->GetSize(tex,width,height);
	UILabel* newLabel = new UILabel(position, tex, {0,0,(int)width,(int)height}, ElementType::LabelElement, listener, dragable);
	UiElement.push_back((UIElement*)newLabel);
	return newLabel;
}
