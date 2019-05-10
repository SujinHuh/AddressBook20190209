//UpdatingForm.cpp
#include "UpdatingForm.h"
#include "FindingForm.h"
#include "AddressBook.h"
#include <afxcmn.h>
#include <afxdb.h>

BEGIN_MESSAGE_MAP(UpdatingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTVIEW_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

UpdatingForm::UpdatingForm(CWnd *parent)
	:CDialog(UpdatingForm::IDD, parent) {

	this->addressBook = NULL;
}

BOOL UpdatingForm::OnInitDialog() {
	CDialog::OnInitDialog();

	this->addressBook = new AddressBook;
	CString number;
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Personal personal;
	Long i = 0;

	Load();

	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(0, "번호", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(1, "성명", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(2, "주소", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(3, "전화번호", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertColumn(4, "이메일주소", LVCFMT_CENTER, 100);

	while (i < this->addressBook->GetLength()) {
		personal = this->addressBook->GetAt(i);
		number.Format("%d", i + 1);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertItem(i, number);
		name = CString(personal.GetName().c_str());
		address = CString(personal.GetAddress().c_str());
		telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
		emailAddress = CString(personal.GetEmailAddress().c_str());
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 1, name);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 2, address);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 3, telephoneNumber);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 4, emailAddress);
		i++;
	}

	return FALSE;
}

void UpdatingForm::OnRecordButtonClicked() {
	Long index;
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	CString number;
	Personal personal;

	GetDlgItem(IDC_EDIT_NAME)->GetWindowTextA(name);
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowTextA(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowTextA(emailAddress);

	index = this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);

	Insert(index);

	personal = this->addressBook->GetAt(index);

	name = CString(personal.GetName().c_str());
	address = CString(personal.GetAddress().c_str());
	telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
	emailAddress = CString(personal.GetEmailAddress().c_str());

	number.Format("%d", index + 1);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertItem(index, number);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 1, name);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 2, address);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 3, telephoneNumber);
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 4, emailAddress);
}

void UpdatingForm::OnFindButtonClicked() {
	FindingForm findingForm;

	findingForm.DoModal();
}

void UpdatingForm::OnCorrectButtonClicked() {
	Long index;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Personal personal;

	index = ((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetSelectionMark();
	GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowTextA(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowTextA(emailAddress);
	index = this->addressBook->Correct(index, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);

	Modify(index);

	personal = this->addressBook->GetAt(index);
	address = CString(personal.GetAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 2, address);
	telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 3, telephoneNumber);
	emailAddress = CString(personal.GetEmailAddress().c_str());
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(index, 4, emailAddress);
}

//지우기 버튼을 클릭했을 때
void UpdatingForm::OnEraseButtonClicked() {
	Long index;
	Personal personal;
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	CString number;
	Long i = 0;

	//5.1.선택되어진 리스트뷰 컨트롤러의 인덱스를 읽는다.
	index = ((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetSelectionMark();
	//5.2 주소록에서 지운다.
	this->addressBook->Erase(index);
	
	Delete(index);

	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->DeleteAllItems();

	//5.4 리스트뷰컨트롤러의 항목을 개인의 개수만큼 추가한다.
	i = 0;
	while (i < this->addressBook->GetLength())
	{
		personal = this->addressBook->GetAt(i);

		number.Format("%d", i + 1);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertItem(i, number);

		name = CString(personal.GetName().c_str());
		address = CString(personal.GetAddress().c_str());
		telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
		emailAddress = CString(personal.GetEmailAddress().c_str());

		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 1, name);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 2, address);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 3, telephoneNumber);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 4, emailAddress);
		i++;
	}
}

