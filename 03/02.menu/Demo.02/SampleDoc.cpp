// A flat popup menu for controls
// Copyright (c) 1999 Andy Brown <andy@mirage.dabsol.co.uk>
// You may do whatever you like with this file, I just don't care.


#include "stdafx.h"
#include "SampleDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSampleDoc, CDocument)


/***************/
/* Message map */
/***************/

BEGIN_MESSAGE_MAP(CSampleDoc, CDocument)
	//{{AFX_MSG_MAP(CSampleDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************/
/* Constructor */
/***************/

CSampleDoc::CSampleDoc()
{
}


/**************/
/* Destructor */
/**************/

CSampleDoc::~CSampleDoc()
{
}



/**************************/
/* CSampleDoc diagnostics */
/**************************/

#ifdef _DEBUG
void CSampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
