
#include <QIcon>
#include "UI/SRMHelpDialog.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QString>


const QString c_sHelpText = QString::fromStdWString(L"\
���ڹ���ԱȨ��:\n\
  ����װ/���������ע�����Ҫ����ԱȨ��;\n\
  ��һ������ʱ, ���Զ���װ��������ߺͺ�̨����;\n\
  ���̲˵����ṩ����������ߺͺ�̨�������,�Ƴ����ǰ������ж����Ӧ���;\n\n\
�����Զ�����ɫ����:\n\
  �����Ӧ��ɫ��������ö�Ӧ�������ɫ;\n\
  ������ֵʱ,�������ֵ�������ǰ�����ֵ;");

SRMHelpDialog::SRMHelpDialog(QWidget* pParent /*=nullptr*/)
	: QDialog(pParent)
{
	initLayout();
	initProp();
}

SRMHelpDialog::~SRMHelpDialog()
{
}

void SRMHelpDialog::initLayout()
{
	QVBoxLayout* pMainLayout = new QVBoxLayout;
	QTextEdit* pTextEdit = new QTextEdit(this);
	pTextEdit->setReadOnly(true);
	pTextEdit->setText(c_sHelpText);

	pMainLayout->addWidget(pTextEdit);
	this->setLayout(pMainLayout);
}

void SRMHelpDialog::initProp()
{
	this->setFixedSize(550, 300);
	this->setWindowTitle(QString::fromStdWString(L"SRMResourceMonitor ����"));
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	this->setAttribute(Qt::WA_DeleteOnClose, false);
	this->setAttribute(Qt::WA_QuitOnClose, false);
	this->setWindowIcon(QIcon(":/Images/SysResourceMonitor.png"));
}

