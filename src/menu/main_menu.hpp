#pragma once
#include "Script/Script.hpp"

namespace VX
{
	
	class MainMenu : public Script
	{
	public:
		explicit MainMenu() = default;
		~MainMenu() noexcept = default;

		bool IsInitialized() override;
		ScriptType GetType() override;
		void Initialize() override;
		void Destroy() override;
		void Tick() override;
	private:
		bool m_Initialized{};
	};

	inline std::shared_ptr<MainMenu> g_MainMenu;
}
