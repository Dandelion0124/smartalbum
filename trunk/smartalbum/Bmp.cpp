#include "StdAfx.h"
#include "Bmp.h"

/********************************************************************

purpose:	读写BMP

*********************************************************************/


// 声明串行化过程
IMPLEMENT_SERIAL(CBmp, CObject, 0);

CBmp::CBmp(void) 
{
	m_pBMIH = NULL;
	m_pBits = NULL;

	m_hPalette = NULL;
}

CBmp::~CBmp(void)
{
	if (m_pBMIH != NULL)
	{
		delete m_pBMIH;
		m_pBMIH = NULL;
	}

	if(m_pBits != NULL)
	{
		m_pBits = NULL;
	}

	if(m_hPalette != NULL)
	{
		::DeleteObject(m_hPalette);
	}
}

/*************************************************
Function:       Read
Description:    读取BMP图像
Input:          CFile *pFile
Output:         
Return:         BOOL  成功返回TRUE，否则返回FALSE
Others:         读取文件头、信息头、调色板和图像数据 
*************************************************/
BOOL CBmp::Read(CFile *pFile)
{
	// 进行读操作
	try 
	{
		BITMAPFILEHEADER bmfh;

		// 步骤1　读取文件头
		int nCount = pFile->Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

		// 判断是否是BMP格式的位图
		if(bmfh.bfType != BMP_HEADER_MARKER) 
		{
			//throw new CException;
		}

		// 计算信息头加上调色板的大小并分内存
		int nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		m_pBMIH = (LPBITMAPINFOHEADER) new BYTE[nSize];

		// 步骤2　读取信息头和调色板
		nCount = pFile->Read(m_pBMIH, nSize); 

		// 步骤3　读取图象数据
		m_pBits = (LPBYTE) new BYTE[m_pBMIH->biSizeImage];
		nCount = pFile->Read(m_pBits, m_pBMIH->biSizeImage); 
	}

	catch(CException* pe) 
	{
//		AfxMessageBox("read error",MB_OK,0);
		pe->Delete();
		return FALSE;
	}

	//创建调色板
	MakePalette();

	return TRUE;
}

/*************************************************
Function:       Write
Description:    写入BMP图像
Input:          CFile *pFile
Output:         
Return:         BOOL  成功返回TRUE，否则返回FALSE
Others:         BMP格式的图像以“BM”为开始标志
*************************************************/
BOOL CBmp::Write(CFile *pFile)
{
	BITMAPFILEHEADER bmfh;

	// 设置文件头中文件类型 0x424D="BM"
	bmfh.bfType = BMP_HEADER_MARKER;  

	// 计算信息头和调色板大小
	int nSizeHeader = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetPaletteSize();

	// 设置文件头信息
	bmfh.bfSize      = sizeof(BITMAPFILEHEADER) + nSizeHeader + GetImageSize();
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;

	//计算偏移量　文件头大小+信息头大小+调色板大小
	bmfh.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) 
		+ sizeof(RGBQUAD) * GetPaletteSize();	

	// 进行写操作
	try 
	{
		pFile->Write((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));
		pFile->Write((LPVOID) m_pBMIH,  nSizeHeader);
		pFile->Write((LPVOID) m_pBits, GetImageSize());
	}	

	catch(CException* pe)
	{
		pe->Delete();
//		AfxMessageBox("write error",MB_OK,0);
		return FALSE;
	}

	return TRUE;
}


//计算调色板的大小
int CBmp::GetPaletteSize() const
{
	int ret = 0;

	if(m_pBMIH->biClrUsed == 0) 	// 调色板的大小为2的biBitCount次方		
	{
		switch(m_pBMIH->biBitCount)
		{
		case 1:
			ret = 2;
			break;
		case 4:
			ret = 16;
			break;
		case 8:
			ret = 256;
			break;
		case 16:
		case 24:
		case 32:
			ret = 0;
			break;
		default:
			ret = 0;
		}
	}	
	else // 调色板的大小为实际用到的颜色数
	{
		ret = m_pBMIH->biClrUsed;
	}

	return ret;
}

//串行化
void CBmp::Serialize(CArchive &ar)
{

	if(ar.IsStoring()) 
	{
		Write(ar.GetFile());
	}
	else 
	{
		Read(ar.GetFile());
	}
}

//创建调色板
BOOL CBmp::MakePalette()
{
	// 如果不存在调色板，则返回FALSE
	if(GetPaletteSize() == 0) 
	{
		return FALSE;
	}

	if(m_hPalette != NULL) 
	{
		::DeleteObject(m_hPalette);
	}

	// 给逻辑调色板分配内存
	LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) 
		+ GetPaletteSize() * sizeof(PALETTEENTRY)];

	// 设置逻辑调色板的信息
	pLogPal->palVersion = 	0x300;
	pLogPal->palNumEntries = GetPaletteSize();

	// 拷贝DIB中的颜色表到逻辑调色板
	LPRGBQUAD pDibQuad = (LPRGBQUAD) GetColorTable();
	for(int i = 0; i < GetPaletteSize(); ++i) 
	{
		pLogPal->palPalEntry[i].peRed = pDibQuad->rgbRed;
		pLogPal->palPalEntry[i].peGreen = pDibQuad->rgbGreen;
		pLogPal->palPalEntry[i].peBlue = pDibQuad->rgbBlue;
		pLogPal->palPalEntry[i].peFlags = 0;
		pDibQuad++;
	}

	// 创建调色板
	m_hPalette = ::CreatePalette(pLogPal);

	// 删除临时变量并返回TRUE
	delete []pLogPal;

	return TRUE;
}

