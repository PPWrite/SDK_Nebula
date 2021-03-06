﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
//using System.Linq;
using System.Text;
using System.Windows.Forms;
using RobotpenGateway;

namespace RobotPenTestDll
{
    public partial class setForm : Form
    {

        private eDeviceType nDeviceM;
        public string strCustomNum { get; set; }
        public string strClassNum { get; set; }
        public string strDeviceNum { get; set; }

        public setForm(eDeviceType edevType, string strCustomNum, string strClassNum, string strDeviceNum)
        {
            InitializeComponent();
            if (edevType == eDeviceType.Gateway)
            {
                this.label3.Hide();
                this.textBox3.Hide();
            }

            nDeviceM = edevType;

            this.textBox1.Text = strCustomNum;
            this.textBox2.Text = strClassNum;
            if (nDeviceM != eDeviceType.Gateway)
            {
                this.textBox3.Text = strDeviceNum;
            }

            if (edevType == eDeviceType.Gateway)
            {
                this.textBox3.Hide();
                this.label3.Hide();
            }
        }

        // 点击确认
        private void button1_Click(object sender, EventArgs e)
        {
            strCustomNum = this.textBox1.Text;
            strClassNum = this.textBox2.Text;
            if (nDeviceM != eDeviceType.Gateway)
            {
                strDeviceNum = this.textBox3.Text;
                if (strDeviceNum == string.Empty)
                {
                    MessageBox.Show("设备号不能为空");
                    return;
                }

                int nDeviceNum = Convert.ToInt32(strDeviceNum);
                if (nDeviceNum > 59)
                {
                    MessageBox.Show("DeviceNum 不能大于59!");
                    return;
                }
            }

            if (strCustomNum == string.Empty || strClassNum == string.Empty)
            {
                MessageBox.Show("数据填写不完整");
                return;
            }
            else if (nDeviceM != 0 && strDeviceNum == string.Empty)
            {
                MessageBox.Show("数据填写不完整");
                return;
            }

            int nClassNum = Convert.ToInt32(strClassNum);
            if (nClassNum > 9)
            {
                MessageBox.Show("ClassNum 不能大于9!");
                return;
            }
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        // 点击取消
        private void button2_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != '\b')
            {
                if ((e.KeyChar < '0') || (e.KeyChar > '9'))
                {
                    e.Handled = true;
                }
            }
        }

        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != '\b')
            {
                if ((e.KeyChar < '0') || (e.KeyChar > '9'))
                {
                    e.Handled = true;
                }
            }
        }

        private void textBox3_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != '\b')
            {
                if ((e.KeyChar < '0') || (e.KeyChar > '9'))
                {
                    e.Handled = true;
                }
            }
        }

        // 数据
    }
}
