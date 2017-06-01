// ado.cpp : implementation file
//
#include "stdafx.h"
#include "ado.h"
#include <afxdisp.h>
/////////////////////////////////////////////////////////////////////////////
// CADODatabase class

BOOL CADODatabase::Open(LPCTSTR lpstrConnection)
{
	HRESULT hr = S_OK;

	if(IsOpen())
		Close();

	if(strcmp(lpstrConnection, _T("")) != 0)
		m_strConnection = lpstrConnection;

	ASSERT(!m_strConnection.IsEmpty());

	try
	{
		hr = m_pConnection->Open(_bstr_t(m_strConnection), "", "", NULL);
		return hr == S_OK;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
	}
	return FALSE;
}

BOOL CADODatabase::Execute(LPCTSTR lpstrExec)
{
	ASSERT(m_pConnection != NULL);
	ASSERT(strcmp(lpstrExec, _T("")) != 0);
	
	try
	{
		m_pConnection->Execute(_bstr_t(lpstrExec), NULL, adExecuteNoRecords);
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
	}
	return TRUE;	
}

void CADODatabase::dump_com_error(_com_error &e)
{
	CString ErrorStr;
	
	
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	ErrorStr.Format( "CADODataBase Error\n\tCode = %08lx\n\tCode meaning = %s\n\tSource = %s\n\tDescription = %s\n",
		e.Error(), e.ErrorMessage(), (LPCSTR)bstrSource, (LPCSTR)bstrDescription );
	m_strLastError = _T("Connection String = " + GetConnectionString() + '\n' + ErrorStr);
	#ifdef _DEBUG
		AfxMessageBox( ErrorStr, MB_OK | MB_ICONERROR );
	#endif	
}

BOOL CADODatabase::IsOpen()
{	try
	{
		return (m_pConnection != NULL && (m_pConnection->State & adStateOpen));
	}
	catch (_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	} 
	return FALSE;
}

void CADODatabase::Close()
{
	try
	{	if (IsOpen()) 
			m_pConnection->Close();		
	}
	catch (_com_error e)
	{
		dump_com_error(e);
	} 
}

long CADODatabase::BeginTransaction()
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return m_pConnection->BeginTrans();
	}
	catch (_com_error e)
	{
		dump_com_error(e);
		return -1;
	} 
	return -1;
}

BOOL CADODatabase::CommitTransaction()
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return SUCCEEDED(m_pConnection->CommitTrans());
	}
	catch (_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	} 
	return FALSE;
}

