#ifndef SRMCPUTEMPERATUREOBSERVER_H_5E8031EF_46E0_45DD_B472_C44951B51DAD
#define SRMCPUTEMPERATUREOBSERVER_H_5E8031EF_46E0_45DD_B472_C44951B51DAD
/************************************************************************/
/* CPU�¶ȵ�Ԫ����Service�ж���                                                                     */
/************************************************************************/
#include "Observer/SRMServiceReadObserverBase.h"

class SRMCPUTemperatureObserver : public SRMServiceReadObserverBase
{
public:
	SRMCPUTemperatureObserver();
	~SRMCPUTemperatureObserver();
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
};

#endif //SRMCPUTEMPERATUREOBSERVER_H_5E8031EF_46E0_45DD_B472_C44951B51DAD