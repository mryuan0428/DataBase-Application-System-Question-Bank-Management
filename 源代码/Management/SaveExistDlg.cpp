// SaveExistDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "SaveExistDlg.h"
#include "PaperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveExistDlg dialog


CSaveExistDlg::CSaveExistDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveExistDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveExistDlg)
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	strContent = "";
	ID = "";
	IsSave = FALSE;
}

CSaveExistDlg::~CSaveExistDlg()
{
}

void CSaveExistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveExistDlg)
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveExistDlg, CDialog)
	//{{AFX_MSG_MAP(CSaveExistDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveExistDlg message handlers

BOOL CSaveExistDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CPaperDlg *parent = (CPaperDlg *)GetParent();
	pDB = parent->pDB;
	strUsername = parent->GetUsername();
	m_strTitle = "确认将该试卷导入到：";
	m_strTitle += strTablename;
	m_strTitle += "试卷库";
	UpdateData(FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CSaveExistDlg::FindtbExist()
{
	CString strExistName = "";
	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbTableName where ChineseName='%s' order by ID",strTablename);
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
	{
		pTableRs->GetFieldValue("ExistName",strExistName);		
		pTableRs->Close();
	}		
	if(pTableRs)
		delete(pTableRs);
	return strExistName;
}

void CSaveExistDlg::OnOK() 
{
	// TODO: Add extra validation here
    CString strDate;
	GetDlgItem(IDC_DATETIMEPICKER_CREATE)->GetWindowText(strDate);

	CString strExistName = FindtbExist();
	ExistTable_name = strExistName;
	CADORecordset* pExistRs;
	pExistRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from %s order by ID",strExistName);
	pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	
	if(pExistRs->IsOpen())
	{
		int nCount = pExistRs->GetRecordCount();
		
		CString strNum;
		strNum.Format(_T("%d"),nCount+1);
		int n = strNum.GetLength();
		for(int i = 0 ; i < 5-n ; i++)
			ID += "0";
		ID += strNum;
		
		//添加新试卷
		pExistRs->AddNew();
		pExistRs->SetFieldValue("ID",ID);
		pExistRs->SetFieldValue("内容",strContent);
		pExistRs->SetFieldValue("创建时间",strDate);
		pExistRs->SetFieldValue("创建人",strUsername);
		pExistRs->Update();
		IsSave = TRUE;
		pExistRs->Close();
	}
	delete pExistRs;			
	CDialog::OnOK();
}
