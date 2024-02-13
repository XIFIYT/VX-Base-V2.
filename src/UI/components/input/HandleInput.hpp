#pragma once

namespace VX
{
	class HandleInput
	{
	private:
		
	public:
        void Init();
        bool m_OpenKeyPressed = false;
		bool m_BackKeyPressed = false;
		bool m_EnterKeyPressed = false;
		bool m_UpKeyPressed = false;
		bool m_DownKeyPressed = false;
		bool m_LeftKeyPressed = false;
		bool m_RightKeyPressed = false;
	};

	HandleInput* GetHandle();
}