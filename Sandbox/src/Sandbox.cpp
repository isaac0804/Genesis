#include <Genesis.h>

#include "ImGui/imgui.h"

class ExampleLayer : public Genesis::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		GS_INFO("ExampleLayer::OnUpdate");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::Text("Hello World!");
	}

	void OnEvent(Genesis::Event& event) override
	{
		//GS_TRACE("{0}", event);
	}
};

class Sandbox : public Genesis::Application
{
public: 
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Genesis::Application* Genesis::CreateApplication()
{
	return new Sandbox();
}
