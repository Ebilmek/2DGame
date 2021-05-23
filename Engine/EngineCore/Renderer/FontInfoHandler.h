#pragma once
#include "TextRenderable.h"

class FontInfoHandler
{
public:
	/**
	 * \brief Add information to container
	 * \param _text_renderable Information to add
	 */
	void AddFontInfo(std::shared_ptr<TextRenderable> _text_renderable);
	
	/**
	 * \brief Remove information to container if it's in
	 * \param _text_renderable Information to remove
	 * \return True if information was found and removed
	 */
	bool RemoveFontInfo(std::shared_ptr<TextRenderable> _text_renderable);

	
	/**
	 * \brief Gets requested information at stated position, safe
	 * \param _position Position of requested information
	 * \return Information at position or empty pointer if outside of range.
	 */
	std::shared_ptr<TextRenderable> GetFontInfo(unsigned int _position);
	
	/**
	 * \brief Amount of information in container
	 * \return Amount of information in container
	 */
	size_t GetFontInfoAmount() const;

	
	/**
	 * \brief Sorts the information based on layer and z-value
	 */
	void SortFontInfo();
private:
	std::vector<std::shared_ptr<TextRenderable>> renderables_;
};
