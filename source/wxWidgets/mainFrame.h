#include <wx/wx.h>
#include "wx/listbox.h"

#include <vector>
#include <string>
#include <map>

class Major;

using namespace::std;

enum IDs {
	SCORE_ID = 0,
	NAME_ID = 1,
	MAJOR_ID = 2,

	GET_NAME_ID = 3,
	GET_SCORE_ID = 4,
	ADD_MAJOR_ID = 5,
	CANDIDATE_ID = 6,
	APPLICATION_ID = 7,
	TIN_ID = 8,
	TEL_ID = 9,
	CBE_ID = 10,
	IST_ID = 11,
	RESULTS_ID = 12,
};

class MainFrame : public wxFrame {
private:
	shared_ptr<Major> TIN;
	shared_ptr<Major> IST;
	shared_ptr<Major> TEL;
	shared_ptr<Major> CBE;

	unordered_map<string, shared_ptr<Major>> majorsMap;
	long candidateScore;
	wxString candidateName;
	wxString chosenMajor;
	vector<shared_ptr<Major>> candidateMajors;

	wxTextCtrl* setName;
	wxTextCtrl* setScore;
	wxListBox* majorChoose;
	wxListBox* candidateInfo; 
	wxListBox* qualified_TIN;
	wxListBox* qualified_CBE;
	wxListBox* qualified_TEL;
	wxListBox* qualified_IST;

	wxPanel* panel;

	wxButton* getScore;
	wxButton* getName;
	wxButton* addMajor;
	wxButton* setApplication;
	wxButton* showResults;

	void GetScore(wxCommandEvent& event); 
	void GetName(wxCommandEvent& event); 
	void GetMajor(wxCommandEvent& event);
	void AddMajor(wxCommandEvent& event);
	void SetApplication(wxCommandEvent& event);
	void ShowResults(wxCommandEvent& event);
	void SetMajors();
	void Setup();
	void AddToResults(shared_ptr<Major> major, wxListBox* list);
	void ResultsSetup();

public:
	MainFrame(const wxString& title);

	wxDECLARE_EVENT_TABLE();
};