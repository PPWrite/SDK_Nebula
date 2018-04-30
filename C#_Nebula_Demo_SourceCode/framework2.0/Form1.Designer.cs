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
            this.slave_listView = new System.Windows.Forms.ListView();
            this.dongle_san_button = new System.Windows.Forms.Button();
            this.dongle_stopsan_button = new System.Windows.Forms.Button();
            this.dg_con_button = new System.Windows.Forms.Button();
            this.dg_discon_button = new System.Windows.Forms.Button();
            this.slave_ststus_label = new System.Windows.Forms.Label();
            this.slave_status_label1 = new System.Windows.Forms.Label();
            this.slave_version_label = new System.Windows.Forms.Label();
            this.slave_version1_label = new System.Windows.Forms.Label();
            this.slave_name_textBox = new System.Windows.Forms.TextBox();
            this.slave_name_set_button = new System.Windows.Forms.Button();
            this.adjust_button = new System.Windows.Forms.Button();
            this.start_sync_button = new System.Windows.Forms.Button();
            this.end_sync_button = new System.Windows.Forms.Button();
            this.offline_label = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            this.labelnote = new System.Windows.Forms.Label();
            this.label_sync_offline_tip = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button1.Location = new System.Drawing.Point(6, 332);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(104, 31);
            this.button1.TabIndex = 0;
            this.button1.Text = "开始投票";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button2.Location = new System.Drawing.Point(127, 332);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(100, 31);
            this.button2.TabIndex = 1;
            this.button2.Text = "结束投票";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // status_label
            // 
            this.status_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.status_label.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(255)))));
            this.status_label.Location = new System.Drawing.Point(183, 208);
            this.status_label.Name = "status_label";
            this.status_label.Size = new System.Drawing.Size(266, 25);
            this.status_label.TabIndex = 2;
            // 
            // Error_label
            // 
            this.Error_label.Location = new System.Drawing.Point(274, 230);
            this.Error_label.Name = "Error_label";
            this.Error_label.Size = new System.Drawing.Size(188, 23);
            this.Error_label.TabIndex = 3;
            // 
            // open_button
            // 
            this.open_button.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.open_button.Cursor = System.Windows.Forms.Cursors.Hand;
            this.open_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.open_button.Location = new System.Drawing.Point(6, 156);
            this.open_button.Name = "open_button";
            this.open_button.Size = new System.Drawing.Size(104, 36);
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
            this.version_label.Location = new System.Drawing.Point(130, 162);
            this.version_label.Name = "version_label";
            this.version_label.Size = new System.Drawing.Size(62, 21);
            this.version_label.TabIndex = 6;
            this.version_label.Text = "版本号:";
            // 
            // version_label_show
            // 
            this.version_label_show.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.version_label_show.Location = new System.Drawing.Point(194, 162);
            this.version_label_show.Name = "version_label_show";
            this.version_label_show.Size = new System.Drawing.Size(184, 23);
            this.version_label_show.TabIndex = 7;
            // 
            // status_button_query
            // 
            this.status_button_query.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.status_button_query.Cursor = System.Windows.Forms.Cursors.Hand;
            this.status_button_query.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.status_button_query.Location = new System.Drawing.Point(7, 198);
            this.status_button_query.Name = "status_button_query";
            this.status_button_query.Size = new System.Drawing.Size(104, 35);
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
            this.status_label_title.Location = new System.Drawing.Point(134, 207);
            this.status_label_title.Name = "status_label_title";
            this.status_label_title.Size = new System.Drawing.Size(46, 21);
            this.status_label_title.TabIndex = 9;
            this.status_label_title.Text = "状态:";
            // 
            // ns_start_button
            // 
            this.ns_start_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ns_start_button.Location = new System.Drawing.Point(6, 369);
            this.ns_start_button.Name = "ns_start_button";
            this.ns_start_button.Size = new System.Drawing.Size(104, 31);
            this.ns_start_button.TabIndex = 10;
            this.ns_start_button.Text = "ms模式";
            this.ns_start_button.UseVisualStyleBackColor = true;
            this.ns_start_button.Click += new System.EventHandler(this.ns_start_button_Click);
            // 
            // ms_end_button
            // 
            this.ms_end_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ms_end_button.Location = new System.Drawing.Point(126, 369);
            this.ms_end_button.Name = "ms_end_button";
            this.ms_end_button.Size = new System.Drawing.Size(100, 31);
            this.ms_end_button.TabIndex = 11;
            this.ms_end_button.Text = "结束MS模式";
            this.ms_end_button.UseVisualStyleBackColor = true;
            this.ms_end_button.Click += new System.EventHandler(this.ms_end_button_Click);
            // 
            // set_button
            // 
            this.set_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.set_button.Location = new System.Drawing.Point(6, 440);
            this.set_button.Name = "set_button";
            this.set_button.Size = new System.Drawing.Size(104, 32);
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
            this.custom_label.Location = new System.Drawing.Point(12, 534);
            this.custom_label.Name = "custom_label";
            this.custom_label.Size = new System.Drawing.Size(108, 21);
            this.custom_label.TabIndex = 13;
            this.custom_label.Text = "customNum:";
            // 
            // class_label
            // 
            this.class_label.AutoSize = true;
            this.class_label.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.class_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.class_label.Location = new System.Drawing.Point(211, 534);
            this.class_label.Name = "class_label";
            this.class_label.Size = new System.Drawing.Size(87, 21);
            this.class_label.TabIndex = 14;
            this.class_label.Text = "classNum:";
            this.class_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // device_label
            // 
            this.device_label.AutoSize = true;
            this.device_label.BackColor = System.Drawing.Color.Blue;
            this.device_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.device_label.Location = new System.Drawing.Point(365, 534);
            this.device_label.Name = "device_label";
            this.device_label.Size = new System.Drawing.Size(100, 21);
            this.device_label.TabIndex = 15;
            this.device_label.Text = "deviceNum:";
            this.device_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // class_textBox
            // 
            this.class_textBox.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.class_textBox.Location = new System.Drawing.Point(304, 534);
            this.class_textBox.Name = "class_textBox";
            this.class_textBox.ReadOnly = true;
            this.class_textBox.Size = new System.Drawing.Size(55, 29);
            this.class_textBox.TabIndex = 16;
            this.class_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // device_textBox
            // 
            this.device_textBox.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.device_textBox.Location = new System.Drawing.Point(471, 531);
            this.device_textBox.Name = "device_textBox";
            this.device_textBox.ReadOnly = true;
            this.device_textBox.Size = new System.Drawing.Size(83, 29);
            this.device_textBox.TabIndex = 17;
            this.device_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // custom_textBox
            // 
            this.custom_textBox.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.custom_textBox.Location = new System.Drawing.Point(126, 534);
            this.custom_textBox.Name = "custom_textBox";
            this.custom_textBox.ReadOnly = true;
            this.custom_textBox.Size = new System.Drawing.Size(66, 29);
            this.custom_textBox.TabIndex = 18;
            this.custom_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // update_button
            // 
            this.update_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.update_button.Location = new System.Drawing.Point(12, 591);
            this.update_button.Name = "update_button";
            this.update_button.Size = new System.Drawing.Size(75, 31);
            this.update_button.TabIndex = 19;
            this.update_button.Text = "升级";
            this.update_button.UseVisualStyleBackColor = true;
            // 
            // mode_label_tip
            // 
            this.mode_label_tip.AutoSize = true;
            this.mode_label_tip.Location = new System.Drawing.Point(104, 603);
            this.mode_label_tip.Name = "mode_label_tip";
            this.mode_label_tip.Size = new System.Drawing.Size(41, 12);
            this.mode_label_tip.TabIndex = 20;
            this.mode_label_tip.Text = "模式：";
            // 
            // mode_label
            // 
            this.mode_label.Location = new System.Drawing.Point(150, 422);
            this.mode_label.Name = "mode_label";
            this.mode_label.Size = new System.Drawing.Size(157, 23);
            this.mode_label.TabIndex = 21;
            this.mode_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // voteClear_button
            // 
            this.voteClear_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.voteClear_button.Location = new System.Drawing.Point(246, 332);
            this.voteClear_button.Name = "voteClear_button";
            this.voteClear_button.Size = new System.Drawing.Size(75, 31);
            this.voteClear_button.TabIndex = 22;
            this.voteClear_button.Text = "清除";
            this.voteClear_button.UseVisualStyleBackColor = true;
            this.voteClear_button.Click += new System.EventHandler(this.voteClear_button_Click);
            // 
            // msClear_button
            // 
            this.msClear_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.msClear_button.Location = new System.Drawing.Point(245, 369);
            this.msClear_button.Name = "msClear_button";
            this.msClear_button.Size = new System.Drawing.Size(75, 31);
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
            this.comboBox1.Location = new System.Drawing.Point(106, 655);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 29);
            this.comboBox1.TabIndex = 24;
            // 
            // screen_set_label
            // 
            this.screen_set_label.AutoSize = true;
            this.screen_set_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.screen_set_label.Location = new System.Drawing.Point(14, 658);
            this.screen_set_label.Name = "screen_set_label";
            this.screen_set_label.Size = new System.Drawing.Size(78, 21);
            this.screen_set_label.TabIndex = 25;
            this.screen_set_label.Text = "屏幕设置:";
            // 
            // listView1
            // 
            this.listView1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.listView1.FullRowSelect = true;
            this.listView1.GridLines = true;
            this.listView1.Location = new System.Drawing.Point(16, 10);
            this.listView1.Margin = new System.Windows.Forms.Padding(2);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(336, 126);
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
            this.comboBox2.Location = new System.Drawing.Point(7, 242);
            this.comboBox2.Margin = new System.Windows.Forms.Padding(2);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(92, 28);
            this.comboBox2.TabIndex = 27;
            // 
            // slave_listView
            // 
            this.slave_listView.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_listView.FullRowSelect = true;
            this.slave_listView.GridLines = true;
            this.slave_listView.Location = new System.Drawing.Point(472, 10);
            this.slave_listView.Margin = new System.Windows.Forms.Padding(2);
            this.slave_listView.Name = "slave_listView";
            this.slave_listView.Size = new System.Drawing.Size(355, 126);
            this.slave_listView.TabIndex = 28;
            this.slave_listView.UseCompatibleStateImageBehavior = false;
            this.slave_listView.View = System.Windows.Forms.View.Details;
            // 
            // dongle_san_button
            // 
            this.dongle_san_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.dongle_san_button.Location = new System.Drawing.Point(472, 156);
            this.dongle_san_button.Margin = new System.Windows.Forms.Padding(2);
            this.dongle_san_button.Name = "dongle_san_button";
            this.dongle_san_button.Size = new System.Drawing.Size(76, 36);
            this.dongle_san_button.TabIndex = 29;
            this.dongle_san_button.Text = "开始扫描";
            this.dongle_san_button.UseVisualStyleBackColor = true;
            this.dongle_san_button.Click += new System.EventHandler(this.dongle_san_button_Click);
            // 
            // dongle_stopsan_button
            // 
            this.dongle_stopsan_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.dongle_stopsan_button.Location = new System.Drawing.Point(568, 156);
            this.dongle_stopsan_button.Margin = new System.Windows.Forms.Padding(2);
            this.dongle_stopsan_button.Name = "dongle_stopsan_button";
            this.dongle_stopsan_button.Size = new System.Drawing.Size(72, 36);
            this.dongle_stopsan_button.TabIndex = 29;
            this.dongle_stopsan_button.Text = "停止扫描";
            this.dongle_stopsan_button.UseVisualStyleBackColor = true;
            this.dongle_stopsan_button.Click += new System.EventHandler(this.dongle_stopsan_button_Click);
            // 
            // dg_con_button
            // 
            this.dg_con_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.dg_con_button.Location = new System.Drawing.Point(658, 156);
            this.dg_con_button.Margin = new System.Windows.Forms.Padding(2);
            this.dg_con_button.Name = "dg_con_button";
            this.dg_con_button.Size = new System.Drawing.Size(81, 36);
            this.dg_con_button.TabIndex = 29;
            this.dg_con_button.Text = "连接";
            this.dg_con_button.UseVisualStyleBackColor = true;
            this.dg_con_button.Click += new System.EventHandler(this.dg_con_button_Click);
            // 
            // dg_discon_button
            // 
            this.dg_discon_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.dg_discon_button.Location = new System.Drawing.Point(756, 156);
            this.dg_discon_button.Margin = new System.Windows.Forms.Padding(2);
            this.dg_discon_button.Name = "dg_discon_button";
            this.dg_discon_button.Size = new System.Drawing.Size(70, 36);
            this.dg_discon_button.TabIndex = 29;
            this.dg_discon_button.Text = "断开";
            this.dg_discon_button.UseVisualStyleBackColor = true;
            this.dg_discon_button.Click += new System.EventHandler(this.dg_discon_button_Click);
            // 
            // slave_ststus_label
            // 
            this.slave_ststus_label.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_ststus_label.Location = new System.Drawing.Point(472, 230);
            this.slave_ststus_label.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.slave_ststus_label.Name = "slave_ststus_label";
            this.slave_ststus_label.Size = new System.Drawing.Size(45, 29);
            this.slave_ststus_label.TabIndex = 30;
            this.slave_ststus_label.Text = "状态:";
            // 
            // slave_status_label1
            // 
            this.slave_status_label1.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_status_label1.Location = new System.Drawing.Point(514, 230);
            this.slave_status_label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.slave_status_label1.Name = "slave_status_label1";
            this.slave_status_label1.Size = new System.Drawing.Size(166, 23);
            this.slave_status_label1.TabIndex = 31;
            // 
            // slave_version_label
            // 
            this.slave_version_label.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_version_label.Location = new System.Drawing.Point(691, 230);
            this.slave_version_label.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.slave_version_label.Name = "slave_version_label";
            this.slave_version_label.Size = new System.Drawing.Size(45, 29);
            this.slave_version_label.TabIndex = 30;
            this.slave_version_label.Text = "版本:";
            // 
            // slave_version1_label
            // 
            this.slave_version1_label.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_version1_label.Location = new System.Drawing.Point(740, 230);
            this.slave_version1_label.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.slave_version1_label.Name = "slave_version1_label";
            this.slave_version1_label.Size = new System.Drawing.Size(128, 29);
            this.slave_version1_label.TabIndex = 30;
            // 
            // slave_name_textBox
            // 
            this.slave_name_textBox.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_name_textBox.Location = new System.Drawing.Point(469, 278);
            this.slave_name_textBox.Margin = new System.Windows.Forms.Padding(2);
            this.slave_name_textBox.Multiline = true;
            this.slave_name_textBox.Name = "slave_name_textBox";
            this.slave_name_textBox.Size = new System.Drawing.Size(109, 32);
            this.slave_name_textBox.TabIndex = 32;
            // 
            // slave_name_set_button
            // 
            this.slave_name_set_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_name_set_button.Location = new System.Drawing.Point(643, 278);
            this.slave_name_set_button.Margin = new System.Windows.Forms.Padding(2);
            this.slave_name_set_button.Name = "slave_name_set_button";
            this.slave_name_set_button.Size = new System.Drawing.Size(74, 28);
            this.slave_name_set_button.TabIndex = 33;
            this.slave_name_set_button.Text = "设置";
            this.slave_name_set_button.UseVisualStyleBackColor = true;
            this.slave_name_set_button.Click += new System.EventHandler(this.slave_name_set_button_Click);
            // 
            // adjust_button
            // 
            this.adjust_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.adjust_button.Location = new System.Drawing.Point(737, 278);
            this.adjust_button.Margin = new System.Windows.Forms.Padding(2);
            this.adjust_button.Name = "adjust_button";
            this.adjust_button.Size = new System.Drawing.Size(74, 28);
            this.adjust_button.TabIndex = 33;
            this.adjust_button.Text = "校准";
            this.adjust_button.UseVisualStyleBackColor = true;
            this.adjust_button.Click += new System.EventHandler(this.adjust_button_Click);
            // 
            // start_sync_button
            // 
            this.start_sync_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.start_sync_button.Location = new System.Drawing.Point(470, 354);
            this.start_sync_button.Margin = new System.Windows.Forms.Padding(2);
            this.start_sync_button.Name = "start_sync_button";
            this.start_sync_button.Size = new System.Drawing.Size(74, 28);
            this.start_sync_button.TabIndex = 33;
            this.start_sync_button.Text = "开始同步";
            this.start_sync_button.UseVisualStyleBackColor = true;
            this.start_sync_button.Click += new System.EventHandler(this.start_sync_button_Click);
            // 
            // end_sync_button
            // 
            this.end_sync_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.end_sync_button.Location = new System.Drawing.Point(579, 354);
            this.end_sync_button.Margin = new System.Windows.Forms.Padding(2);
            this.end_sync_button.Name = "end_sync_button";
            this.end_sync_button.Size = new System.Drawing.Size(74, 28);
            this.end_sync_button.TabIndex = 33;
            this.end_sync_button.Text = "结束同步";
            this.end_sync_button.UseVisualStyleBackColor = true;
            this.end_sync_button.Click += new System.EventHandler(this.end_sync_button_Click);
            // 
            // offline_label
            // 
            this.offline_label.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.offline_label.Location = new System.Drawing.Point(671, 354);
            this.offline_label.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.offline_label.Name = "offline_label";
            this.offline_label.Size = new System.Drawing.Size(140, 29);
            this.offline_label.TabIndex = 30;
            this.offline_label.Text = "离线笔记:";
            this.offline_label.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // button4
            // 
            this.button4.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button4.Location = new System.Drawing.Point(7, 281);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(93, 33);
            this.button4.TabIndex = 35;
            this.button4.Text = "开始同步";
            this.button4.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // labelnote
            // 
            this.labelnote.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelnote.Location = new System.Drawing.Point(130, 287);
            this.labelnote.Name = "labelnote";
            this.labelnote.Size = new System.Drawing.Size(191, 23);
            this.labelnote.TabIndex = 36;
            // 
            // label_sync_offline_tip
            // 
            this.label_sync_offline_tip.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_sync_offline_tip.Location = new System.Drawing.Point(134, 257);
            this.label_sync_offline_tip.Name = "label_sync_offline_tip";
            this.label_sync_offline_tip.Size = new System.Drawing.Size(164, 23);
            this.label_sync_offline_tip.TabIndex = 37;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(846, 708);
            this.Controls.Add(this.label_sync_offline_tip);
            this.Controls.Add(this.labelnote);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.adjust_button);
            this.Controls.Add(this.end_sync_button);
            this.Controls.Add(this.start_sync_button);
            this.Controls.Add(this.slave_name_set_button);
            this.Controls.Add(this.slave_name_textBox);
            this.Controls.Add(this.slave_status_label1);
            this.Controls.Add(this.slave_version1_label);
            this.Controls.Add(this.slave_version_label);
            this.Controls.Add(this.offline_label);
            this.Controls.Add(this.slave_ststus_label);
            this.Controls.Add(this.dg_discon_button);
            this.Controls.Add(this.dg_con_button);
            this.Controls.Add(this.dongle_stopsan_button);
            this.Controls.Add(this.dongle_san_button);
            this.Controls.Add(this.slave_listView);
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
        private System.Windows.Forms.ListView slave_listView;
        private System.Windows.Forms.Button dongle_san_button;
        private System.Windows.Forms.Button dongle_stopsan_button;
        private System.Windows.Forms.Button dg_con_button;
        private System.Windows.Forms.Button dg_discon_button;
        private System.Windows.Forms.Label slave_ststus_label;
        private System.Windows.Forms.Label slave_status_label1;
        private System.Windows.Forms.Label slave_version_label;
        private System.Windows.Forms.Label slave_version1_label;
        private System.Windows.Forms.TextBox slave_name_textBox;
        private System.Windows.Forms.Button slave_name_set_button;
        private System.Windows.Forms.Button adjust_button;
        private System.Windows.Forms.Button start_sync_button;
        private System.Windows.Forms.Button end_sync_button;
        private System.Windows.Forms.Label offline_label;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Label labelnote;
        private System.Windows.Forms.Label label_sync_offline_tip;
    }
}

