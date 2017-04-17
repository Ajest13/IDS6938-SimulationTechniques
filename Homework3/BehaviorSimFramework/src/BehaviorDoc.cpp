// BehaviorDoc.cpp : implementation of the CBehaviorDoc class
//

#include "stdafx.h"
#include "Behavior.h"

#include "BehaviorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBehaviorDoc

IMPLEMENT_DYNCREATE(CBehaviorDoc, CDocument)

BEGIN_MESSAGE_MAP(CBehaviorDoc, CDocument)
	//{{AFX_MSG_MAP(CBehaviorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBehaviorDoc construction/destruction

CBehaviorDoc::CBehaviorDoc()
{
	// TODO: add one-time construction code here

}

CBehaviorDoc::~CBehaviorDoc()
{
}

BOOL CBehaviorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBehaviorDoc serialization

void CBehaviorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBehaviorDoc diagnostics

#ifdef _DEBUG
void CBehaviorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBehaviorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBehaviorDoc commands
