// dialog2_3.cpp: 实现文件
//

#include "pch.h"
#include "MFCGC.h"
#include "afxdialogex.h"
#include "dialog2_3.h"


// dialog2_3 对话框

IMPLEMENT_DYNAMIC(dialog2_3, CDialogEx)

dialog2_3::dialog2_3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

dialog2_3::~dialog2_3()
{
}

void dialog2_3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(dialog2_3, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// dialog2_3 消息处理程序



 void dialog2_3::OnPaint()
{
	
    CPaintDC dc(this); // 为绘图提供上下文

    // 使用 SetPixel 绘制从 (100, 100) 到 (400, 100) 的黑色直线
    for (int x = 100; x <= 400; ++x)
    {
        dc.SetPixel(x, 100, RGB(0, 0, 0));  // 黑色像素
    }
    dc.TextOutW(150,70,L" SetPixel函数绘制");

    // 使用 LineTo 绘制从 (100, 100) 到 (400, 100) 的黑色直线
    dc.SelectStockObject(BLACK_PEN);  // 选择黑色画笔
    dc.MoveTo(100, 200);              // 设置起点
    dc.LineTo(400, 200);              // 绘制直线
    dc.TextOutW(150, 170, L" LineTo函数绘制");
}