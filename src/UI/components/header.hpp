#pragma once

namespace VX
{
	class HeaderComponents
	{
	private:
		
	public:
        void Init();
	};
    enum class HeaderType : std::int32_t
	{
		Static = 0,
		Gradient = 1,
		YTD = 2
	};
    inline const char* HeaderTypesFrontend[]
	{
		"Static",
		"Gradient",
		"YTD"
	};

	inline HeaderType HeaderTypesBackend[]
	{
		HeaderType::Static,
		HeaderType::Gradient,
		HeaderType::YTD
	};

	inline std::size_t HeaderTypesPosition = 1;
    inline HeaderType m_HeaderType = HeaderType::YTD;

	HeaderComponents* GetHeader();
}