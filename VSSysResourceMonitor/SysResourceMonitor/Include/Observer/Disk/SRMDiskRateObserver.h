#ifndef SRMDISKRATEOBSERVER_H_3E936524_6BD6_45BA_9453_64D317DBB998
#define SRMDISKRATEOBSERVER_H_3E936524_6BD6_45BA_9453_64D317DBB998
/************************************************************************/
/* ����ioʹ����
   ʹ�� WMI ��ȡ����*/
/************************************************************************/
#include "Observer\SRMObserverBase.h"
#include <QString>
#include <QHash>
#include "Observer\Disk\SRMDiskRateSubObserver.h"

class IWbemRefresher;
class IWbemHiPerfEnum;

struct PartitionInfo
{
	QString sTrayMenuName;
	QString sPartitionName;
	int nUsingRate;
};

class SRMDiskRateObserver : public SRMObserverBase
{
public:
	SRMDiskRateObserver();
	~SRMDiskRateObserver();

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
	// ѡ�е���Ŀ����
	virtual int checkedCount() const override;
	// �Զ�������
	virtual QList<ISRMCustomSettingInf*> customSettingInfList() override;

private:
	void updatePartitionInfo();
	void addAvgAndBusiest();
	SRMDiskRateSubObserver* findSubObserver(const PartitionInfo& oPartitionInfo);

private:
	IWbemRefresher* m_pWbemRefresher;
	IWbemHiPerfEnum* m_pWbemHiPerfEnum;

private:
	QList<PartitionInfo> m_oPartitionInfoList;
	QHash<QString, SRMDiskRateSubObserver*> m_oSubObserverHash;
};

#endif //SRMDISKRATEOBSERVER_H_3E936524_6BD6_45BA_9453_64D317DBB998
