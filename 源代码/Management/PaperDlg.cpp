// PaperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "PaperDlg.h"
#include "ManageAllDlg.h"
#include "AutoMakeupDlg.h"
#include "PersonMakeupDlg.h"
#include "SaveExistDlg.h"
#include "ImportDlg.h"
#include "msword.h"
#include "BrowseAllDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString pDifficulty_Chinese[5] = {"易","较易","中等","较难","难"};
/////////////////////////////////////////////////////////////////////////////
// CPaperDlg dialog


CPaperDlg::CPaperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPaperDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaperDlg)
	m_checkDate = FALSE;
	m_strCreateperson = _T("");
	m_strSubject = _T("");
	m_strID = _T("");
	//}}AFX_DATA_INIT
	Exist_ID = _T("");
	ExistTable_name = _T("");
	Now_ID = _T("");
}

void CPaperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaperDlg)
	DDX_Control(pDX, IDC_LIST_PAPER, m_listPaper);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_DateTo);
	DDX_Control(pDX, IDC_LIST_QUESTION, m_listQuestion);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_DateFrom);
	DDX_Control(pDX, IDC_COMBO_SUBJECT, m_comboSubject);
	DDX_Control(pDX, IDC_COMBO_CREATEPERSON, m_comboCreateperson);
	DDX_Control(pDX, IDC_TREE_PAPER, m_paperTree);
	DDX_Control(pDX, IDC_BUTTON_INANSWER, m_buttonAnswer);
	DDX_Check(pDX, IDC_CHECK_DATE, m_checkDate);
	DDX_CBString(pDX, IDC_COMBO_CREATEPERSON, m_strCreateperson);
	DDX_CBString(pDX, IDC_COMBO_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPaperDlg, CDialog)
	//{{AFX_MSG_MAP(CPaperDlg)
	ON_BN_CLICKED(IDC_BUTTON_IN, OnButtonIn)
	ON_BN_CLICKED(IDC_BUTTON_INANSWER, OnButtonInanswer)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBJECT, OnSelchangeComboSubject)
	ON_NOTIFY(NM_CLICK, IDC_TREE_PAPER, OnClickTreePaper)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_PAPER, OnSelchangedTreePaper)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PAPER, OnClickListPaper)
	ON_BN_CLICKED(IDC_CHECK_DATE, OnCheckDate)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_ONLYQUERY, OnButtonOnlyquery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaperDlg message handlers

BOOL CPaperDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CManageAllDlg *parent = (CManageAllDlg *)GetParent();
	pDB = parent->pDB;
	CString strPurview = parent->GetPurview();
	strUsername = parent->GetUsername();
	if(strPurview == "系统管理员")
	{
		Purview = TRUE;
	}
	else
		Purview = FALSE;             //只能查看自己科目的试卷

	//初始化List控件的栏目
	m_listPaper.InsertColumn(0,"试卷ID",LVCFMT_LEFT,177,-1);
	m_listPaper.InsertColumn(1,"试卷创建时间",LVCFMT_LEFT,120,-1);
	m_listPaper.InsertColumn(2,"试卷创建者",LVCFMT_LEFT,100,-1);
	m_listPaper.InsertColumn(3,"试卷类型",LVCFMT_LEFT,100,-1);
	m_listPaper.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_listQuestion.InsertColumn(0,"试卷ID",LVCFMT_LEFT,167,-1);
	m_listQuestion.InsertColumn(1,"ID",LVCFMT_LEFT,100,-1);
	m_listQuestion.InsertColumn(2,"题型",LVCFMT_LEFT,100,-1);
	m_listQuestion.InsertColumn(3,"难度",LVCFMT_LEFT,60,-1);
	m_listQuestion.InsertColumn(4,"所属章节",LVCFMT_LEFT,70,-1);	
	m_listQuestion.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	InitComboSubject();
	
	//设置Date Time Picker控件的日期显示格式
	m_DateFrom.SetFormat("yyyyMMdd");
	m_DateTo.SetFormat("yyyyMMdd");
	//如期查询初始化时是不选中的，设置起始日期的控件不可用
	m_checkDate = FALSE;
	m_DateFrom.EnableWindow(FALSE);
	m_DateTo.EnableWindow(FALSE);


	//初始化数型控件
		

	m_buttonAnswer.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//初始化选择科目combo(非系统管理员只能查看自己具有权限的科目)
