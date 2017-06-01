// ManagementDlg.h : header file
//

#if !defined(AFX_MANAGEMENTDLG_H__24D091BD_F953_485F_812B_CA6D1116CFAF__INCLUDED_)
#define AFX_MANAGEMENTDLG_H__24D091BD_F953_485F_812B_CA6D1116CFAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CManagementDlg dialog

class CManagementDlg : public CDialog
{
// Construction
	CString strUsername;
	CString strPurview;
	CString strSubject;
public:
	CManagementDlg(CWnd* pParent = NULL);	// standard constructor
	~CManagementDlg();
	CADODatabase * pDB;
	CString GetUsername(){return strUsername;};
	CString GetPurview(){return strPurview;};
	CString GetSubject(){return strSubject;};

// Dialog Data
	//{{AFX_DATA(CManagementDlg)
	enum { IDD = IDD_DIALOG_MAIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManagementDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CManagementDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonLogin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGEMENTDLG_H__24D091BD_F953_485F_812B_CA6D1116CFAF__INCLUDED_)
