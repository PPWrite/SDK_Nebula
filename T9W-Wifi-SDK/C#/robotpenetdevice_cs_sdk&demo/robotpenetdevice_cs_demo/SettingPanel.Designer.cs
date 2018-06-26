namespace rbt_win32_2_demo
{
    partial class SettingPanel
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
            this.WifiSetting = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.SleepTimeGroup = new System.Windows.Forms.GroupBox();
            this.button2 = new System.Windows.Forms.Button();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.WifiSetting.SuspendLayout();
            this.SleepTimeGroup.SuspendLayout();
            this.SuspendLayout();
            // 
            // WifiSetting
            // 
            this.WifiSetting.Controls.Add(this.button1);
            this.WifiSetting.Controls.Add(this.label5);
            this.WifiSetting.Controls.Add(this.label4);
            this.WifiSetting.Controls.Add(this.textBox3);
            this.WifiSetting.Controls.Add(this.label3);
            this.WifiSetting.Controls.Add(this.textBox2);
            this.WifiSetting.Controls.Add(this.label2);
            this.WifiSetting.Controls.Add(this.textBox1);
            this.WifiSetting.Controls.Add(this.label1);
            this.WifiSetting.Location = new System.Drawing.Point(12, 12);
            this.WifiSetting.Name = "WifiSetting";
            this.WifiSetting.Size = new System.Drawing.Size(390, 177);
            this.WifiSetting.TabIndex = 0;
            this.WifiSetting.TabStop = false;
            this.WifiSetting.Text = "配网";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(205, 142);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 8;
            this.button1.Text = "确定";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.ForeColor = System.Drawing.Color.Red;
            this.label5.Location = new System.Drawing.Point(296, 70);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(65, 12);
            this.label5.TabIndex = 7;
            this.label5.Text = "*小于10位*";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.Color.Red;
            this.label4.Location = new System.Drawing.Point(296, 32);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "*小于10位*";
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(85, 105);
            this.textBox3.MaxLength = 10;
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(195, 21);
            this.textBox3.TabIndex = 5;
            this.textBox3.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_KeyPress);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(21, 105);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(63, 19);
            this.label3.TabIndex = 4;
            this.label3.Text = "source：";
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(85, 65);
            this.textBox2.MaxLength = 10;
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(195, 21);
            this.textBox2.TabIndex = 3;
            this.textBox2.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_KeyPress);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(21, 65);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(69, 19);
            this.label2.TabIndex = 2;
            this.label2.Text = "wifi密码：";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(85, 27);
            this.textBox1.MaxLength = 10;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(195, 21);
            this.textBox1.TabIndex = 1;
            this.textBox1.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_KeyPress);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(21, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(69, 19);
            this.label1.TabIndex = 0;
            this.label1.Text = "wifi名称：";
            // 
            // SleepTimeGroup
            // 
            this.SleepTimeGroup.Controls.Add(this.label7);
            this.SleepTimeGroup.Controls.Add(this.button2);
            this.SleepTimeGroup.Controls.Add(this.textBox4);
            this.SleepTimeGroup.Controls.Add(this.label6);
            this.SleepTimeGroup.Location = new System.Drawing.Point(13, 205);
            this.SleepTimeGroup.Name = "SleepTimeGroup";
            this.SleepTimeGroup.Size = new System.Drawing.Size(389, 105);
            this.SleepTimeGroup.TabIndex = 1;
            this.SleepTimeGroup.TabStop = false;
            this.SleepTimeGroup.Text = "睡眠时间";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(204, 67);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 11;
            this.button2.Text = "确定";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(84, 30);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(195, 21);
            this.textBox4.TabIndex = 10;
            this.textBox4.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_KeyPress_onlyNum);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.Location = new System.Drawing.Point(20, 30);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(48, 19);
            this.label6.TabIndex = 9;
            this.label6.Text = "时间：";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.ForeColor = System.Drawing.Color.Red;
            this.label7.Location = new System.Drawing.Point(295, 35);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 12);
            this.label7.TabIndex = 12;
            this.label7.Text = "*分钟*";
            // 
            // SettingPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(419, 331);
            this.Controls.Add(this.SleepTimeGroup);
            this.Controls.Add(this.WifiSetting);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SettingPanel";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "配置面板";
            this.TopMost = true;
            this.WifiSetting.ResumeLayout(false);
            this.WifiSetting.PerformLayout();
            this.SleepTimeGroup.ResumeLayout(false);
            this.SleepTimeGroup.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox WifiSetting;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox SleepTimeGroup;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
    }
}