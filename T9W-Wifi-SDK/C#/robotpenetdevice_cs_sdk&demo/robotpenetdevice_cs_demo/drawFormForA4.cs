using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using WindowsForms.Class;


namespace rbt_win32_2_demo
{
    public partial class drawFormForA4 : Form
    {
        private int m_nDeviceW = 29700;
        private int m_nDeviceH = 21000;

        Angle angle = Angle._270;

        //答题书写区
        Dictionary<int, DrawingInfo> drawingDic = new Dictionary<int, DrawingInfo>();
        int DrawInfo = 0;
        int previewNum = 0;

        private string MacAdr = string.Empty;

        public drawFormForA4(string _mac)
        {
            MacAdr = _mac;
            InitializeComponent();
        }

        public void RememberData(ushort us, ushort ux, ushort uy, ushort up)
        {
            RobotPoint rPoint = new RobotPoint()
            {
                bPenStatus = us,
                bPress = up,
                bx = ux,
                by = uy,
                isOptimize = false
            };
            try
            {
                if(!drawingDic.ContainsKey(DrawInfo))
                {
                    addPictoreBox();
                }
                drawingDic[DrawInfo].drawing.recvData(rPoint.bPenStatus, rPoint.bx, rPoint.by, rPoint.bPress);
            }
            catch(Exception ex)
            {

            }
        }
        public void RememberData(ushort us, ushort ux, ushort uy, float uw, float uspeed)
        {
            RobotPoint rPoint = new RobotPoint()
            {
                bPenStatus = us,
                bWidth = uw,
                bSpeed = uspeed,
                bx = ux,
                by = uy,
                isOptimize = true
            };
            try
            {
                if (!drawingDic.ContainsKey(DrawInfo))
                {
                    addPictoreBox();
                }
                drawingDic[DrawInfo].drawing.recvOptimizeData(rPoint.bPenStatus, rPoint.bx, rPoint.by, rPoint.bWidth);
            }
            catch (Exception ex)
            {

            }
        }

        #region 委托修改控件
        private delegate void updateTextBox_Evt(TextBox _tbox, string Text);
        public void updateTextBox(TextBox _tbox, string Text)
        {
            if (_tbox.InvokeRequired)
            {
                while (!_tbox.IsHandleCreated)
                {
                    if (_tbox.Disposing || _tbox.IsDisposed)
                    {
                        return;
                    }
                }
                updateTextBox_Evt uLEvt = new updateTextBox_Evt(updateTextBox);
                _tbox.Invoke(uLEvt, new object[] { _tbox, Text });
            }
            else
            {
                _tbox.Text = Text;
            }
        }
        private delegate void updateLable_Evt(Label _lable, string Text);
        public void UpdateLableText(Label _lable, string Text)
        {
            if (_lable.InvokeRequired)
            {
                while (!_lable.IsHandleCreated)
                {
                    if (_lable.Disposing || _lable.IsDisposed)
                    {
                        return;
                    }
                }
                updateLable_Evt uLEvt = new updateLable_Evt(UpdateLableText);
                _lable.Invoke(uLEvt, new object[] { _lable, Text });
            }
            else
            {
                _lable.Text = Text;
            }
        }
        #endregion

        /// <summary>
        /// 设置屏幕宽度，并生成点坐标缩放比例
        /// </summary>
        private void compressPictureBox()
        {
            if (drawingDic.Count == 0)
            {
                DrawingInfo Dinfo = CreateCanvase(DrawInfo);
                this.Controls.Add(Dinfo.pbox);
                Dinfo.drawing = new Drawing_RePlay(Dinfo.pbox, angle, m_nDeviceW, m_nDeviceH, 0, 0);
                Dinfo.drawing.DrawingCallbackBrushstroke_Evt += Form_DrawingCallbackBrushstroke;
                drawingDic.Add(DrawInfo, Dinfo);

                Dinfo.pbox.Visible = true;
            }
            foreach (var item in drawingDic)
            {
                if (item.Value.drawing == null)
                {
                    item.Value.drawing = new Drawing_RePlay(item.Value.pbox, angle, m_nDeviceW, m_nDeviceH, 0, 0);
                    item.Value.drawing.DrawingCallbackBrushstroke_Evt += Form_DrawingCallbackBrushstroke;
                }
            }
        }

        private void Form_DrawingCallbackBrushstroke(List<RobotPoint> _plist)
        {

        }

        #region UI事件
        private void drawFormForA4_Load(object sender, EventArgs e)
        {
            this.Text = MacAdr;
            compressPictureBox();
        }

        private void drawFormForA4_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }

