// DIALOG2_5.cpp: 实现文件
//

#include "pch.h"
#include "MFCGC.h"
#include "afxdialogex.h"
#include "DIALOG2_5.h"
#include "MainFrm.h"

// DIALOG2_5 对话框

IMPLEMENT_DYNAMIC(DIALOG2_5, CDialogEx)

DIALOG2_5::DIALOG2_5(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, x25dep(3)
{

}

DIALOG2_5::~DIALOG2_5()
{
}

void DIALOG2_5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, x25dep);
}


BEGIN_MESSAGE_MAP(DIALOG2_5, CDialogEx)
	ON_BN_CLICKED(IDOK, &DIALOG2_5::OnBnClickedOk)
END_MESSAGE_MAP()


// DIALOG2_5 消息处理程序


void DIALOG2_5::OnBnClickedOk()
{
	UpdateData(1);
	 // 获取指向主窗口的指针
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	if (pMainFrame) // 确保指针有效
	{
		// 修改 CMainFrame 中的 nowDraw 变量
		pMainFrame->nowDraw = 25; 
		pMainFrame->dep = x25dep;
		pMainFrame->Invalidate();
	}

	
	CDialogEx::OnOK();

}
