#ifndef SRMMEMRATEOBSERVER_H_BD5E3A7E_9EC3_4F22_B78D_5CB8A0A21C0B
#define SRMMEMRATEOBSERVER_H_BD5E3A7E_9EC3_4F22_B78D_5CB8A0A21C0B
/************************************************************************/
/* �ڴ�ռ��                                                                     */
/************************************************************************/

#include "Observer/SRMObserverBase.h"

class SRMMemRateObserver : public SRMObserverBase
{
public:
	SRMMemRateObserver();
	~SRMMemRateObserver();

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
	int getMemRate();
};

#endif //SRMMEMRATEOBSERVER_H_BD5E3A7E_9EC3_4F22_B78D_5CB8A0A21C0B