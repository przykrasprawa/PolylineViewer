// ZoomDialog.cpp : implementation file
//
#include "stdafx.h"
#include "PolylineViewer.h"
#include "ChildView.h"
#include "ZoomDialog.h"
#include "afxdialogex.h"


// ZoomDialog dialog


CWnd* ZoomDialog::m_pedit1 = nullptr;
CWnd* ZoomDialog::m_pedit2 = nullptr;
CWnd* ZoomDialog::m_pedit3 = nullptr;


bool ZoomEdit1::m_update_trace = false;
bool ZoomEdit2::m_update_trace = false;
bool ZoomEdit3::m_update_trace = false;


IMPLEMENT_DYNAMIC(ZoomDialog, CDialogEx)


ZoomDialog::ZoomDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZOOMDIALOG, pParent)
{

}

ZoomDialog::~ZoomDialog()
{
}

void ZoomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_SPIN3, m_spin);
	DDX_Control(pDX, IDC_BUTTON, m_button);
}


BEGIN_MESSAGE_MAP(ZoomDialog, CDialogEx)
END_MESSAGE_MAP()


// ZoomDialog message handlers


BOOL ZoomDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_pedit1 = GetDlgItem(IDC_EDIT1);
	m_pedit2 = GetDlgItem(IDC_EDIT2);
	m_pedit3 = GetDlgItem(IDC_EDIT3);
	vector<int> v(2); 
	v=GetRationalRepresentation(CChildView::m_scurrent_zoom, constants::init_bound,
	constants::zoom_max, constants::interval);
	CSpinButtonCtrl spin_button;
	spin_button.Attach(GetDlgItem(IDC_SPIN1)->m_hWnd);
	spin_button.SetPos(v[1]);
	spin_button.SetRange(constants::num_min,constants::num_max);
	spin_button.Detach();
	spin_button.Attach(GetDlgItem(IDC_SPIN2)->m_hWnd);
	spin_button.SetPos(v[0]);
	spin_button.SetRange(constants::den_min, constants::den_max);
	spin_button.Detach();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


