#include "UI/components/header.hpp"
#include "GTA/Natives.hpp"
#include "UI/drawers/DrawersHelper.hpp"
#include "UI/UIManager.hpp"
#include "UI/components/option.hpp"
namespace VX
{
    OptionComponents g_option;

    void OptionComponents::Init(AbstractOption *opt, bool selected)
    {
        const char *shouldText = "";
        int shouldDrawTick = 0;
        if ((!std::strcmp(opt->GetRightText(), "~r~") || !std::strcmp(opt->GetRightText(), "~g~")))
        {
            if ((!std::strcmp(opt->GetRightText(), "~r~")))
            {
                shouldText = "";
                shouldDrawTick = 1;
            }
            else
            {
                shouldText = "";
                shouldDrawTick = 2;
            }
        }
        else
        {
            shouldText = opt->GetRightText();
        }
        DrawRect(
            g_Ui->m_PosX,
            g_Ui->m_DrawBaseY + (g_Ui->m_OptionHeight / 2.f),
            g_Ui->m_Width,
            g_Ui->m_OptionHeight,
            selected ? g_Ui->m_OptionSelectedBackgroundColor : g_Ui->m_OptionUnselectedBackgroundColor);
        DrawLeftText(
            opt->GetLeftText(),
            g_Ui->m_PosX - (g_Ui->m_Width / g_Ui->m_OptionPadding),
            g_Ui->m_DrawBaseY + (g_Ui->m_OptionHeight / 2.f) - (GetTextHeight(0, g_Ui->m_OptionTextSize) / 1.5f),
            g_Ui->m_OptionTextSize,
            0,
            selected ? g_Ui->m_OptionSelectedTextColor : g_Ui->m_OptionUnselectedTextColor,
            false, false);
        DrawRightText(
            opt->GetRightText(),
            g_Ui->m_PosX + (g_Ui->m_Width / g_Ui->m_OptionPadding),
            g_Ui->m_DrawBaseY + (g_Ui->m_OptionHeight / 2.f) - (GetTextHeight(0, g_Ui->m_OptionTextSize) / 1.5f),
            g_Ui->m_OptionTextSize,
            0,
            selected ? g_Ui->m_OptionSelectedTextColor : g_Ui->m_OptionUnselectedTextColor,
            false, false);
        if (shouldDrawTick == 1)
        {
            DrawSprite("commonmenu", "common_medal", g_Ui->m_PosX + (g_Ui->m_Width / g_Ui->m_OptionPadding) - 0.01,
                       g_Ui->m_DrawBaseY + (g_Ui->m_OptionHeight / 2.0f) - (GetTextHeight(0, g_Ui->m_OptionTextSize) / 1.5f) + 0.0125, g_Ui->m_OptionTextSize * 0.055,
                       g_Ui->m_OptionTextSize * 0.10, g_Ui->m_Toggle_Off, 0);
        }
        else if (shouldDrawTick == 2)
        {
            DrawSprite("commonmenu", "common_medal", g_Ui->m_PosX + (g_Ui->m_Width / g_Ui->m_OptionPadding) - 0.01,
                       g_Ui->m_DrawBaseY + (g_Ui->m_OptionHeight / 2.0f) - (GetTextHeight(0, g_Ui->m_OptionTextSize) / 1.5f) + 0.0125, g_Ui->m_OptionTextSize * 0.055,
                       g_Ui->m_OptionTextSize * 0.10, g_Ui->m_Toggle_On, 0);
        }
        if (opt->GetFlag(OptionFlag::Enterable))
        {
            DrawRightText(
                ">",
                g_Ui->m_PosX + (g_Ui->m_Width / g_Ui->m_OptionPadding),
                g_Ui->m_DrawBaseY + (g_Ui->m_OptionHeight / 2.f) - (GetTextHeight(2, g_Ui->m_OptionTextSize) / 1.725f),
                g_Ui->m_OptionTextSize,
                2,
                selected ? g_Ui->m_OptionSelectedTextColor : g_Ui->m_OptionUnselectedTextColor,
                false, false);
        }

        g_Ui->m_DrawBaseY += g_Ui->m_OptionHeight;
    }

    OptionComponents *GetOption() { return &g_option; }
}