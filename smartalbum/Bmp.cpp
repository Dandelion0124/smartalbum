#include "StdAfx.h"
#include "Bmp.h"

/********************************************************************

purpose:	��дBMP

*********************************************************************/


// �������л�����
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
Description:    ��ȡBMPͼ��
Input:          CFile *pFile
Output:         
Return:         BOOL  �ɹ�����TRUE�����򷵻�FALSE
Others:         ��ȡ�ļ�ͷ����Ϣͷ����ɫ���ͼ������ 
*************************************************/
BOOL CBmp::Read(CFile *pFile)
{
	// ���ж�����
	try 
	{
		BITMAPFILEHEADER bmfh;

		// ����1����ȡ�ļ�ͷ
		int nCount = pFile->Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

		// �ж��Ƿ���BMP��ʽ��λͼ
		if(bmfh.bfType != BMP_HEADER_MARKER) 
		{
			//throw new CException;
		}

		// ������Ϣͷ���ϵ�ɫ��Ĵ�С�����ڴ�
		int nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		m_pBMIH = (LPBITMAPINFOHEADER) new BYTE[nSize];

		// ����2����ȡ��Ϣͷ�͵�ɫ��
		nCount = pFile->Read(m_pBMIH, nSize); 

		// ����3����ȡͼ������
		m_pBits = (LPBYTE) new BYTE[m_pBMIH->biSizeImage];
		nCount = pFile->Read(m_pBits, m_pBMIH->biSizeImage); 
	}

	catch(CException* pe) 
	{
//		AfxMessageBox("read error",MB_OK,0);
		pe->Delete();
		return FALSE;
	}

	//������ɫ��
	MakePalette();

	return TRUE;
}

/*************************************************
Function:       Write
Description:    д��BMPͼ��
Input:          CFile *pFile
Output:         
Return:         BOOL  �ɹ�����TRUE�����򷵻�FALSE
Others:         BMP��ʽ��ͼ���ԡ�BM��Ϊ��ʼ��־
*************************************************/
BOOL CBmp::Write(CFile *pFile)
{
	BITMAPFILEHEADER bmfh;

	// �����ļ�ͷ���ļ����� 0x424D="BM"
	bmfh.bfType = BMP_HEADER_MARKER;  

	// ������Ϣͷ�͵�ɫ���С
	int nSizeHeader = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetPaletteSize();

	// �����ļ�ͷ��Ϣ
	bmfh.bfSize      = sizeof(BITMAPFILEHEADER) + nSizeHeader + GetImageSize();
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;

	//����ƫ�������ļ�ͷ��С+��Ϣͷ��С+��ɫ���С
	bmfh.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) 
		+ sizeof(RGBQUAD) * GetPaletteSize();	

	// ����д����
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


//�����ɫ��Ĵ�С
int CBmp::GetPaletteSize() const
{
	int ret = 0;

	if(m_pBMIH->biClrUsed == 0) 	// ��ɫ��Ĵ�СΪ2��biBitCount�η�		
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
	else // ��ɫ��Ĵ�СΪʵ���õ�����ɫ��
	{
		ret = m_pBMIH->biClrUsed;
	}

	return ret;
}

//���л�
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

//������ɫ��
BOOL CBmp::MakePalette()
{
	// ��������ڵ�ɫ�壬�򷵻�FALSE
	if(GetPaletteSize() == 0) 
	{
		return FALSE;
	}

	if(m_hPalette != NULL) 
	{
		::DeleteObject(m_hPalette);
	}

	// ���߼���ɫ������ڴ�
	LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) 
		+ GetPaletteSize() * sizeof(PALETTEENTRY)];

	// �����߼���ɫ�����Ϣ
	pLogPal->palVersion = 	0x300;
	pLogPal->palNumEntries = GetPaletteSize();

	// ����DIB�е���ɫ���߼���ɫ��
	LPRGBQUAD pDibQuad = (LPRGBQUAD) GetColorTable();
	for(int i = 0; i < GetPaletteSize(); ++i) 
	{
		pLogPal->palPalEntry[i].peRed = pDibQuad->rgbRed;
		pLogPal->palPalEntry[i].peGreen = pDibQuad->rgbGreen;
		pLogPal->palPalEntry[i].peBlue = pDibQuad->rgbBlue;
		pLogPal->palPalEntry[i].peFlags = 0;
		pDibQuad++;
	}

	// ������ɫ��
	m_hPalette = ::CreatePalette(pLogPal);

	// ɾ����ʱ����������TRUE
	delete []pLogPal;

	return TRUE;
}

//ͼ��Ĵ�С
DWORD CBmp::GetImageSize() const
{
	ASSERT(m_pBMIH != NULL);
	return m_pBMIH->biSizeImage;
}

