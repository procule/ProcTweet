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
            this.Stweetstatus = new System.Windows.Forms.StatusStrip();
            this.StatusText = new System.Windows.Forms.ToolStripStatusLabel();
            this.Stweetstatus.SuspendLayout();
            this.SuspendLayout();
            // 
            // TweetPanel
            // 
            this.TweetPanel.AutoScroll = true;
            this.TweetPanel.Location = new System.Drawing.Point(0, 0);
            this.TweetPanel.Size = new System.Drawing.Size(318, 553);
            this.TweetPanel.Name = "TweetPanel";
            this.TweetPanel.TabIndex = 0;
            // 
            // Stweetstatus
            // 
            this.Stweetstatus.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.StatusText});
            this.Stweetstatus.Dock = DockStyle.Bottom;
            this.Stweetstatus.Name = "Stweetstatus";
            this.Stweetstatus.Size = new System.Drawing.Size(318, 22);
            this.Stweetstatus.TabIndex = 1;
            // 
            // StatusText
            // 
            this.StatusText.Name = "StatusText";
            this.StatusText.Size = new System.Drawing.Size(0, 17);
            // 
            // TweetWin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(318, 575);
            this.Controls.Add(this.Stweetstatus);
            this.Controls.Add(this.TweetPanel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "TweetWin";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "TweetWin";
            this.Stweetstatus.ResumeLayout(false);
            this.Stweetstatus.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public StatusStrip Stweetstatus;
        public ToolStripStatusLabel StatusText;


        public Panel TweetPanel;
        public TweetWin()
        {
            
            InitializeComponent();

        }
    }
}