BOOL CADODatabase::RollbackTransaction()
{
	ASSERT(m_pConnection != NULL);
	try
	{
		return SUCCEEDED(m_pConnection->RollbackTrans());
	}
	catch (_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	} 
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////
// CADORecordset class

/////////////////////////////////////////////////////////////////////////////
//构造函数
CADORecordset::CADORecordset(CADODatabase* pAdoDatabase)
{
	m_pRecordset = NULL;
	m_strQuery = _T("");
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_nSearchDirection = CADORecordset::searchForward;

	m_pConnection = pAdoDatabase->GetActiveConnection();
}
/////////////////////////////////////////////////////////////////////////////
//打开记录集
BOOL CADORecordset::Open(_ConnectionPtr mpdb, LPCTSTR lpstrExec, int nOption)
{	
	if (IsOpen()) Close();
	
	if(strcmp(lpstrExec, _T("")) != 0)
		m_strQuery = lpstrExec;

	ASSERT(!m_strQuery.IsEmpty());
	
	m_strQuery.TrimLeft();
	BOOL bIsSelect = m_strQuery.Mid(0, strlen("Select ")).CompareNoCase("select ") == 0;

	try
	{
		m_pRecordset->CursorLocation = adUseClient;
		if(bIsSelect || nOption == openQuery)
			m_pRecordset->Open((LPCSTR)m_strQuery, _variant_t((IDispatch*)mpdb, TRUE), 
							adOpenStatic, adLockOptimistic, adCmdText);
		else if(nOption == openTable)
			m_pRecordset->Open((LPCSTR)m_strQuery, _variant_t((IDispatch*)mpdb, TRUE), 
							adOpenDynamic, adLockOptimistic, adCmdTable);
		else if(nOption == openStoredProc)
		{
			m_pRecordset->Open((LPCSTR)m_strQuery, _variant_t((IDispatch*)mpdb, TRUE), 
				adOpenStatic, adLockOptimistic, adCmdStoredProc);
		}
		else
		{
			TRACE( "Unknown parameter. %d", nOption);
			return FALSE;
		}
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}
	return m_pRecordset != NULL;
}

BOOL CADORecordset::Open(LPCTSTR lpstrExec, int nOption)
{
	ASSERT(m_pConnection != NULL);
	return Open(m_pConnection, lpstrExec, nOption);
}


BOOL CADORecordset::GetFieldValue(LPCTSTR lpFieldName, double& dbValue)
{	
	double val = (double)NULL;
	_variant_t vtFld;
	try
	{	
		vtFld = m_pRecordset->Fields->GetItem(lpFieldName)->Value;
		if(vtFld.vt != VT_NULL)
			val = vtFld.dblVal;
		dbValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		dbValue=0;
		return FALSE;
	}
}


BOOL CADORecordset::GetFieldValue(int nIndex, double& dbValue)
{	
	double val = (double)NULL;
	_variant_t vtFld;
	_variant_t vtIndex;

	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	try
	{
		vtFld = m_pRecordset->Fields->GetItem(vtIndex)->Value;
		if(vtFld.vt != VT_NULL)
			val = vtFld.dblVal;
		dbValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		dbValue=0;
		return FALSE;
	}
	
}


BOOL CADORecordset::GetFieldValue(LPCTSTR lpFieldName, long& lValue)
{
	long val = (long)NULL;
	_variant_t vtFld;
	try
	{	
		vtFld = m_pRecordset->Fields->GetItem(lpFieldName)->Value;
		if(vtFld.vt != VT_NULL)
			val = vtFld.lVal;
		lValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		lValue=0;
		return FALSE;
	}
}

BOOL CADORecordset::GetFieldValue(int nIndex, long& lValue)
{
	long val = (long)NULL;
	_variant_t vtFld;
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	try
	{
		vtFld = m_pRecordset->Fields->GetItem(vtIndex)->Value;
		if(vtFld.vt != VT_NULL)
			val = vtFld.lVal;
		lValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		lValue=0;
		return FALSE;
	}	
}


BOOL CADORecordset::GetFieldValue(LPCTSTR lpFieldName, int& nValue)
{
	int val = NULL;
	_variant_t vtFld;
	try
	{
		vtFld = m_pRecordset->Fields->GetItem(lpFieldName)->Value;
		switch(vtFld.vt)
		{
		case VT_I2:
			val = vtFld.iVal;
			break;
		case VT_BOOL:
			val = vtFld.boolVal;
		case VT_NULL:
		case VT_EMPTY:
			break;
		default:
			nValue = 0;
			return FALSE;
		}	
		nValue = val;
		return TRUE;		
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		nValue=0;
		return FALSE;
	}
}

BOOL CADORecordset::GetFieldValue(int nIndex, int& nValue)
{
	int val = (int)NULL;
	_variant_t vtFld;
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	try
	{
		vtFld = m_pRecordset->Fields->GetItem(vtIndex)->Value;
		switch(vtFld.vt)
		{
		case VT_I2:
			val = vtFld.iVal;
			break;
		case VT_NULL:
		case VT_EMPTY:
			val = 0;
			break;
		default:
			return FALSE;
		}	
		nValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		nValue=0;
		return FALSE;
	}
	
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpFieldName, CString& strValue)
{
	CString str = _T("");
	_variant_t vtFld;
	try
	{
		vtFld = m_pRecordset->Fields->GetItem(lpFieldName)->Value;
		switch(vtFld.vt) 
		{
		case VT_BSTR:
			str = vtFld.bstrVal;
			break;
		case VT_I4:
			str = IntToStr(vtFld.iVal);
			break;
		case VT_DATE:
			{
				COleDateTime dt(vtFld);
				
				str = dt.Format("%Y-%m-%d %H:%M:%S");
			}
			break;
		case VT_EMPTY:
		case VT_NULL:
			break;
		default:
			strValue.Empty();
			return FALSE;
		}
		strValue = str;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		strValue= _T("");
		return FALSE;
	}
}

BOOL CADORecordset::GetFieldValue(int nIndex, CString& strValue)
{
	CString str = _T("");
	_variant_t vtFld;
	_variant_t vtIndex;

	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	try
	{
		vtFld = m_pRecordset->Fields->GetItem(vtIndex)->Value;
		switch(vtFld.vt) 
		{
		case VT_BSTR:
			str = vtFld.bstrVal;
			break;
		case VT_DATE:
			{
				COleDateTime dt(vtFld);
				
				str = dt.Format("%Y-%m-%d %H:%M:%S");
			}
			break;
		case VT_EMPTY:
		case VT_NULL:
			break;
		default:
			strValue.Empty();
			return FALSE;
		}
		strValue = str;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		strValue= _T("");
		return FALSE;
	}	
}

BOOL CADORecordset::GetFieldValue(LPCTSTR lpFieldName, COleDateTime& time)
{
	_variant_t vtFld;
	try
	{
		vtFld = m_pRecordset->Fields->GetItem(lpFieldName)->Value;
		switch(vtFld.vt) 
		{
		case VT_DATE:
			{
				COleDateTime dt(vtFld);
				time = dt;
			}
			break;
		case VT_EMPTY:
		case VT_NULL:
			break;
		default:
			return FALSE;
		}
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}	
}

BOOL CADORecordset::GetFieldValue(int nIndex, COleDateTime& time)
{
	_variant_t vtFld;
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	try
	{
		vtFld = m_pRecordset->Fields->GetItem(vtIndex)->Value;
		switch(vtFld.vt) 
		{
		case VT_DATE:
			{
				COleDateTime dt(vtFld);
				time = dt;
			}
			break;
		case VT_EMPTY:
		case VT_NULL:
			break;
		default:
			return FALSE;
		}
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}	
}

/*
BOOL CADORecordset::IsFieldNull(LPCTSTR lpFieldName)
{
	_variant_t vtFld;
	
	vtFld = m_pRecordset->Fields->GetItem(lpFieldName)->Value;
	return vtFld.vt == VT_NULL;
}

BOOL CADORecordset::IsFieldNull(int nIndex)
{
	_variant_t vtFld;
	_variant_t vtIndex;

	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	
	vtFld = m_pRecordset->Fields->GetItem(vtIndex)->Value;
	return vtFld.vt == VT_NULL;
}

BOOL CADORecordset::IsFieldEmpty(LPCTSTR lpFieldName)
{
	_variant_t vtFld;
	
	vtFld = m_pRecordset->Fields->GetItem(lpFieldName)->Value;
	return vtFld.vt == VT_EMPTY || vtFld.vt == VT_NULL;
}

BOOL CADORecordset::IsFieldEmpty(int nIndex)
{
	_variant_t vtFld;
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
		
	vtFld = m_pRecordset->Fields->GetItem(vtIndex)->Value;
	return vtFld.vt == VT_EMPTY || vtFld.vt == VT_NULL;
}*/

/////////////////////////////////////////////////////////////////////////////
//获得记录数目
DWORD CADORecordset::GetRecordCount()
{
	DWORD nRows = 0;
	try{	
		nRows = m_pRecordset->GetRecordCount();
		//如果提供者不支持计算记录个数,则通过遍历计算
		if(nRows == -1)
		{
			nRows = 0;
			if(m_pRecordset->adoEOF != VARIANT_TRUE)
				m_pRecordset->MoveFirst();
			while(m_pRecordset->adoEOF != VARIANT_TRUE)
				{
					nRows++;
					m_pRecordset->MoveNext();
				}
			if(nRows > 0)
				m_pRecordset->MoveFirst();
		}
	}
	catch (_com_error& e)
		{
			dump_com_error(e);
			return -1;
		}	
	return nRows;
}

BOOL CADORecordset::IsOpen()
{
	try
	{
		if(m_pRecordset)
			return m_pRecordset->GetState() != adStateClosed;
	}
	catch (_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	} 
	return FALSE;
}

void CADORecordset::Close()
{	try
	{
		if (m_pRecordset != NULL && m_pRecordset->State != adStateClosed)
				m_pRecordset->Close();
	}
	catch (_com_error& e)
	{dump_com_error(e);}	
}

void CADORecordset::dump_com_error(_com_error &e)
{
	CString ErrorStr;
	
	
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	ErrorStr.Format( "CADORecordset Error\n\tCode = %08lx\n\tCode meaning = %s\n\tSource = %s\n\tDescription = %s\n",
		e.Error(), e.ErrorMessage(), (LPCSTR)bstrSource, (LPCSTR)bstrDescription );
	m_strLastError = _T("Query = " + GetQuery() + '\n' + ErrorStr);

	#ifdef _DEBUG
		AfxMessageBox( ErrorStr, MB_OK | MB_ICONERROR );
	#endif	
}


long CADORecordset::GetAbsolutePosition()
{
	ASSERT(m_pRecordset != NULL);	
	try
	{
		return m_pRecordset->GetAbsolutePosition();
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return -1;
	}
}

CString IntToStr(int nVal)
{
	CString strRet;
	char buff[10];
	
	itoa(nVal, buff, 10);
	strRet = buff;
	return strRet;
}

CString LongToStr(long lVal)
{
	CString strRet;
	char buff[20];
	
	ltoa(lVal, buff, 10);
	strRet = buff;
	return strRet;
}
/////////////////////////////////////////////////////////////////////////////
//添加记录、更新记录
BOOL CADORecordset::AddNew()
{
	try
	{
		if(m_pRecordset->AddNew() != S_OK)
			return FALSE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}
	return TRUE;
}

BOOL CADORecordset::Update()
{
	try
	{
		if(m_pRecordset->Update() != S_OK)
			return FALSE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}
	return TRUE;
}


BOOL CADORecordset::SetFieldValue(int nIndex, CString strValue)
{
	_variant_t vtFld;
	vtFld.vt = VT_BSTR;
	vtFld.bstrVal = _bstr_t(strValue);

	_variant_t vtIndex;	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	try
	{
		m_pRecordset->Fields->GetItem(vtIndex)->Value = _bstr_t(vtFld);//_bstr_t(strValue);
		return TRUE;
	}	
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}	
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpFieldName, CString strValue)
{
	_variant_t vtFld;
	vtFld.vt = VT_BSTR;
	vtFld.bstrVal = _bstr_t(strValue);
	try
	{
		m_pRecordset->Fields->GetItem(lpFieldName)->Value = _bstr_t(vtFld);
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}		
}

