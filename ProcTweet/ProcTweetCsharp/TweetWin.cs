using System.Windows.Forms;

namespace ProcTweetCsharp
{
    public class TweetWin : Form
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.TweetPanel = new System.Windows.Forms.Panel();
            this._stweetstatus = new System.Windows.Forms.StatusStrip();
            this.TweetPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // TweetPanel
            // 
            this.TweetPanel.AutoScroll = true;
            this.TweetPanel.AutoSize = true;
            this.TweetPanel.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.TweetPanel.Controls.Add(this._stweetstatus);
            this.TweetPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TweetPanel.Location = new System.Drawing.Point(0, 0);
            this.TweetPanel.Name = "TweetPanel";
            this.TweetPanel.Size = new System.Drawing.Size(318, 575);
            this.TweetPanel.TabIndex = 0;
            // 
            // _stweetstatus
            // 
            this._stweetstatus.Location = new System.Drawing.Point(0, 553);
            this._stweetstatus.Name = "_stweetstatus";
            this._stweetstatus.Size = new System.Drawing.Size(318, 22);
            this._stweetstatus.Stretch = false;
            this._stweetstatus.TabIndex = 0;
            // 
            // TweetWin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(318, 575);
            this.Controls.Add(this.TweetPanel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "TweetWin";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "TweetWin";
            this.TweetPanel.ResumeLayout(false);
            this.TweetPanel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private StatusStrip _stweetstatus;

        public Panel TweetPanel;
        public TweetWin()
        {
            
            InitializeComponent();

        }
    }
}
