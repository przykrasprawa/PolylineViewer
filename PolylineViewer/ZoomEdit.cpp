// ZoomEdit.cpp : implementation file
//


#include "stdafx.h"
#include <vector>
#include <string>
#include "PolylineViewer.h"
#include "ChildView.h"
#include "ZoomDialog.h"
#include "ZoomEdit.h"
#include "utilities.h"


using namespace std;


int ZoomEdit1::m_zoom_num = 0;


// ZoomEdit1


IMPLEMENT_DYNAMIC(ZoomEdit1, CEdit)


ZoomEdit1::ZoomEdit1()
{
}


ZoomEdit1::~ZoomEdit1()
{
}


BEGIN_MESSAGE_MAP(ZoomEdit1, CEdit)
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_UPDATE, &ZoomEdit1::OnEnUpdate)
	ON_MESSAGE(WM_USER_UPDATE, OnUserUpdate)
END_MESSAGE_MAP()


// ZoomEdit1 message handlers


void ZoomEdit1::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	CString buffer1;
	GetWindowText(buffer1);
	CStringA buffer2(buffer1);
	m_zoom_num= atof(buffer2);
	if (m_zoom_num < constants::num_min) {
		m_zoom_num = constants::num_min;
	}
	else if (m_zoom_num > constants::num_max) {
		m_zoom_num = constants::num_max;
	}
	buffer1.Format(_T("%i"), m_zoom_num);
	SetWindowText(buffer1);
}


int ZoomEdit1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


void ZoomEdit1::OnEnUpdate()
{	
	CString buffer;
	GetWindowText(buffer);
	CStringA buffer1(buffer);
	m_zoom_num = atof(buffer1);
	if (ZoomDialog::m_pedit3&&!ZoomEdit3::m_update_trace) {
		::PostMessage(ZoomDialog::m_pedit3->m_hWnd,WM_USER_UPDATE, NULL,NULL);
	}
	ZoomEdit3::m_update_trace = false;
}


LRESULT ZoomEdit1::OnUserUpdate(WPARAM wParam, LPARAM lParam)
{
	ZoomEdit3::m_update_trace = true;
	vector<int> v;
	double temp = ZoomEdit3::m_zoom_percent / 100;
	v = GetRationalRepresentation(temp, constants::init_bound,
	constants::zoom_max, constants::interval);
	m_zoom_num = v[0];
	CString buffer;
	buffer.Format(_T("%i"),m_zoom_num);
	SetWindowText(buffer);
	return 0;
}


// ZoomEdit2


int ZoomEdit2::m_zoom_den = 0;


IMPLEMENT_DYNAMIC(ZoomEdit2, CEdit)


ZoomEdit2::ZoomEdit2()
{
}

ZoomEdit2::~ZoomEdit2()
{
}


BEGIN_MESSAGE_MAP(ZoomEdit2, CEdit)
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_CHANGE, &ZoomEdit2::OnEnChange)
	ON_MESSAGE(WM_USER_UPDATE, OnUserUpdate)
END_MESSAGE_MAP()


// ZoomEdit2 message handlers


void ZoomEdit2::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	CString buffer1;
	GetWindowText(buffer1);
	CStringA buffer2(buffer1);
	m_zoom_den = atof(buffer2);
		if (m_zoom_den < constants::den_min) {
			m_zoom_den = constants::den_min;
		}
		else if (m_zoom_den > constants::den_max) {
			m_zoom_den = constants::den_max;
		}
	buffer1.Format(_T("%i"), m_zoom_den);
	SetWindowText(buffer1);
}


int ZoomEdit2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


void ZoomEdit2::OnEnChange()
{
	CString buffer;
	GetWindowText(buffer);
	CStringA buffer1(buffer);
	m_zoom_den = atof(buffer1);
	if (ZoomDialog::m_pedit3&&!ZoomEdit3::m_update_trace) {
		::PostMessage(ZoomDialog::m_pedit3->m_hWnd, WM_USER_UPDATE, NULL, NULL);
	}
	ZoomEdit3::m_update_trace = false;
}

