#ifndef SRMMODULESUBJECT_H_C34DA930_C79E_4710_B025_4E5B70F9C1F5
#define SRMMODULESUBJECT_H_C34DA930_C79E_4710_B025_4E5B70F9C1F5
/************************************************************************/
/* �������۲��ߣ���֪ͨ�۲��߸�������                                                                    */
/************************************************************************/

#include <QObject>
#include <QList>
#include <QTimer>
#include <QLabel>

class SRMObserverBase;
class ISRMCustomSettingInf;
class VSSharedMemStruct;
class QMenu;

class SRMObserverFactory
{
public:
	virtual SRMObserverBase* createObject() = 0;
};

class SRMModuleSubject : public QObject
{
	Q_OBJECT

public:// �����һЩ����
	//************************************
	// Remark:    ֪ͨ����
	// FullName:  SRMModuleSubject::doOntify
	// Returns:   void
	// Parameter: VSSharedMemStruct * pSharedMemStruct	��߿ؼ�
	// Parameter: QList<QLabel * > & oLabelList			�����ؼ�
	//************************************
	void doOntify(VSSharedMemStruct* pSharedMemStruct, QList<QLabel*>& oLabelList);
	//************************************
	// Remark:    ע���Ҽ��˵�
	// FullName:  SRMModuleSubject::doRegTrayMenu
	// Returns:   void
	// Parameter: QMenu * pTrayMenu
	//************************************
	void doRegTrayMenu(QMenu* pTrayMenu);
	//************************************
	// Remark:    ͳ��ѡ�е���Ŀ�����ڱ�ߡ������ؼ���ʼ��
	// FullName:  SRMModuleSubject::doCheckedCount
	// Returns:   int
	//************************************
	int doCheckedCount();
	//************************************
	// Remark:    ��ȡ�Զ������ýӿڣ������Զ������ù���
	// FullName:  SRMModuleSubject::doCustomSettingInfList
	// Returns:   QList<ISRMCustomSettingInf*>
	//************************************
	QList<ISRMCustomSettingInf*> doCustomSettingInfList();	

public:// ��Դ����
	static SRMModuleSubject* getInstance();
	void init();
	void release();

public:// �۲���ע����
	void regObserverFactory(SRMObserverFactory* pObserverFactory);

private:
	SRMModuleSubject();
	~SRMModuleSubject();	

private:
	QList<SRMObserverBase*> m_oObserverList;
	QList<SRMObserverFactory*> m_oObserverFactoryList; // ����һ��factory������ observer�������ʼ��
};

#define REG_SRM_OBSERVER(observer)\
class observer##Factory : public SRMObserverFactory\
{\
public:\
	SRMObserverBase* createObject() override\
	{\
		return new observer;\
	}\
};\
class observer##Register\
{\
public:\
	observer##Register()\
	{\
		SRMModuleSubject::getInstance()->regObserverFactory(new observer##Factory);\
	};\
};\
static observer##Register s_observer##Register;

#endif //SRMMODULESUBJECT_H_C34DA930_C79E_4710_B025_4E5B70F9C1F5
