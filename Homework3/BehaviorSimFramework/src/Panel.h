#if !defined(AFX_PANEL_H__63ED30D5_52B5_4587_A584_6D24B0123393__INCLUDED_)
#define AFX_PANEL_H__63ED30D5_52B5_4587_A584_6D24B0123393__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Panel.h : header file
//
#include "Simulation.h"

/////////////////////////////////////////////////////////////////////////////
// CPanel form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CPanel : public CFormView
{
protected:
	CPanel();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPanel)

// Form Data
public:
	//{{AFX_DATA(CPanel)
	enum { IDD = IDD_PANEL };
	UINT	m_Number;
	float	m_KAlign;
	float	m_KArrival;
	float	m_KAvoid;
	float	m_KCohesion;
	float	m_KDeparture;
	float	m_KNeighborhood;
	float	m_KNoise;
	float	m_KV0;
	float	m_KP1;
	float	m_KV1;
	float	m_KSeparate;
	float	m_KWander;
	float	m_TAvoid;
	float	m_Mass;
	float	m_MaxForce;
	float	m_MaxTorque;
	float	m_MaxVel;
	float	m_MaxW;
	float	m_Inertia;
	//}}AFX_DATA

// Attributes
public:
	CSimulation* sim;

// Operations
public:
	void GetSimulation(CSimulation* sim);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanel)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPanel();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPanel)
	afx_msg void OnButtonNum();
	afx_msg void OnRadioArrival();
	afx_msg void OnRadioDeparture();
	afx_msg void OnRadioFlee();
	afx_msg void OnRadioSeek();
	afx_msg void OnRadioWander();
	afx_msg void OnRadioOavoid();
	afx_msg void OnRadioSeparation();
	afx_msg void OnRadioAlignment();
	afx_msg void OnRadioCohesion();
	afx_msg void OnRadioFlocking();
	afx_msg void OnRadioLead();
	afx_msg void OnButtonUpdate();
	afx_msg void OnCheckDebug();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANEL_H__63ED30D5_52B5_4587_A584_6D24B0123393__INCLUDED_)
