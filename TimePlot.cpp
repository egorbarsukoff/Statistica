#include "stdafx.h"
#include "TimePlot.h"



TimePlot::TimePlot(CDC *pDC, const ParametersTime * _pt) : 
	Plot(pDC, "Time dependence on lambda", "lambda", "t, ms"), pt(*_pt), redPen(PS_SOLID, 2, RGB(255, 0, 0)), greenPen(PS_SOLID, 2, RGB(0, 255, 0)) {}


double TimePlot::yMax() {
	return pt.getMax();
}

void TimePlot::printLegend() {
	pDC->SelectObject(redPen);
	pDC->MoveTo(legendX(), legendY(1) + 7);
	pDC->LineTo(legendX()+30, legendY(1) + 7);
	pDC->TextOutW(legendX()+40, legendY(1), CString("Poisson1"));

	pDC->SelectObject(greenPen);
	pDC->MoveTo(legendX(), legendY(2) + 7);
	pDC->LineTo(legendX() + 30, legendY(2) + 7);
	pDC->TextOutW(legendX() + 40, legendY(2), CString("Poisson2"));

	std::string stepstr = std::string("Plot step = ") + std::to_string(pt.getStep());
	pDC->TextOutW(legendX(), legendY(4), CString(stepstr.c_str()));
}

void TimePlot::printXLim() {
	static const int n = 5;
	for (int i = 0; i <= n; ++i) {
		if (i != 0 && i != n) {
			pDC->MoveTo(contentX((double)i / n), contentY(0) + 5);
			pDC->LineTo(contentX((double)i / n), contentY(0) - 5);
		}
		if (i != 0)
			pDC->TextOutW(contentX((double)i / n) - 10, contentY(0) + 10, 
				CString(std::to_string(pt.getA() + (pt.getB() - pt.getA()) * (double)i / n).substr(0, 4).c_str()));

	}
}

void TimePlot::printContent() {
	if (pt.getN() == 0)
		return;
	printLine(&ParametersTime::getTime1, redPen);
	printLine(&ParametersTime::getTime2, greenPen);
}

void TimePlot::printLine(double(ParametersTime::*getter)(size_t) const, CPen& pen) {
	pDC->SelectObject(pen);
	pDC->MoveTo(contentX(0), contentY((pt.*getter)(0) / pt.getMax()));
	for (int i = 1; i < pt.getN(); ++i) {
		pDC->LineTo(contentX(i*pt.getStep() / (pt.getB() - pt.getA())), contentY((pt.*getter)(i) / pt.getMax()));
	}
}
