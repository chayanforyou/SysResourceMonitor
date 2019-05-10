#ifndef SRMCPURATEOBSERVER_H_CBB28C7F_C36A_43F5_A6EC_C30C4FADEBA2
#define SRMCPURATEOBSERVER_H_CBB28C7F_C36A_43F5_A6EC_C30C4FADEBA2
/************************************************************************/
/* CPUʹ���ʼ��㵥Ԫ                                                                     */
/************************************************************************/
#include "Observer/SRMObserverBase.h"
#include <windows.h>

class SRMCPURateObserver : public SRMObserverBase
{
public:
	SRMCPURateObserver();
	~SRMCPURateObserver();

public:
	// ���س�ʼ����� ��ʼ��ʧ�ܵģ�ֱ��ɾ��
	virtual bool init() override;
	// ֪ͨ����
	virtual void update(int nIndex, VSSharedMemStruct* pSharedMemStruct, QList<QLabel*>& oLabelList) override;
	// ע���������˵�
	virtual void regTrayMenu(QMenu* pTrayMenu) override;
	// ������
	virtual int order() override;
	// �Զ������ý������ʾ��Ϣ
	virtual QString customSettingDescription() override;

private:
	int getCPURate();

private:
	FILETIME m_oPreIdleTime;
	FILETIME m_oPreKernelTime;
	FILETIME m_oPreUserTime;
};

#endif //SRMCPURATEOBSERVER_H_CBB28C7F_C36A_43F5_A6EC_C30C4FADEBA2