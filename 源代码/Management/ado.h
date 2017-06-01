#ifndef _ADO_H_
#define _ADO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//引入ado库
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace  rename("EOF", "adoEOF"),rename("BOF","adoBOF")

CString IntToStr(int nVal);

CString LongToStr(long lVal);
/////////////////////////////////////////////////////////////////////////////
//  CADODatabase class
class CADODatabase
{
public:
	/////////////////////////////////////////////////////////////////////////////
	// 构造和析构函数
	CADODatabase()
	{
		//初始COM库
		::CoInitialize(NULL);
			
		m_pConnection = NULL;
		m_strConnection = _T("");
		m_pConnection.CreateInstance(__uuidof(Connection));
	}
	
	~CADODatabase()
	{
		Close();
		m_pConnection.Release();
		m_pConnection = NULL;
		::CoUninitialize();
	}
	/////////////////////////////////////////////////////////////////////////////
	//打开关闭连接、判断是否打开、执行不返回记录的SQL命令
	BOOL Open(LPCTSTR lpstrConnection = _T(""));
	void Close();
	BOOL IsOpen();	
	BOOL Execute(LPCTSTR lpstrExec);

	/////////////////////////////////////////////////////////////////////////////
	// 事务处理
	long BeginTransaction() ;
	BOOL CommitTransaction();
	BOOL RollbackTransaction();
	/////////////////////////////////////////////////////////////////////////////
	//设置和获得连接串、获得连接指针、错误信息
	_ConnectionPtr GetActiveConnection() {return m_pConnection;};
	void SetConnectionString(LPCTSTR lpstrConnection)
		{m_strConnection = lpstrConnection;};
	CString GetConnectionString()
		{return m_strConnection;};
	CString GetLastError() 
		{return m_strLastError;};
protected:
	void dump_com_error(_com_error &e);

protected:
	_ConnectionPtr m_pConnection;
	CString m_strConnection;
	CString m_strLastError;
};

class CADORecordset
{
public:
	//未知、SQL语句、表、存储过程
	enum cadoOpenEnum
	{
		openUnknown = 0,
		openQuery = 1,
		openTable = 2,
		openStoredProc = 3
	};
	enum cadoPositionEnum
	{
	
		positionUnknown = -1,
		positionBOF = -2,
		positionEOF = -3
	};
	//搜索方向，对应于ADO的
	enum cadoSearchEnum
	{	
		searchForward = 1,
		searchBackward = -1
	};
	/////////////////////////////////////////////////////////////////////////////
	//构造、析构函数
	CADORecordset()
	{
		m_pRecordset = NULL;
		m_strQuery = _T("");
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_nSearchDirection = CADORecordset::searchForward;
	}
	//利用CADODatabase类参数初始化
	CADORecordset(CADODatabase* pAdoDatabase);	
	~CADORecordset()
	{
		Close();
		m_pRecordset.Release();
		m_pRecordset = NULL;
		m_strQuery = _T("");
	}	
	/////////////////////////////////////////////////////////////////////////////
	//打开关闭记录集
	BOOL Open(_ConnectionPtr mpdb, LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openUnknown);
	BOOL Open(LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openUnknown);
	void Close();
	/////////////////////////////////////////////////////////////////////////////
	//获得记录个数，判断记录集是否打开
	DWORD GetRecordCount();
	BOOL IsOpen();
	/////////////////////////////////////////////////////////////////////////////
	//存取字段
	BOOL SetFieldValue(int nIndex, CString strValue);
	BOOL SetFieldValue(LPCTSTR lpFieldName, CString strValue);
	BOOL SetFieldValue(int nIndex, int nValue);
	BOOL SetFieldValue(LPCTSTR lpFieldName, int nValue);
	BOOL SetFieldValue(int nIndex, long lValue);
	BOOL SetFieldValue(LPCTSTR lpFieldName, long lValue);
	BOOL SetFieldValue(int nIndex, double dblValue);
	BOOL SetFieldValue(LPCTSTR lpFieldName, double dblValue);
	BOOL SetFieldValue(int nIndex, COleDateTime time);
	BOOL SetFieldValue(LPCTSTR lpFieldName, COleDateTime time);

	BOOL GetFieldValue(LPCTSTR lpFieldName, double& dbValue);
	BOOL GetFieldValue(int nIndex, double& dbValue);
	BOOL GetFieldValue(LPCTSTR lpFieldName, long& lValue);
	BOOL GetFieldValue(int nIndex, long& lValue);
	BOOL GetFieldValue(LPCTSTR lpFieldName, int& nValue);
	BOOL GetFieldValue(int nIndex, int& nValue);
	BOOL GetFieldValue(LPCTSTR lpFieldName, CString& strValue);
	BOOL GetFieldValue(int nIndex, CString& strValue);
	BOOL GetFieldValue(LPCTSTR lpFieldName, COleDateTime& time);
	BOOL GetFieldValue(int nIndex, COleDateTime& time);
	BOOL MoveTo(int nIndex);
/*	BOOL MoveTo(LPCTSTR lpFieldName, CString& strValue);
	BOOL MoveTo(int nIndex,CString& strValue);*/
	/////////////////////////////////////////////////////////////////////////////
	//更新记录集的记录
	BOOL Update();
	BOOL AddNew();
	BOOL Requery(long Options);
	BOOL Delete();
/*	
	BOOL IsFieldNull(LPCTSTR lpFieldName);
	BOOL IsFieldNull(int nIndex);
	BOOL IsFieldEmpty(LPCTSTR lpFieldName);
	BOOL IsFieldEmpty(int nIndex);	*/
	/////////////////////////////////////////////////////////////////////////////
	//判断位置
	BOOL IsEOF();
	BOOL IsBOF();
	/////////////////////////////////////////////////////////////////////////////
	//遍历记录
	BOOL MoveFirst();		
	BOOL MoveNext(); 	
	BOOL MovePrevious();		
	BOOL MoveLast(); 	
	/////////////////////////////////////////////////////////////////////////////
	//搜索记录，获得当前记录的位置序号
	BOOL Find(LPCTSTR lpFind, int nSearchDirection);
	BOOL Find(LPCTSTR lpFind);
	long GetAbsolutePosition();			
/*		void SetAbsolutePosition(int nPosition)
			{m_pRecordset->PutAbsolutePosition((enum PositionEnum)nPosition);};
		*/
	/////////////////////////////////////////////////////////////////////////////
	//其他
	CString GetQuery() 
	{return m_strQuery;};
	void SetQuery(LPCSTR strQuery) 
	{m_strQuery = strQuery;};	
	/////////////////////////////////////////////////////////////////////////////
	//书签操作
//	void GetBookmark();
//	BOOL SetBookmark();	
	/////////////////////////////////////////////////////////////////////////////
	//错误处理
	CString GetLastError() {return m_strLastError;};
protected:
	void dump_com_error(_com_error &e);

protected:
	_ConnectionPtr m_pConnection;	
	_RecordsetPtr m_pRecordset;
	int m_nSearchDirection;
	CString m_strFind;
//	_variant_t m_varBookFind;
//	_variant_t m_varBookmark;
	CString m_strLastError;	
	CString m_strQuery;
	
};

#endif

