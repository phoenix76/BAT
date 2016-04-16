#ifndef _BAT_LOG_MGR_H_
#define _BAT_LOG_MGR_H_

#include "bat_platform.h"
#include "bat_memory.h"
#include "bat_other_utils.h"

#include <string>
#include <fstream>
#include <vector>
#include <ctime>

namespace BAT
{
	struct SLogChannel
	{
		SLogChannel(const std::string& fileName, const std::string& channelName, const std::string& filePath)
		{
			_fileName = fileName;
			_channelName = channelName;
			_filePath = filePath;
			file = new std::ofstream;
			file->open(_filePath + _fileName, std::ios_base::app);
			*file << "START SESSION AT " << GetTimeStamp().c_str() << "\n\n\n";
		}
		template<typename T>
		void Write(const T& msg)
		{
			*file << msg;
		}
		template<> void Write<>(const std::string& msg)
		{
			*file << msg.c_str();
		}
		void Destroy()
		{
			if(file)
			{
				*file << "\n\nEND SESSION AT " << GetTimeStamp().c_str() << '\n'
					<< "--------------------------------------------------------------------\n\n";
				file->close();
				_DELETE(file);
			}
		}
		std::string GetTimeStamp()
		{
			time_t rawtime;
			tm * timeinfo;
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			std::string info = "";
			if(timeinfo->tm_mday < 10)
			info += '0' +std::to_string(timeinfo->tm_mday) + '.';
			else
				info += std::to_string(timeinfo->tm_mday) + '.';
			if(timeinfo->tm_mon < 10)
				info += '0' + std::to_string(timeinfo->tm_mon) + '.';
			else
				info += std::to_string(timeinfo->tm_mon) + '.';
			info += std::to_string(timeinfo->tm_year + 1900) + " | ";
			if(timeinfo->tm_hour < 10)
				info += '0' + std::to_string(timeinfo->tm_hour) + ':';
			else
				info += std::to_string(timeinfo->tm_hour) + ':';
			if(timeinfo->tm_min < 10)
				info += '0' + std::to_string(timeinfo->tm_min) + ':';
			else
				info += std::to_string(timeinfo->tm_min) + ':';
			if(timeinfo->tm_sec < 10)
				info += '0' + std::to_string(timeinfo->tm_sec);
			else
				info += std::to_string(timeinfo->tm_sec);
			return info;
		}

		void PrintTimeStamp()
		{
			*file << GetTimeStamp() << "-> ";
		}

		std::ofstream* file = nullptr;
		std::string _fileName;
		std::string _channelName;
		std::string _filePath;
	};

	class CLogManager
	{
	public:
		//Создает лог по умолчанию "system_log.txt"
		CLogManager();

		//Добавляет и открывает файл для логирования
		void AddLogChannel(const std::string& channelName, const std::string& logFilename);

		void LogToChannel(const std::string& channelName, const std::string& i);

		void DebugLogToChannel(const std::string& channelName, const std::string& i);

		void LogToChannel(const std::string& channelName, const char* i, ...);

		void DebugLogToChannel(const std::string& channelName, const char* i, ...);

		~CLogManager();

	private:
		std::string m_FilePath;
		std::vector<SLogChannel> m_LogChannelsList;

	};
}

#endif