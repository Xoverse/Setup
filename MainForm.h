#pragma once

using namespace System;
using namespace System::Media;
using namespace System::Windows::Forms;

namespace XoverseSetup
{
	public ref class MainForm : Form
	{
	public:
		MainForm();
	private:
		Panel^ colorBar;
		Panel^ topBar;
		Button^ closeBtn;
		Button^ minBtn;
		Label^ title;
		Button^ musTgl;
		PictureBox^ logo;
		Label^ installDir_label;
		TextBox^ installDir;
		Button^ installDir_browse;
		Button^ install;

		SoundPlayer^ music;

		void InitializeComponent();
		System::Resources::ResourceManager^ getResourceManager();
		void formClosing(Object^ sender, FormClosingEventArgs^ e);
		void closeBtn_Click(Object^ sender, EventArgs^ e);
		void minBtn_Click(Object^ sender, EventArgs^ e);
		void musTgl_Click(Object^ sender, EventArgs^ e);
		void installDir_browse_Click(Object^ sender, EventArgs^ e);
		void install_Click(Object^ sender, EventArgs^ e);
	};
}