﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace rbt_win32_2_demo
{
    public partial class SettingPanel : Form
    {
        private Form1 form;

        private bool isStartConfigWifi = false;
        private bool isStartConfigSleep = false;
        public SettingPanel(Form1 _from)
        {
            form = _from;
            InitializeComponent();
        }

        private void textBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= ' ' && e.KeyChar <= '~') || e.KeyChar == '\b')
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void textBox_KeyPress_onlyNum(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= '0' && e.KeyChar <= '9') || (e.KeyChar == 8))
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(this.textBox1.Text))
            {
                int t = Form1.rbtnet_.configWifi(this.textBox1.Text, this.textBox2.Text, this.textBox3.Text);
                if (t == 0)
                {
                    isStartConfigWifi = true;
                    MessageBox.Show("配网成功");
                }
            }
            else
            {
                MessageBox.Show("wifi名称不能为空");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int num = 0;
            if (!string.IsNullOrEmpty(this.textBox4.Text))
            {
                num = int.Parse(this.textBox4.Text);
                Form1.rbtnet_.configSleep(num);
                isStartConfigSleep = true;
            }
            else
            {
                MessageBox.Show("时间不能为空");
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(this.textBox1.Text)&& isStartConfigWifi)
            {
                int t = Form1.rbtnet_.configWifi(this.textBox1.Text, this.textBox2.Text, this.textBox3.Text);
            }
            if (!string.IsNullOrEmpty(this.textBox4.Text)&& isStartConfigSleep)
            {
                int num = 0;
                num = int.Parse(this.textBox4.Text);
                Form1.rbtnet_.configSleep(num);
            }
        }
    }
}
