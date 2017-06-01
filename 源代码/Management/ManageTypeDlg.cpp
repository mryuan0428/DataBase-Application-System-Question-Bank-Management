// ManageTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "ManageTypeDlg.h"
#include "ManageAllDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManageTypeDlg dialog


CManageTypeDlg::CManageTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManageTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManageTypeDlg)
	m_strType = _T("");
	//}}AFX_DATA_INIT
	
}


void CManageTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManageTypeDlg)
	DDX_Control(pDX, IDC_LIST_TYPE, m_listType);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_strType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManageTypeDlg, CDialog)
	//{{AFX_MSG_MAP(CManageTypeDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManageTypeDlg message handlers

BOOL CManageTypeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CManageAllDlg *parent = (CManageAllDlg *)GetParent();
	pDB = parent->pDB;

	//初始化List控件的栏目
	m_listType.InsertColumn(0,"ID",LVCFMT_LEFT,50,-1);
	m_listType.InsertColumn(1,"题型名称",LVCFMT_LEFT,115,-1);
	m_listType.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	InitTypeList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CManageTypeDlg::InitTypeList()
{
	m_listType.DeleteAllItems();
	CADORecordset* pTypeRs;
	pTypeRs = new CADORecordset(pDB); 
	CString strSQL = "select * from tbType order by ID";
	pTypeRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTypeRs->IsOpen() && pTypeRs->GetRecordCount() > 0)
	{
		int indexofList = 0;
		CString strID;
		CString strName;
		while(!(pTypeRs->IsEOF()))
		{
			pTypeRs->GetFieldValue("ID",strID);
			pTypeRs->GetFieldValue("Name",strName);
			
			m_listType.InsertItem(indexofList,strID);
			m_listType.SetItemText(indexofList,1,strName);
			indexofList+=1;

			pTypeRs->MoveNext();
		}
		pTypeRs->Close();
		delete(pTypeRs);
		return TRUE;
	}		
	if(pTypeRs)
		delete(pTypeRs);
	return FALSE;
}

void CManageTypeDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_strType.IsEmpty())
	{
		AfxMessageBox("请输入新添加的题型名称!");
		return;
	}
	int count = m_listType.GetItemCount();
	for(int i = 0 ; i < count ; i++)
	{
		if(m_listType.GetItemText(i,1) == m_strType)
		{
			AfxMessageBox("已经存在的题型!");
			return;
		}
	}
	CADORecordset* pTypeRs;
	pTypeRs = new CADORecordset(pDB); 
	CString strSQL = "select * from tbType order by ID";
	pTypeRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTypeRs->IsOpen())
	{	
		pTypeRs->MoveLast();
		CString strLast;
		pTypeRs->GetFieldValue("ID",strLast);
		count = atoi(strLast);
		pTypeRs->AddNew();
		pTypeRs->SetFieldValue("ID",count+1);
		pTypeRs->SetFieldValue("Name",m_strType);		
		pTypeRs->Update();
		
		m_strType.Empty();
		UpdateData(FALSE);
		pTypeRs->Close();
	}		
	if(pTypeRs)
		delete(pTypeRs);
	InitTypeList();
}

BOOL CManageTypeDlg::TypeIsExist(int i,CString strName)
{
	CString strNo;
	strNo.Format(_T("%d"),i);
	CString strTableName = "tb";
	strTableName += strNo;
	CADORecordset* pRs;
	pRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from %s where Type='%s'",strTableName,strName);
	pRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pRs->IsOpen() && pRs->GetRecordCount() > 0)
	{
		pRs->Close();
		delete pRs;
		return TRUE;
	}
	if(pRs)
		delete pRs;
	return FALSE;
}

void CManageTypeDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	int sel = m_listType.GetSelectionMark();
	if(sel < 0)
		return;
	BOOL IsCanDelete = FALSE;
	CString strID = m_listType.GetItemText(sel,0);
	CString strName = m_listType.GetItemText(sel,1);
	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbTableName");
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTableRs->IsOpen())
	{
		int count = pTableRs->GetRecordCount();
		for(int i = 0 ; i < count ; i++)
			if(TypeIsExist(i+1,strName))
			{
				IsCanDelete = FALSE;
				AfxMessageBox("请先确认该题型未在试题库中出现再进行删除!");
				return;
			}
		IsCanDelete = TRUE;
		pTableRs->Close();
	}
	delete pTableRs;
	
	if(IsCanDelete)
	{
		CString strDelete = "要删除[";
		strDelete += strName;
		strDelete += "]题型?";
		if(MessageBox(strDelete,"确认删除",MB_ICONQUESTION|MB_OKCANCEL) ==IDCANCEL)
			return;
		
		UpdateData(FALSE);
		
		try
		{
			pDB->BeginTransaction();
			CString strSQL;
			strSQL.Format("delete from tbType where ID='%s'",strID);
			pDB->Execute(strSQL);
			pDB->CommitTransaction();
		}
		catch(_com_error e)
		{
			pDB->RollbackTransaction();
			AfxMessageBox(e.ErrorMessage());
		}
	}
	else
	{
		AfxMessageBox("请先确认该科目试题库及试卷库均清空再进行删除!");
	}
	InitTypeList();
}
