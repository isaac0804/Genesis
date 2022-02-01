#include "gspch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLVertexArray.h"

namespace Genesis {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:     GS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:   return new OpenGLVertexArray();
		}
		GS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

}