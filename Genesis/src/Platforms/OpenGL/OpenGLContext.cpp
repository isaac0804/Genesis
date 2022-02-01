#include "gspch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace Genesis {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		GS_CORE_ASSERT(windowHandle, "Window Handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GS_CORE_ASSERT(status, "Failed to initialize Glad!");

		GS_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		GS_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		GS_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}