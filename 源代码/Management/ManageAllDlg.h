#if !defined(AFX_MANAGEALLDLG_H__A8FBC5EE_CD69_46B6_A205_9749D873B923__INCLUDED_)
#define AFX_MANAGEALLDLG_H__A8FBC5EE_CD69_46B6_A205_9749D873B923__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManageAllDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManageAllDlg dialog

class CManageAllDlg : public CDialog
{
// Construction
	CString strUsername;
	CString strPurview;
	CString strSubject;
public:
	CManageAllDlg(CWnd* pParent = NULL);   // standard constructor
	CADODatabase * pDB;

	CString GetUsername(){return strUsername;};
	CString GetPurview(){return strPurview;};
	CString GetSubject(){return strSubject;};
// Dialog Data
	//{{AFX_DATA(CManageAllDlg)
	enum { IDD = IDD_DIALOG_MANAGE };
	CButton	m_buttonType;
	CButton	m_buttonQuestion;
	CButton	m_buttonPool;
	CButton	m_buttonPerson;
	CButton	m_buttonPaper;
	CButton	m_buttonManagepaper;
	CButton	m_buttonAuto;
	CString	m_strTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManageAllDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CManageAllDlg)
	afx_msg void OnButtonPaper();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonQuestion();
	afx_msg void OnButtonAuto();
	afx_msg void OnButtonPerson();
	afx_msg void OnButtonPassword();
	afx_msg void OnButtonManagepaper();
	afx_msg void OnButtonPool();
	afx_msg void OnButtonManagetype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGEALLDLG_H__A8FBC5EE_CD69_46B6_A205_9749D873B923__INCLUDED_)
