#pragma once


// ZoomButton

class ZoomButton : public CButton
{
	DECLARE_DYNAMIC(ZoomButton)

public:
	static bool m_select_area_trace;
	ZoomButton();
	virtual ~ZoomButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked();
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


