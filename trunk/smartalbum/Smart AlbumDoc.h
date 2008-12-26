// Smart AlbumDoc.h : CSmartAlbumDoc 类的接口
//


#pragma once

class CBmp;
class CSmartAlbumDoc : public CDocument
{
protected: // 仅从序列化创建
	CSmartAlbumDoc();
	DECLARE_DYNCREATE(CSmartAlbumDoc)

// 属性
public:

// 操作
public:
	CBmp* GetImage();								//获取图像指针

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CSmartAlbumDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
private:
	CBmp * m_pBmp;				//图像指针
};


