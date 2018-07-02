
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "PolylineViewer.h"
#include "ChildView.h"
#include "ZoomDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView
const TCHAR CChildView::m_scfilters[] =
_T("Shape Files (*.shp)¦*.shp¦All Files (*.*)¦*.*¦¦");

double CChildView::m_scurrent_zoom = 1;

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_PAINT()
	ON_COMMAND(ID_REVERTZOOM, &CChildView::OnRevertZoom)
	ON_UPDATE_COMMAND_UI(ID_REVERTZOOM, &CChildView::OnUpdateRevertZoomUI)
	ON_COMMAND(ID_ZOOMOUT, &CChildView::OnZoomOut)
	ON_COMMAND(ID_ZOOMIN, &CChildView::OnZoomIn)
	ON_COMMAND_RANGE(ID_ZOOM_1, ID_ZOOM_OTHER, &CChildView::OnSelectZoom)
	ON_UPDATE_COMMAND_UI_RANGE(ID_ZOOM_1, ID_ZOOM_OTHER,OnUpdateSelectZoomUI)
	ON_COMMAND(ID_ZOOM_OTHER, &CChildView::OnZoomOther)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_OTHER, &CChildView::OnUpdateZoomOtherUI)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnFileOpen()
{
	CFileDialog dlg(TRUE, _T("shp"), _T("*.shp"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, m_scfilters);
	if (dlg.DoModal() == IDOK) {
		if (LoadFile(dlg.GetPathName())) {
			Invalidate();
			return;
		}
		else {
			MessageBox(_T("Failed to open file"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		}
	}
}

void CChildView::OnPaint() 
{

	if (m_opened) {
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	dc.SetMapMode(MM_ISOTROPIC);
	dc.SetWindowExt(m_scurrent_zoom*ceil((m_max_bound[0] - m_min_bound[0]) * m_scprecision), -m_scurrent_zoom*ceil((m_max_bound[1] - m_min_bound[1]) * m_scprecision));
	dc.SetViewportExt(rect.Width(), rect.Height());
	POINT point_x = { (m_max_bound[0] - m_min_bound[0]) *m_scprecision, (m_max_bound[0] - m_min_bound[0]) * m_scprecision };
	POINT point_y = { (m_max_bound[1] - m_min_bound[1]) *m_scprecision, (m_max_bound[1] - m_min_bound[1]) * m_scprecision };
	LPtoDP(dc, &point_x, 1);
	LPtoDP(dc, &point_y, 1);
	dc.SetViewportOrg(rect.Width() / 2 - (point_x.x) / 2 + m_org_shift.x, rect.Height()/2+ (point_y.x) / 2 + m_org_shift.y);
		for (const auto& x : m_vec_shapes) {
			DrawShape(dc,x);
		}
	}
}


BOOL CChildView::LoadFile(LPCTSTR pfile) {
	ShapeOpen Open(CStringA(pfile), "rb");
	if (Open.GetState() == FALSE) return FALSE;
	SHPGetInfo(Open.GetSHPHandle(), &m_entities,
	&m_shape_type,m_min_bound, m_max_bound);
	for (int i = 0; i < m_entities; ++i) {
		m_vec_shapes.push_back(Shape(Open.GetSHPHandle(),i));
	}
	m_opened = TRUE;
	return TRUE;
}


void CChildView::DrawShape(CPaintDC& dc, const Shape& shape) const {
	if (shape.Get()->nParts > 1) {
		for (auto i = 0; i < shape.Get()->nParts - 1; ++i) {
			dc.MoveTo((shape.Get()->padfX[shape.Get()->panPartStart[i]] - m_min_bound[0])*m_scprecision, (shape.Get()->padfY[shape.Get()->panPartStart[i]] - m_min_bound[1])*m_scprecision);
			for (auto j = shape.Get()->panPartStart[i] + 1; (j < shape.Get()->panPartStart[i + 1]); ++j) {
				dc.LineTo((shape.Get()->padfX[j] - m_min_bound[0])*m_scprecision, (shape.Get()->padfY[j] - m_min_bound[1])*m_scprecision);
			}
		}
		dc.MoveTo((shape.Get()->padfX[shape.Get()->panPartStart[shape.Get()->nParts - 1]] - m_min_bound[0])*m_scprecision, (shape.Get()->padfY[shape.Get()->panPartStart[shape.Get()->nParts - 1]] - m_min_bound[1])*m_scprecision);
		for (auto i = shape.Get()->panPartStart[shape.Get()->nParts - 1] + 1; i < shape.Get()->nVertices; ++i) {
			dc.LineTo((shape.Get()->padfX[i] - m_min_bound[0])*m_scprecision, (shape.Get()->padfY[i] - m_min_bound[1])*m_scprecision);
		}
	}
	else {
		dc.MoveTo((shape.Get()->padfX[0] - m_min_bound[0])*m_scprecision, (shape.Get()->padfY[0] - m_min_bound[1])*m_scprecision);
		for (auto i = 1; i < shape.Get()->nVertices; ++i) {
			dc.LineTo((shape.Get()->padfX[i] - m_min_bound[0])*m_scprecision, (shape.Get()->padfY[i] - m_min_bound[1])*m_scprecision);
		}
	}
}


void CChildView::OnRevertZoom()
{
	swap(m_scurrent_zoom, m_prev_zoom);
	Invalidate();
}


void CChildView::OnUpdateRevertZoomUI(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}


void CChildView::OnZoomOut()
{
	m_prev_zoom = m_scurrent_zoom;
	m_scurrent_zoom *= constants::zoom_out_multiplier;
	Invalidate();
}


void CChildView::OnZoomIn()
{
	m_prev_zoom = m_scurrent_zoom;
	m_scurrent_zoom *= constants::zoom_in_multiplier;
	Invalidate();
}


void CChildView::OnSelectZoom(UINT ID)
{
	if (ID != ID_ZOOM_OTHER) {
		m_prev_zoom = m_scurrent_zoom;
		m_scurrent_zoom = constants::zoom_min*pow(2, ID - ID_ZOOM_1);
	}
	else {
		m_zoom_other_trail = true;
		ZoomDialog dlg;
		int nReturn = dlg.DoModal();
		if (nReturn == IDOK) {
			m_scurrent_zoom = 1/(ZoomEdit3::m_zoom_percent/100);
		}
	}
	Invalidate();
}


void CChildView::OnUpdateSelectZoomUI(CCmdUI *pCmdUI)
{		
		pCmdUI->SetRadio((constants::zoom_min*pow(2, pCmdUI->m_nID - ID_ZOOM_1) ==
			m_scurrent_zoom) && !m_zoom_other_trail);
		if (pCmdUI->m_nID == ID_ZOOM_OTHER) {
			pCmdUI->SetRadio(m_zoom_other_trail);
			m_zoom_other_trail = false;
		}
}

void CChildView::OnZoomOther()
{
	

}


void CChildView::OnUpdateZoomOtherUI(CCmdUI *pCmdUI)
{
	
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
		m_point_from = point;
		m_point_to = point;
		m_tracking = true;
	SetCapture();
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_tracking) {
		if (ZoomButton::m_select_area_trace) {
			CClientDC dc(this);
			InvertRectangle(&dc, m_point_from, m_point_to);
			InvertRectangle(&dc, m_point_from, point);
		}
		else {
			m_org_shift.x = m_org_shift.x + (point.x - m_point_from.x);
			m_org_shift.y = m_org_shift.y + (point.y - m_point_from.y);
			m_point_from = point;
			Invalidate();
		}
		m_point_to = point;
	}
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_tracking) {
		m_tracking = false;
		if (GetCapture() == this)
			::ReleaseCapture();
		if (ZoomButton::m_select_area_trace) {
			CClientDC dc(this);
			InvertRectangle(&dc, m_point_from, m_point_to);
		}
	}
}





//BOOL CChildView::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	return 1;
//}
