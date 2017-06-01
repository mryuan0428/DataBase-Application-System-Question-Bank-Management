#if !defined(AFX_PERSONMAKEUPDLG_H__B52CCF6F_0510_4771_A865_38CA8C26E52C__INCLUDED_)
#define AFX_PERSONMAKEUPDLG_H__B52CCF6F_0510_4771_A865_38CA8C26E52C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PersonMakeupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonMakeupDlg dialog
typedef struct paperItem      //试卷
{  
	CString FanganID;    
	CString ID;
	CString QuestionID;
	CString QuestionScore;
	CString QuestionAnswer;
	CString Content;
	CString Answer;
	CString Date;
	CString Username;
}personPaperNode;

class CPersonMakeupDlg : public CDialog
{
// Construction
	BOOL Purview;
	personPaperNode newPaper;
public:
	CPersonMakeupDlg(CWnd* pParent = NULL);   // standard constructor
	~CPersonMakeupDlg();
	CADODatabase * pDB;
    CADORecordset* pRs;
	int     m_nCount[10];            //存放数量
	int     m_nScore[10];            //存放分值
	CString m_str[10];               //存放题型字符串
	CComboBox   m_combo[10];         //选择题型
	CButton     m_buttonOther[10];   //选择题目
	CEdit       m_editCount[10];     //数量
	CEdit       m_editScore[10];     //分值
	int nButtonOther_index;
	//保存限制，下次再按下ButtonOther初始化用,组完卷后清零
	CString strSelQues[10];
	//判断能否组卷用，所选章节和难度限制总数与当前选择数目是否一致,组完卷后清零
//	int nSelQues[10];
	//取得本类题型的章节和难度给Sel用
	CString Chapter_all[30];
    CString Difficulty_all[5];

	CString GetTableName();

// Dialog Data
	//{{AFX_DATA(CPersonMakeupDlg)
	enum { IDD = IDD_DIALOG_PERSON };
	CDateTimeCtrl	m_DateTimeCreate;
	CEdit	m_editAllscore;
	CButton	m_buttonOutAnswer;
	CEdit	m_editAnswer;
	CEdit	m_editPaper;
	CComboBox	m_comboSubject;
	CComboBox	m_comboNumber;
	CButton	m_buttonStart;
	CButton	m_buttonSelect;
	CButton	m_buttonReset;
	CButton	m_buttonOut;
	int		m_nNumber;
	CString	m_strSubject;
	CString	m_strPaper;
	CString	m_strAnswer;
	int		m_nAllscore;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonMakeupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL InitCombo();
	BOOL InitComboSubject();
	BOOL FindAllItems();
	BOOL InsertNewItems();
	CString FindTable();
	CString FindID(CString fangan_ID);
	CString FindType(CString strType);
	CString IntToString(int index);
	int FindDifficulty(CString strDifficulty);
	BOOL CanStart();
	CString SetTitle();

	CString Table_name;    //当前选择的科目试题库
	CString strPaperName;  //当前选择的科目试卷库

	// Generated message map functions
	//{{AFX_MSG(CPersonMakeupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOut();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonSelect();
	afx_msg void OnButtonStart();
	afx_msg void OnSelchangeComboNumber();
	afx_msg void OnButtonOutanswer();
	//}}AFX_MSG
	void OnButtonOther(UINT nID);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONMAKEUPDLG_H__B52CCF6F_0510_4771_A865_38CA8C26E52C__INCLUDED_)
