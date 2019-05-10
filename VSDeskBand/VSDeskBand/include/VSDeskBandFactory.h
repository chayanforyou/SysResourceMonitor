#ifndef VSDeskBandFactory_H
#define VSDeskBandFactory_H
/************************************************************************/
/* COM���������
   ϵͳ����øù�������������Ӧ��object    
   ����com�������ʵ�ֵĽӿ�
   */
/************************************************************************/
#include <Unknwn.h>

class VSDeskBandFactory : public IClassFactory
{
public:
    VSDeskBandFactory();
    ~VSDeskBandFactory();

public:
    //IUnknown 
    STDMETHODIMP QueryInterface(const IID& riid, void** ppvObject);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    //IClassFactory
    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, const IID& riid, void **ppvObject);
    STDMETHODIMP LockServer(BOOL bLock);

private:
    ULONG m_lRef;
};

#endif //VSDeskBandFactory_H