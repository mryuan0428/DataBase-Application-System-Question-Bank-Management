// SelChapAndDiffDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "SelChapAndDiffDlg.h"
#include "AutoMakeupDlg.h"
#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelChapAndDiffDlg dialog
//定义全局变量
CString selDifficulty_Chinese[5] = {"易","较易","中等","较难","难"};
CString selChapter_Chinese[30] = {"第01章","第02章","第03章","第04章","第05章","第06章","第07章","第08章","第09章","第10章",
"第11章","第12章","第13章","第14章","第15章","第16章","第17章","第18章","第19章","第20章",
"第21章","第22章","第23章","第24章","第25章","第26章","第27章","第28章","第29章","第30章"};

CSelChapAndDiffDlg::CSelChapAndDiffDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelChapAndDiffDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelChapAndDiffDlg)
	m_strTitle = _T("");
	m_strDiffAll = _T("");
	m_strTypeExist = _T("");
	m_strTypeSel = _T("");
	m_strSelAll = _T("");
	//}}AFX_DATA_INIT
	for(int i = 0 ; i < 5 ; i++)
	{
		m_nDiff[i] = 0;
		m_strExistDiff[i] = "";
		nExistDiff[i] = 0;
	}
	Table_name = "";
	strType = "";
//    m_strDiffCount = "0";
//	m_strChapCount = "0";
	strSelChapter = "";
	strSelDifficulty = "";
	nChapnum = 0;
	nDiffnum = 0;
	for(i = 0 ; i < 30 ; i++)
		Chapter_num[i] = 0;
	for(i = 0 ; i < 5 ; i++)
		Difficulty_num[i]= 0;
	ChapOrDiff = true;
}


void CSelChapAndDiffDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelChapAndDiffDlg)
	DDX_Control(pDX, IDC_TREE_CHAPTER, m_chapterTree);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_STATIC_DIFFALL, m_strDiffAll);
	DDX_Text(pDX, IDC_STATIC_TYPEEXIST, m_strTypeExist);
	DDX_Text(pDX, IDC_STATIC_TYPESEL, m_strTypeSel);
	DDX_Text(pDX, IDC_STATIC_SELALL, m_strSelAll);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SPIN_MID, m_ctrlDiffSpin[2]);
	DDX_Control(pDX, IDC_SPIN_HARDER, m_ctrlDiffSpin[3]);
	DDX_Control(pDX, IDC_SPIN_HARD, m_ctrlDiffSpin[4]);
	DDX_Control(pDX, IDC_SPIN_EASY, m_ctrlDiffSpin[0]);
	DDX_Control(pDX, IDC_SPIN_EASIER, m_ctrlDiffSpin[1]);
	DDX_Control(pDX, IDC_EDIT_MID, m_editDiff[2]);
	DDX_Control(pDX, IDC_EDIT_HARDER, m_editDiff[3]);
	DDX_Control(pDX, IDC_EDIT_HARD, m_editDiff[4]);
	DDX_Control(pDX, IDC_EDIT_EASY, m_editDiff[0]);
	DDX_Control(pDX, IDC_EDIT_EASIER, m_editDiff[1]);
	DDX_Text(pDX, IDC_EDIT_EASIER, m_nDiff[1]);
	DDX_Text(pDX, IDC_EDIT_EASY, m_nDiff[0]);
	DDX_Text(pDX, IDC_EDIT_HARD, m_nDiff[4]);
	DDX_Text(pDX, IDC_EDIT_HARDER, m_nDiff[3]);
	DDX_Text(pDX, IDC_EDIT_MID, m_nDiff[2]);
	DDX_Text(pDX, IDC_STATIC_EASIER, m_strExistDiff[1]);
	DDX_Text(pDX, IDC_STATIC_EASY, m_strExistDiff[0]);
	DDX_Text(pDX, IDC_STATIC_HARD, m_strExistDiff[4]);
	DDX_Text(pDX, IDC_STATIC_HARDER, m_strExistDiff[3]);
	DDX_Text(pDX, IDC_STATIC_MID, m_strExistDiff[2]);
}


