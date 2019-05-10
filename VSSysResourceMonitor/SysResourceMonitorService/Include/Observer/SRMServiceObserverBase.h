#ifndef SRMSERVICEOBSERVERBASE_H_94631F19_4A82_41A8_8305_8F659B242279
#define SRMSERVICEOBSERVERBASE_H_94631F19_4A82_41A8_8305_8F659B242279
/************************************************************************/
/* �۲��߻���                                                                     */
/************************************************************************/
#include <QObject>
#include <windows.h>

class SRMServiceObserverBase : public QObject
{
	Q_OBJECT
public:
	SRMServiceObserverBase(QString sWriteMutexSemaphoreName, QString sShareMemoryName);
	virtual ~SRMServiceObserverBase();

public:
	// ���س�ʼ����� ��ʼ��ʧ�ܵģ�ֱ��ɾ��
	virtual bool init();
	// ֪ͨ����
	virtual void update() = 0;

protected:
	// ֻ�ܴ�һ��intֵ
	void writeValue(int nValue);

private:
	void initSharedMemory();
	void freeSharedMemory();
	void* m_pSharedBuffer;
	HANDLE m_hMapFile;
	HANDLE m_hWriteSemaphore;
	QString m_sMutexSemaphoreName;
	QString m_sShareMemoryName;
};

#endif //SRMSERVICEOBSERVERBASE_H_94631F19_4A82_41A8_8305_8F659B242279