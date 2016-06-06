#ifndef BAT_INI_READER_H
#define BAT_INI_READER_H

#include <string>
#include <fstream>
#include <vector>

#include <bat_sys_macroses.h>

namespace RISEN
{
	enum EINIReadFileResult
	{
		INI_READ_FILE_SUCCEEDED,
		INI_READ_FILE_NOT_EXISTS,
		INI_READ_FILE_IS_INCORRECT
	};

	struct SINIAttribute
	{
		std::string attribute;
		std::string value;
	};

	class CINIFile
	{
	public:
		CINIFile() {}
		//Format "patch\\filename.ini"
		bool Read(const std::string& filename);
		bool VerifyAttribute(const std::string& attrName) const;
		std::string GetAttribute(const std::string& attrName) const;
		std::string GetFileName() const;
		void ChangeAttribute(const std::string& attrName, const std::string& value);
		void AddAttribute(const std::string& attrName, const std::string& value);
		void RewriteFile();
		~CINIFile() {}

	private:
		void CreateAttributeFromString(SINIAttribute& rstruct, const std::string& data);
		std::string m_Filename;
		std::vector<SINIAttribute> m_AttrList;
	};

	class DLLEXP CIniFileReader
	{
	public:
		CIniFileReader() {}

		static CIniFileReader* Instance()
		{
			static CIniFileReader _instance;
			return &_instance;
		}

		//Format "filename"
		EINIReadFileResult ReadINIFile(const std::string& filename);

		bool ChangeINIAttribute(const std::string& filename, const std::string& attrName, const std::string& newValue);

		bool VerifyExistsINIAttribute(const std::string& filename, const std::string& attrName) const;

		std::string GetINIAttribute(const std::string& filename, const std::string& attrName) const;

		void AddINIAttribute(const std::string& filename, const std::string& attrName, const std::string& value);

		void ShutdownSystem();

		~CIniFileReader() {}

	private:
		void RewriteAllINIFiles();

		std::vector<CINIFile*> m_INIFiles;
	};
}

#define IINIReader RISEN::CIniFileReader::Instance()

#endif