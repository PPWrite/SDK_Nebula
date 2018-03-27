using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using RobotpenWifi;

namespace RobotpenWifiDemoNet
{
    public partial class MainForm : Form
    {
        RobotpenController m_robotpenController;

        private delegate void AddListViewDelegate(string strTarget, string strNotekey); 

        public MainForm()
        {
            InitializeComponent();
            m_robotpenController = new RobotpenController();
            m_robotpenController.onConnectResult_ += new RobotpenController.mqtt_onConnectResult(onConnectResult);
            m_robotpenController.onPushJob_ += new RobotpenController.mqtt_onPushJob(onPushJob);
            m_robotpenController.onStartAnswer_ += new RobotpenController.mqtt_onStartdAnswer(onStartdAnswer);
            m_robotpenController.onStopAnswer_ += new RobotpenController.mqtt_onStopAnswer(onStopAnswer);
            m_robotpenController.onFinishedAnswer_ += new RobotpenController.mqtt_onFinishedAnswer(onFinishedAnswer);

            m_robotpenController.Init();


            this.listView1.Columns.Add("Target", 160, HorizontalAlignment.Left);
            this.listView1.Columns.Add("Notekey", 0, HorizontalAlignment.Left);
           
        }

        private void button_start_Click(object sender, EventArgs e)
        {
            m_robotpenController.LoginMqttServer();
        }

        private void button_stop_Click(object sender, EventArgs e)
        {
            m_robotpenController.DisconnectMqttServer();
        }

        public void onConnectResult(IntPtr context, IntPtr response)
        {
            System.Console.WriteLine("onConnectResult");
        }

        public void onPushJob(IntPtr conect, ref string strNoteKey, ref string strTarget)
        {
            System.Console.WriteLine("onPushJob");
            AddListViewDelegate d = new AddListViewDelegate(AddListView);
            this.Invoke(d, new object[] { strTarget, strNoteKey });
        }

        public void onStartdAnswer(IntPtr context)
        {
            System.Console.WriteLine("onStartdAnswer");
        }

        public void onStopAnswer(IntPtr context)
        {
            System.Console.WriteLine("onStopAnswer");
        }

        public void onFinishedAnswer()
        {
            System.Console.WriteLine("onFinishedAnswer");
        }

        public void AddListView(string strTarget, string strNotekey)
        {
            ListViewItem item = new ListViewItem();
            item = listView1.Items.Add(strTarget);
            item.SubItems.Add(strNotekey);    
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            int selectCount = this.listView1.SelectedItems.Count;
            if (selectCount > 0)
            {
                string strNoteKey = this.listView1.SelectedItems[0].SubItems[1].Text;
                List<RobotpenWifi.RobotpenController.PEN_INFO> listPenInfo = m_robotpenController.getServerTrails(strNoteKey);
                foreach (RobotpenWifi.RobotpenController.PEN_INFO penInfo in listPenInfo)
                {
                    this.canvasControl1.recvData(penInfo.s, penInfo.x, penInfo.y, penInfo.p);
                }
            }
        }
    }
}
