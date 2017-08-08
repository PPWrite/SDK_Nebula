using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace RobotPenTestDll
{
    public partial class UserControl1 : UserControl
    {
        public UserControl1(canvasType canvasTy)
        {
            InitializeComponent();
            this.m_onLine = false;

            windowType = canvasTy;
        }

        public int m_nIndex { get; set; }
        public bool m_onLine { get; set; }
        private Font indexFont = new Font("Times New Roman", 14);
        private Font voteFont = new Font("Times New Roman", 18);

        canvasType windowType { get; set; }
        //public void delegate testDelegate();

        #region  波形网格数据
        private Pen gridPen = new Pen(Color.Green, 1);
        private int nGridSpacing = 10;
        private int nGridOffset = 6;
        #endregion

        #region 波形数据存储
        List<int> lstPoint = new List<int>();  // 存储Y坐标
        Point ptOriginal = new Point();
        Point ptLast = new Point();
        Pen linePen = new Pen(Color.Red, 1);
        #endregion

        Graphics g;

        public void start()
        {
            this.timer1.Start();
        }

        public void setControlSize(int w, int h)
        {
            this.Size = new Size(w, h);
            this.pictureBox1.Size = new Size(w, h);
        }
        private string m_strVoteStr = string.Empty;

        public void setVoteMode(string strVote)
        {
            m_strVoteStr = strVote;
            this.pictureBox1.Invalidate(false);
        }

        public void refreshWindow()
        {
            this.pictureBox1.Refresh();
        }

        // 清除窗口
        public void clearWindowBoxing()
        {
            lstPoint.Clear();
            refreshWindow();
        }

        public void updateNodeConnectionStatus()
        {
            this.pictureBox1.Invalidate(false);
        }

        // 控件自绘事件
        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            //Console.WriteLine("pictureBox1_Paint");
            g = e.Graphics;
            // 绘制波形网格
            /*for (int i = this.pictureBox1.Width; i >= 0; i -= nGridSpacing)
            {
                // 绘制竖线
                g.DrawLine(gridPen, i, 0, i, this.pictureBox1.Height);
            }

            for (int i = 0; i < this.pictureBox1.Height; i += nGridSpacing)
            {
                // 绘制横线
                g.DrawLine(gridPen, 0, i, this.pictureBox1.Width, i);
            }*/

            ptLast.X = 0;
            // 绘制波形图
            for (int i = 0; i < lstPoint.Count - 1; ++i)
            {
                ptOriginal.X = ptLast.X;
                ptOriginal.Y = lstPoint[i];
                ptLast.X += nGridOffset;
                ptLast.Y = lstPoint[i + 1];
                g.DrawLine(linePen, ptOriginal, ptLast);
            }

            // 底部绘制一个10*10的原型图标
            Rectangle bottomLog = new Rectangle(this.pictureBox1.Width - 24, this.pictureBox1.Height - 24, 20, 20);
            Brush b = this.m_onLine ? new SolidBrush(Color.Green) : new SolidBrush(Color.Red);
            g.DrawEllipse(new Pen(Color.Black), bottomLog);
            g.FillEllipse(b, bottomLog);

            // 绘制索引
            string strIndex;

            RectangleF rf;
            if (windowType == canvasType.DONGLE || windowType == canvasType.P1 || windowType == canvasType.T7E_TS)
            {
                strIndex = "双击显示画布";
                SizeF sizeString = g.MeasureString(strIndex, indexFont);
                rf = new RectangleF(0, 0, sizeString.Width, sizeString.Height);
            }
            else
            {
                strIndex = Convert.ToString(m_nIndex);
                SizeF sizeString = g.MeasureString(strIndex, indexFont);
                rf = new RectangleF(this.Width / 2 - sizeString.Width, this.Height - sizeString.Height - 4, sizeString.Width, sizeString.Height);
            }

            g.DrawRectangle(Pens.Transparent, rf.Left, rf.Top, rf.Width, rf.Height);
            Brush bString = new SolidBrush(Color.FromArgb(0, Color.Green));
            g.FillRectangle(bString, rf);
            g.DrawString(strIndex, indexFont, Brushes.White, rf);

            // 绘制投票模式
            if (m_strVoteStr != string.Empty)
            {
                SizeF sizef = g.MeasureString(m_strVoteStr, voteFont);
                RectangleF rect = new RectangleF(this.pictureBox1.Width / 2 - sizef.Width / 2, this.pictureBox1.Height / 2 - sizef.Height / 2, sizef.Width, sizef.Height);
                g.DrawRectangle(Pens.Transparent, rect.Left, rect.Top, rect.Width, rect.Height);
                g.FillRectangle(new SolidBrush(Color.FromArgb(0, Color.Green)), rect);
                g.DrawString(m_strVoteStr, voteFont, Brushes.White, rect);
            }
        }

        //用随机数来填充Y坐标数组
        private void getlist()
        {
        }

        // 定时器响应事件
        private void timer1_Tick(object sender, EventArgs e)
        {
            getlist();
            this.pictureBox1.Refresh();//此方法触发pictureBox1重绘事件pictureBox1_Paint
        }

        // 双击弹窗
        public delegate void control_DbClk(string strTitle);
        public control_DbClk canvasShowEvt;
        private void pictureBox1_DoubleClick(object sender, EventArgs e)
        {
            string strIndex = Convert.ToString(m_nIndex);
            if (canvasShowEvt != null)
                canvasShowEvt(strIndex);
        }

        // 有数据到达
        public void dataArrive(int nX, int nY)
        {
            int nTemp = nX % this.pictureBox1.Height;
            //Console.WriteLine("{0}", nTemp);
            if (lstPoint.Count >= 210)
            {
                lstPoint.RemoveAt(0);
                lstPoint.Add(nTemp);
            }
            else
            {
                lstPoint.Add(nTemp);
            }

            this.pictureBox1.Invalidate(false);
            //Console.WriteLine("{0},{1}", nTemp, nX);
            //此方法触发pictureBox1重绘事件pictureBox1_Paint
            //this.pictureBox1.Refresh();
        }
    }
}
