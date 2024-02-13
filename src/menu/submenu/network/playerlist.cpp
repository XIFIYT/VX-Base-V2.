#include "UI/components/header.hpp"
#include "GTA/Natives.hpp"
#include "menu/submenu/self.hpp"
#include "menu/submenu.h"
#include "menu/submenu/self/animation.hpp"
#include "menu/submenu/network/playerlist.hpp"
#include "menu/submenu/network.hpp"
namespace VX
{
	PlayerListMenu g_PlayerList;
using namespace UserInterface;
	void PlayerListMenu::Init()
    {
        using namespace UserInterface;
       	g_Ui->AddSubmenu<RegularSubmenu>("Players", SubmenuPlayerList, [](RegularSubmenu* sub)
		{
			for (std::uint32_t i = 0; i < 32; ++i)
			{
				if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
				{
					sub->AddOption<SubOption>(PLAYER::GET_PLAYER_NAME(i), nullptr, SubmenuSelectedPlayer, [=]
					{
						selectedPlayer = i;
					});
				}
			}
		});
		g_Ui->AddSubmenu<PlayerSubmenu>(&selectedPlayer, SubmenuSelectedPlayer, [](PlayerSubmenu* sub)
		{
			sub;
		});
    }
    void PlayerListMenu::Update()
    {
        Init();
    }

	PlayerListMenu* GetPlayerList() { return &g_PlayerList; }
}