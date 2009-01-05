#include "StdAfx.h"
#include "Relight.h"
#include "Bmp.h"

#define patch_Height 40
#define patch_Width  40
CRelight::CRelight(void)
{

}

CRelight::~CRelight(void)
{

}
void CRelight::patch_analysis_relight(CBmp* pBmp)
{
	CSize imagesize,patchsize,patchnumber;

	patchsize.cx = patch_Width;
	patchsize.cy = patch_Height;

	imagesize.cx = pBmp->GetWidth();
	imagesize.cy = pBmp->GetHeight();

	patchnumber.cx = imagesize.cx / patchsize.cx;
	patchnumber.cy = imagesize.cy / patchsize.cy;

	for(int i = 0; i < patchnumber.cx; ++i)
		for (int j = 0; j < patchnumber.cy; ++j)
		{
			
		}
}