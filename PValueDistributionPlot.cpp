#include "stdafx.h"
#include "PValueDistributionPlot.h"



double PValueDistributionPlot::yMax() {
	return 1;
}

void PValueDistributionPlot::printXLim() {
	static const int n = 5;
	for (int i = 0; i <= n; ++i) {
		if (i != 0 && i != n) {
			pDC->MoveTo(contentX((double)i / n), contentY(0) + 5);
			pDC->LineTo(contentX((double)i / n), contentY(0) - 5);
		}
		if (i != 0)
			pDC->TextOutW(contentX((double)i / n) - 10, contentY(0) + 10, CString(std::to_string((double)i/n).substr(0, 4).c_str()));

	}
}

void PValueDistributionPlot::printLegend() {
	std::string lambda0 = std::string("lambda H0 = ") + std::to_string(pvd.getH0Lambda());
	std::string lambda1 = std::string("lambda H1 = ") + std::to_string(pvd.getH1Lambda());
	std::string ss = std::string("samples size = ") + std::to_string(pvd.getSampleSize());
	std::string rs = std::string("pVal sample size = ") + std::to_string(pvd.getRepeats());

	pDC->TextOutW(legendX(), legendY(1), CString(lambda0.c_str()));
	pDC->TextOutW(legendX(), legendY(2), CString(lambda1.c_str()));
	pDC->TextOutW(legendX(), legendY(3), CString(ss.c_str()));
	pDC->TextOutW(legendX(), legendY(4), CString(rs.c_str()));

	pDC->SelectObject(whiteBrush);
	pDC->Rectangle(legendX(), legendY(6), legendX() + 30, legendY(7));
	pDC->TextOutW(legendX() + 40, legendY(6) + 6, CString("emperical"));

	pDC->SelectObject(redPen);
	pDC->MoveTo(legendX(), legendY(8)+7);
	pDC->LineTo(legendX()+30, legendY(8)+7);
	pDC->TextOutW(legendX() + 40, legendY(8), CString("theoretical"));
}

void PValueDistributionPlot::
printContent() {
	pDC->SelectObject(penBlack);
	pDC->SelectObject(whiteBrush);
	for (size_t i = 0; i < pvd.getNCol(); ++i) {
		pDC->Rectangle(contentX(i*width_p)+1, contentY(0), contentX((i+1)*width_p)-1, contentY(pvd((double)i/pvd.getNCol())));
	}
	pDC->SelectObject(redPen);
	pDC->MoveTo(contentX(0), contentY(0));
	pDC->LineTo(contentX(1), contentY(1));
}

PValueDistributionPlot::PValueDistributionPlot(CDC * pDC, const PValueDistribution& _pvd) : 
	Plot(pDC, "P-value distribution", "a", "P(pval < a)"), pvd(_pvd), redPen(PS_SOLID, 2, RGB(255, 100, 100)) {
	whiteBrush.CreateSolidBrush(RGB(255, 255, 255));
	width_p = (double)1 / pvd.getNCol();
}

PValueDistributionPlot::~PValueDistributionPlot() {
}
