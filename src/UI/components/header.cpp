#include "UI/components/header.hpp"
#include "GTA/Natives.hpp"
#include "UI/drawers/DrawersHelper.hpp"
#include "UI/UIManager.hpp"
#include "UI/YTD/YTDLoader.hpp"
namespace VX
{
	HeaderComponents g_headers;

	void HeaderComponents::Init()
    {
        switch (m_HeaderType)
		{
		case HeaderType::Static:
			DrawRect(g_Ui->m_PosX, g_Ui->m_DrawBaseY + (g_Ui->m_HeaderHeight / 2.f), g_Ui->m_Width, g_Ui->m_HeaderHeight, g_Ui->m_HeaderBackgroundColor);
			break;
		case HeaderType::Gradient:
			for (std::size_t i = 0; i < (g_Ui->m_HeaderGradientTransparent ? 1 : 20); ++i)
			{
				DrawSprite("aircraft_dials", "aircraft_dials_g0", g_Ui->m_PosX - (g_Ui->m_HeaderGradientStretch / 2.f), g_Ui->m_DrawBaseY + (g_Ui->m_HeaderHeight / 2.f), g_Ui->m_Width + g_Ui->m_HeaderGradientStretch + g_Ui->m_HeaderGradientFiller, g_Ui->m_HeaderHeight, g_Ui->m_HeaderGradientColorRight, g_Ui->m_HeaderGradientFlip ? 0.f : 180.f);
				DrawSprite("aircraft_dials", "aircraft_dials_g0",g_Ui->m_PosX + (g_Ui->m_HeaderGradientStretch / 2.f),g_Ui->m_DrawBaseY + (g_Ui->m_HeaderHeight / 2.f),g_Ui->m_Width + g_Ui->m_HeaderGradientStretch + g_Ui->m_HeaderGradientFiller,g_Ui->m_HeaderHeight,g_Ui->m_HeaderGradientColorLeft,g_Ui->m_HeaderGradientFlip ? 180.f : 0.f);
			}
			break;
		case HeaderType::YTD:
			GetYTDLoader()->FullYTD(GetYTDLoader()->FullHeaderName + ".ytd");
			DrawSprite("VX", "Header", g_Ui->m_PosX, g_Ui->m_DrawBaseY + (g_Ui->m_HeaderHeight / 2.f), g_Ui->m_Width, g_Ui->m_HeaderHeight, g_Ui->m_HeaderBackgroundColor, 0);

			break;
		}

		if (g_Ui->m_HeaderText)
		{
			DrawCenteredText(VX_NAME,g_Ui->m_PosX,g_Ui->m_DrawBaseY + (g_Ui->m_HeaderHeight / 2.f) - (GetTextHeight(1, g_Ui->m_HeaderTextSize) / 2.f),g_Ui->m_HeaderTextSize,1,g_Ui->m_HeaderTextColor,false, true);
		}

		g_Ui->m_DrawBaseY += g_Ui->m_HeaderHeight;
    }

	HeaderComponents* GetHeader() { return &g_headers; }
}