// Smart Album.h : Smart Album Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CSmartAlbumApp:
// �йش����ʵ�֣������ Smart Album.cpp
//

class CSmartAlbumApp : public CWinApp
{
public:
	CSmartAlbumApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	DECLARE_MESSAGE_MAP()
};

extern CSmartAlbumApp theApp;