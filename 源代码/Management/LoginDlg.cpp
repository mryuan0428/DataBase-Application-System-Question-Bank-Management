// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "LoginDlg.h"
#include "ManagementDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_password = _T("");
	m_username = _T("");
	m_strPurview = _T("");
	//}}AFX_DATA_INIT
	strUsername = "";
	strPurview = "";
	strSubject = "";
	wrong_num = 0;
}

CLoginDlg::~CLoginDlg()
{
	if(pRs && pRs->IsOpen())
		pRs->Close();
	if(pRs)
		delete(pRs);
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	DDX_CBString(pDX, IDC_COMBO_PURVIEW, m_strPurview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(m_strPurview.IsEmpty())
	{
		AfxMessageBox("请先选择登录方式!");
		return;
	}
	if(m_username.IsEmpty() || m_password.IsEmpty())
	{
		AfxMessageBox("用户名或密码未填写!");
		return;
	}

	CString strSql;
	strSql.Format("SELECT * FROM tbLogin where Username='%s'",m_username);
	pRs->Open(strSql,CADORecordset.openQuery);
	if(!pRs->IsOpen())
	   return;
    if(pRs->GetRecordCount()<=0)
	{
		AfxMessageBox("用户不存在!");
		wrong_num++;
		if(wrong_num == 3)
			OnCancel();
		return;
	}
	pRs->MoveFirst();
	CString strPassword;
	
	pRs->GetFieldValue("Username",strUsername);
	pRs->GetFieldValue("Password",strPassword);
	pRs->GetFieldValue("Purview",strPurview);
	pRs->GetFieldValue("Subject",strSubject);
	if(m_strPurview != strPurview)
	{
		AfxMessageBox("用户不存在!");
		return;
	}
	if(m_password != strPassword)
	{
		AfxMessageBox("密码不正确，请重新输入!");
		m_password.Empty();
		UpdateData(FALSE);
		wrong_num++;
		if(wrong_num == 3)
			OnCancel();
		return;
	}
	CDialog::OnOK();
}

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CManagementDlg *parent = (CManagementDlg *)GetParent();
	pDB = parent->pDB;
	pRs = new CADORecordset(pDB);
	m_strPurview = "系统管理员";
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}