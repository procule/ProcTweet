using System;
using System.IO;
using System.Configuration;
using System.Drawing;
using System.Net;
using System.Threading;
using System.Web;
using System.Windows.Forms;
using Dimebrain.TweetSharp;
using Dimebrain.TweetSharp.Extensions;
using Dimebrain.TweetSharp.Fluent;
using Dimebrain.TweetSharp.Model;
using EPB;
using System.Xml;
using System.Text.RegularExpressions;
using Dimebrain.TweetSharp.Core.Web;


namespace ProcTweetCsharp
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>   Utilities. </summary>
    ///
    /// <remarks>   Olivier Gagnon, 2009-11-19. </remarks>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    public class Utilities
    {
        private const string HtmlTagPattern = "<.*?>";
        public static string StripHtml(string inputString)
        {
            return Regex.Replace(inputString, HtmlTagPattern, string.Empty);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Information about the net user. </summary>
        ///
        /// <remarks>   Olivier Gagnon, 2009-11-19. </remarks>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public class NetUserInfo
        {
            string response; // Raw HTTP response, contains XML
            private XmlDocument _xmlreponse;
            public string IP;
            public string Location;

            public NetUserInfo()
            {
                //initialize Object
                //Get net info
                const string apiUrl = "http://ipinfodb.com/ip_query.php";
                var httpClient = new WebClient();
                try
                {
                    response = httpClient.DownloadString(apiUrl);
                    _xmlreponse = new XmlDocument();
                    _xmlreponse.LoadXml(response);

                    IP = _xmlreponse.SelectSingleNode("/Response/Ip").InnerText;
                    Location = _xmlreponse.SelectSingleNode("/Response/City").InnerText;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////////
            /// <summary>   Gets a geo location from google. </summary>
            ///
            /// <remarks>   Olivier Gagnon, 2009-11-19. </remarks>
            ///
            /// <param name="nearLocation"> The near location. </param>
            ///
            /// <returns>   The geo location from google. </returns>
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            public static string GetGeoLocationFromGoogle(string nearLocation)
            {
                string ret;
                string longitude;
                string latitude;

                string apiKey = "ABQIAAAAGVxQZun2X26Yy7IO-574uhQ_6aNsXpkAYqY4oouAQOK55B3a4RS5IlIUAy8n35pNhhMwll4cK1NH7A";
                string reqUrl = String.Format("http://maps.google.com/maps/geo?q={0}&output={1}&key={2}",
                                              HttpUtility.UrlEncode(nearLocation), "csv", apiKey);

                var httpClient = new WebClient();

                try
                {
                    var resp = httpClient.DownloadString(reqUrl);
                    string r = ",";
                    var values = resp.Split(r.ToCharArray());
                    if (values.Length == 4)
                    {
                        if (values[0] == "200")
                        {
                            latitude = values[2];
                            longitude = values[3];

                            ret = latitude + "," + longitude;
                            return ret;
                        }
                            return "Error getting coordinates";
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                    return "ERROR!";
                }
                return "Error getting coordinates";
            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Gets an authorisation token and puts it in the configuration file. </summary>
        ///
        /// <remarks>   Olivier Gagnon, 2009-11-13. </remarks>
        ///
        /// <param name="logininfo">    The login informations. </param>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public static void GetAuthToken(LoginInfo logininfo)
        {
            Configuration oConfig = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
            IFluentTwitter tf = FluentTwitter.CreateRequest(logininfo.TcInfo);

            tf.Configuration.UseUrlShortening(ShortenUrlServiceProvider.TinyUrl);

            OAuthToken rtoken = tf.Authentication.GetRequestToken(logininfo.TcInfo.ConsumerKey, logininfo.TcInfo.ConsumerSecret).Request().AsToken();

            tf.Authentication.AuthorizeDesktop(rtoken.Token);

            var epb = new EnterPinBox();
            logininfo.Authtoken =
                tf.Authentication.GetAccessToken(logininfo.TcInfo.ConsumerKey, logininfo.TcInfo.ConsumerSecret, rtoken.Token,
                                                 (string)epb.PIN).Request().AsToken();
            oConfig.AppSettings.Settings.Remove("atoken");
            oConfig.AppSettings.Settings.Add("atoken", logininfo.Authtoken.Token);
            oConfig.AppSettings.Settings.Remove("atokens");
            oConfig.AppSettings.Settings.Add("atokens", logininfo.Authtoken.TokenSecret);
            oConfig.Save();
            logininfo.IsLogged = true;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Verify twitter credentials. </summary>
        ///
        /// <remarks>   Olivier Gagnon, 2009-11-04. </remarks>
        ///
        /// <param name="username"> The username. </param>
        /// <param name="password"> The password. </param>
        ///
        /// <returns>   true if it succeeds, false if it fails. </returns>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public static bool VerifyTwitterCredentials(string username, string password)
        {
            var twitter = FluentTwitter.CreateRequest()
                .AuthenticateAs(username, password)
                .Account().VerifyCredentials().AsJson().Request();
            
            var response = twitter.AsUser();
            if (response == null)
            {
                MessageBox.Show("Authentication failed", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            return true;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>   Information about the account. </summary>
    ///
    /// <remarks>   Olivier Gagnon, 2009-11-11. </remarks>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    public class AccountInfo
    {
        //Properties
        public string Username { get; set; }
        public string Name { get; set; }
        public string Bio { get; set; }
        /// <summary>
        /// Profile background image URI
        /// </summary>
        public string Background { get; set; }

        /// <summary>Constructor</summary>
        public AccountInfo(string username)
        {
            Username = username;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Gets a twitter account information. </summary>
        ///
        /// <remarks>   Olivier Gagnon, 2009-11-04. </remarks>
        ///
        /// <param name="username"> The username. </param>
        ///
        /// <returns>   The twitter account information. </returns>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public static AccountInfo GetTwitterAccountInfo(string username)
        {
            var ac = new AccountInfo(username);
            var request = FluentTwitter.CreateRequest()
                .Users().ShowProfileFor(username).AsJson().Request();
            var response = request.AsUser();

            ac.Name = response.Name;
            ac.Bio = response.Description;
            ac.Background = response.ProfileBackgroundImageUrl;

            return ac;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>   Information about the login. </summary>
    ///
    /// <remarks>   Olivier Gagnon, 2009-11-18. </remarks>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    public class LoginInfo
    {
        public LoginInfo()
        {
            IsLogged = false;
            Username = "";
        }

        public bool IsLogged { get; set; }
        public string Username { get; set; }
        public string Password { get; set; }
        public TwitterClientInfo TcInfo { get; set; }
        public OAuthToken Authtoken { get; set; }

    }

}