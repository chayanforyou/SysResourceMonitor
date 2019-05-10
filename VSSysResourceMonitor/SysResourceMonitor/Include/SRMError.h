#ifndef SRMERROR_H_52A7B72E_A4CF_423B_A57E_9640516FCB94
#define SRMERROR_H_52A7B72E_A4CF_423B_A57E_9640516FCB94
/************************************************************************/
/* �쳣����                                                                     */
/************************************************************************/
#include <QString>

enum EnSRMError
{
	esrmeUnKnown = -1,
	esrmeNoError = 0,			// 0
	esrmeConfigError = 10,		// 10 �����ļ�����д�򴴽�ʧ��
	esrmeGpuReadError,			// 10 �Կ����ݶ�ȡ����
};

class SRMError
{
public:
	SRMError(EnSRMError enError, QString &sMessage = QString("")) 
		: m_enErrorCode(enError), m_sErrorMessage(sMessage){
	}
	~SRMError(){

	}

	EnSRMError errorCode() {
		return m_enErrorCode;
	}
	QString errorMessage() {
		return m_sErrorMessage;
	}

private:
	EnSRMError m_enErrorCode;
	QString m_sErrorMessage;
};

#endif //SRMERROR_H_52A7B72E_A4CF_423B_A57E_9640516FCB94