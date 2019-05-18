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

// �Զ������ýӿ�
class ISRMCustomSettingInf
{
	friend class SRMCustomSettingItem;
private:// ����
	virtual int v1() = 0;
	virtual int v2() = 0;
	virtual void setV1(int nV) = 0;
	virtual void setV2(int nV) = 0;
	virtual QColor color1() = 0;
	virtual QColor color2() = 0;
	virtual QColor color3() = 0;
	virtual void setColor1(QColor& oColor) = 0;
	virtual void setColor2(QColor& oColor) = 0;
	virtual void setColor3(QColor& oColor) = 0;
private:// ��ʾ��Ϣ
	virtual QString customSettingDescription() = 0;
};

// �۲��߻���
class SRMObserverBase : public QObject, public ISRMCustomSettingInf
{
	Q_OBJECT

public:
	SRMObserverBase(QString sObserverClassName);
	virtual ~SRMObserverBase();

public:// ����ʵ�ֵĽӿ�
	//************************************
	// Remark:    ���س�ʼ����� ��ʼ��ʧ�ܵģ�������Ч
	// FullName:  SRMObserverBase::init
	// Returns:   bool
	//************************************
	virtual bool init() = 0;
	//************************************
	// Remark:    ֪ͨ����
	// FullName:  SRMObserverBase::update
	// Returns:   void
	// Parameter: int nIndex								����λ�ã��±�
	// Parameter: VSSharedMemStruct * pSharedMemStruct		ʹ���±��������Լ��ı������
	// Parameter: QList<QLabel * > & oLabelList				ʹ���°����������Լ��ĸ�����Ϣ
	//************************************
	virtual void update(int nIndex, VSSharedMemStruct *pSharedMemStruct, QList<QLabel*> &oLabelList) = 0;
	//************************************
	// Remark:    ע���������˵�
	// FullName:  SRMObserverBase::regTrayMenu
	// Returns:   void
	// Parameter: QMenu * pTrayMenu							���˵�
	//************************************
	virtual void regTrayMenu(QMenu *pTrayMenu) = 0;
	//************************************
	// Remark:    �����룬�����˿ؼ�˳��
	// FullName:  SRMObserverBase::order
	// Returns:   int
	//************************************
	virtual int order() = 0;

public:// �����ӵĹ۲��ߣ���Ҫʵ��
	//************************************
	// Remark:    �����Զ������ýӿڣ�������ӣ���������һ�鷵��
	// FullName:  SRMObserverBase::customSettingInf
	// Returns:   QList<ISRMCustomSettingInf*>
	//************************************
	virtual QList<ISRMCustomSettingInf*> customSettingInfList();
	//************************************
	// Remark:    ѡ�е���Ŀ������������ӣ���Ҫ�����ӵ�ѡ�����������򷵻�1
	//			  ��������ѡ�����Ŀ��������������ߡ������еĿؼ�
	// FullName:  SRMObserverBase::getCheckedCount
	// Returns:   int
	//************************************
	virtual int checkedCount() const;

protected:// ��������õĿ�ݺ���
	void regTrayMenu(QMenu* pTrayMenu, QString sTrayActionName);	
	QColor fillCollorByValue(int nValue, VSShareMemTextNode* pValueNode);	

private:// �Զ����������
	virtual int v1() override;
	virtual int v2() override;
	virtual void setV1(int nV) override;
	virtual void setV2(int nV) override;
	virtual QColor color1() override;
	virtual QColor color2() override;
	virtual QColor color3() override;
	virtual void setColor1(QColor& oColor) override;
	virtual void setColor2(QColor& oColor) override;
	virtual void setColor3(QColor& oColor) override;

private:
	void readConfig();
	void actionStateChanged(); // slot
	void setIsChecked(bool bChecked);

private:
	int m_nV1;
	int m_nV2;
	QColor m_oColor1;
	QColor m_oColor2;
	QColor m_oColor3;
	bool m_bIsChecked;
	QString m_sObserverClassName;
};

#endif //SRMOBSERVERBASE_H_161F24E2_6327_472C_AEA5_A8CA6EED6519