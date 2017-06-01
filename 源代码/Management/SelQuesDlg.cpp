// SelQuesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "SelQuesDlg.h"
#include "PersonMakeupDlg.h"
#include "msword.h"
#include <AtlBase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelQuesDlg dialog


CSelQuesDlg::CSelQuesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelQuesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelQuesDlg)
	m_selectChapter = _T("");
	m_selectDifficulty = _T("");
	m_answer = _T("");
	m_chapter = _T("");
	m_content = _T("");
	m_queryid = _T("");
	m_type = _T("");
	m_strTitle = _T("");
	m_difficulty = _T("");
	m_id = _T("");
	m_strNum = _T("");
	//}}AFX_DATA_INIT
}

CSelQuesDlg::~CSelQuesDlg()
{
	//关闭记录集
	if(pRs && pRs->IsOpen())
		pRs->Close();
	if(pRs)
		delete(pRs);
}

void CSelQuesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelQuesDlg)
	DDX_Control(pDX, IDC_LIST_SELECT, m_selectList);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_buttonAdd);
	DDX_Control(pDX, IDC_BUTTON_QUERYONLY, m_buttonQueryOnly);
	DDX_Control(pDX, IDC_BUTTON_QUERY, m_buttonQuery);
	DDX_Control(pDX, IDC_BUTTON_OUT, m_buttonOut);
	DDX_Control(pDX, IDC_BUTTON_PRE, m_buttonPre);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_buttonNext);
	DDX_Control(pDX, IDC_BUTTON_LAST, m_buttonLast);
	DDX_Control(pDX, IDC_BUTTON_FIRST, m_buttonFirst);
	DDX_Control(pDX, IDC_EDIT_ID, m_editID);
	DDX_Control(pDX, IDC_LIST_QUESTION, m_questionList);
	DDX_Control(pDX, IDC_EDIT_TYPE, m_editType);
	DDX_Control(pDX, IDC_EDIT_DIFFICULTY, m_editDifficulty);
	DDX_Control(pDX, IDC_EDIT_CONTENT, m_editContent);
	DDX_Control(pDX, IDC_EDIT_CHAPTER, m_editChapter);
	DDX_Control(pDX, IDC_EDIT_ANSWER, m_editAnswer);
	DDX_Control(pDX, IDC_COMBO_DIFFICULTY, m_comboDifficulty);
	DDX_Control(pDX, IDC_COMBO_CHAPTER, m_comboChapter);
	DDX_CBString(pDX, IDC_COMBO_CHAPTER, m_selectChapter);
	DDX_CBString(pDX, IDC_COMBO_DIFFICULTY, m_selectDifficulty);
	DDX_Text(pDX, IDC_EDIT_ANSWER, m_answer);
	DDX_Text(pDX, IDC_EDIT_CHAPTER, m_chapter);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_content);
	DDX_Text(pDX, IDC_EDIT_QUERYID, m_queryid);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_type);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_DIFFICULTY, m_difficulty);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDX_Text(pDX, IDC_STATIC_NUM, m_strNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelQuesDlg, CDialog)
	//{{AFX_MSG_MAP(CSelQuesDlg)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_PRE, OnButtonPre)
	ON_BN_CLICKED(IDC_BUTTON_OUT, OnButtonOut)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_QUERYONLY, OnButtonQueryonly)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_QUESTION, OnClickListQuestion)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelQuesDlg message handlers

