#include "stdafx.h"
#include "plot.h"


Plot::Plot(CDC* _pDC, std::string _plotName, std::string _xLab, std::string _yLab) : 
	pDC(_pDC), plotName(_plotName), xLab(_xLab), yLab(_yLab) {
	penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CRect rc;
	GetClientRect(::GetActiveWindow(), &rc);
	screenHeight = rc.Height();
	screenWidth = rc.Width();
	
}

void Plot::plot() {
	printAxis();
	printNames(plotName, xLab, yLab);
	printYLim();
	printXLim();
	printLegend();
	printContent();
}

void Plot::printAxis() {
	pDC->SelectObject(&penBlack);

	// Оси
	pDC->MoveTo(40, 40);
	pDC->LineTo(40, screenHeight - 100);
	pDC->LineTo(screenWidth - legendWidth, screenHeight - 100);

	// Стрелочки
	pDC->LineTo(screenWidth - legendWidth - 10, screenHeight - 100 + 4);
	pDC->MoveTo(screenWidth - legendWidth, screenHeight - 100);
	pDC->LineTo(screenWidth - legendWidth - 10, screenHeight - 100 - 4);
	pDC->MoveTo(40, 40);
	pDC->LineTo(40 - 4, 40 + 10);
	pDC->MoveTo(40, 40);
	pDC->LineTo(40 + 4, 40 + 10);
}

void Plot::printNames(std::string plotName, std::string xLab, std::string yLab) {
	pDC->TextOutW(screenWidth / 2 - plotName.size() * 3, 20, CString(plotName.c_str()));
	pDC->TextOutW(49, 25, CString(yLab.c_str()));
	pDC->TextOutW(screenWidth - legendWidth , screenHeight - 100 - 20, CString(xLab.c_str()));
}

void Plot::printYLim() {
	double max = yMax();
	int n = 5;
	for (int i = 0; i <= n; ++i) {
		pDC->TextOutW(5 ,int( (screenHeight - 100  - 40)* (i / double(n))) + 40,
			CString(std::to_string(((n-i)/5.)*max).substr(0, 4).c_str()));
		pDC->MoveTo(35, int((screenHeight - 100 - 40)* (i / double(n))) + 40);
		if (i != 0 && i != n) 
			pDC->LineTo(45, int((screenHeight - 100 - 40)* (i / double(n))) + 40);
	}
}

int Plot::contentX(double x) {
	return (screenWidth - legendWidth - 40)*x + 40;
}

int Plot::contentY(double y) {
	return (screenHeight - 100 - 40)*(1-y) + 40;
}

int Plot::legendY(int line) {
	return 20 + line*30;
}

int Plot::legendX() {
	return screenWidth - legendWidth + 10;
}
