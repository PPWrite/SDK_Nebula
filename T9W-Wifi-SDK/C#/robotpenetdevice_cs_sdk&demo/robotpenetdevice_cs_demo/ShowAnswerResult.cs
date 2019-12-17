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
    public partial class ShowAnswerResult : Form
    {
        private Dictionary<int, string> dataDic;

        public ShowAnswerResult(Dictionary<int ,string> _dataDic)
        {
            dataDic = _dataDic;
            InitializeComponent();
        }

        private void ShowAnswerResult_Load(object sender, EventArgs e)
        {
            this.listView1.Columns.Add("题号", 120, HorizontalAlignment.Left);
            this.listView1.Columns.Add("选项", 120, HorizontalAlignment.Left);
            int i = 0;
            foreach (var item in dataDic)
            {
                this.listView1.Items.Add(item.Key.ToString());
                this.listView1.Items[i].SubItems.Add(item.Value);
                i++;
            }
        }
    }
}
