#ifndef SRMREGMANAGER_H_D4E06FFC_3DAE_4AE1_B6DD_377417E4F52B
#define SRMREGMANAGER_H_D4E06FFC_3DAE_4AE1_B6DD_377417E4F52B
/************************************************************************/
/* ע������                                                                     */
/************************************************************************/
#include <QString>

class SRMRegManager
{
public:
	static SRMRegManager* getInstance();
	~SRMRegManager();

public:// ��������
	bool setAutoRun();
	bool cancelAutoRun();
	bool isAutoRun();

public:
	//************************************
	// Remark:    ����ע�����
	// FullName:  SRMRegManager::saveCustomInfo
	// Returns:   bool
	// Parameter: QString & sKey
	// Parameter: QString & sValue  ��֧�ֿո񣬲�֧�ֿո񣬲�֧�ֿո�
	//************************************
	bool saveCustomInfo(QString &sKey, QString &sValue);
	QString readCustomInfo(QString& sKey);

private:
	bool regWrite(QString sRegPath, QString sKey, QString sValue);

private:
	SRMRegManager();
};

#endif //SRMREGMANAGER_H_D4E06FFC_3DAE_4AE1_B6DD_377417E4F52B