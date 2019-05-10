#include "SysResourceMonitorService.h"
#include "Observer/SRMServiceSubject.h"
static std::wstring lsSysResourceMonitorServiceMutex = L"Global\\VS_SysResourceMonitorServiceMutex";
static QString c_sServiceName = QString::fromStdWString(L"SysResourceMonitor Service");
static QString c_sServiceDescription = QString::fromStdWString(L"SysResourceMonitor ���ڶ�ȡ���ָ�Ȩ��ϵͳ��Դ��Ϣ�ķ���");

SysResourceMonitorService::SysResourceMonitorService(int argc, char** argv)
	: QtService<QCoreApplication>(argc, argv, c_sServiceName)
	, m_hSysResourceMonitorServiceMutex(nullptr)
{
	setServiceDescription(c_sServiceDescription);
	setServiceFlags(QtServiceBase::Default);
	setStartupType(QtServiceController::AutoStartup);
}

SysResourceMonitorService::~SysResourceMonitorService()
{

}

void SysResourceMonitorService::start()
{
	// �������е�Ȩ�ޱ���ͨ����Ҫ�ߣ���Ҫһ�������� ��ȫ������ ��������ͨ���̷���
	SECURITY_DESCRIPTOR oSecutityDese;
	::InitializeSecurityDescriptor(&oSecutityDese, SECURITY_DESCRIPTOR_REVISION);
	::SetSecurityDescriptorDacl(&oSecutityDese, TRUE, NULL, FALSE);
	SECURITY_ATTRIBUTES oSecurityAttr;
	oSecurityAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	oSecurityAttr.bInheritHandle = FALSE;
	oSecurityAttr.lpSecurityDescriptor = &oSecutityDese;
	HANDLE hResult = OpenMutex(SEMAPHORE_ALL_ACCESS, FALSE, lsSysResourceMonitorServiceMutex.c_str());
	if (hResult)
	{
		CloseHandle(hResult);
		return;
	}

	m_hSysResourceMonitorServiceMutex = CreateMutex(&oSecurityAttr, FALSE, lsSysResourceMonitorServiceMutex.c_str());
	connect(&m_oTimer, &QTimer::timeout, this, &SysResourceMonitorService::update, Qt::UniqueConnection);
	m_oTimer.start(1000);
	logMessage(QString::fromStdWString(L"SysResourceMonitorService���������ɹ�"));
}

void SysResourceMonitorService::stop()
{
	CloseHandle(m_hSysResourceMonitorServiceMutex);
	m_hSysResourceMonitorServiceMutex = nullptr;
	m_oTimer.stop();
	logMessage(QString::fromStdWString(L"SysResourceMonitorService����ֹͣ�ɹ�"));
}

void SysResourceMonitorService::update()
{
	SRMServiceSubject::getInstance()->doOntify();
}
