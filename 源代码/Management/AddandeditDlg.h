#if !defined(AFX_ADDANDEDITDLG_H__F13F97C4_8154_4E73_945B_6EABCFB4BE35__INCLUDED_)
#define AFX_ADDANDEDITDLG_H__F13F97C4_8154_4E73_945B_6EABCFB4BE35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddandeditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddandeditDlg dialog

class CAddandeditDlg : public CDialog
{
// Construction
public:
	CAddandeditDlg(CWnd* pParent = NULL);   // standard constructor
	~CAddandeditDlg();
	CADODatabase * pDB;
	CADORecordset* pTypeRs;
	bool IsContentEdit;
	bool IsAttributesEdit;

// Dialog Data
	//{{AFX_DATA(CAddandeditDlg)
	enum { IDD = IDD_DIALOG_ADDANDEDIT };
	CComboBox	m_comboDifficulty;
	CComboBox	m_comboChapter;
	CComboBox	m_comboType;
	CString	m_chapter;
	CString	m_difficulty;
	CString	m_type;
	CString	m_answer;
	CString	m_content;
	CString	m_title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddandeditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddandeditDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDANDEDITDLG_H__F13F97C4_8154_4E73_945B_6EABCFB4BE35__INCLUDED_)
