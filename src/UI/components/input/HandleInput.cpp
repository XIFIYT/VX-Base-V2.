#include "UI/components/header.hpp"
#include "GTA/Natives.hpp"
#include "UI/drawers/DrawersHelper.hpp"
#include "UI/UIManager.hpp"
#include "UI/components/Footer.hpp"
#include "UI/UIManager.hpp"
#include "UI/components/Desc.hpp"
#include "UI/components/input/HandleInput.hpp"
namespace VX
{
    HandleInput g_HandleInput;
    using namespace UserInterface;
    void HandleInput::Init()
    {
        static auto openTicker = GetTickCount();
        if (m_OpenKeyPressed && GetTickCount() - openTicker >= static_cast<std::uint32_t>(g_Ui->m_OpenDelay))
        {
            openTicker = GetTickCount();
            g_Ui->m_Opened ^= true;

            if (g_Ui->m_Sounds)
                AUDIO::PLAY_SOUND_FRONTEND(-1, g_Ui->m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
        }

        static Timer backTimer(0ms);
        backTimer.SetDelay(std::chrono::milliseconds(g_Ui->m_BackDelay));
        if (g_Ui->m_Opened && m_BackKeyPressed && backTimer.Update())
        {
            if (g_Ui->m_Sounds)
                AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

            if (g_Ui->m_SubmenuStack.size() <= 1)
            {
                g_Ui->m_Opened = false;
            }
            else
            {
                g_Ui->m_SubmenuStack.pop();
            }
        }

        if (g_Ui->m_Opened && !g_Ui->m_SubmenuStack.empty())
        {
            auto sub = g_Ui->m_SubmenuStack.top();

            static Timer enterTimer(0ms);
            enterTimer.SetDelay(std::chrono::milliseconds(g_Ui->m_EnterDelay));
            if (m_EnterKeyPressed && sub->GetNumOptions() != 0 && enterTimer.Update())
            {
                if (g_Ui->m_Sounds)
                    AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

                if (auto opt = sub->GetOption(sub->GetSelectedOption()))
                {
                    opt->HandleAction(OptionAction::EnterPress);
                }
            }

            static Timer upTimer(0ms);
            upTimer.SetDelay(std::chrono::milliseconds(g_Ui->m_VerticalDelay));
            if (m_UpKeyPressed && sub->GetNumOptions() != 0 && upTimer.Update())
            {
                if (g_Ui->m_Sounds)
                    AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

                sub->ScrollBackward();
            }

            static Timer downTimer(0ms);
            downTimer.SetDelay(std::chrono::milliseconds(g_Ui->m_VerticalDelay));
            if (m_DownKeyPressed && sub->GetNumOptions() != 0 && downTimer.Update())
            {
                if (g_Ui->m_Sounds)
                    AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

                sub->ScrollForward();
            }

            static Timer leftTimer(0ms);
            leftTimer.SetDelay(std::chrono::milliseconds(g_Ui->m_HorizontalDelay));
            if (m_LeftKeyPressed && sub->GetNumOptions() != 0 && leftTimer.Update())
            {
                if (g_Ui->m_Sounds)
                    AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

                if (auto opt = sub->GetOption(sub->GetSelectedOption()))
                {
                    opt->HandleAction(OptionAction::LeftPress);
                }
            }

            static Timer rightTimer(0ms);
            rightTimer.SetDelay(std::chrono::milliseconds(g_Ui->m_HorizontalDelay));
            if (m_RightKeyPressed && sub->GetNumOptions() != 0 && rightTimer.Update())
            {
                if (g_Ui->m_Sounds)
                    AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

                if (auto opt = sub->GetOption(sub->GetSelectedOption()))
                {
                    opt->HandleAction(OptionAction::RightPress);
                }
            }
        }
    }

    HandleInput *GetHandle() { return &g_HandleInput; }
}