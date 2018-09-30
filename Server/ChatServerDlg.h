// ChatServerDlg.h : header file
//

#include "afxwin.h"
#if !defined(AFX_CHATSERVERDLG_H__EBA31B27_5B3F_11D5_95D8_0050DA8BB346__INCLUDED_)
#define AFX_CHATSERVERDLG_H__EBA31B27_5B3F_11D5_95D8_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChatServerDlg dialog

class CChatServerDlg : public CDialog
{
// Construction
public:
	CChatServerDlg(CWnd* pParent = NULL);	// standard constructor

	CSocServer m_socServer;
	CSocCom    *m_socCom;
// Dialog Data
	//{{AFX_DATA(CChatServerDlg)
	enum { IDD = IDD_CHATSERVER_DIALOG };
	CListBox	m_list;
	CString	m_strStatus;
	CString	m_strSend;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChatServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnButton2();
	afx_msg void OnButtonSend();
	//}}AFX_MSG
	afx_msg LPARAM OnAccept(UINT wParam, LPARAM lParam);
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_Combo;
	afx_msg void OnCbnSelchangeCombo1();
	CFont font1, font2, font3;
	COLORREF Color;
	int ColorChange;
	afx_msg void OnBnClickedButtonColor();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	char *checklist[3];
	char *check;
	char *chatNo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSERVERDLG_H__EBA31B27_5B3F_11D5_95D8_0050DA8BB346__INCLUDED_)
