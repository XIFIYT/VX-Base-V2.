#include "UI/components/header.hpp"
#include "GTA/Natives.hpp"
#include "menu/submenu/self/animation.hpp"
#include "menu/submenu.h"
namespace VX
{
	AnimationMenu g_AnimationMenu;
using namespace UserInterface;
	void AnimationMenu::Init()
    {
        using namespace UserInterface;
      g_Ui->AddSubmenu<RegularSubmenu>("Animation", SubmenuAnimation, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Teste", nullptr, SubmenuTest);
		});
    }
    void AnimationMenu::Update()
    {
        Init();
    }

	AnimationMenu* GetAnimation() { return &g_AnimationMenu; }
}