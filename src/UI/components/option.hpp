#pragma once
#include "UI/AbstractSubmenu.hpp"
#include "UI/AbstractOption.hpp"
using namespace UserInterface;
namespace VX
{
	class OptionComponents
	{
        
	private:
		
	public:
        void Init(AbstractOption* opt, bool selected);
	};

	OptionComponents* GetOption();
}