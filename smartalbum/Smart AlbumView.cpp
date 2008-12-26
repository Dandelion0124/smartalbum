// Smart AlbumView.cpp : CSmartAlbumView ���ʵ��
//

#include "stdafx.h"
#include "Smart Album.h"
#include "Bmp.h"

#include "Smart AlbumDoc.h"
#include "Smart AlbumView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSmartAlbumView

IMPLEMENT_DYNCREATE(CSmartAlbumView, CView)

BEGIN_MESSAGE_MAP(CSmartAlbumView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSmartAlbumView ����/����

CSmartAlbumView::CSmartAlbumView()
{
	// TODO: �ڴ˴���ӹ������

}

CSmartAlbumView::~CSmartAlbumView()
{
}

BOOL CSmartAlbumView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSmartAlbumView ����

void CSmartAlbumView::OnDraw(CDC* pDC)
{
	CSmartAlbumDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//���BMPָ��
	CBmp *pBmp = pDoc->GetImage();

	if(pBmp->GetBMIH() != NULL)
	{			
		CSize szDisplay;
		szDisplay.cx = pBmp->GetWidth();
		szDisplay.cy = pBmp->GetHeight();

		// ��ʾ��ʽ3��ʹ��VFW���������ʾ		
		//pBmp->DrawUseVFW(m_hDrawDib, pDC,CPoint(0,0),szDisplay);

		// ��ʾ��ʽ1��һ����ʾ��ʽ
		pBmp->Draw(pDC,CPoint(0,0),szDisplay);	

		// ��ʾ��ʽ2��ʹ��λͼDC������ʾ
		//pBmp->DrawOnMemory(pDC,CPoint(0,0),szDisplay);
	}

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSmartAlbumView ��ӡ

BOOL CSmartAlbumView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSmartAlbumView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSmartAlbumView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CSmartAlbumView ���

#ifdef _DEBUG
void CSmartAlbumView::AssertValid() const
{
	CView::AssertValid();
}

void CSmartAlbumView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSmartAlbumDoc* CSmartAlbumView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSmartAlbumDoc)));
	return (CSmartAlbumDoc*)m_pDocument;
}
#endif //_DEBUG


// CSmartAlbumView ��Ϣ�������
