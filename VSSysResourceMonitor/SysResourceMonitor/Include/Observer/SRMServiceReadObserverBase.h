#ifndef SRMSERVICEREADOBSERVERBASE_H_850BDCDF_78E4_402A_8C35_B4442BB7CBD1
#define SRMSERVICEREADOBSERVERBASE_H_850BDCDF_78E4_402A_8C35_B4442BB7CBD1

/************************************************************************/
/* ����Service�Ĺ۲��߻���
��Ҫ��Service�л�ȡ����*/
/************************************************************************/

#include "SRMObserverBase.h"
#include <windows.h>

class SRMServiceReadObserverBase : public SRMObserverBase
{
public:
	SRMServiceReadObserverBase(QString sReadMutexSemaphoreName, QString sShareMemoryName, QString sObserverClassName);
	virtual ~SRMServiceReadObserverBase();
	bool init();

protected:
	int readServiceData();

private: // �����ڴ����
	HANDLE m_hFile;							// ���������
	HANDLE m_hReadMutexSemaphore;			// ȫ�ֻ�����
	void* m_pBuffer;						// ������ָ��
	QString m_sReadMutexSemaphoreName;
	QString m_sShareMemoryName;
};

#endif //SRMSERVICEREADOBSERVERBASE_H_850BDCDF_78E4_402A_8C35_B4442BB7CBD1
