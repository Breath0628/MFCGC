// d2_4.cpp: 实现文件
//

#include "pch.h"
#include "MFCGC.h"
#include "afxdialogex.h"
#include "d2_4.h"


// d2_4 对话框

IMPLEMENT_DYNAMIC(d2_4, CDialogEx)

d2_4::d2_4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, x2_4_R(100)
	, x_2_4_r(50)
	, x_2_4_n(18)
{


}

d2_4::~d2_4()
{
}

void d2_4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, x2_4_R);
	DDX_Text(pDX, IDC_EDIT3, x_2_4_r);
	DDX_Text(pDX, IDC_EDIT4, x_2_4_n);
}

void d2_4::OnPaint()
{
	
    CPaintDC dc(this); // device context for painting
	CPaintDC* pDC = &dc;
	pDC->TextOut(10, 10, CString("习题2-4: "));

	// 定义常量
	int n ; // 等分的大圆份数
	int R ; // 大圆的半径
	int r ;  // 小圆的半径
	n=x_2_4_n;
	R=x2_4_R;
	r = x_2_4_r;
	// 获取窗口中心点作为大圆圆心
	CRect rect;
	GetClientRect(&rect);
	int centerX = rect.Width() / 2;
	int centerY = rect.Height() / 2;

	// 定义大圆圆心
	CPoint center(centerX, centerY);

	// 设置黑色画笔来绘制圆（边框颜色）
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0)); // 黑色边框
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->SelectStockObject(NULL_BRUSH);

	// 计算每个等分点并绘制小圆
	for (int i = 0; i < n; i++)
	{
		// 计算每个等分点的角度（弧度制）
		double angle = 2 * 3.14159 * i / n;

		// 计算等分点的坐标
		int x = static_cast<int>(centerX + R * cos(angle));
		int y = static_cast<int>(centerY + R * sin(angle));

		// 绘制小圆（以等分点为圆心，半径为 r），不填充背景
		// 计算小圆的外接矩形
		pDC->Ellipse(x - r, y - r, x + r, y + r);
	}

	// 恢复原来的画笔
	pDC->SelectObject(pOldPen);
}

BEGIN_MESSAGE_MAP(d2_4, CDialogEx)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT1, &d2_4::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, &d2_4::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &d2_4::OnEnChangeEdit4)
END_MESSAGE_MAP()


// d2_4 消息处理程序


void d2_4::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(1);
	if (x2_4_R&&x_2_4_n&&x_2_4_r)
	{
		Invalidate();
	}
	
}


void d2_4::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(1);
	if (x2_4_R && x_2_4_n && x_2_4_r)
	{
		Invalidate();
	}
}


void d2_4::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(1);
	if (x2_4_R && x_2_4_n && x_2_4_r)
	{
		Invalidate();
	}
}