BOOL CPaperDlg::InitComboSubject()
{
	CManageAllDlg *parent = (CManageAllDlg *)GetParent();
	pDB = parent->pDB;
	if(Purview)
	{
		CADORecordset* pTableRs;
		pTableRs = new CADORecordset(pDB); 
		CString strSQL = "select * from tbTableName order by ID";
		pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
		{
			CString strName;
			while(!(pTableRs->IsEOF()))
			{
				pTableRs->GetFieldValue("ChineseName",strName);
				int count = m_comboSubject.GetCount();
				m_comboSubject.InsertString(count,strName);
				pTableRs->MoveNext();
			}
			pTableRs->Close();
		}
		if(pTableRs)
			delete(pTableRs);
	}
	else
	{
		CString strSubject = parent->GetSubject();
		if(strSubject.IsEmpty())
			return FALSE;
		int len = strSubject.GetLength();
		int i = 0;
		while(i < len)
		{
			char c = strSubject.GetAt(i);
			char sub[20];
			int j = 0;
			while(c != ',' && i < len)
			{
				sub[j] = c;
				i++;
				j++;
				if(i < len)
					c = strSubject.GetAt(i);			
			}
			i++;
			sub[j] = '\0';
			CString strsub = sub;
			m_comboSubject.AddString(strsub);			
		}
	}
	return TRUE;
}

//初始化创建者combo
BOOL CPaperDlg::InitComboCreate()
{
	int count = m_comboCreateperson.GetCount();
	for(int i = 0 ; i < count ; i++)
		m_comboCreateperson.DeleteString(0);
	m_comboCreateperson.AddString("");
	CString strChineseName = m_strSubject;
	CString Username;
	
	CString strPaperName = FindtbPaper(strChineseName);
	CADORecordset *pPaperRs = new CADORecordset(pDB);
	CString strSql;
	strSql.Format("select * from %s order by ID",strPaperName);
	pPaperRs->Open(strSql,CADORecordset.openQuery);
	if(pPaperRs->IsOpen() && pPaperRs->GetRecordCount() >=0)
	{
		while(!pPaperRs->IsEOF())
		{
			pPaperRs->GetFieldValue("创建人",Username);
			int n = m_comboCreateperson.FindString(0,Username);
			if(n == -1)
				m_comboCreateperson.AddString(Username);
			pPaperRs->MoveNext();				
		}
		pPaperRs->Close();
	}
	delete pPaperRs;
	
	CString strExistName = FindtbExist(strChineseName);
	CADORecordset *pExistRs = new CADORecordset(pDB);
	strSql.Format("select * from %s order by 创建人",strExistName);
	pExistRs->Open(strSql,CADORecordset.openQuery);
	if(pExistRs->IsOpen() && pExistRs->GetRecordCount() >=0)
	{
		while(!pExistRs->IsEOF())
		{
			pExistRs->GetFieldValue("创建人",Username);
			int n = m_comboCreateperson.FindString(0,Username);
			if(n == -1)
				m_comboCreateperson.AddString(Username);
			pExistRs->MoveNext();				
		}
		pExistRs->Close();
	}
	delete pExistRs;	
	return TRUE;
}


//找到存放已组试卷的tb名
CString CPaperDlg::FindtbPaper(CString strChineseName)
{
	CString strPaperName = "";
	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbTableName where ChineseName='%s' order by ID",strChineseName);
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
	{		
		pTableRs->GetFieldValue("PaperName",strPaperName);	
		pTableRs->Close();
	}
	if(pTableRs)
		delete(pTableRs);
	return strPaperName;
}

//找到存放成套试卷的tb名
CString CPaperDlg::FindtbExist(CString strChineseName)
{
	CString strExistName = "";
	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbTableName where ChineseName='%s' order by ID",strChineseName);
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

//初始化试卷列表
BOOL CPaperDlg::InitPaperList()
{
	m_listPaper.DeleteAllItems();
	int indexofList = 0;
	CString strChineseName = m_strSubject;
	CString strPaperName = FindtbPaper(strChineseName);
	CString strExistName = FindtbExist(strChineseName);
	//加入已组试卷
	CADORecordset* pPaperRs;
	pPaperRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from %s order by 方案ID",strPaperName);
	pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	if(pPaperRs->IsOpen() && pPaperRs->GetRecordCount() > 0)
	{
		CString strID,strCreatetime,strCreateperson;
		while(!pPaperRs->IsEOF())
		{
			pPaperRs->GetFieldValue("ID",strID);
			pPaperRs->GetFieldValue("创建时间",strCreatetime);
			pPaperRs->GetFieldValue("创建人",strCreateperson);

			m_listPaper.InsertItem(indexofList,strID);
			m_listPaper.SetItemText(indexofList,1,strCreatetime);
			m_listPaper.SetItemText(indexofList,2,strCreateperson);
			m_listPaper.SetItemText(indexofList,3,"已组试卷");
			indexofList+=1;

			pPaperRs->MoveNext();
		}
		//题目list
		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);
		pPaperRs->Close();
	}
	if(pPaperRs)
		delete pPaperRs;

	//加入成套导入的试卷
	CADORecordset* pExistRs;
	pExistRs = new CADORecordset(pDB); 
	strSQL.Format("select * from %s order by ID",strExistName);
	pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	if(pExistRs->IsOpen() && pExistRs->GetRecordCount() > 0)
	{
		CString strID,strCreatetime,strCreateperson;
		while(!pExistRs->IsEOF())
		{
			pExistRs->GetFieldValue("ID",strID);
			pExistRs->GetFieldValue("创建时间",strCreatetime);
			pExistRs->GetFieldValue("创建人",strCreateperson);

			m_listPaper.InsertItem(indexofList,strID);
			m_listPaper.SetItemText(indexofList,1,strCreatetime);
			m_listPaper.SetItemText(indexofList,2,strCreateperson);
			m_listPaper.SetItemText(indexofList,3,"成套试卷");
			indexofList+=1;

			pExistRs->MoveNext();
		}
		pExistRs->Close();
	}
	if(pExistRs)
		delete pExistRs;

	//当前选中的试卷
	if(m_listPaper.GetItemCount() > 0)
	{
		Now_ID = m_listPaper.GetItemText(0,0);
	}
	else
		Now_ID = "";

	m_listPaper.SetFocus();
	m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
	return TRUE;
}

//初始化树形列表
BOOL CPaperDlg::InitPaperTree()
{
	m_paperTree.DeleteAllItems();
	CString strChineseName = m_strSubject;
	m_paperTree.ModifyStyle(0,TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|WS_BORDER);
	HTREEITEM hRoot = m_paperTree.InsertItem(_T(strChineseName),0,1);

	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbTableName where ChineseName='%s' order by ID",strChineseName);
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
	{
		CString strEnglishName = "";
		CString strPaperName = "";
		CString strExistName = "";
		
		pTableRs->GetFieldValue("PaperName",strPaperName);
		pTableRs->GetFieldValue("ExistName",strExistName);
		
		HTREEITEM hItem1 = m_paperTree.InsertItem(_T("已组试卷"),0,1,hRoot,TVI_LAST);
		InsertPaperItem(hItem1,strPaperName);

		HTREEITEM hItem2 = m_paperTree.InsertItem(_T("成套试卷"),0,1,hRoot,TVI_LAST);
		InsertExistItem(hItem2,strExistName);
		
		m_paperTree.Expand(hItem1, TVE_EXPAND);
		m_paperTree.Expand(hItem2, TVE_EXPAND);
		
		
		m_paperTree.Expand(hRoot, TVE_EXPAND);
		pTableRs->Close();
		delete pTableRs;
		return TRUE;
	}
	if(pTableRs)
		delete pTableRs;
	return FALSE;
}

//在树形列表中插入已组试卷
BOOL CPaperDlg::InsertPaperItem(HTREEITEM hItem,CString strPaperName)
{
	CADORecordset* pPaperRs;
	pPaperRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from %s order by 方案ID",strPaperName);
	pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	if(pPaperRs->IsOpen() && pPaperRs->GetRecordCount() > 0)
	{
		CString last_ID = "";
		HTREEITEM hItem_child;
		CString strID,strfangID;
		while(!pPaperRs->IsEOF())
		{
			pPaperRs->GetFieldValue("方案ID",strfangID);
			if(strfangID != last_ID)
			{ 
				hItem_child = m_paperTree.InsertItem(_T(strfangID),0,1,hItem,TVI_LAST);
			}
			last_ID = strfangID;
			pPaperRs->GetFieldValue("ID",strID);
			m_paperTree.InsertItem(_T(strID),0,1,hItem_child,TVI_LAST);
			pPaperRs->MoveNext();
		}
		pPaperRs->Close();
		delete pPaperRs;
		return TRUE;
	}
	if(pPaperRs)
		delete pPaperRs;
	return FALSE;
}

//在树形列表中插入成套试卷
BOOL CPaperDlg::InsertExistItem(HTREEITEM hItem,CString strExistName)
{
	CADORecordset* pExistRs;
	pExistRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from %s order by ID",strExistName);
	pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);

	if(pExistRs->IsOpen() && pExistRs->GetRecordCount() > 0)
	{
		CString strID;
		while(!pExistRs->IsEOF())
		{
			pExistRs->GetFieldValue("ID",strID);
			m_paperTree.InsertItem(_T(strID),0,1,hItem,TVI_LAST);
			pExistRs->MoveNext();
		}
		pExistRs->Close();
		delete pExistRs;	
		return TRUE;
	}
	if(pExistRs)
		delete pExistRs;
	return FALSE;
}


//更新List控件,将记录移到第一条  +++++++++++在其他函数中被调用++++++++++
void CPaperDlg::RefreshList(BOOL PaperOrExist,CADORecordset& recordset) 
{	
	CString strType;
	if(PaperOrExist)
		strType = "已组试卷";
	else
		strType = "成套试卷";
	if(!recordset.IsOpen())
	{
		Now_ID = "";
		return;
	}
	if(recordset.GetRecordCount() <= 0)
	{
		Now_ID = "";
		return;
	}
	recordset.MoveFirst();
	CString strID,strCreatetime,strCreateperson;
	int indexofList=0;
	
	while(!(recordset.IsEOF()))
	{
		recordset.GetFieldValue("ID",strID);
		recordset.GetFieldValue("创建时间",strCreatetime);
		recordset.GetFieldValue("创建人",strCreateperson);

		m_listPaper.InsertItem(indexofList,strID);
		m_listPaper.SetItemText(indexofList,1,strCreatetime);
		m_listPaper.SetItemText(indexofList,2,strCreateperson);
		m_listPaper.SetItemText(indexofList,3,strType);
		indexofList+=1;
		recordset.MoveNext();
	}
	recordset.MoveFirst();
	//当前选中的试卷
	if(m_listPaper.GetItemCount() > 0)
	{
		Now_ID = m_listPaper.GetItemText(0,0);
	}
	else
		Now_ID = "";
}

//查找类型
CString CPaperDlg::FindType(CString type)
{
	CString strType = "";
	CADORecordset* pTypeRs;
	pTypeRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbType where ID='%s'",type);
	pTypeRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTypeRs->IsOpen() && pTypeRs->GetRecordCount() > 0)
	{
		pTypeRs->GetFieldValue("Name",strType);
		pTypeRs->Close();
	}
	if(pTypeRs)
		delete(pTypeRs);
	return strType;
}

//查找难度
CString CPaperDlg::FindDifficulty(CString Difficulty)
{
	CString strDifficulty = "";
	if(Difficulty == "00")
		return strDifficulty;
	else
	{
		int i = atoi(Difficulty);
		strDifficulty = pDifficulty_Chinese[i-1];
		return strDifficulty;
	}
}

//查找章节
CString CPaperDlg::FindChapter(CString Chapter)
{
	CString strChapter = "";
	if(Chapter == "00")
		return strChapter;
	else
	{
		strChapter = "第";
		strChapter += Chapter;
		strChapter += "章";
		return strChapter;
	}
}

void CPaperDlg::UpdateQuestionList(CADORecordset &recordset)
{
	if(!recordset.IsOpen())
		return;
	if(recordset.GetRecordCount() <= 0)
		return;
	recordset.MoveFirst();
	CString strID,strQuesID;
	int indexofList=0;
	
	recordset.GetFieldValue("ID",strID);
	recordset.GetFieldValue("题目ID",strQuesID);

	int len = strQuesID.GetLength();
	int i = 0;
	while(i < len)
	{
		char quesID[12];
		int j = 0;
		char c;
		do
		{
			c = strQuesID.GetAt(i);
			if(c != ',')
				quesID[j] = c;
			i++;
			j++;
		}while(i < len && c != ',');
		quesID[j] = '\0';

		CString strNowID = quesID;
		char type[3];
		type[0] = quesID[0];
		type[1] = quesID[1];
		type[2] = '\0';
		CString Type = type;
		CString strType = FindType(Type);

		char difficulty[3];
		difficulty[0] = quesID[2];
		difficulty[1] = quesID[3];
		difficulty[2] = '\0';
		CString Difficulty = difficulty;
		CString strDifficulty = FindDifficulty(Difficulty);

		char chapter[3];
		chapter[0] = quesID[4];
		chapter[1] = quesID[5];
		chapter[2] = '\0';
		CString Chapter = chapter;
		CString strChapter = FindChapter(Chapter);

		m_listQuestion.InsertItem(indexofList,strID);
		m_listQuestion.SetItemText(indexofList,1,strNowID);
		m_listQuestion.SetItemText(indexofList,2,strType);
        m_listQuestion.SetItemText(indexofList,3,strDifficulty);
		m_listQuestion.SetItemText(indexofList,4,strChapter);
		indexofList+=1;
	}
}



void CPaperDlg::OnButtonIn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strContent = "";
	if(m_strSubject.IsEmpty())
		return;
	CLSID clsid;
	HRESULT hr;
	hr=::CLSIDFromProgID(L"Word.Application",&clsid);	//通过ProgID取得CLSID
	if(FAILED(hr))
	{
		AfxMessageBox(_T("没有安装OFFICE!"));
		return;
	}//endif
	
	IUnknown *pUnknown = NULL;
	IDispatch *pDispatch = NULL;
	_Application app = NULL;
	Selection sel = NULL;
	
	//++++++++++打开一个word文档 
	CString strFilename;
	CImportDlg importDlg;
	if(importDlg.DoModal() == IDOK)
		strFilename = importDlg.GetFilename();
	else
		return;

	UpdateData(FALSE);
	//目录
	char name[100];
	strcpy(name,strFilename.GetBuffer(100));
	
	char catalog[1000];
	int indexe = strFilename.ReverseFind('\\');		
	int i;
	for(i = 0 ; i < indexe+1 ; i++)
		catalog[i] = name[i];
	catalog[i] = '\0';
	
	//得到文件名.doc
	CString file = strFilename.Mid(indexe+1);
	
	ShellExecute(NULL,NULL,_T(file),NULL,_T(catalog),NULL);
	
	
	hr=::GetActiveObject(clsid,NULL,&pUnknown);	//查找是否有WORD程序在运行
	if(FAILED(hr))
	{
		AfxMessageBox(_T("没有正在运行中的WORD应用程序"));
		return;
	}//enfif
	
	try
	{
		hr = pUnknown->QueryInterface(IID_IDispatch,(LPVOID *)&app);
		if(FAILED(hr))	throw(_T("没有取得IDispatchPtr"));
		pUnknown->Release();	pUnknown=NULL;
		
		sel = app.GetSelection();
		if(!sel)	throw(_T("没有正在编辑的文档"));
		sel.WholeStory();				//全部选择
		CString str = sel.GetText();		//取得文本
		char con[100000];
		
		int len = str.GetLength();
		int i = 0;
		int j = 0;
		while(i < len)
		{				
			con[j] = str.GetAt(i);
			if(con[j] == '?' || con[j] == '')
				con[j] = ' ';
			if(str.GetAt(i) == '\r')
			{
				j++;
				con[j] = '\n';
			}
			i++;
			j++;
		}
		con[j] = '\0';
		strContent = con;
		UpdateData(FALSE);	
		
	}
	catch(LPCTSTR lpErr)
	{
		AfxMessageBox(lpErr);
	}
	if(pUnknown)	pUnknown->Release();
	if(sel)	sel.ReleaseDispatch();
	if(app)	sel.ReleaseDispatch();	
	if(SaveExist(strContent))
	{
		m_buttonAnswer.EnableWindow(TRUE);
		m_listPaper.DeleteAllItems();
		CString strChineseName = m_strSubject;
		CString strExistName = FindtbExist(strChineseName);
		CADORecordset* pExistRs;
		pExistRs = new CADORecordset(pDB); 
		CString strSQL;
	    strSQL.Format("select * from %s where ID='%s'",strExistName,Exist_ID);
		pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(FALSE,*pExistRs);
		pExistRs->Close();
		delete pExistRs;
		m_listPaper.SetFocus();
		m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		m_listQuestion.DeleteAllItems();
	}
}

//选择是否添加该试卷
BOOL CPaperDlg::SaveExist(CString strContent)
{
	if(strContent.IsEmpty())
	{
		AfxMessageBox("试卷内容不能为空!");
		return FALSE;
	}
	CSaveExistDlg saveexistDlg;
	saveexistDlg.strContent = strContent;
	saveexistDlg.strTablename = m_strSubject;
	if(saveexistDlg.DoModal() == IDOK && saveexistDlg.IsSave)
	{
		CString ID = saveexistDlg.ID;
		Exist_ID = ID;
		CString strChineseName = m_strSubject;
		ExistTable_name = FindtbExist(strChineseName);
		m_paperTree.DeleteAllItems();
		m_listPaper.DeleteAllItems();
		InitPaperTree();
		InitPaperList();
		CString afx = "试卷编号：";
		afx += ID;
		afx += "已添加到";
		afx += m_strSubject;
		afx += "试题库";
		AfxMessageBox(afx);
		return TRUE;
	}
	return FALSE;
}

void CPaperDlg::OnButtonInanswer() 
{
	// TODO: Add your control notification handler code here
	CString Exist_Answer;
	CLSID clsid;
	HRESULT hr;
	hr=::CLSIDFromProgID(L"Word.Application",&clsid);	//通过ProgID取得CLSID
	if(FAILED(hr))
	{
		AfxMessageBox(_T("没有安装OFFICE!"));
		return;
	}//endif
	
	IUnknown *pUnknown = NULL;
	IDispatch *pDispatch = NULL;
	_Application app = NULL;
	Selection sel = NULL;
	
	//++++++++++打开一个word文档
	CString strFilename;
	CImportDlg importDlg;
	if(importDlg.DoModal() == IDOK)
		strFilename = importDlg.GetFilename();
	else
		return;

	//目录
	char name[100];
	strcpy(name,strFilename.GetBuffer(100));
	
	char catalog[1000];
	int indexe = strFilename.ReverseFind('\\');		
	int i;
	for(i = 0 ; i < indexe+1 ; i++)
		catalog[i] = name[i];
	catalog[i] = '\0';
	
	//得到文件名.doc
	CString file = strFilename.Mid(indexe+1);
	
	ShellExecute(NULL,NULL,_T(file),NULL,_T(catalog),NULL);
	
	
	hr=::GetActiveObject(clsid,NULL,&pUnknown);	//查找是否有WORD程序在运行
	if(FAILED(hr))
	{
		AfxMessageBox(_T("没有正在运行中的WORD应用程序"));
		return;
	}//enfif
	
	try
	{
		hr = pUnknown->QueryInterface(IID_IDispatch,(LPVOID *)&app);
		if(FAILED(hr))	throw(_T("没有取得IDispatchPtr"));
		pUnknown->Release();	pUnknown=NULL;
		
		sel = app.GetSelection();
		if(!sel)	throw(_T("没有正在编辑的文档"));
		sel.WholeStory();				//全部选择
		CString str = sel.GetText();		//取得文本
		char con[100000];
		
		int len = str.GetLength();
		int i = 0;
		int j = 0;
		while(i < len)
		{
			con[j] = str.GetAt(i);
			if(str.GetAt(i) == '\r')
			{
				j++;
				con[j] = '\n';
			}
			i++;
			j++;
		}
		con[j] = '\0';
		Exist_Answer = "〖答案〗\r\n";
		Exist_Answer += con;
		UpdateData(FALSE);	
		
	}
	catch(LPCTSTR lpErr)
	{
		AfxMessageBox(lpErr);
	}
	if(pUnknown)	pUnknown->Release();
	if(sel)	sel.ReleaseDispatch();
	if(app)	sel.ReleaseDispatch();	

	if(ExistTable_name.IsEmpty() || Exist_ID.IsEmpty())
		return;
	CADORecordset* pExistRs;
	pExistRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from %s where ID='%s'",ExistTable_name,Exist_ID);
	pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	
	if(pExistRs->IsOpen())
	{
		pExistRs->SetFieldValue("答案",Exist_Answer);
		pExistRs->Update();
		CString strSuc = "试卷";
		strSuc += Exist_ID;
		strSuc += "答案导入成功";
		AfxMessageBox(strSuc);
		pExistRs->Close();
	}
	else
	{
		AfxMessageBox("答案导入失败!");
	}
	delete pExistRs;		

	m_buttonAnswer.EnableWindow(FALSE);
}


//浏览试卷及答案
void CPaperDlg::OnButtonBrowse() 
{
	// TODO: Add your control notification handler code here
	CBrowseAllDlg browseallDlg;
	CString strID = Now_ID;
	if(strID.IsEmpty())
		return;
	CString strType;
	if(strID.GetLength() % 2)
		strType = "成套试卷";
	else
		strType = "已组试卷";
	CString strAnswer,strPaper;
	
	CString strChineseName = m_strSubject;
	CString strTableName;
	if(strType == "已组试卷")
		strTableName = FindtbPaper(strChineseName);
	else
		strTableName = FindtbExist(strChineseName);
	
	CADORecordset *pRs = new CADORecordset(pDB);
	CString strSql;
	strSql.Format("select * from %s where ID='%s'",strTableName,strID);
	pRs->Open(_bstr_t(strSql),CADORecordset.openQuery);
	if(pRs->IsOpen())
	{
		pRs->GetFieldValue("答案",strAnswer);
		pRs->GetFieldValue("内容",strPaper);
		browseallDlg.m_strTitleAnswer = "试卷ID：";
		browseallDlg.m_strTitleAnswer += strID;
		browseallDlg.m_strTitleAnswer += "答案";
		browseallDlg.m_strTitlePaper = "试卷ID：";
		browseallDlg.m_strTitlePaper += strID;
		browseallDlg.m_strTitlePaper += "内容";
		browseallDlg.m_strAnswer = strAnswer;
		browseallDlg.m_strPaper = strPaper;
		browseallDlg.strID = strID;
		
		browseallDlg.DoModal();
		
		pRs->Close();
	}
	delete pRs;	
}

//选择科目发生变化
void CPaperDlg::OnSelchangeComboSubject() 
{
	// TODO: Add your control notification handler code here
	m_buttonAnswer.EnableWindow(FALSE);
	UpdateData(TRUE);
	m_listPaper.DeleteAllItems();
	m_listQuestion.DeleteAllItems();
	InitPaperList();
	InitPaperTree();
	InitComboCreate();
}

void CPaperDlg::OnClickTreePaper(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_buttonAnswer.EnableWindow(FALSE);
	CString strChineseName = m_strSubject;
	if(strChineseName.IsEmpty())
		return;
	HTREEITEM hItem = m_paperTree.GetSelectedItem();
	if(m_paperTree.GetItemText(hItem) == strChineseName)
	{
		InitPaperList();
		return;
	}
	CString strPaperName = FindtbPaper(strChineseName);
	CString strExistName = FindtbExist(strChineseName);
	
	m_listPaper.DeleteAllItems();

	if(m_paperTree.GetItemText(hItem) == "已组试卷")
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s order by 方案ID",strPaperName);
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);

		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	if(m_paperTree.GetItemText(hItem) == "成套试卷")
	{
		CADORecordset* pExistRs;
		pExistRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s order by ID",strExistName);
		pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(FALSE,*pExistRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pExistRs->Close();
		delete pExistRs;

		m_listQuestion.DeleteAllItems();
		
		*pResult = 0;
		return;
	}
	HTREEITEM hParent = m_paperTree.GetParentItem(hItem);
	if(m_paperTree.GetItemText(hParent) == "成套试卷")
	{
		CADORecordset* pExistRs;
		pExistRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where ID='%s'",strExistName,m_paperTree.GetItemText(hItem));
		pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(FALSE,*pExistRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pExistRs->Close();
		delete pExistRs;

		m_listQuestion.DeleteAllItems();

		*pResult = 0;
		return;
	}
	HTREEITEM hpParent = m_paperTree.GetParentItem(hParent);
	if(m_paperTree.GetItemText(hpParent) == strChineseName)
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where 方案ID='%s' order by ID",strPaperName,m_paperTree.GetItemText(hItem));
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
		m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);

		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	if(m_paperTree.GetItemText(hpParent) == "已组试卷")
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where ID='%s'",strPaperName,m_paperTree.GetItemText(hItem));
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
		m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);

		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	*pResult = 0;
}

