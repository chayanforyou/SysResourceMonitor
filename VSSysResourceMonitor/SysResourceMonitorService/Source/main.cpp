/****************************************************************************
-i ��װ����
-u ж�ط���
-e ��Ϊ����exeִ��
-s ��������
-t ֹͣ����
-p ��ͣ����
-r �ָ���ͣ�ķ���
-c ��ָ���������뷢�͵�����
-v ��ʾ�汾��״̬��Ϣ
****************************************************************************/

#include <QCoreApplication>
#include "SysResourceMonitorService.h"

int main(int argc, char **argv)
{
	SysResourceMonitorService service(argc, argv);
    return service.exec();
}
