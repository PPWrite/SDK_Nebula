namespace RobotPenTestDll
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.status_label = new System.Windows.Forms.Label();
            this.Error_label = new System.Windows.Forms.Label();
            this.open_button = new System.Windows.Forms.Button();
            this.version_label = new System.Windows.Forms.Label();
            this.version_label_show = new System.Windows.Forms.Label();
            this.status_button_query = new System.Windows.Forms.Button();
            this.status_label_title = new System.Windows.Forms.Label();
            this.ns_start_button = new System.Windows.Forms.Button();
            this.ms_end_button = new System.Windows.Forms.Button();
            this.set_button = new System.Windows.Forms.Button();
            this.custom_label = new System.Windows.Forms.Label();
            this.class_label = new System.Windows.Forms.Label();
            this.device_label = new System.Windows.Forms.Label();
            this.class_textBox = new System.Windows.Forms.TextBox();
            this.device_textBox = new System.Windows.Forms.TextBox();
            this.custom_textBox = new System.Windows.Forms.TextBox();
            this.update_button = new System.Windows.Forms.Button();
            this.mode_label_tip = new System.Windows.Forms.Label();
            this.mode_label = new System.Windows.Forms.Label();
            this.voteClear_button = new System.Windows.Forms.Button();
            this.msClear_button = new System.Windows.Forms.Button();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.screen_set_label = new System.Windows.Forms.Label();
            this.listView1 = new System.Windows.Forms.ListView();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button1.Location = new System.Drawing.Point(19, 348);
            this.button1.Margin = new System.Windows.Forms.Padding(4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(139, 39);
            this.button1.TabIndex = 0;
            this.button1.Text = "开始投票";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button2.Location = new System.Drawing.Point(184, 348);
            this.button2.Margin = new System.Windows.Forms.Padding(4);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(133, 39);
            this.button2.TabIndex = 1;
            this.button2.Text = "结束投票";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // status_label
            // 
            this.status_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.status_label.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(255)))));
            this.status_label.Location = new System.Drawing.Point(295, 250);
            this.status_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.status_label.Name = "status_label";
            this.status_label.Size = new System.Drawing.Size(388, 44);
            this.status_label.TabIndex = 2;
            this.status_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Error_label
            // 
            this.Error_label.Location = new System.Drawing.Point(365, 288);
            this.Error_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Error_label.Name = "Error_label";
            this.Error_label.Size = new System.Drawing.Size(251, 29);
            this.Error_label.TabIndex = 3;
            // 
            // open_button
            // 
            this.open_button.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.open_button.Cursor = System.Windows.Forms.Cursors.Hand;
            this.open_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.open_button.Location = new System.Drawing.Point(19, 195);
            this.open_button.Margin = new System.Windows.Forms.Padding(4);
            this.open_button.Name = "open_button";
            this.open_button.Size = new System.Drawing.Size(139, 45);
            this.open_button.TabIndex = 5;
            this.open_button.Text = "打开设备";
            this.open_button.UseVisualStyleBackColor = false;
            this.open_button.Click += new System.EventHandler(this.open_button_Click);
            // 
            // version_label
            // 
            this.version_label.AutoSize = true;
            this.version_label.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.version_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.version_label.Location = new System.Drawing.Point(173, 203);
            this.version_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.version_label.Name = "version_label";
            this.version_label.Size = new System.Drawing.Size(77, 27);
            this.version_label.TabIndex = 6;
            this.version_label.Text = "版本号:";
            // 
            // version_label_show
            // 
            this.version_label_show.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.version_label_show.Location = new System.Drawing.Point(295, 203);
            this.version_label_show.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.version_label_show.Name = "version_label_show";
            this.version_label_show.Size = new System.Drawing.Size(245, 29);
            this.version_label_show.TabIndex = 7;
            this.version_label_show.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // status_button_query
            // 
            this.status_button_query.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.status_button_query.Cursor = System.Windows.Forms.Cursors.Hand;
            this.status_button_query.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.status_button_query.Location = new System.Drawing.Point(19, 247);
            this.status_button_query.Margin = new System.Windows.Forms.Padding(4);
            this.status_button_query.Name = "status_button_query";
            this.status_button_query.Size = new System.Drawing.Size(139, 44);
            this.status_button_query.TabIndex = 8;
            this.status_button_query.Text = "状态查询";
            this.status_button_query.UseVisualStyleBackColor = false;
            this.status_button_query.Click += new System.EventHandler(this.status_button_query_Click);
            // 
            // status_label_title
            // 
            this.status_label_title.AutoSize = true;
            this.status_label_title.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192)))));
            this.status_label_title.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.status_label_title.Location = new System.Drawing.Point(179, 259);
            this.status_label_title.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.status_label_title.Name = "status_label_title";
            this.status_label_title.Size = new System.Drawing.Size(57, 27);
            this.status_label_title.TabIndex = 9;
            this.status_label_title.Text = "状态:";
            // 
            // ns_start_button
            // 
            this.ns_start_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ns_start_button.Location = new System.Drawing.Point(19, 406);
            this.ns_start_button.Margin = new System.Windows.Forms.Padding(4);
            this.ns_start_button.Name = "ns_start_button";
            this.ns_start_button.Size = new System.Drawing.Size(139, 39);
            this.ns_start_button.TabIndex = 10;
            this.ns_start_button.Text = "ms模式";
            this.ns_start_button.UseVisualStyleBackColor = true;
            this.ns_start_button.Click += new System.EventHandler(this.ns_start_button_Click);
            // 
            // ms_end_button
            // 
            this.ms_end_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ms_end_button.Location = new System.Drawing.Point(184, 406);
            this.ms_end_button.Margin = new System.Windows.Forms.Padding(4);
            this.ms_end_button.Name = "ms_end_button";
            this.ms_end_button.Size = new System.Drawing.Size(133, 39);
            this.ms_end_button.TabIndex = 11;
            this.ms_end_button.Text = "结束MS模式";
            this.ms_end_button.UseVisualStyleBackColor = true;
            this.ms_end_button.Click += new System.EventHandler(this.ms_end_button_Click);
            // 
            // set_button
            // 
            this.set_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.set_button.Location = new System.Drawing.Point(19, 496);
            this.set_button.Margin = new System.Windows.Forms.Padding(4);
            this.set_button.Name = "set_button";
            this.set_button.Size = new System.Drawing.Size(139, 40);
            this.set_button.TabIndex = 12;
            this.set_button.Text = "设置";
            this.set_button.UseVisualStyleBackColor = true;
            this.set_button.Click += new System.EventHandler(this.set_button_Click);
            // 
            // custom_label
            // 
            this.custom_label.AutoSize = true;
            this.custom_label.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.custom_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.custom_label.Location = new System.Drawing.Point(16, 616);
            this.custom_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.custom_label.Name = "custom_label";
            this.custom_label.Size = new System.Drawing.Size(134, 27);
            this.custom_label.TabIndex = 13;
            this.custom_label.Text = "customNum:";
            // 
            // class_label
            // 
            this.class_label.AutoSize = true;
            this.class_label.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.class_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.class_label.Location = new System.Drawing.Point(281, 616);
            this.class_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.class_label.Name = "class_label";
            this.class_label.Size = new System.Drawing.Size(108, 27);
            this.class_label.TabIndex = 14;
            this.class_label.Text = "classNum:";
            this.class_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // device_label
            // 
            this.device_label.AutoSize = true;
            this.device_label.BackColor = System.Drawing.Color.Blue;
            this.device_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.device_label.Location = new System.Drawing.Point(487, 616);
            this.device_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.device_label.Name = "device_label";
            this.device_label.Size = new System.Drawing.Size(125, 27);
            this.device_label.TabIndex = 15;
            this.device_label.Text = "deviceNum:";
            this.device_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // class_textBox
            // 
            this.class_textBox.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.class_textBox.Location = new System.Drawing.Point(405, 616);
            this.class_textBox.Margin = new System.Windows.Forms.Padding(4);
            this.class_textBox.Name = "class_textBox";
            this.class_textBox.ReadOnly = true;
            this.class_textBox.Size = new System.Drawing.Size(72, 34);
            this.class_textBox.TabIndex = 16;
            this.class_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // device_textBox
            // 
            this.device_textBox.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.device_textBox.Location = new System.Drawing.Point(628, 612);
            this.device_textBox.Margin = new System.Windows.Forms.Padding(4);
            this.device_textBox.Name = "device_textBox";
            this.device_textBox.ReadOnly = true;
            this.device_textBox.Size = new System.Drawing.Size(109, 34);
            this.device_textBox.TabIndex = 17;
            this.device_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // custom_textBox
            // 
            this.custom_textBox.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.custom_textBox.Location = new System.Drawing.Point(168, 616);
            this.custom_textBox.Margin = new System.Windows.Forms.Padding(4);
            this.custom_textBox.Name = "custom_textBox";
            this.custom_textBox.ReadOnly = true;
            this.custom_textBox.Size = new System.Drawing.Size(87, 34);
            this.custom_textBox.TabIndex = 18;
            this.custom_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // update_button
            // 
            this.update_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.update_button.Location = new System.Drawing.Point(19, 689);
            this.update_button.Margin = new System.Windows.Forms.Padding(4);
            this.update_button.Name = "update_button";
            this.update_button.Size = new System.Drawing.Size(100, 39);
            this.update_button.TabIndex = 19;
            this.update_button.Text = "升级";
            this.update_button.UseVisualStyleBackColor = true;
            // 
            // mode_label_tip
            // 
            this.mode_label_tip.AutoSize = true;
            this.mode_label_tip.Location = new System.Drawing.Point(139, 700);
            this.mode_label_tip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.mode_label_tip.Name = "mode_label_tip";
            this.mode_label_tip.Size = new System.Drawing.Size(52, 15);
            this.mode_label_tip.TabIndex = 20;
            this.mode_label_tip.Text = "模式：";
            // 
            // mode_label
            // 
            this.mode_label.Location = new System.Drawing.Point(200, 528);
            this.mode_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.mode_label.Name = "mode_label";
            this.mode_label.Size = new System.Drawing.Size(209, 29);
            this.mode_label.TabIndex = 21;
            this.mode_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // voteClear_button
            // 
            this.voteClear_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.voteClear_button.Location = new System.Drawing.Point(368, 348);
            this.voteClear_button.Margin = new System.Windows.Forms.Padding(4);
            this.voteClear_button.Name = "voteClear_button";
            this.voteClear_button.Size = new System.Drawing.Size(100, 39);
            this.voteClear_button.TabIndex = 22;
            this.voteClear_button.Text = "清除";
            this.voteClear_button.UseVisualStyleBackColor = true;
            this.voteClear_button.Click += new System.EventHandler(this.voteClear_button_Click);
            // 
            // msClear_button
            // 
            this.msClear_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.msClear_button.Location = new System.Drawing.Point(368, 406);
            this.msClear_button.Margin = new System.Windows.Forms.Padding(4);
            this.msClear_button.Name = "msClear_button";
            this.msClear_button.Size = new System.Drawing.Size(100, 39);
            this.msClear_button.TabIndex = 23;
            this.msClear_button.Text = "清除";
            this.msClear_button.UseVisualStyleBackColor = true;
            this.msClear_button.Click += new System.EventHandler(this.msClear_button_Click);
            // 
            // comboBox1
            // 
            this.comboBox1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "横屏",
            "竖屏"});
            this.comboBox1.Location = new System.Drawing.Point(141, 819);
            this.comboBox1.Margin = new System.Windows.Forms.Padding(4);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(160, 35);
            this.comboBox1.TabIndex = 24;
            // 
            // screen_set_label
            // 
            this.screen_set_label.AutoSize = true;
            this.screen_set_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.screen_set_label.Location = new System.Drawing.Point(19, 823);
            this.screen_set_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.screen_set_label.Name = "screen_set_label";
            this.screen_set_label.Size = new System.Drawing.Size(97, 27);
            this.screen_set_label.TabIndex = 25;
            this.screen_set_label.Text = "屏幕设置:";
            // 
            // listView1
            // 
            this.listView1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.listView1.FullRowSelect = true;
            this.listView1.GridLines = true;
            this.listView1.Location = new System.Drawing.Point(21, 12);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(447, 156);
            this.listView1.TabIndex = 26;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            // 
            // comboBox2
            // 
            this.comboBox2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox2.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comboBox2.ForeColor = System.Drawing.SystemColors.InfoText;
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "单选",
            "多选",
            "抢答"});
            this.comboBox2.Location = new System.Drawing.Point(24, 303);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(121, 32);
            this.comboBox2.TabIndex = 27;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1128, 885);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.screen_set_label);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.msClear_button);
            this.Controls.Add(this.voteClear_button);
            this.Controls.Add(this.mode_label);
            this.Controls.Add(this.mode_label_tip);
            this.Controls.Add(this.update_button);
            this.Controls.Add(this.custom_textBox);
            this.Controls.Add(this.device_textBox);
            this.Controls.Add(this.class_textBox);
            this.Controls.Add(this.device_label);
            this.Controls.Add(this.class_label);
            this.Controls.Add(this.custom_label);
            this.Controls.Add(this.set_button);
            this.Controls.Add(this.ms_end_button);
            this.Controls.Add(this.ns_start_button);
            this.Controls.Add(this.status_label_title);
            this.Controls.Add(this.status_button_query);
            this.Controls.Add(this.version_label_show);
            this.Controls.Add(this.version_label);
            this.Controls.Add(this.open_button);
            this.Controls.Add(this.Error_label);
            this.Controls.Add(this.status_label);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label status_label;
        private System.Windows.Forms.Label Error_label;
        private System.Windows.Forms.Button open_button;
        private System.Windows.Forms.Label version_label;
        private System.Windows.Forms.Label version_label_show;
        private System.Windows.Forms.Button status_button_query;
        private System.Windows.Forms.Label status_label_title;
        private System.Windows.Forms.Button ns_start_button;
        private System.Windows.Forms.Button ms_end_button;
        private System.Windows.Forms.Button set_button;
        private System.Windows.Forms.Label custom_label;
        private System.Windows.Forms.Label class_label;
        private System.Windows.Forms.Label device_label;
        private System.Windows.Forms.TextBox class_textBox;
        private System.Windows.Forms.TextBox device_textBox;
        private System.Windows.Forms.TextBox custom_textBox;
        private System.Windows.Forms.Button update_button;
        private System.Windows.Forms.Label mode_label_tip;
        private System.Windows.Forms.Label mode_label;
        private System.Windows.Forms.Button voteClear_button;
        private System.Windows.Forms.Button msClear_button;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label screen_set_label;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ComboBox comboBox2;
    }
}

