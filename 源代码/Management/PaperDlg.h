#if !defined(AFX_PAPERDLG_H__027A1889_5D95_442D_9432_E5BADC076BC7__INCLUDED_)
#define AFX_PAPERDLG_H__027A1889_5D95_442D_9432_E5BADC076BC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaperDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPaperDlg dialog

class CPaperDlg : public CDialog
{
// Construction
	CString strUsername;     //用户名(导入试卷用)
	BOOL Purview;       //是否是系统管理员
	CString ExistTable_name;   //当前导入试卷所属表名
	CString Exist_ID;         //当前导入试卷ID
	CString Now_ID;           //当前选中试卷ID
public:
	CPaperDlg(CWnd* pParent = NULL);   // standard constructor
	CADODatabase *pDB;
	CString GetUsername(){return strUsername;};

// Dialog Data
	//{{AFX_DATA(CPaperDlg)
	enum { IDD = IDD_DIALOG_PAPER };
	CListCtrl	m_listPaper;        //试卷列表
	CDateTimeCtrl	m_DateTo;       //结束时间控件
	CListCtrl	m_listQuestion;     //试题列表
	CDateTimeCtrl	m_DateFrom;     //开始时间控件
	CComboBox	m_comboSubject;     //选择科目Combo
	CComboBox	m_comboCreateperson;  //选择创建人Combo
	CTreeCtrl	m_paperTree;        //试卷树形控件
	CButton	m_buttonAnswer;         //导入答案按钮
	BOOL	m_checkDate;            //是否按时间查询
	CString	m_strCreateperson;      //创建人
	CString	m_strSubject;           //试卷科目
	CString	m_strID;                //精确查询ID
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaperDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	CImageList m_ImgList;          //树形结构(m_ImgLst.Create(IDB_TREE,16,1,RGB(0,255,255));  m_wndTree.SetImageList(&m_ImgLst,TVSIL_NORMAL);加图标)
	BOOL InitComboSubject();       //初始化科目Combo   
	BOOL InitComboCreate();        //选定科目后初始化创建人Combo
	BOOL InitPaperList();          //变化时初始化试卷列表
	BOOL InitPaperTree();          //变化时初始化试卷树形控件
	CString FindtbPaper(CString strChineseName);    //通过科目名称返回已组试卷表名
	CString FindtbExist(CString strChineseName);    //通过科目名称返回成套试卷表名
	BOOL InsertPaperItem(HTREEITEM hItem,CString strPaperName);  //将已组试卷插入树形控件
	BOOL InsertExistItem(HTREEITEM hItem,CString strExistName);  //将成套试卷插入树形控件
	void RefreshList(BOOL PaperOrExist,CADORecordset &recordset); //更新试卷列表
	void UpdateQuestionList(CADORecordset &recordset);           //更新试题列表
	CString FindType(CString Type);                 //通过类型编码返回题目类型名称
	CString FindDifficulty(CString Difficulty);     //通过难度编码返回题目难度名称
	CString FindChapter(CString Chapter);           //通过章节编码返回题目章节名称
	BOOL SaveExist(CString strContent);             //判断是否保存成套导入的试卷     
	// Generated message map functions
	//{{AFX_MSG(CPaperDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonIn();                  //导入成套试卷
	afx_msg void OnButtonInanswer();            //继续导入答案
	afx_msg void OnButtonBrowse();              //浏览试卷及答案
	afx_msg void OnSelchangeComboSubject();      //科目选择发生变化
	afx_msg void OnClickTreePaper(NMHDR* pNMHDR, LRESULT* pResult);   //点击树形控件
	afx_msg void OnSelchangedTreePaper(NMHDR* pNMHDR, LRESULT* pResult);  //树形控件选择发生变化
	afx_msg void OnClickListPaper(NMHDR* pNMHDR, LRESULT* pResult);   //点击试卷列表
	afx_msg void OnCheckDate();          //选择是否按时间查询
	afx_msg void OnButtonQuery();       //条件查询
	afx_msg void OnButtonOnlyquery();   //精确查询
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAPERDLG_H__027A1889_5D95_442D_9432_E5BADC076BC7__INCLUDED_)
