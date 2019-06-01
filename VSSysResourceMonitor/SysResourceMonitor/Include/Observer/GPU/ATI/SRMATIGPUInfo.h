#ifndef SRMATIGPUINFO_H_8ADE5879_B99F_46F9_BC02_D750992626DB
#define SRMATIGPUINFO_H_8ADE5879_B99F_46F9_BC02_D750992626DB
/************************************************************************/
/* ATI�Կ���Ϣ 
���� atiadlxx.dll
���� atiadlxx.dll �� atiadlxy.dll:
xx��Զ������ϵͳ����һ�µġ�32λϵͳ�ϣ�xx����32λ��64λϵͳ�ϣ�xx����64λ��
xy����;�ǣ�64λϵͳ�ϣ�����32λ����ʱ��xxû���ã�����32λ��xy��
����ȼ���xx�����ʧ���ˣ��ټ���xy
ADL û���ṩ�Դ���Ϣ��ȡ�ӿ�
*/
/************************************************************************/
#include "Observer\GPU\ATI\ADL\adl_sdk.h"
#include "Observer\GPU\SRMGPUInfoInf.h"
#include <windows.h>

// API����
typedef int (*ADL_MAIN_CONTROL_CREATE) (ADL_MAIN_MALLOC_CALLBACK, int);
typedef int (*ADL_MAIN_CONTROL_DESTROY) ();
typedef int (*ADL_ADAPTER_NUMBEROFADAPTERS_GET) (int*);
typedef int (*ADL_ADAPTER_ADAPTERINFO_GET) (LPAdapterInfo, int);
typedef int (*ADL_DISPLAY_COLORCAPS_GET) (int, int, int*, int*);
typedef int (*ADL_DISPLAY_COLOR_GET) (int, int, int, int*, int*, int*, int*, int*);
typedef int (*ADL_DISPLAY_COLOR_SET) (int, int, int, int);
typedef int (*ADL_DISPLAY_DISPLAYINFO_GET)	(int, int*, ADLDisplayInfo**, int);
typedef int (*ADL_OVERDRIVE5_TEMPERATURE_GET) (int, int, ADLTemperature*);
typedef int (*ADL_OVERDRIVE5_FANSPEED_GET) (int, int, ADLFanSpeedValue*);
typedef int (*ADL_OVERDRIVE5_CURRENTACTIVITY_GET) (int, ADLPMActivity*);
typedef int (*ADL_ADAPTER_MEMORYINFO_GET) (int, ADLMemoryInfo*);

class SRMATIGPUInfo : public SRMGPUInfoInf
{
public:
    static SRMGPUInfoInf* createGPUInfoInf();

public:
    virtual int getGPUCount() override;
    virtual int getGPURate(int nIndex) override;
    virtual int getMemRate(int nIndex) override;
    virtual int getTemperature(int nIndex) override;

private:
    SRMATIGPUInfo();
    ~SRMATIGPUInfo();
    void init();
    void unInit();

private:// API�ӿ�ָ��
    ADL_MAIN_CONTROL_CREATE				m_pFun_ADL_Main_Control_Create;
    ADL_MAIN_CONTROL_DESTROY			m_pFun_ADL_Main_Control_Destroy;
    ADL_ADAPTER_NUMBEROFADAPTERS_GET	m_pFun_ADL_Adapter_NumberOfAdapters_Get;
    ADL_ADAPTER_ADAPTERINFO_GET		    m_pFun_ADL_Adapter_AdapterInfo_Get;
    ADL_OVERDRIVE5_CURRENTACTIVITY_GET	m_pFun_ADL_Overdrive5_CurrentActivity_Get;
    ADL_OVERDRIVE5_TEMPERATURE_GET		m_pFun_ADL_Overdrive5_Temperature_Get;
    ADL_ADAPTER_MEMORYINFO_GET          m_pFun_ADL_Adapter_MemoryInfo_Get;
    //ADL_DISPLAY_COLORCAPS_GET			m_pFun_ADL_Display_ColorCaps_Get;
    //ADL_DISPLAY_COLOR_GET				m_pFun_ADL_Display_Color_Get;
    //ADL_DISPLAY_COLOR_SET				m_pFun_ADL_Display_Color_Set;
    //ADL_DISPLAY_DISPLAYINFO_GET		    m_pFun_ADL_Display_DisplayInfo_Get;    
    //ADL_OVERDRIVE5_FANSPEED_GET			m_pFun_ADL_Overdrive5_FanSpeed_Get;

private:
    bool m_bIsValid;
    int m_AdaptersNumber;               // �Կ�����
    AdapterInfo* m_pAdapterInfos;       // �Կ���Ϣ, ����һ������
    HINSTANCE m_hATIApiDll;             // API dll ���
};
#endif //SRMATIGPUINFO_H_8ADE5879_B99F_46F9_BC02_D750992626DB
