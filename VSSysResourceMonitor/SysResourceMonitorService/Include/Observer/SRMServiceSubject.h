#ifndef SRMSERVICESUBJECT_H_B8C0F79A_4D8E_4D22_854A_C2C64A12ED65
#define SRMSERVICESUBJECT_H_B8C0F79A_4D8E_4D22_854A_C2C64A12ED65
/************************************************************************/
/*   �������۲��ߣ���֪ͨ�۲��߸�������                                                                   */
/************************************************************************/
#include <QObject>

class SRMServiceObserverBase;

class SRMServiceSubject : public QObject
{
	Q_OBJECT
public:
	static SRMServiceSubject* getInstance();
	void doOntify();

public:
	void regObserver(SRMServiceObserverBase* pObserver);

private:
	SRMServiceSubject();
	~SRMServiceSubject();

private:
	QList<SRMServiceObserverBase*> m_oObserverList;
};

#define REG_SRM_SERVICE_OBSERVER(observer)\
class observer##ServiceRegister\
{\
public:\
	observer##ServiceRegister()\
	{\
		SRMServiceSubject::getInstance()->regObserver(new observer);\
	};\
};\
static observer##ServiceRegister s_observer##ServiceRegister;

#endif //SRMSERVICESUBJECT_H_B8C0F79A_4D8E_4D22_854A_C2C64A12ED65