BOOL CSelQuesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CPersonMakeupDlg *parent = (CPersonMakeupDlg *)GetParent();
	pDB = parent->pDB;
	pRs=new CADORecordset(pDB);
	Table_name = parent->GetTableName();   //得到表名

	int index = parent->nButtonOther_index;
	int num = parent->m_nCount[index];
	CString strnum;
	strnum.Format(_T("%d"),num);
	strType = parent->m_str[index];       //得到类型
	m_strTitle = parent->m_str[index];
	m_strTitle += "(共 ";
	m_strTitle += strnum;
	m_strTitle += " 道)请选择试题：";
	m_strNum = "0";
	UpdateData(FALSE);

	//初始化所有控件
	m_editID.SetReadOnly(TRUE);
	m_editType.SetReadOnly(TRUE);
	m_editDifficulty.SetReadOnly(TRUE);
	m_editChapter.SetReadOnly(TRUE);
	m_editContent.SetReadOnly(TRUE);
	m_editAnswer.SetReadOnly(TRUE);

	if(!Table_name.IsEmpty())
	{
		//定义字符串存储SQL语句
		CString strSql;
		//初始化SQL语句字符串，获得所选题库的数据
		strSql.Format("select * from %s where Type='%s' order by ID",Table_name,strType);
		
		//打开当前选中的题库
		pRs->Open(strSql,CADORecordset.openQuery);
	}
	if(pRs->IsOpen())
	{
		InitCombo();
		InitQuestionList();
		InitSelectList();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSelQuesDlg::InitCombo()
{
	CPersonMakeupDlg *parent = (CPersonMakeupDlg *)GetParent();
	int i = 0;
	CString strChapter = parent->Chapter_all[i];
	if(strChapter.IsEmpty())
		return FALSE;
	m_comboChapter.AddString("");
	while(!strChapter.IsEmpty() && i < 30)
	{
		m_comboChapter.AddString(strChapter);
		i++;
		if(i == 30)
			break;
		strChapter = parent->Chapter_all[i];
	}
	m_comboDifficulty.AddString("");
	i = 0;
	for(i = 0 ; i < 5 ; i++)
	{
		CString strDifficulty = parent->Difficulty_all[i];
		if(!strDifficulty.IsEmpty())			
			m_comboDifficulty.AddString(strDifficulty);
	}
	return TRUE;
}

BOOL CSelQuesDlg::InitQuestionList()
{
	//初始化List控件的栏目
	m_questionList.InsertColumn(0,"ID",LVCFMT_LEFT,75,-1);
	m_questionList.InsertColumn(1,"题型",LVCFMT_LEFT,85,-1);
	m_questionList.InsertColumn(2,"难度",LVCFMT_LEFT,60,-1);
	m_questionList.InsertColumn(3,"所属章节",LVCFMT_LEFT,77,-1);
	
	//设置List的行被选中时是全行
	m_questionList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

    RefreshList(*pRs);
	SetAllControls();
	
	m_questionList.SetFocus();
	m_questionList.SetItemState(0,LVIS_SELECTED, LVIS_SELECTED);
	return TRUE;
}

BOOL CSelQuesDlg::InitSelectList()
{
	CPersonMakeupDlg *parent = (CPersonMakeupDlg *)GetParent();
	int index = parent->nButtonOther_index;
	CString str = parent->strSelQues[index];
	if(!str.IsEmpty())
	{
		int num = parent->m_nCount[index];
		m_strNum.Format(_T("%d"),num);
		UpdateData(FALSE);

		int len = str.GetLength();
		char temp[1000];
		strcpy(temp,str.GetBuffer(100));
		int i = 0;
		while(i < len)
		{
			int j = 0;
			char ques[100];
			while(temp[i] != ',' && i < len)
			{
				ques[j] = temp[i];
				i++;
				j++;
			}
			ques[j] = '\0';
			CString strques = ques;
			m_selectList.AddString(strques);
			i++;
		}
		return TRUE;
	}
	return FALSE;
}

void CSelQuesDlg::RefreshList(CADORecordset &recordset)
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

		m_buttonLast.EnableWindow(FALSE);
		m_buttonNext.EnableWindow(FALSE);
		m_buttonFirst.EnableWindow(FALSE);
		m_buttonPre.EnableWindow(FALSE);
		m_buttonAdd.EnableWindow(FALSE);
		m_buttonOut.EnableWindow(FALSE);

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
	m_buttonFirst.EnableWindow(FALSE);
	m_buttonPre.EnableWindow(FALSE);
	m_buttonAdd.EnableWindow(TRUE);
	m_buttonOut.EnableWindow(TRUE);

	if(recordset.GetRecordCount() > 1)
	{
		m_buttonLast.EnableWindow(TRUE);
		m_buttonNext.EnableWindow(TRUE);
	}
	else
	{
		m_buttonLast.EnableWindow(FALSE);
		m_buttonNext.EnableWindow(FALSE);
	}
}

