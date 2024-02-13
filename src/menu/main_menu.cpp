#include "../Common.hpp"
#include "utility/Settings.h"
#include "../SelfFeatures.h"
#include "menu/submenu/self.hpp"
#include "menu/submenu.h"
#include "menu/submenu/settings.hpp"
namespace VX
{


	bool MainMenu::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType MainMenu::GetType()
	{
		return ScriptType::Game;
	}

	void MainMenu::Initialize()
	{
		m_Initialized = 1;
		using namespace UserInterface;
		g_Ui->AddSubmenu<RegularSubmenu>("Home", SubmenuHome, [](RegularSubmenu* sub)
		{			
			sub->AddOption<SubOption>("Self", nullptr, SubmenuPlayer);
			sub->AddOption<SubOption>("Weapon", nullptr, SubmenuTest);
			sub->AddOption<SubOption>("Network", nullptr, SubmenuNetwork);
			sub->AddOption<SubOption>("Vehicle", nullptr, SubmenuTest);
			sub->AddOption<SubOption>("Teleport", nullptr, SubmenuTest);
			sub->AddOption<SubOption>("World", nullptr, SubmenuTest);
			sub->AddOption<SubOption>("Recovery", nullptr, SubmenuTest);
			sub->AddOption<SubOption>("Spawner", nullptr, SubmenuTest);
			sub->AddOption<SubOption>("Protection", nullptr, SubmenuTest);
			sub->AddOption<SubOption>("Settings", nullptr, SubmenuSettings);
		});
	}

	void MainMenu::Destroy()
	{
		g_Ui.reset();
	}
	void MainMenu::Tick()
	{
		Self::SelfLoop();
		g_Ui->OnTick();
		GetSelf()->Update();
		GetSettings()->Update();
	}
}
