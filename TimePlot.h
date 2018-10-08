#pragma once
#include "plot.h"
#include "ParametersTime.h"


/// Plot the ParametersTime 
class TimePlot :
	public Plot {
	const ParametersTime& pt;
	CPen redPen, greenPen;
	double yMax();
	void printLegend();
	void printXLim();
	void printContent();
	void printLine(double(ParametersTime::*getter)(size_t) const, CPen& pen);
public:
	/// Constructor
	TimePlot(CDC *pDC, const ParametersTime* _pt);
};

