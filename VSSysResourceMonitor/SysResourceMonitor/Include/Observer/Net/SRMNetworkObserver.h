#ifndef SRMNETWORKOBSERVER_H_602C161A_DF67_4F1A_9E82_A5E2EE71D319
#define SRMNETWORKOBSERVER_H_602C161A_DF67_4F1A_9E82_A5E2EE71D319
/************************************************************************/
/* ���ٶ�ȡģ��     
������ Iphlpapi.lib ģ��
*/
/************************************************************************/

#include "Observer/SRMObserverBase.h"
#include <QSet>
#include <windows.h>
#include <iphlpapi.h>

class SRMNetworkObserver : public SRMObserverBase
{
public:
	SRMNetworkObserver();
	~SRMNetworkObserver();

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
	bool initAdapterTable();
	QSet<std::wstring> getPCI();

private:
	void readNetValue();

private:
	double m_dCurDownloadSpeed;
	double m_dCurUploadSpeed;
	PMIB_IFTABLE m_pAdapterTable;
	QSet<DWORD> m_oAdapterIDSet;
};

#endif //SRMNETWORKOBSERVER_H_602C161A_DF67_4F1A_9E82_A5E2EE71D319