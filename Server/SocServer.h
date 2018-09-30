#if !defined(AFX_SOCSERVER_H__EBA31B2F_5B3F_11D5_95D8_0050DA8BB346__INCLUDED_)
#define AFX_SOCSERVER_H__EBA31B2F_5B3F_11D5_95D8_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SocServer.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSocServer command target

class CSocServer : public CSocket
{
// Attributes
public:

// Operations
public:
	CSocServer();
	virtual ~CSocServer();

	HWND m_hWnd; // 메인 윈도우 핸들
	CSocCom m_socCom; // 접속 요청이 왔을때 연결한 소켓
	
	void Init(HWND hWnd);
	CSocCom *GetAcceptSocCom();
	
// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocServer)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSocServer)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCSERVER_H__EBA31B2F_5B3F_11D5_95D8_0050DA8BB346__INCLUDED_)
