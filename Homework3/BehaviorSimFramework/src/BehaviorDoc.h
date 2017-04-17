// BehaviorDoc.h : interface of the CBehaviorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEHAVIORDOC_H__BEE4E052_0A55_4D0F_A58B_CC0748AF2154__INCLUDED_)
#define AFX_BEHAVIORDOC_H__BEE4E052_0A55_4D0F_A58B_CC0748AF2154__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBehaviorDoc : public CDocument
{
protected: // create from serialization only
	CBehaviorDoc();
	DECLARE_DYNCREATE(CBehaviorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBehaviorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBehaviorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBehaviorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEHAVIORDOC_H__BEE4E052_0A55_4D0F_A58B_CC0748AF2154__INCLUDED_)
