
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "MFCGC.h"

#include "MainFrm.h"
#include "DIALOG2_2.h"
#include "dialog2_3.h"
#include "d2_4.h"
#include "DIALOG2_5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
//	ON_COMMAND(ID_22, &CMainFrame::On22)
ON_COMMAND(ID_22, &CMainFrame::On22)
ON_COMMAND(ID_32778, &CMainFrame::On32778)
ON_COMMAND(ID_32779, &CMainFrame::On32779)
ON_COMMAND(ID_32780, &CMainFrame::On32780)
ON_COMMAND(ID_32781, &CMainFrame::On32781)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序






void CMainFrame::On22()
{
	// TODO: 2-2
	DIALOG2_2 dlg;
	dlg.DoModal();
} 


void CMainFrame::On32778()
{
	// TODO: 2-3
	dialog2_3 dlg;
	dlg.DoModal();
}


void CMainFrame::On32779()
{
	// TODO: 2.4
	nowDraw = 24;
	d2_4 dlg;
	dlg.DoModal();
	//Invalidate();
}


void CMainFrame::On32780()
{
	// TODO: 在此添加命令处理程序代码
	DIALOG2_5 dlg;
	dlg.DoModal();
}


void CMainFrame::On32781()
{
	// TODO: 展示习题3-3的绘画逻辑
	 // 获取指向主窗口的指针
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	if (pMainFrame) // 确保指针有效
	{
		// 修改 CMainFrame 中的 nowDraw 变量
		pMainFrame->nowDraw = 33;
		pMainFrame->Invalidate();

	}


}
