#pragma once
#include "Script/Script.hpp"

namespace VX
{
	class ScriptManager
	{
	public:
		explicit ScriptManager();
		~ScriptManager() noexcept;
		ScriptManager(ScriptManager const&) = delete;
		ScriptManager(ScriptManager&&) = delete;
		ScriptManager& operator=(ScriptManager const&) = delete;
		ScriptManager& operator=(ScriptManager&&) = delete;

		/**
		 * \brief Registers a script
		 * \param script The script to be registered
		 */
		void AddScript(std::shared_ptr<Script> script);

		/**
		 * \brief Checks if the script is initialized
		 * \param script The script to be unregistered
		 */
		void RemoveScript(Script* script);

		/**
		 * \brief Runs a tick on the script thread
		 */
		void OnGameTick();

		/**
		 * \brief Runs a tick on the D3D thread
		 */
		void OnD3DTick();
	private:
		std::mutex m_Mutex;
		std::vector<std::shared_ptr<Script>> m_Scripts;
	};

	inline std::unique_ptr<ScriptManager> g_ScriptManager;
}
