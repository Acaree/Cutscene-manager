#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UiElement.h"
#include "UiImage.h"
#include "UiLabel.h"
#include "j1Fonts.h"


#include <vector>


// TODO 1: Create your structure of classes

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	bool Update(float);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	SDL_Texture* GetAtlas() const;

	UIImage* AddImage(iPoint, SDL_Rect, SDL_Texture*, j1Module*, bool);
	UILabel* AddLabel(iPoint position, char* text, SDL_Color color, _TTF_Font* font, j1Module* listener, bool dragable, uint wrap_length);
private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	std::vector<UIElement*> UiElement;
};

#endif // __j1GUI_H__