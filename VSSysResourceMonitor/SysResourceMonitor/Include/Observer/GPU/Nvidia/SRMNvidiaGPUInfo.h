#ifndef SRMNVIDIAGPUINFO_H_B9DFEF68_12C7_4604_A025_8E75E8BA74B6
#define SRMNVIDIAGPUINFO_H_B9DFEF68_12C7_4604_A025_8E75E8BA74B6

/********************************************************************
 Nvidia�Կ���Ϣ����Ҫ�õ� nvapi64.lib
 GPU��Ϣ��ȡ������һ������
*********************************************************************/
#include <Windows.h>
#include "SRMError.h"
#include "Observer/GPU/SRMGPUInfoInf.h"
#include "Observer\GPU\Nvidia\NvAPI\nvapi.h"

// Nv SDKû��ֱ���ṩ �Կ�ʹ���ʣ�����Com����ķ�ʽ����
typedef void* (*NvAPI_QueryInterface)(unsigned int offset);
#define NVAPI_MAX_USAGES_PER_GPU 33
typedef struct _NvUsages
{
    unsigned int Version;
    unsigned int Usages[NVAPI_MAX_USAGES_PER_GPU];
}NvUsages;
#define GPU_USAGES_VER (sizeof(NvUsages) | 0x10000)  
#define ID_NvAPI_GPU_GetUsages 0x189A1FDF
typedef NvAPI_Status(*NvAPI_GPU_GetUsages)(NvPhysicalGpuHandle gpuHandle, NvUsages* pnvUsages);

// �ඨ��
class SRMNvidiaGPUInfo : public SRMGPUInfoInf
{
public:
    static SRMGPUInfoInf* createGPUInfoInf();

public:
	virtual int getGPUCount() override;
	virtual int getGPURate(int nIndex) override;
	virtual int getMemRate(int nIndex) override;
	virtual int getTemperature(int nIndex) override;

private:
    SRMNvidiaGPUInfo();
    ~SRMNvidiaGPUInfo();

private:
	void init();
	void unInit();

private:// API dll �ӿڶ���
    NvAPI_QueryInterface m_pFun_NvAPI_QueryInterface;
    NvAPI_GPU_GetUsages m_pFun_NvAPI_GPU_GetUsages;

private:
	bool m_bIsValid;
    NvU32               m_nGPUCount;                            // �Կ�����
    NvPhysicalGpuHandle m_hGPUHandles[NVAPI_MAX_PHYSICAL_GPUS]; // �Կ���Ϣ
    HMODULE             m_hNvApiDll;                            // Nv API dll
};
#endif //SRMNVIDIAGPUINFO_H_B9DFEF68_12C7_4604_A025_8E75E8BA74B6