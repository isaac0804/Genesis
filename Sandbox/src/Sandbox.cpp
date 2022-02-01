#include <Genesis.h>

#include "ImGui/imgui.h"

class ExampleLayer : public Genesis::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Genesis::Event& event) override
	{
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
