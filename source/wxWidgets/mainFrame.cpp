#include "mainFrame.h"
#include "candidate.h"
#include "major.h"

void MainFrame::Setup() {
	TIN = make_shared<Major>();
	IST = make_shared<Major>();
	TEL = make_shared<Major>();
	CBE = make_shared<Major>();

	majorsMap = {
		{"Teleinfromatics", TIN},
		{"Applied computer science", IST},
		{"Telecommunications", TEL},
		{"Cybersecurity", CBE}
	};
}
void MainFrame::SetMajors() {
	majorChoose->Append("Teleinformatics");
	majorChoose->Append("Applied computer science");
	majorChoose->Append("Cybersecurity");
	majorChoose->Append("Telecomunications");
}

void MainFrame::GetScore(wxCommandEvent& event) {
	long newScore = -1;
	setScore->GetValue().ToLong(&newScore);
	if (newScore >= 0 && newScore <= 520) candidateScore = newScore; // points bracket is 0-520 pts
	wxLogStatus(wxString::Format("%ld", candidateScore) + " points");
	return;
}

void MainFrame::GetName(wxCommandEvent& event) {
	candidateName = setName->GetValue();
	wxLogStatus("candidate " + candidateName);
	return;
}

void MainFrame::GetMajor(wxCommandEvent& event) {
	int index = event.GetSelection();
	if (index != wxNOT_FOUND) {
		chosenMajor = event.GetString();
	}
	wxLogStatus(chosenMajor);
	return;
}

void MainFrame::AddMajor(wxCommandEvent& event) {
	if (majorsMap.find(chosenMajor.ToStdString()) == majorsMap.end()) {
		return;
	}
	auto it = find(candidateMajors.begin(), candidateMajors.end(), majorsMap[chosenMajor.ToStdString()]);
	if (it != candidateMajors.end()) {
		candidateMajors.erase(it);
	}
	candidateMajors.push_back(majorsMap[chosenMajor.ToStdString()]);
}

void MainFrame::SetApplication(wxCommandEvent& event) {
	if (candidateMajors.empty() || candidateScore == INT_MIN || candidateName == "") return;
	shared_ptr<Candidate> newCandidate = make_shared<Candidate>(candidateName.ToStdString(), int(candidateScore), candidateMajors); // allows priorities
	if (!newCandidate) {
		return;
	}
	for (auto& it : candidateMajors) {
		if (it) {
			it->AddCandidate(newCandidate);
		}
	}
	wxLogStatus("added succesfully");
	chosenMajor = "";
	candidateName = "";
	candidateScore = INT_MIN;
}

void MainFrame::AddToResults(shared_ptr<Major> major, wxListBox* list) {
	if (major->AcceptedList().empty()) return;
	set<shared_ptr<Candidate>> accepted = major->AcceptedList();
	for (auto& it : accepted) {
		list->Append(wxString(it->GetName()));
	}
}

void MainFrame::ShowResults(wxCommandEvent& event) {
	TIN->ProcessApplications(5);
	TEL->ProcessApplications(5);
	IST->ProcessApplications(5);
	CBE->ProcessApplications(5);


	
	this->AddToResults(TIN, qualified_TIN);
	this->AddToResults(CBE, qualified_CBE);
	this->AddToResults(TEL, qualified_TEL);
	this->AddToResults(IST, qualified_IST);

	for (auto& control : panel->GetChildren()) {
		control->Hide();
	}

	panel->Layout();

	qualified_CBE->Show();
	qualified_IST->Show();
	qualified_TEL->Show();
	qualified_TIN->Show();
}

void MainFrame::ResultsSetup() {
	qualified_CBE = new wxListBox(panel, CBE_ID, wxPoint(155, 250), wxSize(100, 400));
	qualified_TIN = new wxListBox(panel, TIN_ID, wxPoint(265, 250), wxSize(100, 400));
	qualified_IST = new wxListBox(panel, IST_ID, wxPoint(375, 250), wxSize(100, 400));
	qualified_TEL = new wxListBox(panel, TEL_ID, wxPoint(485, 250), wxSize(100, 400));
	qualified_CBE->Append("CBE");
	qualified_TEL->Append("TEL");
	qualified_TIN->Append("TIN");
	qualified_IST->Append("IST");
	qualified_CBE->Hide();
	qualified_TEL->Hide();
	qualified_TIN->Hide();
	qualified_IST->Hide();
}

MainFrame::MainFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {

	this->Setup();

	chosenMajor = "";
	candidateName = "";
	candidateScore = INT_MIN;

	panel = new wxPanel(this, wxID_ANY);

	CreateStatusBar();

	getName = new wxButton(panel, GET_NAME_ID, "add name", wxPoint(265, 170), wxSize(100, 30));

	getScore = new wxButton(panel, GET_SCORE_ID, "add score", wxPoint(265, 210), wxSize(100, 30));

	setName = new wxTextCtrl(panel, NAME_ID, "name", wxPoint(155, 170), wxSize(100, 30));

	setScore = new wxTextCtrl(panel, SCORE_ID, "score", wxPoint(155, 210), wxSize(100, 30));

	majorChoose = new wxListBox(panel, MAJOR_ID, wxPoint(155, 250), wxSize(300, 100));

	addMajor = new wxButton(panel, ADD_MAJOR_ID, "add major", wxPoint(465, 285), wxSize(100, 30));

	setApplication = new wxButton(panel, APPLICATION_ID, "set application", wxPoint(155, 365), wxSize(200, 60));

	showResults = new wxButton(panel, RESULTS_ID, "show results", wxPoint(465, 485), wxSize(100, 30));

	this->ResultsSetup();
		
	this->SetMajors();
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_LISTBOX(MAJOR_ID, MainFrame::GetMajor)
EVT_BUTTON(GET_SCORE_ID, MainFrame::GetScore)
EVT_BUTTON(GET_NAME_ID, MainFrame::GetName)
EVT_BUTTON(ADD_MAJOR_ID, MainFrame::AddMajor)
EVT_BUTTON(APPLICATION_ID, MainFrame::SetApplication)
EVT_BUTTON(RESULTS_ID, MainFrame::ShowResults)
wxEND_EVENT_TABLE()