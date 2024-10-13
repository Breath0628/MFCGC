// DIALOG2_2.cpp: 实现文件
//

#include "pch.h"
#include "MFCGC.h"
#include "afxdialogex.h"
#include "DIALOG2_2.h"


// DIALOG2_2 对话框

IMPLEMENT_DYNAMIC(DIALOG2_2, CDialogEx)

DIALOG2_2::DIALOG2_2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, recLen(0)

{


}

DIALOG2_2::~DIALOG2_2()
{
}

void DIALOG2_2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, recWidth);
	DDX_Text(pDX, IDC_EDIT2, recLen);
}


BEGIN_MESSAGE_MAP(DIALOG2_2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DIALOG2_2::OnBnClickedButton1)
	ON_WM_PAINT()  // 消息映射，关联WM_PAINT消息
END_MESSAGE_MAP()


// DIALOG2_2 消息处理程序

void DIALOG2_2::OnPaint()
{
	CPaintDC dc(this); // 设备上下文，用于绘图
	CString strValue;
	if (ok)
	{
		strValue.Format(_T("长方形的面积:%.4f"), recLen * recWidth);
		dc.TextOutW(160, 70, strValue);
		strValue.Format(_T("长方形的周长:%.4f"), (recLen + recWidth)*2);
		dc.TextOutW(160, 110, strValue);
	}
	

}
void DIALOG2_2::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理
	UpdateData(true);
	ok = true;
	Invalidate();

}
