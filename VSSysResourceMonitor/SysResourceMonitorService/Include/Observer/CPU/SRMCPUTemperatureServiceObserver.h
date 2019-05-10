#ifndef SRMCPUTEMPERATURESERVICEOBSERVER_H_2C99CD6D_65A4_4111_86A8_578EE6BFF7A5
#define SRMCPUTEMPERATURESERVICEOBSERVER_H_2C99CD6D_65A4_4111_86A8_578EE6BFF7A5
/************************************************************************/
/* �������¶ȶ�ȡģ�飬����  WinRing0x64.libģ��
*/
/************************************************************************/
#include "Observer/SRMServiceObserverBase.h"
static QString s_sCPUTemperatureServiceWriteMutexSemaphoreName = "Global\\CPUTemperatureServiceWriteMutexSemaphoreName";
static QString s_sCPUTemperatureServiceShareMemoryName = "Global\\CPUTemperatureServiceShareMemoryName";

class SRMCPUTemperatureServiceObserver : public SRMServiceObserverBase
{
public:
	SRMCPUTemperatureServiceObserver();
	~SRMCPUTemperatureServiceObserver();

public:
	virtual bool init() override;
	virtual void update() override;

private:
	int getCPUTemperature();

private:
	void readRduTjunctionMax();

private:
	DWORD m_uRduTjunctionMax;
};

#endif //SRMCPUTEMPERATURESERVICEOBSERVER_H_2C99CD6D_65A4_4111_86A8_578EE6BFF7A5