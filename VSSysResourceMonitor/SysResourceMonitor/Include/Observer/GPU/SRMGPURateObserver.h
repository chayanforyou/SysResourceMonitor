#ifndef SRMGPURATEOBSERVER_H_28F5CF90_5408_47D0_B748_FFE7CBAE8E0E
#define SRMGPURATEOBSERVER_H_28F5CF90_5408_47D0_B748_FFE7CBAE8E0E
/************************************************************************/
/* GPUʹ����                                                                     */
/************************************************************************/
#include "Observer/SRMObserverBase.h"

class SRMGPUInfoInf;

class SRMGPURateObserver : public SRMObserverBase
{
public:
	SRMGPURateObserver();
	~SRMGPURateObserver();

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
	QString customSettingDescription() override;

private:
	SRMGPUInfoInf* m_pGPUInfoInf;
};

#endif //SRMGPURATEOBSERVER_H_28F5CF90_5408_47D0_B748_FFE7CBAE8E0E
