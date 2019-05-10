#ifndef SRMGPUMEMRATEOBSERVER_H_3CFC26CB_F532_4FCE_9647_BD495AAF1EDD
#define SRMGPUMEMRATEOBSERVER_H_3CFC26CB_F532_4FCE_9647_BD495AAF1EDD

#include "Observer/SRMObserverBase.h"

enum EnGPUType
{
	egtNune = 0,
	egtNvidia,
	egtAMD
};

class SRMGPUMemRateObserver : public SRMObserverBase
{
public:
	SRMGPUMemRateObserver();
	~SRMGPUMemRateObserver();

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
	int getGPUMamRate();

private:
	EnGPUType m_enGPUType;
};

#endif //SRMGPUMEMRATEOBSERVER_H_3CFC26CB_F532_4FCE_9647_BD495AAF1EDD