BEGIN_MESSAGE_MAP(CSelChapAndDiffDlg, CDialog)
	//{{AFX_MSG_MAP(CSelChapAndDiffDlg)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CHAPTER, OnClickTreeChapter)
	ON_NOTIFY(TVN_KEYDOWN, IDC_TREE_CHAPTER, OnKeydownTreeChapter)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UWM_TV_CHECKBOX, OnTvCheckbox)
//	ON_CONTROL_RANGE(UDN_DELTAPOS, IDC_SPIN_EASY, IDC_SPIN_HARD, OnDeltaposSpin)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelChapAndDiffDlg message handlers

BOOL CSelChapAndDiffDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CAutoMakeupDlg *parent = (CAutoMakeupDlg *)GetParent();
	pDB = parent->pDB;
	Table_name = parent->GetTableName();

	int index = parent->nButtonOther_index;
	int num = parent->m_nCount[index];
	CString strnum;
	strnum.Format(_T("%d"),num);
	strType = parent->m_str[index];
	m_strTitle = parent->m_str[index];
	m_strTitle += "(共 ";
	m_strTitle += strnum;
	m_strTitle += " 道)所属章节和难度选择：";

	m_strTypeExist = parent->m_str[index];
	m_strTypeExist += ":";
	m_strTypeSel = parent->m_str[index];
	m_strTypeSel += ":";
	UpdateData(FALSE);
//	InitCombo();
//	

	for(int i = 0 ; i < 5 ; i++)
	{
		m_strExistDiff[i] = selDifficulty_Chinese[i];
		m_strExistDiff[i] += "：";
		m_strExistDiff[i] += "0";
		//spin设置
		m_ctrlDiffSpin[i].SetBuddy(GetDlgItem(IDC_EDIT_EASY+i));
		m_ctrlDiffSpin[i].SetRange(0,100);
		m_ctrlDiffSpin[i].SetPos(0);
	}
	m_strDiffAll = "共：0";
//	m_strSelAll = "0";
	UpdateData(FALSE);

	InitChapterTree();

	//初始化
/*	m_buttonSelbychap.EnableWindow(FALSE);
	m_editChapter.EnableWindow(TRUE);
	m_comboChapter.EnableWindow(TRUE);
	m_buttonChapter.EnableWindow(TRUE);
//	m_listChapter.EnableWindow(TRUE);
	m_buttonSeldiff.EnableWindow(TRUE);
	m_buttonDelchap.EnableWindow(TRUE);

	m_buttonSelbydiff.EnableWindow(TRUE);
	m_editDifficulty.EnableWindow(FALSE);
	m_comboDifficulty.EnableWindow(FALSE);
	m_buttonDifficulty.EnableWindow(FALSE);
//	m_listDifficulty.EnableWindow(FALSE);
	m_buttonSelchap.EnableWindow(FALSE);
	m_buttonDeldiff.EnableWindow(FALSE);*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//初始化章节和难度combo
BOOL CSelChapAndDiffDlg::InitCombo()
{
/*	CAutoMakeupDlg *parent = (CAutoMakeupDlg *)GetParent();
	int i = 0;
	CString strChapter = parent->Chapter_all[i];
	if(strChapter.IsEmpty())
		return FALSE;
	while(!strChapter.IsEmpty() && i < 30)
	{
		m_comboChapter.AddString(strChapter);
		i++;
		if(i == 30)
			break;
		strChapter = parent->Chapter_all[i];
	}
	i = 0;
	for(i = 0 ; i < 5 ; i++)
	{
		CString strDifficulty = parent->Difficulty_all[i];
		if(!strDifficulty.IsEmpty())			
			m_comboDifficulty.AddString(strDifficulty);
	}*/
	return TRUE;
}


