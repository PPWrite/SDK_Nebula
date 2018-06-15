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
            this.slave_name_textBox = new System.Windows.Forms.TextBox();
            this.slave_name_set_button = new System.Windows.Forms.Button();
            this.adjust_button = new System.Windows.Forms.Button();
            this.start_sync_button = new System.Windows.Forms.Button();
            this.end_sync_button = new System.Windows.Forms.Button();
            this.offline_label = new System.Windows.Forms.Label();
            this.StartSyncBtn = new System.Windows.Forms.Button();
            this.labelnote = new System.Windows.Forms.Label();
            this.label_sync_offline_tip = new System.Windows.Forms.Label();
            this.BaseGroup = new System.Windows.Forms.GroupBox();
            this.mode_label = new System.Windows.Forms.Label();
            this.mac_label_show = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.BaseOpenOfflineNote = new System.Windows.Forms.Button();
            this.EndSyncBtn = new System.Windows.Forms.Button();
            this.BLEGroup = new System.Windows.Forms.GroupBox();
            this.BleOpenOfflineNote = new System.Windows.Forms.Button();
            this.slave_version1_label = new System.Windows.Forms.Label();
            this.slave_version_label = new System.Windows.Forms.Label();
            this.GATEWAYGroup = new System.Windows.Forms.GroupBox();
            this.USBOfflineGroup = new System.Windows.Forms.GroupBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripProgressBar1 = new System.Windows.Forms.ToolStripProgressBar();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.SwichModeBtn = new System.Windows.Forms.Button();
            this.BaseGroup.SuspendLayout();
            this.BLEGroup.SuspendLayout();
            this.GATEWAYGroup.SuspendLayout();
            this.USBOfflineGroup.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button1.Location = new System.Drawing.Point(7, 57);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(93, 28);
            this.button1.TabIndex = 0;
            this.button1.Text = "开始投票";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button2.Location = new System.Drawing.Point(106, 57);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(93, 28);
            this.button2.TabIndex = 1;
            this.button2.Text = "结束投票";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // status_label
            // 
            this.status_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.status_label.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(255)))));
            this.status_label.Location = new System.Drawing.Point(219, 81);
            this.status_label.Name = "status_label";
            this.status_label.Size = new System.Drawing.Size(266, 25);
            this.status_label.TabIndex = 2;
            this.status_label.Text = "状态";
            // 
            // Error_label
            // 
            this.Error_label.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Error_label.Location = new System.Drawing.Point(21, 115);
            this.Error_label.Name = "Error_label";
            this.Error_label.Size = new System.Drawing.Size(188, 23);
            this.Error_label.TabIndex = 3;
            this.Error_label.Text = "操作提示";
            // 
            // open_button
            // 
            this.open_button.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.open_button.Cursor = System.Windows.Forms.Cursors.Hand;
            this.open_button.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.open_button.Location = new System.Drawing.Point(15, 20);
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
            this.version_label.Location = new System.Drawing.Point(125, 24);
            this.version_label.Name = "version_label";
            this.version_label.Size = new System.Drawing.Size(82, 21);
            this.version_label.TabIndex = 6;
            this.version_label.Text = "版  本  号:";
            // 
            // version_label_show
            // 
            this.version_label_show.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.version_label_show.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
            this.version_label_show.Location = new System.Drawing.Point(219, 24);
            this.version_label_show.Name = "version_label_show";
            this.version_label_show.Size = new System.Drawing.Size(184, 23);
            this.version_label_show.TabIndex = 7;
            this.version_label_show.Text = "版本号";
            // 
            // status_button_query
            // 
            this.status_button_query.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.status_button_query.Cursor = System.Windows.Forms.Cursors.Hand;
            this.status_button_query.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.status_button_query.Location = new System.Drawing.Point(15, 70);
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
            this.status_label_title.Location = new System.Drawing.Point(125, 81);
            this.status_label_title.Name = "status_label_title";
            this.status_label_title.Size = new System.Drawing.Size(83, 21);
            this.status_label_title.TabIndex = 9;
            this.status_label_title.Text = "设备 状态:";
            // 
            // ns_start_button
            // 
            this.ns_start_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ns_start_button.Location = new System.Drawing.Point(7, 94);
            this.ns_start_button.Name = "ns_start_button";
            this.ns_start_button.Size = new System.Drawing.Size(93, 28);
            this.ns_start_button.TabIndex = 10;
            this.ns_start_button.Text = "ms模式";
            this.ns_start_button.UseVisualStyleBackColor = true;
            this.ns_start_button.Click += new System.EventHandler(this.ns_start_button_Click);
            // 
            // ms_end_button
            // 
            this.ms_end_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ms_end_button.Location = new System.Drawing.Point(106, 94);
            this.ms_end_button.Name = "ms_end_button";
            this.ms_end_button.Size = new System.Drawing.Size(93, 28);
            this.ms_end_button.TabIndex = 11;
            this.ms_end_button.Text = "结束MS模式";
            this.ms_end_button.UseVisualStyleBackColor = true;
            this.ms_end_button.Click += new System.EventHandler(this.ms_end_button_Click);
            // 
            // set_button
            // 
            this.set_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.set_button.Location = new System.Drawing.Point(16, 30);
            this.set_button.Name = "set_button";
            this.set_button.Size = new System.Drawing.Size(93, 28);
            this.set_button.TabIndex = 12;
            this.set_button.Text = "设置";
            this.set_button.UseVisualStyleBackColor = true;
            this.set_button.Click += new System.EventHandler(this.set_button_Click);
            // 
            // custom_label
            // 
            this.custom_label.AutoSize = true;
            this.custom_label.BackColor = System.Drawing.Color.Transparent;
            this.custom_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.custom_label.Location = new System.Drawing.Point(18, 65);
            this.custom_label.Name = "custom_label";
            this.custom_label.Size = new System.Drawing.Size(108, 21);
            this.custom_label.TabIndex = 13;
            this.custom_label.Text = "customNum:";
            // 
            // class_label
            // 
            this.class_label.AutoSize = true;
            this.class_label.BackColor = System.Drawing.Color.Transparent;
            this.class_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.class_label.Location = new System.Drawing.Point(39, 102);
            this.class_label.Name = "class_label";
            this.class_label.Size = new System.Drawing.Size(87, 21);
            this.class_label.TabIndex = 14;
            this.class_label.Text = "classNum:";
            this.class_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // device_label
            // 
            this.device_label.AutoSize = true;
            this.device_label.BackColor = System.Drawing.Color.Transparent;
            this.device_label.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.device_label.Location = new System.Drawing.Point(26, 138);
            this.device_label.Name = "device_label";
            this.device_label.Size = new System.Drawing.Size(100, 21);
            this.device_label.TabIndex = 15;
            this.device_label.Text = "deviceNum:";
            this.device_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // class_textBox
            // 
            this.class_textBox.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.class_textBox.Location = new System.Drawing.Point(132, 99);
            this.class_textBox.Name = "class_textBox";
            this.class_textBox.ReadOnly = true;
            this.class_textBox.Size = new System.Drawing.Size(175, 29);
            this.class_textBox.TabIndex = 16;
            this.class_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // device_textBox
            // 
            this.device_textBox.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.device_textBox.Location = new System.Drawing.Point(132, 135);
            this.device_textBox.Name = "device_textBox";
            this.device_textBox.ReadOnly = true;
            this.device_textBox.Size = new System.Drawing.Size(175, 29);
            this.device_textBox.TabIndex = 17;
            this.device_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // custom_textBox
            // 
            this.custom_textBox.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.custom_textBox.Location = new System.Drawing.Point(132, 62);
            this.custom_textBox.Name = "custom_textBox";
            this.custom_textBox.ReadOnly = true;
            this.custom_textBox.Size = new System.Drawing.Size(175, 29);
            this.custom_textBox.TabIndex = 18;
            this.custom_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // update_button
            // 
            this.update_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.update_button.Location = new System.Drawing.Point(220, 143);
            this.update_button.Name = "update_button";
            this.update_button.Size = new System.Drawing.Size(93, 28);
            this.update_button.TabIndex = 19;
            this.update_button.Text = "升级";
            this.update_button.UseVisualStyleBackColor = true;
            this.update_button.Click += new System.EventHandler(this.update_button_Click);
            // 
            // mode_label_tip
            // 
            this.mode_label_tip.AutoSize = true;
            this.mode_label_tip.Location = new System.Drawing.Point(219, 115);
            this.mode_label_tip.Name = "mode_label_tip";
            this.mode_label_tip.Size = new System.Drawing.Size(74, 19);
            this.mode_label_tip.TabIndex = 20;
            this.mode_label_tip.Text = "连接模式：";
            // 
            // voteClear_button
            // 
            this.voteClear_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.voteClear_button.Location = new System.Drawing.Point(205, 57);
            this.voteClear_button.Name = "voteClear_button";
            this.voteClear_button.Size = new System.Drawing.Size(93, 28);
            this.voteClear_button.TabIndex = 22;
            this.voteClear_button.Text = "清除";
            this.voteClear_button.UseVisualStyleBackColor = true;
            this.voteClear_button.Click += new System.EventHandler(this.voteClear_button_Click);
            // 
            // msClear_button
            // 
            this.msClear_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.msClear_button.Location = new System.Drawing.Point(205, 94);
            this.msClear_button.Name = "msClear_button";
            this.msClear_button.Size = new System.Drawing.Size(93, 28);
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
            this.comboBox1.Location = new System.Drawing.Point(93, 142);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 29);
            this.comboBox1.TabIndex = 24;
            // 
            // screen_set_label
            // 
            this.screen_set_label.AutoSize = true;
            this.screen_set_label.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.screen_set_label.Location = new System.Drawing.Point(20, 145);
            this.screen_set_label.Name = "screen_set_label";
            this.screen_set_label.Size = new System.Drawing.Size(64, 19);
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
            this.listView1.Size = new System.Drawing.Size(497, 117);
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
            this.comboBox2.Location = new System.Drawing.Point(7, 23);
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
            this.slave_listView.Location = new System.Drawing.Point(12, 29);
            this.slave_listView.Margin = new System.Windows.Forms.Padding(2);
            this.slave_listView.Name = "slave_listView";
            this.slave_listView.Size = new System.Drawing.Size(472, 126);
            this.slave_listView.TabIndex = 28;
            this.slave_listView.UseCompatibleStateImageBehavior = false;
            this.slave_listView.View = System.Windows.Forms.View.Details;
            // 
            // dongle_san_button
            // 
            this.dongle_san_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.dongle_san_button.Location = new System.Drawing.Point(13, 164);
            this.dongle_san_button.Margin = new System.Windows.Forms.Padding(2);
            this.dongle_san_button.Name = "dongle_san_button";
            this.dongle_san_button.Size = new System.Drawing.Size(93, 28);
            this.dongle_san_button.TabIndex = 29;
            this.dongle_san_button.Text = "开始扫描";
            this.dongle_san_button.UseVisualStyleBackColor = true;
            this.dongle_san_button.Click += new System.EventHandler(this.dongle_san_button_Click);
            // 
            // dongle_stopsan_button
            // 
            this.dongle_stopsan_button.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.dongle_stopsan_button.Location = new System.Drawing.Point(110, 164);
            this.dongle_stopsan_button.Margin = new System.Windows.Forms.Padding(2);
            this.dongle_stopsan_button.Name = "dongle_stopsan_button";
            this.dongle_stopsan_button.Size = new System.Drawing.Size(93, 28);
            this.dongle_stopsan_button.TabIndex = 29;
            this.dongle_stopsan_button.Text = "停止扫描";
            this.dongle_stopsan_button.UseVisualStyleBackColor = true;
            this.dongle_stopsan_button.Click += new System.EventHandler(this.dongle_stopsan_button_Click);
            // 
            // dg_con_button
            // 
            this.dg_con_button.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.dg_con_button.Location = new System.Drawing.Point(207, 164);
            this.dg_con_button.Margin = new System.Windows.Forms.Padding(2);
            this.dg_con_button.Name = "dg_con_button";
            this.dg_con_button.Size = new System.Drawing.Size(93, 28);
            this.dg_con_button.TabIndex = 29;
            this.dg_con_button.Text = "连接";
            this.dg_con_button.UseVisualStyleBackColor = true;
            this.dg_con_button.Click += new System.EventHandler(this.dg_con_button_Click);
            // 
            // dg_discon_button
            // 
            this.dg_discon_button.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.dg_discon_button.Location = new System.Drawing.Point(304, 164);
            this.dg_discon_button.Margin = new System.Windows.Forms.Padding(2);
            this.dg_discon_button.Name = "dg_discon_button";
            this.dg_discon_button.Size = new System.Drawing.Size(93, 28);
            this.dg_discon_button.TabIndex = 29;
            this.dg_discon_button.Text = "断开";
            this.dg_discon_button.UseVisualStyleBackColor = true;
            this.dg_discon_button.Click += new System.EventHandler(this.dg_discon_button_Click);
            // 
            // slave_ststus_label
            // 
            this.slave_ststus_label.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_ststus_label.Location = new System.Drawing.Point(12, 203);
            this.slave_ststus_label.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.slave_ststus_label.Name = "slave_ststus_label";
            this.slave_ststus_label.Size = new System.Drawing.Size(68, 21);
            this.slave_ststus_label.TabIndex = 30;
            this.slave_ststus_label.Text = "设备 状态:";
            // 
            // slave_status_label1
            // 
            this.slave_status_label1.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_status_label1.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
            this.slave_status_label1.Location = new System.Drawing.Point(88, 203);
            this.slave_status_label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.slave_status_label1.Name = "slave_status_label1";
            this.slave_status_label1.Size = new System.Drawing.Size(166, 23);
            this.slave_status_label1.TabIndex = 31;
            this.slave_status_label1.Text = "设备状态";
            // 
            // slave_name_textBox
            // 
            this.slave_name_textBox.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_name_textBox.Location = new System.Drawing.Point(13, 276);
            this.slave_name_textBox.Margin = new System.Windows.Forms.Padding(2);
            this.slave_name_textBox.Multiline = true;
            this.slave_name_textBox.Name = "slave_name_textBox";
            this.slave_name_textBox.Size = new System.Drawing.Size(154, 28);
            this.slave_name_textBox.TabIndex = 32;
            // 
            // slave_name_set_button
            // 
            this.slave_name_set_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_name_set_button.Location = new System.Drawing.Point(171, 276);
            this.slave_name_set_button.Margin = new System.Windows.Forms.Padding(2);
            this.slave_name_set_button.Name = "slave_name_set_button";
            this.slave_name_set_button.Size = new System.Drawing.Size(93, 28);
            this.slave_name_set_button.TabIndex = 33;
            this.slave_name_set_button.Text = "设置";
            this.slave_name_set_button.UseVisualStyleBackColor = true;
            this.slave_name_set_button.Click += new System.EventHandler(this.slave_name_set_button_Click);
            // 
            // adjust_button
            // 
            this.adjust_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.adjust_button.Location = new System.Drawing.Point(268, 276);
            this.adjust_button.Margin = new System.Windows.Forms.Padding(2);
            this.adjust_button.Name = "adjust_button";
            this.adjust_button.Size = new System.Drawing.Size(93, 28);
            this.adjust_button.TabIndex = 33;
            this.adjust_button.Text = "校准";
            this.adjust_button.UseVisualStyleBackColor = true;
            this.adjust_button.Click += new System.EventHandler(this.adjust_button_Click);
            // 
            // start_sync_button
            // 
            this.start_sync_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.start_sync_button.Location = new System.Drawing.Point(114, 323);
            this.start_sync_button.Margin = new System.Windows.Forms.Padding(2);
            this.start_sync_button.Name = "start_sync_button";
            this.start_sync_button.Size = new System.Drawing.Size(93, 28);
            this.start_sync_button.TabIndex = 33;
            this.start_sync_button.Text = "开始同步";
            this.start_sync_button.UseVisualStyleBackColor = true;
            this.start_sync_button.Visible = false;
            this.start_sync_button.Click += new System.EventHandler(this.start_sync_button_Click);
            // 
            // end_sync_button
            // 
            this.end_sync_button.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.end_sync_button.Location = new System.Drawing.Point(211, 323);
            this.end_sync_button.Margin = new System.Windows.Forms.Padding(2);
            this.end_sync_button.Name = "end_sync_button";
            this.end_sync_button.Size = new System.Drawing.Size(93, 28);
            this.end_sync_button.TabIndex = 33;
            this.end_sync_button.Text = "结束同步";
            this.end_sync_button.UseVisualStyleBackColor = true;
            this.end_sync_button.Visible = false;
            this.end_sync_button.Click += new System.EventHandler(this.end_sync_button_Click);
            // 
            // offline_label
            // 
            this.offline_label.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.offline_label.Location = new System.Drawing.Point(12, 360);
            this.offline_label.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.offline_label.Name = "offline_label";
            this.offline_label.Size = new System.Drawing.Size(140, 29);
            this.offline_label.TabIndex = 30;
            this.offline_label.Text = "离线笔记:";
            this.offline_label.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // StartSyncBtn
            // 
            this.StartSyncBtn.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.StartSyncBtn.Location = new System.Drawing.Point(112, 22);
            this.StartSyncBtn.Name = "StartSyncBtn";
            this.StartSyncBtn.Size = new System.Drawing.Size(93, 28);
            this.StartSyncBtn.TabIndex = 35;
            this.StartSyncBtn.Text = "开始同步";
            this.StartSyncBtn.UseVisualStyleBackColor = true;
            this.StartSyncBtn.Visible = false;
            this.StartSyncBtn.Click += new System.EventHandler(this.button4_Click);
            // 
            // labelnote
            // 
            this.labelnote.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelnote.Location = new System.Drawing.Point(16, 60);
            this.labelnote.Name = "labelnote";
            this.labelnote.Size = new System.Drawing.Size(187, 24);
            this.labelnote.TabIndex = 36;
            this.labelnote.Text = "离线笔记条数";
            // 
            // label_sync_offline_tip
            // 
            this.label_sync_offline_tip.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_sync_offline_tip.ForeColor = System.Drawing.Color.Red;
            this.label_sync_offline_tip.Location = new System.Drawing.Point(20, 90);
            this.label_sync_offline_tip.Name = "label_sync_offline_tip";
            this.label_sync_offline_tip.Size = new System.Drawing.Size(164, 23);
            this.label_sync_offline_tip.TabIndex = 37;
            // 
            // BaseGroup
            // 
            this.BaseGroup.Controls.Add(this.SwichModeBtn);
            this.BaseGroup.Controls.Add(this.mode_label);
            this.BaseGroup.Controls.Add(this.screen_set_label);
            this.BaseGroup.Controls.Add(this.comboBox1);
            this.BaseGroup.Controls.Add(this.mac_label_show);
            this.BaseGroup.Controls.Add(this.label1);
            this.BaseGroup.Controls.Add(this.mode_label_tip);
            this.BaseGroup.Controls.Add(this.open_button);
            this.BaseGroup.Controls.Add(this.update_button);
            this.BaseGroup.Controls.Add(this.status_button_query);
            this.BaseGroup.Controls.Add(this.version_label);
            this.BaseGroup.Controls.Add(this.version_label_show);
            this.BaseGroup.Controls.Add(this.status_label_title);
            this.BaseGroup.Controls.Add(this.status_label);
            this.BaseGroup.Controls.Add(this.Error_label);
            this.BaseGroup.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BaseGroup.Location = new System.Drawing.Point(18, 132);
            this.BaseGroup.Name = "BaseGroup";
            this.BaseGroup.Size = new System.Drawing.Size(495, 182);
            this.BaseGroup.TabIndex = 38;
            this.BaseGroup.TabStop = false;
            this.BaseGroup.Text = "BaseGroup";
            // 
            // mode_label
            // 
            this.mode_label.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
            this.mode_label.Location = new System.Drawing.Point(289, 113);
            this.mode_label.Name = "mode_label";
            this.mode_label.Size = new System.Drawing.Size(157, 23);
            this.mode_label.TabIndex = 38;
            this.mode_label.Text = "USB";
            this.mode_label.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // mac_label_show
            // 
            this.mac_label_show.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.mac_label_show.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
            this.mac_label_show.Location = new System.Drawing.Point(219, 52);
            this.mac_label_show.Name = "mac_label_show";
            this.mac_label_show.Size = new System.Drawing.Size(184, 23);
            this.mac_label_show.TabIndex = 29;
            this.mac_label_show.Text = "mac地址";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(255)))));
            this.label1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(125, 52);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(83, 21);
            this.label1.TabIndex = 28;
            this.label1.Text = "mac 地址:";
            // 
            // BaseOpenOfflineNote
            // 
            this.BaseOpenOfflineNote.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BaseOpenOfflineNote.Location = new System.Drawing.Point(11, 22);
            this.BaseOpenOfflineNote.Name = "BaseOpenOfflineNote";
            this.BaseOpenOfflineNote.Size = new System.Drawing.Size(96, 28);
            this.BaseOpenOfflineNote.TabIndex = 30;
            this.BaseOpenOfflineNote.Text = "打开离线笔记";
            this.BaseOpenOfflineNote.UseVisualStyleBackColor = true;
            this.BaseOpenOfflineNote.Click += new System.EventHandler(this.BaseOpenOfflineNote_Click);
            // 
            // EndSyncBtn
            // 
            this.EndSyncBtn.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.EndSyncBtn.Location = new System.Drawing.Point(211, 22);
            this.EndSyncBtn.Name = "EndSyncBtn";
            this.EndSyncBtn.Size = new System.Drawing.Size(93, 28);
            this.EndSyncBtn.TabIndex = 36;
            this.EndSyncBtn.Text = "结束同步";
            this.EndSyncBtn.UseVisualStyleBackColor = true;
            this.EndSyncBtn.Visible = false;
            this.EndSyncBtn.Click += new System.EventHandler(this.EndSyncBtn_Click);
            // 
            // BLEGroup
            // 
            this.BLEGroup.Controls.Add(this.BleOpenOfflineNote);
            this.BLEGroup.Controls.Add(this.end_sync_button);
            this.BLEGroup.Controls.Add(this.start_sync_button);
            this.BLEGroup.Controls.Add(this.offline_label);
            this.BLEGroup.Controls.Add(this.adjust_button);
            this.BLEGroup.Controls.Add(this.slave_listView);
            this.BLEGroup.Controls.Add(this.dongle_san_button);
            this.BLEGroup.Controls.Add(this.dongle_stopsan_button);
            this.BLEGroup.Controls.Add(this.slave_name_set_button);
            this.BLEGroup.Controls.Add(this.dg_con_button);
            this.BLEGroup.Controls.Add(this.slave_name_textBox);
            this.BLEGroup.Controls.Add(this.dg_discon_button);
            this.BLEGroup.Controls.Add(this.slave_ststus_label);
            this.BLEGroup.Controls.Add(this.slave_status_label1);
            this.BLEGroup.Controls.Add(this.slave_version1_label);
            this.BLEGroup.Controls.Add(this.slave_version_label);
            this.BLEGroup.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BLEGroup.Location = new System.Drawing.Point(524, 162);
            this.BLEGroup.Name = "BLEGroup";
            this.BLEGroup.Size = new System.Drawing.Size(497, 411);
            this.BLEGroup.TabIndex = 39;
            this.BLEGroup.TabStop = false;
            this.BLEGroup.Text = "BLEGroup";
            this.BLEGroup.Visible = false;
            // 
            // BleOpenOfflineNote
            // 
            this.BleOpenOfflineNote.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.BleOpenOfflineNote.Location = new System.Drawing.Point(13, 323);
            this.BleOpenOfflineNote.Name = "BleOpenOfflineNote";
            this.BleOpenOfflineNote.Size = new System.Drawing.Size(96, 28);
            this.BleOpenOfflineNote.TabIndex = 34;
            this.BleOpenOfflineNote.Text = "打开离线笔记";
            this.BleOpenOfflineNote.UseVisualStyleBackColor = true;
            this.BleOpenOfflineNote.Click += new System.EventHandler(this.BleOpenOfflineNote_Click);
            // 
            // slave_version1_label
            // 
            this.slave_version1_label.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_version1_label.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
            this.slave_version1_label.Location = new System.Drawing.Point(88, 231);
            this.slave_version1_label.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.slave_version1_label.Name = "slave_version1_label";
            this.slave_version1_label.Size = new System.Drawing.Size(128, 28);
            this.slave_version1_label.TabIndex = 30;
            this.slave_version1_label.Text = "版本号";
            // 
            // slave_version_label
            // 
            this.slave_version_label.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.slave_version_label.Location = new System.Drawing.Point(12, 231);
            this.slave_version_label.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.slave_version_label.Name = "slave_version_label";
            this.slave_version_label.Size = new System.Drawing.Size(68, 29);
            this.slave_version_label.TabIndex = 30;
            this.slave_version_label.Text = "版  本  号:";
            // 
            // GATEWAYGroup
            // 
            this.GATEWAYGroup.Controls.Add(this.button1);
            this.GATEWAYGroup.Controls.Add(this.button2);
            this.GATEWAYGroup.Controls.Add(this.ns_start_button);
            this.GATEWAYGroup.Controls.Add(this.comboBox2);
            this.GATEWAYGroup.Controls.Add(this.ms_end_button);
            this.GATEWAYGroup.Controls.Add(this.msClear_button);
            this.GATEWAYGroup.Controls.Add(this.voteClear_button);
            this.GATEWAYGroup.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.GATEWAYGroup.Location = new System.Drawing.Point(524, 12);
            this.GATEWAYGroup.Name = "GATEWAYGroup";
            this.GATEWAYGroup.Size = new System.Drawing.Size(497, 144);
            this.GATEWAYGroup.TabIndex = 40;
            this.GATEWAYGroup.TabStop = false;
            this.GATEWAYGroup.Text = "GATEWAYGroup";
            this.GATEWAYGroup.Visible = false;
            // 
            // USBOfflineGroup
            // 
            this.USBOfflineGroup.Controls.Add(this.StartSyncBtn);
            this.USBOfflineGroup.Controls.Add(this.label_sync_offline_tip);
            this.USBOfflineGroup.Controls.Add(this.EndSyncBtn);
            this.USBOfflineGroup.Controls.Add(this.labelnote);
            this.USBOfflineGroup.Controls.Add(this.BaseOpenOfflineNote);
            this.USBOfflineGroup.Location = new System.Drawing.Point(18, 325);
            this.USBOfflineGroup.Name = "USBOfflineGroup";
            this.USBOfflineGroup.Size = new System.Drawing.Size(495, 132);
            this.USBOfflineGroup.TabIndex = 41;
            this.USBOfflineGroup.TabStop = false;
            this.USBOfflineGroup.Text = "USBOfflineGroup";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripProgressBar1,
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 669);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(1033, 22);
            this.statusStrip1.TabIndex = 42;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripProgressBar1
            // 
            this.toolStripProgressBar1.Name = "toolStripProgressBar1";
            this.toolStripProgressBar1.Size = new System.Drawing.Size(100, 16);
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(916, 17);
            this.toolStripStatusLabel1.Spring = true;
            this.toolStripStatusLabel1.Text = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.device_label);
            this.groupBox1.Controls.Add(this.device_textBox);
            this.groupBox1.Controls.Add(this.class_textBox);
            this.groupBox1.Controls.Add(this.custom_textBox);
            this.groupBox1.Controls.Add(this.class_label);
            this.groupBox1.Controls.Add(this.custom_label);
            this.groupBox1.Controls.Add(this.set_button);
            this.groupBox1.Font = new System.Drawing.Font("微软雅黑", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.Location = new System.Drawing.Point(18, 463);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(497, 187);
            this.groupBox1.TabIndex = 43;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "2.4GSetting";
            // 
            // SwichModeBtn
            // 
            this.SwichModeBtn.Location = new System.Drawing.Point(319, 142);
            this.SwichModeBtn.Name = "SwichModeBtn";
            this.SwichModeBtn.Size = new System.Drawing.Size(93, 28);
            this.SwichModeBtn.TabIndex = 39;
            this.SwichModeBtn.Text = "切换";
            this.SwichModeBtn.UseVisualStyleBackColor = true;
            this.SwichModeBtn.Visible = false;
            this.SwichModeBtn.Click += new System.EventHandler(this.SwichModeBtn_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1033, 691);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.USBOfflineGroup);
            this.Controls.Add(this.GATEWAYGroup);
            this.Controls.Add(this.BLEGroup);
            this.Controls.Add(this.BaseGroup);
            this.Controls.Add(this.listView1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.SizeChanged += new System.EventHandler(this.Form1_SizeChanged);
            this.BaseGroup.ResumeLayout(false);
            this.BaseGroup.PerformLayout();
            this.BLEGroup.ResumeLayout(false);
            this.BLEGroup.PerformLayout();
            this.GATEWAYGroup.ResumeLayout(false);
            this.USBOfflineGroup.ResumeLayout(false);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
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
        private System.Windows.Forms.TextBox slave_name_textBox;
        private System.Windows.Forms.Button slave_name_set_button;
        private System.Windows.Forms.Button adjust_button;
        private System.Windows.Forms.Button start_sync_button;
        private System.Windows.Forms.Button end_sync_button;
        private System.Windows.Forms.Label offline_label;
        private System.Windows.Forms.Button StartSyncBtn;
        private System.Windows.Forms.Label labelnote;
        private System.Windows.Forms.Label label_sync_offline_tip;
        private System.Windows.Forms.GroupBox BaseGroup;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button EndSyncBtn;
        private System.Windows.Forms.Button BaseOpenOfflineNote;
        private System.Windows.Forms.Label mac_label_show;
        private System.Windows.Forms.GroupBox BLEGroup;
        private System.Windows.Forms.Button BleOpenOfflineNote;
        private System.Windows.Forms.GroupBox GATEWAYGroup;
        private System.Windows.Forms.Label mode_label;
        private System.Windows.Forms.GroupBox USBOfflineGroup;
        private System.Windows.Forms.ToolStripProgressBar toolStripProgressBar1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.Label slave_version1_label;
        private System.Windows.Forms.Label slave_version_label;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button SwichModeBtn;
    }
}

