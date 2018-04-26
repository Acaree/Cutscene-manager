#include "j1App.h"
#include "Entity.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Textures.h"

Entity::Entity(int x, int y) : position(x, y)
{

}

Entity::~Entity()
{
	
}

void Entity::Draw(SDL_Texture* sprites)
{
	
	if (animation != nullptr) {
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
	}
}
