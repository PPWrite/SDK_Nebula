namespace rbt_win32_2_demo
{
    partial class drawForm
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
            this.SuspendLayout();
            // 
            // drawForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(585, 753);
            this.Name = "drawForm";
            this.Text = "drawForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.drawForm_FormClosing);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.drawForm_Paint);
            this.DoubleClick += new System.EventHandler(this.TrailsShowFrom_DoubleClick);
            this.ResumeLayout(false);

        }

        #endregion
    }
}