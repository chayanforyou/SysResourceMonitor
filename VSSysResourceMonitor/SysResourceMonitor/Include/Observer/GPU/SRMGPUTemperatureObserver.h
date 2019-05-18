#ifndef SRMGPUTEMPERATUREOBSERVER_H_136B2060_1A58_4DF2_97BB_3CCDFA4DE3E2
#define SRMGPUTEMPERATUREOBSERVER_H_136B2060_1A58_4DF2_97BB_3CCDFA4DE3E2
/************************************************************************/
/* GPU�¶�                                                                   */
/************************************************************************/
#include "Observer/SRMObserverBase.h"

class SRMGPUInfoInf;

class SRMGPUTemperatureObserver : public SRMObserverBase
{
public:
	SRMGPUTemperatureObserver();
	~SRMGPUTemperatureObserver();

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

#endif //SRMGPUTEMPERATUREOBSERVER_H_136B2060_1A58_4DF2_97BB_3CCDFA4DE3E2