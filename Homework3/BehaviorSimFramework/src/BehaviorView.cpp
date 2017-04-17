// BehaviorView.cpp : implementation of the CBehaviorView class
//

#include "stdafx.h"
#include "Behavior.h"

#include "BehaviorDoc.h"
#include "BehaviorView.h"
#include "MainFrm.h"
#include "AgentDisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBehaviorView

IMPLEMENT_DYNCREATE(CBehaviorView, CView)

BEGIN_MESSAGE_MAP(CBehaviorView, CView)
	//{{AFX_MSG_MAP(CBehaviorView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBehaviorView construction/destruction

CBehaviorView::CBehaviorView()
{
	// TODO: add construction code here
	sim.env.groundSize = 2000.0f;
	goal = vec2(0.0f,0.0f);
	debug = false;
}

CBehaviorView::~CBehaviorView()
{
	
}

BOOL CBehaviorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBehaviorView drawing

void CBehaviorView::OnDraw(CDC* pDC)
{
	CBehaviorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	m_camera.LookAt();
	glDisable(GL_LIGHTING);
	m_camera.DrawFloor();
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(goal[0], 0, goal[1]);
	glutSolidSphere(20.0, 12, 12);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	sim.Display();
	SwapBuffers(m_hDC);
}

/////////////////////////////////////////////////////////////////////////////
// CBehaviorView diagnostics

#ifdef _DEBUG
void CBehaviorView::AssertValid() const
{
	CView::AssertValid();
}

void CBehaviorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBehaviorDoc* CBehaviorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBehaviorDoc)));
	return (CBehaviorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBehaviorView message handlers

int CBehaviorView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	int nPixelFormat;					// Pixel format index
	m_hDC = ::GetDC(m_hWnd);			// Get the Device context
	
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// Size of this structure
			1,								// Version of this structure	
			PFD_DRAW_TO_WINDOW |			// Draw to Window (not to bitmap)
			PFD_SUPPORT_OPENGL |            // Support OpenGL clas in window
			PFD_DOUBLEBUFFER,			    // use double buffering
			PFD_TYPE_RGBA,					// RGBA Color mode
			32,								// Want 24bit color 
			0,0,0,0,0,0,					// Not used to select mode
			0,0,							// Not used to select mode
			0,0,0,0,0,						// Not used to select mode
			32,								// Size of depth buffer
			0,								// Not used to select mode
			0,								// Not used to select mode
			PFD_MAIN_PLANE,					// Draw in main plane
			0,								// Not used to select mode
			0,0,0 };						// Not used to select mode
		
		// Choose a pixel format that best matches that described in pfd
		nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
		
		// Set the pixel format for the device context
		SetPixelFormat(m_hDC, nPixelFormat, &pfd);
		
		// Create the rendering context
		m_hRC = wglCreateContext(m_hDC);
		
		// Make the rendering context current, perform initialization, then
		// deselect it
		wglMakeCurrent(m_hDC,m_hRC);
		
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glEnable(GL_LIGHTING);								// Enable Lighting
		glEnable(GL_LIGHT0);								// First Light Source
		glEnable(GL_NORMALIZE);								// Normalize Surface Normal Vector
		glEnable(GL_BLEND);									// Blend Color								
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

		//////////////////////////////////////////////////////////////////
		// Do any initialization of the rendering context here, such as
		// setting background colors, setting up lighting, or performing
		// preliminary calculations.
		float lightPosition[4] = {200.0f, 200.0f, 200.0f, 0.0};
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

		float lightColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
		float ambientColor[4] = {0.3f, 0.3f, 0.3f, 1.0f};
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
		
		// erase both buffers:
		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers(m_hDC);
		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers(m_hDC);
	return 0;
}

void CBehaviorView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (cy==0)										// Prevent A Divide By Zero By
	{
		cy=1;										// Making Height Equal One
	}

	glViewport(0,0,cx,cy);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix	
	// Calculate The Aspect Ratio Of The Window	
	m_camera.Perspective();

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

BOOL CBehaviorView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

