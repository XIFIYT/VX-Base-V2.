#pragma once

namespace VX
{
	class YTDLoader
	{
	private:
		
	public:
        void YTD(std::string name);
        void FullYTD(std::string name);
        bool FileExists(const std::string& fileName);
        std::string m_YTDName{ "VX" };
	    std::string FullHeaderName{ "VX" };
	};

	 YTDLoader* GetYTDLoader();
}