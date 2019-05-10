#include <QMessageBox>
#include "Observer/GPU/Nvidia/SRMNvidiaGPUInfo.h"

//************************************
// Method:    getInstance
// FullName:  SRMGPUInfo::getInstance
// Access:    public 
// Returns:   SRMGPUInfo*
// Qualifier:
// Note:      
//************************************
SRMNvidiaGPUInfo* SRMNvidiaGPUInfo::getInstance()
{
	static SRMNvidiaGPUInfo s_oSRMGPUInfo;
	return &s_oSRMGPUInfo;
}

//************************************
// Method:    SRMGPUInfo
// FullName:  SRMGPUInfo::SRMGPUInfo
// Access:    private 
// Returns:   
// Qualifier:
// Note:      
//************************************
SRMNvidiaGPUInfo::SRMNvidiaGPUInfo()
{
	Init();
}

//************************************
// Method:    ~SRMGPUInfo
// FullName:  SRMGPUInfo::~SRMGPUInfo
// Access:    private 
// Returns:   
// Qualifier:
// Note:      
//************************************
SRMNvidiaGPUInfo::~SRMNvidiaGPUInfo()
{
	Unit();
}

//************************************
// Method:    Init
// FullName:  SRMGPUInfo::Init
// Access:    private 
// Returns:   void
// Qualifier:
// Note:      
//************************************
void SRMNvidiaGPUInfo::Init()
{
	bool bResult = false;
	bool bRetCode = false;

	int nIndex = 0;
	int nResult = 0;

	m_hNvApiDll = LoadLibrary(L"nvapi64.dll");
	if (nullptr == m_hNvApiDll)
	{
		//QMessageBox::warning(nullptr, QStringLiteral("����"), QStringLiteral("�Ҳ���nvpai64.dll"));
		m_bIsValid = false;
		return;
	}

	m_bIsValid = true;
	m_pfnNvapi_QueryInterface = (Nvapi_QueryInterfaceType)GetProcAddress(m_hNvApiDll, "nvapi_QueryInterface");
	if (m_pfnNvapi_QueryInterface)
	{
		m_pfnNvAPI_Initialize = (NvAPI_InitializeType)m_pfnNvapi_QueryInterface(ID_NvAPI_Initialize);
		m_pfnNvAPI_GPU_GetThermalSettings = (NvAPI_GPU_GetThermalSettingsType)m_pfnNvapi_QueryInterface(ID_NvAPI_GPU_GetThermalSettings);
		m_pfnNvAPI_EnumNvidiaDisplayHandle = (NvAPI_EnumNvidiaDisplayHandleType)m_pfnNvapi_QueryInterface(ID_NvAPI_EnumNvidiaDisplayHandle);
		m_pfnNvAPI_GPU_GetUsages = (NvAPI_GPU_GetUsagesType)m_pfnNvapi_QueryInterface(ID_NvAPI_GPU_GetUsages);
		m_pfnNvAPI_GPU_GetMemoryInfo = (NvAPI_GPU_GetMemoryInfoType)m_pfnNvapi_QueryInterface(ID_NvAPI_GPU_GetMemoryInfo);
		m_pfnNvAPI_GetPhysicalGPUsFromDisplay = (NvAPI_GetPhysicalGPUsFromDisplayType)m_pfnNvapi_QueryInterface(ID_NvAPI_GetPhysicalGPUsFromDisplay);

		if (m_pfnNvAPI_Initialize)
		{
			nResult = m_pfnNvAPI_Initialize();
			if (enumNvStatus_OK == nResult)
			{
				m_pDisplayCards = new DISPLAY_CARD_INFO[MAX_DISPLAY_CARDS];
				ZeroMemory(m_pDisplayCards, MAX_DISPLAY_CARDS * sizeof(DISPLAY_CARD_INFO));

				// ��ȡ�Կ�����  
				nResult = EnumDisplayCards();
				MY_PROCESS_ERROR(nResult > 0);

				// ��ȡÿ���Կ���GPU����  
				for (nIndex = 0; nIndex < m_nDisplayCardCount; ++nIndex)
				{
					bRetCode = GetGpuHandles(m_pDisplayCards[nIndex].nvDisplayHandle, &m_pDisplayCards[nIndex]);
					MY_PROCESS_ERROR(bRetCode);
				}

				bResult = true;
			}
		}
	}
	else
	{
		m_bIsValid = false;
		QMessageBox::warning(nullptr, QStringLiteral("����"), QStringLiteral("�Կ������쳣"));
		return;
	}
}

