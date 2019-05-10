#ifndef IVSDESKBANDOPERATION_H_74B0AB51_EA37_4C79_B336_1EDE7DF1744E
#define IVSDESKBANDOPERATION_H_74B0AB51_EA37_4C79_B336_1EDE7DF1744E

class VSSharedMemStruct;

class IVSDeskBandOperation
{
public:
	//************************************
	// Mark:       �Ƿ�ע���
	//			DeskBand��Ҫע��󣬲ſ��Գ����ڹ�����ѡ����
	// FullName:  IVSDeskBandOperation::registered
	// Access:    virtual public 
	// Returns:   bool
	// Qualifier:
	//************************************
	virtual bool isRegistered() = 0;

	//************************************
	// Mark:      ע�ᣨ��DeskBand��Ϣд��ע���
	// FullName:  IVSDeskBandOperation::reg
	// Access:    virtual public 
	// Returns:   bool
	// Qualifier:
	//************************************
	virtual bool doReg() = 0;

	//************************************
	// Mark:      ��ע��(��ע������Ƴ�DeskBand)
	// FullName:  IVSDeskBandOperation::unreg
	// Access:    virtual public 
	// Returns:   bool
	// Qualifier:
	//************************************
	virtual bool doUnreg() = 0;

	//************************************
	// Mark:      �Ƿ�ɼ�
	// FullName:  IVSDeskBandOperation::visible
	// Access:    virtual public 
	// Returns:   bool
	// Qualifier:
	//************************************
	virtual bool visible() = 0;
	//************************************
	// Mark:      ��ʾ
	// FullName:  IVSDeskBandOperation::show
	// Access:    virtual public 
	// Returns:   bool
	// Parameter: bool bAutoClick	�Զ����ȷ����ť������ʱ���ʹ��hook������Դ�������Ϲ�hook��
	//************************************
	virtual bool show(bool bAutoClick) = 0;

	//************************************
	// Mark:      ����
	// FullName:  IVSDeskBandOperation::hide
	// Access:    virtual public 
	// Returns:   bool
	// Qualifier:
	//************************************
	virtual bool hide() = 0;

	//************************************
	// Mark:      ������ʾ����
	// FullName:  IVSDeskBandOperation::updateMessage
	// Access:    virtual public 
	// Returns:   bool
	// Parameter: VSSharedMemStruct * pMessageArray
	//************************************
	virtual bool updateMessage(VSSharedMemStruct *pMessageArray) = 0;
};

#endif //IVSDESKBANDOPERATION_H_74B0AB51_EA37_4C79_B336_1EDE7DF1744E