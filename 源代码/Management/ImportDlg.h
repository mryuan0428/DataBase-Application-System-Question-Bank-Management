#if !defined(AFX_IMPORTDLG_H__37B86D1A_384C_428D_AE55_7A392D691E4D__INCLUDED_)
#define AFX_IMPORTDLG_H__37B86D1A_384C_428D_AE55_7A392D691E4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportDlg dialog

class CImportDlg : public CDialog
{
// Construction
public:
	CImportDlg(CWnd* pParent = NULL);   // standard constructor
	CString GetFilename(){return strFilename;};

// Dialog Data
	//{{AFX_DATA(CImportDlg)
	enum { IDD = IDD_DIALOG_IMPORT };
	CString	m_strFilename;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString strFilename;

	// Generated message map functions
	//{{AFX_MSG(CImportDlg)
	afx_msg void OnButtonBrowse();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTDLG_H__37B86D1A_384C_428D_AE55_7A392D691E4D__INCLUDED_)
