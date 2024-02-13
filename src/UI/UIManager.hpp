#pragma once
#include "../Common.hpp"
#include "utility/Types.hpp"
#include "TextBox.hpp"
#include "AbstractSubmenu.hpp"

namespace VX::UserInterface
{
	enum class Font : std::int32_t
	{
		ChaletLondon = 0,
		HouseScript = 1,
		Monospace = 2,
		Wingdings = 3,
		ChaletComprimeCologne = 4,
		Pricedown = 7
	};

	struct Rectangle
	{
		Vector2 m_Center;
		Vector2 m_Size;

		bool IsInBounds(Vector2 point)
		{
			auto left = m_Center.x - (m_Size.x / 2.f);
			auto right = m_Center.x + (m_Size.x / 2.f);
			auto top = m_Center.y + (m_Size.y / 2.f);
			auto bottom = m_Center.y - (m_Size.y / 2.f);

			if (point.x > right || point.x < left)
				return false;
			if (point.y > top || point.y < bottom)
				return false;

			return true;
		}
	};

	class UIManager
	{
	public:
		explicit UIManager() = default;
		~UIManager() noexcept = default;
		UIManager(UIManager const&) = delete;
		UIManager(UIManager&&) = delete;
		UIManager& operator=(UIManager const&) = delete;
		UIManager& operator=(UIManager&&) = delete;

		template <typename SubmenuType, typename ...TArgs>
		void AddSubmenu(TArgs&&... args)
		{
			auto sub = std::make_unique<SubmenuType>(std::forward<TArgs>(args)...);
			if (m_SubmenuStack.empty())
			{
				m_SubmenuStack.push(sub.get());
			}

			m_AllSubmenus.push_back(std::move(sub));
		}

		void SwitchToSubmenu(std::uint32_t id)
		{
			for (auto&& sub : m_AllSubmenus)
			{
				if (sub->GetId() == id)
				{
					m_SubmenuStack.push(sub.get());
					return;
				}
			}
		}

		void OnTick();
	public:
		std::mutex m_Mutex;
		std::string FullHeaderName;
		bool m_Smoothscroll = false;
		bool g_FullThemeLoading{ false };
		bool m_Opened = false;
		bool m_MouseLocked = false;
		float m_PosX = 0.8f;
		float m_PosY = 0.1f;
		float m_Width = 0.22f;
		std::size_t m_OptionsPerPage = 11;
		bool m_Sounds = true;
		bool m_hotkey_pressed = false;
		bool m_select_pressed = false;
		bool m_up_pressed = false;
		bool m_down_pressed = false;
		bool m_left_pressed = false;
		bool m_right_pressed = false;
		float m_last_option_base = { 0.f };
		int m_current_option;

		// Input
		std::int32_t m_OpenDelay = 200;
		std::int32_t m_BackDelay = 300;
		std::int32_t m_EnterDelay = 300;
		std::int32_t m_VerticalDelay = 120;
		std::int32_t m_HorizontalDelay = 120;

		// Header
		float m_HeaderHeight = 0.1f;
		bool m_HeaderText = true;
		float m_HeaderTextSize = 1.f;
		Font m_HeaderFont = Font::HouseScript;
		Color m_HeaderBackgroundColor{ 2, 130, 53, 255 };
		Color m_HeaderTextColor{ 255, 255, 255, 255 };

		bool m_HeaderGradientTransparent = false;
		bool m_HeaderGradientFlip = false;
		float m_HeaderGradientStretch = 0.f;
		float m_HeaderGradientFiller = 0.f;
		Color m_HeaderGradientColorLeft{ 0, 255, 255, 255 };
		Color m_HeaderGradientColorRight{ 0, 255, 0, 255 };

		// Submenu bar
		float m_SubmenuBarHeight = 0.035f;
		float m_SubmenuBarTextSize = 0.30f;
		Font m_SubmenuBarFont = Font::ChaletLondon;
		float m_SubmenuBarPadding = 2.1f;
		Color m_SubmenuBarBackgroundColor{ 0, 0, 0, 255 };
		Color m_SubmenuBarTextColor{ 255, 255, 255, 255 };

		int m_break_font = 1;
		float m_break_font_size = { 0.4f };

		Color m_break_text = { 255, 255, 255, 255 };

		// Options
		float m_OptionHeight = 0.035f;
		float m_OptionTextSize = 0.30f;
		Font m_OptionFont = Font::ChaletLondon;
		float m_OptionPadding = 2.1f;
		Color m_OptionSelectedTextColor{ 10, 10, 10, 255 };
		Color m_OptionUnselectedTextColor{ 255, 255, 255, 255 };
		Color m_OptionSelectedBackgroundColor{ 255, 255, 255, 255 };
		Color m_OptionUnselectedBackgroundColor{ 0, 0, 0, 255 };
		int m_option_count;
		//Toggle
		Color m_Toggle_On{ 0, 255, 255, 255 };
		Color m_Toggle_Off{ 255, 255, 255, 255 };

		// Footer
		float m_FooterHeight = 0.035f;
		float m_FooterSpriteSize = 0.040f;
		Color m_FooterBackgroundColor{ 0, 0, 0, 255 };
		Color m_FooterSpriteColor{ 255, 255, 255, 255 };

		// Description
		float m_DescriptionHeightPadding = 0.01f;
		float m_DescriptionHeight = 0.033f;
		float m_DescriptionTextSize = 0.28f;
		Font m_DescriptionFont = Font::ChaletLondon;
		Color m_DescriptionBackgroundColor{ 0, 0, 0, 120 };
		Color m_DescriptionTextColor{ 255, 255, 255, 255 };
		float m_DescriptionSpriteSize = 0.025f;
		float m_DescriptionPadding = 2.1f;
		Color m_DescriptionSpriteColor{ 255, 255, 255, 255 };
		float m_DrawBaseY{};

		std::stack<AbstractSubmenu*, std::vector<AbstractSubmenu*>> m_SubmenuStack;
	private:
		void CheckForInput();
		void HandleInput();
		void ResetInput();

		
		void draw_break(const char* option);
		void DrawRect(float x, float y, float width, float height, Color color);

		bool IsMouseLocked();
		Rectangle GetMenuRect();
		Vector2 GetMousePos();

		std::vector<std::unique_ptr<AbstractSubmenu>> m_AllSubmenus;
	
	};
}

namespace VX
{
	inline std::unique_ptr<UserInterface::UIManager> g_Ui;
}