//************************************
// Method:    GetDisplayInfo
// FullName:  SRMGPUInfo::GetDisplayInfo
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const int nCardIndex
// Parameter: DISPLAY_INFO * pDisplayInfo
// Note:      
//************************************
bool SRMNvidiaGPUInfo::GetDisplayInfo(const int nCardIndex, DISPLAY_INFO* pDisplayInfo)
{
	bool bResult = false;

	int nIndex = 0;

	if (nCardIndex < m_nDisplayCardCount)
	{
		bResult = GetDisplayCardGpuUsages(m_pDisplayCards[nCardIndex].nvDisplayHandle, &m_pDisplayCards[nCardIndex]);
		if (!bResult) // �����˯��֮�󣬻ᵼ���Կ�����ʧЧ
		{
			Unit();
			Init();
			bResult = GetDisplayCardGpuUsages(m_pDisplayCards[nCardIndex].nvDisplayHandle, &m_pDisplayCards[nCardIndex]);
			MY_PROCESS_ERROR(bResult);
		}		

		pDisplayInfo->nGpuCount = m_pDisplayCards[nCardIndex].nGpuCount;
		for (nIndex = 0; nIndex < pDisplayInfo->nGpuCount; ++nIndex)
		{
			pDisplayInfo->nGpuUsages[nIndex] = m_pDisplayCards[nCardIndex].sGpuInfo[nIndex].nUsage;
		}

		bResult = GetDisplayCardMemoryInfo(m_pDisplayCards[nCardIndex].nvDisplayHandle, &m_pDisplayCards[nCardIndex]);
		MY_PROCESS_ERROR(bResult);

		pDisplayInfo->dwTotalMemory = m_pDisplayCards[nCardIndex].dwTotalMemory;
		pDisplayInfo->dwFreeMemory = m_pDisplayCards[nCardIndex].dwFreeMemory;
	}
	return bResult;
}

//************************************
// Method:    GetDisplayCardGpuUsages
// FullName:  SRMGPUInfo::GetDisplayCardGpuUsages
// Access:    private 
// Returns:   bool
// Qualifier:
// Parameter: const NvDisplayHandle nvDisplayHandle
// Parameter: DISPLAY_CARD_INFO * pCardInfo
// Note:      
//************************************
bool SRMNvidiaGPUInfo::GetDisplayCardGpuUsages(const NvDisplayHandle nvDisplayHandle, DISPLAY_CARD_INFO* pCardInfo)
{
	UNREFERENCED_PARAMETER(nvDisplayHandle);
	bool bResult = false;
	int nIndex = 0;

	NvStatus nvStatus = enumNvStatus_ERROR;
	NvUsages* pnvUsages = nullptr;

	if (m_pfnNvAPI_GPU_GetUsages)
	{
		pnvUsages = new NvUsages;
		pnvUsages->Version = GPU_USAGES_VER;
		for (nIndex = 0; nIndex < pCardInfo->nGpuCount; ++nIndex)
		{
			nvStatus = m_pfnNvAPI_GPU_GetUsages(pCardInfo->sGpuInfo[nIndex].nvGpuHandle, pnvUsages);
			if (enumNvStatus_OK == nvStatus)
			{
				pCardInfo->sGpuInfo[nIndex].nUsage = pnvUsages->Usages[2];
			}
		}

		delete pnvUsages;
		pnvUsages = nullptr;

		bResult = (enumNvStatus_OK == nvStatus) ? true : false;
	}

	return bResult;
}

//************************************
// Method:    GetDisplayCardMemoryInfo
// FullName:  SRMGPUInfo::GetDisplayCardMemoryInfo
// Access:    private 
// Returns:   bool
// Qualifier:
// Parameter: const NvDisplayHandle nvDisplayHandle
// Parameter: DISPLAY_CARD_INFO * pCardInfo
// Note:      
//************************************
bool SRMNvidiaGPUInfo::GetDisplayCardMemoryInfo(const NvDisplayHandle nvDisplayHandle, DISPLAY_CARD_INFO * pCardInfo)
{
	bool bResult = false;

	NvStatus nvStatus = enumNvStatus_ERROR;
	NvMemoryInfo sMemoryInfo;

	if (m_pfnNvAPI_GPU_GetMemoryInfo)
	{
		sMemoryInfo.Version = GPU_MEMORY_INFO_VER;
		nvStatus = m_pfnNvAPI_GPU_GetMemoryInfo(nvDisplayHandle, &sMemoryInfo);
		if (enumNvStatus_OK == nvStatus)
		{
			pCardInfo->dwTotalMemory = (DWORD)(sMemoryInfo.Values[0]);
			pCardInfo->dwFreeMemory = (DWORD)(sMemoryInfo.Values[4]);

			bResult = true;
		}
	}

	return bResult;
}