BOOL CADORecordset::SetFieldValue(int nIndex, int nValue)
{
	_variant_t vtFld;
	vtFld.vt = VT_I2;
	vtFld.iVal = nValue;
	
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	try
	{
		m_pRecordset->Fields->GetItem(vtIndex)->Value = vtFld;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}		
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpFieldName, int nValue)
{
	_variant_t vtFld;
	vtFld.vt = VT_I2;
	vtFld.iVal = nValue;
	try
	{
		m_pRecordset->Fields->GetItem(lpFieldName)->Value = vtFld;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}		
}

BOOL CADORecordset::SetFieldValue(int nIndex, long lValue)
{
	_variant_t vtFld;
	vtFld.vt = VT_I4;
	vtFld.lVal = lValue;
	
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	try
	{
		m_pRecordset->Fields->GetItem(vtIndex)->Value = vtFld;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}		
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpFieldName, long lValue)
{
	_variant_t vtFld;
	vtFld.vt = VT_I4;
	vtFld.lVal = lValue;
	try
	{
		m_pRecordset->Fields->GetItem(lpFieldName)->Value = vtFld;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}		
}

BOOL CADORecordset::SetFieldValue(int nIndex, double dblValue)
{
	_variant_t vtFld;
	vtFld.vt = VT_R8;
	vtFld.dblVal = dblValue;

	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	try
	{
		m_pRecordset->Fields->GetItem(vtIndex)->Value = vtFld;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}		
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpFieldName, double dblValue)
{
	_variant_t vtFld;
	vtFld.vt = VT_R8;
	vtFld.dblVal = dblValue;
	try
	{
		m_pRecordset->Fields->GetItem(lpFieldName)->Value = vtFld;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}	
}

