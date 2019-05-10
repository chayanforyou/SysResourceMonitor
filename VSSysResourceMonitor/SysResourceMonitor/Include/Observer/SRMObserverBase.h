#ifndef SRMOBSERVERBASE_H_161F24E2_6327_472C_AEA5_A8CA6EED6519
#define SRMOBSERVERBASE_H_161F24E2_6327_472C_AEA5_A8CA6EED6519
/************************************************************************/
/* ��ͨ�۲��߻��࣬������ֱ�ӿ��������Ӧ���ݻ�ȡ
������ SRMServiceReadObserverBase				*/
/************************************************************************/
#include <QString>
#include <QColor>
#include <QObject>
#include <QLabel>
#include "VSDeskBandOperation.h"

class QMenu;

class SRMObserverBase : public QObject
{
	Q_OBJECT

public:
	SRMObserverBase(QString sObserverClassName);
	virtual ~SRMObserverBase();

public:
	// ���س�ʼ����� ��ʼ��ʧ�ܵģ�ֱ��ɾ��
	virtual bool init() = 0;
	// ֪ͨ����
	virtual void update(int nIndex, VSSharedMemStruct *pSharedMemStruct, QList<QLabel*> &oLabelList) = 0;
	// ע���������˵�
	virtual void regTrayMenu(QMenu *pTrayMenu) = 0;
	// ������
	virtual int order() = 0;
	// �Զ������ý������ʾ��Ϣ
	virtual QString customSettingDescription() = 0;

protected:
	virtual void actionStateChanged();
	virtual void regTrayMenu(QMenu *pTrayMenu, QString sTrayActionName);

public:// �������
	int v1();
	int v2();
	QColor color1();
	QColor color2();
	QColor color3();
	bool isChecked();
	void setV1(int nV);
	void setV2(int nV);
	void setColor1(QColor& oColor);
	void setColor2(QColor& oColor);
	void setColor3(QColor& oColor);
	void setIsChecked(bool bChecked);

protected:
	QColor fillCollorByValue(int nValue, VSShareMemTextNode* pValueNode);

private:
	void readConfig();

private:
	int m_nV1;
	int m_nV2;
	QColor m_oColor1;
	QColor m_oColor2;
	QColor m_oColor3;
	bool m_bIsChecked;

protected:
	QString m_sObserverClassName;
};

#endif //SRMOBSERVERBASE_H_161F24E2_6327_472C_AEA5_A8CA6EED6519