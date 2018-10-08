#pragma once
#include "plot.h"
#include "ChiSquareHistogram.h"

///Plotting DistributionHistogram and display chi-square
class HistogramPlot : public Plot {
private:
	const ChiSquareHistogram *h; 
	CBrush brushRed; 
	CBrush brushGreen; 
	double width_p; 
	double yMax(); 
	void printXLim(); 
	void printLegend(); 
	void printContent(); 
public:
	/// Constructor
	HistogramPlot(CDC* pDC, const ChiSquareHistogram * _h); 
};

