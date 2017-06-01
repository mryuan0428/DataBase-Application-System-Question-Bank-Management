#if !defined(AFX_EDITANSWERDLG_H__8B0537A4_BB9E_4CF0_9185_3AF0A6E7F84E__INCLUDED_)
#define AFX_EDITANSWERDLG_H__8B0537A4_BB9E_4CF0_9185_3AF0A6E7F84E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditAnswerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditAnswerDlg dialog

class CEditAnswerDlg : public CDialog
{
// Construction
public:
	CEditAnswerDlg(CWnd* pParent = NULL);   // standard constructor
	CString strID;

// Dialog Data
	//{{AFX_DATA(CEditAnswerDlg)
	enum { IDD = IDD_DIALOG_EDITANSWER };
	CString	m_strAnswer;
	CString	m_strTitle;
	CString	m_strPaper;
	CString	m_strTitilePaper;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditAnswerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditAnswerDlg)
	afx_msg void OnButtonOut();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITANSWERDLG_H__8B0537A4_BB9E_4CF0_9185_3AF0A6E7F84E__INCLUDED_)
