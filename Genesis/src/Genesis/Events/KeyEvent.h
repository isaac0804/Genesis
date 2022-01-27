#pragma once

#include "Event.h"

namespace Genesis {

	class GENESIS_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode;  }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}
		
		int m_KeyCode;
	};

	class GENESIS_API KeyPressedEvent : puclic KeyEvent
	{
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeat_count) {}
		
		inline int GetRepeatCount() const { return m_RepeatCount;  }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << "repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private: 
		int m_RepeatCount;
	};

	class GENESIS_API KeyReleasedEvent : puclic KeyEvent
	{
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}
		
		inline int GetRepeatCount() const { return m_RepeatCount;  }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