//图像的大小
DWORD CBmp::GetImageSize() const
{
	ASSERT(m_pBMIH != NULL);
	return m_pBMIH->biSizeImage;
}

//获取颜色表指针
LPVOID CBmp::GetColorTable() const
{
	ASSERT(m_pBMIH != NULL);
	return (LPVOID) (m_pBMIH + sizeof(BITMAPINFOHEADER));
}

//获取信息头指针　
LPBITMAPINFOHEADER CBmp::GetBMIH() const
{
	return m_pBMIH;
}

//返回图像数据
LPBYTE CBmp::GetBits() const
{
	return m_pBits;
}

int CBmp::GetWidth() const
{
	ASSERT(m_pBMIH != NULL);
	return m_pBMIH->biWidth;
}

int CBmp::GetHeight() const
{
	ASSERT(m_pBMIH != NULL);
	return m_pBMIH->biHeight;
}

//内存宽度，4字节的倍数
int CBmp::GetWidthMemory()
{
	int ret = (m_pBMIH->biWidth * m_pBMIH->biBitCount + 31) / 32 * 4;
	return ret;	
}

int CBmp::GetBitCount() const
{
	ASSERT(m_pBMIH != NULL);
	return m_pBMIH->biBitCount;
}
//显示图像
void CBmp::Draw(CDC *pDC, CPoint ptOrigin, CSize szImage)
{
	// 如果信息头为空，返回FALSE
	if(m_pBMIH == NULL) 
	{
		return;
	}

	// 如果使用调色板，则将调色板选入设备上下文
	if(m_hPalette != NULL) 
	{
		::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	}

	// 设置显示模式
	pDC->SetStretchBltMode(COLORONCOLOR);

	// 在设备的ptOrigin位置上画出大小为szImage的图象
	::StretchDIBits(pDC->GetSafeHdc(), 
		ptOrigin.x, ptOrigin.y,			//起始点
		szImage.cx,szImage.cy,			//长和宽
		0, 0, 
		m_pBMIH->biWidth, m_pBMIH->biHeight,
		m_pBits, (LPBITMAPINFO) m_pBMIH, 
		DIB_RGB_COLORS, SRCCOPY);
}

/*************************************************
Function:       DrawOnMemory
Description:    使用双缓存技术，在内存上显示图像
Input:          
Output:         
Return:        
Others:         
步骤：
1>定义内存显示设备环境
2>在内存上画图
3>将内存中的图像拷贝到屏幕上
*************************************************/
void CBmp::DrawOnMemory(CDC *pDC, CPoint ptOrigin, CSize szImage)
{
	// 如果信息头为空，返回FALSE
	if(m_pBMIH == NULL) 
	{
		return;
	}

	// 如果使用调色板，则将调色板选入设备上下文
	if(m_hPalette != NULL) 
	{
		::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	}

	CDC memDC;				//定义显示设备环境
	CBitmap memBiitmap;		//定义位图对象

	//与屏幕显示设备兼容的内存DC
	memDC.CreateCompatibleDC(NULL);

	//与屏幕显示设备兼容的位图
	memBiitmap.CreateCompatibleBitmap(pDC, m_pBMIH->biWidth, m_pBMIH->biHeight);

	//将位图选入内存设备环境
	CBitmap *pOldBit = memDC.SelectObject(&memBiitmap);

	//先用背景色填充
	memDC.FillSolidRect(0, 0, m_pBMIH->biWidth, m_pBMIH->biHeight, RGB(192, 192, 192));

	// 设置显示模式
	pDC->SetStretchBltMode(COLORONCOLOR);

	// 在内存中画图
	::StretchDIBits(memDC.GetSafeHdc(), 
		ptOrigin.x, ptOrigin.y,			//起始点
		szImage.cx,szImage.cy,			//长和宽
		0, 0, 
		m_pBMIH->biWidth, m_pBMIH->biHeight,
		m_pBits, (LPBITMAPINFO) m_pBMIH, 
		DIB_RGB_COLORS, SRCCOPY);

	//将内存中的图像拷贝拷贝到屏幕上
	pDC->BitBlt(0, 0, m_pBMIH->biWidth, m_pBMIH->biHeight, &memDC, 0, 0, SRCCOPY);

	//释放资源
	memBiitmap.DeleteObject();
	memDC.DeleteDC();	
}

/*
//使用VFW组件提高显示性能
void CBmp::DrawUseVFW(HDRAWDIB hDrawDib, CDC *pDC, CPoint ptOrigin, CSize szImage)
{
	//准备画图，设置DrawDib环境
	DrawDibBegin(hDrawDib, pDC->GetSafeHdc(), 
		szImage.cx, szImage.cy, m_pBMIH, 			 
		m_pBMIH->biWidth, m_pBMIH->biHeight,
		DDF_SAME_HDC);

	//开始画图－－代替SDK中的StretchDIBits函数
	DrawDibDraw(hDrawDib, pDC->GetSafeHdc(), 
		ptOrigin.x, ptOrigin.y,
		szImage.cx, szImage.cy,			
		m_pBMIH, m_pBits,
		0, 0,
		m_pBMIH->biWidth,m_pBMIH->biHeight,
		DDF_SAME_HDC ) ;

	//画图结束，清除DrawDib环境
	DrawDibEnd(hDrawDib);
}
*/

