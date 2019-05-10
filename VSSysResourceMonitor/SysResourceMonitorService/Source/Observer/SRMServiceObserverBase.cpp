
#include "Observer/SRMServiceObserverBase.h"

SRMServiceObserverBase::SRMServiceObserverBase(QString sWriteMutexSemaphoreName, QString sShareMemoryName)
	: m_sMutexSemaphoreName(sWriteMutexSemaphoreName)
	, m_sShareMemoryName(sShareMemoryName)
{
	initSharedMemory();
}

SRMServiceObserverBase::~SRMServiceObserverBase()
{
	freeSharedMemory();
}

bool SRMServiceObserverBase::init()
{
	if (!m_pSharedBuffer
		|| !m_hMapFile
		|| !m_hWriteSemaphore)
		return false;

	return true;
}

void SRMServiceObserverBase::writeValue(int nValue)
{
	WaitForSingleObject(m_hWriteSemaphore, INFINITE);	// ���ź���������ȴ�ʱ�䣩
	memcpy(m_pSharedBuffer, &nValue, sizeof(int));
	ReleaseSemaphore(m_hWriteSemaphore, 1, NULL);		// ���ź���������ͷŵ�������out�ͷ�֮ǰ��Դ������
}

void SRMServiceObserverBase::initSharedMemory()
{
	// �������е�Ȩ�ޱ���ͨ����Ҫ�ߣ���Ҫһ�������� ��ȫ������ ��������ͨ���̷���
	SECURITY_DESCRIPTOR oSecutityDese;
	::InitializeSecurityDescriptor(&oSecutityDese, SECURITY_DESCRIPTOR_REVISION);
	::SetSecurityDescriptorDacl(&oSecutityDese, TRUE, NULL, FALSE);
	SECURITY_ATTRIBUTES oSecurityAttr;
	oSecurityAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	oSecurityAttr.bInheritHandle = FALSE;
	oSecurityAttr.lpSecurityDescriptor = &oSecutityDese;
	m_hMapFile = ::CreateFileMapping(INVALID_HANDLE_VALUE, &oSecurityAttr, PAGE_READWRITE, 0, 1024, m_sShareMemoryName.toStdWString().c_str());
	m_pSharedBuffer = ::MapViewOfFile(m_hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	m_hWriteSemaphore = CreateSemaphore(&oSecurityAttr, 1, 1, m_sMutexSemaphoreName.toStdWString().c_str());
}

void SRMServiceObserverBase::freeSharedMemory()
{
	UnmapViewOfFile(m_pSharedBuffer);
	CloseHandle(m_hMapFile);
	CloseHandle(m_hWriteSemaphore);
}

