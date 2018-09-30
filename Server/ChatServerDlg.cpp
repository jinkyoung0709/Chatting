// ChatServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatServerDlg dialog

CChatServerDlg::CChatServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatServerDlg)
	m_strStatus = _T("");
	m_strSend = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatServerDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialog)
	//{{AFX_MSG_MAP(CChatServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_ACCEPT, OnAccept)
	ON_MESSAGE(UM_RECEIVE, OnReceive)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CChatServerDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CChatServerDlg::OnBnClickedButtonColor)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatServerDlg message handlers

BOOL CChatServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	m_socCom = NULL;
	// 서버 소켓을 생성해 접속을 기다린다.
	m_socServer.Create(5000);
	m_socServer.Listen();
	m_socServer.Init(this->m_hWnd);

	//지정된 폰트 목록
	m_Combo.AddString(_T("굴림체"));
	m_Combo.AddString(_T("궁서체"));
	m_Combo.AddString(_T("돋움체"));
	m_Combo.SetCurSel(0);
	font1.CreateFont(12, 7, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("굴림체"));
	font2.CreateFont(12, 7, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("궁서체"));
	font3.CreateFont(12, 7, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("돋움체"));

	//색상 변경을 위한 변수 초기화
	ColorChange = 0;
	Color = RGB(0, 0, 0);

	//욕설 필터를 위한 초기화
	checklist[0] = "순천";
	checklist[1] = "향대";
	checklist[2] = "School";
	chatNo = "금지어 사용하여 전송할 수 없습니다.";
	check = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LPARAM CChatServerDlg::OnAccept(UINT wParam, LPARAM lParam)
{
	// 클라이언트에서 접속 요청이 왔을때
	m_strStatus = "접속성공";
	
	// 통신용 소켓을 생성한뒤
	m_socCom = new CSocCom;
	// 서버소켓과 통신소켓을 연결한다.
	m_socCom = m_socServer.GetAcceptSocCom();
	m_socCom->Init(this->m_hWnd);

	m_socCom->Send("접속성공", 256);

	UpdateData(FALSE);
	return TRUE;
}


LPARAM CChatServerDlg::OnReceive(UINT wParam, LPARAM lParam)
{
	// 접속된 곳에서 데이터가 도착했을때

	char pTmp[256];
	CString strTmp;
	memset(pTmp, '\0', 256);
	
	// 데이터를 pTmp에 받는다.
	m_socCom->Receive(pTmp, 256);
	for(int i = 0; i < 3; i++) {
		check = strstr(pTmp, checklist[i]);
		if(check != 0) break;
	}
	if(check != 0) {
		strTmp.Format("Client: %s", chatNo);
	} else
		strTmp.Format("Client: %s", pTmp);

	// 리스트박스에 보여준다.
	int i = m_list.GetCount();
	m_list.InsertString(i, strTmp);
	m_list.SetTopIndex(m_list.GetCount() - 1);
	return TRUE;
}

void CChatServerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CChatServerDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	
	CDialog::OnOK();
}

void CChatServerDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char pTmp[256];
	CString strTmp;
	// pTmp에 전송할 데이터 입력
	memset(pTmp, '\0', 256);
	strcpy(pTmp, m_strSend);
	// 전송
	m_socCom->Send(pTmp, 256);

	// 전송한 데이터도 리스트박스에 보여준다
	for(int i = 0; i < 3; i++) {
		check = strstr(pTmp, checklist[i]);
		if(check != 0) break;
	}
	if(check != 0) {
		strTmp.Format("Server: %s", chatNo);
	} else
		strTmp.Format("Server: %s", pTmp);
	int i = m_list.GetCount();
	m_list.InsertString(i, strTmp);
	SetDlgItemText(IDC_EDIT_SEND, 0);
	m_list.SetTopIndex(m_list.GetCount() - 1);
}

void CChatServerDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strFontName;
	int nIndex = m_Combo.GetCurSel();
	if(nIndex != LB_ERR) {
		if(nIndex == 0) {
			GetDlgItem(IDC_EDIT_SEND)->SetFont(&font1);
			GetDlgItem(IDC_LIST1)->SetFont(&font1);
		} else if(nIndex == 1) {
			GetDlgItem(IDC_EDIT_SEND)->SetFont(&font2);
			GetDlgItem(IDC_LIST1)->SetFont(&font2);
		} else if(nIndex == 2) {
			GetDlgItem(IDC_EDIT_SEND)->SetFont(&font3);
			GetDlgItem(IDC_LIST1)->SetFont(&font3);
		}
	}
}

void CChatServerDlg::OnBnClickedButtonColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CColorDialog dlg(Color);
	if(dlg.DoModal() == IDCANCEL)
		return;
	Color = dlg.GetColor();
	ColorChange = 1;
}

HBRUSH CChatServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if(pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT_SEND)->GetSafeHwnd())
		pDC->SetTextColor(Color);
	if(pWnd->GetSafeHwnd() == GetDlgItem(IDC_LIST1)->GetSafeHwnd())
		pDC->SetTextColor(Color);
	if(ColorChange == 1) {
		GetDlgItem(IDC_EDIT_SEND)->Invalidate();
		GetDlgItem(IDC_LIST1)->Invalidate();
		ColorChange = 0;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
