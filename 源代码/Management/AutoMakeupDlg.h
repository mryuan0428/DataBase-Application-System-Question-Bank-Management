#if !defined(AFX_AUTOMAKEUPDLG_H__59648BBC_1686_4B23_8B5B_8FD96E59EA8C__INCLUDED_)
#define AFX_AUTOMAKEUPDLG_H__59648BBC_1686_4B23_8B5B_8FD96E59EA8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoMakeupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAutoMakeupDlg dialog
typedef struct Item      //试卷
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
}PaperNode;

class CAutoMakeupDlg : public CDialog
{
// Construction
	BOOL Purview;                    //权限是否为管理员
	PaperNode newPaper;              //新试卷结点
public:
	CAutoMakeupDlg(CWnd* pParent = NULL);   // standard constructor
	~CAutoMakeupDlg();
	CADODatabase * pDB;
    CADORecordset* pRs;
	int     m_nCount[10];            //存放各题数量
	int     m_nScore[10];            //存放各题分值
	CString m_str[10];               //存放各题题型名称
	CComboBox   m_combo[10];         //选择题型
	CButton     m_buttonOther[10];   //选择章节、难度
	CEdit       m_editCount[10];     //数量
	CEdit       m_editScore[10];     //分值
	int nButtonOther_index;
	//保存限制，下次再按下ButtonOther初始化用,组完卷后清除
	CString strSelChap[10];
	CString strSelDiff[10];
	//判断能否组卷用，所选章节和难度限制总数与当前选择数目是否一致,组完卷后清零
	int nSelChap[10];
	int nSelDiff[10];
	//取得本类题型的章节和难度给Sel用
	CString Chapter_all[30];
    CString Difficulty_all[5];
	//取得题库中每章每种难度的数目，在选择时判断数量是否合理用
	int EveryChapNum[30];
	int EveryDiffNum[5];
	//记录下OnButtonOther后每类题型每章、每种难度的数目，组卷时用,组完卷后清零
	int Chapter_num[10][30];
	int Difficulty_num[10][5];
	CString GetTableName();
	

// Dialog Data
	//{{AFX_DATA(CAutoMakeupDlg)
	enum { IDD = IDD_DIALOG_AUTO };
	CDateTimeCtrl	m_DateTimeCreate;      //试卷创建时间
	CEdit	m_editAllscore;                //填写总分控件
	CEdit	m_editAnswer;
	CButton	m_buttonOutAnswer;
	CButton	m_buttonOut;
	CButton	m_buttonStart;
	CButton	m_buttonSelect;
	CButton	m_buttonReset;
	CEdit	m_editPaper;
	CComboBox	m_comboSubject;
	CComboBox	m_comboNumber;
	int		m_nNumber;             //大题总数
	CString	m_strSubject;          //科目名称
	CString	m_strPaper;	           //存放试卷内容
	CString	m_strAnswer;           //存放试卷答案
	int		m_nAllscore;           //总分值
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoMakeupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL InitCombo();         //每次选中科目之后初始化所有选择题型Combo Box的Data值
	BOOL InitComboSubject();  //初始化选择科目Combo Box的Data值
	BOOL FindAllItems();      //找到所有组卷所需的试题进行组卷
	BOOL IsExist(int No[],int x);  //判断当前随机抽取的试题是否已选中过
	BOOL InsertNewItems();         //将新组的试卷添加到试卷库
	CString FindTable();           //查表判断当前选中的科目题库是否存在，返回值为试题表名
	CString FindID(CString fangan_ID);  //通过形参方案ID，返回当前组成试卷要插入试题库中的ID
	CString FindType(CString strType);  //通过形参题型名称，返回题型代码
	int FindDifficulty(CString strDifficulty);  //通过形参难度名称，返回索引
	CString IntToString(int index);     //将试题数量转换为2位的字符串
	CString SetTitle();              //设置卷头

	CString Table_name;              //记录当前选中科目试题表名
	CString strPaperName;            //记录当前选择的科目试卷表名


	// Generated message map functions
	//{{AFX_MSG(CAutoMakeupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonOut();
	afx_msg void OnSelchangeComboNumber();
	afx_msg void OnButtonSelect();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonOutanswer();
	//}}AFX_MSG
	void OnButtonOther(UINT nID); 
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOMAKEUPDLG_H__59648BBC_1686_4B23_8B5B_8FD96E59EA8C__INCLUDED_)
