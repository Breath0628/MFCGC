// DIALOG3_5.cpp: 实现文件
//

#include "pch.h"
#include "MFCGC.h"
#include "afxdialogex.h"
#include "DIALOG3_5.h"
#include "MainFrm.h"

// DIALOG3_5 对话框

IMPLEMENT_DYNAMIC(DIALOG3_5, CDialogEx)

DIALOG3_5::DIALOG3_5(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
	, x3_5_p1x(0)
	, x3_5_p1y(0)
	, x3_5_p2x(100)
	, x3_5_p2y(100)
{
	
}

DIALOG3_5::~DIALOG3_5()
{
}

void DIALOG3_5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, x3_5_p1x);
	DDX_Text(pDX, IDC_EDIT4, x3_5_p1x);
	DDX_Text(pDX, IDC_EDIT5, x3_5_p2x);
	DDX_Text(pDX, IDC_EDIT6, x3_5_p2y);
}


BEGIN_MESSAGE_MAP(DIALOG3_5, CDialogEx)
	ON_BN_CLICKED(IDOK, &DIALOG3_5::OnBnClickedOk)
END_MESSAGE_MAP()


// DIALOG3_5 消息处理程序


void DIALOG3_5::OnBnClickedOk()
{
	//反走样直线确定
	UpdateData(1);
	// 获取指向主窗口的指针
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	if (pMainFrame) // 确保指针有效
	{
		// 修改 CMainFrame 中的 nowDraw 变量
		pMainFrame->nowDraw = 34;
		pMainFrame->x3_5p1 = CPoint(x3_5_p1x,x3_5_p1y);
		pMainFrame->x3_5p2 = CPoint(x3_5_p2x, x3_5_p2y);
		pMainFrame->Invalidate();
	}

	CDialogEx::OnOK();
}
