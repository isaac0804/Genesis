#include "gspch.h"
#include "Application.h"

#include "Genesis/Events/ApplicationEvent.h"
#include "Genesis/Log.h"

namespace Genesis {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run() 
	{
		WindowResizeEvent e(1280, 720);
		GS_TRACE(e);
		while (true);
	}
}
