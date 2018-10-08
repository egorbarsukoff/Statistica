#pragma once

#include <string>

/// Abstract plot
class Plot {
	int screenWidth, screenHeight;
	static const int legendWidth = 250;
	std::string plotName, xLab, yLab;
protected:
	/// Returns the Y upper limit
	virtual double yMax() = 0; 
	/// Plots legend
	virtual void printLegend() = 0; 
	/// Plots axis
	void printAxis(); 
	/// Prints the names of the plot and the axis
	void printNames(std::string plotName, std::string xLab, std::string yLab); 
	/// Prints the Y Limits
	void printYLim(); 
	/// Prints the X Limits
	virtual void printXLim() = 0; 
	/// Prints the content of of plot
	virtual void printContent() = 0; 
	/// Transorm relative X coordinate to absolute
	int contentX(double x); 
	/// Transorm relative Y coordinate to absolute
	int contentY(double y); 
	/// Returns absolute Y coordinate of the i-th line of legend
	int legendY(int line); 
	/// Returns absolute X coordinate of legend
	int legendX(); 
	/// Print device 
	CDC * pDC;
	/// Black pen for drawing
	CPen penBlack;
	
public:
	/// Constructor
	Plot(CDC* _pDC, std::string plotName, std::string xLab, std::string yLab); 
	/// Makes plot
	void plot(); 
};

