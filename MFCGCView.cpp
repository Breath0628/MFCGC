
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
#include <queue>

void CMFCGCView::SeedFill(CDC* pDC, int x, int y, COLORREF fillColor, COLORREF boundaryColor)
{
	// 获取种子点的初始颜色
	COLORREF startColor = pDC->GetPixel(x, y);

	// 如果种子点已经是填充颜色或者是边界颜色，则不进行填充
	if (startColor == fillColor || startColor == boundaryColor)
		return;

	// 使用队列来存储需要填充的像素位置
	std::queue<CPoint> pixelQueue;
	pixelQueue.push(CPoint(x, y));

	// 8连通方向（上下左右以及四个对角线方向）
	int dx[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
	int dy[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };

	while (!pixelQueue.empty())
	{
		// 从队列中取出一个点
		CPoint point = pixelQueue.front();
		pixelQueue.pop();

		// 获取当前点的颜色
		COLORREF currentColor = pDC->GetPixel(point.x, point.y);

		// 如果当前点是起始颜色，则填充它并处理它的相邻点
		if (currentColor == startColor)
		{
			// 填充当前像素
			pDC->SetPixel(point.x, point.y, fillColor);

			// 检查8个方向上的相邻像素
			for (int i = 0; i < 8; ++i)
			{
				int newX = point.x + dx[i];
				int newY = point.y + dy[i];

				// 获取相邻像素的颜色
				COLORREF neighborColor = pDC->GetPixel(newX, newY);

				// 如果相邻像素的颜色不是边界颜色且不是填充颜色，则将它加入队列
				if (neighborColor != fillColor && neighborColor != boundaryColor)
				{
					pixelQueue.push(CPoint(newX, newY));
				}
			}
		}
	}
}
// CMFCGCView 绘图
#include <cmath>
using namespace std;
void CMFCGCView::FillPolygon(CDC* pDC, COLORREF GetClr, CPoint P[], int MaxX)
{
	COLORREF BClr = RGB(255, 255, 255);//背景色
	COLORREF FClr = GetClr;//填充色
	int yMin, yMax;//边的最小y值与最大y值
	double x, y, k;//x,y当前点，k斜率的倒数
	for (int i = 0; i < 7; i++)//循环多边形所有边
	{
		int j = (i + 1) % 7;
		k = double(P[i].x - P[j].x) / double(P[i].y - P[j].y);//计算1/k
		if (P[i].y < P[j].y)//得到每条边y的最大值与最小值
		{
			yMin = P[i].y;
			yMax =P[j].y;
			x = P[i].x;//得到x|ymin
		}
		else
		{
			yMin = (P[j].y);
			yMax =P[i].y;
			x = P[j].x;
		}

		for (y = yMin; y < yMax; y++)//沿每一条边循环扫描线
		{
			//对每一条扫描线与边的交点的右侧像素循环   
			for (int m = x; m < MaxX; m++)
				//MaxX为包围盒的右边界
			{
				if (FClr == pDC->GetPixel(m, y))		
					pDC->SetPixelV(m, y, BClr);
				else
					pDC->SetPixelV(m,y, FClr);
			}
			x += k;
		}
	}
}



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

		case 34:
		{//习题3-4
			CPoint x3_5p1 = pMainFrame->x3_5p1;
			CPoint x3_5p2 = pMainFrame->x3_5p2;
			pDC->TextOut(10 - centerX, centerY, CString("习题3-4: "));
			wuLine(pDC, x3_5p1, x3_5p2);
			break;
		}
		case 38: {
			pDC->TextOut(10 - centerX, centerY, CString("习题3-8: "));
			
			CLine e;
			e.MoveTo(pDC, pMainFrame->x3_8p1.x, pMainFrame->x3_8p1.y);
			e.LineToColor(pDC, pMainFrame->x3_8p2.x, pMainFrame->x3_8p2.y, pMainFrame->x3_8C1, pMainFrame->x3_8C2);

			break;
		}
		case 39:
		{
			pDC->TextOut(10 - centerX, centerY, CString("习题3-9: "));

			break;
		}
		case 43:
		{
			pDC->TextOut(10 - centerX, centerY, CString("习题4-3: "));
			CRect rectLeft(-250, 200, -50, 0);  // 左边的正方形
			CRect rectRight(50, 200, 250, 0); // 右边的正方形

			    // 创建四种不同颜色的刷子来填充四个三角形
			CBrush brush1(RGB(0, 0, 0));    // 黑色刷子
		
			// 定义左边正方形的四个顶点
			POINT leftTopLeft = { rectLeft.left, rectLeft.top };        // 左上角
			POINT leftTopRight = { rectLeft.right, rectLeft.top };      // 右上角
			POINT leftBottomLeft = { rectLeft.left, rectLeft.bottom };  // 左下角
			POINT leftBottomRight = { rectLeft.right, rectLeft.bottom }; // 右下角
		
			// 定义右边正方形的四个顶点
			POINT rightTopLeft = { rectRight.left, rectRight.top };        // 左上角
			POINT rightTopRight = { rectRight.right, rectRight.top };      // 右上角
			POINT rightBottomLeft = { rectRight.left, rectRight.bottom };  // 左下角
			POINT rightBottomRight = { rectRight.right, rectRight.bottom }; // 右下角
			
			// 左边正方形的2个三角形
			POINT leftTriangle1[] = { leftTopLeft, leftTopRight, leftBottomLeft };
			POINT leftTriangle2[] = { leftTopRight, leftBottomRight, leftBottomLeft };
	
			// 右边正方形的2个三角形
			POINT rightTriangle1[] = { rightTopLeft, rightBottomLeft, rightBottomRight };
			POINT rightTriangle2[] = { rightTopLeft, rightTopRight, rightBottomRight };

			// 绘制左正方形的右对角线
			pDC->MoveTo(leftTopRight);
			pDC->LineTo(leftBottomLeft);

			// 绘制右正方形的左对角线
			pDC->MoveTo(rightTopLeft);
			pDC->LineTo(rightBottomRight);

			// 填充左正方形的四个三角形
			pDC->SelectObject(&brush1);
			pDC->Polygon(leftTriangle1, 3);  // 左上角三角形
			pDC->SelectObject(&brush1);
			pDC->Polygon(leftTriangle2, 3);  // 右上角三角形
			pDC->SelectObject(&brush1);

			// 填充右正方形的四个三角形
			pDC->SelectObject(&brush1);
			pDC->Polygon(rightTriangle1, 3);  // 左上角三角形
			pDC->SelectObject(&brush1);
			pDC->Polygon(rightTriangle2, 3);  // 右上角三角形
	
			break;
		}
		case 47:
		{
			pDC->TextOut(10 - centerX, centerY, CString("习题4-7: "));
			CRect rect(-220, 220 ,220, -220);
			CPoint pList[7] = 
			{
				CPoint(7,8),CPoint(3,12),CPoint(1,7),CPoint(3,1),
				CPoint(6,5),CPoint(8,1),CPoint(12,9),
			};
			//放大40倍 坐标转换
			for (size_t i = 0; i < 7; i++)
			{
				pList[i].x *= 40;
				pList[i].y *= 40;
				pList[i].x -= 260;
				pList[i].y -= 260;
			}
			pDC->Rectangle(rect);
			for (size_t i = 0; i < 7; i++)
			{
				pDC->MoveTo(pList[i]);
				pDC->LineTo(pList[(i + 1)%7]);
			}
			FillPolygon(pDC,RGB(0,0,0),pList,220);
			break;
		}
		case 49:
		{
			pDC->TextOut(10 - centerX, centerY, CString("习题4-9: "));
			// 设置边界矩形
			CRect rect1(-200, 0, 0, -200);
			CRect rect2(0, 200, 200, 0);
			// 创建一个画笔用于绘制矩形边界
			CPen pen(PS_SOLID, 1, RGB(0, 0, 0));  // 黑色画笔
			pDC->SelectObject(&pen);
			// 定义填充颜色和边界颜色
			COLORREF fillColor = RGB(0, 0, 0);   // 黑色填充
			COLORREF boundaryColor = RGB(0, 0, 0); // 黑色边界

			pDC->Rectangle(rect1);
			pDC->Rectangle(rect2);
			// 选定种子点
			int seedX1 = -100;
			int seedY1 = -100;
			int seedX2 = 100;
			int seedY2 = 100;
			// 调用种子填充算法
			SeedFill(pDC, seedX1, seedY1, fillColor, boundaryColor);
			SeedFill(pDC, seedX2, seedY2, fillColor, boundaryColor);
			break;
		}
		default:
			break;
		}


	}
	
}

