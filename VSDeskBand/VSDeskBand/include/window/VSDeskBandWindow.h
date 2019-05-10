#ifndef VSDeskBandWindow_H
#define VSDeskBandWindow_H

/************************************************************************/
/* DeskBand�Ĵ��ڣ�����ʾ����������
  �������ʾ�Լ��Ĵ�����ʽ���޸�����༴��
*/
/************************************************************************/
#include "window/IVSDeskBandWindowInf.h"
#include "Def/VSSharedMemStructDef.h"
#include <Uxtheme.h>
#include <string>
#include <list>

const int c_sMaxTextLength = 1024; // ������Ϣ�п��ַ� �ֽڳ�������

class VSDeskBandWindow : public IVSDeskBandWindowInf
{
    friend LRESULT CALLBACK deskBandWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    VSDeskBandWindow();
    virtual ~VSDeskBandWindow();

public:
    virtual BOOL createNewDeskBandWindow(HWND hParent, HINSTANCE dllInstance);

    virtual BOOL showDeskBandWindow(BOOL bShow = TRUE);

    virtual BOOL closeDeskBandWindow();

    virtual HWND getDeskBandWindowHandle();

    virtual SIZE getDeskBandWindowMinSize(BOOL bNormalViewMode = TRUE);

    virtual void updateDeskBandWindow();

private:
    void setErrorText();
    void readSharedMemData();
    LRESULT OnPaint();
    int paintOneCol(/*HTHEME hTheme, */HDC hCacheDC, int nLeft, int nTop, int nCol);
    HFONT& borrowFontInfo(int nTextHeight);

private:
	int calcTextHeight();
	int calcColWidth(HDC hCacheDC, int nCol);

private:
    static const UINT m_nTimer = 100;		// ��ʱ����ţ����ȡ�˸�100
    HWND m_hDeskBandWindow;
	HINSTANCE m_dllInstance;

private: // �����ڴ����
    VSSharedMemStruct m_oSharedMemStruct;	// �����ڴ�������
    HANDLE m_hFile;							// ���������
    HANDLE m_hReadMutexSemaphore;			// ȫ�ֻ�����
    void *m_pBuffer;						// ������ָ��
	std::list<std::pair<int, HFONT>> m_oFontList; // ���������ָ��
};

#endif //VSDeskBandWindow_H