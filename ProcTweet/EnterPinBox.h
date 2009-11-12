#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace EPB {

	public ref class EnterPinBox : public System::Windows::Forms::Form
	{
	public:
		EnterPinBox(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EnterPinBox()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  bpin;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	
		/// Required method for Designer support - do not modify the contents of this method with the
		/// code editor. 
		/// </summary>
		///
		/// <remarks>	Ogagnon, 2009-10-30. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->bpin = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(4, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(276, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Entrez le PIN que vous allez recevoir dans votre fureteur:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(95, 34);
			this->textBox1->MaxLength = 7;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 1;
			// 
			// bpin
			// 
			this->bpin->Location = System::Drawing::Point(109, 64);
			this->bpin->Name = L"bpin";
			this->bpin->Size = System::Drawing::Size(75, 23);
			this->bpin->TabIndex = 2;
			this->bpin->Text = L"OK";
			this->bpin->UseVisualStyleBackColor = true;
			this->bpin->Click += gcnew System::EventHandler(this, &EnterPinBox::bpin_Click);
			// 
			// EnterPinBox
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 95);
			this->Controls->Add(this->bpin);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Name = L"EnterPinBox";
			this->Text = L"Entrez le PIN";
			this->ResumeLayout(false);
			this->PerformLayout();
			this->ShowDialog();

		}

#pragma endregion

	public: String^ PIN;
	private: System::Void bpin_Click(System::Object^  sender, System::EventArgs^  e);
	
	};
}
