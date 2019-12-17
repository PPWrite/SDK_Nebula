using rbt_win32_2_demo;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace robopenetdevice_cs_demo
{
    public partial class SetFBMsg : Form
    {
        private string macNum = string.Empty;
        private Form1 form;

        public SetFBMsg(string mac, Form1 _from)
        {
            macNum = mac;
            form = _from;
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1.rbtnet_.SetFBDeviceMessages(macNum, this.textBox1.Text);
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= ' ' && e.KeyChar <= '~')||e.KeyChar== '\b')
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
