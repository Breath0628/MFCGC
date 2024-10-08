#pragma once
#include "afxdialogex.h"


// dialog2_3 对话框

class dialog2_3 : public CDialogEx
{
	DECLARE_DYNAMIC(dialog2_3)

public:
	dialog2_3(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dialog2_3();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
