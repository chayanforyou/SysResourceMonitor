#ifndef SharedMemStructDef_h
#define SharedMemStructDef_h
/************************************************************************/
/*
	�����ڴ����
	������DeskBand����������ͨѶ�õĹ����ڴ��ʽ
*/
/************************************************************************/
#include "wtypes.h"
#include <string>
#include <vector>

#define DOUBLE_LENGTH(a) ((a)*2)

// 1. �����ڴ��С
static const int c_nSharedMemSize = 1024; // 1K
// 2. �����ڴ�����
static LPCWSTR c_lsSRMShareMemoryName = L"SRMSharedMemory";
// 3. �����ڴ���ʻ���������
static LPCWSTR c_lsSRMMutexSemaphoreName = L"SRMMutexSemaphore";

using std::wstring;
using std::vector;

class VSShareMemTextNode
{
public:
	VSShareMemTextNode(int nR, int nG, int nB, wstring sInfo) 
		: m_nRed(nR), m_nGreen(nG), m_nBlue(nB), m_sInfo(sInfo) {};
	VSShareMemTextNode() 
		: m_nRed(255), m_nGreen(255), m_nBlue(255), m_sInfo(L"") {};
	~VSShareMemTextNode() {};

	int byteSize(){
		return DOUBLE_LENGTH(int(m_sInfo.length()) + 1) + sizeof(int) * 3;
	};

	void writeToStream(void *pBuff){        
		*((int*)pBuff) = m_nRed;
		pBuff = (int*)pBuff + 1;

		*((int*)pBuff) = m_nGreen;
		pBuff = (int*)pBuff + 1;

		*((int*)pBuff) = m_nBlue;
		pBuff = (int*)pBuff + 1;	

		lstrcpy((WCHAR*)pBuff, m_sInfo.c_str());
	};

	void readFromStream(void *pBuff){
		m_nRed = *((int*)pBuff);
		pBuff = (int*)pBuff + 1;

		m_nGreen = *((int*)pBuff);
		pBuff = (int*)pBuff + 1;

		m_nBlue = *((int*)pBuff);
		pBuff = (int*)pBuff + 1;

		m_sInfo = std::wstring((WCHAR*)pBuff);
	};

public:
	int m_nRed;			    // ɫֵ��R
	int m_nGreen;			// ɫֵ��G
	int m_nBlue;			// ɫֵ��B
	wstring m_sInfo;		// ����
};

#define MAX_SIZE_ROW 2	// �������2��
#define MAX_SIZE_COL 40 // �������40��
class VSSharedMemStruct
{
public:
    VSSharedMemStruct() 
		: m_oUnVaildTextNode(255, 0, 0, L"Cross-border access")
	{ 
		m_oTextNodeVector.resize(MAX_SIZE_ROW);
		for (int i = 0; i < MAX_SIZE_ROW; ++i){
			m_oTextNodeVector[i].resize(MAX_SIZE_COL);
		}
		this->reset(); 
	};
	~VSSharedMemStruct() {};
    void reset(){
		m_nMessageID = 0;
		m_nRowCount = 1;
		m_nColCount = 1;
		m_nLeftSpace = 1;
		m_nRightSpace = 1;
		m_nColSpace = 2;
    };

	void setTextNode(int nRow, int nCol, VSShareMemTextNode& oNodeInfo){
		if (nRow < MAX_SIZE_ROW && nCol < MAX_SIZE_COL)
			m_oTextNodeVector[nRow][nCol] = oNodeInfo;	
	}

	VSShareMemTextNode& getTextNode(int nRow, int nCol)	{
		if (nRow < MAX_SIZE_ROW && nCol < MAX_SIZE_COL)
			return m_oTextNodeVector[nRow][nCol];
		else
			return m_oUnVaildTextNode;
	}

