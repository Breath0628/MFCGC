
// MFCGCView.cpp: CMFCGCView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCGC.h"
#endif

#include "MFCGCDoc.h"
#include "MFCGCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MainFrm.h"
#include "CLine.h"

// CMFCGCView

IMPLEMENT_DYNCREATE(CMFCGCView, CView)

BEGIN_MESSAGE_MAP(CMFCGCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCGCView 构造/析构

CMFCGCView::CMFCGCView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCGCView::~CMFCGCView()
{
}

BOOL CMFCGCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}
//由四个点得交点 整型
CPoint intersection_point(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	double A1, B1, C1, A2, B2, C2, denominator;
	double x, y;
	A1 = y2 - y1;
	B1 = x1 - x2;
	C1 = A1 * x1 + B1 * y1;

	A2 = y4 - y3;
	B2 = x3 - x4;
	C2 = A2 * x3 + B2 * y3;

	denominator = A1 * B2 - A2 * B1;
	if (denominator == 0) {
		return NULL;
	}

	x = (B2 * C1 - B1 * C2) / denominator;
	y = (A1 * C2 - A2 * C1) / denominator;
	return CPoint(round(x), round(y));
}
// CMFCGCView 绘图

void CMFCGCView::OnDraw(CDC* pDC)
{
	CMFCGCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	//将所有的视区都修改为向上向右为正 原点为中间
	CRect rect;//不是单纯的一个数值
	GetClientRect(rect);
	pDC->SetMapMode(MM_ANISOTROPIC);//变量是一种映射模式；->：指向成员运算符
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口大小（宽度、高度）
	pDC->SetViewportExt(rect.Width(), -rect.Height());//设置视区的大小，使Y轴向上
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//设置原点位置
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);//偏移函数,向左偏移


	// 获取主框架窗口
	CMainFrame* pMainFrame = (CMainFrame*)GetParentFrame();
	if (pMainFrame)
	{
		// 访问 CMainFrame 中的变量
		int nowDraw = pMainFrame->nowDraw;
		CString txt;
		txt.Format(_T("%d"), nowDraw);

		// 获取主窗口的尺寸
		CRect clientRect;
		GetClientRect(&clientRect);

		// 计算窗口中心
		int centerX = clientRect.Width() / 2;
		int centerY = clientRect.Height() / 2;

		// 根据nowDraw 进行绘图
		//pDC->TextOut(10, 10, CString("Value: ")+ txt);
		switch (nowDraw)
		{
		case 24:
		{
			pDC->TextOut(10, 10, CString("习题2-4: "));
			break;
		}
		case 25:

		{
			int depth=pMainFrame->dep;
			pDC->TextOut(10- centerX, centerY, CString("习题2-5: "));

			CPen pen(PS_SOLID, 1, RGB(0, 0, 0)); // 黑色边框
			CPen* pOldPen = pDC->SelectObject(&pen);
			pDC->SelectStockObject(NULL_BRUSH);


			CPoint pList[5];
			double c=0.5*3.1415926,r=200;
			double x, y;
			//迭代深度
			for (size_t j = 0; j < depth; j++)
			{
				//根据起始弧度和半径计算顶点
				for (size_t i = 0; i < 5; i++)
				{
					x =(r * cos(c));
					y = (r * sin(c));
					pList[i] = CPoint(round(x), round(y));
					c += 0.4 * 3.1415926;
				}
				//绘制
				CPoint p, p2;
				for (size_t i = 0; i < 5; i++)
				{
					
					p = pList[i];
					for (size_t m= 0; m< 5; m++)
					{
						pDC->MoveTo(p);
						p2 = pList[m];
						pDC->LineTo(p2);
					}
					
				}
				
				//计算下层迭代的起始位置 转为起始弧度和半径
				CPoint pp=intersection_point(
					pList[0].x, pList[0].y, pList[2].x, pList[2].y,
					pList[1].x, pList[1].y, pList[3].x, pList[3].y);

				r = pow((pow(pp.x, 2) + pow(pp.y, 2)), 0.5);
				c = asin(pp.y / r);
			}
			
			pDC->SelectObject(pOldPen);
			break;
		}
		case 33:
		{
			//习题3-3
			pDC->TextOut(10 - centerX, centerY, CString("习题3-3: "));
	
			CLine e;
			CPoint p1, p2;

			//根据线条数量画图
			for (size_t i = 0; i < LineNum; i++)
			{
				p1 = lineList[i][0];
				p2 = lineList[i][1];
				e.MoveTo(pDC, p1.x- rect.Width() / 2, -p1.y+rect.Height() / 2);
				e.LineTo(pDC, p2.x - rect.Width() / 2, -p2.y + rect.Height() / 2);
			}
			
			break;
		}


		default:
			break;
		}


	}
	
}




// CMFCGCView 打印

BOOL CMFCGCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCGCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCGCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCGCView 诊断

#ifdef _DEBUG
void CMFCGCView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCGCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCGCDoc* CMFCGCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCGCDoc)));
	return (CMFCGCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCGCView 消息处理程序


void CMFCGCView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:左键点击
	
// 获取指向主窗口的指针
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	if (pMainFrame) // 确保指针有效
	{
		// 修改 CMainFrame 中的 nowDraw 变量
		switch (pMainFrame->nowDraw)
		{
		case 33:
		{// 获取点击的坐标
			//CString str;
			//str.Format(_T("右键点击坐标: X = %d, Y = %d"), point.x, point.y);

			//// 显示坐标信息
			//AfxMessageBox(str);

			lineList[LineNum][0] = point;//起始点赋值
			break;
			
		}
		default:
			break;
		} 
	
	}

	CView::OnLButtonUp(nFlags, point);
}


void CMFCGCView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 3-3右键点击事件
	// 获取指向主窗口的指针
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	if (pMainFrame) // 确保指针有效
	{
		// 修改 CMainFrame 中的 nowDraw 变量
		switch (pMainFrame->nowDraw)
		{
		case 33:
		{
			lineList[LineNum][1] = point;//终止点赋值
			LineNum++;
			Invalidate();
			break;
	

		}
		default:
			break;
		}

	}
	CView::OnRButtonUp(nFlags, point);
	
}

