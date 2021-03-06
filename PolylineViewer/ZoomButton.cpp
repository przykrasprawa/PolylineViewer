// ZoomButton.cpp : implementation file
//

#include "stdafx.h"
#include "PolylineViewer.h"
#include "ZoomButton.h"


// ZoomButton

bool ZoomButton::m_select_area_trace = false;

IMPLEMENT_DYNAMIC(ZoomButton, CButton)

ZoomButton::ZoomButton()
{
}

ZoomButton::~ZoomButton()
{
}


BEGIN_MESSAGE_MAP(ZoomButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &ZoomButton::OnBnClicked)
//	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// ZoomButton message handlers




void ZoomButton::OnBnClicked()
{
	m_select_area_trace = !m_select_area_trace;
}


//void ZoomButton::OnMouseMove(UINT nFlags, CPoint point)
//{
//	
//
//	CButton::OnMouseMove(nFlags, point);
//}
