﻿using robotpenetdevice_cs;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace rbt_win32_2_demo
{
    public partial class SetStuName : Form
    {
        private string macNum = string.Empty;
        private string stuNum = string.Empty;
        private string stuName = string.Empty;
        private bool isSubChinese = false;
        private Form1 form;
        /// <summary>
        /// 初始化传入是否是支持中文的操作
        /// </summary>
        public SetStuName(bool subChinese,string macStr,string _stuNum, string _stuName, Form1 _from)
        {
            isSubChinese = subChinese;
            stuNum = _stuNum;
            stuName = _stuName;
            macNum = macStr;
            form = _from;
            InitializeComponent();
        }
        private void SetStuName_Load(object sender, EventArgs e)
        {
            this.textBox1.Text = stuNum;
            this.textBox2.Text = stuName;
            if (isSubChinese)
            {
                this.Text += "(支持中文)";
                this.textBox2.Enabled = true;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(string.IsNullOrEmpty(macNum))
            {
                MessageBox.Show("mac地址不能为空");
            }
            if (string.IsNullOrEmpty(this.textBox1.Text))
            {
                MessageBox.Show("学生名称不能为空");
            }
            if(isSubChinese)
            {
                Form1.rbtnet_.configStu(macNum, this.textBox1.Text);
                Thread.Sleep(100);
                if (Form1.oemkey == "TY")
                {
                    Form1.rbtnet_.configBmpStu2(macNum, this.textBox2.Text);
                }
                else
                {
                    Form1.rbtnet_.configBmpStu(macNum, this.textBox1.Text, this.textBox2.Text);
                }
                form.UpdateListViewSelectedStuName(this.textBox1.Text, this.textBox2.Text);
            }
            else
            {
                Form1.rbtnet_.configStu(macNum, this.textBox1.Text);
                form.UpdateListViewSelectedStuName(this.textBox1.Text);
            }
            
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= 'a' && e.KeyChar <= 'z') || (e.KeyChar >= 'A' && e.KeyChar <= 'Z')
                || (e.KeyChar >= '0' && e.KeyChar <= '9') || (e.KeyChar == 8))
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }
    }
}
