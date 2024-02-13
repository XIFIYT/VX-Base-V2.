#pragma once
#include "../Common.hpp"
#include "memory/handle.hpp"
#include "memory/fwddec.hpp"
#include "memory/pattern.hpp"
#include "memory/range.hpp"
#include "memory/pattern_batch.hpp"
#include <script/scrProgramTable.hpp>
#include <script/scrNativeHandler.hpp>
#include <script/scrNativeRegistration.hpp>
#include <script/scrNativeRegistrationTable.hpp>

namespace VX
{
    class pointers
    {
    public:
        explicit pointers();
        ~pointers();

    public:
        HWND m_hwnd{};

        std::uint32_t *m_game_state{};
        std::uint32_t *m_FrameCount;
        std::uint64_t **m_GlobalBase;
        bool *m_is_session_started{};

        using FixVectors = void(rage::scrNativeCallContext *);
        FixVectors *m_FixVectors;

        using GetNativeHandler = rage::scrNativeHandler(rage::scrNativeRegistrationTable *, std::uint64_t);
        GetNativeHandler *m_GetNativeHandler;

        rage::scrProgramTable *m_ScriptProgramTable;

        rage::scrNativeRegistrationTable *m_native_registration_table{};

        std::int64_t **m_script_globals{};

        IDXGISwapChain **m_swapchain{};

        PVOID m_model_spawn_bypass;
    };

    inline pointers *g_pointers{};
}