void CSelQuesDlg::SetAllControls()
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

void CSelQuesDlg::OnButtonFirst() 
{
	// TODO: Add your control notification handler code here
	if((pRs->IsOpen())&&(pRs->GetRecordCount()!=0))
	{
		pRs->MoveFirst();
		SetAllControls();
		m_buttonFirst.EnableWindow(FALSE);
	    m_buttonPre.EnableWindow(FALSE);
		m_buttonLast.EnableWindow(TRUE);
		m_buttonNext.EnableWindow(TRUE);
	}
}

void CSelQuesDlg::OnButtonLast() 
{
	// TODO: Add your control notification handler code here
	if((pRs->IsOpen())&&(pRs->GetRecordCount()!=0))
	{
		pRs->MoveLast();
		SetAllControls();
		m_buttonFirst.EnableWindow(TRUE);
	    m_buttonPre.EnableWindow(TRUE);
		m_buttonLast.EnableWindow(FALSE);
		m_buttonNext.EnableWindow(FALSE);
	}
}

void CSelQuesDlg::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	if((pRs->IsOpen())&&(pRs->GetRecordCount()!=0)&&(!pRs->IsEOF()))
	{	
		pRs->MoveNext();
		//判断是不是最后一条记录
		pRs->MoveNext();
		if (pRs->IsEOF()) 
		{
			//			pRs->MovePrevious();
			m_buttonLast.EnableWindow(FALSE);
			m_buttonNext.EnableWindow(FALSE);
			//		AfxMessageBox("末记录!");
			//		return;
		}
		//恢复
		pRs->MovePrevious();
		SetAllControls();
		m_buttonFirst.EnableWindow(TRUE);
		m_buttonPre.EnableWindow(TRUE);
		
	}
}

void CSelQuesDlg::OnButtonPre() 
{
	// TODO: Add your control notification handler code here
	if((pRs->IsOpen())&&(pRs->GetRecordCount()!=0)&&(!pRs->IsBOF()))
	{
		pRs->MovePrevious();
		//判断是不是第一条记录
		pRs->MovePrevious();
		if (pRs->IsBOF()) 
		{
			m_buttonFirst.EnableWindow(FALSE);
			m_buttonPre.EnableWindow(FALSE);
		}
		//恢复
		pRs->MoveNext();
		SetAllControls();
		m_buttonLast.EnableWindow(TRUE);
		m_buttonNext.EnableWindow(TRUE);
	}
}

