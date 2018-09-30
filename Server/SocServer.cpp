// SocServer.cpp : implementation file
//

#include "stdafx.h"
#include "ChatServer.h"
#include "SocServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSocServer

CSocServer::CSocServer()
{
}

CSocServer::~CSocServer()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSocServer, CSocket)
	//{{AFX_MSG_MAP(CSocServer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSocServer member functions

void CSocServer::Init(HWND hWnd)
{
	// 메인 윈도우 포인터 받기
	
	m_hWnd = hWnd;
}
void CSocServer::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// 클라이언트가 접속하면 메인 윈도우에 접속메시지(UM_ACCEPT)를 보낸다
	Accept(m_socCom);
	SendMessage(m_hWnd, UM_ACCEPT, 0, 0);
	CSocket::OnAccept(nErrorCode);
}

CSocCom* CSocServer::GetAcceptSocCom()
{
	// 통신소켓을 리턴한다.
	// 반환되는 통신 소켓은 클라이언트와 연결된다.
	return &m_socCom;
}
