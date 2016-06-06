#include "ris_ini_reader.h"
#include "bat_win_utils.h"
#include "bat_string_utils.h"

namespace RISEN
{
	bool CINIFile::Read(const std::string& filename)
	{
		m_Filename = filename;
		SINIAttribute tempAttr;
		std::ifstream file(m_Filename);
		std::string temp = "";
		std::getline(file, temp);
		if(file.eof() || temp == "")
			return false;
		do
		{
			CreateAttributeFromString(tempAttr, temp);
			m_AttrList.push_back(tempAttr);
			if(file.eof()) break;
			std::getline(file, temp);
		} while(true);
		file.close();
		return true;
	}
	bool CINIFile::VerifyAttribute(const std::string& attrName) const
	{
		for(auto it = m_AttrList.begin(); it != m_AttrList.end(); it++)
		if(it->attribute == attrName)
			return true;
		return false;

	}
	std::string CINIFile::GetAttribute(const std::string& attrName) const
	{
		for(auto it = m_AttrList.begin(); it != m_AttrList.end(); it++)
		{
			if(it->attribute == attrName)
				return it->value;
		}
		return std::string("NULL");
	}
	std::string CINIFile::GetFileName() const
	{
		return m_Filename;
	}
	void CINIFile::ChangeAttribute(const std::string& attrName, const std::string& newValue)
	{
		for(auto it = m_AttrList.begin(); it != m_AttrList.end(); it++)
		{
			if(it->attribute == attrName)
			{
				it->value = newValue;
				break;
			}
		}
	}
	void CINIFile::AddAttribute(const std::string& attrName, const std::string& value)
	{
		SINIAttribute temp = { attrName, value };
		m_AttrList.push_back(temp);
	}
	void CINIFile::RewriteFile()
	{
		BAT_UTILS::DeleteSomeFile(BAT_UTILS::STDStrToWCHAR(m_Filename).c_str());
		std::ofstream file(m_Filename);
		file << m_AttrList[0].attribute << '=' << m_AttrList[0].value;
		for(auto it = m_AttrList.begin() + 1; it != m_AttrList.end(); it++)
			file << '\n' << it->attribute << '=' << it->value;
		file.close();
	}
	void CINIFile::CreateAttributeFromString(SINIAttribute& rstruct, const std::string& data)
	{
		rstruct.attribute = data.substr(0, data.find('='));
		rstruct.value = data.substr(data.find('=') + 1, data.length());
	}

	EINIReadFileResult CIniFileReader::ReadINIFile(const std::string& filename)
	{
		std::string fdir = "configs\\" + filename + ".ini";
		if(!(BAT_UTILS::VerifyFileExists(BAT_UTILS::STDStrToWCHAR(fdir).c_str())))
			return INI_READ_FILE_NOT_EXISTS;
		m_INIFiles.push_back(new CINIFile());
		if(!(m_INIFiles.back()->Read(fdir)))
		{
			delete m_INIFiles.back();
			m_INIFiles.pop_back();
			return INI_READ_FILE_IS_INCORRECT;
		}
		return INI_READ_FILE_SUCCEEDED;
	}
	bool CIniFileReader::ChangeINIAttribute(const std::string& filename, const std::string& attrName, const std::string& newVal)
	{
		for(auto it = m_INIFiles.begin(); it != m_INIFiles.end(); it++)
		{
			if((*it)->GetFileName() == "configs\\" + filename + ".ini")
			{
				(*it)->ChangeAttribute(attrName, newVal);
				return true;
			}
		}
		return false;
	}
	bool CIniFileReader::VerifyExistsINIAttribute(const std::string& filename, const std::string& attrName) const
	{
		for(auto it = m_INIFiles.begin(); it != m_INIFiles.end(); it++)
		{
			if((*it)->GetFileName() == "configs\\" + filename + ".ini")
				return (*it)->VerifyAttribute(attrName);
		}
		return false;
	}
	std::string CIniFileReader::GetINIAttribute(const std::string& filename, const std::string& attrName) const
	{
		for(auto it = m_INIFiles.begin(); it != m_INIFiles.end(); it++)
		{
			if((*it)->GetFileName() == "configs\\" + filename + ".ini")
				return (*it)->GetAttribute(attrName);
		}
		return "Not found";
	}
	void CIniFileReader::AddINIAttribute(const std::string& filename, const std::string& attrName, const std::string& value)
	{
		for(auto it = m_INIFiles.begin(); it != m_INIFiles.end(); it++)
		{
			if((*it)->GetFileName() == "configs\\" + filename + ".ini")
			{
				(*it)->AddAttribute(attrName, value);
				break;
			}
		}
	}
	void CIniFileReader::ShutdownSystem()
	{
		RewriteAllINIFiles();
		for(auto it = m_INIFiles.begin(); it != m_INIFiles.end(); it++)
			delete *it;
	}
	void CIniFileReader::RewriteAllINIFiles()
	{
		for(auto it = m_INIFiles.begin(); it != m_INIFiles.end(); it++)
			(*it)->RewriteFile();
	}
}