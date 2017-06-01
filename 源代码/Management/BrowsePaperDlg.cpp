// BrowsePaperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "BrowsePaperDlg.h"
#include "ManagePaperDlg.h"
#include "PaperDlg.h"
#include "msword.h"
#include <AtlBase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowsePaperDlg dialog


CBrowsePaperDlg::CBrowsePaperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBrowsePaperDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBrowsePaperDlg)
	m_strPaper = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	strID = "";
}


void CBrowsePaperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBrowsePaperDlg)
	DDX_Text(pDX, IDC_EDIT_PAPER, m_strPaper);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBrowsePaperDlg, CDialog)
	//{{AFX_MSG_MAP(CBrowsePaperDlg)
	ON_BN_CLICKED(IDC_BUTTON_OUT, OnButtonOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowsePaperDlg message handlers

BOOL CBrowsePaperDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBrowsePaperDlg::OnButtonOut() 
{
	// TODO: Add your control notification handler code here
	if(m_strPaper.IsEmpty())
		return;
	CString strFilter;
	strFilter.LoadString(IDS_FILE_FILTER);
	CString Filename = "试卷";
	Filename += strID;
	CFileDialog fileDlg(FALSE, NULL, Filename, OFN_HIDEREADONLY, strFilter, NULL);
	if(fileDlg.DoModal() != IDOK)
		return;
	CString strFilename = fileDlg.GetPathName();
	strFilename += ".doc";
	
	_Application app;
	app.CreateDispatch(_T("Word.Application"));
	app.SetVisible(TRUE);
	
	Documents docs=app.GetDocuments();
	CComVariant Template(_T(""));
	CComVariant NewTemplate(false),DocumentType(0),Visible;
	docs.Add(&Template,&NewTemplate,&DocumentType,&Visible);
	
	Selection sel=app.GetSelection();
	
	sel.TypeText(_T(m_strPaper));
	
	CString strSave = "是否保存文档1到";
	strSave += strFilename;
	if(MessageBox(strSave,"确认保存",MB_ICONQUESTION|MB_OKCANCEL) == IDOK)
	{
		_Document doc=app.GetActiveDocument();		//得到ActiveDocument
		CComVariant FileName(_T(strFilename));	//文件名
		CComVariant FileFormat(0);
		CComVariant LockComments(false),Password(_T(""));
		CComVariant AddToRecentFiles(true),WritePassword(_T(""));
		CComVariant ReadOnlyRecommended(false),EmbedTrueTypeFonts(false);
		CComVariant SaveNativePictureFormat(false),SaveFormsData(false);
		CComVariant SaveAsAOCELetter(false);
		
		doc.SaveAs(&FileName,&FileFormat,&LockComments,&Password,
			&AddToRecentFiles,&WritePassword,&ReadOnlyRecommended,
			&EmbedTrueTypeFonts,&SaveNativePictureFormat,&SaveFormsData,
			&SaveAsAOCELetter);
		doc.ReleaseDispatch();
	}
	sel.ReleaseDispatch();	
	docs.ReleaseDispatch();
	
	CComVariant SaveChanges(false),OriginalFormat,RouteDocument;
	app.Quit(&SaveChanges,&OriginalFormat,&RouteDocument);
	app.ReleaseDispatch();
}
