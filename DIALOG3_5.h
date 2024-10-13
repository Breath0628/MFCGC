#pragma once
#include "afxdialogex.h"


// DIALOG3_5 对话框

class DIALOG3_5 : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG3_5)

public:
	DIALOG3_5(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DIALOG3_5();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int x3_5_p1x;
	int x3_5_p1y;
	int x3_5_p2x;
	int x3_5_p2y;
	afx_msg void OnBnClickedOk();
};