void CSelQuesDlg::OnButtonOut() 
{
	// TODO: Add your control notification handler code here
/*	if((pRs->IsOpen())&&(pRs->GetRecordCount()!=0))
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
		
		try
		{			
			HANDLE hFind; 
			WIN32_FIND_DATA findData = {0}; 
			hFind = FindFirstFile(strFilename,&findData); 
			
			// FindFirstFile是Windows API 函数 
			
			if(hFind != INVALID_HANDLE_VALUE)
			{
				DeleteFile(strFilename); //利用API函数删除该临时文件 
			}
			
			//modeCreate指示构造函数创建一个新文件 
			CFile outFile(strFilename,CFile::modeCreate|CFile::modeWrite);
			
			//下面这段把已经在内存中的BLOB字段数据内容写到生成的文件中
			CString strID,strDifficulty,strChapter,strContent,strAnswer;
	
			char *all[] = {"","","",""};
			LPSTR buffer;
			int len;

			//题型
			CString nowtype = "";			
			nowtype += "       +++++++++++++++++++++";
			nowtype += strType;
			nowtype += "+++++++++++++++++++++";
			nowtype += "\r\n\r\n";
			all[1] = nowtype.GetBuffer(100);
			buffer = (LPSTR)all[1];
			len = strlen(all[1]);
			outFile.WriteHuge(buffer,len);

			while(!pRs->IsEOF())
			{
				pRs->GetFieldValue("ID",strID);
				pRs->GetFieldValue("Difficulty",strDifficulty);
				pRs->GetFieldValue("Chapter",strChapter);
				pRs->GetFieldValue("Content",strContent);
				pRs->GetFieldValue("Answer",strAnswer);
				
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
				
				all[0] = str.GetBuffer(100);
				buffer = (LPSTR)all[0];
				len = strlen(all[0]);
				outFile.WriteHuge(buffer,len);
				
				//内容
				strContent += "\r\n";
				all[2] = strContent.GetBuffer(100);
				//			strcpy(all[4],strContent.GetBuffer(100));
				buffer = (LPSTR)all[2];
				len = strlen(all[2]);
				outFile.WriteHuge(buffer,len);
				
				//答案
				CString nowanswer = "答案:";
				nowanswer += strAnswer;
				nowanswer += "\r\n\r\n";
				all[3] = nowanswer.GetBuffer(100);
				buffer = (LPSTR)all[3];
				len = strlen(all[3]);
				outFile.WriteHuge(buffer,len);
				
				pRs->MoveNext();
			}
			
			
			outFile.Close(); 
			//目录
			char name[100];
			strcpy(name,strFilename.GetBuffer(100));
			
			char catalog[1000];
			int indexe = strFilename.ReverseFind('\\');		
			int i;
			for(i = 0 ; i < indexe+1 ; i++)
				catalog[i] = name[i];
			catalog[i] = '\0';
			
			CString file = strFilename.Mid(indexe+1);
			
			ShellExecute(NULL,NULL,_T(file),NULL,_T(catalog),NULL);
		}
		catch(CException pE)         //下面执行外部程序，Word会自动启动并打开文件  
		{
			pE.ReportError(); 
			pE.Delete(); 
			return; 
		}
		pRs->MoveFirst();
		SetAllControls();	
	}	*/
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
		CString strID,strDifficulty,strChapter,strContent,strAnswer;
		//题型
		CString nowtype = "";			
		nowtype += "       +++++++++++++++++++++";
		nowtype += strType;
		nowtype += "+++++++++++++++++++++";
		nowtype += "\r\n\r\n";
		strAll += nowtype;

		while(!pRs->IsEOF())
		{
			pRs->GetFieldValue("ID",strID);
			pRs->GetFieldValue("Type",strType);
			pRs->GetFieldValue("Difficulty",strDifficulty);
			pRs->GetFieldValue("Chapter",strChapter);
			pRs->GetFieldValue("Content",strContent);
			pRs->GetFieldValue("Answer",strAnswer);
			
	
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

//返回当前查询状态代码
int CSelQuesDlg::State()
{
	//00
	if(m_selectDifficulty.IsEmpty() && m_selectChapter.IsEmpty())
		return 0;
	//01
	if(m_selectDifficulty.IsEmpty() && !m_selectChapter.IsEmpty())
		return 1;
	//10
	if(!m_selectDifficulty.IsEmpty() && m_selectChapter.IsEmpty())
		return 2;
	//11
	if(!m_selectDifficulty.IsEmpty() && !m_selectChapter.IsEmpty())
		return 3;
	return -1;
}

void CSelQuesDlg::OnButtonQuery() 
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
			strSql.Format("select * from %s where Type='%s' order by ID",Table_name,strType);
			break;
		}
	case 1:
		{
			strSql.Format("select * from %s where Type='%s' and Chapter='%s' order by ID",Table_name,strType,m_selectChapter);
			break;
		}
	case 2:
		{
			strSql.Format("select * from %s where Type='%s' and Difficulty='%s' order by ID",Table_name,strType,m_selectDifficulty);
			break;
		}
	case 3:
		{
			strSql.Format("select * from %s where Type='%s' and Difficulty='%s' and Chapter='%s' order by ID",Table_name,strType,m_selectDifficulty,m_selectChapter);
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
}

void CSelQuesDlg::OnButtonQueryonly() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(pRs->IsOpen())
		pRs->Close();
	CString strSql;
	strSql.Format("select * from %s where Type='%s' order by ID",Table_name,strType);
	pRs->Open(strSql,CADORecordset.openQuery);
	CString strID = "";
	if(pRs->IsOpen() && pRs->GetRecordCount() > 0)
	{
		while(!pRs->IsEOF())
		{
			pRs->GetFieldValue("ID",strID);
			if(m_queryid == strID)
				break;
			pRs->MoveNext();
		}
		if(pRs->IsEOF())
		{
			m_id = "";
			m_type = "";
			m_difficulty = "";
			m_chapter = "";
			m_content = "";
			m_answer = "";
			m_questionList.DeleteAllItems();
			
			m_buttonLast.EnableWindow(FALSE);
			m_buttonNext.EnableWindow(FALSE);
			m_buttonFirst.EnableWindow(FALSE);
			m_buttonPre.EnableWindow(FALSE);
			m_buttonOut.EnableWindow(FALSE);
			m_buttonAdd.EnableWindow(FALSE);

			UpdateData(FALSE);
			AfxMessageBox("无此题!");
		}
		else
		{
			pRs->Close();
			strSql.Format("select * from %s where ID='%s' order by ID",Table_name,strID);
			pRs->Open(strSql,CADORecordset.openQuery);
			RefreshList(*pRs);
			SetAllControls();
		}
	}	
}

