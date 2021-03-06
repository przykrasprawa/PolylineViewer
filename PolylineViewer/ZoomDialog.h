#pragma once

#include "ZoomEdit.h"
#include "ZoomSpin.h"
#include "ZoomButton.h"
#include "utilities.h"
// ZoomDialog dialog



class ZoomDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ZoomDialog)

public:
	static  CWnd* m_pedit1;
	static  CWnd* m_pedit2;
	static  CWnd* m_pedit3;
	ZoomDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ZoomDialog();
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZOOMDIALOG };
#endif
	ZoomEdit1 m_edit1;
	ZoomEdit2 m_edit2;
	ZoomEdit3 m_edit3;
	ZoomSpin m_spin;
	ZoomButton m_button;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
};
