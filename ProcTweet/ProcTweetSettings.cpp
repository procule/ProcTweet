#include "StdAfx.h"
#include "MainWin.h"
#include "ProcTweetSettings.h"

using namespace ProcTweet;

System::Void ProcTweetSettings::ProcTweetSettings_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) 
{
	ProcTweetSettings^ PTSForm = (ProcTweetSettings^) sender;
	MainWin^ MW = (MainWin^) PTSForm->Owner;
	MW->llaccount->Text = PTSForm->tsuser->Text;
}

System::Void ProcTweetSettings::bsave_Click(System::Object^  sender, System::EventArgs^  e)
{
	ProcTweetSettings^ PTSForm = (ProcTweetSettings^) (((System::Windows::Forms::Control^)(((System::Windows::Forms::ButtonBase^)(((System::Windows::Forms::Button^)(sender)))))))->Tag;

	System::Configuration::Configuration^ oConfig;
	oConfig = ConfigurationManager::OpenExeConfiguration(ConfigurationUserLevel::None);
	oConfig->AppSettings->Settings->Remove("username");
	oConfig->AppSettings->Settings->Add("username", PTSForm->tsuser->Text);
	oConfig->AppSettings->Settings->Remove("password");
	oConfig->AppSettings->Settings->Add("password", PTSForm->tspassword->Text);
	oConfig->AppSettings->Settings->Remove("geolocation");
	if (PTSForm->cbgeolocation->Checked)
		oConfig->AppSettings->Settings->Add("geolocation", "1");
	else
		oConfig->AppSettings->Settings->Add("geolocation", "0");
	oConfig->Save();

	PTSForm->Close();

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Bsetuser click. </summary>
///
/// <remarks>	Ogagnon, 2009-10-30. </remarks>
///
/// <param name="sender">	[in,out] If non-null, the sender. </param>
/// <param name="e">		[in,out] If non-null, the. </param>
///
/// <returns>	. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

System::Void ProcTweetSettings::bsetuser_Click(System::Object^  sender, System::EventArgs^  e)
{
	ProcTweetSettings^ PTSForm = (ProcTweetSettings^) (((System::Windows::Forms::Control^)(((System::Windows::Forms::ButtonBase^)(((System::Windows::Forms::Button^)(sender)))))))->Tag;
	MainWin^ MW = (MainWin^) PTSForm->Owner;
	String^ username = PTSForm->tsuser->Text;
	String^ password = PTSForm->tspassword->Text;

	if (username == "" || password == "")
		MessageBox::Show("Entre tes infos calisse !", "Maudit juif...", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	else
	{
		try
		{
			if (!(ProcTweetCsharp::Utilities::VerifyTwitterCredentials(PTSForm->tsuser->Text, PTSForm->tspassword->Text)))
				return;

			PTSForm->tsuser->Enabled = false;
			PTSForm->tspassword->Enabled = false;
			PTSForm->bsetuser->Enabled = false;

			MW->logininfo->Username = PTSForm->tsuser->Text;
			MW->logininfo->Password = PTSForm->tspassword->Text;
			
			if (MW->logininfo->Authtoken->TokenSecret == nullptr)
				ProcTweetCsharp::Utilities::GetAuthToken(MW->logininfo);

			NetUserInfo^ UNI = gcnew NetUserInfo;
			PTSForm->lville->Text = UNI->Location;
			PTSForm->lcoords->Text = NetUserInfo::GetGeoLocationFromGoogle(UNI->Location);

			ProcTweetCsharp::AccountInfo^ ac = ProcTweetCsharp::AccountInfo::GetTwitterAccountInfo(PTSForm->tsuser->Text);
			PTSForm->lname->Text = ac->Name;
			PTSForm->lbio->Text = ac->Bio;
			PTSForm->toolTip1->SetToolTip(PTSForm->lbio, PTSForm->lbio->Text);
			if (ConfigurationManager::AppSettings["geolocation"])
				PTSForm->cbgeolocation->Checked = true;
			PTSForm->cbgeolocation->Enabled = true;
			PTSForm->bsave->Enabled = true;
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->Message);
		}
	}
}

System::Void ProcTweetSettings::lcoords_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) 
{
		LinkLabel^ lcoords = (LinkLabel^)sender;
		String^ link = "http://maps.google.com/maps?f=q&source=proctweet&z=12&q=" + HttpUtility::UrlEncode(lcoords->Text);
		System::Diagnostics::Process::Start(link);
}


