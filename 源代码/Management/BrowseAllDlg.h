#if !defined(AFX_BROWSEALLDLG_H__FBEB9BCE_1D8F_42DE_9FA1_DD9C9B50F037__INCLUDED_)
#define AFX_BROWSEALLDLG_H__FBEB9BCE_1D8F_42DE_9FA1_DD9C9B50F037__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BrowseAllDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBrowseAllDlg dialog

class CBrowseAllDlg : public CDialog
{
// Construction
public:
	CBrowseAllDlg(CWnd* pParent = NULL);   // standard constructor
	CString strID;

// Dialog Data
	//{{AFX_DATA(CBrowseAllDlg)
	enum { IDD = IDD_DIALOG_BROWSWALL };
	CString	m_strAnswer;
	CString	m_strPaper;
	CString	m_strTitleAnswer;
	CString	m_strTitlePaper;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowseAllDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBrowseAllDlg)
	afx_msg void OnButtonOutanswer();
	afx_msg void OnButtonOutpaper();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSEALLDLG_H__FBEB9BCE_1D8F_42DE_9FA1_DD9C9B50F037__INCLUDED_)
