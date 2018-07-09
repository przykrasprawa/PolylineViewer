#pragma once


// ZoomSpin


namespace constants {
	constexpr double spin_delta = 10;
}
class ZoomSpin : public CSpinButtonCtrl
{
	DECLARE_DYNAMIC(ZoomSpin)

public:
	ZoomSpin();
	virtual ~ZoomSpin();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDeltapos(NMHDR *pNMHDR, LRESULT *pResult);
};


