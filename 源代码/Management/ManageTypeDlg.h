#if !defined(AFX_MANAGETYPEDLG_H__E1418578_78F9_4AE9_B18A_A2FA99B25DA7__INCLUDED_)
#define AFX_MANAGETYPEDLG_H__E1418578_78F9_4AE9_B18A_A2FA99B25DA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManageTypeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManageTypeDlg dialog

class CManageTypeDlg : public CDialog
{
// Construction
public:
	CManageTypeDlg(CWnd* pParent = NULL);   // standard constructor
	CADODatabase *pDB;

// Dialog Data
	//{{AFX_DATA(CManageTypeDlg)
	enum { IDD = IDD_DIALOG_MANAGETYPE };
	CListCtrl	m_listType;
	CString	m_strType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManageTypeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL InitTypeList();
	BOOL TypeIsExist(int i,CString strName);
//	void UpdateOthers(CString old_id);

	// Generated message map functions
	//{{AFX_MSG(CManageTypeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGETYPEDLG_H__E1418578_78F9_4AE9_B18A_A2FA99B25DA7__INCLUDED_)
