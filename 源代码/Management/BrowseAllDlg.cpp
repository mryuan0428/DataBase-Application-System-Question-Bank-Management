// BrowseAllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "BrowseAllDlg.h"
#include "PaperDlg.h"
#include "msword.h"
#include <AtlBase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowseAllDlg dialog


CBrowseAllDlg::CBrowseAllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBrowseAllDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBrowseAllDlg)
	m_strAnswer = _T("");
	m_strPaper = _T("");
	m_strTitleAnswer = _T("");
	m_strTitlePaper = _T("");
	//}}AFX_DATA_INIT
}


void CBrowseAllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBrowseAllDlg)
	DDX_Text(pDX, IDC_EDIT_ANSWER, m_strAnswer);
	DDX_Text(pDX, IDC_EDIT_PAPER, m_strPaper);
	DDX_Text(pDX, IDC_STATIC_ANSWER, m_strTitleAnswer);
	DDX_Text(pDX, IDC_STATIC_PAPER, m_strTitlePaper);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBrowseAllDlg, CDialog)
	//{{AFX_MSG_MAP(CBrowseAllDlg)
	ON_BN_CLICKED(IDC_BUTTON_OUTANSWER, OnButtonOutanswer)
	ON_BN_CLICKED(IDC_BUTTON_OUTPAPER, OnButtonOutpaper)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowseAllDlg message handlers

void CBrowseAllDlg::OnButtonOutanswer() 
{
	// TODO: Add your control notification handler code here
	if(m_strAnswer.IsEmpty())
		return;

	CString strFilter;
	strFilter.LoadString(IDS_FILE_FILTER);
	CString Filename = "试卷";
	Filename += strID;
	Filename += "答案";
	CFileDialog fileDlg(FALSE, NULL, Filename, NULL, strFilter, NULL);
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
	
	sel.TypeText(_T(m_strAnswer));
	
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

void CBrowseAllDlg::OnButtonOutpaper() 
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
