#include <windows.h>
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QDir>
#include "SRMError.h"
#include "SRMScopeOnExit.h"
#include "SysResourceMonitor.h"

// �жϳ���֮��Ļ���, ֻ�ܴ�һ�����
bool checkUnique()
{
	std::wstring sTitle = L"��ʾ";
	std::wstring sMessage = L"SysResourceMonitor �Ѿ���������";
	std::wstring sMutex = L"VS_SysResourceMonitor";
	HANDLE hMutex = CreateMutex(NULL, TRUE, sMutex.c_str());
	if (!hMutex){
		MessageBox(NULL, sMessage.c_str(), sTitle.c_str(), S_OK);
		return false;
	}
		
	if (GetLastError() == ERROR_ALREADY_EXISTS){
		MessageBox(NULL, sMessage.c_str(), sTitle.c_str(), S_OK);
		CloseHandle(hMutex);
		return false;
	};

	return true;
}

int main(int argc, char* argv[])
{
	// 1. com���ͳһ��ʼ���������ط���Ҫ�ٳ�ʼ��
	HRESULT hResult =  CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	SCOPE_EXIT{ CoUninitialize(); };

	if (hResult != S_OK) 
		return -1;	

	// 2. ��֧�ֶ����
	if (!checkUnique()){
		return 0;
	}

	// 3. ������
	QApplication a(argc, argv);
	QDir::setCurrent(qApp->applicationDirPath());
	try{
		SysResourceMonitor w;
		w.setWindowIcon(QIcon(":/Images/SysResourceMonitor.png"));
		w.hide(); // �����岻��ʾ
		w.doWork();
		return a.exec();
	}
	catch (SRMError & e){
		QMessageBox::critical(nullptr, QString::fromStdWString(L"���д���"), QString::fromStdWString(L"������:%1").arg(e.errorCode()), QMessageBox::Ok);
		return -1;
	}
}