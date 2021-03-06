#define _CRT_SECURE_NO_WARNINGS
// StatProgramView.cpp: реализация класса CStatProgramView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "StatProgram.h"
#endif

#include "StatProgramDoc.h"
#include "StatProgramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStatProgramView

IMPLEMENT_DYNCREATE(CStatProgramView, CView)

BEGIN_MESSAGE_MAP(CStatProgramView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CStatProgramView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CStatProgramView

CStatProgramView::CStatProgramView()
{
	// TODO: добавьте код создания

}

CStatProgramView::~CStatProgramView()
{
}

BOOL CStatProgramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CStatProgramView

void CStatProgramView::OnDraw(CDC* pDC)
{
	CStatProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->printMode == 1) 
		printHistogram(pDoc->h, pDC);
	if (pDoc->printMode == 2)
		printPValDistribution(pDoc->pvd, pDC);
	if (pDoc->printMode == 3)
		printTimePlot(pDoc->pt, pDC);
	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CStatProgramView


void CStatProgramView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CStatProgramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CStatProgramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CStatProgramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CStatProgramView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CStatProgramView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CStatProgramView

#ifdef _DEBUG
void CStatProgramView::AssertValid() const
{
	CView::AssertValid();
}

void CStatProgramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStatProgramDoc* CStatProgramView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStatProgramDoc)));
	return (CStatProgramDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CStatProgramView

void CStatProgramView::printHistogram(const ChiSquareHistogram * h, CDC* pDC) {
	HistogramPlot hp1(pDC, h);
	hp1.plot();
}

void CStatProgramView::printPValDistribution(const PValueDistribution * pwd, CDC* pDC) {
	PValueDistributionPlot hp1(pDC, *pwd);
	hp1.plot();
}

void CStatProgramView::printTimePlot(const ParametersTime * pt, CDC * pDC) {
	TimePlot tp(pDC, pt);
	tp.plot();
}