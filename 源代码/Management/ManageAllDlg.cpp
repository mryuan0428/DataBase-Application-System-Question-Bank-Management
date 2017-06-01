// ManageAllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "ManageAllDlg.h"
#include "ManagementDlg.h"
#include "PaperDlg.h"             //抽取现有试卷
#include "AutoMakeupDlg.h"        //自动组卷
#include "PersonMakeupDlg.h"      //手动组卷
#include "ManagePaperDlg.h"       //管理试卷
#include "QuestionDlg.h"
#include "ManageTypeDlg.h"        //题型管理
#include "ManagePoolDlg.h"        //题库管理
#include "PasswordDlg.h"          //修改密码

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManageAllDlg dialog


CManageAllDlg::CManageAllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManageAllDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManageAllDlg)
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
}


void CManageAllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManageAllDlg)
	DDX_Control(pDX, IDC_BUTTON_MANAGETYPE, m_buttonType);
	DDX_Control(pDX, IDC_BUTTON_QUESTION, m_buttonQuestion);
	DDX_Control(pDX, IDC_BUTTON_POOL, m_buttonPool);
	DDX_Control(pDX, IDC_BUTTON_PERSON, m_buttonPerson);
	DDX_Control(pDX, IDC_BUTTON_PAPER, m_buttonPaper);
	DDX_Control(pDX, IDC_BUTTON_MANAGEPAPER, m_buttonManagepaper);
	DDX_Control(pDX, IDC_BUTTON_AUTO, m_buttonAuto);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManageAllDlg, CDialog)
	//{{AFX_MSG_MAP(CManageAllDlg)
	ON_BN_CLICKED(IDC_BUTTON_PAPER, OnButtonPaper)
	ON_BN_CLICKED(IDC_BUTTON_QUESTION, OnButtonQuestion)
	ON_BN_CLICKED(IDC_BUTTON_AUTO, OnButtonAuto)
	ON_BN_CLICKED(IDC_BUTTON_PERSON, OnButtonPerson)
	ON_BN_CLICKED(IDC_BUTTON_PASSWORD, OnButtonPassword)
	ON_BN_CLICKED(IDC_BUTTON_MANAGEPAPER, OnButtonManagepaper)
	ON_BN_CLICKED(IDC_BUTTON_POOL, OnButtonPool)
	ON_BN_CLICKED(IDC_BUTTON_MANAGETYPE, OnButtonManagetype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManageAllDlg message handlers

void CManageAllDlg::OnButtonPaper() 
{
	// TODO: Add your control notification handler code here
	CPaperDlg paperDlg;
	ShowWindow(SW_HIDE);
	paperDlg.DoModal();
	ShowWindow(SW_SHOW);
}

BOOL CManageAllDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CManagementDlg *parent = (CManagementDlg *)GetParent();
	pDB = parent->pDB;
	strUsername = parent->GetUsername();
	strPurview = parent->GetPurview();
	strSubject = parent->GetSubject();

	m_strTitle = "欢迎";
	m_strTitle += strPurview;
	m_strTitle += strUsername;
	m_strTitle += "登录系统";
	UpdateData(FALSE);
	if(strPurview == "普通管理员")
	{
		m_buttonPool.EnableWindow(FALSE);
	}
	if(strPurview == "一般用户")
	{
		m_buttonManagepaper.EnableWindow(FALSE);
		m_buttonQuestion.EnableWindow(FALSE);
		m_buttonPool.EnableWindow(FALSE);
		m_buttonType.EnableWindow(FALSE);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CManageAllDlg::OnButtonQuestion() 
{
	// TODO: Add your control notification handler code here
	CQuestionDlg questionDlg;
	ShowWindow(SW_HIDE);
	questionDlg.DoModal();
	ShowWindow(SW_SHOW);
}

void CManageAllDlg::OnButtonAuto() 
{
	// TODO: Add your control notification handler code here
	CAutoMakeupDlg automakeupDlg;
	ShowWindow(SW_HIDE);
	automakeupDlg.DoModal();
	ShowWindow(SW_SHOW);
}

void CManageAllDlg::OnButtonPerson() 
{
	// TODO: Add your control notification handler code here
	CPersonMakeupDlg personmakeupDlg;
	ShowWindow(SW_HIDE);
	personmakeupDlg.DoModal();
	ShowWindow(SW_SHOW);
}

void CManageAllDlg::OnButtonPassword() 
{
	// TODO: Add your control notification handler code here
	CPasswordDlg passwordDlg;
	ShowWindow(SW_HIDE);
	passwordDlg.DoModal();
	ShowWindow(SW_SHOW);
}

void CManageAllDlg::OnButtonManagepaper() 
{
	// TODO: Add your control notification handler code here
	CManagePaperDlg managepaperDlg;
	ShowWindow(SW_HIDE);
	managepaperDlg.DoModal();
	ShowWindow(SW_SHOW);
}

void CManageAllDlg::OnButtonPool() 
{
	// TODO: Add your control notification handler code here
	CManagePoolDlg managepoolDlg;
	ShowWindow(SW_HIDE);
	managepoolDlg.DoModal();
	ShowWindow(SW_SHOW);
}

void CManageAllDlg::OnButtonManagetype() 
{
	// TODO: Add your control notification handler code here
	CManageTypeDlg managetypeDlg;
	ShowWindow(SW_HIDE);
	managetypeDlg.DoModal();
	ShowWindow(SW_SHOW);
}
