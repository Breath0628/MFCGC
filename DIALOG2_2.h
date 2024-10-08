#pragma once
#include "afxdialogex.h"


// DIALOG2_2 对话框

class DIALOG2_2 : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG2_2)

public:
	DIALOG2_2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DIALOG2_2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
	bool ok=false;
	double recWidth;
	double recLen;
};
