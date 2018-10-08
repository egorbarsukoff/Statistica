#include "stdafx.h"
#include "HistogramPlot.h"


double HistogramPlot::yMax() {
	return h->getDistributionHistogram().getMaxVal();
}

void HistogramPlot::printXLim() {
	for (int i = h->getDistributionHistogram().getMinX(); i <= h->getDistributionHistogram().getMaxX(); ++i) {
		pDC->TextOutW(contentX((3 * (i - h->getDistributionHistogram().getMinX()) + 1)*width_p)-5, contentY(0)+10, CString(std::to_string(i).c_str()));
	}
}

void HistogramPlot::printLegend() {
	std::string lambda = std::string("lambda = ") + std::to_string(h->getDistribution().getLambda());
	std::string n = std::string("n = ") + std::to_string(h->getDistributionHistogram().getSampleSize());
	std::string chi = std::string("chi-square = ") + std::to_string(h->getChiSquare());
	std::string dof = std::string("d.o.f. = ") + std::to_string(h->getDoF());
	std::string pval = std::string("p-value = ") + std::to_string(h->getPValue());
	pDC->TextOutW(legendX(), legendY(1), CString(lambda.c_str()));
	pDC->TextOutW(legendX(), legendY(2), CString(n.c_str()));
	pDC->TextOutW(legendX(), legendY(4), CString(chi.c_str()));
	pDC->TextOutW(legendX(), legendY(5), CString(dof.c_str()));
	pDC->TextOutW(legendX(), legendY(6), CString(pval.c_str()));
	


	pDC->SelectObject(brushRed);
	pDC->Rectangle(legendX(), legendY(7), legendX() + 30, legendY(8));
	pDC->TextOutW(legendX() + 40, legendY(7) + 6, CString("observed"));

	pDC->SelectObject(brushGreen);
	pDC->Rectangle(legendX(), legendY(9), legendX() + 30, legendY(10));
	pDC->TextOutW(legendX() + 40, legendY(9) + 6, CString("expected"));
}

void HistogramPlot::printContent() {
	pDC->SelectObject(penBlack);
	pDC->SelectObject(brushRed);
	for (int i = h->getDistributionHistogram().getMinX(); i <= h->getDistributionHistogram().getMaxX(); ++i) {
		pDC->Rectangle(contentX(3 * (i- h->getDistributionHistogram().getMinX())*width_p), contentY(0),
			contentX(3 * (i- h->getDistributionHistogram().getMinX())*width_p + width_p), contentY(h->getDistributionHistogram().getObs(i)/h->getDistributionHistogram().getMaxVal()));
	}
	pDC->SelectObject(brushGreen);
	for (int i = h->getDistributionHistogram().getMinX(); i <= h->getDistributionHistogram().getMaxX(); ++i) {
		pDC->Rectangle(contentX((3 * (i-h->getDistributionHistogram().getMinX()) + 1)*width_p), contentY(0),
			contentX((3 * (i-  h->getDistributionHistogram().getMinX()) + 2)*width_p ), contentY(h->getDistributionHistogram().getTheor(i) / h->getDistributionHistogram().getMaxVal()));
	}
}

HistogramPlot::HistogramPlot(CDC * pDC, const ChiSquareHistogram * _h) : Plot(pDC, "Poisson Distribution", "x", "P(x)"), h(_h) {
	brushRed.CreateSolidBrush(RGB(255, 0, 0));
	brushGreen.CreateSolidBrush(RGB(0, 255, 0));
	width_p = 1. / (3 * (1+h->getDistributionHistogram().getMaxX() - h->getDistributionHistogram().getMinX()));
}



