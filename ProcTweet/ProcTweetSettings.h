#pragma once

#include "geolocator.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Configuration;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace ProcTweet {

	/// <summary>
	/// Summary for ProcTweetSettings
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>

	public ref class ProcTweetSettings : public System::Windows::Forms::Form
	{
	public:
		ProcTweetSettings(void)
		{
			
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			tsuser->Text = ConfigurationManager::AppSettings["username"];
			tspassword->Text = ConfigurationManager::AppSettings["password"];
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ProcTweetSettings()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox1;
	public: System::Windows::Forms::TextBox^  tspassword;
	public: System::Configuration::ConfigurationManager^ oConfig;
	private: System::Windows::Forms::Label^  label2;
	public: System::Windows::Forms::TextBox^  tsuser;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  bsetuser;
	private: System::Windows::Forms::GroupBox^  groupBox2;

	private: System::Windows::Forms::Label^  lville;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  bsave;

	private: System::Windows::Forms::LinkLabel^  lcoords;
	private: System::Windows::Forms::CheckBox^  cbgeolocation;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  lname;
	private: System::Windows::Forms::Label^  lbio;
	private: System::ComponentModel::IContainer^  components;
	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->bsetuser = (gcnew System::Windows::Forms::Button());
			this->tspassword = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tsuser = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->lname = (gcnew System::Windows::Forms::Label());
			this->lbio = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->cbgeolocation = (gcnew System::Windows::Forms::CheckBox());
			this->lcoords = (gcnew System::Windows::Forms::LinkLabel());
			this->lville = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->bsave = (gcnew System::Windows::Forms::Button());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->bsetuser);
			this->groupBox1->Controls->Add(this->tspassword);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->tsuser);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(13, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(268, 120);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Account";
			// 
			// bsetuser
			// 
			this->bsetuser->Location = System::Drawing::Point(97, 82);
			this->bsetuser->Name = L"bsetuser";
			this->bsetuser->Size = System::Drawing::Size(75, 23);
			this->bsetuser->TabIndex = 4;
			this->bsetuser->Tag = this;
			this->bsetuser->Text = L"Verify";
			this->bsetuser->UseVisualStyleBackColor = true;
			this->bsetuser->Click += gcnew System::EventHandler(this, &ProcTweetSettings::bsetuser_Click);
			// 
			// tspassword
			// 
			this->tspassword->Location = System::Drawing::Point(115, 48);
			this->tspassword->Name = L"tspassword";
			this->tspassword->Size = System::Drawing::Size(100, 20);
			this->tspassword->TabIndex = 3;
			this->tspassword->UseSystemPasswordChar = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(54, 48);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(56, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Password:";
			// 
			// tsuser
			// 
			this->tsuser->Location = System::Drawing::Point(115, 18);
			this->tsuser->Name = L"tsuser";
			this->tsuser->Size = System::Drawing::Size(100, 20);
			this->tsuser->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(51, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Username:";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->lname);
			this->groupBox2->Controls->Add(this->lbio);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->cbgeolocation);
			this->groupBox2->Controls->Add(this->lcoords);
			this->groupBox2->Controls->Add(this->lville);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Location = System::Drawing::Point(13, 138);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(268, 195);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Informations";
			// 
			// lname
			// 
			this->lname->AutoSize = true;
			this->lname->Location = System::Drawing::Point(98, 103);
			this->lname->Name = L"lname";
			this->lname->Size = System::Drawing::Size(0, 13);
			this->lname->TabIndex = 10;
			// 
			// lbio
			// 
			this->lbio->Location = System::Drawing::Point(98, 132);
			this->lbio->Name = L"lbio";
			this->lbio->Size = System::Drawing::Size(164, 60);
			this->lbio->TabIndex = 9;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(22, 132);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(25, 13);
			this->label6->TabIndex = 8;
			this->label6->Text = L"Bio:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(22, 103);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(38, 13);
			this->label5->TabIndex = 7;
			this->label5->Text = L"Name:";
			// 
			// cbgeolocation
			// 
			this->cbgeolocation->AutoSize = true;
			this->cbgeolocation->Enabled = false;
			this->cbgeolocation->Location = System::Drawing::Point(75, 71);
			this->cbgeolocation->Name = L"cbgeolocation";
			this->cbgeolocation->Size = System::Drawing::Size(119, 17);
			this->cbgeolocation->TabIndex = 6;
			this->cbgeolocation->Text = L"Enable Geolocation";
			this->toolTip1->SetToolTip(this->cbgeolocation, L"Enable the sending of your geographic location to Twitter");
			this->cbgeolocation->UseVisualStyleBackColor = true;
			// 
			// lcoords
			// 
			this->lcoords->AutoSize = true;
			this->lcoords->Location = System::Drawing::Point(98, 46);
			this->lcoords->Name = L"lcoords";
			this->lcoords->Size = System::Drawing::Size(0, 13);
			this->lcoords->TabIndex = 5;
			this->lcoords->VisitedLinkColor = System::Drawing::Color::Blue;
			this->lcoords->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &ProcTweetSettings::lcoords_LinkClicked);
			// 
			// lville
			// 
			this->lville->AutoSize = true;
			this->lville->Location = System::Drawing::Point(98, 20);
			this->lville->Name = L"lville";
			this->lville->Size = System::Drawing::Size(0, 13);
			this->lville->TabIndex = 2;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(22, 46);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(73, 13);
			this->label4->TabIndex = 1;
			this->label4->Text = L"Coordonnées:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(22, 20);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(29, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Ville:";
			// 
			// bsave
			// 
			this->bsave->Enabled = false;
			this->bsave->Location = System::Drawing::Point(110, 343);
			this->bsave->Name = L"bsave";
			this->bsave->Size = System::Drawing::Size(75, 23);
			this->bsave->TabIndex = 4;
			this->bsave->Tag = this;
			this->bsave->Text = L"Save";
			this->bsave->UseCompatibleTextRendering = true;
			this->bsave->UseVisualStyleBackColor = true;
			this->bsave->Click += gcnew System::EventHandler(this, &ProcTweetSettings::bsave_Click);
			// 
			// ProcTweetSettings
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(294, 374);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->bsave);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"ProcTweetSettings";
			this->Text = L"Settings";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &ProcTweetSettings::ProcTweetSettings_FormClosed);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void bsetuser_Click(System::Object^  sender, System::EventArgs^  e);	
private: System::Void ProcTweetSettings_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
private: System::Void lcoords_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e);
private: System::Void bsave_Click(System::Object^  sender, System::EventArgs^  e);
};
}
