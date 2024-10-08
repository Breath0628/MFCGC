#pragma once
#include "afxdialogex.h"


// d2_4 对话框

class d2_4 : public CDialogEx
{
	DECLARE_DYNAMIC(d2_4)

public:
	d2_4(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~d2_4();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
public:
	int x2_4_R,x_2_4_r, x_2_4_n;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
};