void CBehaviorView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
/*
	const MSG* msg;
	msg = GetCurrentMessage();
	if (msg->message == WM_TIMER){
		OnTimer(1);
	}*/

	
	int dx, dy;
	if ( nFlags & MK_CONTROL )
	{
		if( nFlags & MK_RBUTTON )
		{
			// Zoom camera
			if ( m_lastMouseY != -1 )
			{
				m_camera.Zoom(((point.y - m_lastMouseY) + (point.x - m_lastMouseX)) / 2.0f);
				OnDraw( NULL );
			}
			m_lastMouseY = point.y;
			m_lastMouseX = point.x;
		}
		else if ( nFlags & MK_MBUTTON )
		{
			// Move camera
			if ( m_lastMouseX != -1 )
			{
				dx = (point.x - m_lastMouseX);
				dy = (point.y - m_lastMouseY);
				
				m_camera.MoveSWD(-dx, dy);
				
				OnDraw( NULL );
			}
			m_lastMouseX = point.x;
			m_lastMouseY = point.y;
		}
		else
			if (nFlags & MK_LBUTTON) {
				// Rotate camera.
				if ( m_lastMouseX != -1 )
				{
					dy = point.y - m_lastMouseY;
					dx = point.x - m_lastMouseX;
					m_camera.RotateCenter(-dx, -dy);
					OnDraw( NULL );
				}
				m_lastMouseX = point.x;
				m_lastMouseY = point.y;
			}
			else{
				m_lastMouseX = -1;
				m_lastMouseY = -1;
			}
	}else
		if (nFlags & MK_LBUTTON){
			ComputePosition(point.x, point.y, goal);
			sim.SetGoal(goal);
			OnDraw(NULL);
		}	
		else{
			m_lastMouseX = -1;
			m_lastMouseY = -1;
		}
	CView::OnMouseMove(nFlags, point);
}

void CBehaviorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar) {
	case 0x44: debug = !debug;
		break;
	case 0x20: sim.SimulationStep(0.033f);
			   OnDraw(NULL);
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CBehaviorView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();	
	// TODO: Add your specialized code here and/or call the base class
	CWnd::SetTimer(1, 33, 0);
	AgentDisplay::CreateDrawList();	
}

void CBehaviorView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1 && debug == false){
		sim.SimulationStep(0.033f);
		OnDraw(NULL);
	}
	CView::OnTimer(nIDEvent);
}

void CBehaviorView::ComputePosition(int x, int y, vec2 &goal)
{
	vec3 P, N;
	float rx, ry, h, w, t;
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);
	rx = float(x * 2) / float(viewport[2]) - 1.0;
	ry = float(y * 2) / float(viewport[3]) - 1.0;
	h = m_camera.m_nearP * tan(m_camera.m_fovy / 360.0 * M_PI);
	w = h * float(viewport[2]) / float(viewport[3]);
	rx = rx * w;
	ry = -1.0 * ry * h;
	P = m_camera.m_eye + m_camera.m_frontVec + m_camera.m_rightVec * rx + m_camera.m_upVec * ry;
	P = P - m_camera.m_eye;
	P = P.Normalize();
	N = vec3(0.0, 1.0, 0.0);
	t = -1.0 * (m_camera.m_eye * N);
	t = t / (P * N);
	P = P * t + m_camera.m_eye;
	goal[0] = P[0];
	goal[1] = P[2];
}

void CBehaviorView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ComputePosition(point.x, point.y, goal);
	sim.SetGoal(goal);
	CView::OnLButtonDblClk(nFlags, point);
	OnDraw(NULL);
}

void CBehaviorView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (nFlags == 1){
		ComputePosition(point.x, point.y, goal);
		sim.SetGoal(goal);
		OnDraw(NULL);
	}	
	CView::OnLButtonDown(nFlags, point);
	
}

void CBehaviorView::OnTimer()
{
	sim.SimulationStep(0.033f);
	OnDraw(NULL);
}

void CBehaviorView::OnDestroy() 
{
	CView::OnDestroy();
	KillTimer(1);
	// TODO: Add your message handler code here
	
}
