#include "admissionApp.h"
#include "mainFrame.h"

bool App::OnInit() {
	MainFrame* frame = new MainFrame("Rekrutacja");
	frame->Show(true);
	return true;
}