#pragma once

/********************************************************************
created:	2005/06/21
created:	21:6:2005   21:53
filename: 	imagetest\bmp.h
file path:	imagetest
file base:	bmp
file ext:	h
author:		Gengxun

purpose:	��дBMP
//  [6/22/2005]�������ʾ����

*********************************************************************/
#ifndef _BMP_H__
#define _BMP_H__

//���VFW���
#include  <vfw.h>
//BMP�ļ�ͷ��־
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
	//���ڴ��л�ͼ
	void DrawOnMemory(CDC *pDC, CPoint ptOrigin, CSize szImage);  	
	//ʹ��VFW�����ͼ
	void DrawUseVFW(HDRAWDIB hDrawDib, CDC *pDC, CPoint ptOrigin, CSize szImage);

private:
	BOOL MakePalette();						//������ɫ��

public:
	//Attributes
	int GetHeight() const;
	int GetWidth() const;
	int GetBitCount() const;				//Bpp
	int GetPaletteSize() const;				//��ɫ���С
	DWORD GetImageSize() const;				//ͼ���С
	LPVOID GetColorTable() const;			//��ɫ��
	LPBITMAPINFOHEADER GetBMIH() const;		//λͼ��Ϣͷ
	LPBYTE GetBits() const;					//����ͼ������
	int GetWidthMemory();					//�ڴ��ȣ�4�ı���


	//Data
private:
	LPBITMAPINFOHEADER  m_pBMIH;			//λͼ��Ϣͷ
	LPBYTE				m_pBits;			//λͼ����

	HPALETTE            m_hPalette;			//��ɫ����	
};

#endif
