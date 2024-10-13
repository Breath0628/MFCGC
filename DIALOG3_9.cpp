// DIALOG3_9.cpp: 实现文件
//

#include "pch.h"
#include "MFCGC.h"
#include "afxdialogex.h"
#include "DIALOG3_9.h"


// DIALOG3_9 对话框

IMPLEMENT_DYNAMIC(DIALOG3_9, CDialogEx)

DIALOG3_9::DIALOG3_9(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
{

}

DIALOG3_9::~DIALOG3_9()
{
}

void DIALOG3_9::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DIALOG3_9, CDialogEx)
	ON_BN_CLICKED(IDOK, &DIALOG3_9::OnBnClickedOk)
END_MESSAGE_MAP()


// DIALOG3_9 消息处理程序


#include "MainFrm.h"
void DIALOG3_9::OnBnClickedOk()
{
	// TODO: 
		// 获取指向主窗口的指针
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	if (pMainFrame) // 确保指针有效
	{
		// 修改 CMainFrame 中的 nowDraw 变量
		pMainFrame->nowDraw = 39;
		pMainFrame->Invalidate();
	}


	CDialogEx::OnOK();
}

