#pragma once

// - - - - - -
// Video system entry point
// - - - - - -

#include <GL/glew.h>
#include "../Core/Core.hpp"
#include "GLEWException.hpp"

using namespace Core;

namespace Video
{
	void Init();
	void Quit();
	bool IsInitialized();
}

#include "PixelRect.hpp"
#include "Shader.hpp"
#include "Model.hpp"
#include "FBXImporter.hpp"
#include "Material.hpp"
#include "Window.hpp"