BOOL CSelQuesDlg::IsExist(CString str)
{
	int nCount = m_selectList.GetCount();
	for(int i = 0 ; i < nCount ; i++)
	{
		CString strExist;
		m_selectList.GetText(i,strExist);
		if(str == strExist)
			return TRUE;
	}
	return FALSE;
}

void CSelQuesDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	if(IsExist(m_id))
	{
		AfxMessageBox("不能重复选择试题!");
		return;
	}
	m_selectList.AddString(m_id);
	int num = atoi(m_strNum);
	num++;
	CString temp;
	temp.Format(_T("%d"),num);
	m_strNum = temp;
	UpdateData(FALSE);
}

void CSelQuesDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	int No = m_selectList.GetCurSel();
	if(No != -1)
	{
		m_selectList.DeleteString(No);
		int num = atoi(m_strNum);
		num--;
		CString temp;
		temp.Format(_T("%d"),num);
		m_strNum = temp;
		UpdateData(FALSE);
	}
}

void CSelQuesDlg::OnClickListQuestion(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int sel=m_questionList.GetSelectionMark();
	if(sel<0)
		return;
	else
	{
		m_buttonFirst.EnableWindow(TRUE);
	    m_buttonPre.EnableWindow(TRUE);
		m_buttonLast.EnableWindow(TRUE);
		m_buttonNext.EnableWindow(TRUE);
		CString strID = m_questionList.GetItemText(sel,0);		
		if(pRs->IsOpen())
		{
			if(pRs->Find("ID="+strID,1)||pRs->Find("ID="+strID,-1))
				SetAllControls();
		}
		//判断是否是第一题或最后一题
		pRs->MovePrevious();
		if (pRs->IsBOF()) 
		{
			m_buttonFirst.EnableWindow(FALSE);
			m_buttonPre.EnableWindow(FALSE);
		}
		//恢复
		pRs->MoveNext();

		pRs->MoveNext();
		if (pRs->IsEOF()) 
		{
			m_buttonLast.EnableWindow(FALSE);
			m_buttonNext.EnableWindow(FALSE);
		}
		//恢复
		pRs->MovePrevious();
	}
	*pResult = 0;
}

void CSelQuesDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CPersonMakeupDlg *parent = (CPersonMakeupDlg *)GetParent();
	int index = parent->nButtonOther_index;
	int num = parent->m_nCount[index];   //总数目
	
	int nCount = m_selectList.GetCount();
	if(nCount != num)
	{
		AfxMessageBox("所选题目数量不正确!");
		strSelQues = "";
		return;
	}
	for(int i = 0 ; i < nCount ; i++)
	{
		CString str;
		m_selectList.GetText(i,str);
		strSelQues += str;
		if(i != nCount-1)
			strSelQues += ",";
	}
	CDialog::OnOK();
}
