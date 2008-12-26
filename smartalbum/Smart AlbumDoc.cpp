// Smart AlbumDoc.cpp : CSmartAlbumDoc ���ʵ��
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


// CSmartAlbumDoc ����/����

CSmartAlbumDoc::CSmartAlbumDoc()
{
	// TODO: �ڴ����һ���Թ������
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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CSmartAlbumDoc ���л�

void CSmartAlbumDoc::Serialize(CArchive& ar)
{
	m_pBmp->Serialize(ar);

}

CBmp * CSmartAlbumDoc::GetImage()
{
	return m_pBmp;
}

// CSmartAlbumDoc ���

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


// CSmartAlbumDoc ����
