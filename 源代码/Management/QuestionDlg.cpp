// QuestionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "QuestionDlg.h"
#include "AddandeditDlg.h"
#include "string.h"
#include "ManageAllDlg.h"
#include "ImportDlg.h"
#include "msword.h"
#include <AtlBase.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuestionDlg dialog
//定义全局变量
CString Difficulty_Chinese[5] = {"易","较易","中等","较难","难"};
CString Chapter_Chinese[30] = {"第01章","第02章","第03章","第04章","第05章","第06章","第07章","第08章","第09章","第10章",
"第11章","第12章","第13章","第14章","第15章","第16章","第17章","第18章","第19章","第20章",
"第21章","第22章","第23章","第24章","第25章","第26章","第27章","第28章","第29章","第30章"};


CQuestionDlg::CQuestionDlg(CWnd* pParent /*=NULL*/)
: CDialog(CQuestionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQuestionDlg)
	m_chapter = _T("");
	m_content = _T("");
	m_difficulty = _T("");
	m_id = _T("");
	m_type = _T("");
	m_answer = _T("");
	m_subject = _T("");
	m_selectChapter = _T("");
	m_selectDifficulty = _T("");
	m_selectType = _T("");
	m_queryid = _T("");
	//}}AFX_DATA_INIT
	m_AddorEdit = TRUE;
	Table_name = "";
	Purview = FALSE;
}

CQuestionDlg::~CQuestionDlg()
{
	//关闭记录集
	if(pRs && pRs->IsOpen())
		pRs->Close();
	if(pRs)
		delete(pRs);
}

void CQuestionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuestionDlg)
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_buttonClear);
	DDX_Control(pDX, IDC_EDIT_QUERYID, m_editQueryid);
	DDX_Control(pDX, IDC_BUTTON_QUERYONLY, m_buttonQueryOnly);
	DDX_Control(pDX, IDC_BUTTON_QUERY, m_buttonQuery);
	DDX_Control(pDX, IDC_BUTTON_PRE, m_buttonPre);
	DDX_Control(pDX, IDC_BUTTON_OUT, m_buttonOut);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_buttonNext);
	DDX_Control(pDX, IDC_BUTTON_LAST, m_buttonLast);
	DDX_Control(pDX, IDC_BUTTON_IN, m_buttonIn);
	DDX_Control(pDX, IDC_BUTTON_FIRST, m_buttonFirst);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_buttonEdit);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_buttonDelete);
	DDX_Control(pDX, IDC_BUTTON_CONFIRM, m_buttonConfirm);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_buttonClose);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_buttonAdd);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboType);
	DDX_Control(pDX, IDC_COMBO_DIFFICULTY, m_comboDifficulty);
	DDX_Control(pDX, IDC_COMBO_CHAPTER, m_comboChapter);
	DDX_Control(pDX, IDC_EDIT_ANSWER, m_editAnswer);
	DDX_Control(pDX, IDC_EDIT_TYPE, m_editType);
	DDX_Control(pDX, IDC_EDIT_ID, m_editID);
	DDX_Control(pDX, IDC_EDIT_DIFFICULTY, m_editDifficulty);
	DDX_Control(pDX, IDC_EDIT_CONTENT, m_editContent);
	DDX_Control(pDX, IDC_EDIT_CHAPTER, m_editChapter);
	DDX_Control(pDX, IDC_LIST_QUESTION, m_questionList);
	DDX_Control(pDX, IDC_COMBO_SUBJECT, m_comboSubject);
	DDX_Text(pDX, IDC_EDIT_CHAPTER, m_chapter);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_content);
	DDX_Text(pDX, IDC_EDIT_DIFFICULTY, m_difficulty);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_type);
	DDX_Text(pDX, IDC_EDIT_ANSWER, m_answer);
	DDX_CBString(pDX, IDC_COMBO_SUBJECT, m_subject);
	DDX_CBString(pDX, IDC_COMBO_CHAPTER, m_selectChapter);
	DDX_CBString(pDX, IDC_COMBO_DIFFICULTY, m_selectDifficulty);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_selectType);
	DDX_Text(pDX, IDC_EDIT_QUERYID, m_queryid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQuestionDlg, CDialog)
//{{AFX_MSG_MAP(CQuestionDlg)
ON_NOTIFY(NM_CLICK, IDC_LIST_QUESTION, OnClickListQuestion)
ON_BN_CLICKED(IDC_BUTTON_CONFIRM, OnButtonConfirm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
ON_BN_CLICKED(IDC_BUTTON_FIRST, OnButtonFirst)
ON_BN_CLICKED(IDC_BUTTON_LAST, OnButtonLast)
ON_BN_CLICKED(IDC_BUTTON_PRE, OnButtonPre)
ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_QUERYONLY, OnButtonQueryonly)
ON_BN_CLICKED(IDC_BUTTON_IN, OnButtonIn)
ON_BN_CLICKED(IDC_BUTTON_OUT, OnButtonOut)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_QUESTION, OnKeydownListQuestion)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuestionDlg message handlers

BOOL CQuestionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CManageAllDlg *parent = (CManageAllDlg *)GetParent();
	pDB = parent->pDB;
	pRs = new CADORecordset(pDB);
	CString strPurview = parent->GetPurview();
	if(strPurview == "系统管理员")
	{
		Purview = TRUE;
	}
	else
		Purview = FALSE;

	//初始化按钮
	m_buttonQueryOnly.EnableWindow(FALSE);
	m_buttonQuery.EnableWindow(FALSE);
	m_buttonPre.EnableWindow(FALSE);
	m_buttonOut.EnableWindow(FALSE);
	m_buttonNext.EnableWindow(FALSE);
	m_buttonLast.EnableWindow(FALSE);
	m_buttonIn.EnableWindow(FALSE);
	m_buttonFirst.EnableWindow(FALSE);
	m_buttonEdit.EnableWindow(FALSE);
	m_buttonDelete.EnableWindow(FALSE);
	m_buttonClear.EnableWindow(FALSE);
	m_buttonClose.EnableWindow(FALSE);
	m_buttonAdd.EnableWindow(FALSE);
	
	//初始化List控件的栏目
	m_questionList.InsertColumn(0,"ID",LVCFMT_LEFT,85,-1);
	m_questionList.InsertColumn(1,"题型",LVCFMT_LEFT,95,-1);
	m_questionList.InsertColumn(2,"难度",LVCFMT_LEFT,60,-1);
	m_questionList.InsertColumn(3,"所属章节",LVCFMT_LEFT,77,-1);
	
	//设置List的行被选中时是全行
	m_questionList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		
	//初始化Combo题库控件
	InitComboSubject();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CQuestionDlg::InitCombo()
{
    //清空
	int count = m_comboType.GetCount();
	for(int i = 0 ; i < count ; i++)	
		m_comboType.DeleteString(0);
	count = m_comboChapter.GetCount();
	for(i = 0 ; i < count ; i++)
		m_comboChapter.DeleteString(0);
	count = m_comboDifficulty.GetCount();
	for(i = 0 ; i < count ; i++)
		m_comboDifficulty.DeleteString(0);

	UpdateData(TRUE);
	if(Table_name.IsEmpty())
		return FALSE;
	//初始化

	//+++++++++++++++++++++++类型+++++++++++++++++++++++++++
	if(pRs->IsOpen())
		pRs->Close();
	CString strSql;
	strSql.Format("select * from %s order by ID",Table_name);
	pRs->Open(strSql,CADORecordset.openQuery);
	if(pRs->IsOpen() && pRs->GetRecordCount() > 0)
	{
		m_comboType.AddString("");
		CString strType = "";
		CString lastType = "";
		while(!pRs->IsEOF())
		{			
			pRs->GetFieldValue("Type",strType);
			if(strType != lastType)
			{
				m_comboType.AddString(strType);
			}
			lastType = strType;
			pRs->MoveNext();
		}
	}
	else 
		return FALSE;
	pRs->Close();

	//+++++++++++++++++++++++章节++++++++++++++++++++++++++
	strSql.Format("select * from %s order by Chapter",Table_name);	
	pRs->Open(strSql,CADORecordset.openQuery);
	if(!pRs->IsOpen())
		return FALSE;
	m_comboChapter.AddString("");
	CString strChapter = "";
	CString lastChapter = "";
	while(!pRs->IsEOF())
	{
		pRs->GetFieldValue("Chapter",strChapter);
		if(strChapter != lastChapter)
		{
			m_comboChapter.AddString(strChapter);
		}	
		lastChapter = strChapter;
		pRs->MoveNext();
	}
	pRs->Close();

	//+++++++++++++++++++++++难度+++++++++++++++++++++++++++
	strSql.Format("select * from %s order by Difficulty",Table_name);	
	pRs->Open(strSql,CADORecordset.openQuery);
	if(!pRs->IsOpen())
		return FALSE;
	m_comboDifficulty.AddString("");
	CString strDifficulty = "";
	CString lastDifficulty = "";
	int Difficulty_num[5] = {0};
	int index = -1;
	while(!pRs->IsEOF())
	{	
		pRs->GetFieldValue("Difficulty",strDifficulty);
		if(strDifficulty != lastDifficulty)
		{
			for(i = 0 ; i < 5 ; i++)
				if(strDifficulty == Difficulty_Chinese[i])
					index = i;
		}
		Difficulty_num[index]++;
		lastDifficulty = strDifficulty;
		pRs->MoveNext();
	}
	pRs->Close();
	for(i = 0 ; i < 5 ; i++)
	{
		if(Difficulty_num[i] > 0 )
			m_comboDifficulty.AddString(Difficulty_Chinese[i]);
	}
	return TRUE;
}

BOOL CQuestionDlg::InitComboSubject()
{
	//初始化Combo题库控件
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

//查找表(即题库是否存在)
CString CQuestionDlg::FindTable()
{
	UpdateData(TRUE);
	
	CADORecordset* pTableRs;
	pTableRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbTableName where Chinesename='%s'",m_subject);
	pTableRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	
	CString strEnglishName = "";
	if(pTableRs->IsOpen() && pTableRs->GetRecordCount() > 0)
	{
		pTableRs->GetFieldValue("EnglishName",strEnglishName);
		pTableRs->Close();
	}
	if(pTableRs)
		delete(pTableRs);
	return strEnglishName;
}

//显示题目详细信息
void CQuestionDlg::SetAllControls()
{
	if((pRs->IsOpen()) && (pRs->GetRecordCount()>0))
	{
		pRs->GetFieldValue(0,m_id);
		pRs->GetFieldValue(1,m_type);
		pRs->GetFieldValue(2,m_difficulty);
		pRs->GetFieldValue(3,m_chapter);
		pRs->GetFieldValue(4,m_content);
		pRs->GetFieldValue(5,m_answer);
		UpdateData(FALSE);
	}			
}

//更新List控件,将记录移到第一条  +++++++++++在其他函数中被调用++++++++++
void CQuestionDlg::RefreshList(CADORecordset& recordset) 
{
	if(!recordset.IsOpen())
		return;
    if(recordset.GetRecordCount() <= 0)
	{
		m_id = "";
		m_type = "";
		m_difficulty = "";
		m_chapter = "";
		m_content = "";
		m_answer = "";
		m_questionList.DeleteAllItems();
		UpdateData(FALSE);
		return;
	}
	recordset.MoveFirst();
	CString strID,strType,strDifficulty,strChapter;
	int indexofList=0;
	m_questionList.DeleteAllItems();
	while(!(recordset.IsEOF()))
	{
		recordset.GetFieldValue("ID",strID);
		recordset.GetFieldValue("Type",strType);
		recordset.GetFieldValue("Difficulty",strDifficulty);
		recordset.GetFieldValue("Chapter",strChapter);
		m_questionList.InsertItem(indexofList,strID);
		m_questionList.SetItemText(indexofList,1,strType);
		m_questionList.SetItemText(indexofList,2,strDifficulty);
		m_questionList.SetItemText(indexofList,3,strChapter);
		indexofList+=1;
		recordset.MoveNext();
	}
	recordset.MoveFirst();
}

void CQuestionDlg::OnButtonConfirm() 
{
	// TODO: Add your control notification handler code here
	
	//判断是否已经有题库打开
	if(pRs->IsOpen())
		pRs->Close();
	
    //查找当前要打开的题库是否存在
	Table_name = FindTable();
	if(Table_name.IsEmpty())
	{
		//清空所有控件
		m_id = "";
		m_type = "";
		m_difficulty = "";
		m_chapter = "";
		m_content = "";
		m_answer = "";
		m_questionList.DeleteAllItems();
		UpdateData(FALSE);
		AfxMessageBox("请选择题库!");
		return;
	}
	//初始化combo
	InitCombo();
	//定义字符串存储SQL语句
	CString strSql;
	//初始化SQL语句字符串，获得所选题库的数据
	strSql.Format("select * from %s order by ID",Table_name);
	
	//打开当前选中的题库
	pRs->Open(strSql,CADORecordset.openQuery);
    RefreshList(*pRs);
	SetAllControls();
	
	m_questionList.SetFocus();
	m_questionList.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
	//改变按钮状态
	if(pRs->GetRecordCount() > 0)
	{
		m_buttonQueryOnly.EnableWindow(TRUE);
		m_buttonQuery.EnableWindow(TRUE);
		m_buttonPre.EnableWindow(TRUE);
		m_buttonOut.EnableWindow(TRUE);
		m_buttonNext.EnableWindow(TRUE);
		m_buttonLast.EnableWindow(TRUE);
		m_buttonFirst.EnableWindow(TRUE);
		m_buttonEdit.EnableWindow(TRUE);
		m_buttonDelete.EnableWindow(TRUE);
		m_buttonClear.EnableWindow(TRUE);
		m_comboType.EnableWindow(TRUE);
		m_comboDifficulty.EnableWindow(TRUE);
		m_comboChapter.EnableWindow(TRUE);
	}
	m_buttonIn.EnableWindow(TRUE);
	m_buttonAdd.EnableWindow(TRUE);
	m_buttonClose.EnableWindow(TRUE);
	m_buttonConfirm.EnableWindow(FALSE);
	m_comboSubject.EnableWindow(FALSE);
	m_editQueryid.EnableWindow(TRUE);
}

//选中题目
void CQuestionDlg::OnClickListQuestion(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int sel=m_questionList.GetSelectionMark();
	if(sel<0)
		return;
	else
	{
		CString strID = m_questionList.GetItemText(sel,0);		
		if(pRs->IsOpen())
		{
			if(pRs->Find("ID="+strID,1)||pRs->Find("ID="+strID,-1))
				SetAllControls();
		}
	}
	*pResult = 0;
}

void CQuestionDlg::OnButtonFirst() 
{
	// TODO: Add your control notification handler code here
	if((pRs->IsOpen())&&(pRs->GetRecordCount()!=0))
	{
		pRs->MoveFirst();
		SetAllControls();
	}
}

void CQuestionDlg::OnButtonLast() 
{
	// TODO: Add your control notification handler code here
	if((pRs->IsOpen())&&(pRs->GetRecordCount()!=0))
	{
		pRs->MoveLast();
		SetAllControls();
	}
}

void CQuestionDlg::OnButtonPre() 
{
	// TODO: Add your control notification handler code here
	if((pRs->IsOpen())&&(pRs->GetRecordCount()!=0)&&(!pRs->IsBOF()))
	{
		pRs->MovePrevious();
		if (pRs->IsBOF()) 
		{
			pRs->MoveNext();
			AfxMessageBox("首记录!");
			return;
		}	
		SetAllControls();
	}
}

void CQuestionDlg::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	if((pRs->IsOpen())&&(pRs->GetRecordCount()!=0)&&(!pRs->IsEOF()))
	{	
		pRs->MoveNext();
		if (pRs->IsEOF()) 
		{
			pRs->MovePrevious();
			AfxMessageBox("末记录!");
			return;
		}	

		SetAllControls();	
	}
}

void CQuestionDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	if(pRs->IsOpen())
	{
		m_AddorEdit = TRUE;
		CAddandeditDlg addandeditDlg;
		if(addandeditDlg.DoModal() == IDOK)
		{
			//更新控件
			m_type = addandeditDlg.m_type;
			m_difficulty = addandeditDlg.m_difficulty;
			m_chapter = addandeditDlg.m_chapter;
			
			CString ID = "";
			ID += FindType(m_type);
			ID += FindDifficulty(m_difficulty);
			ID += FindChapter(m_chapter);
			ID += FindNum(m_type,m_difficulty,m_chapter);
			m_id = ID;
			
			m_content = addandeditDlg.m_content;
			m_answer = addandeditDlg.m_answer;
			UpdateData(FALSE);

			//插入记录到记录集
			pRs->AddNew();
			pRs->SetFieldValue("ID",m_id);
			pRs->SetFieldValue("Type",m_type);
			pRs->SetFieldValue("Difficulty",m_difficulty);
			pRs->SetFieldValue("Chapter",m_chapter);
			pRs->SetFieldValue("Content",m_content);
			pRs->SetFieldValue("Answer",m_answer);
			pRs->Update();
			
			//重新初始化combo
			InitCombo();
			//重新打开题库
			if(pRs->IsOpen())
				pRs->Close();
			CString strSql;
			strSql.Format("select * from %s order by ID",Table_name);			
			pRs->Open(strSql,CADORecordset.openQuery);
			
			if(pRs->IsOpen())
			{
				RefreshList(*pRs);
				pRs->Find("ID="+m_id);
			}
			m_comboType.EnableWindow(TRUE);
			m_comboDifficulty.EnableWindow(TRUE);
			m_comboChapter.EnableWindow(TRUE);
			m_editID.EnableWindow(TRUE);
			m_buttonQueryOnly.EnableWindow(TRUE);
			m_buttonQuery.EnableWindow(TRUE);
			m_buttonPre.EnableWindow(TRUE);
			m_buttonOut.EnableWindow(TRUE);
			m_buttonNext.EnableWindow(TRUE);
			m_buttonLast.EnableWindow(TRUE);
			m_buttonFirst.EnableWindow(TRUE);
			m_buttonEdit.EnableWindow(TRUE);
			m_buttonDelete.EnableWindow(TRUE);
			m_buttonClear.EnableWindow(TRUE);
		}
	}
}

//查找类型编号
CString CQuestionDlg::FindType(CString type)
{
	CString strType = "";
	CADORecordset* pTypeRs;
	pTypeRs = new CADORecordset(pDB); 
	CString strSQL;
	strSQL.Format("select * from tbType");
	pTypeRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	if(pTypeRs->IsOpen() && pTypeRs->GetRecordCount() > 0)
	{
		while(!pTypeRs->IsEOF())
		{
			CString strID;
			CString str;
			pTypeRs->GetFieldValue("Name",str);
			if(str != type)
			{
				pTypeRs->MoveNext();
				continue;
			}	
			pTypeRs->GetFieldValue("ID",strID);
			if(strID.GetLength() == 1)
			{
				strType += "0";
				strType += strID;
			}
			else
				strType += strID;
			pTypeRs->MoveNext();
		}
		pTypeRs->Close();
	}
	if(pTypeRs)
		delete(pTypeRs);
	return strType;
}

//查找难度编号
CString CQuestionDlg::FindDifficulty(CString difficulty)
{
	if(difficulty.IsEmpty())
		return "00";
	CString Diff = "";
	int i = 0;
	for(i = 0 ; i < 5 ; i++)
	{
		if(difficulty == Difficulty_Chinese[i])
		{
			Diff += "0";
			Diff += i + 48 + 1;
		}
	}
	return Diff;
}

//查找章节编号
CString CQuestionDlg::FindChapter(CString chapter)
{
	if(chapter.IsEmpty())
		return "00";
	char chap[10];
	strcpy(chap,chapter);
	char id[3];
	id[0] = chap[2];
	id[1] = chap[3];
	id[2] = '\0';
	CString strchap = id;
	return strchap;
}

//确定编号后4位
CString CQuestionDlg::FindNum(CString type,CString difficulty,CString chapter)
{
	CADORecordset* pIDRs;
	pIDRs = new CADORecordset(pDB);
	
	//打开当前题库查找
	CString strSQL; 
	strSQL.Format("select * from %s where Type='%s' and Difficulty='%s' and Chapter='%s'",Table_name,type,difficulty,chapter);
	pIDRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
	
	CString strNum = "";
	if(pIDRs->IsOpen())
	{
		CString Num;
		int count = pIDRs->GetRecordCount();
		Num.Format(_T("%d"),count+1);
		int n = Num.GetLength();	
		for(int i = 0 ; i < 4-n ; i++)
		{
			strNum += "0";
		}
		strNum += Num;
		pIDRs->Close();
	}
	if(pIDRs)
		delete(pIDRs);
	return strNum;
}

//记录变化后更改相关记录ID       ++++++++只在edit后调用++++++++++
void CQuestionDlg::UpdateOthers(CString old_id,CString old_type,CString old_difficulty,CString old_chapter)
{
	if(pRs->IsOpen())
		pRs->Close();
	CString strSql;
	strSql.Format("select * from %s where Type='%s' and Difficulty='%s' and Chapter='%s' order by ID",Table_name,old_type,old_difficulty,old_chapter);
	pRs->Open(strSql,CADORecordset.openQuery);
	
	CString strID;
	long id = atol(old_id);
	
	if(pRs->IsOpen())
	{		
		if(pRs->GetRecordCount() > 0)
		{
			pRs->MoveFirst();
			while(!(pRs->IsEOF()))
			{			
				pRs->GetFieldValue("ID",strID);
				long r_id = atol(strID);
				
				if(r_id > id)
				{	
					r_id--;
					strID.Format(_T("%ld"),r_id);
					if(strID.GetLength() != 10)
					{
						CString ID = "0";
						ID += strID;
						strID = ID;
					}
					pRs->SetFieldValue("ID",strID);
					pRs->Update();
				}
				pRs->MoveNext();
			}
		}
		pRs->Close();
		CString strSQL; 
		strSql.Format("select * from %s order by ID",Table_name);
		pRs->Open(strSql,CADORecordset.openQuery);
	}
}

void CQuestionDlg::OnButtonEdit() 
{
	// TODO: Add your control notification handler code here
	if((pRs->IsOpen())&&(pRs->GetRecordCount()>0))
	{
		m_AddorEdit = FALSE;
		CAddandeditDlg addandeditDlg;
		if(addandeditDlg.DoModal() == IDOK)
		{	
			if(!addandeditDlg.IsAttributesEdit && !addandeditDlg.IsContentEdit)
				return;
			
			CString old_id,old_type,old_difficulty,old_chapter;
			old_id = m_id;
			old_type = m_type;
			old_difficulty = m_difficulty;
			old_chapter = m_chapter;
			
			if(addandeditDlg.IsContentEdit)
			{
				m_content = addandeditDlg.m_content;
				m_answer = addandeditDlg.m_answer;
				UpdateData(FALSE);
				pRs->SetFieldValue("Content",m_content);
				pRs->SetFieldValue("Answer",m_answer);
				pRs->Update();	
            }
			
			if(addandeditDlg.IsAttributesEdit)
			{
				m_type = addandeditDlg.m_type;
				m_difficulty = addandeditDlg.m_difficulty;
				m_chapter = addandeditDlg.m_chapter;
				UpdateData(FALSE);
				
				CString ID = "";
				ID += FindType(m_type);
				ID += FindDifficulty(m_difficulty);
				ID += FindChapter(m_chapter);
				ID += FindNum(m_type,m_difficulty,m_chapter);
				m_id = ID;
				UpdateData(FALSE);
				
				pRs->SetFieldValue("ID",m_id);
				pRs->SetFieldValue("Type",m_type);
				pRs->SetFieldValue("Difficulty",m_difficulty);
				pRs->SetFieldValue("Chapter",m_chapter);
				pRs->Update();	
				UpdateOthers(old_id,old_type,old_difficulty,old_chapter);
			}	
			//重新初始化combo
			InitCombo();
			//重新打开题库
			if(pRs->IsOpen())
				pRs->Close();
			CString strSql;
			strSql.Format("select * from %s order by ID",Table_name);			
			pRs->Open(strSql,CADORecordset.openQuery);
			RefreshList(*pRs);
            //定位到当前修改的题目
			pRs->Find("ID="+m_id);
		}
	}
}

void CQuestionDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
			
	if((pRs->IsOpen())&&(pRs->GetRecordCount()>0))
	{
		CString Find_ID = "";
		pRs->MoveNext();
		if(pRs->IsEOF())
		{
			pRs->MovePrevious();
			pRs->MovePrevious();
			if(!pRs->IsBOF())
			{
				pRs->GetFieldValue("ID",Find_ID);
			}		
			else
				Find_ID = "";
		}
		else
		{
			pRs->GetFieldValue("ID",Find_ID);
			if(!Find_ID.IsEmpty())
			{
				char temp[11];
				strcpy(temp,Find_ID.GetBuffer(100));
				char tt[5];
				for(int i = 6,j = 0 ; i < 10 ; i++,j++)
					tt[j] = temp[i];
				tt[j] = '\0';
				if(strcmp(tt,"0001"))
					Find_ID = m_id;
			}			
		}

		CString strdelete = "要删除No.";
		strdelete += m_id;
		strdelete += "试题?";
		if(MessageBox(strdelete,"确认删除",MB_ICONQUESTION|MB_OKCANCEL) == IDCANCEL)
			return;
		
		try
		{
			pDB->BeginTransaction();
			CString strID = m_id;
			CString strSQL;
			strSQL.Format("delete from %s where ID='%s'",Table_name,strID);
			pDB->Execute(strSQL);
			//重新执行记录集的原查询操作更新数据
			UpdateOthers(m_id,m_type,m_difficulty,m_chapter);
			pRs->Requery(adConnectUnspecified);
			
			//重新初始化combo
			InitCombo();
			//重新打开题库
			if(pRs->IsOpen())
				pRs->Close();
			CString strSql;
			strSql.Format("select * from %s order by ID",Table_name);			
			pRs->Open(strSql,CADORecordset.openQuery);
			RefreshList(*pRs);
			if(!Find_ID.IsEmpty())
				pRs->Find("ID="+Find_ID);
			SetAllControls();
			pDB->CommitTransaction();
		}
		catch(_com_error e)
		{
			pDB->RollbackTransaction();
			AfxMessageBox(e.ErrorMessage());
		}
	}
	if(pRs->GetRecordCount() <= 0)
	{
		m_buttonQueryOnly.EnableWindow(FALSE);
		m_buttonQuery.EnableWindow(FALSE);
		m_buttonPre.EnableWindow(FALSE);
		m_buttonOut.EnableWindow(FALSE);
		m_buttonNext.EnableWindow(FALSE);
		m_buttonLast.EnableWindow(FALSE);
		m_buttonFirst.EnableWindow(FALSE);
		m_buttonEdit.EnableWindow(FALSE);
		m_buttonDelete.EnableWindow(FALSE);
		m_buttonClear.EnableWindow(FALSE);
	}
}

//返回当前查询状态代码
int CQuestionDlg::State()
{
	//000
	if(m_selectType.IsEmpty() && m_selectDifficulty.IsEmpty() && m_selectChapter.IsEmpty())
		return 0;
	//001
	if(m_selectType.IsEmpty() && m_selectDifficulty.IsEmpty() && !m_selectChapter.IsEmpty())
		return 1;
	//010
	if(m_selectType.IsEmpty() && !m_selectDifficulty.IsEmpty() && m_selectChapter.IsEmpty())
		return 2;
	//011
	if(m_selectType.IsEmpty() && !m_selectDifficulty.IsEmpty() && !m_selectChapter.IsEmpty())
		return 3;
	//100
	if(!m_selectType.IsEmpty() && m_selectDifficulty.IsEmpty() && m_selectChapter.IsEmpty())
		return 4;
	//101
	if(!m_selectType.IsEmpty() && m_selectDifficulty.IsEmpty() && !m_selectChapter.IsEmpty())
		return 5;
	//110
	if(!m_selectType.IsEmpty() && !m_selectDifficulty.IsEmpty() && m_selectChapter.IsEmpty())
		return 6;
	//111
	if(!m_selectType.IsEmpty() && !m_selectDifficulty.IsEmpty() && !m_selectChapter.IsEmpty())
		return 7;
	return -1;
}

void CQuestionDlg::OnButtonQuery() 
{
	// TODO: Add your control notification handler code here
	if(!pRs->IsOpen())
		return;
	UpdateData(TRUE);
	pRs->Close();
	CString strSql;
	int state = State();
	switch(state)
	{
	case 0:
		{
			strSql.Format("select * from %s order by ID",Table_name);
			break;
		}
	case 1:
		{
			strSql.Format("select * from %s where Chapter='%s' order by ID",Table_name,m_selectChapter);
			break;
		}
	case 2:
		{
			strSql.Format("select * from %s where Difficulty='%s' order by ID",Table_name,m_selectDifficulty);
			break;
		}
	case 3:
		{
			strSql.Format("select * from %s where Difficulty='%s' and Chapter='%s' order by ID",Table_name,m_selectDifficulty,m_selectChapter);
			break;
		}
	case 4:
		{
			strSql.Format("select * from %s where Type='%s' order by ID",Table_name,m_selectType);
			break;
		}
	case 5:
		{
			strSql.Format("select * from %s where Type='%s' and Chapter='%s' order by ID",Table_name,m_selectType,m_selectChapter);
			break;
		}
	case 6:
		{
			strSql.Format("select * from %s where Type='%s' and Difficulty='%s' order by ID",Table_name,m_selectType,m_selectDifficulty);
			break;
		}
	case 7:
		{
			strSql.Format("select * from %s where Type='%s' and Difficulty='%s' and Chapter='%s' order by ID",Table_name,m_selectType,m_selectDifficulty,m_selectChapter);
			break;
		}
	case -1:
		{
			return;
		}
	}
	
	pRs->Open(strSql,CADORecordset.openQuery);
	RefreshList(*pRs);
	SetAllControls();
	m_questionList.SetFocus();
	m_questionList.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
	if(pRs->GetRecordCount() > 0)
	{
		m_buttonQueryOnly.EnableWindow(TRUE);
		m_buttonQuery.EnableWindow(TRUE);
		m_buttonPre.EnableWindow(TRUE);
		m_buttonOut.EnableWindow(TRUE);
		m_buttonNext.EnableWindow(TRUE);
		m_buttonLast.EnableWindow(TRUE);
		m_buttonFirst.EnableWindow(TRUE);
		m_buttonEdit.EnableWindow(TRUE);
		m_buttonDelete.EnableWindow(TRUE);
	}
	else
	{
		m_buttonQueryOnly.EnableWindow(FALSE);
		m_buttonQuery.EnableWindow(TRUE);
		m_buttonPre.EnableWindow(FALSE);
		m_buttonOut.EnableWindow(FALSE);
		m_buttonNext.EnableWindow(FALSE);
		m_buttonLast.EnableWindow(FALSE);
		m_buttonFirst.EnableWindow(FALSE);
		m_buttonEdit.EnableWindow(FALSE);
		m_buttonDelete.EnableWindow(FALSE);
	}
}

void CQuestionDlg::OnButtonQueryonly() 
{
	// TODO: Add your control notification handler code here
	if(!pRs->IsOpen())
		return;
	UpdateData(TRUE);
	if(m_queryid.IsEmpty())
	{	
		AfxMessageBox("请先输入试题ID再进行查询!");
		return;
	}
	pRs->Close();
	CString strSql;
	strSql.Format("select * from %s where ID='%s'",Table_name,m_queryid);
	pRs->Open(strSql,CADORecordset.openQuery);
	if(pRs->IsOpen() && pRs->GetRecordCount() == 0)
	{
		RefreshList(*pRs);
	    SetAllControls();
		AfxMessageBox("无此题!");
	}
	RefreshList(*pRs);
	SetAllControls();
	m_questionList.SetFocus();
	m_questionList.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
	if(pRs->GetRecordCount() > 0)
	{
		m_buttonQueryOnly.EnableWindow(TRUE);
		m_buttonQuery.EnableWindow(TRUE);
		m_buttonPre.EnableWindow(TRUE);
		m_buttonOut.EnableWindow(TRUE);
		m_buttonNext.EnableWindow(TRUE);
		m_buttonLast.EnableWindow(TRUE);
		m_buttonFirst.EnableWindow(TRUE);
		m_buttonEdit.EnableWindow(TRUE);
		m_buttonDelete.EnableWindow(TRUE);
	}
	else
	{
		m_buttonQueryOnly.EnableWindow(FALSE);
		m_buttonQuery.EnableWindow(TRUE);
		m_buttonPre.EnableWindow(FALSE);
		m_buttonOut.EnableWindow(FALSE);
		m_buttonNext.EnableWindow(FALSE);
		m_buttonLast.EnableWindow(FALSE);
		m_buttonFirst.EnableWindow(FALSE);
		m_buttonEdit.EnableWindow(FALSE);
		m_buttonDelete.EnableWindow(FALSE);
	}
}

bool IsNum(char c)
{
	if(c >= 48 && c <= 57)
		return true;
	else 
		return false;
}

BOOL CQuestionDlg::InsertNewItem(CString type,CString difficulty,CString chapter,CString content,CString answer)
{
	CString ID = "";
	ID += FindType(type);
	ID += FindDifficulty(difficulty);
	ID += FindChapter(chapter);
	ID += FindNum(type,difficulty,chapter);
	
	//插入记录到记录集
	pRs->AddNew();
	pRs->SetFieldValue("ID",ID);
	pRs->SetFieldValue("Type",type);
	pRs->SetFieldValue("Difficulty",difficulty);
	pRs->SetFieldValue("Chapter",chapter);
	pRs->SetFieldValue("Content",content);
	pRs->SetFieldValue("Answer",answer);
	pRs->Update();
	return TRUE;
}

CString CQuestionDlg::CanOpen(CString in_filename)
{
	CString strChapter = "";
	for(int i = 0 ; i < 30 ; i++)
	{
		int re = in_filename.Find(_T(Chapter_Chinese[i]),0);
		if(re != -1)
		{
			strChapter = Chapter_Chinese[i];
			return strChapter;
		}
	}
	return strChapter;
}

bool CQuestionDlg::IsStop(int index,int len)
{
	if(index == len)
	{
		if(index == len)
		{
			AfxMessageBox("文件格式不符合要求!试题无法导入!");
			return true;
		}
	}
	return false;
}

BOOL CQuestionDlg::ImportQuestiones(CString strChapter,CString strSel)
{
	char *con[1] = {""};
	con[0] = strSel.GetBuffer(1000);
	int i = 0;
	int length = strlen(con[0]);
	bool IsCanimport = true;
	pNode head = NULL;
	pNode p1,p2;

	while(i < length)
	{
		//开头有回车等字符
		while(con[0][i] != -95 && i < length)
			i++;

		if(IsStop(i,length))
		{
			IsCanimport = false;
			break;
		}
		
		//题型前括号
		while((con[0][i] == -95 && con[0][i+1] == -68 || con[0][i] == -68 && con[0][i-1] == -95) && i < length)	
			i++;

		if(IsStop(i,length))
		{
			IsCanimport = false;
			break;
		}

		//找题型
		int j = 0;
		char type[30];
		while(con[0][i] != '\r' && i < length)
		{
			//如果是题型标志后括号
			if(con[0][i] == -95 && con[0][i+1] == -67 || con[0][i] == -67 && con[0][i-1] == -95)
			{
				i++;
				continue;
			}
			type[j] = con[0][i];
			i++;
			j++;
		}
		type[j] = '\0';
		if(IsStop(i,length))
		{
			IsCanimport = false;
			break;
		}

		//类型  难度
		CString result = FindType(type);
		if(result.IsEmpty())
		{ 
			AfxMessageBox("文件中某些或全部题型不符合要求，无法导入!");    //类型不存在
			break;
		}

		
		i++;
		if(IsStop(i,length))
		{
			IsCanimport = false;
			break;
		}

		//空过回车
		while(con[0][i] == '\r' && i < length)
			i++;
		if(IsStop(i,length))
		{
			IsCanimport = false;
			break;
		}


		//找内容
		char content[10000];
		while(con[0][i] != '\r' && i < length)
		{
			int k = 0;
			//空过无效字符
			while(!IsNum(con[0][i]) && i < length)
				i++;
			if(IsStop(i,length))
			{
				IsCanimport = false;
				break;
			}

            //空过试题开始标志：数字. 
			while((IsNum(con[0][i]) || con[0][i] == '.') && i < length)
				i++;


			if(IsStop(i,length))
			{
				IsCanimport = false;
				break;
			}

			//遇到一行回车或者遇到答案标志结束内容
			while(!(con[0][i] == '\r' && con[0][i-1] == '\r') && !(con[0][i-1] == -95 && con[0][i] == -70) && i < length)
			{
				if(con[0][i] == '\r')
				{
					content[k] = '\r';
					k++;
					content[k] = '\n';
					k++;
				}
				else
				{
					if(con[0][i] != ' ')
					{
						content[k] = con[0][i];
					    k++;
					}
				}
				if(content[k-1] == -95 && content[k] == -70)
					content[k-1] = '\0';

				i++;
			}
			if(IsStop(i,length))
			{
				IsCanimport = false;
				break;
			}

			content[k] = '\0';
			char answer[10000] = "";

			//如果有答案
			if(con[0][i] == -70)
			{
				k = 0;
				//读过答案开始符号
				while(!(con[0][i] == -69 && con[0][i-1] == -95) && i < length)
					i++;
				i++;
				
				if(i != length)
				{				
					while(!(con[0][i] == '\r' && con[0][i-1] == '\r') && i < length)
					{
						if(con[0][i] == '\r')
						{
							answer[k] = '\r';
							k++;
							answer[k] = '\n';
						}
						else
							answer[k] = con[0][i];
						i++;
						k++;				
					}
					answer[k] = '\0';
				}
			}
			if(IsStop(i,length))
			{
				IsCanimport = false;
				break;
			}
			
			
	//***********************************************************
			if(!result.IsEmpty())
			{
				p1 = (pNode)malloc(sizeof(Node));

				strcpy(p1->type,type);
				strcpy(p1->difficulty,"中等");
				strcpy(p1->chapter,strChapter.GetBuffer(100));
				strcpy(p1->content,content);
				strcpy(p1->answer,answer);

				p1->next = NULL;

				if(!head)
					head = p1;
				else
					p2->next = p1;
				p2 = p1;
			}
			
			//跳过回车及空格
			while((con[0][i] == '\r' || con[0][i] == ' ') && i < length)
				i++;
			if(i == length)
			{
				AfxMessageBox("试题全部导入!");
				break;
			}

			//查看是否是新题型的开始
			if(con[0][i] == -95 && con[0][i+1] == -68)
				break;
		}

	}//endwhile
	if(IsCanimport)
	{
		pNode p = head;
		while(p)
		{
			CString strType = p->type;
			CString strDifficulty = p->difficulty;
			//内容  答案
			CString strContent = p->content;
			CString strAnswer = p->answer; 
			InsertNewItem(strType,strDifficulty,strChapter,strContent,strAnswer);
			p = p->next;
		}
	}
	p1 = head;
	while(p1)
	{
		p2 = p1;
		p1 = p1->next;
		delete p2;
	}
	//重新打开题库
	pRs->Close();
	CString strSql;
	strSql.Format("select * from %s order by ID",Table_name);			
	pRs->Open(strSql,CADORecordset.openQuery);

	if(IsCanimport)
		return TRUE;
	return FALSE;
}

void CQuestionDlg::OnButtonIn() 
{
	// TODO: Add your control notification handler code here
	
	if(pRs->IsOpen())
	{
		CLSID clsid;
		HRESULT hr;
		hr=::CLSIDFromProgID(L"Word.Application",&clsid);	//通过ProgID取得CLSID
		if(FAILED(hr))               //检测是否安装了office
		{
			AfxMessageBox(_T("没有安装OFFICE!"));
			return;
		}//endif

		//++++++++++打开一个word文档
		CString strFilename;
		CImportDlg importDlg;
		if(importDlg.DoModal() == IDOK)
			strFilename = importDlg.GetFilename();
		else
			return;
		
		
		//目录	
		char catalog[1000];
		int indexe = strFilename.ReverseFind('\\');		
		int i;
		for(i = 0 ; i < indexe+1 ; i++)
			catalog[i] = strFilename.GetAt(i);
		catalog[i] = '\0';

		//得到文件名.doc
		CString file = strFilename.Mid(indexe+1);		
		
		//++++++++是否可以打开++++++++     所属章节
		CString strChapter = CanOpen(file);
		if(strChapter.IsEmpty())
		{
			AfxMessageBox("所选文件命名不符合要求!");
			return;
		}
		
		ShellExecute(NULL,NULL,_T(file),NULL,_T(catalog),NULL);    //执行选中的word文档
		
		IUnknown *pUnknown = NULL;
		_Application app = NULL;
		Selection sel = NULL;	

		hr=::GetActiveObject(clsid,NULL,&pUnknown);	//查找是否有WORD程序在运行
		if(FAILED(hr))
		{
			AfxMessageBox(_T("没有正在运行中的WORD应用程序"));
			return;
		}//enfif
		
		try
		{
			hr = pUnknown->QueryInterface(IID_IDispatch,(LPVOID *)&app);  //获取IDispatchPtr
			if(FAILED(hr))	throw(_T("没有取得IDispatchPtr"));
			pUnknown->Release();	pUnknown=NULL;
			
			sel = app.GetSelection();
			if(!sel)	throw(_T("没有正在编辑的文档"));
			sel.WholeStory();				   //全部选择
			CString str = sel.GetText();		//取得文本

			if(MessageBox("是否导入该文档中试题?","确认导入试题",MB_ICONQUESTION|MB_OKCANCEL) == IDCANCEL)
				return;

			ImportQuestiones(strChapter,str);   //拆分试题并添加到试题库
			//重新初始化combo
			InitCombo();
			if(pRs->IsOpen())
				pRs->Close();

			CString strSql;
			strSql.Format("select * from %s order by ID",Table_name);
			pRs->Open(strSql,CADORecordset.openQuery);			
			RefreshList(*pRs);
			SetAllControls();
		}
		catch(LPCTSTR lpErr)
		{
			AfxMessageBox(lpErr);
		}
		if(pUnknown)	pUnknown->Release();
		if(sel)	sel.ReleaseDispatch();
		if(app)	sel.ReleaseDispatch();	
    }
	if(pRs->GetRecordCount() > 0)
	{
		m_buttonQueryOnly.EnableWindow(TRUE);
		m_buttonQuery.EnableWindow(TRUE);
		m_buttonPre.EnableWindow(TRUE);
		m_buttonOut.EnableWindow(TRUE);
		m_buttonNext.EnableWindow(TRUE);
		m_buttonLast.EnableWindow(TRUE);
		m_buttonFirst.EnableWindow(TRUE);
		m_buttonEdit.EnableWindow(TRUE);
		m_buttonDelete.EnableWindow(TRUE);
		m_buttonClear.EnableWindow(TRUE);
	}
	else
	{
		m_buttonQueryOnly.EnableWindow(FALSE);
		m_buttonQuery.EnableWindow(FALSE);
		m_buttonPre.EnableWindow(FALSE);
		m_buttonOut.EnableWindow(FALSE);
		m_buttonNext.EnableWindow(FALSE);
		m_buttonLast.EnableWindow(FALSE);
		m_buttonFirst.EnableWindow(FALSE);
		m_buttonEdit.EnableWindow(FALSE);
		m_buttonDelete.EnableWindow(FALSE);
		m_buttonClear.EnableWindow(FALSE);
	}
}

void CQuestionDlg::OnButtonOut() 
{
	// TODO: Add your control notification handler code here
	if((pRs->IsOpen())&&(pRs->GetRecordCount()!=0))
	{
		pRs->MoveFirst();
		
		CString strFilter;
		strFilter.LoadString(IDS_FILE_FILTER);
		CString Filename = "out";
		CFileDialog fileDlg(FALSE, NULL, Filename, NULL, strFilter, NULL);
		if(fileDlg.DoModal() != IDOK)
			return;
		CString strFilename = fileDlg.GetPathName();
		strFilename += ".doc";
		
		
		
		_Application app;
		app.CreateDispatch(_T("Word.Application"));
		app.SetVisible(TRUE);
		
		Documents docs=app.GetDocuments();
		CComVariant Template(_T(""));
		CComVariant NewTemplate(false),DocumentType(0),Visible;
		docs.Add(&Template,&NewTemplate,&DocumentType,&Visible);
		
		Selection sel=app.GetSelection();
		
		CString strAll = "";
		CString strID,strType,strDifficulty,strChapter,strContent,strAnswer;
		CString strOldType = "";
		int type_num = 0;
		while(!pRs->IsEOF())
		{
			pRs->GetFieldValue("ID",strID);
			pRs->GetFieldValue("Type",strType);
			pRs->GetFieldValue("Difficulty",strDifficulty);
			pRs->GetFieldValue("Chapter",strChapter);
			pRs->GetFieldValue("Content",strContent);
			pRs->GetFieldValue("Answer",strAnswer);
			
			//题型
			if(strcmp(strOldType,strType))
			{
				CString nowtype = "";
				if(type_num)
					CString nowtype = "\r\n";
				
				nowtype += "       +++++++++++++++++++++";
				nowtype += strType;
				nowtype += "+++++++++++++++++++++";
				nowtype += "\r\n\r\n";
				strAll += nowtype;
				
				type_num++;
			}
			
			if(strDifficulty.IsEmpty())
				strDifficulty = "无";
			if(strChapter.IsEmpty())
				strChapter = "无";
			if(strAnswer.IsEmpty())
				strAnswer = "无";
			
			//信息
			CString str = "[ID:";
			str += strID;
			str += " 难度:";
			str += strDifficulty;
			str += " 所属章节:";
			str += strChapter;
			str +="]\r\n";
			
			strAll += str;
			
			//内容
			strContent += "\r\n";
			strAll += strContent;
			
			//答案
			CString nowanswer = "答案:";
			nowanswer += strAnswer;
			nowanswer += "\r\n\r\n";
			strAll += nowanswer;
			
			strOldType = strType;
			pRs->MoveNext();
		}	
		
		sel.TypeText(_T(strAll));
		
		CString strSave = "是否保存文档1到";
		strSave += strFilename;
		if(MessageBox(strSave,"确认保存",MB_ICONQUESTION|MB_OKCANCEL) == IDOK)
		{
			_Document doc=app.GetActiveDocument();		//得到ActiveDocument
			CComVariant FileName(_T(strFilename));	//文件名
			CComVariant FileFormat(0);
			CComVariant LockComments(false),Password(_T(""));
			CComVariant AddToRecentFiles(true),WritePassword(_T(""));
			CComVariant ReadOnlyRecommended(false),EmbedTrueTypeFonts(false);
			CComVariant SaveNativePictureFormat(false),SaveFormsData(false);
			CComVariant SaveAsAOCELetter(false);
			
			doc.SaveAs(&FileName,&FileFormat,&LockComments,&Password,
				&AddToRecentFiles,&WritePassword,&ReadOnlyRecommended,
				&EmbedTrueTypeFonts,&SaveNativePictureFormat,&SaveFormsData,
				&SaveAsAOCELetter);
			doc.ReleaseDispatch();
		}
		sel.ReleaseDispatch();
		
		docs.ReleaseDispatch();
		
		CComVariant SaveChanges(false),OriginalFormat,RouteDocument;
		app.Quit(&SaveChanges,&OriginalFormat,&RouteDocument);
		app.ReleaseDispatch();

		pRs->MoveFirst();
		SetAllControls();	
	}	
}


void CQuestionDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	if(pRs && pRs->IsOpen())
	{	
		m_id = "";
		m_type = "";
		m_difficulty = "";
		m_chapter = "";
		m_content = "";
		m_answer = "";		
		m_questionList.DeleteAllItems();
		UpdateData(FALSE);
		pRs->Close();
	}
	m_buttonQueryOnly.EnableWindow(FALSE);
	m_buttonQuery.EnableWindow(FALSE);
	m_buttonPre.EnableWindow(FALSE);
	m_buttonOut.EnableWindow(FALSE);
	m_buttonNext.EnableWindow(FALSE);
	m_buttonLast.EnableWindow(FALSE);
	m_buttonIn.EnableWindow(FALSE);
	m_buttonFirst.EnableWindow(FALSE);
	m_buttonEdit.EnableWindow(FALSE);
	m_buttonDelete.EnableWindow(FALSE);
	m_buttonClear.EnableWindow(FALSE);
	m_buttonClose.EnableWindow(FALSE);
	m_buttonAdd.EnableWindow(FALSE);
	m_buttonConfirm.EnableWindow(TRUE);
	m_comboType.EnableWindow(FALSE);
	m_comboDifficulty.EnableWindow(FALSE);
	m_comboChapter.EnableWindow(FALSE);
	m_editQueryid.EnableWindow(FALSE);
	m_comboSubject.EnableWindow(TRUE);
}

void CQuestionDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	if((pRs->IsOpen())&&(pRs->GetRecordCount()>0))
	{
		CString strdelete = "要删除题库中全部试题?";
		if(MessageBox(strdelete,"确认清空",MB_ICONQUESTION|MB_OKCANCEL) == IDCANCEL)
			return;
		
		try
		{
			pDB->BeginTransaction();
			CString strID = m_id;
			CString strSQL;
			strSQL.Format("delete from %s",Table_name);
			pDB->Execute(strSQL);
			//重新执行记录集的原查询操作更新数据
			pRs->Requery(adConnectUnspecified);
			
			//重新初始化combo
			InitCombo();
			//重新打开题库
			if(pRs->IsOpen())
				pRs->Close();
			CString strSql;
			strSql.Format("select * from %s order by ID",Table_name);			
			pRs->Open(strSql,CADORecordset.openQuery);
			RefreshList(*pRs);
			pDB->CommitTransaction();
		}
		catch(_com_error e)
		{
			pDB->RollbackTransaction();
			AfxMessageBox(e.ErrorMessage());
		}
		MessageBox("试题全部清空!","提示",MB_ICONINFORMATION|MB_OK);
	}
	if(pRs->GetRecordCount() <= 0)
	{
		m_buttonQueryOnly.EnableWindow(FALSE);
		m_buttonQuery.EnableWindow(FALSE);
		m_buttonPre.EnableWindow(FALSE);
		m_buttonOut.EnableWindow(FALSE);
		m_buttonNext.EnableWindow(FALSE);
		m_buttonLast.EnableWindow(FALSE);
		m_buttonFirst.EnableWindow(FALSE);
		m_buttonEdit.EnableWindow(FALSE);
		m_buttonDelete.EnableWindow(FALSE);
		m_buttonClear.EnableWindow(FALSE);
	}
}

void CQuestionDlg::OnKeydownListQuestion(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
    int sel=m_questionList.GetSelectionMark();
	if(sel<0)
		return;
	else
	{
		CString strID = m_questionList.GetItemText(sel,0);		
		if(pRs->IsOpen())
		{
			if(pRs->Find("ID="+strID,1)||pRs->Find("ID="+strID,-1))
				SetAllControls();
		}
	}	*pResult = 0;
}
