// Smart Album.h : Smart Album 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CSmartAlbumApp:
// 有关此类的实现，请参阅 Smart Album.cpp
//

class CSmartAlbumApp : public CWinApp
{
public:
	CSmartAlbumApp();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	DECLARE_MESSAGE_MAP()
};

extern CSmartAlbumApp theApp;