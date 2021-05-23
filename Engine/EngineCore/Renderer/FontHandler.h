#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include "FontInfo.h"
#include "FontInfoHandler.h"
#include "ImageContainer.h"
#include "ObserverFont.h"
#include "TextRenderable.h"

class FontHandler : public ObserverFont
{
public:
	FontHandler();
	virtual ~FontHandler();	

	/**
	 * \brief Register TextRenderable with renderer and load texture
	 * \param _renderable Information for font texture
	 * \param _renderer Renderer for the window
	 * \return If creation of the texture succeeded
	 */
	bool RegisterRenderable(std::shared_ptr<TextRenderable> _renderable, SDL_Renderer& _renderer);
	
	/**
	 * \brief Remove information and texture 
	 * \param _renderable Information for the font texture
	 * \return If information was found and removed
	 */
	bool RemoveRenderable(std::shared_ptr<TextRenderable> _renderable);

	/**
	 * \brief Retrieve texture pointer
	 * \param _name Name of texture file
	 * \return Texture pointer
	 */
	SDL_Texture* GetTexture(const std::string& _name);

	/**
	 * \brief Sort Information by layer and z-value
	 */
	void SortPoolByZ();
	
	/**
	 * \brief Get the amount of information stored
	 * \return Get the amount of information stored
	 */
	size_t GetPoolAmount();
	
	/**
	 * \brief Get information at a given position in the container, safe
	 * \param _position Position in the container, checked if within range
	 * \return Shared pointer to information
	 */
	std::shared_ptr<TextRenderable> GetTextRenderableAt(unsigned int _position) const;

	// Inherited via Observer
	virtual void OnNotify(FontInfo _info, Event _event) override;
private:
	SDL_Texture* CreateFontTexture(FontInfo& _font_info, TTF_Font* _font, SDL_Renderer* _renderer);

	void AddText(const std::string& _name, SDL_Texture& _texture);

	void RemoveText(const std::string& _name);

	void UpdateText();

	bool is_info_sorted_by_z_ = true;

	std::unordered_map<std::string, ImageContainer> text_image_container_;

	std::string file_path_;

	std::unique_ptr<FontInfoHandler> font_info_handler_ = std::make_unique<FontInfoHandler>();
};
