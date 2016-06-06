#ifndef BAT_CORE_INTERFACE_H
#define BAT_CORE_INTERFACE_H

#include <bat_sys_macroses.h>
#include <bat_audio_interface.h>
#include <bat_framework_interface.h>
#include <bat_graphics_interface.h>
#include <bat_engine_log.h>
#include <bat_cfg_reader.h>

namespace BAT_ENGINE
{
	class DLLEXP CEngineCore : CFrameworkCore, CAudioCore, CGraphicsCore
	{
	public:
		CEngineCore()
		{
			m_QueryInterface = new CQueryInterface;
			m_QueryInterface->SetPtrs((CFrameworkCore*)this, (CGraphicsCore*)this, (CAudioCore*)this);

			m_Config = new CConfigLoader;
			
			BGE_Log("START SESSION AT %s%s", BAT_UTILS::GetTimeStamp().c_str(),
				"\n---------------------------------------------------------------\n\n");
		}

		HRESULT Initialize();
		
		class DLLEXP CQueryInterface
		{	
		public:
			friend class CEngineCore;

			CAudioCore*	Audio()	
			{ 
				if(m_Audio->IsInitialized())
					return m_Audio;
				else
					return NULL;
			}
			CFrameworkCore*	Framework() 
			{ 
				if(m_Framework->IsInitialized())
					return m_Framework;
				else
					return NULL;
			}
			CGraphicsCore* Graphics() 
			{ 
				if(m_Graphics->IsInitialized())
					return m_Graphics;
				else
					return NULL;
			}

		private:
			void SetPtrs(CFrameworkCore* frm, CGraphicsCore* graph, CAudioCore* audio)
			{
				m_Framework = frm;
				m_Graphics = graph;
				m_Audio = audio;
			}

			CFrameworkCore* m_Framework;
			CAudioCore* m_Audio;
			CGraphicsCore* m_Graphics;
		};

		CQueryInterface* QueryInterface() { return m_QueryInterface; }

		~CEngineCore()
		{
			delete m_Config;
			delete m_QueryInterface;
			BGE_Log("\n\nEND SESSION AT %s%s", BAT_UTILS::GetTimeStamp().c_str(),
				"\n---------------------------------------------------------------\n\n\n");
		}

	private:
		CQueryInterface* m_QueryInterface;
		CConfigLoader* m_Config;

	};
}

#endif