#include "gspch.h"
#include "RenderCommand.h"

#include "Platforms/OpenGL/OpenGLRendererAPI.h"

namespace Genesis {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}