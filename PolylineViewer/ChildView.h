
// ChildView.h : interface of the CChildView class
//


#pragma once
#include <vector>
#include <string>
#include <math.h>
#include "utilities.h"
#include "shapefil.h"


using namespace std;


// CChildView window


namespace constants {
	constexpr double zoom_in_multiplier = 0.5;
	constexpr double zoom_out_multiplier = 2;
}


class CChildView : public CWnd
{
	// Construction
public:
	CChildView();

	// Attributes
public:

	// Operations
public:

	// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Implementation
public:
	static const int m_scprecision = 1000;
	static double m_scurrent_zoom;
	virtual ~CChildView();


	// Generated message map functions
protected:
	BOOL LoadFile(LPCTSTR pszFile);
	void DrawShape(CPaintDC&, const Shape&) const;
	static const TCHAR m_scfilters[];
	CString m_path_name;
	vector<Shape> m_vec_shapes;
	double m_min_bound[4] = {};
	double m_max_bound[4] = { 1,1,1,1 };
	int m_entities;
	int m_shape_type;
	int m_width;
	int m_height;
	bool m_opened = false;
	bool m_zoom_other_trail = false;
	bool m_tracking = false;
	bool m_origin_init = true;
	POINT m_origin;
	POINT m_org_shift = { 0,0 };
	POINT m_point_from;
	POINT m_point_to;
	double m_prev_zoom = 1;
	afx_msg void OnFileOpen();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRevertZoom();
	afx_msg void OnUpdateRevertZoomUI(CCmdUI *pCmdUI);
	afx_msg void OnZoomOut();
	afx_msg void OnZoomIn();
	afx_msg void OnSelectZoom(UINT);
	afx_msg void OnUpdateSelectZoomUI(CCmdUI *pCmdUI);
	afx_msg void OnZoomOther();
	afx_msg void OnUpdateZoomOtherUI(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};







