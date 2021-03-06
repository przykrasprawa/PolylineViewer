// ZoomSpin.cpp : implementation file
//


#include "stdafx.h"
#include "PolylineViewer.h"
#include "ZoomSpin.h"
#include "ZoomDialog.h"
#include "ZoomEdit.h"


// ZoomSpin


IMPLEMENT_DYNAMIC(ZoomSpin, CSpinButtonCtrl)


ZoomSpin::ZoomSpin()
{

}

ZoomSpin::~ZoomSpin()
{
}


BEGIN_MESSAGE_MAP(ZoomSpin, CSpinButtonCtrl)
	ON_NOTIFY_REFLECT(UDN_DELTAPOS, &ZoomSpin::OnDeltapos)
END_MESSAGE_MAP()



// ZoomSpin message handlers




void ZoomSpin::OnDeltapos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if (pNMUpDown->iDelta > 0) {
		ZoomEdit3::m_zoom_percent -= constants::spin_delta;
	}
	else {
		ZoomEdit3::m_zoom_percent += constants::spin_delta;
	}
	::PostMessage(ZoomDialog::m_pedit3->m_hWnd, WM_USER_UPDATE, NULL, NULL);
	ZoomEdit3::m_spin_trace = true;
	*pResult = 0;
}
