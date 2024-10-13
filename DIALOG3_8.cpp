// DIALOG3_8.cpp: 实现文件
//

#include "pch.h"
#include "MFCGC.h"
#include "afxdialogex.h"
#include "DIALOG3_8.h"


// DIALOG3_8 对话框

IMPLEMENT_DYNAMIC(DIALOG3_8, CDialogEx)

DIALOG3_8::DIALOG3_8(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	, R1(255)
	, G1(0)
	, B1(0)
	, R2(0)
	, G2(0)
	, B2(255)
	, x3_8p1x(0)
	, x3_8p1y(0)
	, x3_8p2x(100)
	, x3_8p2y(100)
{

}

DIALOG3_8::~DIALOG3_8()
{
}

void DIALOG3_8::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT2, R1);
	DDV_MinMaxInt(pDX, R1, 0, 255);
	DDX_Text(pDX, IDC_EDIT8, G1);
	DDV_MinMaxInt(pDX, G1, 0, 255);
	DDX_Text(pDX, IDC_EDIT9, B1);
	DDV_MinMaxInt(pDX, B1, 0, 255);
	DDX_Text(pDX, IDC_EDIT10, R2);
	DDV_MinMaxInt(pDX, R2, 0, 255);
	DDX_Text(pDX, IDC_EDIT11, G2);
	DDX_Text(pDX, IDC_EDIT12, B2);
	DDV_MinMaxInt(pDX, B2, 0, 255);
	DDX_Text(pDX, IDC_EDIT1, x3_8p1x);
	DDX_Text(pDX, IDC_EDIT4, x3_8p1y);
	DDX_Text(pDX, IDC_EDIT5, x3_8p2x);
	DDX_Text(pDX, IDC_EDIT6, x3_8p2y);
}


BEGIN_MESSAGE_MAP(DIALOG3_8, CDialogEx)
	ON_BN_CLICKED(IDOK, &DIALOG3_8::OnBnClickedOk)
END_MESSAGE_MAP()


// DIALOG3_8 消息处理程序

#include "MainFrm.h"
void DIALOG3_8::OnBnClickedOk()
{
	// TODO: 颜色渐变直线参数设置
	UpdateData(1);
	
		// 获取指向主窗口的指针
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	if (pMainFrame) // 确保指针有效
	{
		// 修改 CMainFrame 中的 nowDraw 及相关参数变量
		pMainFrame->nowDraw = 38;
		pMainFrame->x3_8C1 = RGB(R1,G1,B1);
		pMainFrame->x3_8C2 = RGB(R2, G2, B2);
		pMainFrame->x3_8p1 = CPoint(x3_8p1x,x3_8p1y);
		pMainFrame->x3_8p2 = CPoint(x3_8p2x, x3_8p2y);
		pMainFrame->Invalidate();



	}


	CDialogEx::OnOK();
}
