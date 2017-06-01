#if !defined(AFX_MANAGEPAPERDLG_H__D6E31080_470D_4620_8567_BA6C308CA9D8__INCLUDED_)
#define AFX_MANAGEPAPERDLG_H__D6E31080_470D_4620_8567_BA6C308CA9D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManagePaperDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManagePaperDlg dialog

class CManagePaperDlg : public CDialog
{
// Construction
	CString strUsername;
	BOOL Purview;
	CString Now_ID;
public:
	CManagePaperDlg(CWnd* pParent = NULL);   // standard constructor
	CADODatabase *pDB;

// Dialog Data
	//{{AFX_DATA(CManagePaperDlg)
	enum { IDD = IDD_DIALOG_MANAGEPAPER };
	CDateTimeCtrl	m_DateTo;
	CDateTimeCtrl	m_DateFrom;
	CTreeCtrl	m_paperTree;
	CListCtrl	m_listQuestion;
	CListCtrl	m_listPaper;
	CComboBox	m_comboSubject;
	CComboBox	m_comboCreateperson;
	CString	m_strCreateperson;
	CString	m_strSubject;
	CString	m_strID;
	BOOL	m_checkDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManagePaperDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL InitComboSubject();
	BOOL InitComboCreate();
	BOOL InitPaperList();
	BOOL InitPaperTree();
	CString FindtbPaper(CString strChineseName);
	CString FindtbExist(CString strChineseName);
	BOOL InsertPaperItem(HTREEITEM hItem,CString strPaperName);
	BOOL InsertExistItem(HTREEITEM hItem,CString strExistName);
	void RefreshList(BOOL PaperOrExist,CADORecordset &recordset);
	void UpdateQuestionList(CADORecordset &recordset);
	CString FindType(CString Type);
	CString FindDifficulty(CString Difficulty);
	CString FindChapter(CString Chapter);
	void UpdateOthers(BOOL PaperOrExist,CString strID);

	// Generated message map functions
	//{{AFX_MSG(CManagePaperDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboSubject();
	afx_msg void OnCheckDate();
	afx_msg void OnButtonQuery();
	afx_msg void OnButtonQueryonly();
	afx_msg void OnClickTreePaper(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTreePaper(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonBrowse();
	afx_msg void OnButtonEditanswer();
	afx_msg void OnClickListPaper(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGEPAPERDLG_H__D6E31080_470D_4620_8567_BA6C308CA9D8__INCLUDED_)
