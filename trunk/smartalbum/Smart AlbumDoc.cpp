// Smart AlbumDoc.cpp : CSmartAlbumDoc 类的实现
//

#include "stdafx.h"
#include "Smart Album.h"
#include "Bmp.h"

#include "Smart AlbumDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSmartAlbumDoc

IMPLEMENT_DYNCREATE(CSmartAlbumDoc, CDocument)

BEGIN_MESSAGE_MAP(CSmartAlbumDoc, CDocument)
END_MESSAGE_MAP()


// CSmartAlbumDoc 构造/析构

CSmartAlbumDoc::CSmartAlbumDoc()
{
	// TODO: 在此添加一次性构造代码
	m_pBmp = new CBmp;


}

CSmartAlbumDoc::~CSmartAlbumDoc()
{
	if(m_pBmp != NULL){
		delete m_pBmp;
		m_pBmp = NULL;
	}
}

BOOL CSmartAlbumDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CSmartAlbumDoc 序列化

void CSmartAlbumDoc::Serialize(CArchive& ar)
{
	m_pBmp->Serialize(ar);

}

CBmp * CSmartAlbumDoc::GetImage()
{
	return m_pBmp;
}

// CSmartAlbumDoc 诊断

#ifdef _DEBUG
void CSmartAlbumDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSmartAlbumDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSmartAlbumDoc 命令
