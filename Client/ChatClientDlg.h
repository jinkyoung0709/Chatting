// ChatClientDlg.h : header file
//

#include "afxwin.h"
#if !defined(AFX_CHATCLIENTDLG_H__D8E213A7_5B4A_11D5_95D8_0050DA8BB346__INCLUDED_)
#define AFX_CHATCLIENTDLG_H__D8E213A7_5B4A_11D5_95D8_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChatClientDlg dialog

class CChatClientDlg : public CDialog
{
// Construction
public:
	CChatClientDlg(CWnd* pParent = NULL);	// standard constructor

	CSocCom m_socCom;
// Dialog Data
	//{{AFX_DATA(CChatClientDlg)
	enum { IDD = IDD_CHATCLIENT_DIALOG };
	CListBox	m_list;
	CString	m_strIP;
	CString	m_strSend;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChatClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonSend();
	//}}AFX_MSG
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Combo;
	afx_msg void OnCbnSelchangeCombo1();
	CFont font1, font2, font3;
	afx_msg void OnBnClickedButtonColor();
	COLORREF color;
	int ColorChange;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	char *checklist[3];
	char *check;
	char *chatNo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATCLIENTDLG_H__D8E213A7_5B4A_11D5_95D8_0050DA8BB346__INCLUDED_)
