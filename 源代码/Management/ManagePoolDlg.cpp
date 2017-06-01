// ManagePoolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "ManagePoolDlg.h"
#include "ManageAllDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManagePoolDlg dialog


CManagePoolDlg::CManagePoolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManagePoolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManagePoolDlg)
	m_strSubject = _T("");
	//}}AFX_DATA_INIT
}


void CManagePoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManagePoolDlg)
	DDX_Control(pDX, IDC_LIST_POOL, m_listPool);
	DDX_Text(pDX, IDC_EDIT_SUBJECT, m_strSubject);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManagePoolDlg, CDialog)
	//{{AFX_MSG_MAP(CManagePoolDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManagePoolDlg message handlers

BOOL CManagePoolDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CManageAllDlg *parent = (CManageAllDlg *)GetParent();
	pDB = parent->pDB;

	//初始化List控件的栏目
	m_listPool.InsertColumn(0,"ID",LVCFMT_LEFT,50,-1);
	m_listPool.InsertColumn(1,"科目名称",LVCFMT_LEFT,115,-1);
	m_listPool.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	InitPoolList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CManagePoolDlg::InitPoolList()
{
	m_listPool.DeleteAllItems();
	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL = "select * from tbTableName order by ID";
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
	{
		int indexofList = 0;
		CString strID;
		CString strName;
		while(!(pTableRs->IsEOF()))
		{
			pTableRs->GetFieldValue("ID",strID);
			pTableRs->GetFieldValue("ChineseName",strName);
			CString no;
			no.Format(_T("%d"),indexofList+1);
			m_listPool.InsertItem(indexofList,no);
			m_listPool.SetItemText(indexofList,1,strName);
			indexofList+=1;

			pTableRs->MoveNext();
		}
		pTableRs->Close();
		delete(pTableRs);
		return TRUE;
	}		
	if(pTableRs)
		delete(pTableRs);
	return FALSE;
}

void CManagePoolDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_strSubject.IsEmpty())
	{
		AfxMessageBox("请输入新建题库的科目名称!");
		return;
	}
	int count = m_listPool.GetItemCount();
	for(int i = 0 ; i < count ; i++)
		if(m_listPool.GetItemText(i,1) == m_strSubject)
		{
			AfxMessageBox("已经存在的科目!");
			return;
		}
	
	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL = "select * from tbTableName order by ID";
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTableRs->IsOpen())
	{
		if(count != 0)
		{
			pTableRs->MoveLast();
			CString last_no;
			pTableRs->GetFieldValue("ID",last_no);
			count = atoi(last_no); 
		}
		
		//得到EnglishName
		CString strEnglishName = "tb";
		CString str;
		str.Format(_T("%d"),count+1);
		strEnglishName += str;
		
		CString strPaperName = "tbPaper";
		strPaperName += str;
		
		CString strExistName = "tbExist";
		strExistName += str;
		
		if(CreateNewTable(strEnglishName,strPaperName,strExistName))
		{
			pTableRs->AddNew();
			pTableRs->SetFieldValue("ID",count+1);
			pTableRs->SetFieldValue("ChineseName",m_strSubject);		
			pTableRs->SetFieldValue("EnglishName",strEnglishName);
			pTableRs->SetFieldValue("PaperName",strPaperName);
			pTableRs->SetFieldValue("ExistName",strExistName);
			pTableRs->Update();
			
			m_strSubject.Empty();
			UpdateData(FALSE);
		}	
		
		pTableRs->Close();
	}
	if(pTableRs)
		delete(pTableRs);
	InitPoolList();
}

//+++++++++++++++建立新表++++++++++++++++
BOOL CManagePoolDlg::CreateNewTable(CString tablename,CString papername,CString existname)
{
	try
	{
		pDB->BeginTransaction();
		CString strSQL;
		strSQL.Format("create table %s(ID nvarchar(12) not null primary key,Type nvarchar(10) not null,Difficulty nvarchar(10),Chapter nvarchar(10),Content text not null,Answer text)",tablename);
		pDB->Execute(strSQL);
		strSQL.Format("create table %s(ID nvarchar(50) not null primary key,方案ID nvarchar(50) not null,题目ID text not null,题目分值 text not null,题目答案 text not null,内容 text not null,答案 text not null,创建时间 datetime not null,创建人 nvarchar(20) not null)",papername);
		pDB->Execute(strSQL);
		strSQL.Format("create table %s(ID nvarchar(5) not null primary key,内容 text not null,答案 text,创建时间 datetime not null,创建人 nvarchar(20) not null)",existname);
		pDB->Execute(strSQL);
	    pDB->CommitTransaction();
	}
	catch(_com_error e)
	{
		pDB->RollbackTransaction();
		AfxMessageBox(e.ErrorMessage());
		return FALSE;
	}
	return TRUE;
}

