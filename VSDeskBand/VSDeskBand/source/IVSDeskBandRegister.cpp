#include <ShObjIdl.h>
#include <ComCat.h>
#include <ShlGuid.h>
#include <strsafe.h>
#include "Def/VSDeskBandGlobalDef.h"
#include "VSDeskBandFactory.h"

HINSTANCE g_hDeskBandGlobalInstanceModule = nullptr;    // dll���� 
ULONG g_l_DllInstanceRef = 0;                           // dllȫ�����ã�Ϊ0ʱdll�ᱻϵͳ�ͷ�

// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    g_hDeskBandGlobalInstanceModule = hModule;
    UNREFERENCED_PARAMETER(lpReserved);
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

HRESULT myRegisterServer();
HRESULT myUnRegisterServer();
HRESULT myCanUnloadNow();
HRESULT myGetClassObject(__in REFCLSID rclsid, __in REFIID riid, LPVOID FAR* ppv);
void updatepTrayDeskBandMenu();

// ע�ᣬ����COM�����UUID���ļ�·��д��ע�����
STDAPI DllRegisterServer() 
{
    if (myRegisterServer() != S_OK)
    {
        MessageBox(nullptr, L"ע�����д����", L"Error", S_OK);
        return S_FALSE;
    }

    // ע��band����
    ICatRegister  *pcr;
    HRESULT        hr = S_OK;
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (LPVOID*)&pcr);
    if (SUCCEEDED(hr))
    {
        CATID catid[] = { CATID_DeskBand };
        hr = pcr->RegisterClassImplCategories(CLSID_VSDeskBandCOM, 1, catid);
        pcr->Release();
    }

    // Ҫ��ˢ�²˵�
    updatepTrayDeskBandMenu();

    return S_OK;
}

// ��ע��
STDAPI DllUnregisterServer()
{
    if (myUnRegisterServer() != S_OK)
    {
        return S_FALSE;
    }

    // Ҫ��ˢ�²˵�
    updatepTrayDeskBandMenu();
    return S_OK;
}

//���ڴ����೧����������ӿڣ���CoGetClassObject��������  
STDAPI DllGetClassObject(__in REFCLSID rclsid, __in REFIID riid, LPVOID FAR* ppv)
{
    return myGetClassObject(rclsid, riid, ppv);
}

//�����ж��Ƿ����ж�ر����, ��CoFreeUnusedLibraries�������ã�һ�㱻ϵͳ����
STDAPI DllCanUnloadNow()
{
    return myCanUnloadNow();
}


// ���嶨��
HRESULT myRegisterServer()
{
    // ��Ϊ���� 

	// 1. �õ�dll�ļ�·��
    WCHAR lsFullFilePath[MAX_PATH] = { 0 };
    DWORD dwResult = GetModuleFileName(g_hDeskBandGlobalInstanceModule, lsFullFilePath, MAX_PATH); //��ȡ�����(dll)����·��
    if (0 == dwResult)
    {
        MessageBox(NULL, L"�޷���ȡ��ǰdll����Ŀ¼", L"ע��ʧ��", MB_OK);
        return S_FALSE;
    }

	// 2. ��CLSID + ·��д��ע�������
    HKEY regkeyCLSID, regkeyDeskBandCOM_GUID, regkeyInProcServer32;
    // �򿪼�ע��� HKEY_CLASSES_ROOT\CLSID,  
    if (ERROR_SUCCESS == RegOpenKey(HKEY_CLASSES_ROOT, L"CLSID", &regkeyCLSID))
    {
        // �¼�: VSCom��CLSID
        if (ERROR_SUCCESS == RegCreateKey(regkeyCLSID, lsCLSID_VSDeskBandCOM_GUID, &regkeyDeskBandCOM_GUID))
        {
            RegSetValue(regkeyDeskBandCOM_GUID, NULL, REG_SZ, lsVSDeskBandMenuName, DWORD(wcslen(lsVSDeskBandMenuName) * 2));
            // �½�: InProcServer32
            if (ERROR_SUCCESS == RegCreateKey(regkeyDeskBandCOM_GUID, L"InProcServer32", &regkeyInProcServer32))
            {
                // ��dll�ļ�·��дΪ�ü���Ĭ��ֵ  
                RegSetValue(regkeyInProcServer32, NULL, REG_SZ, lsFullFilePath, DWORD(wcslen(lsFullFilePath) * 2));
                // RegSetValueֻ�ܸ�Ĭ��ֵ��������RegSetValueEx
                WCHAR const szModel[] = L"Apartment";
                RegSetValueEx(regkeyInProcServer32, L"ThreadingModel", 0, REG_SZ, LPBYTE(szModel), sizeof(szModel));
                RegCloseKey(regkeyInProcServer32);
            }
            RegCloseKey(regkeyDeskBandCOM_GUID);
        }
        RegCloseKey(regkeyCLSID);
    }

	// 3. ��ObjectName + CLSID����ѡ��ע���ȥ
    HKEY regkeyMyComObject, regkeyMyComObjectCLISID;
    //��HKEY_CLASSES_ROOT �´��� CLSID
    if (ERROR_SUCCESS == RegCreateKey(HKEY_CLASSES_ROOT, lsVSDeskBandCOM_Name, &regkeyMyComObject))
    {
        RegSetValue(regkeyMyComObject, NULL, REG_SZ, lsVSDeskBandCOM_Name, DWORD(wcslen(lsVSDeskBandCOM_Name) * 2));
        // �����Ӽ� CLSID
        if (ERROR_SUCCESS == RegCreateKey(regkeyMyComObject, L"CLSID", &regkeyMyComObjectCLISID))
        {
            // ��MyCom��CLSIDдΪ�ü���Ĭ��ֵ  
            RegSetValue(regkeyMyComObjectCLISID, NULL, REG_SZ, lsCLSID_VSDeskBandCOM_GUID, DWORD(wcslen(lsCLSID_VSDeskBandCOM_GUID) * 2));
            RegCloseKey(regkeyMyComObjectCLISID);
        }
        RegCloseKey(regkeyMyComObject);
    }

    //�����Ļ�һ���ͻ��˳��������Ҫʹ�ñ���������ȿ�����MyCom.ICustomInfΪ��������CLSIDFromProgID����  
    //����ȡMyCom.ICustomInf��CLSID���������CLSIDΪ��������CoCreateInstance����COM����  
    // MessageBox(NULL, lsFullFilePath, L"ע��ɹ����ѽ�����·��д��ע���", MB_OK);
    return S_OK;
}