BOOL CSelChapAndDiffDlg::InitChapterTree()
{
	m_chapterTree.DeleteAllItems();
//	CString strChineseName = m_strSubject;
//	m_chapterTree.SetImageList(&m_ImgList,TVSIL_STATE);
//	m_chapterTree.ModifyStyle(0,TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|WS_BORDER);
	

	CAutoMakeupDlg *parent = (CAutoMakeupDlg *)GetParent();
	int i = 0;
	CString strChapter = parent->Chapter_all[i];
	if(strChapter.IsEmpty())
		return FALSE;
	while(!strChapter.IsEmpty() && i < 30)
	{
		m_chapterTree.InsertItem(_T(strChapter),0,1);
		i++;
		if(i == 30)
			break;
		strChapter = parent->Chapter_all[i];
	}

//	HTREEITEM hItem = m_chapterTree.GetRootItem();
//	m_chapterTree.SetCheck(hItem,TRUE);
//  m_chapterTree.SetItemState(hItem,TVIS_BOLD,TVIS_BOLD);
//	m_chapterTree.SetRedraw(TRUE);


/*	str = parent->strSelDiff[index];
	if(!str.IsEmpty())
	{
		int len = str.GetLength();
		char temp[1000];
		strcpy(temp,str.GetBuffer(100));
		int i = 0;
		while(i < len)
		{
			int j = 0;
			char chap[100];
			while(temp[i] != ',' && i < len)
			{
				chap[j] = temp[i];
				i++;
				j++;
			}
			chap[j] = '\0';
			CString strchap = chap;
			m_listDifficulty.AddString(strchap);
			i++;
		}
	}*/
	
	return TRUE;
}

void CSelChapAndDiffDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	for(int i = 0 ; i < 30 ; i++)
		Chapter_num[i] = 0;
	HTREEITEM hItem = m_chapterTree.GetRootItem();
	int count = m_chapterTree.GetCount();
	for(i = 0 ; i < count ; i++)
	{
		if(m_chapterTree.GetCheck(hItem))
		{
			nChapnum = 1;
			CString str = m_chapterTree.GetItemText(hItem);
			for(int j = 0 ; j < 30 ; j++)
				if(str == selChapter_Chinese[j])
					Chapter_num[j] = 1;         //是否选择某章节试题
		}
		hItem = m_chapterTree.GetNextItem(hItem,TVGN_NEXT);
	}
	//改变难度static值
	ExistDiffChange();
	for(i = 0 ; i < 5 ; i++)
	{
		Difficulty_num[i] = m_nDiff[i];        //选择某难度试题的数量
		if(m_nDiff[i] > nExistDiff[i])
		{
			AfxMessageBox("所选难度数量超出题库中题目数量!");
			return;
		}
	}

	CAutoMakeupDlg *parent = (CAutoMakeupDlg *)GetParent();
	int index = parent->nButtonOther_index;
	int num = parent->m_nCount[index];
	int sum = 0 ;
	for(i = 0 ; i < 5 ; i++)
	{
		sum += Difficulty_num[i];
	}
	if(sum != num && sum != 0)
	{
		AfxMessageBox("难度限制题目数量不正确!");
		return;
	}

	sum = 0;
	for(i = 0 ; i < 5 ; i++)
	{
		sum += nExistDiff[i];
	}
	if(sum != 0 && sum < num)
	{
		AfxMessageBox("所选章节的试题总数不能达到要求!");
		return;
	}