//��ȡ��ɫ��ָ��
LPVOID CBmp::GetColorTable() const
{
	ASSERT(m_pBMIH != NULL);
	return (LPVOID) (m_pBMIH + sizeof(BITMAPINFOHEADER));
}

//��ȡ��Ϣͷָ�롡
LPBITMAPINFOHEADER CBmp::GetBMIH() const
{
	return m_pBMIH;
}

//����ͼ������
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

//�ڴ��ȣ�4�ֽڵı���
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
//��ʾͼ��
void CBmp::Draw(CDC *pDC, CPoint ptOrigin, CSize szImage)
{
	// �����ϢͷΪ�գ�����FALSE
	if(m_pBMIH == NULL) 
	{
		return;
	}

	// ���ʹ�õ�ɫ�壬�򽫵�ɫ��ѡ���豸������
	if(m_hPalette != NULL) 
	{
		::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	}

	// ������ʾģʽ
	pDC->SetStretchBltMode(COLORONCOLOR);

	// ���豸��ptOriginλ���ϻ�����СΪszImage��ͼ��
	::StretchDIBits(pDC->GetSafeHdc(), 
		ptOrigin.x, ptOrigin.y,			//��ʼ��
		szImage.cx,szImage.cy,			//���Ϳ�
		0, 0, 
		m_pBMIH->biWidth, m_pBMIH->biHeight,
		m_pBits, (LPBITMAPINFO) m_pBMIH, 
		DIB_RGB_COLORS, SRCCOPY);
}

/*************************************************
Function:       DrawOnMemory
Description:    ʹ��˫���漼�������ڴ�����ʾͼ��
Input:          
Output:         
Return:        
Others:         
���裺
1>�����ڴ���ʾ�豸����
2>���ڴ��ϻ�ͼ
3>���ڴ��е�ͼ�񿽱�����Ļ��
*************************************************/
void CBmp::DrawOnMemory(CDC *pDC, CPoint ptOrigin, CSize szImage)
{
	// �����ϢͷΪ�գ�����FALSE
	if(m_pBMIH == NULL) 
	{
		return;
	}

	// ���ʹ�õ�ɫ�壬�򽫵�ɫ��ѡ���豸������
	if(m_hPalette != NULL) 
	{
		::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	}

	CDC memDC;				//������ʾ�豸����
	CBitmap memBiitmap;		//����λͼ����

	//����Ļ��ʾ�豸���ݵ��ڴ�DC
	memDC.CreateCompatibleDC(NULL);

	//����Ļ��ʾ�豸���ݵ�λͼ
	memBiitmap.CreateCompatibleBitmap(pDC, m_pBMIH->biWidth, m_pBMIH->biHeight);

	//��λͼѡ���ڴ��豸����
	CBitmap *pOldBit = memDC.SelectObject(&memBiitmap);

	//���ñ���ɫ���
	memDC.FillSolidRect(0, 0, m_pBMIH->biWidth, m_pBMIH->biHeight, RGB(192, 192, 192));

	// ������ʾģʽ
	pDC->SetStretchBltMode(COLORONCOLOR);

	// ���ڴ��л�ͼ
	::StretchDIBits(memDC.GetSafeHdc(), 
		ptOrigin.x, ptOrigin.y,			//��ʼ��
		szImage.cx,szImage.cy,			//���Ϳ�
		0, 0, 
		m_pBMIH->biWidth, m_pBMIH->biHeight,
		m_pBits, (LPBITMAPINFO) m_pBMIH, 
		DIB_RGB_COLORS, SRCCOPY);

	//���ڴ��е�ͼ�񿽱���������Ļ��
	pDC->BitBlt(0, 0, m_pBMIH->biWidth, m_pBMIH->biHeight, &memDC, 0, 0, SRCCOPY);

	//�ͷ���Դ
	memBiitmap.DeleteObject();
	memDC.DeleteDC();	
}

/*
//ʹ��VFW��������ʾ����
void CBmp::DrawUseVFW(HDRAWDIB hDrawDib, CDC *pDC, CPoint ptOrigin, CSize szImage)
{
	//׼����ͼ������DrawDib����
	DrawDibBegin(hDrawDib, pDC->GetSafeHdc(), 
		szImage.cx, szImage.cy, m_pBMIH, 			 
		m_pBMIH->biWidth, m_pBMIH->biHeight,
		DDF_SAME_HDC);

	//��ʼ��ͼ��������SDK�е�StretchDIBits����
	DrawDibDraw(hDrawDib, pDC->GetSafeHdc(), 
		ptOrigin.x, ptOrigin.y,
		szImage.cx, szImage.cy,			
		m_pBMIH, m_pBits,
		0, 0,
		m_pBMIH->biWidth,m_pBMIH->biHeight,
		DDF_SAME_HDC ) ;

	//��ͼ���������DrawDib����
	DrawDibEnd(hDrawDib);
}
*/

