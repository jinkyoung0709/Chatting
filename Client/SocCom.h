#if !defined(AFX_SOCCOM_H__A7C0C8E1_5B48_11D5_95D8_0050DA8BB346__INCLUDED_)
#define AFX_SOCCOM_H__A7C0C8E1_5B48_11D5_95D8_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SocCom.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSocCom command target

class CSocCom : public CSocket
{
// Attributes
public:

// Operations
public:
	CSocCom();
	virtual ~CSocCom();

	HWND m_hWnd;
	void Init(HWND hWnd);

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocCom)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSocCom)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCCOM_H__A7C0C8E1_5B48_11D5_95D8_0050DA8BB346__INCLUDED_)