BOOL CADORecordset::SetFieldValue(int nIndex, COleDateTime time)
{
	_variant_t vtFld;
	vtFld.vt = VT_DATE;
	vtFld.date = time;
	
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	try
	{
		m_pRecordset->Fields->GetItem(vtIndex)->Value = vtFld;
		return TRUE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}	
}

BOOL CADORecordset::SetFieldValue(LPCTSTR lpFieldName, COleDateTime time)
{
	_variant_t vtFld;
	vtFld.vt = VT_DATE;
	vtFld.date = time;
	try
	{
		m_pRecordset->Fields->GetItem(lpFieldName)->Value = vtFld;
		return TRUE;	
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return FALSE;
	}
}
/*
BOOL CADORecordset::SetBookmark()
{
	if(m_varBookmark.vt != VT_EMPTY)
	{
		m_pRecordset->Bookmark = m_varBookmark;
		return TRUE;
	}
	return FALSE;
}

void CADORecordset::GetBookmark()
{
	ASSERT(m_pRecordset != NULL);
	try
	{
		if (IsOpen())		
			m_varBookmark = m_pRecordset->GetBookmark();			
	}
	catch (_com_error e)
	{dump_com_error(e);}
}*/

BOOL CADORecordset::Delete()
{
	if(m_pRecordset->Delete(adAffectCurrent) != S_OK)
		return FALSE;

	if(m_pRecordset->Update() != S_OK)
		return FALSE;

	return TRUE;
}

