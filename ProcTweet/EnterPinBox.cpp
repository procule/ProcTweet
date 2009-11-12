#include "StdAfx.h"
#include "EnterPinBox.h"

using namespace EPB;

System::Void EnterPinBox::bpin_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if(EnterPinBox::textBox1->Text->Length != 7)
	{
		MessageBox::Show(L"PIN incorrect", L"PIN", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}
	else
	{
		EnterPinBox::PIN = EnterPinBox::textBox1->Text;
		EnterPinBox::Hide();
	}
}