using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Net;
using System.Windows.Forms;
using Dimebrain.TweetSharp.Core.Web;
using Dimebrain.TweetSharp.Extensions;
using Dimebrain.TweetSharp.Fluent;
using Dimebrain.TweetSharp.Model;

namespace ProcTweetCsharp
{
    public class Requests
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Executes the request return action. </summary>
        ///
        /// <remarks>   Olivier Gagnon, 2009-11-18. </remarks>
        ///
        /// <param name="sender">   Source of the event. </param>
        /// <param name="e">        Event information to send to registered event handlers. </param>
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        private static void OnRequestReturn(TweetWin tw, WebQueryResponseEventArgs e)
        {
            Console.WriteLine(e.Response);
            TwitterRateLimitStatus crate = e.Response.AsRateLimitStatus();
            string chitsleft = String.Format("{0}/{1} hits remaining. Resets at: {2}",
                                             crate.RemainingHits, crate.HourlyLimit,
                                             crate.ResetTime.TimeOfDay);
            if (tw.InvokeRequired)
            {
                tw.Invoke((Action) (() => { tw.StatusText.Text = chitsleft; }));
            }
            else
                tw.StatusText.Text = chitsleft;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Gets the last friends tweets. </summary>
        ///
        /// <remarks>   Olivier Gagnon, 2009-11-09. </remarks>
        ///
        /// <param name="sender">   Source of the event. </param>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public static void GetLastFriendsTweets (object sender)
        {
            var tw = new TweetWin("Last Tweets from Friends");
            int numberOfTweets = 25;
            var logininfo = (LoginInfo) sender;
            AccountInfo ac = AccountInfo.GetTwitterAccountInfo(logininfo.Username);

            // Set background image from twitter
            var uri = new Uri(ac.Background);
            Stream s = WebRequest.Create(uri)
                .GetResponse().GetResponseStream();
            Image backimg = Image.FromStream(s);

            tw.TweetPanel.BackgroundImage = backimg;
            tw.TweetPanel.BackColor = Color.Transparent;

            FluentTwitter.CreateRequest()
                .AuthenticateAs(logininfo.Username, logininfo.Password)
                .Account().GetRateLimitStatus().AsJson()
                .CallbackTo((f,e) => OnRequestReturn(tw, e))
                .RepeatEvery(1.Minute()).RequestAsync();


            // Create Tweets and show
            string twitter = FluentTwitter.CreateRequest()
                .AuthenticateWith(logininfo.TcInfo.ConsumerKey, logininfo.TcInfo.ConsumerSecret,
                                  logininfo.Authtoken.Token, logininfo.Authtoken.TokenSecret)
                .Statuses().OnFriendsTimeline().Take(numberOfTweets).AsJson()
                .Request();

            IEnumerable<TwitterStatus> response = twitter.AsStatuses();
            int i = 0;
            foreach (TwitterStatus ts in response)
            {
                var tweet = new Tweet();
                tweet.Location = new Point(0, (0 + i*100));
                tweet.TweetText.Text = ts.Text;
                tweet.TweetImage.ImageLocation = ts.User.ProfileImageUrl;
                tweet.lluser.Text = ts.User.ScreenName;
                tweet.lvia.Text = "via " + Utilities.StripHtml(ts.Source);
                tweet.ltimeago.Text = ts.CreatedDate.ToRelativeTime();
                tw.TweetPanel.Controls.Add(tweet);
                i++;
            }
            Application.Run(tw);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>   Gets the mentions. </summary>
        ///
        /// <remarks>   Olivier Gagnon, 2009-11-18. </remarks>
        ///
        /// <param name="sender">   Source of the event. </param>
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        public static void GetMentions(object sender)
        {
            var tw = new TweetWin("Mentions");
            var logininfo = (LoginInfo) sender;
            AccountInfo ac = AccountInfo.GetTwitterAccountInfo(logininfo.Username);

            // Set background image from twitter
            var uri = new Uri(ac.Background);
            Stream s = WebRequest.Create(uri)
                .GetResponse().GetResponseStream();
            Image backimg = Image.FromStream(s);

            tw.TweetPanel.BackgroundImage = backimg;
            tw.TweetPanel.BackColor = Color.Transparent;

            FluentTwitter.CreateRequest()
                .AuthenticateAs(logininfo.Username, logininfo.Password)
                .Account().GetRateLimitStatus().AsJson()
                .CallbackTo((f, e) => OnRequestReturn(tw, e))
                .RepeatEvery(1.Minute()).RequestAsync();


            // Create Tweets and show
            string twitter = FluentTwitter.CreateRequest()
                .AuthenticateWith(logininfo.TcInfo.ConsumerKey, logininfo.TcInfo.ConsumerSecret,
                                  logininfo.Authtoken.Token, logininfo.Authtoken.TokenSecret)
                .Statuses().Mentions().AsJson()
                .Request();

            IEnumerable<TwitterStatus> response = twitter.AsStatuses();
            int i = 0;
            foreach (TwitterStatus ts in response)
            {
                var tweet = new Tweet();
                tweet.Location = new Point(0, (0 + i*100));
                tweet.TweetText.Text = ts.Text;
                tweet.TweetImage.ImageLocation = ts.User.ProfileImageUrl;
                tweet.lluser.Text = ts.User.ScreenName;
                tweet.lvia.Text = "via " + Utilities.StripHtml(ts.Source);
                tweet.ltimeago.Text = ts.CreatedDate.ToRelativeTime();
                tw.TweetPanel.Controls.Add(tweet);
                i++;
            }
            Application.Run(tw);
        }
    }
}