LRESULT ZoomEdit2::OnUserUpdate(WPARAM wParam, LPARAM lParam)
{
	ZoomEdit3::m_update_trace = true;
	vector<int> v;
	double temp = ZoomEdit3::m_zoom_percent / 100;
	v = GetRationalRepresentation(temp, constants::init_bound,
	constants::zoom_max, constants::interval);
	m_zoom_den = v[1];
	CString buffer;
	buffer.Format(_T("%i"),m_zoom_den);
	SetWindowText(buffer);
	return 0;
}


// ZoomEdit3


double ZoomEdit3::m_zoom_percent = 0;

bool ZoomEdit3::m_spin_trace = false;


IMPLEMENT_DYNAMIC(ZoomEdit3, CEdit)


ZoomEdit3::ZoomEdit3()
{
}


ZoomEdit3::~ZoomEdit3()
{
}


BEGIN_MESSAGE_MAP(ZoomEdit3, CEdit)
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_CHANGE, &ZoomEdit3::OnEnChange)
	ON_MESSAGE(WM_USER_UPDATE, OnUserUpdate)
END_MESSAGE_MAP()


// ZoomEdit3 message handlers


void ZoomEdit3::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	CString buffer1;
	GetWindowText(buffer1);
	CStringA buffer2(buffer1);
	m_zoom_percent = atof(buffer2);
		if (m_zoom_percent < 100*constants::zoom_min) {
			m_zoom_percent = 100*constants::zoom_min;
		}
		else if (m_zoom_percent > 100*constants::zoom_max) {
			m_zoom_percent = 100*constants::zoom_max;
		}
	buffer1.Format(_T("%.*f"),2, m_zoom_percent);
	SetWindowText(buffer1);
}


int ZoomEdit3::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


void ZoomEdit3::OnEnChange()
{
	CString buffer;
	GetWindowText(buffer);
	CStringA buffer1(buffer);
	m_zoom_percent = atof(buffer1);
	if (m_zoom_percent < 100 * constants::zoom_min) {
		m_zoom_percent = 100 * constants::zoom_min;
	}
	else if (m_zoom_percent > 100 * constants::zoom_max) {
		m_zoom_percent = 100 * constants::zoom_max;
	}
	if (ZoomDialog::m_pedit1 != nullptr&&ZoomDialog::m_pedit2 != nullptr&&(!ZoomEdit3::m_update_trace||ZoomEdit3::m_spin_trace)) {
		::PostMessage(ZoomDialog::m_pedit1->m_hWnd, WM_USER_UPDATE, NULL, NULL);
		::PostMessage(ZoomDialog::m_pedit2->m_hWnd, WM_USER_UPDATE, NULL, NULL);
	}
	m_spin_trace = false;
	m_update_trace = false;
}


LRESULT ZoomEdit3::OnUserUpdate(WPARAM wParam, LPARAM lParam)
{
	m_update_trace = true;
	if (!m_spin_trace) {
		if (ZoomEdit1::m_zoom_num <= constants::num_max && ZoomEdit2::m_zoom_den <= constants::den_max) {
			m_zoom_percent = 100.0 * ZoomEdit1::m_zoom_num / ZoomEdit2::m_zoom_den;
		}
		else if (ZoomEdit1::m_zoom_num > constants::num_max) {
			m_zoom_percent = 100.0*constants::num_max / ZoomEdit2::m_zoom_den;
		}
		else if (ZoomEdit2::m_zoom_den > constants::den_max) {
			m_zoom_percent = 100.0 * ZoomEdit1::m_zoom_num / constants::den_max;
		}
	}
	if (m_zoom_percent < 100 * constants::zoom_min) {
		m_zoom_percent = 100 * constants::zoom_min;
	}
	else if (m_zoom_percent > 100 * constants::zoom_max) {
		m_zoom_percent = 100 * constants::zoom_max;
	}
	CString buffer;
	buffer.Format(_T("%.*f"), 2, m_zoom_percent);
	SetWindowText(buffer);
	return 0;
}





