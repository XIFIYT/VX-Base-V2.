#include "pointers/gtapointers.hpp"
#include "Hook/Hooking.hpp"
#include "Hook/NativeHook.hpp"
#include "Script/manager/ScriptManager.hpp"
#include "utility/LogGames.hpp"
#include "menu/main_menu.hpp"
#include "Script/callback/ScriptCallback.hpp"
#include "GTA/Invoker.hpp"
#include "utility/glt/CustomText.hpp"
#include "D3D/D3DRenderer.hpp"
#include "UI/UIManager.hpp"

#include "utility/Settings.h"
#include "pointers/pointers.hpp"
#include "log/log.hpp"
#include "file/file_manager.hpp"
#include "utility/Util.hpp"

BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
	using namespace VX;

	if (reason == DLL_PROCESS_ATTACH)
	{
		m_Module = hInstance;
		CreateThread(0, 0, [](LPVOID) -> DWORD
		{
			auto logger_instance = std::make_unique<logger>("Virtual Engine", g_file_manager.get_project_file("./cout.log"));
			LOG(INFO) << VX_NAME << " Injected successfully! ";

			namespace fs = std::filesystem;
			if (!fs::exists(GetMenuPath()))
			fs::create_directory(GetMenuPath());
			fs::create_directory(GetMenuPath() + ("\\Textures"));

			g_gtaPointers = std::make_unique<GTAPointers>();
			auto pointers_instance = std::make_unique<pointers>();

			g_settings.load();

			while (*g_pointers->m_game_state != 0)
			{
				std::this_thread::sleep_for(2ms);
				std::this_thread::yield();
			}
			g_CustomText = std::make_unique<CustomText>();
			g_D3DRenderer = std::make_unique<D3DRenderer>();
			g_Ui = std::make_unique<UserInterface::UIManager>();
			g_ScriptManager = std::make_unique<ScriptManager>();
			g_MainMenu = std::make_shared<MainMenu>();
			g_LogGames = std::make_shared<LogGames>();
			g_FiberScript = std::make_shared<FiberScript>();
			g_ScriptManager->AddScript(g_MainMenu);
			g_ScriptManager->AddScript(g_LogGames);
			g_ScriptManager->AddScript(g_FiberScript);

			g_Hooking = std::make_unique<Hooking>();
			g_Hooking->Hook();

			auto g_NativeHook = std::make_unique<NativeHooks>();

			while (m_CheatRunning)
			{
				if (IsKeyPressed(VK_DELETE))
					m_CheatRunning = false;
				std::this_thread::sleep_for(3ms);
				std::this_thread::yield();
			}

			std::this_thread::sleep_for(100ms);

			g_NativeHook.reset();

			g_Hooking->Unhook();

			g_ScriptManager.reset();
			g_LogGames.reset();
			g_MainMenu.reset();
			g_FiberScript.reset();
			g_Ui.reset();
			g_D3DRenderer.reset();
			g_CustomText.reset();

			std::this_thread::sleep_for(100ms);

			g_Hooking.reset();
			g_gtaPointers.reset();
			pointers_instance.reset();
			LOG(INFO) << VX_NAME << " Uninjected successfully! ";
			logger_instance.reset();
			logger_instance->destroy();

			FreeLibraryAndExitThread(m_Module, 0);
		},
		0,
		0,
		0);
	}

	return 1;
}
