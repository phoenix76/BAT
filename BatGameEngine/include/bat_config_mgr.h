#ifndef _BAT_CONFIG_MGR_H_
#define _BAT_CONFIG_MGR_H_

#include <bat_platform.h>
#include <bat_types.h>

#include <string>
#include <fstream>

namespace BAT
{
	enum EConfigParameters
	{
		CP_WINDOW_WIDTH			= 0,
		CP_WINDOW_HEIGHT		= 1,
		CP_FULLSCREEN			= 2,
	};
	class CConfig
	{
	public:
		CConfig();

		bool Initialize();

		bool GetValue(EConfigParameters param, std::string& target);

		void RewriteConfigFile();

		~CConfig();

	private:
		std::ifstream m_InFile;
		std::ofstream m_OutFile;

		std::string m_FrameworkWidth = "";
		std::string m_FrameworkHeight = "";
		std::string m_FrameworkFullscreen = "";

	};
}

#endif