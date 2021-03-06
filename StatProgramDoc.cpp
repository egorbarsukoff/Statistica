
// StatProgramDoc.cpp: реализация класса CStatProgramDoc 
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "StatProgram.h"
#endif

#include "StatProgramDoc.h"

#include <propkey.h>
#include "CommonRandom.h"

std::mt19937 CommonRandom::mt;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStatProgramDoc

IMPLEMENT_DYNCREATE(CStatProgramDoc, CDocument)

BEGIN_MESSAGE_MAP(CStatProgramDoc, CDocument)
	ON_COMMAND(ID_CALL_SETTING_DIALOG, &CStatProgramDoc::OnCallSettingDialog)
	ON_COMMAND(ID_DO_MODELING, &CStatProgramDoc::OnDoModeling)
	ON_COMMAND(ID_PVAL_MODELING, &CStatProgramDoc::OnPvalModeling)
	ON_COMMAND(ID_PAR_TIME, &CStatProgramDoc::OnTimeModeling)
END_MESSAGE_MAP()


// Создание или уничтожение CStatProgramDoc

CStatProgramDoc::CStatProgramDoc() : 
	s(new Poisson1), model_type(0), n(100), pValSampleSize(1000), h(nullptr), printMode(0), pvd(nullptr), pt(nullptr),
	time_lambda0(0), time_lambda1(5), time_step(0.05), nbars(20)
{
	// TODO: добавьте код для одноразового вызова конструктора
}

CStatProgramDoc::~CStatProgramDoc()
{
	if (s != nullptr) delete s;
	if (h != nullptr) delete h;
	if (pvd != nullptr) delete pvd;
	if (pt != nullptr) delete pt;
}

BOOL CStatProgramDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	
	return TRUE;
}




// Сериализация CStatProgramDoc

void CStatProgramDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CStatProgramDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CStatProgramDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CStatProgramDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CStatProgramDoc

#ifdef _DEBUG
void CStatProgramDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStatProgramDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CStatProgramDoc


void CStatProgramDoc::OnCallSettingDialog() {
	ModelingSettingDialog d;
	d.m_type = model_type;
	d.m_nx = n;
	d.m_np = pValSampleSize;
	d.m_nbars = nbars;
	d.m_lambda0 =  d0.getLambda();
	d.m_lambda1 = d1.getLambda();
	d.m_time_lambda0 = time_lambda0;
	d.m_time_lambda1 = time_lambda1;
	d.m_time_step = time_step;
	if (d.DoModal() == IDOK) {
		delete s;
		s = nullptr;
		if (d.m_type == 0) {
			s = new Poisson1;
		}
		else if (d.m_type == 1) {
			s = new Poisson2;
		}
		n = d.m_nx;
		pValSampleSize = d.m_np;
		model_type = d.m_type;
		d0.setLambda(d.m_lambda0);
		d1.setLambda(d.m_lambda1);
		nbars = d.m_nbars;

		time_lambda0 = d.m_time_lambda0;
		time_lambda1 = d.m_time_lambda1;
		time_step = d.m_time_step;
	}
	// TODO: добавьте свой код обработчика команд
}

void CStatProgramDoc::OnDoModeling() {
	printMode = 1;
	s->modeling(d1, n);
	if (h != nullptr)
		delete h;
	h = new ChiSquareHistogram(s, d0);
	UpdateAllViews(0);
}






void CStatProgramDoc::OnPvalModeling() {
	printMode = 2;
	if (pvd != nullptr)
		delete pvd;
	pvd = new PValueDistribution(*s, d0, d1, nbars, n, pValSampleSize);
	pvd->simulate();
	UpdateAllViews(0);
}


void CStatProgramDoc::OnTimeModeling() {
	printMode = 3;
	if (pt != nullptr)
		delete pt;
	pt = new ParametersTime(time_lambda0, time_lambda1, time_step, n);
	pt->simulate();
	UpdateAllViews(0);
	// TODO: добавьте свой код обработчика команд
}
