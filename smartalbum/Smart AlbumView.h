// Smart AlbumView.h : CSmartAlbumView ��Ľӿ�
//


#pragma once


class CSmartAlbumView : public CView
{
protected: // �������л�����
	CSmartAlbumView();
	DECLARE_DYNCREATE(CSmartAlbumView)

// ����
public:
	CSmartAlbumDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSmartAlbumView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Smart AlbumView.cpp �еĵ��԰汾
inline CSmartAlbumDoc* CSmartAlbumView::GetDocument() const
   { return reinterpret_cast<CSmartAlbumDoc*>(m_pDocument); }
#endif

