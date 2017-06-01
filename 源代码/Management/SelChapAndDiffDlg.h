#if !defined(AFX_SELCHAPANDDIFFDLG_H__DE74AC6F_AC7E_45C8_B519_D7C5996A4557__INCLUDED_)
#define AFX_SELCHAPANDDIFFDLG_H__DE74AC6F_AC7E_45C8_B519_D7C5996A4557__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelChapAndDiffDlg.h : header file
//

#define UWM_TV_CHECKBOX    WM_APP   // WPARAM == DlgCtrlID of tree, LPARAM is HTREEITEM
/////////////////////////////////////////////////////////////////////////////
// CSelChapAndDiffDlg dialog

class CSelChapAndDiffDlg : public CDialog
{
// Construction
public:
	CSelChapAndDiffDlg(CWnd* pParent = NULL);   // standard constructor
	CADODatabase * pDB;
	//读取上次保存的信息
	CString strSelChapter;
	CString strSelDifficulty;
	//限制章节、难度的总数(判断是否与该题型总数一致用)
	int nChapnum;
	int nDiffnum;
	//各章节是否需要题，各难度各需要多少题
	int Chapter_num[30];
	int Difficulty_num[5];
	bool ChapOrDiff;
	CSpinButtonCtrl	m_ctrlDiffSpin[5];
	CEdit	m_editDiff[5];
	int 	m_nDiff[5];
	CString	m_strExistDiff[5];
	int     nExistDiff[5];
	afx_msg LRESULT OnTvCheckbox(WPARAM wp, LPARAM lp);

// Dialog Data
	//{{AFX_DATA(CSelChapAndDiffDlg)
	enum { IDD = IDD_DIALOG_SELCHAPANDDIFF };
	CTreeCtrl	m_chapterTree;
	CString	m_strTitle;
	CString	m_strDiffAll;
	CString	m_strTypeExist;
	CString	m_strTypeSel;
	CString	m_strSelAll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelChapAndDiffDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_ImgList;
	//题库
	CString Table_name;
	//当前题型
	CString strType;
	BOOL InitChapterTree();
	BOOL InitCombo();
	void ExistDiffChange();

	// Generated message map functions
	//{{AFX_MSG(CSelChapAndDiffDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickTreeChapter(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownTreeChapter(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
//	void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult,UINT nID);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELCHAPANDDIFFDLG_H__DE74AC6F_AC7E_45C8_B519_D7C5996A4557__INCLUDED_)
