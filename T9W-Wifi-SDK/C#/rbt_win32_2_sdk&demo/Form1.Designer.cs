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
            this.button_start_stop = new System.Windows.Forms.Button();
            this.button_answer = new System.Windows.Forms.Button();
            this.listView1 = new System.Windows.Forms.ListView();
            this.label_tip = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // button_start_stop
            // 
            this.button_start_stop.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_start_stop.Location = new System.Drawing.Point(12, 12);
            this.button_start_stop.Name = "button_start_stop";
            this.button_start_stop.Size = new System.Drawing.Size(97, 31);
            this.button_start_stop.TabIndex = 0;
            this.button_start_stop.Text = "开始";
            this.button_start_stop.UseVisualStyleBackColor = true;
            this.button_start_stop.Click += new System.EventHandler(this.button_start_stop_Click);
            // 
            // button_answer
            // 
            this.button_answer.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_answer.Location = new System.Drawing.Point(148, 12);
            this.button_answer.Name = "button_answer";
            this.button_answer.Size = new System.Drawing.Size(102, 31);
            this.button_answer.TabIndex = 1;
            this.button_answer.Text = "开始答题";
            this.button_answer.UseVisualStyleBackColor = true;
            this.button_answer.Click += new System.EventHandler(this.button_answer_Click);
            // 
            // listView1
            // 
            this.listView1.FullRowSelect = true;
            this.listView1.GridLines = true;
            this.listView1.Location = new System.Drawing.Point(13, 49);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(604, 489);
            this.listView1.TabIndex = 2;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.DoubleClick += new System.EventHandler(this.listView1_DoubleClick);
            // 
            // label_tip
            // 
            this.label_tip.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_tip.ForeColor = System.Drawing.Color.Red;
            this.label_tip.Location = new System.Drawing.Point(132, 545);
            this.label_tip.Name = "label_tip";
            this.label_tip.Size = new System.Drawing.Size(347, 23);
            this.label_tip.TabIndex = 3;
            this.label_tip.Text = "双击设备行打开画布";
            this.label_tip.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(629, 573);
            this.Controls.Add(this.label_tip);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.button_answer);
            this.Controls.Add(this.button_start_stop);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_start_stop;
        private System.Windows.Forms.Button button_answer;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.Label label_tip;
    }
}

