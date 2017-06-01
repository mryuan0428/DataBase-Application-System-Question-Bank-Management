#if !defined(AFX_SAVEEXISTDLG_H__8C5FB6DA_2769_40AD_9F60_E43EB272F9E6__INCLUDED_)
#define AFX_SAVEEXISTDLG_H__8C5FB6DA_2769_40AD_9F60_E43EB272F9E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveExistDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveExistDlg dialog

class CSaveExistDlg : public CDialog
{
// Construction
public:
	CSaveExistDlg(CWnd* pParent = NULL);   // standard constructor
	~CSaveExistDlg();
	CADODatabase * pDB;
	CString strContent;
	CString strTablename;
	CString ID;
	CString ExistTable_name;
	CString strUsername;
	BOOL IsSave;

// Dialog Data
	//{{AFX_DATA(CSaveExistDlg)
	enum { IDD = IDD_DIALOG_SAVEEXIST };
	CString	m_strTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveExistDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString FindtbExist();

	// Generated message map functions
	//{{AFX_MSG(CSaveExistDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEEXISTDLG_H__8C5FB6DA_2769_40AD_9F60_E43EB272F9E6__INCLUDED_)
