// MenuHash.cpp: implementation of the CMenuHash class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGtoolbar.h"
#include "MenuHash.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMenuHash g_menuHash;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMenuHash::CMenuHash()
{
}
//****************************************************************************************
CMenuHash::~CMenuHash()
{
}
//****************************************************************************************
BOOL CMenuHash::SaveMenuBar (HMENU hMenu, CBCGToolBar* pBar)
{
	ASSERT_VALID (pBar);

	if (pBar->GetCount () == 0)
	{
		return FALSE;
	}

	//---------------------
	// Get the temp path...
	//---------------------
	CString strTempPath;
	GetTempPath (MAX_PATH, strTempPath.GetBuffer (MAX_PATH));
	strTempPath.ReleaseBuffer();

	//-------------------------------------------
	// Create a temporary file for the output....
	//-------------------------------------------
	CString strTempName;
	GetTempFileName (strTempPath, _T("BCG"), 0, strTempName.GetBuffer (MAX_PATH));
	strTempName.ReleaseBuffer ();

	HANDLE hFile = ::CreateFile (strTempName, GENERIC_READ | GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		TRACE(_T("Can't create temporary file!\n"));
		return FALSE;
	}

	try
	{
		//---------------------------------
		// Write a menubar context to file:
		//---------------------------------
		CFile file ((HFILE) hFile);
		{
			CArchive ar (&file, CArchive::store);

			pBar->Serialize (ar);
			ar.Flush ();
		}
	}
	catch (CArchiveException* pEx)
	{
		TRACE(_T("Archive exception in CMenuHash::SaveMenuBar ()!\n"));
		pEx->Delete ();

		return FALSE;
	}
	catch (CMemoryException* pEx)
	{
		TRACE(_T("Memory exception in CMenuHash::SaveMenuBar ()!\n"));
		pEx->Delete ();

		return FALSE;
	}
	catch (CFileException* pEx)
	{
		TRACE(_T("Memory exception in CMenuHash::SaveMenuBar ()!\n"));
		pEx->Delete ();

		return FALSE;
	}

	m_StoredMenues.SetAt (hMenu, hFile);
	return TRUE;
}
//****************************************************************************************
BOOL CMenuHash::LoadMenuBar (HMENU hMenu, CBCGToolBar* pBar) const
{
	ASSERT_VALID (pBar);
	ASSERT (hMenu != NULL);

	//----------------------------------------------
	// Find a file handler associated with the menu:
	//----------------------------------------------
	HANDLE hFile;
	if (!m_StoredMenues.Lookup (hMenu, hFile))
	{
		return FALSE;
	}

	//-----------------
	// Rewind the file:
	//-----------------
	if (::SetFilePointer (hFile, 0, NULL, FILE_BEGIN) == 0xFFFFFFFF)
	{
		TRACE(_T("CMenuHash::LoadMenuBar (). Invalid file handle\n"));
		return FALSE;
	}

	try
	{
		CFile file ((HFILE) hFile);
		CArchive ar (&file, CArchive::load);

		pBar->Serialize (ar);
	}
	catch (CArchiveException* pEx)
	{
		TRACE(_T("Archive exception in CMenuHash::LoadMenuBar ()!\n"));
		pEx->Delete ();

		return FALSE;
	}
	catch (CMemoryException* pEx)
	{
		TRACE(_T("Memory exception in CMenuHash::LoadMenuBar ()!\n"));
		pEx->Delete ();

		return FALSE;
	}
	catch (CFileException* pEx)
	{
		TRACE(_T("File exception in CMenuHash::LoadMenuBar ()!\n"));
		pEx->Delete ();

		return FALSE;
	}

	return TRUE;
}
