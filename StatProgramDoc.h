
// StatProgramDoc.h: интерфейс класса CStatProgramDoc 
//


#pragma once
#include "ModelingSettingDialog.h"
#include "Sample.h"
#include "Poisson1.h"
#include "Poisson2.h"
#include "ChiSquareHistogram.h"
#include "PValueDistribution.h"
#include "ParametersTime.h"


class CStatProgramDoc : public CDocument
{
protected: // создать только из сериализации
	CStatProgramDoc();
	DECLARE_DYNCREATE(CStatProgramDoc)

// Атрибуты
public:
	size_t n;
	unsigned int pValSampleSize;
	int model_type;
	int nbars;
	int printMode;
	Sample * s;
	Distribution d0;
	Distribution d1;
	ChiSquareHistogram *h;
	PValueDistribution *pvd;

	double time_lambda0;
	double time_lambda1;
	double time_step;
	ParametersTime *pt;
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CStatProgramDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnCallSettingDialog();
	afx_msg void OnDoModeling();
	afx_msg void OnPvalModeling();
	afx_msg void OnTimeModeling();
};
