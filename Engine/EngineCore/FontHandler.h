#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include "FontInfo.h"
#include "ImageContainer.h"
#include "ObserverFont.h"
#include "TextRenderable.h"
#include "Font.h"

class FontHandler : public ObserverFont
{
public:
	FontHandler();
	virtual ~FontHandler();

	void AddText(const std::string& _name, SDL_Texture& _texture);
	void UpdateText();
	void RemoveText();

	void AddFont();
	void CreateTextFromFont();
	void RemoveFont();

	bool RegisterRenderable(std::shared_ptr<TextRenderable> _renderable, SDL_Renderer& _renderer);
	bool RemoveRenderable(std::shared_ptr<TextRenderable> _renderable);

	SDL_Texture* GetTexture(const std::string& _name);

	void SortPoolByZ();
	int GetPoolAmount();
	std::weak_ptr<const TextRenderable> GetTextRenderableAt(unsigned int position);

	// Inherited via Observer
	virtual void OnNotify(FontInfo _info, Event _event) override;
private:
	std::vector<std::shared_ptr<const TextRenderable>> renderables_;

	bool is_info_sorted_by_z_ = true;

	std::unordered_map<std::string, ImageContainer> text_image_container_;

	std::string file_path_;
};
