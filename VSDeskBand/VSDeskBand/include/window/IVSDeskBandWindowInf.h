
#ifndef IVSDeskBandWindowInf_H
#define IVSDeskBandWindowInf_H

/************************************************************************/
/* DeskBand���ڽӿ�
   DeskBand������Ҫ���½ӿ�
/************************************************************************/
#include <Unknwn.h>
#include <Strsafe.h>

// ������Ϣ���
static LPCTSTR lsVSDeskBandWindowClassName = L"VSDeskBandWindowClass";        // ����������win��ÿ��������Ҫ���Լ��Ĵ�����
static LPCTSTR lsVSDeskBandWindowName = L"VSDeskBandWindow";                  // �������ƣ�DeskBand���ڵ�����                      
static const int c_nUpdateText = 1;      // ������ʾ����

class IVSDeskBandWindowInf
{
public:
    virtual ~IVSDeskBandWindowInf() {};

    virtual BOOL createNewDeskBandWindow(HWND hParent, HINSTANCE dllInstance) = 0;

    virtual BOOL showDeskBandWindow(BOOL bShow = TRUE) = 0;

    virtual BOOL closeDeskBandWindow() = 0;

    virtual HWND getDeskBandWindowHandle() = 0;

    virtual SIZE getDeskBandWindowMinSize(BOOL bNormalViewMode = TRUE) = 0;

    virtual void updateDeskBandWindow() = 0;
};

#endif //IVSDeskBandWindowInf_H