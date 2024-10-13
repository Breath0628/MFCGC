#pragma once
#include "afxdialogex.h"


// DIALOG3_8 对话框

class DIALOG3_8 : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG3_8)

public:
	DIALOG3_8(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DIALOG3_8();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int R1;
	int G1;
	int B1;
	int R2;
	int G2;
	int B2;
	int x3_8p1x;
	int x3_8p1y;
	int x3_8p2x;
	int x3_8p2y;
};
