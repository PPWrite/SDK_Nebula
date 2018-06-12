using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
//using System.Linq;
using System.Text;
//using System.Threading.Tasks;
using System.Windows.Forms;

namespace RobotPenTestDll
{
    public struct CanvasItem
    {
        public PointF beginPoint { get; set; }
        public List<PointF> listpoints;
        public List<float> listPenWidthf;
    }

    public enum canvasType
    {
        GATEWAY,
        NODE,
        DONGLE,
        P1,
        T7E_TS,
    }

    public partial class TrailsShowFrom : Form
    {
        private int m_nDeviceW;
        private int m_nDeviceH;
        private int m_nPageNumber = 0;
        private int m_nNoteNumber = 0;

        public TrailsShowFrom(canvasType canvasty)
        {
            InitializeComponent();
            canvastype = canvasty;
            if (canvastype == canvasType.DONGLE)
            {
                m_nDeviceW = 14335;
                m_nDeviceH = 8191;

                m_nDeviceW = 22015;
                m_nDeviceH = 15359;
            }
            else if (canvastype == canvasType.P1)
            {
                m_nDeviceW = 17407;
                m_nDeviceH = 10751;
            }
            else if (canvasty == canvasType.T7E_TS)
            {
                m_nDeviceW = 14335;
                m_nDeviceH = 8191;
            }
            else
            {
                m_nDeviceW = 22015;
                m_nDeviceH = 15359;
            }

            bOptimize = false;
        }

        public TrailsShowFrom(int len, int width)
        {
            InitializeComponent();
            m_nDeviceW = width;
            m_nDeviceH = len;
            bOptimize = false;
        }

        public bool bOptimize { get; set; }
        public int pageNumber { get { return m_nPageNumber; } set { m_nPageNumber = value; } }
        public int noteNumber { get { return m_nNoteNumber; } set { m_nNoteNumber = value; } }

        public void updatePageInfo()
        {
            this.Invalidate(false);
        }

