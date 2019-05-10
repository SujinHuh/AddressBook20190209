//FindingForm.cpp
#include "UpdatingForm.h"
#include "FindingForm.h"
#include "AddressBook.h"
#include <afxcmn.h>

BEGIN_MESSAGE_MAP(FindingForm , CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked) 
	ON_NOTIFY(NM_DBLCLK, IDC_LISTVIEW_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

//생성자
FindingForm::FindingForm(CWnd *parent) 
	:CDialog(FindingForm::IDD, parent) {
	this->indexes = NULL;
	this->count = 0;
}

//찾기 프레임 윈도우가 생성될 때
BOOL FindingForm::OnInitDialog() {
	CDialog::OnInitDialog();  //overriding

	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(0, "번호", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(1, "성명", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(2, "주소", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(3, "전화번호", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(4, "이메일주소", LVCFMT_CENTER, 100);

	return FALSE;  //사용법. 이렇게 해야 윈도우가 실행된다.
}

//찾기 버튼을 클릭했을 때
void FindingForm::OnFindButtonClicked() {
	CString number;
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	UpdatingForm *updatingForm;
	Long i = 0;
	Personal personal;

	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	updatingForm = (UpdatingForm*)(CWnd::FindWindowA("#32770", "주소록"));
	updatingForm->addressBook->Find((LPCTSTR)name, &this->indexes, &this->count);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->DeleteAllItems();
	while (i < count) {
		personal = updatingForm->addressBook->GetAt(indexes[i]);
		number.Format("%d", i+1);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertItem(i, number);
		name = CString(personal.GetName().c_str());
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 1, name);
		address = CString(personal.GetAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 2, address);
		telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 3, telephoneNumber);
		emailAddress = CString(personal.GetEmailAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 4, emailAddress);
		i++;
	}
}

//리스트뷰 컨트롤의 항목을 더블클릭했을 때
void FindingForm::OnListViewItemDoubleClicked(NMHDR* PNotifyStruct, LRESULT *result) {
	Long index;
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	UpdatingForm *updatingForm;

	index = ((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetSelectionMark();
	name = ((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 1);
	address = ((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 2);
	telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 3);
	emailAddress = ((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 4);
	
	updatingForm = (UpdatingForm*)(CWnd::FindWindow("#32770", "주소록"));
	updatingForm->GetDlgItem(IDC_EDIT_NAME)->SetWindowText(name);
	updatingForm->GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText(address);
	updatingForm->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText(telephoneNumber);
	updatingForm->GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText(emailAddress);
	((CListCtrl*)updatingForm->GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetSelectionMark(this->indexes[index]);

	if (this->indexes != 0) {
		delete[] this->indexes;
	}

	EndDialog(0);
}

//닫기 버튼을 클릭했을 때
void FindingForm::OnClose() {
	
	if (this->indexes != 0) {
		delete[] this->indexes;
	}

	EndDialog(0);
}