/*	for(int i = 0 ; i < 30 ; i++)
		Chapter_num[i] = 0;
	for(i = 0 ; i < 5 ; i++)
		Difficulty_num[i] = 0;
	CAutoMakeupDlg *parent = (CAutoMakeupDlg *)GetParent();
	int index = parent->nButtonOther_index;
	int num = parent->m_nCount[index];
	int chap_num = 0;
	int diff_num = 0;
	
	int nCount = m_listChapter.GetCount();
	for(i = 0 ; i < nCount ; i++)
	{
		CString str;
		m_listChapter.GetText(i,str);
		strSelChapter += str;
		if(i != nCount-1)
			strSelChapter += ",";
		int n = 0;
		int j = 0;

		char ch[7];
		int k = 0;
		//计算数量
		char c = str.GetAt(j);
		while(!IsNum(c))
		{
			ch[k] = c;
			k++;
			j++;
			c = str.GetAt(j);
		}
		
		while(IsNum(c))
		{
			ch[k] = c;
			k++;
			j++;
			c = str.GetAt(j);
		}
		while(!IsNum(c))
		{
			ch[k] = c;
			k++;
			j++;
			c = str.GetAt(j);
		}
		ch[k] = '\0';
//共几题		
		while(IsNum(c))
		{
			n = n * 10 + c - 48;
			j++;
			c = str.GetAt(j);
		}

		int index = BelongTo(TRUE,ch);
		if(index != -1)
		{
			Chapter_num[index] = n;
		}
		chap_num += n;
		nChapnum = chap_num;
	}
	if(chap_num != num && chap_num != 0)
	{
		AfxMessageBox("章节限制的题目数量不正确!");
		strSelChapter = "";
		nChapnum = 0;
		strSelDifficulty = "";
		nDiffnum = 0;
		return;
	}
	
	nCount = m_listDifficulty.GetCount();
	for(i = 0 ; i < nCount ; i++)
	{
		CString str;
		m_listDifficulty.GetText(i,str);
		strSelDifficulty += str;
		if(i != nCount-1)
			strSelDifficulty += ",";
		int n = 0;
		char di[5];
		int k = 0;
//计算数量
		int j = 0;
		char c = str.GetAt(j);
		while(!IsNum(c) && j < str.GetLength())
		{
			di[k] = c;
			k++;
			j++;
			c = str.GetAt(j);
		}
		di[k] = '\0';
		while(IsNum(c))
		{
			n = n * 10 + c - 48;
			j++;
			c = str.GetAt(j);
		}

		int index = BelongTo(FALSE,di);
		if(index != -1)
		{
			Difficulty_num[index] = n;
		}
		diff_num += n;
		nDiffnum = diff_num;
	}
	if(diff_num != num && diff_num != 0)
	{
		AfxMessageBox("难度限制的题目数量不正确!");
		strSelDifficulty = "";
		nDiffnum = 0;
		strSelChapter = "";
		nChapnum = 0;
		return;
	}
	for(i = 0 ; i < 30 ; i++)
		if(Chapter_num[i] > 0)
			for(int j = 0 ; j < 5 ; j++)
			{
				if(Difficulty_num[j] <= 0)
					continue;
				if(!CanSave(TRUE,selChapter_Chinese[i],Chapter_num[i],selDifficulty_Chinese[j],Difficulty_num[j]))
				{
					AfxMessageBox("由于题目数量有限，章节和难度选择有冲突!");
					strSelChapter = "";
					nChapnum = 0;
					strSelDifficulty = "";
					nDiffnum = 0;
					return;
				}
			}
	for(i = 0 ; i < 5 ; i++)
		if(Difficulty_num[i] > 0)
			for(int j = 0 ; j < 30 ; j++)
			{
				if(Chapter_num[j] <= 0)
					continue;
				if(!CanSave(FALSE,selChapter_Chinese[j],Chapter_num[j],selDifficulty_Chinese[i],Difficulty_num[i]))
				{
					strSelChapter = "";
					strSelDifficulty = "";
					nDiffnum = 0;
					nChapnum = 0;
					AfxMessageBox("由于题目数量有限，章节和难度选择有冲突!");
					return;
				}
			}*/
	CDialog::OnOK();
}

