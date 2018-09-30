// ChatClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"

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
// CChatClientDlg dialog

CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatClientDlg)
	m_strIP = _T("");
	m_strSend = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatClientDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialog)
	//{{AFX_MSG_MAP(CChatClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_RECEIVE, OnReceive)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CChatClientDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CChatClientDlg::OnBnClickedButtonColor)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatClientDlg message handlers

BOOL CChatClientDlg::OnInitDialog()
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

	//������ ��Ʈ ���
	m_Combo.AddString(_T("����ü"));
	m_Combo.AddString(_T("�ü�ü"));
	m_Combo.AddString(_T("����ü"));
	m_Combo.SetCurSel(0);
	font1.CreateFont(12, 7, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("����ü"));
	font2.CreateFont(12, 7, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("�ü�ü"));
	font3.CreateFont(12, 7, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("����ü"));

	//���� ������ ���� ���� �ʱ�ȭ
	ColorChange = 0;
	color = RGB(0, 0, 0);

	//�弳 ���͸� ���� �ʱ�ȭ
	checklist[0] = "��õ";
	checklist[1] = "���";
	checklist[2] = "School";
	chatNo = "����� ����Ͽ� ������ �� �����ϴ�.";
	check = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatClientDlg::OnPaint() 
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
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChatClientDlg::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here
	//����
	UpdateData(TRUE);
	m_socCom.Create();
	// IP �ּҿ� ��Ʈ ��ȣ�� ����
	m_socCom.Connect(m_strIP, 5000);
	m_socCom.Init(this->m_hWnd);
}

LPARAM CChatClientDlg::OnReceive(UINT wParam, LPARAM lParam)

{
	// ���ӵ� ������ �����Ͱ� ����������
	
	char pTmp[256];
	CString strTmp;
	memset(pTmp, '\0', 256);
	
	// �����͸� pTmp�� �޴´�.
	m_socCom.Receive(pTmp, 256);
	for(int i = 0; i < 3; i++) {
		check = strstr(pTmp, checklist[i]);
		if(check != 0) break;
	}
	if(check != 0) {
		strTmp.Format("Server: %s", chatNo);
	} else
		strTmp.Format("Server: %s", pTmp);
	
	// ����Ʈ�ڽ��� �����ش�.
	int i = m_list.GetCount();
	m_list.InsertString(i, strTmp);
	m_list.SetTopIndex(m_list.GetCount() - 1);
	return TRUE;
}


void CChatClientDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CChatClientDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char pTmp[256];
	CString strTmp;
	// pTmp�� ������ ������ �Է�
	memset(pTmp, '\0', 256);
	strcpy(pTmp, m_strSend);
	// ����
	m_socCom.Send(pTmp, 256);
	
	// ������ �����͵� ����Ʈ�ڽ��� �����ش�
	for(int i = 0; i < 3; i++) {
		check = strstr(pTmp, checklist[i]);
		if(check != 0) break;
	}
	if(check != 0) {
		strTmp.Format("Client: %s", chatNo);
	} else
		strTmp.Format("Client: %s", pTmp);
	int i = m_list.GetCount();
	m_list.InsertString(i, strTmp);
	SetDlgItemText(IDC_EDIT_SEND, 0);
	m_list.SetTopIndex(m_list.GetCount() - 1);
}

void CChatClientDlg::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

void CChatClientDlg::OnBnClickedButtonColor()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlg(color);
	if(dlg.DoModal() == IDCANCEL)
		return;
	color = dlg.GetColor();
	ColorChange = 1;
}

HBRUSH CChatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if(pWnd->GetSafeHwnd() == GetDlgItem(IDC_EDIT_SEND)->GetSafeHwnd())
		pDC->SetTextColor(color);
	if(pWnd->GetSafeHwnd() == GetDlgItem(IDC_LIST1)->GetSafeHwnd())
		pDC->SetTextColor(color);
	if(ColorChange == 1) {
		GetDlgItem(IDC_EDIT_SEND)->Invalidate();
		GetDlgItem(IDC_LIST1)->Invalidate();
		ColorChange = 0;
	}

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