BOOL CManagePoolDlg::TableIsEmpty(CString tablename)
{
	CADORecordset* pRs;
	pRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from %s",tablename);
	pRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pRs->IsOpen() && pRs->GetRecordCount() <= 0)
	{
		pRs->Close();
		delete pRs;
		return TRUE;
	}
	if(pRs)
		delete pRs;
	return FALSE;
}
/*
void CManagePoolDlg::UpdateOthers(CString old_id)
{
	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbTableName order by ID");
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	int id = atol(old_id);	
	CString strID;
	if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
	{	
		pTableRs->MoveFirst();
		while(!(pTableRs->IsEOF()))
		{			
			pTableRs->GetFieldValue("ID",strID);
			long r_id = atol(strID);
			CString tb_old = "tb";
			CString paper_old = "tbPaper";
			CString exist_old = "tbExist";
			tb_old += strID;
			paper_old += strID;
			exist_old += strID;
			if(r_id > id)
			{	
				r_id--;
				strID.Format(_T("%ld"),r_id);
				CString tb_name = "tb";
				CString paper_name = "tbPaper";
				CString exist_name = "tbExist";
				tb_name += strID;
				paper_name += strID;
				exist_name += strID;
				pTableRs->SetFieldValue("ID",strID);
				pTableRs->Update();
//select * into %s from %s
				CString strSql;
				strSql.Format("create table %s as select * from %s",tb_name,tb_old);
				pDB->Execute(strSQL);
				strSql.Format("create table %s as select * from %s",paper_name,paper_old);
				pDB->Execute(strSQL);
				strSql.Format("create table %s as select * from %s",exist_name,exist_old);
				pDB->Execute(strSQL);
				strSQL.Format("drop table %s",tb_old);
				pDB->Execute(strSQL);
				strSQL.Format("drop table %s",paper_old);
				pDB->Execute(strSQL);
				strSQL.Format("drop table %s",exist_old);
				pDB->Execute(strSQL);
			}
			pTableRs->MoveNext();
		}
		pTableRs->Close();
	}
	delete pTableRs;
}*/

void CManagePoolDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	int sel = m_listPool.GetSelectionMark();
	if(sel < 0)
		return;
	BOOL IsCanDelete = FALSE;
	CString strChineseName = m_listPool.GetItemText(sel,1);
	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbTableName where ChineseName='%s'",strChineseName);
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	CString strID,strEnglishName,strPaperName,strExistName;
	if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
	{
		pTableRs->GetFieldValue("ID",strID);
		pTableRs->GetFieldValue("EnglishName",strEnglishName);
		pTableRs->GetFieldValue("PaperName",strPaperName);
		pTableRs->GetFieldValue("ExistName",strExistName);
		if(TableIsEmpty(strEnglishName) && TableIsEmpty(strPaperName) && TableIsEmpty(strExistName))
			IsCanDelete = TRUE;
		pTableRs->Close();
		delete(pTableRs);
	}
	else
	{
		AfxMessageBox("无法删除题库!");
		delete pTableRs;
		return;
	}
		
	if(IsCanDelete)
	{
		CString strDelete = "要删除[";
		strDelete += strChineseName;
		strDelete += "]题库?";
		if(MessageBox(strDelete,"确认删除",MB_ICONQUESTION|MB_OKCANCEL) ==IDCANCEL)
			return;
		
		try
		{
			pDB->BeginTransaction();
			CString strSQL;
			strSQL.Format("drop table %s",strEnglishName);
			pDB->Execute(strSQL);
			strSQL.Format("drop table %s",strPaperName);
			pDB->Execute(strSQL);
			strSQL.Format("drop table %s",strExistName);
			pDB->Execute(strSQL);
			strSQL.Format("delete from tbTableName where ID='%s'",strID);
			pDB->Execute(strSQL);
//			UpdateOthers(strID);
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
	InitPoolList();
}