	// ���ؽṹ��ռ�õ��ֽ�����ע�⣬�ṹ�������TextNode���ֽ�����䳤������Ҫ��֤�ṹ�����ݲ��ٱ仯ʱ����ȡsize
	int byteSize(){
		int nByteSize = sizeof(int) * 6;
		size_t nRowCount = getRowCount();
		size_t nColCount = getColCount();
		for (int i = 0; i < nRowCount; ++i){
			for (int j = 0; j < nColCount; ++j)
				nByteSize += m_oTextNodeVector[i][j].byteSize();
		}
		return nByteSize;
	};

	void readFromStream(void *pBuff){
        m_nMessageID = *((int*)(pBuff));
        pBuff = (int*)(pBuff)+1;

		m_nLeftSpace = *((int*)pBuff);
		pBuff = (int*)pBuff + 1;

		m_nRightSpace = *((int*)pBuff);
		pBuff = (int*)pBuff + 1;

		m_nColSpace = *((int*)pBuff);
		pBuff = (int*)pBuff + 1;

		int nRowCount = *((int*)(pBuff));
		pBuff = (int*)(pBuff)+1;
		setRowCount(nRowCount);// ���õ�ʱ�򣬱��������ú���������Խ��

		int nColCount = *((int*)(pBuff));
		pBuff = (int*)(pBuff)+1;
		setColCount(nColCount);// ���õ�ʱ�򣬱��������ú���������Խ��

		for (int i = 0; i < m_nRowCount; ++i){
			for (int j = 0; j < m_nColCount; ++j){
				VSShareMemTextNode oTextNode;
				oTextNode.readFromStream(pBuff);
				pBuff = (char*)pBuff + oTextNode.byteSize();
				m_oTextNodeVector[i][j] = oTextNode;
			}
		}
	};

	void writeToStream(void *pBuff){
        *((int*)pBuff) = m_nMessageID;
        pBuff = (int*)(pBuff) + 1;

		*((int*)pBuff) = m_nLeftSpace;
		pBuff = (int*)pBuff + 1;

		*((int*)pBuff) = m_nRightSpace;
		pBuff = (int*)pBuff + 1;

		*((int*)pBuff) = m_nColSpace;
		pBuff = (int*)pBuff + 1;	

		size_t nRowCount = m_nRowCount;
		*((int*)pBuff) = int(nRowCount);
		pBuff = (int*)(pBuff)+1;

		size_t nColCount = m_nColCount;
		*((int*)pBuff) = int(nColCount);
		pBuff = (int*)(pBuff)+1;

		for (int i = 0; i < nRowCount; ++i){
			for (int j = 0; j < nColCount; ++j){
				m_oTextNodeVector[i][j].writeToStream(pBuff);
				pBuff = (char*)pBuff + m_oTextNodeVector[i][j].byteSize();
			}
		}
	};

	void setRowCount(int nRowCount) {
		if (nRowCount > MAX_SIZE_ROW)
			nRowCount = MAX_SIZE_ROW;

		m_nRowCount = nRowCount;
	}

	void setColCount(int nColCount) {
		if (nColCount > MAX_SIZE_COL)
			nColCount = MAX_SIZE_COL;

		m_nColCount = nColCount;
	}
	void setMessageID(int n){m_nMessageID = n;};
	void setLeftSpace(int n){m_nLeftSpace = n;};
	void setRightSpace(int n){m_nRightSpace = n;};
	void setColSpace(int n){m_nColSpace = n;};
	int getRowCount() { return m_nRowCount; }
	int getColCount() { return m_nColCount; }
	int getMessageID() {return m_nMessageID;};
	int getLeftSpace() {return m_nLeftSpace;};
	int getRightSpace() {return m_nRightSpace;};
	int getColSpace() {return m_nColSpace;};

private:
    int m_nMessageID;		// ��ϢID��ֻҪ���ϴβ�һ������
	int m_nLeftSpace;		// �����׾��룬����
	int m_nRightSpace;		// �����׾��룬����
	int m_nColSpace;		// �м�࣬���������ң�����
	int m_nRowCount;		// 
	int m_nColCount;		// 
	vector<vector<VSShareMemTextNode>> m_oTextNodeVector;
	VSShareMemTextNode m_oUnVaildTextNode;
};

#endif // SharedMemStructDef_h