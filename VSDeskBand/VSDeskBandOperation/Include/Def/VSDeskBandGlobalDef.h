#ifndef VSDeskBandGlobalDef_H
#define VSDeskBandGlobalDef_H
/************************************************************************/
/* com�����������
   ���������Ҫ�õ���Щ����
*/
/************************************************************************/
#include "wtypes.h"

/************************************************************************/
/* COM ����Ķ��壬����ʶ��COM���                                                            */
/************************************************************************/
// 1. �������˵���ʾ���ƣ������޸�������壬���ı乤����ѡ�����ƣ�
static LPCWSTR lsVSDeskBandMenuName = L"VSDeskBand";
// 2. com�������ƣ�������ע���������������Ʋ鵽GUID/CLSID
static LPCWSTR lsVSDeskBandCOM_Name = L"VSDeskBand.VSDeskBandCOM";
// 3. CLSID �ַ���, ע��Ҫ�д�����
static LPCWSTR lsCLSID_VSDeskBandCOM_GUID = L"{86BB96B4-BB0D-414D-BA76-CE8A06BA7CB6}";
// 4. CLSID GUID����
static GUID CLSID_VSDeskBandCOM = { 0x86BB96B4, 0xBB0D, 0x414D,{ 0xBA, 0x76, 0xCE, 0x8A, 0x06, 0xBA, 0x7C, 0xB6 } };		


/************************************************************************/
/* Object�����壬������ʶCOM����ڲ��Ľӿڶ���
   ͨ����ЩGUID���� QueryInterface����Ӧ�Ľӿ�
   Ŀǰ���GUID���ǽ� VSDeskBandObject ����ֱ�ӷ��أ�
   �����Ҫ������������ӿڣ������Լ�����GUID��Ȼ���� VSDeskBandObject::QueryInterface�н��䷵�ؼ��ɡ�
*/
/************************************************************************/
// 1. VSDeskBandObject����
static LPCWSTR lsIVSDeskBandObject_GUID = L"{BD783BE6-299D-4D68-9DBA-654CD01B71E0}";
static GUID IID_VSDeskBandObject = { 0xBD783BE6, 0x299D, 0x4D68,{ 0x9D, 0xBA, 0x65, 0x4C, 0xD0, 0x1B, 0x71, 0xE0 } };

#endif //VSDeskBandGlobalDef_H
