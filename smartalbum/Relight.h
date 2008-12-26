#pragma once
class CBmp;
class CRelight
{
public:
	CRelight(void);
public:
	~CRelight(void);
private:
	void exposoure();
	void sub_histogram(int sub_width, int sub_length);
	void patch_analysis_relight(CBmp* pBmp);

};
