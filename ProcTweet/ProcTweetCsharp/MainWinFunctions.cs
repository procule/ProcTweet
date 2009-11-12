using System;
using System.Configuration;
using System.Drawing;
using System.Net;
using System.Web;
using System.Windows.Forms;
using Dimebrain.TweetSharp;
using Dimebrain.TweetSharp.Extensions;
using Dimebrain.TweetSharp.Fluent;
using Dimebrain.TweetSharp.Model;
using EPB;
using MSXML;

namespace ProcTweetCsharp
{
    public class MainWinFunctions
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Refresh status. </summary>
        ///
        /// <remarks>   Olivier Gagnon, 2009-11-10. </remarks>
        ///
        /// <param name="currenttweet"> The currenttweet. </param>
        /// <param name="llaccount">    The llaccount. </param>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public static void RefreshStatus(Tweet currenttweet, string llaccount)
        {
            TwitterUser profile;

            try
            {
                currenttweet.TweetText.Text = "Allons chercher votre status.......";
                currenttweet.TweetText.Update();
                profile =
                    FluentTwitter.CreateRequest().Users().ShowProfileFor(llaccount).AsJson().Request().AsUser();

                currenttweet.TweetImage.Load(profile.ProfileImageUrl);
                currenttweet.TweetText.Font =
                    (new Font("Microsoft Sans Serif", 8.25F, FontStyle.Regular, GraphicsUnit.Point, Byte.Parse("0")));
                currenttweet.TweetText.Text = profile.Status.Text;
                currenttweet.ltimeago.Text = profile.Status.CreatedDate.ToRelativeTime();
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, "Erreur !", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Send tweet. </summary>
        ///
        /// <remarks>   Olivier Gagnon, 2009-11-11. </remarks>
        ///
        /// <param name="currenttweet"> The currenttweet control. </param>
        /// <param name="llaccount">    The account. </param>
        /// <param name="tweetbox">     The tweetbox control. </param>
        /// <param name="tcInfo">       Information describing the Twitter client. </param>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public static void SendTweet(Tweet currenttweet, string llaccount, TextBox tweetbox, TwitterClientInfo tcInfo)
        {
            try
            {
                Configuration oConfig = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
                IFluentTwitter tf = FluentTwitter.CreateRequest(tcInfo);
                OAuthToken rtoken;
                OAuthToken atoken;

                if (ConfigurationManager.AppSettings["atoken"] == "")
                {
                    tf.Configuration.UseUrlShortening(ShortenUrlServiceProvider.TinyUrl);

                    rtoken =
                        tf.Authentication.GetRequestToken(tcInfo.ConsumerKey, tcInfo.ConsumerSecret).Request().AsToken();

                    tf.Authentication.AuthorizeDesktop(rtoken.Token);

                    var epb = new EnterPinBox();
                    atoken =
                        tf.Authentication.GetAccessToken(tcInfo.ConsumerKey, tcInfo.ConsumerSecret, rtoken.Token,
                                                         (string) epb.PIN).Request().AsToken();
                    oConfig.AppSettings.Settings.Remove("atoken");
                    oConfig.AppSettings.Settings.Add("atoken", atoken.Token);
                    oConfig.AppSettings.Settings.Remove("atokens");
                    oConfig.AppSettings.Settings.Add("atokens", atoken.TokenSecret);
                    oConfig.Save();
                }
                else
                {
                    atoken = new OAuthToken
                                 {
                                     Token = ConfigurationManager.AppSettings["atoken"],
                                     TokenSecret = ConfigurationManager.AppSettings["atokens"]
                                 };
                }

                string request =
                    tf.AuthenticateWith(atoken.Token, atoken.TokenSecret).Statuses().Update(tweetbox.Text).AsJson().
                        Request();

                RefreshStatus(currenttweet, llaccount);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, "Erreur lors de l'envoi du TWEET", MessageBoxButtons.OK,
                                MessageBoxIcon.Exclamation);
            }
        }
    }

    public class NetUserInfo
    {
        private string[] _xmlContent;

        public NetUserInfo()
        {
            //initialize Object
            //Get net info
            const string apiUrl = "http://ipinfodb.com/ip_query.php";
            var httpClient = new WebClient();
            try
            {
                string response = httpClient.DownloadString(apiUrl);
                var xmlResponse = new DOMDocument();
                xmlResponse.loadXML(response);
                const string r = " ";

                _xmlContent = xmlResponse.text.Split(r.ToCharArray());
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Gets a geo location from google. </summary>
        ///
        /// <remarks>   Olivier Gagnon, 2009-11-11. </remarks>
        ///
        /// <param name="nearLocation"> The location. </param>
        ///
        /// <returns>   The geo location (coordinates) from google. </returns>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public static string GetGeoLocationFromGoogle(String nearLocation)
        {
            const string apiKey =
                "ABQIAAAAGVxQZun2X26Yy7IO-574uhQ_6aNsXpkAYqY4oouAQOK55B3a4RS5IlIUAy8n35pNhhMwll4cK1NH7A";
            string reqUrl = String.Format("http://maps.google.com/maps/geo?q={0}&output={1}&key={2}",
                                          HttpUtility.UrlEncode(nearLocation), "csv", apiKey);

            var httpClient = new WebClient();

            try
            {
                string response = httpClient.DownloadString(reqUrl);
                const string r = ",";
                string[] values = response.Split(r.ToCharArray());
                if (values.Length == 4)
                {
                    if (values[0] == "200")
                    {
                        string latitude = values[2];
                        string longitude = values[3];

                        string ret = latitude + "," + longitude;
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
            return "";
        }
    }
}