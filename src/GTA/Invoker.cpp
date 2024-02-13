#include "GTA/Invoker.hpp"
#include "pointers/gtapointers.hpp"
#include "log/log.hpp"
#include "pointers/pointers.hpp"
namespace VX
{
    Invoker::NativeCallContext::NativeCallContext()
    {
        m_return_value = &m_ReturnStack[0];
        m_args = &m_ArgStack[0];
    }

    void Invoker::CacheHandlersImpl()
    {
        for (const auto [firstHash, currHash] : g_CrossMap)
        {
            auto handler = g_gtaPointers->m_GetNativeHandler(g_gtaPointers->m_NativeRegistrations, currHash);

            m_HandlerCache.emplace(firstHash, handler);
        }

        m_HandlersCached = true;
    }

    void Invoker::BeginCallImpl()
    {
        m_CallContext.reset();
    }

    void Invoker::EndCallImpl(rage::scrNativeHash hash)
    {
        if (const auto& it = m_HandlerCache.find(hash); it != m_HandlerCache.end())
        {
            const auto& handler = it->second;

            handler(&m_CallContext);
            return g_gtaPointers->m_FixVectors(&m_CallContext);
        }

        LOG(FATAL) << "Failed to find '0x%p' native's handler." << hash;
    }
}