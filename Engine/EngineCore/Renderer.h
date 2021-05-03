#pragma once
#include <unordered_map>

#include "Font.h"
#include "Renderable.h"
#include "SDL_render.h"
#include "TextRenderable.h"
#include "TextureHandler.h"

class Renderer
{
public:
	Renderer() = default;
	
	/**
	 *	\brief Copies the stored textures into the given renderer using the stored data
	 *	\returns SDL return from the copy if there is an error
	 */
	int CopyToBuffer(SDL_Renderer& _renderer);

	/**
	 * \brief Tie the object to the renderable 
	 * \param _renderable Object that can be rendered
	 * \param _renderer The current window renderer
	 * \return If the process failed
	 */
	bool RegisterRenderable(const Renderable& _renderable, SDL_Renderer& _renderer);

	bool RegisterRenderable(TextRenderable& _renderable, SDL_Renderer& _renderer, std::string _text, Font* _font);
	
	/**
	 * \brief Unlink the renderable and update the texture pool
	 * \param _renderable Renderable to unlink
	 * \return If the process failed
	 */
	bool RemoveRenderable(const std::shared_ptr<Renderable>& _renderable);

	/**
	 *	\brief Gets amount of textures stored
	 *	\return Amount of textures stored by the texture handler (Can return 0 if texture handler was a nullptr)
	 */
	size_t GetStoredTextureAmount() const;
	
	/**
	 *	\brief Gets the amount of information, does represent how many are being rendered to the screen each frame
	 *	\return Amount of texture information stored
	 */
	size_t GetStoredTextureInfoAmount() const;
private:
	std::vector<std::weak_ptr<const Renderable>> renderables_;

	bool is_texture_info_sorted_by_z_ = false;

	std::unique_ptr<TextureHandler> texture_handler_ = std::make_unique<TextureHandler>();
};
