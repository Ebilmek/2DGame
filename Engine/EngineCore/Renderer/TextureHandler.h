#pragma once
#include <string>
#include <unordered_map>

#include "ImageContainer.h"
#include "ObserverSprite.h"
#include "SDL_render.h"
#include "Sprite.h"
#include "TextureInfoHandler.h"


/*
 *	Texture Handler
 *	Handle loading of textures and probably copying to buffer
 *	- Reduce chance of repeated loading of the same texture (hashing), have a use count increased with number of refs in container below
 *	- Deal with sprite sheets?
 *	- Struct of information (location, rotation, orientation etc. + image name + z-value)
 *	- Contain for storing tonnes of the above + if image isn't on the list loaded, load it.
 *	- Render/Copy to buffer function - Sort the 
 */

class TextureHandler : public ObserverSprite
{
public:
	TextureHandler();
	~TextureHandler();

	// Load texture if not present, otherwise add one to the ref count
	bool RegisterRenderable(std::shared_ptr<Sprite> _renderable, SDL_Renderer& _renderer);

	// Remove one from the ref count, if 0 delete the texture.
	bool RemoveRenderable(std::shared_ptr<Sprite> _renderable);

	/**
	 * \brief Sort the information by layer and z-value
	 */
	void SortPoolByZ();
	
	/**
	 * \brief Get amount of Sprite information stored
	 * \return Amount of Sprite information
	 */
	size_t GetPoolAmount() const;
	
	/**
	 * \brief Get Sprite information held at the stated position 
	 * \param _position Position in the container
	 * \return Sprite information
	 */
	std::shared_ptr<Sprite> GetSpriteAt(unsigned int _position);

	/**
	 * \brief Get a pointer to the loaded texture within the container
	 * \param _name Must be the shortened version of the filepath from executable to file. Full file path must not be included.
	 */
	SDL_Texture* GetTexture(const std::string& _name);

	/**
	 * \brief Get the amount of buckets in the container (unique textures)
	 * \return Amount of unique textures
	 */
	size_t GetTextureAmount() const { return texture_pool_.size(); }

	// Inherited via Observer
	void OnNotify(SpriteInfo _info, Event _event) override;

private:
	void LoadTexture(const std::string& _name, SDL_Renderer& _renderer);

	void RemoveTexture(const std::string& _name);

private:
	bool is_info_sorted_by_z_ = true;

	std::unordered_map<std::string, ImageContainer> texture_pool_;

	std::string file_path_;

	std::unique_ptr<TextureInfoHandler> texture_info_handler_ = std::make_unique<TextureInfoHandler>();
};

inline SDL_Texture* TextureHandler::GetTexture(const std::string& _name)
{
	return texture_pool_[_name].image;
}
