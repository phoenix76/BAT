#define _CRT_SECURE_NO_WARNINGS
#include "bat_log_mgr.h"
#include <bat_config_mgr.h>
#include <bat_singleton.h>

#include <stdarg.h>

namespace BAT
{
	CLogManager::CLogManager()
	{
		m_FilePath = ISingleton<CConfigManager>::Instance().GetConfigParameter(CONFIG_PARAM_LOG_DIR);
		m_LogChannelsList.push_back(SLogChannel("base_system_log.txt", "system", m_FilePath));
	}
	void CLogManager::AddLogChannel(const std::string& channelName, const std::string& logFilename)
	{
		for(auto it = m_LogChannelsList.begin(); it != m_LogChannelsList.end(); it++)
		{
			if(it->_channelName == channelName || it->_fileName == logFilename)
				return;
		}
		m_LogChannelsList.push_back(SLogChannel(logFilename, channelName, m_FilePath));
	} 
	void CLogManager::LogToChannel(const std::string& channelName, const std::string& i)
	{
		for(auto it = m_LogChannelsList.begin(); it != m_LogChannelsList.end(); it++)
		{
			if(it->_channelName == channelName)
			{
				it->PrintTimeStamp();
				it->Write(i);
				it->Write("\n");
			}
		}
	}
	void CLogManager::DebugLogToChannel(const std::string& channelName, const std::string& i)
	{
#ifdef _DEBUG
		for(auto it = m_LogChannelsList.begin(); it != m_LogChannelsList.end(); it++)
		{
			if(it->_channelName == channelName)
			{
				it->PrintTimeStamp();
				it->Write(i);
				it->Write("\n");
			}
		}
#endif
	}
	void CLogManager::LogToChannel(const std::string& channelName, const char* msg, ...)
	{
		for(auto it = m_LogChannelsList.begin(); it != m_LogChannelsList.end(); it++)
		{	
			if(it->_channelName == channelName)
			{
				it->PrintTimeStamp();
				va_list args;
				va_start(args, msg);
				int len = _vscprintf(msg, args) + 1;
				char *buffer = static_cast<char*>(malloc(len*sizeof(char)));
				vsprintf_s(buffer, len, msg, args);
				it->Write(buffer);
				va_end(args);
				free(buffer);
				it->Write("\n");
			}
		}	
	}
	void CLogManager::DebugLogToChannel(const std::string& channelName, const char* msg, ...)
	{
#ifdef _DEBUG
		for(auto it = m_LogChannelsList.begin(); it != m_LogChannelsList.end(); it++)
		{
			if(it->_channelName == channelName)
			{
				it->PrintTimeStamp();
				va_list args;
				va_start(args, msg);
				int len = _vscprintf(msg, args) + 1;
				char *buffer = static_cast<char*>(malloc(len*sizeof(char)));
				vsprintf_s(buffer, len, msg, args);
				it->Write(buffer);
				va_end(args);
				free(buffer);
				it->Write("\n");
			}
		}
#endif
	}
	CLogManager::~CLogManager()
	{
		for(auto it = m_LogChannelsList.begin(); it != m_LogChannelsList.end(); it++)
			it->Destroy();
	}
}