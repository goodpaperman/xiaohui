#ifndef AFX_CLASSVIEW_H__84F28FA4_C33F_11D1_91F5_9F8A24CCC434__INCLUDED_
#define AFX_CLASSVIEW_H__84F28FA4_C33F_11D1_91F5_9F8A24CCC434__INCLUDED_

// ClassView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Ansicht CClassView 

class CClassView : public CTreeView
{
protected:
	CClassView();           // Dynamische Erstellung verwendet gesch�tzten Konstruktor
	DECLARE_DYNCREATE(CClassView)

// Attribute
public:

// Operationen
public:

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CClassView)
	protected:
	virtual void OnDraw(CDC* pDC);      // �berschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CClassView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CClassView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_CLASSVIEW_H__84F28FA4_C33F_11D1_91F5_9F8A24CCC434__INCLUDED_
