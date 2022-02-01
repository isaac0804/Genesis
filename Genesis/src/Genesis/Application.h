#pragma once

#include "gspch.h"
#include "Window.h"
#include "Core.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

namespace Genesis {

	class GENESIS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		// Window and Layers
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		// Rendering 
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Shader> m_SquareShader;
		
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> m_SquareVertexArray;

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<VertexBuffer> m_SquareVertexBuffer;
		
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<IndexBuffer> m_SquareIndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();

}