        // 绘制线条
        private void TrailsShowFrom_Paint(object sender, PaintEventArgs e)
        {
            Graphics grap = this.CreateGraphics();
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            e.Graphics.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            e.Graphics.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighQuality;

            string strPage = "本子:" + Convert.ToString(m_nNoteNumber) + ", 第" + Convert.ToString(m_nPageNumber) + "页";
            e.Graphics.DrawString(strPage, new Font(new FontFamily("microsoft yahei"), 12), Brushes.Green, new PointF(0,0));

            if (bOptimize)
            {
                foreach (CanvasItem item in m_items)
                {
                    if (item.listpoints == null)
                    {
                        continue;
                    }
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
            else
            {
                foreach (CanvasItem item in m_items)
                {
                    if (item.listpoints == null)
                    {
                        continue;
                    }
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
            //if (canvastype == canvasType.NODE)
            {
                if (!bScreenO)
                {
                    float fY = point.Y;
                    point.Y = m_nDeviceW - point.X;
                    point.X = fY;
                }
            }

            int nBordereW = this.Width - this.ClientRectangle.Width;
            if (bScreenO)  // 横屏
            {
                int nValidWidth = this.ClientRectangle.Width - nBordereW / 2;
                int nValidHeight = this.ClientRectangle.Height - nBordereW;
                m_nCompress = ((double)(m_nDeviceW) / nValidWidth);  // 设备与屏幕的宽比例
                                                             // 计算高的比例
                double nNeedCanvasHeight = (double)(m_nDeviceW / m_nCompress);
                if (nNeedCanvasHeight > nValidHeight)
                    m_nCompress = (double)(m_nDeviceW / nValidHeight);
            }
            else   // 竖屏
            {
                int nValidWidth = this.Width - nBordereW;
                int nValidHeight = this.ClientRectangle.Height - nBordereW/2;
                m_nCompress = ((double)(m_nDeviceH) / nValidWidth);  // 设备与屏幕的宽比例
                                                             // 计算高的比例
                double nNeedCanvasHeight = (double)(m_nDeviceH / m_nCompress);
                if (nNeedCanvasHeight > nValidHeight)
                    m_nCompress = (double)(m_nDeviceH / nValidHeight);
            }


            float nx = (float)(point.X / m_nCompress);
            float ny = (float)(point.Y / m_nCompress);
            point.X = nx;
            point.Y = ny;
            //Console.WriteLine("压缩后的数据为:{0} {1}", nx, ny);
        }

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
           // Console.WriteLine("origin x={0} y={1}", x, y);
            /*if (canvastype == canvasType.T7E_TS)
            {
                //int nx = m_nDeviceH - y;
                //int ny = x;

                int nx = m_nDeviceW - x;
                int ny = m_nDeviceH - y;
                pointf = new PointF(nx, ny);


                //Console.Write(pointf);
                //Console.Write("\r\n");
            }
            else*/
            {
                pointf = new PointF(x, y);
            }

            
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

        // 接收到优化后的数据点数据
        public void recvOptimizeData(int nPenStatus, int x, int y, float fPenWidth)
        {
            if (fPenSize < 0)
                return;

            //Console.WriteLine("origin status={0} x={1} y={2} penWidth={3}", nPenStatus, x, y, fPenSize);
            //Console.WriteLine("origin status={0} x={1} y={2} penWidth={3}", nPenStatus, x, y, fPenWidth);
            PointF pointf;
            /*if (canvastype == canvasType.T7E_TS)
            {
                int nx = m_nDeviceW - x;
                int ny = m_nDeviceH - y;
                pointf = new PointF(nx, ny);
            }
            else*/
            {
                pointf = new PointF(x, y);
            }


            if (!pointIsInvalid(nPenStatus, ref pointf))
                return;

            if (nPenStatus == 0)  // 笔离开到板子
            {
                if (nFlags == 1)
                    onEndDrawBezier();
                //else
                   // onEndDrawBezier();
                nFlags = 0;
            }
            else
            {
                if (nFlags == 0)
                {
                    nFlags = 1;
                    compressPoint(ref pointf);
                    onBeginDrawBezier(ref pointf, fPenWidth);
                }
                else
                {
                    compressPoint(ref pointf);
                    onTrackDrawBezier(ref pointf, fPenWidth);
                }
            }
        }

        List<PointF> lstBezierPoints = new List<PointF>();
        bool bFristPoint = false;
        float fPenSize = 0;

        public void onBeginDrawBezier(ref PointF p, float fPenWidth)
        {
           // doPointDrawing(ref p);
            //return;

            bFristPoint = true;
            lstBezierPoints.Clear();
            m_bDrawing = true;
            bFristPoint = true;
            lstBezierPoints.Add(p);

            CanvasItem item = new CanvasItem();
            item.listpoints = new List<PointF>();
            item.listPenWidthf = new List<float>();

            item.beginPoint = p;
            m_currentItem = item;
        }

        public void onTrackDrawBezier(ref PointF p, float fPenWidth)
        {
            if (!m_bDrawing)
                return;

            //doPointDrawing(ref p);
           // return;


            lstBezierPoints.Add(p);
            m_currentItem.listpoints.Add(p);
            m_currentItem.listPenWidthf.Add(fPenWidth);
            fPenSize = fPenWidth;
            if (bFristPoint) 
            {
                PointF centerPos = new PointF();
                PointF p1 = lstBezierPoints[0];
                PointF p2 = lstBezierPoints[1];
                getCenterPoint(ref p1, ref p2, ref centerPos);
                doLineDrawing(ref p1, ref centerPos, fPenWidth);
                m_lastPoint = centerPos;
                lstBezierPoints.RemoveAt(0);
                bFristPoint = false;
            }
            else
            {
                PointF centerPos = new PointF();
                PointF p1 = lstBezierPoints[0];
                PointF p2 = lstBezierPoints[1];
                double gap = Math.Sqrt(Math.Pow(p1.X - p2.X, 2) + Math.Pow(p1.Y - p2.Y, 2));
                if (gap <= fPenWidth)
                {
                    lstBezierPoints.RemoveAt(1);
                    return;
                }

                getCenterPoint(ref p1, ref p2, ref centerPos);
                doBezierDrawing(ref m_lastPoint, ref p1, ref centerPos, fPenSize);
                m_lastPoint = centerPos;
                lstBezierPoints.RemoveAt(0);
            }
    
        }

        public void onEndDrawBezier()
        {
            m_bDrawing = false;
            //return;

            int nPointCount = lstBezierPoints.Count;
            if (nPointCount == 1)
            {
                PointF p = lstBezierPoints[0];
                doLineDrawing(ref m_lastPoint, ref p, fPenSize);
            }
            else if (nPointCount == 2)
            {
                PointF centerPos = new PointF();
                PointF p1 = lstBezierPoints[0];
                PointF p2 = lstBezierPoints[1];
                getCenterPoint(ref p1, ref p2, ref centerPos);
                doBezierDrawing(ref m_lastPoint, ref p1, ref centerPos, fPenSize);
                doLineDrawing(ref centerPos, ref p2, fPenSize);
            }

            if (m_currentItem.listpoints == null)
            {
                return;
            }
            m_items.Add(m_currentItem);
        }

        ////
        private void doLineDrawing(ref PointF p1, ref PointF p2, float fPenWidthF)
        {
            //Console.WriteLine("doLineDrawing p1={0} p2={1} penWidth={2}", p1, p2, fPenWidthF);
            Graphics grap = this.CreateGraphics();
            grap.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            grap.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            grap.DrawLine(new Pen(Color.Black, fPenWidthF), p1, p2);
            grap.Dispose();
        }

        private void doPointDrawing(ref PointF p1)
        {
            Graphics grap = this.CreateGraphics();
            grap.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            grap.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            grap.FillEllipse(Brushes.Red, p1.X, p1.Y, 2, 2);
            //grap.d(new Pen(Color.Red, 2), p1);
            grap.Dispose();
        }

        private void doControlPointDrawing(ref PointF p1)
        {
            Graphics grap = this.CreateGraphics();
            grap.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            grap.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            grap.FillEllipse(Brushes.Blue, p1.X, p1.Y, 3, 3);
            //grap.d(new Pen(Color.Red, 2), p1);
            grap.Dispose();
        }

        private void doBezierDrawing(ref PointF p1, ref PointF p2, ref PointF p3, float fPenWidthF)
        {
            Graphics grap = this.CreateGraphics();
            grap.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            grap.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            //grap.DrawLine(new Pen(Color.Black, fPenWidthF), p1, p2);
            //PointF [] pointArray = {p1, p2, p3};
            //Console.WriteLine("doBezierDrawing p1={0} p2={1} p3={2} penWidth={3}", p1, p2, p3, fPenWidthF);
            grap.DrawBezier(new Pen(Color.Black, fPenWidthF), p1, p2, p2, p3);
            //grap.FillEllipse(Brushes.Blue, p1.X, p1.Y, 3, 3);
            //grap.FillEllipse(Brushes.Green, p3.X, p3.Y, 3, 3);
            //grap.FillEllipse(Brushes.Red, p2.X, p2.Y, 3, 3);
            grap.Dispose();
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

        // 计算中间点
        private void getCenterPoint(ref PointF p1, ref PointF p2, ref PointF p3)
        {
            float fx = (p1.X + p2.X)/2;
            float fy = (p1.Y + p2.Y)/2;
            p3.X = fx;
            p3.Y = fy;
        }

        private void TrailsShowFrom_Load(object sender, EventArgs e)
        {
            double dwhRatio = (double)m_nDeviceW / m_nDeviceH;
            int nFixedHeight = 960;
            int nWidth = 0;
            if (bScreenO)   // 横屏
            {
                nWidth = (int)(dwhRatio * nFixedHeight);
            }
            else
            {
                // 竖屏
                nWidth = (int)(nFixedHeight / dwhRatio);
            }

            this.Height = nFixedHeight;
            this.Width = nWidth;
        }
    }
}
