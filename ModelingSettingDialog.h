#pragma once


// Диалоговое окно ModelingSettingDialog



class ModelingSettingDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ModelingSettingDialog)

public:
	ModelingSettingDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~ModelingSettingDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif
	int m_type;
	unsigned int m_nx;
	unsigned int m_np;
	unsigned int m_nbars;
	double m_lambda0;
	double m_lambda1;
	double m_time_lambda0;
	double m_time_lambda1;
	double m_time_step;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditLambda2();
};
