// AddandeditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "AddandeditDlg.h"
#include "QuestionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddandeditDlg dialog


CAddandeditDlg::CAddandeditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddandeditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddandeditDlg)
	m_chapter = _T("");
	m_difficulty = _T("");
	m_type = _T("");
	m_answer = _T("");
	m_content = _T("");
	m_title = _T("");
	//}}AFX_DATA_INIT

	IsContentEdit = FALSE;
	IsAttributesEdit = FALSE;
}

CAddandeditDlg::~CAddandeditDlg()
{
	if(pTypeRs && pTypeRs->IsOpen())
		pTypeRs->Close();
	if(pTypeRs)
		delete(pTypeRs);
}

void CAddandeditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddandeditDlg)
	DDX_Control(pDX, IDC_COMBO_DIFFICULTY, m_comboDifficulty);
	DDX_Control(pDX, IDC_COMBO_CHAPTER, m_comboChapter);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboType);
	DDX_CBString(pDX, IDC_COMBO_CHAPTER, m_chapter);
	DDX_CBString(pDX, IDC_COMBO_DIFFICULTY, m_difficulty);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_type);
	DDX_Text(pDX, IDC_EDIT_ANSWER, m_answer);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_content);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddandeditDlg, CDialog)
	//{{AFX_MSG_MAP(CAddandeditDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddandeditDlg message handlers

BOOL CAddandeditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CQuestionDlg *parent = (CQuestionDlg *)GetParent();
	pDB = parent->pDB;
	pTypeRs = new CADORecordset(pDB); 

	if(parent->m_AddorEdit)
		m_title = "请添加新题目:";
	else
		m_title = "请修改题目:";
	UpdateData(FALSE);

	
	CString strSQL = "select * from tbType order by ID";
	pTypeRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTypeRs->IsOpen())
	{
		CString strName;
		while(!(pTypeRs->IsEOF()))
		{
			pTypeRs->GetFieldValue("Name",strName);
			int count = m_comboType.GetCount();
			m_comboType.InsertString(count,strName);
			pTypeRs->MoveNext();
		}
		pTypeRs->MoveFirst();
	}
	
	if(!parent->m_AddorEdit)
	{
		m_type = parent->m_type;
		m_difficulty = parent->m_difficulty;
		m_chapter = parent->m_chapter;
		m_content = parent->m_content;
		m_answer = parent->m_answer;
		UpdateData(FALSE);
	}
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddandeditDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(m_type.IsEmpty() || m_content.IsEmpty())
	{
		AfxMessageBox("题目类型和内容必须填写!");
		return;
	}

	CQuestionDlg *parent = (CQuestionDlg *)GetParent();
	if(!parent->m_AddorEdit)
	{
		if(strcmp(m_type,parent->m_type) || strcmp(m_difficulty,parent->m_difficulty) || strcmp(m_chapter,parent->m_chapter))
			IsAttributesEdit = TRUE;
		if(strcmp(m_content,parent->m_content) || strcmp(m_answer,parent->m_answer))
			IsContentEdit = TRUE;
	}	
	CDialog::OnOK();
}
