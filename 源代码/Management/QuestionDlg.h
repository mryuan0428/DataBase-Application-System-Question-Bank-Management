#if !defined(AFX_QUESTIONDLG_H__79AC77B2_D68B_430E_886D_260F00E7CE97__INCLUDED_)
#define AFX_QUESTIONDLG_H__79AC77B2_D68B_430E_886D_260F00E7CE97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuestionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQuestionDlg dialog
typedef struct question
{
	char type[20];
	char difficulty[10];
	char chapter[10];
	char content[10000];
	char answer[10000];
	struct question * next;
}Node,*pNode;

class CQuestionDlg : public CDialog
{
// Construction
	bool Purview;          //判断权限是否是管理员
public:
	CQuestionDlg(CWnd* pParent = NULL);   // standard constructor
	~CQuestionDlg();
	CADODatabase * pDB;
    CADORecordset* pRs;
	//添加或修改记录
	bool m_AddorEdit;      //CAddandeditDlg中获取该值，判断是添加还是修改

// Dialog Data
	//{{AFX_DATA(CQuestionDlg)
	enum { IDD = IDD_DIALOG_QUESTION };
	CButton	m_buttonClear;
	CEdit	m_editQueryid;
	CButton	m_buttonQueryOnly;
	CButton	m_buttonQuery;
	CButton	m_buttonPre;
	CButton	m_buttonOut;
	CButton	m_buttonNext;
	CButton	m_buttonLast;
	CButton	m_buttonIn;
	CButton	m_buttonFirst;
	CButton	m_buttonEdit;
	CButton	m_buttonDelete;
	CButton	m_buttonConfirm;
	CButton	m_buttonClose;
	CButton	m_buttonAdd;
	CComboBox	m_comboType;
	CComboBox	m_comboDifficulty;
	CComboBox	m_comboChapter;
	CEdit	m_editAnswer;
	CEdit	m_editType;
	CEdit	m_editID;
	CEdit	m_editDifficulty;
	CEdit	m_editContent;
	CEdit	m_editChapter;
	CListCtrl	m_questionList;
	CComboBox	m_comboSubject;
	CString	m_chapter;             //记录章节(当前试题)
	CString	m_content;             //记录内容
	CString	m_difficulty;          //记录难度
	CString	m_id;                  //记录id
	CString	m_type;                //记录题型
	CString	m_answer;              //记录答案
	CString	m_subject;             //记录当前打开题库的科目名称
	CString	m_selectChapter;       //条件查询选择章节
	CString	m_selectDifficulty;    //条件查询选择难度
	CString	m_selectType;          //条件查询选择题型
	CString	m_queryid;             //精确查询id
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuestionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//打开的题库名
	CString Table_name;

	//查找是否存在选中科目的题库
	CString FindTable();
	//更改详细信息
	void SetAllControls();
	//更新试题列表
	void RefreshList(CADORecordset& recordset);
	//得到类型代码
	CString FindType(CString type);
	//得到难度代码
	CString FindDifficulty(CString difficulty);
	//得到章节代码
	CString FindChapter(CString chapter);
	//得到后4位(该类型、章节、难度中的第几题)
	CString FindNum(CString type,CString difficulty,CString chapter);
	//某道题被删除或修改后，修改原来在它之后的所有题目ID
	void UpdateOthers(CString old_id,CString old_type,CString old_difficulty,CString old_chapter);
	//初始化类型、难度和章节combo
	BOOL InitCombo();
	//初始化科目combo
	BOOL InitComboSubject();
	//向题库中添加新试题
	BOOL InsertNewItem(CString type,CString difficulty,CString chapter,CString content,CString answer); 
	//成批导入试题时判断文件是否可以打开
	CString CanOpen(CString in_filename);
	//成批导入试题
	BOOL ImportQuestiones(CString strChapter,CString strSel);
	//条件查询时判断
	int State();
	//停止导入试题
	bool IsStop(int index,int len);


	// Generated message map functions
	//{{AFX_MSG(CQuestionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListQuestion(NMHDR* pNMHDR, LRESULT* pResult);   //点击试题列表响应函数
	afx_msg void OnButtonConfirm();          //打开试题库
	afx_msg void OnButtonClose();            //关闭当前打开科目试题库
	afx_msg void OnButtonFirst();            //第一题
	afx_msg void OnButtonLast();             //最后一题
	afx_msg void OnButtonPre();              //上一题
	afx_msg void OnButtonNext();             //下一题
	afx_msg void OnButtonAdd();              //添加试题
	afx_msg void OnButtonEdit();             //修改试题
	afx_msg void OnButtonDelete();           //删除试题
	afx_msg void OnButtonClear();            //清空试题
    afx_msg void OnButtonQuery();            //条件查询试题
    afx_msg void OnButtonQueryonly();        //精确查询试题
    afx_msg void OnButtonIn();               //成批导入添加试题
	afx_msg void OnButtonOut();              //导出试题查看
	afx_msg void OnKeydownListQuestion(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUESTIONDLG_H__79AC77B2_D68B_430E_886D_260F00E7CE97__INCLUDED_)
