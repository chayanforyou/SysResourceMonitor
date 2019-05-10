#ifndef SRMCUSTOMMENU_H_CE008758_029F_4834_A605_C3430BD404DC
#define SRMCUSTOMMENU_H_CE008758_029F_4834_A605_C3430BD404DC
/************************************************************************/
/*��дQMenu
  �Խ��Qt�����̲˵������Զ���ʧ������                                                                     */
/************************************************************************/
#include <QMenu>
#include <windows.h>

class VSCustomMenu : public QMenu
{
public:
	VSCustomMenu(QWidget* p) :QMenu(p) 
	{

	}
	~VSCustomMenu() 
	{

	}

private:
	virtual void paintEvent(QPaintEvent* e) override 
	{
		SetForegroundWindow(HWND(this->winId()));
		QMenu::paintEvent(e);
	}
};

#endif //SRMCUSTOMMENU_H_CE008758_029F_4834_A605_C3430BD404DC
