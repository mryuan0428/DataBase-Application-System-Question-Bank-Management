#if !defined(AFX_MANAGEPOOLDLG_H__D5047930_1587_43A3_86F1_4CF48C8D4FFC__INCLUDED_)
#define AFX_MANAGEPOOLDLG_H__D5047930_1587_43A3_86F1_4CF48C8D4FFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManagePoolDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManagePoolDlg dialog

class CManagePoolDlg : public CDialog
{
// Construction
public:
	CManagePoolDlg(CWnd* pParent = NULL);   // standard constructor
	CADODatabase *pDB;

// Dialog Data
	//{{AFX_DATA(CManagePoolDlg)
	enum { IDD = IDD_DIALOG_MANAGEPOOL };
	CListCtrl	m_listPool;
	CString	m_strSubject;      //要添加的科目名称
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManagePoolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL InitPoolList();           //初始化题库列表
	BOOL CreateNewTable(CString tablename,CString papername,CString existname);  //新建相应的表
	BOOL TableIsEmpty(CString tablename);         //判断表是否为空
//	void UpdateOthers(CString old_id);            //删除科目后更新后面科目的id

	// Generated message map functions
	//{{AFX_MSG(CManagePoolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();            //添加科目
	afx_msg void OnButtonDelete();         //删除科目
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGEPOOLDLG_H__D5047930_1587_43A3_86F1_4CF48C8D4FFC__INCLUDED_)