HRESULT myUnRegisterServer()
{
	// �ȹر���������ʾ
	ITrayDeskBand* pTrayDeskBand = NULL;
	HRESULT hr = CoCreateInstance(CLSID_TrayDeskBand, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pTrayDeskBand));
	// Vista and higher operating system
	if (SUCCEEDED(hr))
	{
		int nRetryTimes = 5;
		do
		{
			hr = pTrayDeskBand->HideDeskBand(CLSID_VSDeskBandCOM);
		} while (--nRetryTimes && !SUCCEEDED(hr));

		if (pTrayDeskBand)
			pTrayDeskBand->Release();
	}	

    // Ȼ��Ҫ���ͷ�dll
    // Find handle to the task bar.
    HWND hTaskbarWnd = FindWindow(L"Shell_TrayWnd", NULL);
    // If task bar receives this message, it will call CoFreeUnusedLibraries function
    // immediately to free unused libraries.
    PostMessage(hTaskbarWnd, WM_TIMER, 24, 0);


    // �������ע�����Ϣ
	// 1. ����CLSID + �ļ�·��
    HKEY regkeyCLSID;
    if (ERROR_SUCCESS == RegOpenKey(HKEY_CLASSES_ROOT, L"CLSID", &regkeyCLSID))
    {
        // RegDeleteKey����ɾ����������Ľڵ� ����ɾ���Ķ����Ƚ϶ࡣֱ��ʹ��RegDeleteTree, С��ʹ�ã����ע���ȫɾ��     
        RegDeleteTree(regkeyCLSID, lsCLSID_VSDeskBandCOM_GUID);

        // ɾ��VSDeskBandCOM_CLSID
        //deleteKey(regkeyCLSID, lsCLSID_VSDeskBandCOM_GUID);
        RegCloseKey(regkeyCLSID);
    }

	// 2. ����ObjectName + CLSID
    RegDeleteTree(HKEY_CLASSES_ROOT, lsVSDeskBandCOM_Name);  

    return S_OK;
}

void updatepTrayDeskBandMenu()
{
    // ���´��������Toolbars�Ӳ˵�����������������ע���Band����˵���
    ITrayDeskBand *pTrayDeskBand = NULL;
    HRESULT hr = ::CoCreateInstance(CLSID_TrayDeskBand, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pTrayDeskBand));
    if (SUCCEEDED(hr))
    {
        pTrayDeskBand->DeskBandRegistrationChanged();
        pTrayDeskBand->Release();
    }        

    if (FAILED(hr))
    {
        MessageBox(nullptr, L"������ʾDeskBandʧ��", L"Error", S_OK);
    }
}

HRESULT myGetClassObject(__in REFCLSID rclsid, __in REFIID riid, LPVOID FAR* ppv)
{
    if (CLSID_VSDeskBandCOM == rclsid)
    {
        VSDeskBandFactory* pFactory = new VSDeskBandFactory();//�����೧����
        if (NULL == pFactory)
        {
            return E_OUTOFMEMORY;
        }

        HRESULT oResult = pFactory->QueryInterface(riid, ppv);
        pFactory->Release();

        return oResult; //��ȡ����ӿ�
    }
    else
    {
        return CLASS_E_CLASSNOTAVAILABLE;
    }
}

HRESULT myCanUnloadNow()
{
    //����������Ϊ0�������ж��
    if (0 == g_l_DllInstanceRef)
    {
        return S_OK;
    }
    else
    {
        return S_FALSE;
    }
}
