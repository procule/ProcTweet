#pragma once

#include "geolocator.h"
#include "ProcTweetSettings.h"

namespace ProcTweet {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Configuration;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace System::Net;
	using namespace System::Threading;
	using namespace Dimebrain::TweetSharp::Model;
	using namespace Dimebrain::TweetSharp::Fluent;
	using namespace Dimebrain::TweetSharp::Extensions;
	using namespace ProcTweetCsharp;
	using namespace System::Globalization;

#define NCHAR 140

	/// <summary>
	/// Summary for MainWin
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	
	public ref class MainWin : public System::Windows::Forms::Form
	{
	public:
		MainWin(void)
		{
			InitializeComponent();

			oConfig = ConfigurationManager::OpenExeConfiguration(ConfigurationUserLevel::None);

			tcInfo = gcnew Dimebrain::TweetSharp::TwitterClientInfo;
            tcInfo->ClientName = "ProcTweet";
            tcInfo->ClientVersion = "0.2";
            tcInfo->ClientUrl = "http://code.google.com/p/proctweet";
            tcInfo->ConsumerKey = "5bNCGHgcKT53UFAisxj3lg";
            tcInfo->ConsumerSecret = "F7v9jw1nF0bPhFFS83WQan8xDVSurg0OaFAGabrJc";

			this->logininfo = gcnew LoginInfo();
			this->logininfo->Authtoken = gcnew OAuthToken;
			this->logininfo->TcInfo = tcInfo;

			if (ConfigurationManager::AppSettings["username"] != nullptr)
			{
				this->logininfo->Username = ConfigurationManager::AppSettings["username"];
				this->logininfo->Password = ConfigurationManager::AppSettings["password"];
				this->logininfo->Authtoken->Token = ConfigurationManager::AppSettings["atoken"];
				this->logininfo->Authtoken->TokenSecret = ConfigurationManager::AppSettings["atokens"];
				if (this->logininfo->Authtoken->Token != nullptr && this->logininfo->Authtoken->TokenSecret != nullptr &&
					this->logininfo->Password != nullptr)
				{
					this->logininfo->IsLogged = true;
					this->tweetsFromFriendsToolStripMenuItem->Enabled = true;
				}
				this->llaccount->Text = ConfigurationManager::AppSettings["username"];
			}
		}
	public: Dimebrain::TweetSharp::TwitterClientInfo^ tcInfo;
	public: LoginInfo^ logininfo;
	public: System::Windows::Forms::LinkLabel^  llaccount;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ToolStripMenuItem^  lastToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  tweetsFromFriendsToolStripMenuItem;
	private: ProcTweetCsharp::Tweet^  currenttweet;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusRem;
	private: System::Windows::Forms::ToolStripMenuItem^  mentionsToolStripMenuItem;
	private: OAuthToken^ authtoken;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWin()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Configuration::Configuration^ oConfig;
	private: System::Windows::Forms::MenuStrip^  MProcTweet;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  FileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  FileSettingsStripMenuItem;
	private: System::Windows::Forms::StatusStrip^  sstatus;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  tweetbox;
	private: System::Windows::Forms::Label^  ncharlabel;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::Button^  sendbutton;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWin::typeid));
			this->MProcTweet = (gcnew System::Windows::Forms::MenuStrip());
			this->FileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FileSettingsStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lastToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tweetsFromFriendsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mentionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sstatus = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusRem = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->tweetbox = (gcnew System::Windows::Forms::TextBox());
			this->ncharlabel = (gcnew System::Windows::Forms::Label());
			this->sendbutton = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->currenttweet = (gcnew ProcTweetCsharp::Tweet());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->llaccount = (gcnew System::Windows::Forms::LinkLabel());
			this->MProcTweet->SuspendLayout();
			this->sstatus->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// MProcTweet
			// 
			this->MProcTweet->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->FileToolStripMenuItem, 
				this->aboutToolStripMenuItem, this->lastToolStripMenuItem});
			this->MProcTweet->Location = System::Drawing::Point(0, 0);
			this->MProcTweet->Name = L"MProcTweet";
			this->MProcTweet->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->MProcTweet->Size = System::Drawing::Size(326, 24);
			this->MProcTweet->TabIndex = 0;
			// 
			// FileToolStripMenuItem
			// 
			this->FileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->FileSettingsStripMenuItem});
			this->FileToolStripMenuItem->Name = L"FileToolStripMenuItem";
			this->FileToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->FileToolStripMenuItem->Text = L"File";
			// 
			// FileSettingsStripMenuItem
			// 
			this->FileSettingsStripMenuItem->Name = L"FileSettingsStripMenuItem";
			this->FileSettingsStripMenuItem->Size = System::Drawing::Size(135, 22);
			this->FileSettingsStripMenuItem->Text = L"Settings";
			this->FileSettingsStripMenuItem->Click += gcnew System::EventHandler(this, &MainWin::FileSettingsStripMenuItem_Click);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(53, 20);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWin::aboutToolStripMenuItem_Click);
			// 
			// lastToolStripMenuItem
			// 
			this->lastToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->tweetsFromFriendsToolStripMenuItem, 
				this->mentionsToolStripMenuItem});
			this->lastToolStripMenuItem->Name = L"lastToolStripMenuItem";
			this->lastToolStripMenuItem->Size = System::Drawing::Size(43, 20);
			this->lastToolStripMenuItem->Text = L"Last";
			this->lastToolStripMenuItem->DropDownOpening += gcnew System::EventHandler(this, &MainWin::lastToolStripMenuItem_DropDownOpening);
			// 
			// tweetsFromFriendsToolStripMenuItem
			// 
			this->tweetsFromFriendsToolStripMenuItem->Enabled = false;
			this->tweetsFromFriendsToolStripMenuItem->Name = L"tweetsFromFriendsToolStripMenuItem";
			this->tweetsFromFriendsToolStripMenuItem->Size = System::Drawing::Size(219, 22);
			this->tweetsFromFriendsToolStripMenuItem->Text = L"25 tweets from friends";
			this->tweetsFromFriendsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWin::tweetsFromFriendsToolStripMenuItem_Click);
			// 
			// mentionsToolStripMenuItem
			// 
			this->mentionsToolStripMenuItem->Enabled = false;
			this->mentionsToolStripMenuItem->Name = L"mentionsToolStripMenuItem";
			this->mentionsToolStripMenuItem->Size = System::Drawing::Size(219, 22);
			this->mentionsToolStripMenuItem->Text = L"Mentions";
			this->mentionsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWin::mentionsToolStripMenuItem_Click);
			// 
			// sstatus
			// 
			this->sstatus->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripStatusLabel1, 
				this->toolStripStatusRem});
			this->sstatus->Location = System::Drawing::Point(0, 362);
			this->sstatus->Name = L"sstatus";
			this->sstatus->RenderMode = System::Windows::Forms::ToolStripRenderMode::ManagerRenderMode;
			this->sstatus->Size = System::Drawing::Size(326, 22);
			this->sstatus->TabIndex = 1;
			this->sstatus->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(106, 17);
			this->toolStripStatusLabel1->Text = L"Ready to Tweet !";
			// 
			// toolStripStatusRem
			// 
			this->toolStripStatusRem->Name = L"toolStripStatusRem";
			this->toolStripStatusRem->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->toolStripStatusRem->Size = System::Drawing::Size(0, 17);
			this->toolStripStatusRem->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->tweetbox);
			this->groupBox1->Location = System::Drawing::Point(27, 75);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(268, 100);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Enter your tweet message !";
			// 
			// tweetbox
			// 
			this->tweetbox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tweetbox->Location = System::Drawing::Point(6, 15);
			this->tweetbox->MaxLength = 140;
			this->tweetbox->Multiline = true;
			this->tweetbox->Name = L"tweetbox";
			this->tweetbox->Size = System::Drawing::Size(256, 79);
			this->tweetbox->TabIndex = 8;
			this->tweetbox->TextChanged += gcnew System::EventHandler(this, &MainWin::tweetbox_TextChanged);
			// 
			// ncharlabel
			// 
			this->ncharlabel->AutoSize = true;
			this->ncharlabel->Font = (gcnew System::Drawing::Font(L"Lucida Sans Unicode", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ncharlabel->Location = System::Drawing::Point(254, 178);
			this->ncharlabel->Name = L"ncharlabel";
			this->ncharlabel->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->ncharlabel->Size = System::Drawing::Size(35, 16);
			this->ncharlabel->TabIndex = 3;
			this->ncharlabel->Text = L"140";
			// 
			// sendbutton
			// 
			this->sendbutton->Location = System::Drawing::Point(76, 197);
			this->sendbutton->Name = L"sendbutton";
			this->sendbutton->Size = System::Drawing::Size(75, 23);
			this->sendbutton->TabIndex = 9;
			this->sendbutton->Text = L"Send Tweet";
			this->sendbutton->UseVisualStyleBackColor = true;
			this->sendbutton->Click += gcnew System::EventHandler(this, &MainWin::sendbutton_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->currenttweet);
			this->groupBox2->Location = System::Drawing::Point(12, 231);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(300, 116);
			this->groupBox2->TabIndex = 10;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Your status";
			// 
			// currenttweet
			// 
			this->currenttweet->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->currenttweet->Location = System::Drawing::Point(2, 11);
			this->currenttweet->Name = L"currenttweet";
			this->currenttweet->Size = System::Drawing::Size(286, 99);
			this->currenttweet->TabIndex = 0;
			this->currenttweet->Load += gcnew System::EventHandler(this, &MainWin::currenttweet_Load);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(25, 40);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(137, 20);
			this->label1->TabIndex = 12;
			this->label1->Text = L"Twitter account:";
			// 
			// llaccount
			// 
			this->llaccount->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->llaccount->Location = System::Drawing::Point(161, 40);
			this->llaccount->Name = L"llaccount";
			this->llaccount->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->llaccount->Size = System::Drawing::Size(134, 20);
			this->llaccount->TabIndex = 13;
			this->llaccount->VisitedLinkColor = System::Drawing::Color::Blue;
			this->llaccount->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainWin::llaccount_LinkClicked);
			// 
			// MainWin
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(326, 384);
			this->Controls->Add(this->llaccount);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->sendbutton);
			this->Controls->Add(this->ncharlabel);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->sstatus);
			this->Controls->Add(this->MProcTweet);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->MProcTweet;
			this->MaximizeBox = false;
			this->Name = L"MainWin";
			this->Text = L"ProcTweet";
			this->Click += gcnew System::EventHandler(this, &MainWin::tweetsFromFriendsToolStripMenuItem_Click);
			this->MProcTweet->ResumeLayout(false);
			this->MProcTweet->PerformLayout();
			this->sstatus->ResumeLayout(false);
			this->sstatus->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void tweetbox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			this->ncharlabel->Text = (140 - this->tweetbox->Text->Length).ToString();
		}
	
	private: System::Void sendbutton_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if (logininfo->IsLogged)
			ProcTweetCsharp::MainWinFunctions::SendTweet(this->currenttweet, this->logininfo, this->tweetbox);
		else
			MessageBox::Show("Your account is not configured. Go to File/Settings and verify your credentials.", "Not logged",
				MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void FileSettingsStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 ProcTweetSettings^ PTSettings = gcnew ProcTweetSettings;
			 PTSettings->ShowDialog(this);
		 }
	private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 AboutBox^ AboutBox1 = gcnew AboutBox;
			 AboutBox1->ShowDialog();
		 }
	private: System::Void llaccount_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) 
		 {
			 LinkLabel^ llaccount = (LinkLabel^)sender;
			 String^ link = "http://twitter.com/" + HttpUtility::UrlEncode(llaccount->Text);
			 System::Diagnostics::Process::Start(link);
		 }
	private: System::Void tweetsFromFriendsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		{	
			Thread^ t = gcnew Thread(gcnew ParameterizedThreadStart(ProcTweetCsharp::Requests::GetLastFriendsTweets));
			t->Name = "TweetWin Friends";
			t->IsBackground = true;
			t->Start(this->logininfo);
		}

	private: System::Void currenttweet_Load(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (logininfo->IsLogged)
			 {
				try
				{
					ProcTweetCsharp::MainWinFunctions::RefreshStatus(this->currenttweet, this->logininfo);
				}
				catch (Exception^ E)
				{
					MessageBox::Show(E->Message+" "+ E->StackTrace, "Error !", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}
			 }
		 }
private: System::Void lastToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (logininfo->IsLogged)
			 {
				 this->tweetsFromFriendsToolStripMenuItem->Enabled = true;
				 this->mentionsToolStripMenuItem->Enabled = true;
			 }
		 }
private: System::Void mentionsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			Thread^ t = gcnew Thread(gcnew ParameterizedThreadStart(ProcTweetCsharp::Requests::GetMentions));
			t->Name = "TweetWin Mentions";
			t->IsBackground = true;
			t->Start(this->logininfo);
		 }
};
}

