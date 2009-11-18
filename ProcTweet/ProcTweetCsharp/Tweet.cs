using System.ComponentModel;
using System.Web;
using System.Windows.Forms;

namespace ProcTweetCsharp
{
    public class Tweet : UserControl
    {
        public Tweet()
        {
            InitializeComponent();
            TweetText.Text = "Example of text being displayed by the control.";
            ltimeago.Text = "X moments ago.";
            lluser.Text = "foobar";
            lvia.Text = "Example program";
        }
        private IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.TweetImage = new System.Windows.Forms.PictureBox();
            this.TweetText = new System.Windows.Forms.TextBox();
            this.ltimeago = new System.Windows.Forms.Label();
            this.lluser = new System.Windows.Forms.LinkLabel();
            this.lvia = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.TweetImage)).BeginInit();
            this.SuspendLayout();
            // 
            // TweetImage
            // 
            this.TweetImage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TweetImage.Image = global::ProcTweetCsharp.Properties.Resources.oiseaubleu;
            this.TweetImage.InitialImage = global::ProcTweetCsharp.Properties.Resources.oiseaubleu;
            this.TweetImage.Location = new System.Drawing.Point(10, 10);
            this.TweetImage.Name = "TweetImage";
            this.TweetImage.Size = new System.Drawing.Size(52, 52);
            this.TweetImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.TweetImage.TabIndex = 0;
            this.TweetImage.TabStop = false;
            // 
            // TweetText
            // 
            this.TweetText.BackColor = System.Drawing.SystemColors.Info;
            this.TweetText.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TweetText.Location = new System.Drawing.Point(71, 10);
            this.TweetText.Multiline = true;
            this.TweetText.Name = "TweetText";
            this.TweetText.ReadOnly = true;
            this.TweetText.Size = new System.Drawing.Size(215, 48);
            this.TweetText.TabIndex = 1;
            this.TweetText.TabStop = false;
            // 
            // ltimeago
            // 
            this.ltimeago.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Italic);
            this.ltimeago.Location = new System.Drawing.Point(71, 61);
            this.ltimeago.Name = "ltimeago";
            this.ltimeago.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.ltimeago.Size = new System.Drawing.Size(218, 18);
            this.ltimeago.TabIndex = 2;
            // 
            // lluser
            // 
            this.lluser.Location = new System.Drawing.Point(10, 80);
            this.lluser.Name = "lluser";
            this.lluser.Size = new System.Drawing.Size(112, 16);
            this.lluser.TabIndex = 3;
            this.lluser.VisitedLinkColor = System.Drawing.Color.Blue;
            this.lluser.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.lluser_LinkClicked);
            // 
            // lvia
            // 
            this.lvia.Location = new System.Drawing.Point(71, 79);
            this.lvia.Name = "lvia";
            this.lvia.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.lvia.Size = new System.Drawing.Size(215, 18);
            this.lvia.TabIndex = 4;
            this.lvia.Text = "via";
            // 
            // Tweet
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.Controls.Add(this.lvia);
            this.Controls.Add(this.lluser);
            this.Controls.Add(this.ltimeago);
            this.Controls.Add(this.TweetText);
            this.Controls.Add(this.TweetImage);
            this.Name = "Tweet";
            this.Size = new System.Drawing.Size(300, 100);
            ((System.ComponentModel.ISupportInitialize)(this.TweetImage)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public PictureBox TweetImage;
        public TextBox TweetText;
        public Label ltimeago;
        public LinkLabel lluser;
        public Label lvia;

        private void lluser_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            var llaccount = (LinkLabel)sender;
            var link = "http://twitter.com/" + HttpUtility.UrlEncode(llaccount.Text);
            System.Diagnostics.Process.Start(link);
        }
    }
}