BOOL CADORecordset::Find(LPCTSTR lpFind, int nSearchDirection)
{
	m_strFind = lpFind;
	m_nSearchDirection = nSearchDirection;
	ASSERT(!m_strFind.IsEmpty());
	try
	{
		if(m_nSearchDirection == searchForward)
		{
			m_pRecordset->Find(_bstr_t(m_strFind), 0, adSearchForward, "");
			if(!IsEOF())
			{
				//m_varBookFind = m_pRecordset->Bookmark;
				return TRUE;
			}
		}
		else if(m_nSearchDirection == searchBackward)
		{	
			m_pRecordset->Find(_bstr_t(m_strFind), 0, adSearchBackward, "");
			if(!IsBOF())
			{
				//m_varBookFind = m_pRecordset->Bookmark;
				return TRUE;
			}				
		}
		else
		{
			TRACE("Unknown parameter. %d", nSearchDirection);
			m_nSearchDirection = searchForward;
		}
		return FALSE;
	}
	catch(_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	} 	
}

BOOL CADORecordset::Find(LPCTSTR lpFind)
{
	m_strFind = lpFind;
	ASSERT(!m_strFind.IsEmpty());
	try
	{
		
		m_pRecordset->Find(_bstr_t(m_strFind), 0, adSearchForward, "");
		if(!IsEOF())
		{
			//m_varBookFind = m_pRecordset->Bookmark;
			return TRUE;
		}
		
		
		m_pRecordset->Find(_bstr_t(m_strFind), 0, adSearchBackward, "");
		if(!IsBOF())
		{
			//m_varBookFind = m_pRecordset->Bookmark;
			return TRUE;
		}				
			
		return FALSE;
	}
	catch(_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	} 	
}


BOOL CADORecordset::IsBOF()
{
	ASSERT(m_pRecordset != NULL);
	try
	{
		return m_pRecordset->adoBOF;
	}
	catch(_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	} 
	return FALSE;
}

