#include "UI/components/header.hpp"
#include "GTA/Natives.hpp"
#include "UI/drawers/DrawersHelper.hpp"
#include "UI/UIManager.hpp"
#include "UI/components/Footer.hpp"
#include "UI/UIManager.hpp"
#include "UI/components/Desc.hpp"
namespace VX
{
	DescComponents g_Desc;
using namespace UserInterface;
	void DescComponents::Init()
    {
      const char* description{};

		if (!g_Ui->m_SubmenuStack.empty())
		{
			auto sub = g_Ui->m_SubmenuStack.top();
			if (sub->GetNumOptions())
			{
				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					description = opt->GetDescription();
				}
			}
		}

		if (!description || !*description)
			return;

		g_Ui->m_DrawBaseY += g_Ui->m_DescriptionHeightPadding;

		DrawRect(
			g_Ui->m_PosX,
			g_Ui->m_DrawBaseY + (g_Ui->m_DescriptionHeight / 2.f),
			g_Ui->m_Width,
			g_Ui->m_DescriptionHeight,
			g_Ui->m_DescriptionBackgroundColor);
		DrawRect(
			g_Ui->m_PosX,
			g_Ui->m_DrawBaseY - 0.0001f,
			g_Ui->m_Width + 0.0005f, 0.0026f,
			{ 0, 255, 255, 255 });
		auto spriteSize = GetSpriteScale(g_Ui->m_DescriptionSpriteSize);
		DrawSprite(
			"shared", "info_icon_32",
			g_Ui->m_PosX - (g_Ui->m_Width / g_Ui->m_DescriptionPadding) + (spriteSize.x / 2.f),
			g_Ui->m_DrawBaseY + (g_Ui->m_DescriptionHeight / 2.f),
			spriteSize.x,
			spriteSize.y,
			g_Ui->m_DescriptionSpriteColor,
			0.f
		);

		DrawLeftText(
			description,
			g_Ui->m_PosX - (g_Ui->m_Width / g_Ui->m_DescriptionPadding) + (spriteSize.x * 1.15f),
			g_Ui->m_DrawBaseY + (g_Ui->m_DescriptionHeight / 2.f) - (GetTextHeight(0, g_Ui->m_DescriptionTextSize) / 1.5f),
			g_Ui->m_DescriptionTextSize,
			0,
			g_Ui->m_DescriptionTextColor,
			false, false
		);

		g_Ui->m_DrawBaseY += g_Ui->m_DescriptionHeight;
    }

	DescComponents* GetDesc() { return &g_Desc; }
}