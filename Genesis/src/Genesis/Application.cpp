#include "gspch.h"
#include "Application.h"
#include "Input.h"
#include "Genesis/Log.h"
#include "Genesis/Renderer/Renderer.h"



namespace Genesis {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		GS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Vertex Array ///////////////////////////////////////////////////////
		m_VertexArray.reset(VertexArray::Create());
		m_SquareVertexArray.reset(VertexArray::Create());

		// Vertex Buffer //////////////////////////////////////////////////////
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
		 	 0.0f,  0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
		};
		float squareVertices[4 * 3] = {
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		 	-0.75f, -0.75f, 0.0f,
		 	 0.75f, -0.75f, 0.0f,
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_SquareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		// Define Buffer Layout 
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color" }
		};
		BufferLayout squareLayout = {
			{ ShaderDataType::Float3, "a_Position"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_SquareVertexBuffer->SetLayout(squareLayout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);

		// Index Buffer ///////////////////////////////////////////////////////
		unsigned int indices[3] = { 0, 1, 2 };
		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, std::size(indices)));
		m_SquareIndexBuffer.reset(IndexBuffer::Create(squareIndices, std::size(squareIndices)));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		m_SquareVertexArray->SetIndexBuffer(m_SquareIndexBuffer);

		// Shader /////////////////////////////////////////////////////////////
		// Vertex Shader
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() 
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string squareVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main() 
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		// Fragment Shader
		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main() 
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		std::string squareFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() 
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		m_SquareShader.reset(new Shader(squareVertexSrc, squareFragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::Run() 
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({0.1f, 0.1f, 0.2f, 1});
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_SquareShader->Bind();
			Renderer::Submit(m_SquareVertexArray);
			//m_SquareVertexArray->Bind();
			//glDrawElements(GL_TRIANGLES, m_SquareIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);
			//m_VertexArray->Bind();
			//glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}
