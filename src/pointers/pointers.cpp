#include "../Common.hpp"
#include "log/log.hpp"
#include "pointers/pointers.hpp"
#include "memory/fwddec.hpp"
#include "memory/module.hpp"

namespace VX
{
    pointers::pointers()
    {
        memory::pattern_batch main_batch;

        main_batch.add("GS", "83 3D ? ? ? ? ? 75 17 8B 43 20 25", [this](memory::handle ptr)
                       { m_game_state = ptr.add(2).rip().as<std::uint32_t *>(); });

        main_batch.add("FC", "8B 15 ? ? ? ? 41 FF CF", [this](memory::handle ptr)
                       { m_FrameCount = ptr.add(2).rip().as<std::uint32_t *>(); });

        main_batch.add("GB", "48 85 FF 48 89 1D", [this](memory::handle ptr)
                       { m_GlobalBase = ptr.sub(12).rip().as<std::uint64_t **>(); });

        main_batch.add("NR", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A", [this](memory::handle ptr)
                       { m_native_registration_table = ptr.add(3).rip().as<rage::scrNativeRegistrationTable *>(); });

        main_batch.add("NH", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A", [this](memory::handle ptr)
                       { m_GetNativeHandler = ptr.add(12).rip().as<GetNativeHandler *>(); });

        main_batch.add("SPT", "48 8B 1D ? ? ? ? 41 83 F8 FF", [this](memory::handle ptr)
                       { m_ScriptProgramTable = ptr.add(3).rip().as<rage::scrProgramTable*>(); });

        main_batch.add("ISS", "40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE", [this](memory::handle ptr)
                       { m_is_session_started = ptr.add(3).rip().as<bool *>(); });

        main_batch.add("SG", "48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", [this](memory::handle ptr)
                       { m_script_globals = ptr.add(3).rip().as<std::int64_t **>(); });
        main_batch.add("SC", "48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8", [this](memory::handle ptr)
                       { m_swapchain = ptr.add(3).rip().as<IDXGISwapChain **>(); });

        main_batch.add("Model Spawn Bypass", "48 8B C8 FF 52 30 84 C0 74 05 48", [this](memory::handle ptr)
                       { m_model_spawn_bypass = ptr.add(8).as<PVOID>(); });
        main_batch.add("FXV", "83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA", [this](memory::handle ptr)
                       { m_FixVectors = ptr.add(8).as<decltype(m_FixVectors)>(); });

        main_batch.run(memory::module(nullptr));

        m_hwnd = FindWindowW(L"grcWindow", nullptr);
        if (!m_hwnd)
            throw std::runtime_error("Failed to find the game's window.");

        g_pointers = this;
    }

    pointers::~pointers()
    {
        g_pointers = nullptr;
    }
}
