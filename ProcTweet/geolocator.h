#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Data;
using namespace System::Web;
using namespace System::Net;
using namespace System::Xml;
using namespace System::Diagnostics;
using namespace System::Windows::Forms;
using namespace MSXML2;

namespace ProcTweet {

public ref class NetUserInfo 
{
	private: String^ response; // Raw HTTP response, contains XML
	private: DOMDocument^ XmlResponse;
	public: String^ IP;
	public: String^ Location;

	public: NetUserInfo(void)
		{
			//initialize Object
			//Get net info
			String^ ApiUrl = "http://ipinfodb.com/ip_query.php";
			WebClient^ httpClient = gcnew WebClient();
			try
			{
				this->response = httpClient->DownloadString(ApiUrl);
				this->XmlResponse = gcnew DOMDocument;
				this->XmlResponse->loadXML(this->response);
				String^ r = " ";

				array<String^>^ XmlContent = XmlResponse->text->Split(r->ToCharArray());
				this->IP = XmlContent[0];
				this->Location = XmlContent[6];
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}

		
	// Get the coordinates in a string format "latitude,longitude"
	// Takes a string argument like "New York"
	public: static String^ GetGeoLocationFromGoogle(String^ nearLocation);
};
}
