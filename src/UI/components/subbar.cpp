#include "UI/components/subbar.hpp"
#include "GTA/Natives.hpp"
#include "UI/drawers/DrawersHelper.hpp"
#include "UI/UIManager.hpp"
#include "UI/AbstractOption.hpp"
#include "UI/AbstractSubmenu.hpp"
namespace VX
{
	SubbarComponents g_subbar;
    using namespace UserInterface;
	void SubbarComponents::Init(AbstractSubmenu* sub)
    {
        char leftText[64] = {};
		std::strncpy(&leftText[0], sub->GetName(), sizeof(leftText) - 1);
		std::transform(std::begin(leftText), std::end(leftText), std::begin(leftText), [](char c) { return static_cast<char>(toupper(c)); });
		char centerText[64] = {};
		std::strncpy(&centerText[0], "VX Base", sizeof(centerText) - 1);
		std::transform(std::begin(centerText), std::end(centerText), std::begin(centerText), [](char c) { return static_cast<char>(toupper(c)); });
		char rightText[32] = {};
		std::snprintf(rightText, sizeof(rightText) - 1, "%zu / %zu", sub->GetSelectedOption() + 1, sub->GetNumOptions());

		DrawRect(
			g_Ui->m_PosX,
			g_Ui->m_DrawBaseY + (g_Ui->m_SubmenuBarHeight / 2.f),
			g_Ui->m_Width, g_Ui->m_SubmenuBarHeight,
			g_Ui->m_SubmenuBarBackgroundColor);
		DrawLeftText(
			&leftText[0],
			g_Ui->m_PosX - (g_Ui->m_Width / g_Ui->m_SubmenuBarPadding),
			g_Ui->m_DrawBaseY + (g_Ui->m_SubmenuBarHeight / 2.f) - (GetTextHeight(0, g_Ui->m_SubmenuBarTextSize) / 1.5f),
			g_Ui->m_SubmenuBarTextSize, 0,
			g_Ui->m_SubmenuBarTextColor,
			false, true);
		DrawRightText(
			&centerText[0],
			g_Ui->m_PosX + (g_Ui->m_Width / 10),
			g_Ui->m_DrawBaseY + (g_Ui->m_SubmenuBarHeight / 2.f) - (GetTextHeight(0, g_Ui->m_SubmenuBarTextSize) / 1.5f),
			g_Ui->m_SubmenuBarTextSize, 0,
			g_Ui->m_SubmenuBarTextColor,
			false, true);
		DrawRightText(
			&rightText[0],
			g_Ui->m_PosX + (g_Ui->m_Width / g_Ui->m_SubmenuBarPadding),
			g_Ui->m_DrawBaseY + (g_Ui->m_SubmenuBarHeight / 2.f) - (GetTextHeight(0, g_Ui->m_SubmenuBarTextSize) / 1.5f),
			g_Ui->m_SubmenuBarTextSize, 0,
			g_Ui->m_SubmenuBarTextColor,
			false, true);

		g_Ui->m_DrawBaseY += g_Ui->m_SubmenuBarHeight;
    }

	SubbarComponents* GetSubbar() { return &g_subbar; }
}