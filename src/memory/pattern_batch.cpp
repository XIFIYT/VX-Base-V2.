#include "pattern_batch.hpp"

#include "common.hpp"
#include "log/log.hpp"
#include "range.hpp"
#define HEX_TO_UPPER(value) "0x" << std::hex << std::uppercase << (DWORD64)value << std::dec << std::nouppercase
namespace memory
{
	void pattern_batch::add(std::string name, pattern pattern, std::function<void(handle)> callback)
	{
		m_entries.emplace_back(std::move(name), std::move(pattern), std::move(callback));
	}

	void pattern_batch::run(range region)
	{
		bool all_found = true;
		for (auto& entry : m_entries)
		{
			if (auto result = region.scan(entry.m_pattern))
			{
				if (entry.m_callback)
				{
					std::invoke(std::move(entry.m_callback), result);
					using namespace std;
					ostringstream msg; msg << "Found '" << entry.m_name << "' GTA5.exe+" << HEX_TO_UPPER(result.as<DWORD64>() - region.begin().as<DWORD64>());
					LOG(INFO) << msg.str().c_str();
				}
				else
				{
					all_found = false;
					using namespace std;
					ostringstream msg1; msg1 << "Failed to find '" << entry.m_name << "'.";
					LOG(FATAL) <<msg1.str().c_str();
				}
			}
			else
			{
				all_found = false;
				using namespace std;
					ostringstream msg2; msg2 << "Failed to find '" << entry.m_name << "'.";
				LOG(FATAL) << msg2.str().c_str();
			}
		}

		m_entries.clear();
		if (!all_found)
		{
			throw std::runtime_error("Failed to find some patterns.");
		}
	}
}