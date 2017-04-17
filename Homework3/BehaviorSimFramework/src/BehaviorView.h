// BehaviorView.h : interface of the CBehaviorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEHAVIORVIEW_H__C46B35E5_2F22_42DB_8265_BE5197269B6B__INCLUDED_)
#define AFX_BEHAVIORVIEW_H__C46B35E5_2F22_42DB_8265_BE5197269B6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BehaviorDoc.h"
#include "Transformation.h"
#include "Camera.h"
#include "Simulation.h"

class CBehaviorView : public CView
{
protected: // create from serialization only
	CBehaviorView();
	DECLARE_DYNCREATE(CBehaviorView)

// Attributes
public:
	CBehaviorDoc* GetDocument();
	HGLRC m_hRC;
	HDC m_hDC;
	Camera m_camera;
	int	m_lastMouseX, m_lastMouseY;
	int groundsize, groundstep;
	CSimulation sim;
	vec2 goal;
	bool debug;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBehaviorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnTimer();
	void ComputePosition(int x, int y, vec2& goal);
	virtual ~CBehaviorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBehaviorView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BehaviorView.cpp
inline CBehaviorDoc* CBehaviorView::GetDocument()
   { return (CBehaviorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEHAVIORVIEW_H__C46B35E5_2F22_42DB_8265_BE5197269B6B__INCLUDED_)
