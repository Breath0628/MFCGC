
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 习题参数
public:
	int dep = 0;//2-5的迭代深度
	CPoint x3_5p1, x3_5p2;//3-5 p1,p2；
	CPoint x3_8p1, x3_8p2;//3-8 p1,p2；
	COLORREF x3_8C1, x3_8C2; //3-8 c1,c2;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
//	afx_msg void On22();
	afx_msg void On22();
	afx_msg void On32778();
	afx_msg void On32779();
	afx_msg void On32780();
	int nowDraw = 0;//当前绘制的图像
	afx_msg void On32781();


	afx_msg void On32782();


	afx_msg void On32785();
	afx_msg void On32786();
	afx_msg void On32788();
	afx_msg void On32789();
	afx_msg void On32790();
};


