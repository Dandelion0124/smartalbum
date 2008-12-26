// Smart AlbumView.cpp : CSmartAlbumView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSmartAlbumView 构造/析构

CSmartAlbumView::CSmartAlbumView()
{
	// TODO: 在此处添加构造代码

}

CSmartAlbumView::~CSmartAlbumView()
{
}

BOOL CSmartAlbumView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSmartAlbumView 绘制

void CSmartAlbumView::OnDraw(CDC* pDC)
{
	CSmartAlbumDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//获得BMP指针
	CBmp *pBmp = pDoc->GetImage();

	if(pBmp->GetBMIH() != NULL)
	{			
		CSize szDisplay;
		szDisplay.cx = pBmp->GetWidth();
		szDisplay.cy = pBmp->GetHeight();

		// 显示方式3　使用VFW组件进行显示		
		//pBmp->DrawUseVFW(m_hDrawDib, pDC,CPoint(0,0),szDisplay);

		// 显示方式1　一般显示方式
		pBmp->Draw(pDC,CPoint(0,0),szDisplay);	

		// 显示方式2　使用位图DC进行显示
		//pBmp->DrawOnMemory(pDC,CPoint(0,0),szDisplay);
	}

	// TODO: 在此处为本机数据添加绘制代码
}


// CSmartAlbumView 打印

BOOL CSmartAlbumView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSmartAlbumView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSmartAlbumView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CSmartAlbumView 诊断

#ifdef _DEBUG
void CSmartAlbumView::AssertValid() const
{
	CView::AssertValid();
}

void CSmartAlbumView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSmartAlbumDoc* CSmartAlbumView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSmartAlbumDoc)));
	return (CSmartAlbumDoc*)m_pDocument;
}
#endif //_DEBUG


// CSmartAlbumView 消息处理程序
