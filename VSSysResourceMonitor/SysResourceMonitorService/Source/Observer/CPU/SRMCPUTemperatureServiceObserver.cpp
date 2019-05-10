
#include <windows.h>
#include "Observer/CPU/OlsApi.h"
#include "Observer/SRMServiceSubject.h"
#include "Observer/CPU/SRMCPUTemperatureServiceObserver.h"
#include "qtservice.h"

#define IA32_PACKAGE_THERM_STATUS 0x1B1     // CPU package�¶�(16~22)λ
#define IA32_THERM_STATUS_MSR 0x019C        // CPU �����¶�(16~22)λ
#define IA32_TEMPERATURE_TARGET 0x01A2      // TjunctionMax CPU �����¶�  (16~23)λ

REG_SRM_SERVICE_OBSERVER(SRMCPUTemperatureServiceObserver);

SRMCPUTemperatureServiceObserver::SRMCPUTemperatureServiceObserver()
	: SRMServiceObserverBase(s_sCPUTemperatureServiceWriteMutexSemaphoreName, s_sCPUTemperatureServiceShareMemoryName)
{
}

SRMCPUTemperatureServiceObserver::~SRMCPUTemperatureServiceObserver()
{
	DeinitializeOls();
}

bool SRMCPUTemperatureServiceObserver::init()
{
	if (!__super::init())
		return false;

	if (!InitializeOls())
	{
		QtServiceBase::instance()->logMessage(QString::fromStdWString(L"WinRing0x64��ʼ��ʧ��"), QtServiceBase::Warning);
		//switch (GetDllStatus())
		//{
		//case OLS_DLL_NO_ERROR:
		//    QMessageBox::warning(this, QStringLiteral("û���ҵ�����"), QStringLiteral("OLS_DLL_NO_ERROR"));
		//    break;
		//case OLS_DLL_UNSUPPORTED_PLATFORM:
		//    QMessageBox::warning(this, QStringLiteral("û���ҵ�����"), QStringLiteral("OLS_DLL_UNSUPPORTED_PLATFORM"));
		//    break;
		//case OLS_DLL_DRIVER_NOT_LOADED:
		//    QMessageBox::warning(this, QStringLiteral("û���ҵ�����"), QStringLiteral("OLS_DLL_DRIVER_NOT_LOADED"));
		//    break;
		//case OLS_DLL_DRIVER_NOT_FOUND:
		//    QMessageBox::warning(this, QStringLiteral("û���ҵ�����"), QStringLiteral("OLS_DLL_DRIVER_NOT_FOUND"));
		//    break;
		//case OLS_DLL_DRIVER_UNLOADED:
		//    QMessageBox::warning(this, QStringLiteral("û���ҵ�����"), QStringLiteral("OLS_DLL_DRIVER_UNLOADED"));
		//    break;
		//case OLS_DLL_DRIVER_NOT_LOADED_ON_NETWORK:
		//    QMessageBox::warning(this, QStringLiteral("û���ҵ�����"), QStringLiteral("OLS_DLL_DRIVER_NOT_LOADED_ON_NETWORK"));
		//    break;
		//case OLS_DLL_UNKNOWN_ERROR:
		//default:
		//    QMessageBox::warning(this, QStringLiteral("û���ҵ�����"), QStringLiteral("OLS_DLL_UNKNOWN_ERROR"));
		//    return;
		//    break;
		//}
		return false;
	}
	else
	{
		readRduTjunctionMax();
		return true;
	}
}

void SRMCPUTemperatureServiceObserver::update()
{
	writeValue(getCPUTemperature());
}

int SRMCPUTemperatureServiceObserver::getCPUTemperature()
{
	DWORD uHigh, uLow;
	//RdmsrTx(IA32_THERM_STATUS_MSR, &uLow, &uHigh, 1LU << 0);  // 1, 2, 4, 8  ��ͬ���ĵ��¶� 
	RdmsrTx(IA32_PACKAGE_THERM_STATUS, &uLow, &uHigh, 1LU << 0); // CPU���¶�

	DWORD uCur = (uLow & 0x7FFFFF) >> 16;                  // (16~22)λ
	return m_uRduTjunctionMax - uCur;
}

//************************************
// Method:    readRduTjunctionMax
// FullName:  SRMCpuTemperatureObserver::readRduTjunctionMax
// Access:    private 
// Returns:   void
// Qualifier:
// Note:      ��ȡ�����¶�
//************************************
void SRMCPUTemperatureServiceObserver::readRduTjunctionMax()
{
	DWORD uHigh, uLow;
	RdmsrTx(IA32_TEMPERATURE_TARGET, &uLow, &uHigh, 1LU << 0);   // �����¶�
	m_uRduTjunctionMax = (uLow & 0xFFFFFF) >> 16;                // (16~23)λ
}