void CPaperDlg::OnSelchangedTreePaper(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_buttonAnswer.EnableWindow(FALSE);
	CString strChineseName = m_strSubject;
	HTREEITEM hItem = m_paperTree.GetSelectedItem();
	if(m_paperTree.GetItemText(hItem) == strChineseName)
	{
		InitPaperList();
		return;
	}
	CString strPaperName = FindtbPaper(strChineseName);
	CString strExistName = FindtbExist(strChineseName);
	
	m_listPaper.DeleteAllItems();

	if(m_paperTree.GetItemText(hItem) == "已组试卷")
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s order by 方案ID",strPaperName);
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);

		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	if(m_paperTree.GetItemText(hItem) == "成套试卷")
	{
		CADORecordset* pExistRs;
		pExistRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s order by ID",strExistName);
		pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(FALSE,*pExistRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pExistRs->Close();
		delete pExistRs;

		m_listQuestion.DeleteAllItems();
		
		*pResult = 0;
		return;
	}
	HTREEITEM hParent = m_paperTree.GetParentItem(hItem);
	if(m_paperTree.GetItemText(hParent) == "成套试卷")
	{
		CADORecordset* pExistRs;
		pExistRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where ID='%s'",strExistName,m_paperTree.GetItemText(hItem));
		pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(FALSE,*pExistRs);
		m_listPaper.SetFocus();
	    m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
		pExistRs->Close();
		delete pExistRs;

		m_listQuestion.DeleteAllItems();

		*pResult = 0;
		return;
	}
	HTREEITEM hpParent = m_paperTree.GetParentItem(hParent);
	if(m_paperTree.GetItemText(hpParent) == strChineseName)
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where 方案ID='%s' order by ID",strPaperName,m_paperTree.GetItemText(hItem));
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
		m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);

		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	if(m_paperTree.GetItemText(hpParent) == "已组试卷")
	{
		CADORecordset* pPaperRs;
		pPaperRs = new CADORecordset(pDB); 
		CString strSQL;
		strSQL.Format("select * from %s where ID='%s'",strPaperName,m_paperTree.GetItemText(hItem));
		pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
		RefreshList(TRUE,*pPaperRs);
		m_listPaper.SetFocus();
		m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);

		m_listQuestion.DeleteAllItems();
		UpdateQuestionList(*pPaperRs);

		pPaperRs->Close();
		delete pPaperRs;
		*pResult = 0;
		return;
	}
	*pResult = 0;
}

void CPaperDlg::OnClickListPaper(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_buttonAnswer.EnableWindow(FALSE);
	m_listQuestion.DeleteAllItems();
	int sel = m_listPaper.GetSelectionMark();
	if(sel<0)
	{
		Now_ID = "";
		return;
	}
	CString strID = m_listPaper.GetItemText(sel,0);
	CString strType = m_listPaper.GetItemText(sel,3);
	//当前选中的试卷
    Now_ID = strID;

	if(strType == "已组试卷")
	{
		CString strChineseName = m_strSubject;
		CString strPaperName = FindtbPaper(strChineseName);

		CADORecordset *pPaperRs = new CADORecordset(pDB);
		CString strSql;
		strSql.Format("select * from %s where ID='%s'",strPaperName,strID);
		pPaperRs->Open(_bstr_t(strSql),CADORecordset.openQuery);
		if(pPaperRs->IsOpen())
		{
			UpdateQuestionList(*pPaperRs);
			pPaperRs->Close();
		}
		delete pPaperRs;
	}
	*pResult = 0;
}

void CPaperDlg::OnCheckDate() 
{
	// TODO: Add your control notification handler code here
	if(m_checkDate == FALSE)
	{
		m_checkDate = TRUE;
		m_DateFrom.EnableWindow(TRUE);
		m_DateTo.EnableWindow(TRUE);
	}
	else
	{
		m_checkDate = FALSE;
		m_DateFrom.EnableWindow(FALSE);
		m_DateTo.EnableWindow(FALSE);
	}	
}