        private void drawFormForA4_SizeChanged(object sender, EventArgs e)
        {
            if (this.Size.Height <= 54)
            {
                return;
            }
            int heightChange = this.Size.Height - 54;
            double picboxHeight = heightChange;
            double picboxWidth = (heightChange / 297.00) * 210.00;
            Console.WriteLine(picboxHeight);
            Console.WriteLine(picboxWidth);

            foreach (var item in drawingDic)
            {
                item.Value.pbox.Height = Convert.ToInt32(Math.Ceiling(picboxHeight));
                item.Value.pbox.Width = Convert.ToInt32(Math.Ceiling(picboxWidth));
            }
        }

        #endregion


        private DrawingInfo CreateCanvase(int key)
        {
            DrawingInfo Dinfo = new DrawingInfo();

            System.Windows.Forms.PictureBox pInfo = new PictureBox();
            pInfo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            pInfo.Location = new System.Drawing.Point(100, 5);
            pInfo.Name = "pictureBox"+ key;
            pInfo.Size = new System.Drawing.Size(420, 594);
            pInfo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            pInfo.TabIndex = 0;
            pInfo.TabStop = false;
            pInfo.Visible = true;
            //pInfo.Paint += new System.Windows.Forms.PaintEventHandler((object sender, PaintEventArgs e) => {
            //    pInfo.Image = drawingDic[key].drawing.bt;
            //});
            pInfo.DoubleClick += new System.EventHandler((object sender, EventArgs e) =>
            {
                drawingDic[key].pbox.Image = null;
                drawingDic[key].remData.Clear();
                drawingDic[key].drawing.clear();
            });
            Dinfo.pbox = pInfo;

            return Dinfo;
        }

        public void UpdateJDNum(int num)
        {
            DrawInfo = num;
            UpdateLableText(this.label8, string.Format(@"作答页：{0}", num));
        }

        

        private void button3_Click(object sender, EventArgs e)
        {
            if(drawingDic.Where(p => p.Key < previewNum).Count()==0)
            {
                KeyValuePair<int, DrawingInfo> pinfo = drawingDic.OrderBy(p => p.Key).LastOrDefault();

                drawingDic[previewNum].pbox.Visible = false;

                pinfo.Value.pbox.Visible = true;
                pinfo.Value.pbox.Image = pinfo.Value.drawing.bt;

                previewNum = pinfo.Key;
            }
            else
            {
                KeyValuePair<int, DrawingInfo> pinfo = drawingDic.Where(p => p.Key < previewNum).OrderByDescending(p => p.Key).FirstOrDefault();
                drawingDic[previewNum].pbox.Visible = false;

                pinfo.Value.pbox.Visible = true;
                pinfo.Value.pbox.Image = pinfo.Value.drawing.bt;

                previewNum = pinfo.Key;
            }
            UpdateLableText(this.label3, string.Format(@"预览页：{0}", previewNum));
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (drawingDic.Where(p => p.Key > previewNum).Count() == 0)
            {
                KeyValuePair<int, DrawingInfo> pinfo = drawingDic.OrderBy(p => p.Key).First();

                drawingDic[previewNum].pbox.Visible = false;

                pinfo.Value.pbox.Visible = true;
                pinfo.Value.pbox.Image = pinfo.Value.drawing.bt;

                previewNum = pinfo.Key;
            }
            else
            {
                KeyValuePair<int, DrawingInfo> pinfo = drawingDic.Where(p => p.Key > previewNum).OrderBy(p => p.Key).FirstOrDefault();
                drawingDic[previewNum].pbox.Visible = false;

                pinfo.Value.pbox.Visible = true;
                pinfo.Value.pbox.Image = pinfo.Value.drawing.bt;

                previewNum = pinfo.Key;
            }

            UpdateLableText(this.label3, string.Format(@"预览页：{0}", previewNum));
        }


        private delegate void updateForm();
        private void addPictoreBox()
        {
            if (this.InvokeRequired)
            {
                while (!this.IsHandleCreated)
                {
                    if (this.Disposing || this.IsDisposed)
                    {
                        return;
                    }
                }
                updateForm uLEvt = new updateForm(addPictoreBox);
                this.Invoke(uLEvt, new object[] { });
            }
            else
            {
                DrawingInfo Dinfo = CreateCanvase(DrawInfo);
                this.Controls.Add(Dinfo.pbox);
                Dinfo.drawing = new Drawing_RePlay(Dinfo.pbox, angle, m_nDeviceW, m_nDeviceH, 0, 0);
                Dinfo.drawing.DrawingCallbackBrushstroke_Evt += Form_DrawingCallbackBrushstroke;
                drawingDic.Add(DrawInfo, Dinfo);
            }
        }

        private class DrawingInfo
        {
            public Drawing_RePlay drawing { get; set; }
            public List<RobotPoint> remData = new List<RobotPoint>();
            public PictureBox pbox { get; set; }
        }
    }
}
