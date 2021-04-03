#pragma once
#include <string>
#include <unordered_map>

#include "SDL_render.h"

#include "ImageContainer.h"


/*
 *	Texture Handler
 *	Handle loading of textures and probably copying to buffer
 *	- Reduce chance of repeated loading of the same texture (hashing), have a use count increased with number of refs in container below
 *	- Deal with sprite sheets?
 *	- Struct of information (location, rotation, orientation etc. + image name + z-value)
 *	- Contain for storing tonnes of the above + if image isn't on the list loaded, load it.
 *	- Render/Copy to buffer function - Sort the 
 */

class TextureHandler
{
public:
	TextureHandler();

	// Load texture if not present, otherwise add one to the ref count
	void AddTexture(const std::string& name, SDL_Renderer* renderer);

	// Remove one from the ref count, if 0 delete the texture.
	void RemoveTexture(const std::string& name);

	SDL_Texture* GetTexture(const std::string& name);

private:
	std::unordered_map<std::string, ImageContainer*> texturePool;
};

inline SDL_Texture* TextureHandler::GetTexture(const std::string& name)
{
	return texturePool[name]->image;
}
