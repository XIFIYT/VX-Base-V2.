#include "UI/components/header.hpp"
#include "GTA/Natives.hpp"
#include "menu/submenu/self.hpp"
#include "menu/submenu.h"
#include "menu/submenu/self/animation.hpp"
namespace VX
{
	SelfMenu g_Self;
using namespace UserInterface;
	void SelfMenu::Init()
    {
        using namespace UserInterface;
      g_Ui->AddSubmenu<RegularSubmenu>("Player", SubmenuPlayer, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Animation", nullptr,  SubmenuAnimation);
		});
    }
    void SelfMenu::Update()
    {
        Init();
        GetAnimation()->Update();
    }

	SelfMenu* GetSelf() { return &g_Self; }
}