// Copyright (C) 1998-1999 KeyWorks Software. All rights reserved.

// This module contains the interface and class that can be used for reading
// files (streams) out of a .CHM or .ITS file. 


#ifndef __CITS_H__
#define __CITS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

DEFINE_GUID(CLSID_ITStorage, 0x5d02926a, 0x212e, 0x11d0, 0x9d, 0xf9, 0x0, 0xa0, 0xc9, 0x22, 0xe6, 0xec);
DEFINE_GUID(IID_ITStorage, 0x88cc31de, 0x27ab, 0x11d0, 0x9d, 0xf9, 0x0, 0xa0, 0xc9, 0x22, 0xe6, 0xec);

typedef struct _ITS_Control_Data
{
    UINT cdwControlData;     // Number of DWords to follow.
    UINT adwControlData[1];  // Actually this will be adwControlData[cdwControlData]

} ITS_Control_Data, *PITS_Control_Data;  

typedef enum ECompactionLev { 
    COMPACT_DATA = 0, 
    COMPACT_DATA_AND_PATH
};

DECLARE_INTERFACE_(IITStorage, IUnknown)
{
    STDMETHOD(StgCreateDocfile) (const WCHAR* pwcsName, DWORD grfMode, DWORD reserved, IStorage** ppstgOpen) PURE;

    STDMETHOD(StgCreateDocfileOnILockBytes) (ILockBytes * plkbyt, DWORD grfMode, 
                            DWORD reserved, IStorage ** ppstgOpen) PURE;

    STDMETHOD(StgIsStorageFile) (const WCHAR * pwcsName) PURE;

    STDMETHOD(StgIsStorageILockBytes) (ILockBytes * plkbyt) PURE;

    STDMETHOD(StgOpenStorage)(const WCHAR * pwcsName, IStorage * pstgPriority, 
                              DWORD grfMode, SNB snbExclude, DWORD reserved, 
                              IStorage ** ppstgOpen
                             ) PURE;

    STDMETHOD(StgOpenStorageOnILockBytes)
                  (ILockBytes * plkbyt, IStorage * pStgPriority, DWORD grfMode, 
                   SNB snbExclude, DWORD reserved, IStorage ** ppstgOpen
                  ) PURE;

    STDMETHOD(StgSetTimes)(WCHAR const * lpszName,  FILETIME const * pctime, 
                           FILETIME const * patime, FILETIME const * pmtime
                          ) PURE;

    STDMETHOD(SetControlData)(PITS_Control_Data pControlData) PURE;

    STDMETHOD(DefaultControlData)(PITS_Control_Data *ppControlData) PURE;
		
    STDMETHOD(Compact)(const WCHAR* pwcsName, ECompactionLev iLev) PURE;
};

class CItsFile
{
public:
    CItsFile();
    ~CItsFile();

    IStorage* GetStorage(void) { return m_pStorage; }   // this is the root storage

    HRESULT   OpenITS(PCSTR pszFile);

    HRESULT OpenStorage(PCSTR pszName, IStorage** ppStorage, DWORD dwAccess = STGM_READWRITE) {
                return m_pStorage->OpenStorage(FileNameToWCHAR(pszName), NULL, dwAccess, 0, 0, ppStorage); }
    HRESULT OpenStream(PCSTR pszFile, IStream** ppStream, IStorage* pStorage, DWORD dwAccess = STGM_READWRITE) {
                return pStorage->OpenStream(FileNameToWCHAR(pszFile), NULL, dwAccess, 0, ppStream); }

protected:
    WCHAR* FileNameToWCHAR(PCSTR psz);

    IITStorage*   m_pITStorage;
    IStorage*     m_pStorage;
    WCHAR*        m_pwTmpFile;
};

// Use this class to extract strings from the #STRINGS subfile

class CStringSubFile
{
public:
    CStringSubFile(CItsFile* pif);
    ~CStringSubFile();

    bool GetString(DWORD offset, char* pszDst, int cbDst);

protected:
    IStream*      m_pStream;     // pointer to #STRINGS stream
    CItsFile*     m_pif;
};

#endif  // __CITS_H__
