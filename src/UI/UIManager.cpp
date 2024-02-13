#include "UIManager.hpp"
#include "utility/Timer.hpp"
#include "GTA/Natives.hpp"
#include "UI/drawers/DrawersHelper.hpp"
#include "UI/components/header.hpp"
#include "UI/components/subbar.hpp"
#include "UI/components/option.hpp"
#include "UI/components/Footer.hpp"
#include "UI/components/Desc.hpp"
#include "UI/components/input/HandleInput.hpp"
namespace VX::UserInterface
{
	void UIManager::OnTick()
	{
		std::lock_guard lock(m_Mutex);

		if (IsMouseLocked())
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			ShowCursor(true);
			SetCursor(LoadCursorA(NULL, IDC_ARROW));

			if (GetMenuRect().IsInBounds(GetMousePos()))
			{
				LOG(INFO) << "Kekkeke";
			}
		}

		if (g_Ui->m_Opened && g_Settings.m_LockMouse)
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}

		CheckForInput();
		GetHandle()->Init();

		if (m_Opened)
		{

			PAD::DISABLE_CONTROL_ACTION(0, 27, true); // Disable phone

			m_DrawBaseY = m_PosY;
			GetHeader()->Init();
			if (!m_SubmenuStack.empty())
			{
				auto sub = m_SubmenuStack.top();
				sub->Reset();
				sub->Execute();
				GetSubbar()->Init(sub);
				if (sub->GetNumOptions() != 0)
				{
					std::size_t startPoint = 0;
					std::size_t endPoint = sub->GetNumOptions() > m_OptionsPerPage ? m_OptionsPerPage : sub->GetNumOptions();
					if (sub->GetNumOptions() > m_OptionsPerPage && sub->GetSelectedOption() >= m_OptionsPerPage)
					{
						startPoint = sub->GetSelectedOption() - m_OptionsPerPage + 1;
						endPoint = sub->GetSelectedOption() + 1;
					}

					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j)
					{
						GetOption()->Init(sub->GetOption(i), i == sub->GetSelectedOption());
					}
				}
			}

			GetFooter()->Init();
			GetDesc()->Init();
		}
	}

	void UIManager::CheckForInput()
	{
		ResetInput();

		GetHandle()->m_OpenKeyPressed = IsKeyPressed(VK_F5);
		GetHandle()->m_BackKeyPressed = IsKeyPressed(VK_BACK);
		GetHandle()->m_EnterKeyPressed = IsKeyPressed(VK_RETURN);
		GetHandle()->m_UpKeyPressed = IsKeyPressed(VK_UP);
		GetHandle()->m_DownKeyPressed = IsKeyPressed(VK_DOWN);
		GetHandle()->m_LeftKeyPressed = IsKeyPressed(VK_LEFT);
		GetHandle()->m_RightKeyPressed = IsKeyPressed(VK_RIGHT);
	}

	void UIManager::HandleInput()
	{
	}

	void UIManager::ResetInput()
	{
		GetHandle()->m_OpenKeyPressed = false;
		GetHandle()->m_BackKeyPressed = false;
		GetHandle()->m_EnterKeyPressed = false;
		GetHandle()->m_UpKeyPressed = false;
		GetHandle()->m_DownKeyPressed = false;
		GetHandle()->m_LeftKeyPressed = false;
		GetHandle()->m_RightKeyPressed = false;
	}

	bool UIManager::IsMouseLocked()
	{
		return m_Opened && m_MouseLocked;
	}

	Rectangle UIManager::GetMenuRect()
	{
		float height = m_HeaderHeight;
		height += m_SubmenuBarHeight;

		if (!m_SubmenuStack.empty())
		{
			height += m_OptionHeight * std::min(m_SubmenuStack.top()->GetNumOptions(), m_OptionsPerPage);
		}

		height += m_FooterHeight;

		return {
			{m_PosX + (m_Width / 2.f), m_PosY + (height / 2.f)},
			{m_Width, height}};
	}

	Vector2 UIManager::GetMousePos()
	{
		POINT point;
		GetCursorPos(&point);

		return Vector2{static_cast<float>(point.x), static_cast<float>(point.y)};
	}
}