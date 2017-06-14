using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RobotPenTestDll
{
    public struct CanvasItem
    {
        public PointF beginPoint { get; set; }
        public List<PointF> listpoints;
    }

    public enum canvasType
    {
        GATEWAY,
        NODE,
    }

    public partial class TrailsShowFrom : Form
    {
        public TrailsShowFrom()
        {
            InitializeComponent();
            canvastype = canvasType.GATEWAY;
        }

        // 绘制线条
        private void TrailsShowFrom_Paint(object sender, PaintEventArgs e)
        {

            foreach (CanvasItem item in m_items)
            {
                if (item.listpoints == null)
                {
                    continue;
                }
                Graphics grap = this.CreateGraphics();
                e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                e.Graphics.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
                e.Graphics.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighQuality;
                int nSize = item.listpoints.Count + 1;
                PointF[] pointsize = new PointF[nSize];
                pointsize[0] = item.beginPoint;

                PointF pointTemp = item.beginPoint;
                for (int i = 0; i < item.listpoints.Count; ++i)
                {
                    pointsize[i + 1] = item.listpoints[i];
                }
                e.Graphics.DrawLines(new Pen(Color.Black, 2), pointsize);
            }
        }
        public bool bScreenO { get; set; }
        private List<CanvasItem> m_items = new List<CanvasItem>();  // 所有线条
        private CanvasItem m_currentItem;
        private bool m_bDrawing = false;
        private PointF m_lastPoint;
        private int nFlags = 0;

        private PointF m_point;
        private int m_nPenStatus = 0;

        public canvasType canvastype { get; set; }

        private bool pointIsInvalid(int nPenStatus, ref PointF pointValue)
        {
            if ((m_point == pointValue) && (m_nPenStatus == nPenStatus))
                return false;
            m_point = pointValue;
            m_nPenStatus = nPenStatus;
            return true;
        }

        private double m_nCompress = 0;
        private void compressPoint(ref PointF point)
        {
            //
            if (canvastype == canvasType.NODE)
            {
                if (!bScreenO)
                {
                    float fY = point.Y;
                    point.Y = 22015 - point.X;
                    point.X = fY;
                }
            }

            int nBordereW = this.Width - this.ClientRectangle.Width;
            if (bScreenO)  // 横屏
            {
                int nValidWidth = this.ClientRectangle.Width - nBordereW / 2;
                int nValidHeight = this.ClientRectangle.Height - nBordereW;
                m_nCompress = ((double)(22015) / nValidWidth);  // 设备与屏幕的宽比例
                                                             // 计算高的比例
                double nNeedCanvasHeight = (double)(22015 / m_nCompress);
                if (nNeedCanvasHeight > nValidHeight)
                    m_nCompress = (double)(22015 / nValidHeight);
            }
            else   // 竖屏
            {
                int nValidWidth = this.Width - nBordereW;
                int nValidHeight = this.ClientRectangle.Height - nBordereW/2;
                m_nCompress = ((double)(15359) / nValidWidth);  // 设备与屏幕的宽比例
                                                             // 计算高的比例
                double nNeedCanvasHeight = (double)(15359 / m_nCompress);
                if (nNeedCanvasHeight > nValidHeight)
                    m_nCompress = (double)(15359 / nValidHeight);
            }


            float nx = (float)(point.X / m_nCompress);
            float ny = (float)(point.Y / m_nCompress);
            point.X = nx;
            point.Y = ny;
            //Console.WriteLine("压缩后的数据为:{0} {1}", nx, ny);
        }

        private int m_nDeviceW = 22015;
        //private int m_nDeviceH = 17539;
        private int m_nDeviceH = 15359;
        public void recvData(int nPenStatus, int x, int y, int nCompress)
        {
            PointF pointf;
            /*if (!bScreenO)
            {
                pointf = new PointF(y, m_nDeviceW-x);
            }
            else
            {
                pointf = new PointF(x, y);
            }*/
            pointf = new PointF(x, y);
            if (!pointIsInvalid(nPenStatus, ref pointf))
                return;

            if (nPenStatus == 0)  // 笔离开到板子
            {
                if (nFlags == 1)
                    onEndDraw();
                else
                    onEndDraw();
                nFlags = 0;
            }
            else
            {
                if (nFlags == 0)
                {
                    nFlags = 1;
                    compressPoint(ref pointf);
                    onBeginDraw(ref pointf);
                }
                else
                {
                    compressPoint(ref pointf);
                    onTrackDraw(ref pointf);
                }
            }
        }

        public void onBeginDraw(ref PointF p, int nCompress = 0)
        {
            m_bDrawing = true;
            m_lastPoint = p;
            CanvasItem item = new CanvasItem();
            item.listpoints = new List<PointF>();
            item.beginPoint = p;
            m_currentItem = item;
        }

        public void onTrackDraw(ref PointF p, int nCompress = 0)
        {
            if (!m_bDrawing)
                return;
            doDrawing(ref p, nCompress);
            m_currentItem.listpoints.Add(p);

        }

        private void doDrawing(ref PointF pos, int nCompress = 0)
        {
            Graphics grap = this.CreateGraphics();
            grap.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            grap.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            grap.DrawLine(new Pen(Color.Black, 2), m_lastPoint, pos);
            m_lastPoint = pos;
            grap.Dispose();
        }

        public void onEndDraw()
        {
            m_bDrawing = false;
            if (m_currentItem.listpoints == null)
            {
                return;
            }
            m_items.Add(m_currentItem);
        }

        private void TrailsShowFrom_DoubleClick(object sender, EventArgs e)
        {
            m_items.Clear();
            this.Refresh();
        }
    }
}
