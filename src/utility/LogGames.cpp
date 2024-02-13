#include "pointers/gtapointers.hpp"
#include "utility/LogGames.hpp"
#include "UI/UIManager.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

namespace VX
{
	bool LogGames::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType LogGames::GetType()
	{
		return ScriptType::D3D;
	}

	void LogGames::Initialize()
	{
		m_Initialized = true;
	}

	void LogGames::Destroy()
	{
	}

	namespace
	{
		std::size_t s_LastLogCount = 0;
	}

	void LogGames::Tick()
	{
		if (g_Ui->m_Opened && g_Settings.m_LogWindow)
		{
			
		}
	}
}