void CPaperDlg::OnButtonQuery() 
{
	// TODO: Add your control notification handler code here
	m_buttonAnswer.EnableWindow(FALSE);
	UpdateData(TRUE);
	CString strChineseName = m_strSubject;
	if(strChineseName.IsEmpty())
		return;
	CString strPaperName = FindtbPaper(strChineseName);
	CString strExistName = FindtbExist(strChineseName);
	CString strDateFrom,strDateTo;
	CString strSQL1,strSQL2,temp;
	//若没有选择任何查询条件，则查询所有记录
	if((!m_checkDate) && (m_strCreateperson.IsEmpty()))
	{
		strSQL1.Format("select * from %s",strPaperName);
		strSQL2.Format("select * from %s",strExistName);
	}
	else 
	{
		strSQL1.Format("select * from %s where",strPaperName);
		strSQL2.Format("select * from %s where",strExistName);
	}

	//如果选择日期查询，则获得日期控件的字符串和日期信息
	if(m_checkDate)
	{
		CTime timeFrom,timeTo;
		m_DateFrom.GetTime(timeFrom);
		m_DateTo.GetTime(timeTo);
		m_DateFrom.GetWindowText(strDateFrom);
		m_DateTo.GetWindowText(strDateTo);
		//判断时间值的有效性
		if(timeFrom.GetYear() > timeTo.GetYear())
		{
			MessageBox("Date set is wrong!");
			return;
		}
		else if(timeFrom.GetYear() == timeTo.GetYear())
		{
			if(timeFrom.GetMonth() > timeTo.GetMonth())
			{
				MessageBox("Date set is wrong!");
				return;
			}
			else if(timeFrom.GetMonth() == timeTo.GetMonth())
			{
				if(timeFrom.GetDay() > timeTo.GetDay())
				{
					MessageBox("Date set is wrong!");
					return;
				}
			}
		}
		temp.Format(" 创建时间>='%s' and 创建时间<='%s'",strDateFrom,strDateTo);
		strSQL1 += temp;
		strSQL2 += temp;
	}
	//如果用户输入了创建人人的姓名，需要在SQL中加入该条件
	if(!m_strCreateperson.IsEmpty())
	{
		if(m_checkDate)
			temp.Format(" and 创建人='%s'",m_strCreateperson);
		else
			temp.Format(" 创建人='%s'",m_strCreateperson);
		strSQL1 += temp;
		strSQL2 += temp;
	}
	m_listPaper.DeleteAllItems();

	CADORecordset* pExistRs;
	pExistRs = new CADORecordset(pDB); 
	pExistRs->Open(_bstr_t(strSQL2),CADORecordset.openQuery);
	RefreshList(FALSE,*pExistRs);
	pExistRs->Close();
	delete pExistRs;

	CADORecordset* pPaperRs;
	pPaperRs = new CADORecordset(pDB); 
	pPaperRs->Open(_bstr_t(strSQL1),CADORecordset.openQuery);
	RefreshList(TRUE,*pPaperRs);

	m_listQuestion.DeleteAllItems();
	UpdateQuestionList(*pPaperRs);

	pPaperRs->Close();
	delete pPaperRs;

	//当前选中的试卷
	if(m_listPaper.GetItemCount() > 0)
	{
		Now_ID = m_listPaper.GetItemText(0,0);
		if(Now_ID.GetLength() % 2)
			m_listQuestion.DeleteAllItems();
	}
	else
	{
		m_listQuestion.DeleteAllItems();
		Now_ID = "";
	}

	m_listPaper.SetFocus();
	m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);	
}

void CPaperDlg::OnButtonOnlyquery() 
{
	// TODO: Add your control notification handler code here
	m_buttonAnswer.EnableWindow(FALSE);
	UpdateData(TRUE);
	CString strChineseName = m_strSubject;
	if(strChineseName.IsEmpty())
		return;
	CString strPaperName = FindtbPaper(strChineseName);
	CString strExistName = FindtbExist(strChineseName);
	m_listPaper.DeleteAllItems();
	CADORecordset* pPaperRs;
	pPaperRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from %s where ID='%s'",strPaperName,m_strID);
	pPaperRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	RefreshList(TRUE,*pPaperRs);

	m_listQuestion.DeleteAllItems();
	UpdateQuestionList(*pPaperRs);

	pPaperRs->Close();
	delete pPaperRs;

	CADORecordset* pExistRs;
	pExistRs = new CADORecordset(pDB); 
	if(Purview)
		strSQL.Format("select * from %s where ID='%s'",strExistName,m_strID);
	else
		strSQL.Format("select * from %s where ID='%s' and 创建人='%s'",strExistName,m_strID,strUsername);
	pExistRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	RefreshList(FALSE,*pExistRs);
	pExistRs->Close();
	delete pExistRs;

	//当前选中的试卷
	if(m_listPaper.GetItemCount() > 0)
	{
		Now_ID = m_listPaper.GetItemText(0,0);
		if(Now_ID.GetLength() % 2)
			m_listQuestion.DeleteAllItems();
	}
	else
	{
		m_listQuestion.DeleteAllItems();
		Now_ID = "";
	}

	m_listPaper.SetFocus();
	m_listPaper.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
}
