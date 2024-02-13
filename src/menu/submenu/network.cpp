#include "UI/components/header.hpp"
#include "GTA/Natives.hpp"
#include "menu/submenu/self.hpp"
#include "menu/submenu.h"
#include "menu/submenu/self/animation.hpp"
#include "menu/submenu/network/playerlist.hpp"
#include "menu/submenu/network.hpp"
namespace VX
{
	NetworkMenu g_Network;
using namespace UserInterface;
	void NetworkMenu::Init()
    {
        using namespace UserInterface;
        g_Ui->AddSubmenu<RegularSubmenu>("Network", SubmenuNetwork, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Players", nullptr, SubmenuPlayerList);
		});
    }
    void NetworkMenu::Update()
    {
        Init();
        GetPlayerList()->Update();
    }

	NetworkMenu* GetNetwork() { return &g_Network; }
}