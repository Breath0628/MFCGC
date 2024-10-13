#pragma once
#include "afxdialogex.h"


// DIALOG3_9 对话框

class DIALOG3_9 : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG3_9)

public:
	DIALOG3_9(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DIALOG3_9();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
