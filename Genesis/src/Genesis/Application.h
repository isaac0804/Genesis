#pragma once

#include "gspch.h"
#include "Core.h"
#include "Events/Event.h"
#include "Genesis/Events/ApplicationEvent.h"
#include "Window.h"

namespace Genesis {

	class GENESIS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in client
	Application* CreateApplication();

}

