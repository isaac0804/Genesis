#include <Genesis.h>

class ExampleLayer : public Genesis::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		//GS_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(Genesis::Event& event) override
	{
		GS_TRACE("{0}", event);
	}
};

class Sandbox : public Genesis::Application
{
public: 
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new Genesis::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Genesis::Application* Genesis::CreateApplication()
{
	return new Sandbox();
}
