#include "Config.h"
#include "MainForm.h"
using namespace XoverseSetup;

bool musicPause = false;
bool bypassExitPrompt = false;

System::Resources::ResourceManager^ MainForm::getResourceManager()
{
	auto resourceAssembly = Reflection::Assembly::GetExecutingAssembly();
	// .Resources is the name generated by resxgen, e.g., from the input file name Resources.resx
	auto resourceName = resourceAssembly->GetName()->Name + ".Resources";
	auto resourceManager = gcnew Resources::ResourceManager(resourceName, resourceAssembly);

	return resourceManager;
}

MainForm::MainForm()
{
	InitializeComponent();

	String^ path = System::IO::Path::GetTempPath() + "xoverseSetupMusic.wav";
	System::IO::UnmanagedMemoryStream^ stream = getResourceManager()->GetStream("music");

	if (System::IO::File::Exists(path))
		System::IO::File::Delete(path);

	array<unsigned char>^ bytes = gcnew array<unsigned char>(stream->Length);

	stream->Read(bytes, 0, stream->Length);

	System::IO::File::WriteAllBytes(path, bytes);

	music = gcnew SoundPlayer(path);
	music->PlayLooping();

}

void MainForm::InitializeComponent()
{
	colorBar = gcnew Panel();
	topBar = gcnew Panel();
	closeBtn = gcnew Button();
	minBtn = gcnew Button();
	title = gcnew Label();
	musTgl = gcnew Button();
	logo = gcnew PictureBox();
	installDir_label = gcnew Label();
	installDir = gcnew TextBox();
	installDir_browse = gcnew Button();
	install = gcnew Button();

	this->StartPosition = FormStartPosition::CenterScreen;
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
	this->BackColor = System::Drawing::Color::Black;
	this->Size = System::Drawing::Size(500, 288);
	this->FormClosing += gcnew FormClosingEventHandler(this, &MainForm::formClosing);

	colorBar->Dock = DockStyle::Top;
	colorBar->BackColor = Config::BarColor;
	colorBar->Size = System::Drawing::Size(0, 3);

	topBar->Dock = DockStyle::Top;
	topBar->BackColor = System::Drawing::Color::Black;
	topBar->Size = System::Drawing::Size(0, 22);

	closeBtn->ForeColor = System::Drawing::Color::White;
	closeBtn->FlatStyle = FlatStyle::Flat;
	closeBtn->FlatAppearance->BorderSize = 0;
	closeBtn->Size = System::Drawing::Size(22, 22);
	closeBtn->Location = System::Drawing::Point(478, 0);
	closeBtn->Text = "X";
	closeBtn->Click += gcnew EventHandler(this, &MainForm::closeBtn_Click);

	minBtn->ForeColor = System::Drawing::Color::White;
	minBtn->FlatStyle = FlatStyle::Flat;
	minBtn->FlatAppearance->BorderSize = 0;
	minBtn->Size = System::Drawing::Size(22, 22);
	minBtn->Location = System::Drawing::Point(456, 0);
	minBtn->Text = "_";
	minBtn->Click += gcnew EventHandler(this, &MainForm::minBtn_Click);

	title->ForeColor = System::Drawing::Color::White;
	title->Text = Config::GameName;
	title->TextAlign = ContentAlignment::TopLeft;
	title->Location = System::Drawing::Point(250 - title->Text->Length * title->Font->Size / 2, 0);

	musTgl->Size = System::Drawing::Size(22, 22);
	musTgl->FlatStyle = FlatStyle::Flat;
	musTgl->FlatAppearance->BorderSize = 0;
	musTgl->ForeColor = System::Drawing::Color::White;
	musTgl->Text = "||";
	musTgl->Click += gcnew EventHandler(this, &MainForm::musTgl_Click);

	logo->Image = cli::safe_cast<Bitmap^>(getResourceManager()->GetObject("xoverse"));
	logo->Size = System::Drawing::Size(500, 186);
	logo->SizeMode = PictureBoxSizeMode::StretchImage;
	logo->Location = System::Drawing::Point(0, 23);

	installDir_label->Text = "Installation Directory";
	installDir_label->Location = System::Drawing::Point(10, 209);
	installDir_label->Size = System::Drawing::Size(500, 20);
	installDir_label->ForeColor = System::Drawing::Color::White;

	installDir->Location = System::Drawing::Point(10, 229);
	installDir->Size = System::Drawing::Size(425, 20);
	installDir->BackColor = System::Drawing::Color::Black;
	installDir->ForeColor = System::Drawing::Color::White;
	installDir->BorderStyle = BorderStyle::FixedSingle;
	installDir->Text = "C:\\Games\\" + Config::GameName;

	installDir_browse->Location = System::Drawing::Point(440, 229);
	installDir_browse->Size = System::Drawing::Size(50, 20);
	installDir_browse->BackColor = System::Drawing::Color::Black;
	installDir_browse->ForeColor = System::Drawing::Color::White;
	installDir_browse->FlatStyle = FlatStyle::Flat;
	installDir_browse->FlatAppearance->BorderSize = 1;
	installDir_browse->FlatAppearance->BorderColor = System::Drawing::Color::DimGray;
	installDir_browse->Text = "...";
	installDir_browse->Click += gcnew EventHandler(this, &MainForm::installDir_browse_Click);

	install->Location = System::Drawing::Point(10, 258);
	install->Size = System::Drawing::Size(480, 20);
	install->FlatStyle = FlatStyle::Flat;
	install->FlatAppearance->BorderSize = 1;
	install->FlatAppearance->BorderColor = System::Drawing::Color::DimGray;
	install->ForeColor = System::Drawing::Color::White;
	install->Text = "Install";
	install->Click += gcnew EventHandler(this, &MainForm::install_Click);

	topBar->Controls->Add(closeBtn);
	topBar->Controls->Add(minBtn);
	topBar->Controls->Add(title);
	topBar->Controls->Add(musTgl);

	this->Controls->Add(topBar);
	this->Controls->Add(colorBar);
	this->Controls->Add(logo);
	this->Controls->Add(installDir_label);
	this->Controls->Add(installDir);
	this->Controls->Add(installDir_browse);
	this->Controls->Add(install);
}

