#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFCGC.h"
#include "MainFrm.h"

#include "MFCGCDoc.h"
#include "MFCGCView.h"

class CLine
{

public:
	CLine();
	~CLine();
	void MoveTo(CDC* pDC, int x1, int y1 );
	void LineTo(CDC* pDC, int x2, int y2);
    void LineToColor(CDC* pDC, int x2, int y2, COLORREF color1, COLORREF color2);
private:
    CPoint pos = { 0 };
};

CLine::CLine()
{
}

CLine::~CLine()
{
}

void CLine::MoveTo(CDC* pDC, int x1, int y1) {
     //�޸Ļ���λ��
    pos = { x1,y1 };
}
void CLine::LineTo(CDC* pDC, int x2, int y2)

{
    int  x1 = pos.x;
    int  y1 = pos.y;
    int x = x1;
    int y = y1;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int s1 = (x2 > x1) ? 1 : -1;
    int s2 = (y2 > y1) ? 1 : -1;
    bool flag = false;  // flag = true ��ʾб�ʴ���1������ dx �� dy

    if (dy > dx) {
        
        int a=dx;
        dx = dy;
        dy = a;
        flag = true;
    }

    int e = 2 * dy - dx; // ��ʼ�������

    for (int i = 0; i <= dx; i++) {
        pDC->SetPixel(x, y, RGB(0, 0, 0)); // ����blackɫ���ص�

        while (e >= 0) {
            if (flag) {
                x += s1; // б�� > 1 ʱ������ x
            }
            else {
                y += s2; // б�� < 1 ʱ������ y
            }
            e -= 2 * dx;
        }

        if (flag) {
            y += s2; // б�� > 1 ʱ������ y
        }
        else {
            x += s1; // б�� < 1 ʱ������ x
        }
        e += 2 * dy;
    }
    MoveTo(pDC, pos.x, pos.y);
}
void CLine::LineToColor(CDC* pDC, int x2, int y2, COLORREF color1, COLORREF color2)
{
    int x1 = pos.x;
    int y1 = pos.y;
    int x = x1;
    int y = y1;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int s1 = (x2 > x1) ? 1 : -1;
    int s2 = (y2 > y1) ? 1 : -1;
    bool flag = false; // flag = true ��ʾб�ʴ���1������ dx �� dy

    if (dy > dx) {
        int a = dx;
        dx = dy;
        dy = a;
        flag = true;
    }

    int e = 2 * dy - dx; // ��ʼ�������

    // ��ȡ��ɫ��RGB����
    int r1 = GetRValue(color1), g1 = GetGValue(color1), b1 = GetBValue(color1);
    int r2 = GetRValue(color2), g2 = GetGValue(color2), b2 = GetBValue(color2);

    for (int i = 0; i <= dx; i++) {
        // ������ɫ���䣬t �ǵ�ǰ���ȵı���
        double t = (double)i / dx;
        int r = (1 - t) * r1 + t * r2;
        int g = (1 - t) * g1 + t * g2;
        int b = (1 - t) * b1 + t * b2;

        // ���ƽ���ɫ���ص�
        pDC->SetPixel(x, y, RGB(r, g, b));

        while (e >= 0) {
            if (flag) {
                x += s1; // б�� > 1 ʱ������ x
            }
            else {
                y += s2; // б�� < 1 ʱ������ y
            }
            e -= 2 * dx;
        }

        if (flag) {
            y += s2; // б�� > 1 ʱ������ y
        }
        else {
            x += s1; // б�� < 1 ʱ������ x
        }
        e += 2 * dy;
    }

    MoveTo(pDC, pos.x, pos.y);
}