//3-4反走样斜线段
void CMFCGCView::wuLine(CDC* pDC,CPoint p0, CPoint p1)
{

	CPoint p, temp;
	int dx = p1.x - p0.x;
	int dy = p1.y - p0.y;
	double k = (dy * 1.00) / (dx * 1.00);//计算斜率

	if (dx == 0)//垂线
	{
		if (dy < 0)//起点在上方，调换
		{
			temp = p0;
			p0 = p1;
			p1 = temp;
		}
		for (p = p0; p.y < p1.y; p.y++)//主移动方向->y,不包括p1
		{
			pDC->SetPixelV(p.x, p.y, RGB(0, 0, 0));
		}
	}

	else
	{
		double e = 0.00;//增量

		if (k >= 0 && k <= 1)
		{
			if (dx < 0)//p1在左侧，调换
			{
				temp = p0;
				p0 = p1;
				p1 = temp;
			}//p0在左下

			for (p = p0; p.x < p1.x; p.x++)//主移动方向->x,不包括p1
			{
				pDC->SetPixelV(p.x, p.y, RGB(e * 255, e * 255, e * 255));
				pDC->SetPixelV(p.x, p.y + 1, RGB((1 - e) * 255, (1 - e) * 255, (1 - e) * 255));//不同亮度值
				e += k;

				if (e >= 1.0)
				{
					p.y++;
					e -= 1;
				}
			}
			/*p0.x+=10;
			p1.x+=10;
			pDC->MoveTo(p0);
			pDC->LineTo(p1);*/
		}
		else if (k > 1)
		{
			if (dy < 0)//p1在左侧，调换
			{
				temp = p0;
				p0 = p1;
				p1 = temp;
			}//p0在下方

			for (p = p0; p.y < p1.y; p.y++)//主移动方向->y,不包括p1
			{
				pDC->SetPixelV(p.x, p.y, RGB(e * 255, e * 255, e * 255));
				pDC->SetPixelV(p.x + 1, p.y, RGB((1 - e) * 255, (1 - e) * 255, (1 - e) * 255));
				e += 1.00 / (k * 1.00);

				if (e >= 1.0)
				{
					p.x++;
					e -= 1;
				}
			}
		}

		else if (k >= -1 && k < 0)
		{
			e = 0.00;
			if (dx < 0)//p1在左上，调换
			{
				temp = p0;
				p0 = p1;
				p1 = temp;
			}//p0在左上

			for (p = p0; p.x < p1.x; p.x++)//主移动方向->x,不包括p1
			{
				pDC->SetPixelV(p.x, p.y, RGB(-1 * e * 255, -1 * e * 255, -1 * e * 255));
				pDC->SetPixelV(p.x, p.y - 1, RGB((1 + e) * 255, (1 + e) * 255, (1 + e) * 255));//这里e是负数！！！
				e += k;

				if (e <= -1.0)
				{
					p.y--;
					e += 1.0;
				}
			}
		}

		else if (k < -1)
		{
			if (dy > 0)//p1在上方，调换
			{
				temp = p0;
				p0 = p1;
				p1 = temp;
			}//p0在上
			for (p = p0; p.y > p1.y; p.y--)//主移动方向->y,不包括p1
			{
				pDC->SetPixelV(p.x, p.y, RGB(e * 255, e * 255, e * 255));
				pDC->SetPixelV(p.x + 1, p.y, RGB((1 - e) * 255, (1 - e) * 255, (1 - e) * 255));
				e += -1.0 / (k * 1.0);

				if (e >= 1.0)
				{
					p.x++;
					e -= 1;
				}
			}
		}

	}

}
//3-8颜色渐变曲线


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

