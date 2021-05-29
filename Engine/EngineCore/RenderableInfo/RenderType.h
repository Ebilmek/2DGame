#pragma once

enum class RenderType
{
	// Solid, Shaded, Blended, Wrap
	kSolid,		// Basic 8bit fast render
	kShaded,	// Requires background colour
	kBlended,	// Higher quality 32bit
	kWrap		// Requires wrap length in pixels (Blended with a wrap size)
};
