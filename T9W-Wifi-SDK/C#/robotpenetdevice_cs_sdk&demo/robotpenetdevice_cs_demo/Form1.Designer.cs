namespace rbt_win32_2_demo
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
            this.components = new System.ComponentModel.Container();
            this.button_start_stop = new System.Windows.Forms.Button();
            this.button_start = new System.Windows.Forms.Button();
            this.listView1 = new System.Windows.Forms.ListView();
            this.ListViewMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.TSMI_SetStu = new System.Windows.Forms.ToolStripMenuItem();
            this.TSMI_SetBmpStu = new System.Windows.Forms.ToolStripMenuItem();
            this.LookAnswerResultToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SetFBMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label_tip = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.comboBox_Qlist = new System.Windows.Forms.ComboBox();
            this.IpComboBox = new System.Windows.Forms.ComboBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.button_end = new System.Windows.Forms.Button();
            this.button_stop = new System.Windows.Forms.Button();
            this.textBox_num = new System.Windows.Forms.TextBox();
            this.comboBox_Qtype = new System.Windows.Forms.ComboBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.ListViewMenuStrip.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // button_start_stop
            // 
            this.button_start_stop.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_start_stop.Location = new System.Drawing.Point(14, 26);
            this.button_start_stop.Name = "button_start_stop";
            this.button_start_stop.Size = new System.Drawing.Size(84, 26);
            this.button_start_stop.TabIndex = 0;
            this.button_start_stop.Text = "开始";
            this.button_start_stop.UseVisualStyleBackColor = true;
            this.button_start_stop.Click += new System.EventHandler(this.button_start_stop_Click);
            // 
            // button_start
            // 
            this.button_start.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_start.Location = new System.Drawing.Point(261, 22);
            this.button_start.Name = "button_start";
            this.button_start.Size = new System.Drawing.Size(84, 26);
            this.button_start.TabIndex = 1;
            this.button_start.Text = "开始答题";
            this.button_start.UseVisualStyleBackColor = true;
            this.button_start.Click += new System.EventHandler(this.button_start_Click);
            // 
            // listView1
            // 
            this.listView1.ContextMenuStrip = this.ListViewMenuStrip;
            this.listView1.FullRowSelect = true;
            this.listView1.GridLines = true;
            this.listView1.Location = new System.Drawing.Point(12, 268);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(773, 392);
            this.listView1.TabIndex = 2;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.DoubleClick += new System.EventHandler(this.listView1_DoubleClick);
            // 
            // ListViewMenuStrip
            // 
            this.ListViewMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.TSMI_SetStu,
            this.TSMI_SetBmpStu,
            this.LookAnswerResultToolStripMenuItem,
            this.SetFBMenuItem});
            this.ListViewMenuStrip.Name = "ListViewMenuStrip";
            this.ListViewMenuStrip.Size = new System.Drawing.Size(207, 92);
            // 
            // TSMI_SetStu
            // 
            this.TSMI_SetStu.Name = "TSMI_SetStu";
            this.TSMI_SetStu.Size = new System.Drawing.Size(206, 22);
            this.TSMI_SetStu.Text = "设置学生id";
            this.TSMI_SetStu.Click += new System.EventHandler(this.TSMI_SetStu_Click);
            // 
            // TSMI_SetBmpStu
            // 
            this.TSMI_SetBmpStu.Name = "TSMI_SetBmpStu";
            this.TSMI_SetBmpStu.Size = new System.Drawing.Size(206, 22);
            this.TSMI_SetBmpStu.Text = "设置学生中文id(T9W-A)";
            this.TSMI_SetBmpStu.Click += new System.EventHandler(this.TSMI_SetBmpStu_Click);
            // 
            // LookAnswerResultToolStripMenuItem
            // 
            this.LookAnswerResultToolStripMenuItem.Name = "LookAnswerResultToolStripMenuItem";
            this.LookAnswerResultToolStripMenuItem.Size = new System.Drawing.Size(206, 22);
            this.LookAnswerResultToolStripMenuItem.Text = "查看答题结果信息";
            this.LookAnswerResultToolStripMenuItem.Click += new System.EventHandler(this.LookAnswerResultToolStripMenuItem_Click);
            // 
            // SetFBMenuItem
            // 
            this.SetFBMenuItem.Name = "SetFBMenuItem";
            this.SetFBMenuItem.Size = new System.Drawing.Size(206, 22);
            this.SetFBMenuItem.Text = "设置显示信息";
            this.SetFBMenuItem.Visible = false;
            this.SetFBMenuItem.Click += new System.EventHandler(this.SetFBMenuItem_Click);
            // 
            // label_tip
            // 
            this.label_tip.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_tip.ForeColor = System.Drawing.Color.Red;
            this.label_tip.Location = new System.Drawing.Point(217, 663);
            this.label_tip.Name = "label_tip";
            this.label_tip.Size = new System.Drawing.Size(347, 23);
            this.label_tip.TabIndex = 3;
            this.label_tip.Text = "双击设备行打开画布";
            this.label_tip.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button1.Location = new System.Drawing.Point(114, 26);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(84, 26);
            this.button1.TabIndex = 1;
            this.button1.Text = "配置面板";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button_test_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(214, 35);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "IP：";
            // 
            // button2
            // 
            this.button2.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button2.Location = new System.Drawing.Point(380, 26);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(84, 26);
            this.button2.TabIndex = 1;
            this.button2.Text = "切换";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button_switch_Click);
            // 
            // comboBox_Qlist
            // 
            this.comboBox_Qlist.FormattingEnabled = true;
            this.comboBox_Qlist.Location = new System.Drawing.Point(114, 26);
            this.comboBox_Qlist.Name = "comboBox_Qlist";
            this.comboBox_Qlist.Size = new System.Drawing.Size(89, 20);
            this.comboBox_Qlist.TabIndex = 6;
            this.comboBox_Qlist.SelectedIndexChanged += new System.EventHandler(this.comboBox_Qlist_SelectedIndexChanged);
            // 
            // IpComboBox
            // 
            this.IpComboBox.FormattingEnabled = true;
            this.IpComboBox.Location = new System.Drawing.Point(249, 30);
            this.IpComboBox.Name = "IpComboBox";
            this.IpComboBox.Size = new System.Drawing.Size(125, 20);
            this.IpComboBox.TabIndex = 8;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(13, 70);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(74, 19);
            this.label2.TabIndex = 9;
            this.label2.Text = "状态说明：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(85, 70);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(74, 19);
            this.label3.TabIndex = 10;
            this.label3.Text = "服务未开启";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.IpComboBox);
            this.groupBox1.Controls.Add(this.button_start_stop);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.button2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(11, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(774, 111);
            this.groupBox1.TabIndex = 11;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "基础功能";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(488, 35);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 12);
            this.label6.TabIndex = 12;
            this.label6.Text = "在线数量：";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(559, 35);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 12);
            this.label5.TabIndex = 11;
            this.label5.Text = "label5";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.button_end);
            this.groupBox2.Controls.Add(this.button_stop);
            this.groupBox2.Controls.Add(this.textBox_num);
            this.groupBox2.Controls.Add(this.comboBox_Qtype);
            this.groupBox2.Controls.Add(this.comboBox_Qlist);
            this.groupBox2.Controls.Add(this.button_start);
            this.groupBox2.Location = new System.Drawing.Point(12, 132);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(773, 68);
            this.groupBox2.TabIndex = 12;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "互动模拟";
            // 
            // button_end
            // 
            this.button_end.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_end.Location = new System.Drawing.Point(441, 22);
            this.button_end.Name = "button_end";
            this.button_end.Size = new System.Drawing.Size(84, 26);
            this.button_end.TabIndex = 10;
            this.button_end.Text = "结束答题";
            this.button_end.UseVisualStyleBackColor = true;
            this.button_end.Click += new System.EventHandler(this.button_end_Click);
            // 
            // button_stop
            // 
            this.button_stop.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_stop.Location = new System.Drawing.Point(351, 22);
            this.button_stop.Name = "button_stop";
            this.button_stop.Size = new System.Drawing.Size(84, 26);
            this.button_stop.TabIndex = 9;
            this.button_stop.Text = "停止答题";
            this.button_stop.UseVisualStyleBackColor = true;
            this.button_stop.Click += new System.EventHandler(this.button_stop_Click);
            // 
            // textBox_num
            // 
            this.textBox_num.Location = new System.Drawing.Point(210, 25);
            this.textBox_num.Name = "textBox_num";
            this.textBox_num.Size = new System.Drawing.Size(32, 21);
            this.textBox_num.TabIndex = 8;
            this.textBox_num.Text = "1";
            // 
            // comboBox_Qtype
            // 
            this.comboBox_Qtype.FormattingEnabled = true;
            this.comboBox_Qtype.Location = new System.Drawing.Point(22, 26);
            this.comboBox_Qtype.Name = "comboBox_Qtype";
            this.comboBox_Qtype.Size = new System.Drawing.Size(86, 20);
            this.comboBox_Qtype.TabIndex = 7;
            this.comboBox_Qtype.SelectedIndexChanged += new System.EventHandler(this.comboBox_Qtype_SelectedIndexChanged);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.textBox1);
            this.groupBox4.Controls.Add(this.label4);
            this.groupBox4.Controls.Add(this.button3);
            this.groupBox4.Controls.Add(this.button6);
            this.groupBox4.Controls.Add(this.button5);
            this.groupBox4.Controls.Add(this.button4);
            this.groupBox4.Location = new System.Drawing.Point(13, 207);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(772, 55);
            this.groupBox4.TabIndex = 14;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "连接状态";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(657, 21);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 21);
            this.textBox1.TabIndex = 5;
            this.textBox1.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox1_KeyPress);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(619, 25);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 4;
            this.label4.Text = "页码：";
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(488, 20);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(124, 23);
            this.button3.TabIndex = 3;
            this.button3.Text = "开启页码对比";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(195, 21);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(75, 23);
            this.button6.TabIndex = 2;
            this.button6.Text = "设置报点率";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Visible = false;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(21, 20);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(75, 23);
            this.button5.TabIndex = 1;
            this.button5.Text = "导出";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(102, 20);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 23);
            this.button4.TabIndex = 0;
            this.button4.Text = "导入";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(797, 690);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label_tip);
            this.Controls.Add(this.listView1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.Text = "wifi测试工具 HEXL v20191219001";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ListViewMenuStrip.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_start_stop;
        private System.Windows.Forms.Button button_start;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.Label label_tip;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.ComboBox comboBox_Qlist;
        private System.Windows.Forms.ContextMenuStrip ListViewMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem TSMI_SetStu;
        private System.Windows.Forms.ToolStripMenuItem TSMI_SetBmpStu;
        private System.Windows.Forms.ComboBox IpComboBox;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.ComboBox comboBox_Qtype;
        private System.Windows.Forms.Button button_stop;
        private System.Windows.Forms.TextBox textBox_num;
        private System.Windows.Forms.Button button_end;
        private System.Windows.Forms.ToolStripMenuItem LookAnswerResultToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem SetFBMenuItem;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button3;
    }
}

