#if !defined(AFX_BROWSEPAPERDLG_H__0582C635_DB85_429B_BAD1_742705F59515__INCLUDED_)
#define AFX_BROWSEPAPERDLG_H__0582C635_DB85_429B_BAD1_742705F59515__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BrowsePaperDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBrowsePaperDlg dialog

class CBrowsePaperDlg : public CDialog
{
// Construction
public:
	CBrowsePaperDlg(CWnd* pParent = NULL);   // standard constructor
	CString strID;

// Dialog Data
	//{{AFX_DATA(CBrowsePaperDlg)
	enum { IDD = IDD_DIALOG_BROWSE };
	CString	m_strPaper;
	CString	m_strTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowsePaperDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBrowsePaperDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOut();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSEPAPERDLG_H__0582C635_DB85_429B_BAD1_742705F59515__INCLUDED_)
