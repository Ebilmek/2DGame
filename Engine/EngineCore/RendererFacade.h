#pragma once
#include "Renderer.h"

/*
 * Storage of pointers to the two renderers
 * Actual window renderer (SDL)
 * And glorified image sorter (Renderer)
 *
 * Purely storage does not delete pointers
 */

class RendererFacade
{
public:
	// Singleton implementation
	// Scott Meyers Effective Modern C++ better error message if the deleted functions are in public
	static RendererFacade& GetInstance()
	{
		static RendererFacade instance;
		return instance;
	}

private:
	RendererFacade() = default;
	~RendererFacade() = default;
public:
	RendererFacade(RendererFacade const&) = delete;
	void operator=(RendererFacade const&) = delete;
	
private:
	Renderer* renderer_ = nullptr;
	SDL_Renderer* sdl_renderer_ = nullptr;

public:
	void SetRenderer(Renderer* _renderer) { renderer_ = _renderer; }
	void SetSDLRenderer(SDL_Renderer* _sdl_renderer) { sdl_renderer_ = _sdl_renderer; }
	void SetRenderers(Renderer* _renderer, SDL_Renderer* _sdl_renderer)
	{
		SetRenderer(_renderer);
		SetSDLRenderer(_sdl_renderer);
	}

	Renderer* GetRenderer()
	{
		if(renderer_ != nullptr)
			return renderer_;
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer not stored within facade");
		return nullptr;
	}

	SDL_Renderer* GetSDLRenderer()
	{
		if (sdl_renderer_ != nullptr)
			return sdl_renderer_;
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer not stored within facade");
		return nullptr;
	}
};