BOOL CADORecordset::IsEOF()
{
	ASSERT(m_pRecordset != NULL);
	try
	{
		return ((m_pRecordset->adoEOF)==VARIANT_TRUE);
	}
	catch (_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	}
}

BOOL CADORecordset::MoveFirst()
{
	ASSERT(m_pRecordset != NULL);
	try
	{
		if (m_pRecordset != NULL) 
		{
			return SUCCEEDED(m_pRecordset->MoveFirst());
		}
	}
	catch (_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	} 
	return	FALSE;
}

BOOL CADORecordset::MoveNext()
{
	ASSERT(m_pRecordset != NULL);
	try
	{
		if (m_pRecordset != NULL) 
		{
			return SUCCEEDED(m_pRecordset->MoveNext());
		}
	}
	catch (_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	}
	return FALSE;
}
BOOL CADORecordset::MovePrevious()
{
	ASSERT(m_pRecordset != NULL);
	try
	{
		if (m_pRecordset != NULL) 
		{
			return SUCCEEDED(m_pRecordset->MovePrevious());
		}
	}
	catch (_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	}
	return FALSE;	
}
BOOL CADORecordset::MoveLast()
{
	ASSERT(m_pRecordset != NULL);
	try
	{
		if (m_pRecordset != NULL) 
		{
			return SUCCEEDED(m_pRecordset->MoveLast());
		}
	}
	catch (_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	} 
	return	FALSE;
}

BOOL CADORecordset::Requery(long Options)
{
	ASSERT(m_pRecordset != NULL);
	try
	{
		if (m_pRecordset != NULL) 
		{
			return (m_pRecordset->Requery(Options) == S_OK);
		}
	}
	catch (_com_error e)
	{
		dump_com_error(e);
		return FALSE;
	} 
	return	FALSE; 
}

/*BOOL CADORecordset::MoveTo(LPCTSTR lpFieldName, CString& strValue)
{
	CString str = _T("");
	_variant_t vtFld;
	m_pRecordset->MoveFirst();
	try
	{
		while(! m_pRecordset->adoEOF)
		{

			vtFld = m_pRecordset->Fields->GetItem(lpFieldName)->Value;
			switch(vtFld.vt) 
			{
			case VT_BSTR:
				str = vtFld.bstrVal;
				break;
			case VT_I4:
				str = IntToStr(vtFld.iVal);
				break;
			case VT_DATE:
				{
					COleDateTime dt(vtFld);
					
					str = dt.Format("%Y-%m-%d %H:%M:%S");
				}
				break;
			case VT_EMPTY:
			case VT_NULL:
				break;
			default:
				//	strValue.Empty();
				return FALSE;
			}
			if(!strcmp(str,strValue))
				return TRUE;			
			m_pRecordset->MoveNext();
		}
		return FALSE;		
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		strValue= _T("");
		return FALSE;
	}
}

BOOL CADORecordset::MoveTo(int nIndex,CString &strValue)
{
	CString str = _T("");
	_variant_t vtFld;
	_variant_t vtIndex;

	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	try
	{
		while(! m_pRecordset->adoEOF)
		{
			vtFld = m_pRecordset->Fields->GetItem(vtIndex)->Value;
			switch(vtFld.vt) 
			{
			case VT_BSTR:
				str = vtFld.bstrVal;
				break;
			case VT_DATE:
				{
					COleDateTime dt(vtFld);
					
					str = dt.Format("%Y-%m-%d %H:%M:%S");
				}
				break;
			case VT_EMPTY:
			case VT_NULL:
				break;
			default:
				return FALSE;
			}
			if(!strcmp(str,strValue))
				return TRUE;			
			m_pRecordset->MoveNext();
		}
		return FALSE;
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		strValue= _T("");
		return FALSE;
	}	
}*/

BOOL CADORecordset::MoveTo(int nIndex)
{
	MoveFirst();
	for(int i = 0 ; i < nIndex ; i++)
		MoveNext();
	if(IsEOF())
		return FALSE;
	return TRUE;
}