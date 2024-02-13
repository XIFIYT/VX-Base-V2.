#include "UI/components/header.hpp"
#include "GTA/Natives.hpp"
#include "UI/drawers/DrawersHelper.hpp"
#include "UI/UIManager.hpp"
#include "UI/components/Footer.hpp"
#include "UI/UIManager.hpp"
#include "UI/components/Desc.hpp"
#include "UI/YTD/YTDLoader.hpp"
#include "GTA/memory/memoryEdit.hpp"
#include "utility/Util.hpp"
namespace VX
{
    YTDLoader g_YTDLoader;
    using namespace UserInterface;
    bool YTDLoader::FileExists(const std::string &fileName)
    {
        struct stat buffer;
        return (stat(fileName.c_str(), &buffer) == 0);
    }
    void YTDLoader::YTD(std::string name)
    {
        static uint32_t *(*pRegisterFile)(int *, const char *, bool, const char *, bool) = reinterpret_cast<decltype(pRegisterFile)>(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").count(1).get(0).get<void>(0));
        std::string path = GetMenuPath() + "\\Textures\\" + m_YTDName + ".ytd";

        int textureID;
        if (FileExists(path))
        {
            pRegisterFile(&textureID, path.c_str(), true, name.c_str(), false);
        }
    }
    void YTDLoader::FullYTD(std::string name)
    {
        static uint32_t *(*pRegisterFile)(int *, const char *, bool, const char *, bool) = reinterpret_cast<decltype(pRegisterFile)>(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").count(1).get(0).get<void>(0));
        std::string path = GetMenuPath() + "\\Textures\\" + FullHeaderName + ".ytd";

        int textureID;
        if (FileExists(path))
        {
            pRegisterFile(&textureID, path.c_str(), true, name.c_str(), false);
        }
    }

    YTDLoader *GetYTDLoader() { return &g_YTDLoader; }
}