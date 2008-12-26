#pragma once

/********************************************************************
created:	2005/06/21
created:	21:6:2005   21:53
filename: 	imagetest\bmp.h
file path:	imagetest
file base:	bmp
file ext:	h
author:		Gengxun

purpose:	读写BMP
//  [6/22/2005]　添加显示功能

*********************************************************************/
#ifndef _BMP_H__
#define _BMP_H__

//添加VFW组件
#include  <vfw.h>
//BMP文件头标志
#define BMP_HEADER_MARKER	((WORD) ('M' << 8) | 'B') 

class CBmp : public CObject
{
public:
	DECLARE_SERIAL(CBmp)

	//Construction and Destruction
	CBmp();
	~CBmp();

	//Operations
	BOOL Read(CFile *pFile);
	BOOL Write(CFile *pFile);
	void Serialize(CArchive &ar);	

	void Draw(CDC *pDC, CPoint ptOrigin, CSize szImage);	
	//在内存中画图
	void DrawOnMemory(CDC *pDC, CPoint ptOrigin, CSize szImage);  	
	//使用VFW组件画图
	void DrawUseVFW(HDRAWDIB hDrawDib, CDC *pDC, CPoint ptOrigin, CSize szImage);

private:
	BOOL MakePalette();						//创建调色板

public:
	//Attributes
	int GetHeight() const;
	int GetWidth() const;
	int GetBitCount() const;				//Bpp
	int GetPaletteSize() const;				//调色板大小
	DWORD GetImageSize() const;				//图像大小
	LPVOID GetColorTable() const;			//颜色表
	LPBITMAPINFOHEADER GetBMIH() const;		//位图信息头
	LPBYTE GetBits() const;					//返回图像数据
	int GetWidthMemory();					//内存宽度，4的倍数


	//Data
private:
	LPBITMAPINFOHEADER  m_pBMIH;			//位图信息头
	LPBYTE				m_pBits;			//位图数据

	HPALETTE            m_hPalette;			//调色板句柄	
};

#endif
