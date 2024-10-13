
// MFCGCView.h: CMFCGCView 类的接口
//

#pragma once


class CMFCGCView : public CView
{

protected: // 仅从序列化创建
	CMFCGCView() noexcept;
	DECLARE_DYNCREATE(CMFCGCView)

// 特性
public:
	CMFCGCDoc* GetDocument() const;
	CPoint lineList[100][2];;//3-3左右键监听变量 最多存在100条
	int LineNum = 0;//3-3线段数目
	


// 操作
public:
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCGCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//3-4反走样直线函数声明
	void wuLine(CDC* pDC, CPoint p0, CPoint p1);
};

#ifndef _DEBUG  // MFCGCView.cpp 中的调试版本
inline CMFCGCDoc* CMFCGCView::GetDocument() const
   { return reinterpret_cast<CMFCGCDoc*>(m_pDocument); }
#endif

