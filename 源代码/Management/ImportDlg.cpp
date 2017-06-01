// ImportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportDlg dialog


CImportDlg::CImportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportDlg)
	m_strFilename = _T("");
	//}}AFX_DATA_INIT
	strFilename = "";
}


void CImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportDlg)
	DDX_Text(pDX, IDC_EDIT_FILE, m_strFilename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportDlg, CDialog)
	//{{AFX_MSG_MAP(CImportDlg)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportDlg message handlers

void CImportDlg::OnButtonBrowse() 
{
	// TODO: Add your control notification handler code here	
	CString strFilter;
	strFilter.LoadString(IDS_FILE_FILTER);
	
	CFileDialog dlg(TRUE,NULL,NULL,0,strFilter,this); 
	
	if(dlg.DoModal()==IDOK) 
	{
		strFilename = dlg.GetPathName(); 
		m_strFilename = dlg.GetPathName();
		UpdateData(FALSE);
	}
	else
		return;
}

void CImportDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CDialog::OnOK();
}