void CSelChapAndDiffDlg::ExistDiffChange()
{
	for(int i = 0 ; i < 5 ; i++)
		nExistDiff[i] = 0;
	for(i = 0 ; i < 30 ; i++)
	{
		if(Chapter_num[i] == 1)
		{
			CADORecordset* pRs = new CADORecordset(pDB);
			CString strSQL;
			int all_num = 0;
			for(int j = 0 ; j < 5 ; j++)
			{
				strSQL.Format("select * from %s where Type='%s' and Chapter='%s' and Difficulty='%s'",Table_name,strType,selChapter_Chinese[i],selDifficulty_Chinese[j]);
				pRs->Open(_bstr_t(strSQL),CADORecordset.openQuery);
				int num = pRs->GetRecordCount();
				nExistDiff[j] += num;
				pRs->Close();
			}
			delete pRs;				
		}
	}
	int sum = 0;
	for(i = 0 ; i < 5 ; i++)
	{
		sum += nExistDiff[i];
		CString str;
		str.Format(_T("%d"),nExistDiff[i]);
		m_strExistDiff[i] = selDifficulty_Chinese[i];
		m_strExistDiff[i] += "：";
		m_strExistDiff[i] += str;
	}
	CString str;
	str.Format(_T("%d"),sum);
	m_strDiffAll = "共：";
	m_strDiffAll += str;

	UpdateData(FALSE);
}

LRESULT CSelChapAndDiffDlg::OnTvCheckbox(WPARAM wp, LPARAM lp)
{
	// CTreeCtrl & tree = GetDlgItem(wp);  -- if we have multiple trees
	for(int i = 0 ; i < 30 ; i++)
		Chapter_num[i] = 0;
	HTREEITEM hItem = m_chapterTree.GetRootItem();
	int count = m_chapterTree.GetCount();
	for(i = 0 ; i < count ; i++)
	{
		if(m_chapterTree.GetCheck(hItem))
		{
			CString str = m_chapterTree.GetItemText(hItem);
			for(int j = 0 ; j < 30 ; j++)
				if(str == selChapter_Chinese[j])
					Chapter_num[j] = 1;
		}
		hItem = m_chapterTree.GetNextItem(hItem,TVGN_NEXT);
	}
	//改变难度static值
	ExistDiffChange();
	return 0;
}

void CSelChapAndDiffDlg::OnClickTreeChapter(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DWORD dw = GetMessagePos();
	CPoint p(GET_X_LPARAM(dw), GET_Y_LPARAM(dw));
	m_chapterTree.ScreenToClient(&p);
	
	UINT htFlags = 0;
	HTREEITEM it = m_chapterTree.HitTest(p, &htFlags);
	
	if (it != NULL && (htFlags & TVHT_ONITEMSTATEICON)) {   
		// the check box was hit.
		// we post a message, and evaluate the new state in the Message Handler fopr the 'user defined' WM_APP message
		PostMessage(UWM_TV_CHECKBOX, pNMHDR->idFrom, (LPARAM) it);
	}
	*pResult = 0;
}

void CSelChapAndDiffDlg::OnKeydownTreeChapter(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (pTVKeyDown->wVKey == VK_SPACE) {
        HTREEITEM it = m_chapterTree.GetSelectedItem();
        PostMessage(UWM_TV_CHECKBOX, pNMHDR->idFrom, (LPARAM) it);
    }
	*pResult = 0;
}

/*void CSelChapAndDiffDlg::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult,UINT nID) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	int index = nID - IDC_EDIT_EASY;
	UpdateData(TRUE);

	if(m_nDiff[index] > nExistDiff[index])
	{
		m_nDiff[index]--;
		UpdateData(FALSE);
		return;
	}
	int sum = atoi(m_strSelAll);
	int num = m_nDiff[index];
	if(pNMUpDown->iDelta == 1)
	{
		if(num < 100)
			sum++;
	}
	else
	{
		if(num > 0)
			sum--;
	}
	m_strSelAll.Format(_T("%d"),sum);
	UpdateData(FALSE);
	*pResult = 0;
}*/
