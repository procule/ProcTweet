using System;
using System.Configuration;
using System.Drawing;
using System.Net;
using System.Text;
using System.Web;
using System.Xml;
using System.Windows.Forms;
using Dimebrain.TweetSharp;
using Dimebrain.TweetSharp.Extensions;
using Dimebrain.TweetSharp.Fluent;
using Dimebrain.TweetSharp.Model;
using MSXML;
using EPB;
using System.Text.RegularExpressions;


namespace ProcTweetCsharp
{
    public class Utilities
    {
        private const string HtmlTagPattern = "<.*?>";
        private static string StripHtml(string inputString)
        {
            return Regex.Replace(inputString, HtmlTagPattern, string.Empty);
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
            var xmldoc = new DOMDocument();

            ITwitterLeafNode twitter = FluentTwitter.CreateRequest()
                .AuthenticateAs(username, password)
                .Account().VerifyCredentials().AsXml();
            string xmlresponse = twitter.Request();

            xmldoc.loadXML(xmlresponse);
            IXMLDOMNodeList xmlnode = xmldoc.documentElement.getElementsByTagName("error");

            if (xmlnode.length == 1)
            {
                MessageBox.Show("Authentication failed", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            return true;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Gets the last friends tweets. </summary>
        ///
        /// <remarks>   Olivier Gagnon, 2009-11-09. </remarks>
        ///
        /// <param name="numberOfTweets">   Number of tweets. </param>
        /// <param name="logininfo">        The login informations. </param>
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        public static void GetLastFriendsTweets(int numberOfTweets, LoginInfo logininfo)
        {
            var tweetWin = new TweetWin();
            var ac = AccountInfo.GetTwitterAccountInfo(logininfo.Username);

            // Set background image from twitter
            var uri = new Uri(ac.Background);
            System.IO.Stream s =
                WebRequest.Create(uri)
                .GetResponse().GetResponseStream();
            Image backimg = Image.FromStream(s);

            tweetWin.TweetPanel.BackgroundImage = backimg;
            tweetWin.TweetPanel.BackColor = Color.Transparent;

            string twitter = FluentTwitter.CreateRequest()
                .AuthenticateWith(logininfo.TcInfo.ConsumerKey, logininfo.TcInfo.ConsumerSecret, logininfo.Authtoken.Token, logininfo.Authtoken.TokenSecret)
                .Statuses().OnFriendsTimeline().Take(numberOfTweets).AsXml().Request();

            var xmldoc = new XmlDocument();
            xmldoc.LoadXml(twitter);

            var nodeList = xmldoc.SelectNodes("/statuses/status");
            if (nodeList != null)
            {
                var tweets = new Tweet[nodeList.Count];
                for (int i = 0; i < nodeList.Count; i++)
                {
                    tweets[i] = new Tweet();
                    tweets[i].Location = new Point(0, (0 + i * 100));
                    tweets[i].TweetText.Text = nodeList[i].SelectSingleNode("text").InnerText;
                    tweets[i].TweetImage.ImageLocation = nodeList[i].SelectSingleNode("user/profile_image_url").InnerText;
                    tweets[i].lluser.Text = nodeList[i].SelectSingleNode("user/screen_name").InnerText;
                    tweets[i].lvia.Text = "via " + StripHtml(nodeList[i].SelectSingleNode("source").InnerText);
                    tweets[i].ltimeago.Text = TwitterDateTime.ConvertToDateTime(
                        nodeList[i].SelectSingleNode("created_at").InnerText).
                        ToRelativeTime();
                    tweetWin.TweetPanel.Controls.Add(tweets[i]);
                }
            }
            tweetWin.Show();
        }
        public static void Button1()
        {
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
            var xmldoc = new DOMDocument();
            var xmlresponse = FluentTwitter.CreateRequest()
                .Users().ShowProfileFor(username).AsXml().Request();

            xmldoc.loadXML(xmlresponse);

            ac.Name = xmldoc.documentElement.selectSingleNode("/user/name").text;
            ac.Bio = xmldoc.documentElement.selectSingleNode("/user/description").text;
            ac.Background = xmldoc.documentElement.selectSingleNode("/user/profile_background_image_url").text;
            return ac;
        }
    }

}