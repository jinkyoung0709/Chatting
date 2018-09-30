// SocCom.cpp : implementation file
//

#include "stdafx.h"
#include "chatserver.h"
#include "SocCom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSocCom

CSocCom::CSocCom()
{
}

CSocCom::~CSocCom()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSocCom, CSocket)
	//{{AFX_MSG_MAP(CSocCom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSocCom member functions

void CSocCom::Init(HWND hWnd)
{
	m_hWnd = hWnd;
}


void CSocCom::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	SendMessage(m_hWnd, UM_RECEIVE, 0, 0);
	CSocket::OnReceive(nErrorCode);
}
