// DVMDoc.h : interface of the CDVMDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CDVMDoc : public CDocument
{
protected: // create from serialization only
	CDVMDoc();
	DECLARE_DYNCREATE(CDVMDoc)

// Attributes
public:
	CString GetTestText(void);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDVMDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDVMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDVMDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strTestText;
};

/////////////////////////////////////////////////////////////////////////////
