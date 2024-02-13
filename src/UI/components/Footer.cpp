#include "UI/components/header.hpp"
#include "GTA/Natives.hpp"
#include "UI/drawers/DrawersHelper.hpp"
#include "UI/UIManager.hpp"
#include "UI/components/Footer.hpp"
#include "UI/UIManager.hpp"
namespace VX
{
	FooterComponents g_Footer;
using namespace UserInterface;
	void FooterComponents::Init()
    {
       DrawRect(
			g_Ui->m_PosX,
			g_Ui->m_DrawBaseY + (g_Ui->m_FooterHeight / 2.f),
			g_Ui->m_Width,
			g_Ui->m_FooterHeight,
			g_Ui->m_FooterBackgroundColor);

		float size = g_Ui->m_FooterSpriteSize;
		float rotation = 0.f;
		const char* texture = "shop_arrows_upanddown";

		auto sizee = GetSpriteScale(size);

		DrawSprite(
			"commonmenu",
			texture,
			g_Ui->m_PosX,
			g_Ui->m_DrawBaseY + (g_Ui->m_FooterHeight / 2.f),
			sizee.x,
			sizee.y,
			g_Ui->m_FooterSpriteColor,
			rotation);

		g_Ui->m_DrawBaseY += g_Ui->m_FooterHeight;
    }

	FooterComponents* GetFooter() { return &g_Footer; }
}