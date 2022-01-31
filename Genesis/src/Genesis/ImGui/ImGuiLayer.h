#pragma once

#include "Genesis/Layer.h"
#include "Genesis/Events/ApplicationEvent.h"
#include "Genesis/Events/KeyEvent.h"
#include "Genesis/Events/MouseEvent.h"

namespace Genesis {

	class GENESIS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	//	void OnEvent(Event& event);
	//private:
	//	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
	//	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
	//	bool OnMouseMovedEvent(MouseMovedEvent& event);
	//	bool OnMouseScrolledEvent(MouseScrolledEvent& event);
	//	bool OnKeyPressedEvent(KeyPressedEvent& event);
	//	bool OnKeyReleasedEvent(KeyReleasedEvent& event);
	//	bool OnKeyTypedEvent(KeyTypedEvent& event);
	//	bool OnWindowResizeEvent(WindowResizeEvent& event);
	private:
		float m_Time = 0.0f;
	};

}