//************************************
// Method:    isValid
// FullName:  SRMGPUInfo::isValid
// Access:    public 
// Returns:   bool
// Qualifier:
// Note:      
//************************************
bool SRMNvidiaGPUInfo::isValid()
{
	return m_bIsValid;
}

//************************************
// Method:    Unit
// FullName:  SRMGPUInfo::Unit
// Access:    private 
// Returns:   void
// Qualifier:
// Note:      
//************************************
void SRMNvidiaGPUInfo::Unit()
{
	m_nDisplayCardCount = 0;

	if (m_pDisplayCards)
	{
		delete[]m_pDisplayCards;
		m_pDisplayCards = nullptr;
	}

	if (m_hNvApiDll)
	{
		FreeLibrary(m_hNvApiDll);
		m_hNvApiDll = nullptr;
	}
}

//************************************
// Method:    EnumDisplayCards
// FullName:  SRMGPUInfo::EnumDisplayCards
// Access:    private 
// Returns:   int
// Qualifier:
// Note:      
//************************************
int SRMNvidiaGPUInfo::EnumDisplayCards()
{
	NvStatus nvResult;
	NvDisplayHandle nvDisplayCardHandle;

	int nIndex = 0;
	m_nDisplayCardCount = 0;
	if (m_pfnNvAPI_EnumNvidiaDisplayHandle)
	{
		for (nIndex = 0; nIndex < MAX_DISPLAY_CARDS; ++nIndex)
		{
			nvResult = m_pfnNvAPI_EnumNvidiaDisplayHandle(nIndex, &nvDisplayCardHandle);
			if (enumNvStatus_OK == nvResult)
			{
				m_pDisplayCards[m_nDisplayCardCount].nvDisplayHandle = nvDisplayCardHandle;
				++m_nDisplayCardCount;
			}
		}
	}

	return m_nDisplayCardCount;
}

//************************************
// Method:    GetGpuHandles
// FullName:  SRMGPUInfo::GetGpuHandles
// Access:    private 
// Returns:   bool
// Qualifier:
// Parameter: const NvDisplayHandle nvDisplayHandle
// Parameter: DISPLAY_CARD_INFO * pCardInfo
// Note:      
//************************************
bool SRMNvidiaGPUInfo::GetGpuHandles(const NvDisplayHandle nvDisplayHandle, DISPLAY_CARD_INFO * pCardInfo)
{
	bool bResult = false;

	NvStatus nvStatus;
	NvPhysicalGpuHandle* pnvHandles = nullptr;

	int nIndex = 0;
	unsigned int uiGpuCount = 0;

	if (m_pfnNvAPI_GetPhysicalGPUsFromDisplay)
	{
		pnvHandles = new NvPhysicalGpuHandle[MAX_PHYSICAL_GPUS];
		nvStatus = m_pfnNvAPI_GetPhysicalGPUsFromDisplay(nvDisplayHandle, pnvHandles, &uiGpuCount);
		if (enumNvStatus_OK == nvStatus)
		{
			pCardInfo->nGpuCount = min(uiGpuCount, MAX_GPU_NUM);
			for (nIndex = 0; nIndex < pCardInfo->nGpuCount; ++nIndex)
			{
				pCardInfo->sGpuInfo[nIndex].nvGpuHandle = pnvHandles[nIndex];
			}

			bResult = true;
		}

		delete[]pnvHandles;
		pnvHandles = nullptr;
	}

	return bResult;
}

//************************************
// Method:    GetThermal
// FullName:  SRMGPUInfo::GetThermal
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const int nCardIndex
// Parameter: NvGPUThermalSettings * info
// Note:      
//************************************
bool SRMNvidiaGPUInfo::GetThermal(const int nCardIndex, NvGPUThermalSettings * info)
{
	NvStatus nvStatus = enumNvStatus_ERROR;
	if (!m_pfnNvAPI_GPU_GetMemoryInfo)
		return false;

	info->Version = GPU_THERMAL_SETTINGS_VER;
	nvStatus = m_pfnNvAPI_GPU_GetThermalSettings(m_pDisplayCards[nCardIndex].sGpuInfo[0].nvGpuHandle, NVAPI_THERMAL_TARGET_ALL, info);//��ȡ�¶� 
	if (enumNvStatus_OK != nvStatus)// �����˯��֮�󣬻ᵼ���Կ�����ʧЧ
	{
		Unit();
		Init();
		nvStatus = m_pfnNvAPI_GPU_GetThermalSettings(m_pDisplayCards[nCardIndex].sGpuInfo[0].nvGpuHandle, NVAPI_THERMAL_TARGET_ALL, info);//��ȡ�¶� 
		if (enumNvStatus_OK != nvStatus)
			return false;
	}

	return true;
}



