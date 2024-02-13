#pragma once

#include <script/scrProgramTable.hpp>
#include <script/scrNativeHandler.hpp>
#include <script/scrNativeRegistration.hpp>
#include <script/scrNativeRegistrationTable.hpp>

namespace VX
{
	class GTAPointers
	{
	public:
		explicit GTAPointers();
		~GTAPointers() noexcept = default;
		GTAPointers(GTAPointers const&) = delete;
		GTAPointers(GTAPointers&&) = delete;
		GTAPointers& operator=(GTAPointers const&) = delete;
		GTAPointers& operator=(GTAPointers&&) = delete;
		
		std::uint32_t* m_FrameCount;
		HWND m_GameWindow;
		IDXGISwapChain* m_Swapchain;
		rage::scrProgramTable* m_ScriptProgramTable;
		rage::scrNativeRegistrationTable* m_NativeRegistrations;
		std::uint64_t** m_GlobalBase;
		std::int64_t** m_ScriptGlobals;
		PVOID m_ModelSpawnBypass;
		char* m_GameBuild;
		uint64_t m_WorldPtr;
		using GetLabelText = const char*(void* unk, const char* label);
		GetLabelText* m_GetLabelText;

		using GetNativeHandler = rage::scrNativeHandler(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
		GetNativeHandler* m_GetNativeHandler;

		using WndProc = LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		WndProc* m_WndProc;

		using FixVectors = void(rage::scrNativeCallContext*);
		FixVectors* m_FixVectors;

		using QueueDependency = void(void* dependency);
		QueueDependency* m_QueueDependency;
	};

	inline std::unique_ptr<GTAPointers> g_gtaPointers;
}
