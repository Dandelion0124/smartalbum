// Smart AlbumDoc.h : CSmartAlbumDoc ��Ľӿ�
//


#pragma once

class CBmp;
class CSmartAlbumDoc : public CDocument
{
protected: // �������л�����
	CSmartAlbumDoc();
	DECLARE_DYNCREATE(CSmartAlbumDoc)

// ����
public:

// ����
public:
	CBmp* GetImage();								//��ȡͼ��ָ��

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CSmartAlbumDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
private:
	CBmp * m_pBmp;				//ͼ��ָ��
};


