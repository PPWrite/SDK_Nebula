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
            this.button_answer = new System.Windows.Forms.Button();
            this.listView1 = new System.Windows.Forms.ListView();
            this.ListViewMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.TSMI_SetStu = new System.Windows.Forms.ToolStripMenuItem();
            this.TSMI_SetBmpStu = new System.Windows.Forms.ToolStripMenuItem();
            this.label_tip = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.IpComboBox = new System.Windows.Forms.ComboBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.button3 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.ListViewMenuStrip.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
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
            // button_answer
            // 
            this.button_answer.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_answer.Location = new System.Drawing.Point(103, 23);
            this.button_answer.Name = "button_answer";
            this.button_answer.Size = new System.Drawing.Size(84, 26);
            this.button_answer.TabIndex = 1;
            this.button_answer.Text = "开始答题";
            this.button_answer.UseVisualStyleBackColor = true;
            this.button_answer.Click += new System.EventHandler(this.button_answer_Click);
            // 
            // listView1
            // 
            this.listView1.ContextMenuStrip = this.ListViewMenuStrip;
            this.listView1.FullRowSelect = true;
            this.listView1.GridLines = true;
            this.listView1.Location = new System.Drawing.Point(12, 217);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(773, 365);
            this.listView1.TabIndex = 2;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.DoubleClick += new System.EventHandler(this.listView1_DoubleClick);
            // 
            // ListViewMenuStrip
            // 
            this.ListViewMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.TSMI_SetStu,
            this.TSMI_SetBmpStu});
            this.ListViewMenuStrip.Name = "ListViewMenuStrip";
            this.ListViewMenuStrip.Size = new System.Drawing.Size(207, 48);
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
            // label_tip
            // 
            this.label_tip.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_tip.ForeColor = System.Drawing.Color.Red;
            this.label_tip.Location = new System.Drawing.Point(164, 585);
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
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(24, 27);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(73, 20);
            this.comboBox1.TabIndex = 6;
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
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.comboBox1);
            this.groupBox2.Controls.Add(this.button_answer);
            this.groupBox2.Location = new System.Drawing.Point(12, 132);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(227, 68);
            this.groupBox2.TabIndex = 12;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "客观题模拟";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.button3);
            this.groupBox3.Location = new System.Drawing.Point(260, 132);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(525, 68);
            this.groupBox3.TabIndex = 13;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "主观题模拟";
            // 
            // button3
            // 
            this.button3.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button3.Location = new System.Drawing.Point(19, 23);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(84, 26);
            this.button3.TabIndex = 2;
            this.button3.Text = "开始答题";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(122, 26);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(74, 19);
            this.label4.TabIndex = 11;
            this.label4.Text = "未开始答题";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(797, 622);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label_tip);
            this.Controls.Add(this.listView1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.Text = "wifi测试工具";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ListViewMenuStrip.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_start_stop;
        private System.Windows.Forms.Button button_answer;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.Label label_tip;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.ContextMenuStrip ListViewMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem TSMI_SetStu;
        private System.Windows.Forms.ToolStripMenuItem TSMI_SetBmpStu;
        private System.Windows.Forms.ComboBox IpComboBox;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button3;
    }
}

