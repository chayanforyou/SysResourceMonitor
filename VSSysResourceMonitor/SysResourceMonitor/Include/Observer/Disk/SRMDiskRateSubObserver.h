#ifndef SRMDISKRATESUBOBSERVER_H_C37EDFB1_B306_4E9E_AF67_C54882276BC0
#define SRMDISKRATESUBOBSERVER_H_C37EDFB1_B306_4E9E_AF67_C54882276BC0
/************************************************************************/
/* ��������IOʹ���ʣ�����ע�ᣬ��SRMDiskRateObserver ����
	SubObserver ��Ҫ����ˢ����ʾ���������õȣ���������
*/
/************************************************************************/
#include "Observer\SRMObserverBase.h"

class SRMDiskRateSubObserver : public SRMObserverBase
{
public:
	SRMDiskRateSubObserver(QString sPartitionName, QString sTrayMenuName);
	~SRMDiskRateSubObserver();

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

public:
	void updateInfo(QString sPartitionName, int nRate);

private:
	QString m_sPartitionName;
	QString m_sTrayMenuName;
	int m_nRate;
};

#endif //SRMDISKRATESUBOBSERVER_H_C37EDFB1_B306_4E9E_AF67_C54882276BC0