#pragma once
#include "plot.h"
#include "PValueDistribution.h"


/// Plot of p-value empirical distribution function
class PValueDistributionPlot :
	public Plot {
	CPen redPen;
	CBrush whiteBrush;
	double width_p;
	const PValueDistribution& pvd;
	double yMax();
	void printXLim();
	void printLegend();
	void printContent();
public:
	/// Constructor
	PValueDistributionPlot(CDC* pDC, const PValueDistribution& _pvd);
	/// Destructor
	~PValueDistributionPlot();
};

