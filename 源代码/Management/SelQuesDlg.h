#if !defined(AFX_SELQUESDLG_H__0373D95E_3391_4EF5_A349_1AD9EA6B55C7__INCLUDED_)
#define AFX_SELQUESDLG_H__0373D95E_3391_4EF5_A349_1AD9EA6B55C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelQuesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelQuesDlg dialog

class CSelQuesDlg : public CDialog
{
// Construction
public:
	CSelQuesDlg(CWnd* pParent = NULL);   // standard constructor
    ~CSelQuesDlg();
	CADODatabase * pDB;
    CADORecordset* pRs;
	CString strSelQues;
// Dialog Data
	//{{AFX_DATA(CSelQuesDlg)
	enum { IDD = IDD_DIALOG_SELQUES };
	CListBox	m_selectList;
	CButton	m_buttonAdd;
	CButton	m_buttonQueryOnly;
	CButton	m_buttonQuery;
	CButton	m_buttonOut;
	CButton	m_buttonPre;
	CButton	m_buttonNext;
	CButton	m_buttonLast;
	CButton	m_buttonFirst;
	CEdit	m_editID;
	CListCtrl	m_questionList;
	CEdit	m_editType;
	CEdit	m_editDifficulty;
	CEdit	m_editContent;
	CEdit	m_editChapter;
	CEdit	m_editAnswer;
	CComboBox	m_comboDifficulty;
	CComboBox	m_comboChapter;
	CString	m_selectChapter;
	CString	m_selectDifficulty;
	CString	m_answer;
	CString	m_chapter;
	CString	m_content;
	CString	m_queryid;
	CString	m_type;
	CString	m_strTitle;
	CString	m_difficulty;
	CString	m_id;
	CString	m_strNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelQuesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//打开的题库名
	CString Table_name;
	//类型
	CString strType;

	//更改详细信息
	void SetAllControls();
	//更新列表
	void RefreshList(CADORecordset& recordset);
	//初始化章节、难度combo
	BOOL InitCombo();
	//初始化题目列表
	BOOL InitQuestionList();
	//初始化已选题目列表
	BOOL InitSelectList();
	//查询时判断
	int State();
	//判断要添加的试题是否已经存在
	BOOL IsExist(CString str);

	// Generated message map functions
	//{{AFX_MSG(CSelQuesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonFirst();
	afx_msg void OnButtonLast();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonPre();
	afx_msg void OnButtonOut();
	afx_msg void OnButtonQuery();
	afx_msg void OnButtonQueryonly();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	afx_msg void OnClickListQuestion(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELQUESDLG_H__0373D95E_3391_4EF5_A349_1AD9EA6B55C7__INCLUDED_)
