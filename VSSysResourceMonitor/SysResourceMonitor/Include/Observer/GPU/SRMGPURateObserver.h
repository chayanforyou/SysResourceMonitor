#ifndef SRMGPURATEOBSERVER_H_28F5CF90_5408_47D0_B748_FFE7CBAE8E0E
#define SRMGPURATEOBSERVER_H_28F5CF90_5408_47D0_B748_FFE7CBAE8E0E
/************************************************************************/
/* �Կ�����                                                                     */
/************************************************************************/
#include "Observer/SRMObserverBase.h"

enum EnGPUType
{
	egtNune = 0,
	egtNvidia,
	egtAMD
};

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
	int getGPURate();

private:
	EnGPUType m_enGPUType;
};

#endif //SRMGPURATEOBSERVER_H_28F5CF90_5408_47D0_B748_FFE7CBAE8E0E
