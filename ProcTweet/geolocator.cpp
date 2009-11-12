#include "StdAfx.h"
#include "geolocator.h"


using namespace ProcTweet;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets a geo location from google. </summary>
///
/// <remarks>	Ogagnon, 2009-10-30. </remarks>
///
/// <param name="nearLocation">	[in,out] If non-null, the near location. </param>
///
/// <returns>	null if it fails, else the geo location from google. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

String^ NetUserInfo::GetGeoLocationFromGoogle(String^ nearLocation)
{
	String^ ret;
	String^ longitude;
	String^ latitude;

	String^ apiKey = "ABQIAAAAGVxQZun2X26Yy7IO-574uhQ_6aNsXpkAYqY4oouAQOK55B3a4RS5IlIUAy8n35pNhhMwll4cK1NH7A";
	String^ reqUrl = String::Format("http://maps.google.com/maps/geo?q={0}&output={1}&key={2}",
		HttpUtility::UrlEncode(nearLocation), "csv", apiKey);
	
	WebClient^ httpClient = gcnew WebClient();

	try
	{
		String^ response = httpClient->DownloadString(reqUrl);
		String^ r = ",";
		array<String^>^ values = response->Split(r->ToCharArray());
		if (values->Length == 4)
		{
			if (values[0] == "200")
			{
				latitude = values[2];
				longitude = values[3];

				ret = latitude + "," + longitude;
				return ret;
			}
			else
			{
			   return "Error getting coordinates";
			}
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message);
		return "ERROR!";
	}
}