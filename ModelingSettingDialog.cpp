// ModelingSettingDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "StatProgram.h"
#include "ModelingSettingDialog.h"
#include "afxdialogex.h"


// Диалоговое окно ModelingSettingDialog

IMPLEMENT_DYNAMIC(ModelingSettingDialog, CDialogEx)

ModelingSettingDialog::ModelingSettingDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ModelingSettingDialog::~ModelingSettingDialog()
{
}

void ModelingSettingDialog::DoDataExchange(CDataExchange* pDX)
{
	DDX_Radio(pDX, IDC_RADIO_TYPE, m_type);
	DDX_Text(pDX, IDC_EDIT_LAMBDA, m_lambda0);
	DDX_Text(pDX, IDC_EDIT_N, m_nx);
	DDX_Text(pDX, IDC_EDIT_LAMBDA2, m_lambda1);
	DDX_Text(pDX, IDC_EDIT_N2, m_np);
	DDX_Text(pDX, IDC_EDIT_N3, m_nbars);
	DDX_Text(pDX, IDC_EDIT_TIME_LAMBDA0, m_time_lambda0);
	DDX_Text(pDX, IDC_EDIT_TIME_LAMBDA1, m_time_lambda1);
	DDX_Text(pDX, IDC_EDIT_TIME_STEP, m_time_step);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModelingSettingDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &ModelingSettingDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ModelingSettingDialog::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_LAMBDA2, &ModelingSettingDialog::OnEnChangeEditLambda2)
END_MESSAGE_MAP()


// Обработчики сообщений ModelingSettingDialog


void ModelingSettingDialog::OnBnClickedOk() {
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(1);
	if (m_lambda0 < 0 || m_lambda1 < 0 || m_time_lambda0 < 0 || m_time_lambda1 < 0) {
		AfxMessageBox(L"Параметр распределения должен быть больше нуля");
			return;
	}
	if (m_time_lambda0 > m_time_lambda1 || 2*m_time_step > m_time_lambda1 - m_time_lambda0) {
		AfxMessageBox(L"Неправильные параметры");
		return;
	}
	CDialogEx::OnOK();
}




void ModelingSettingDialog::OnBnClickedCancel() {
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}


void ModelingSettingDialog::OnEnChangeEditLambda2() {
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}
