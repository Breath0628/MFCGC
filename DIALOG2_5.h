#pragma once
#include "afxdialogex.h"


// DIALOG2_5 对话框

class DIALOG2_5 : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG2_5)

public:
	DIALOG2_5(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DIALOG2_5();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int x25dep;
};
