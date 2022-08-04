#include "MainForm.h"

[STAThreadAttribute]
int WinMain()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(true);

	Application::Run(gcnew XoverseSetup::MainForm());

	return 0;
}