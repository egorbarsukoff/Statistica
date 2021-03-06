
// StatProgramView.h: интерфейс класса CStatProgramView
//

#pragma once
#include "plot.h"
#include "HistogramPlot.h"
#include "PValueDistributionPlot.h"
#include "TimePlot.h"

class CStatProgramView : public CView
{
protected: // создать только из сериализации
	CStatProgramView();
	DECLARE_DYNCREATE(CStatProgramView)

// Атрибуты
public:
	CStatProgramDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CStatProgramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void printHistogram(const ChiSquareHistogram * h, CDC* pDC);
	void printPValDistribution(const PValueDistribution * pvd, CDC* pDC);
	void printTimePlot(const ParametersTime * pt, CDC* pDC);
// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в StatProgramView.cpp
inline CStatProgramDoc* CStatProgramView::GetDocument() const
   { return reinterpret_cast<CStatProgramDoc*>(m_pDocument); }
#endif