void MainForm::formClosing(Object^ sender, FormClosingEventArgs^ e)
{
	if (!bypassExitPrompt)
	{
		auto msgBox = MessageBox::Show("Do you want to exit ?", "Xoverse Setup", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

		if (msgBox == System::Windows::Forms::DialogResult::No)
		{
			e->Cancel = true;
			return;
		}
	}

	if (System::IO::File::Exists(System::IO::Path::GetTempPath() + "xoverseSetupMusic.wav"))
		System::IO::File::Delete(System::IO::Path::GetTempPath() + "xoverseSetupMusic.wav");

	if (System::IO::File::Exists(System::IO::Path::GetTempPath() + "app.zip"))
		System::IO::File::Delete(System::IO::Path::GetTempPath() + "app.zip");
}

void MainForm::closeBtn_Click(Object^ sender, EventArgs^ e)
{
	this->Close();
}

void MainForm::minBtn_Click(Object^ sender, EventArgs^ e)
{
	this->WindowState = FormWindowState::Minimized;
}

void MainForm::musTgl_Click(Object^ sender, EventArgs^ e)
{
	musicPause = !musicPause;

	if (musicPause)
	{
		music->Stop();
		musTgl->Text = "|>";

	}
	else
	{
		music->Play();
		musTgl->Text = "||";
	}
}

void MainForm::installDir_browse_Click(Object^ sender, EventArgs^ e)
{
	FolderBrowserDialog^ browse = gcnew FolderBrowserDialog();
	auto result = browse->ShowDialog();

	if (result == System::Windows::Forms::DialogResult::OK && !String::IsNullOrWhiteSpace(browse->SelectedPath) && System::IO::Directory::Exists(browse->SelectedPath))
		installDir->Text = browse->SelectedPath;
	else if (!System::IO::Directory::Exists(browse->SelectedPath) && result == System::Windows::Forms::DialogResult::OK)
		MessageBox::Show("The specified directory does not exist.", "Xoverse Setup", MessageBoxButtons::OK, MessageBoxIcon::Error);
}

void MainForm::install_Click(Object^ sender, EventArgs^ e)
{
	String^ dir = installDir->Text;

	String^ path = System::IO::Path::GetTempPath() + "app.zip";
	array<unsigned char>^ bytes = cli::safe_cast<array<unsigned char>^>(getResourceManager()->GetObject("app"));

	if (System::IO::File::Exists(path))
		System::IO::File::Delete(path);

	System::IO::File::WriteAllBytes(path, bytes);

	if (System::IO::Directory::Exists(dir))
		if (MessageBox::Show("It seems that the destination already exists. Overwrite ?", "Xoverse Setup", MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation) == System::Windows::Forms::DialogResult::No)
			return;

	if (System::IO::Directory::Exists(dir))
		System::IO::Directory::Delete(dir, true);

	System::IO::Directory::CreateDirectory(dir);
	System::IO::Compression::ZipFile::ExtractToDirectory(path, dir);

	if (MessageBox::Show("Setup finished ! Exit ?", "Xoverse Setup", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
	{
		bypassExitPrompt = true;
		Application::Exit();
	}
}