//정리하기 버튼을 클릭했을 때
void UpdatingForm::OnArrangeButtonClicked() {
	Personal personal;
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	CString number;
	Long i = 0;

	//6.1 주소록을 정리한다.
	this->addressBook->Arrange();

	//6.2 리스트뷰컨트롤의 모든 항목을 지운다.
	((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->DeleteAllItems();

	//6.3 주소록의 개인 개수만큼 리스트뷰컨트롤의 항목을 추가한다.
	while (i < this->addressBook->GetLength()) {
		personal = this->addressBook->GetAt(i);
		number.Format("%d", i + 1);
		name = CString(personal.GetName().c_str());
		address = CString(personal.GetAddress().c_str());
		telephoneNumber = CString(personal.GetTelephoneNumber().c_str());
		emailAddress = CString(personal.GetEmailAddress().c_str());

		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->InsertItem(i, number);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 1, name);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 2, address);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 3, telephoneNumber);
		((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->SetItemText(i, 4, emailAddress);
		i++;
	}
}

//리스트뷰 컨트롤의 항목을 더블클릭했을 때
void UpdatingForm::OnListViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT* result) {
	Long index;
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;

	index = ((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetSelectionMark();
	name = ((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 1);
	address = ((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 2);
	telephoneNumber = ((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 3);
	emailAddress = ((CListCtrl*)GetDlgItem(IDC_LISTVIEW_PERSONALS))->GetItemText(index, 4);

	GetDlgItem(IDC_EDIT_NAME)->SetWindowTextA(name);
	GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowTextA(address);
	GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowTextA(telephoneNumber);
	GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowTextA(emailAddress);
}


//닫기 버튼을 클릭했을 때
void UpdatingForm::OnClose() {

	if (this->addressBook != NULL) {
		
		Save();
		
		delete this->addressBook;
	}
	EndDialog(0);
}

//로드
void UpdatingForm::Load() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.name, Personal.address,"
		"Personal.telephoneNumber,"
		"Personal.emailAddress FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=rla789456");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;

	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, name);
		rs.GetFieldValue((short)1, address);
		rs.GetFieldValue((short)2, telephoneNumber);
		rs.GetFieldValue((short)3, emailAddress);
		this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);
		rs.MoveNext();
	}
	
	rs.Close();
	db.Close();
}

void UpdatingForm::Save() {
	CDatabase db;
	CRecordset rs(&db);
	CString code;
	Long i = 0;
	Personal personal;

	CString sql = "SELECT personal.code FROM Personal;";
	db.OpenEx("DSN=addressbook;UID=root;PWD=rla789456");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	sql = "DELETE FROM personal;";
	db.ExecuteSQL(sql);

	while (i < this->addressBook->GetLength()) {
		personal = this->addressBook->GetAt(i);
		rs.GetFieldValue((short)0, code);
		sql.Format("INSERT INTO personal(code, name, address, telephoneNumber, emailAddress) VALUES('%s', '%s', '%s', '%s', '%s');",
			(LPCTSTR)code, personal.GetName().c_str(),personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str());
		db.ExecuteSQL(sql);
		rs.MoveNext();
		i++;
	}

	rs.Close();
	db.Close();
}

//tnwjd
void UpdatingForm::Insert(Long index) {
	CDatabase db;
	Personal personal = this->addressBook->GetAt(index);
	CString sql;

	sql.Format("INSERT INTO personal(code, name, address, telephoneNumber, emailAddress) VALUES('%s', '%s', '%s', '%s', '%s');", (LPCTSTR)MakeCode(), personal.GetName().c_str(), personal.GetAddress().c_str(),
		personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str());
	db.OpenEx("DSN=addressBook;UID=root;PWD=rla789456");
	db.ExecuteSQL(sql);
	db.Close();
}

CString UpdatingForm::MakeCode() {
	CDatabase db;
	CRecordset rs(&db);
	int codeInt;
	CString code = "P0001";
	CString sql = "SELECT Personal.code FROM Personal ORDER BY Personal.code DESC;";

	db.OpenEx("DSN=AddressBook;UID=root;PWD=rla789456");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code);
		code = code.Right(4);
		codeInt = _ttoi(code);
		codeInt++;
		code.Format("P%04d", codeInt);
	}

	rs.Close();
	db.Close();

	return code;
}

void UpdatingForm::Delete(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	CString code;
	Long i = 0;

	CString sql = "SELECT Personal.code FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=rla789456");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	while (!rs.IsEOF() && i <= index) {
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("DELETE FROM Personal WHERE Personal.code = '%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);
	db.Close();
}

void UpdatingForm::Modify(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	CString code;
	Long i = 0;
	Personal personal = this->addressBook->GetAt(index);

	CString sql = "SELECT Personal.code FROM Personal;";
	db.OpenEx("DSN=AddressBook;UID=root;PWD=rla789456");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	while (!rs.IsEOF() && i <= index) {
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("UPDATE Personal SET address = '%s', telephoneNumber = '%s', emailAddress = '%s' WHERE Personal.code = '%s';", (LPCTSTR)personal.GetAddress().c_str(),
		(LPCTSTR)personal.GetTelephoneNumber().c_str(), (LPCTSTR)personal.GetEmailAddress().c_str(), (LPCTSTR)code);
	db.ExecuteSQL(sql);

	rs.Close();
	db.Close();
}


