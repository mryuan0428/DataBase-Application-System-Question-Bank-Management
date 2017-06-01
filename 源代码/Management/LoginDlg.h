#if !defined(AFX_LOGINDLG_H__45F85044_EBB4_40BC_8AFB_D8AA6822D99D__INCLUDED_)
#define AFX_LOGINDLG_H__45F85044_EBB4_40BC_8AFB_D8AA6822D99D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

class CLoginDlg : public CDialog
{
// Construction
	CString strUsername;
	CString strPurview;
	CString strSubject;
	int wrong_num;
public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	~CLoginDlg();
	CADODatabase * pDB;
    CADORecordset* pRs;
	CString GetUsername(){return strUsername;};
	CString GetPurview(){return strPurview;};
	CString GetSubject(){return strSubject;};

// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_DIALOG_LOGIN };
	CString	m_password;
	CString	m_username;
	CString	m_strPurview;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__45F85044_EBB4_40BC_8AFB_D8AA6822D99D__INCLUDED_)
