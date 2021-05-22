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

	void AddText(const std::string& _name, SDL_Texture& _texture);
	void UpdateText();
	void RemoveText(const std::string& _name);

	void AddFont();
	void CreateTextFromFont();
	void RemoveFont();

	bool RegisterRenderable(std::shared_ptr<TextRenderable> _renderable, SDL_Renderer& _renderer);
	bool RemoveRenderable(std::shared_ptr<TextRenderable> _renderable);

	SDL_Texture* GetTexture(const std::string& _name);

	void SortPoolByZ();
	size_t GetPoolAmount();
	std::shared_ptr<TextRenderable> GetTextRenderableAt(unsigned int _position) const;

	// Inherited via Observer
	virtual void OnNotify(FontInfo _info, Event _event) override;
private:
	SDL_Texture* CreateFontTexture(FontInfo& _font_info, TTF_Font* _font, SDL_Renderer* _renderer);

	bool is_info_sorted_by_z_ = true;

	std::unordered_map<std::string, ImageContainer> text_image_container_;

	std::string file_path_;

	std::unique_ptr<FontInfoHandler> font_info_handler_ = std::make_unique<FontInfoHandler>();
};
