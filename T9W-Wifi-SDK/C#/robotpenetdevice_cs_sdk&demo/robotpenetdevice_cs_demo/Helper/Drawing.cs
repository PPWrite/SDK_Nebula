using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsForms.Class
{
    public enum Angle
    {
        _0,
        _90,
        _180,
        _270
    }
    public class Drawing
    {
        /// <summary>
        /// 实例化画图类
        /// </summary>
        /// <param name="_control"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        public Drawing(System.Windows.Forms.Control _control, Angle _Angle, int width,int height)
        {
            myControl = _control;
            m_nDeviceW = width;
            m_nDeviceH = height;
            Angle = _Angle;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="_control"></param>
        /// <param name="_Angle"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <param name="_offsetX"></param>
        /// <param name="_offsetY"></param>
        public Drawing(System.Windows.Forms.Control _control, Angle _Angle, int width, int height, int _offsetX, int _offsetY)
        {
            myControl = _control;
            m_nDeviceW = width;
            m_nDeviceH = height;
            Angle = _Angle;
        }

        public Angle Angle = Angle._0;
        public int offsetX = 0;
        public int offsetY = 0;
        public System.Windows.Forms.Control myControl;
        //bool bScreenO = true;//判断是否是横屏，默认横屏
        //画布宽高
        public int m_nDeviceW;
        public int m_nDeviceH;
        /// <summary>
        /// 点缩放比例
        /// </summary>
        public double m_nCompress_x = 0;
        public double m_nCompress_y = 0;

        public List<RobotPoint> plist = new List<RobotPoint>();

        /// <summary>
        /// 根据点缩放比例，缩放XY轴
        /// </summary>
        /// <param name="point"></param>
        public virtual void compressPoint(ref PointF point)
        {
            float px = 0;
            float py = 0;
            switch (Angle)
            {
                case Angle._0:
                    {
                        px = point.X;
                        py = point.Y;

                        m_nCompress_x = (double)myControl.Width / (double)m_nDeviceW;
                        m_nCompress_y = (double)myControl.Height / (double)m_nDeviceH;

                        break;
                    }
                case Angle._90:
                    {
                        px = (m_nDeviceH - point.Y);
                        py = point.X;

                        m_nCompress_x = (double)myControl.Width / (double)m_nDeviceH;
                        m_nCompress_y = (double)myControl.Height / (double)m_nDeviceW;

                        break;
                    }
                case Angle._180:
                    {
                        px = (m_nDeviceW - point.X);
                        py = (m_nDeviceH - point.Y);

                        m_nCompress_x = (double)myControl.Width / (double)m_nDeviceW;
                        m_nCompress_y = (double)myControl.Height / (double)m_nDeviceH;
                        break;
                    }
                case Angle._270:
                    {
                        px = point.Y;
                        py = (m_nDeviceW - point.X);

                        m_nCompress_x = (double)myControl.Width / (double)m_nDeviceH;
                        m_nCompress_y = (double)myControl.Height / (double)m_nDeviceW;
                        break;
                    }
                default:
                    {
                        px = point.X;
                        py = point.Y;
                        m_nCompress_x = (double)myControl.Width / (double)m_nDeviceW;
                        m_nCompress_y = (double)myControl.Height / (double)m_nDeviceH;
                        break;
                    }
            }
            float nx = (float)((px + offsetX) * m_nCompress_x);
            float ny = (float)((py + offsetY) * m_nCompress_y);

            point.X = nx;
            point.Y = ny;
        }
        //上一个点
        private PointF m_point;
        //上一个点状态
        private int m_nPenStatus = 0;
        /// <summary>
        /// 判断是否是有效点
        /// </summary>
        /// <param name="nPenStatus"></param>
        /// <param name="pointValue"></param>
        /// <returns></returns>
        private bool pointIsInvalid(int nPenStatus, ref PointF pointValue)
        {
            if ((m_point == pointValue) && (m_nPenStatus == nPenStatus))
                return false;
            m_point = pointValue;
            m_nPenStatus = nPenStatus;
            return true;
        }


        public void recvData(int nPenStatus, float x, float y, float nPress,float nWidth=1)
        {
            PointF pointf = new PointF(x, y);
            if (!pointIsInvalid(nPenStatus, ref pointf))
                return;

            if (nPenStatus != 17 && nPenStatus != 33 && nPenStatus != 49)  // 笔离开到板子
            {
                if (nFlags == 1)
                {
                    plist.Add(new RobotPoint()
                    {
                        bx = x,
                        by = y,
                        bPenStatus = nPenStatus,
                        bPress = nPress,
                        bWidth= nWidth,
                        bIndex = plist.Count() + 1
                    });
                    if (DrawingCallbackBrushstroke_Evt != null)
                    {
                        DrawingCallbackBrushstroke_Evt(plist);
                        plist.Clear();
                    }
                    onEndDraw();
                }
                else
                {
                    onEndDraw();
                }
                nFlags = 0;
            }
            else
            {
                plist.Add(new RobotPoint()
                {
                    bx = x,
                    by = y,
                    bPenStatus = nPenStatus,
                    bPress = nPress,
                    bWidth = nWidth,
                    bIndex = plist.Count() + 1
                });
                if (nFlags == 0)
                {
                    nFlags = 1;
                    compressPoint(ref pointf);
                    onBeginDraw(ref pointf, nPenStatus);
                }
                else
                {
                    compressPoint(ref pointf);
                    onTrackDraw(ref pointf, nPenStatus, nWidth);
                }
            }
        }

        //轨迹点
        private List<CanvasItem> m_items = new List<CanvasItem>();  // 所有线条
        private CanvasItem m_currentItem;
        private bool m_bDrawing = false;
        public PointF m_lastPoint;
        private int nFlags = 0;
        private void onBeginDraw(ref PointF p,int status)
        {
            m_bDrawing = true;
            m_lastPoint = p;
            CanvasItem item = new CanvasItem();
            item.listpoints = new List<PointF>();
            item.listPenWidthf = new List<float>();
            item.beginPoint = p;
            m_currentItem = item;
        }
        private void onTrackDraw(ref PointF p, int status,float width)
        {
            if (!m_bDrawing)
                return;
            doDrawing(ref p, status, width);
            m_currentItem.listpoints.Add(p);

        }
        /// <summary>
        /// 绘制的方法
        /// </summary>
        /// <param name="pos"></param>
        /// <param name="nCompress"></param>
        public virtual void doDrawing(ref PointF pos, int status,float width)
        {
            Graphics grap = myControl.CreateGraphics();
            grap.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            grap.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            Color pointc = Color.Black;
            float penW = width;
            if(status==33)
            {
                pointc = Color.Red;
            }
            else if(status == 49)
            {
                pointc = Color.White;
                penW = 10;
            }
            grap.DrawLine(new Pen(pointc, penW), m_lastPoint, pos);
            m_lastPoint = pos;
            grap.Dispose();
        }
        private void onEndDraw()
        {
            m_bDrawing = false;
            if (m_currentItem.listpoints == null)
            {
                return;
            }
            m_items.Add(m_currentItem);
        }

        private RobotPoint lastPoint = new RobotPoint();
        // 接收到优化后的数据点数据
        public void recvOptimizeData(int nPenStatus, float x, float y, float fPenWidth)
        {
            RobotPoint nowPoint = new RobotPoint()
            {
                bx = x,
                by = y,
                bPenStatus = nPenStatus,
                bWidth = fPenWidth,
                bIndex = plist.Count() + 1,
                isOptimize = true,
            };

            if (fPenSize < 0)
                return;
            PointF pointf = new PointF(x, y);
            if (!pointIsInvalid(nPenStatus, ref pointf))
                return;

            if (fPenWidth == 0)  // 笔离开到板子
            {
                if (nFlags == 1)
                {
                    plist.Add(nowPoint);
                    if (DrawingCallbackBrushstroke_Evt != null)
                    {
                        DrawingCallbackBrushstroke_Evt(plist);
                        plist.Clear();
                    }

                    //if (Math.Abs(nowPoint.bWidth - lastPoint.bWidth) > 0.1)
                    //{
                    //    int t = (int)((nowPoint.bWidth - lastPoint.bWidth) / 0.1);

                    //    List<RobotPoint> _CheckList = new List<RobotPoint>();
                    //    _CheckList.Add(lastPoint);
                    //    _CheckList.Add(nowPoint);

                    //    for (int i = 0; i < t - 1; i++)
                    //    {
                    //        _CheckList = insertCenterPoing(_CheckList);
                    //    }
                    //    _CheckList.Remove(_CheckList[0]);
                    //    foreach (var item in _CheckList)
                    //    {
                    //        PointF fC = new PointF(item.bx, item.by);

                    //        compressPoint(ref fC);
                    //        onTrackDrawBezier(ref fC, item.bWidth);
                    //    }
                    //    onEndDrawBezier();
                    //}
                    //else
                    //{
                    //    onEndDrawBezier();
                    //}


                    //else
                    onEndDrawBezier();
                    lastPoint = new RobotPoint();
                    nFlags = 0;
                }

            }
            else
            {
                plist.Add(nowPoint);
                if (nFlags == 0)
                {
                    nFlags = 1;
                    compressPoint(ref pointf);
                    onBeginDrawBezier(ref pointf, fPenWidth);
                }
                else
                {


                    //if (Math.Abs(nowPoint.bWidth - lastPoint.bWidth) > 0.1)
                    //{
                    //    int t = (int)((nowPoint.bWidth - lastPoint.bWidth) / 0.1);

                    //    List<RobotPoint> _CheckList = new List<RobotPoint>();
                    //    _CheckList.Add(lastPoint);
                    //    _CheckList.Add(nowPoint);

                    //    for (int i = 0; i < t - 1; i++)
                    //    {
                    //        _CheckList = insertCenterPoing(_CheckList);
                    //    }
                    //    _CheckList.Remove(_CheckList[0]);
                    //    foreach (var item in _CheckList)
                    //    {
                    //        PointF fC = new PointF(item.bx, item.by);

                    //        compressPoint(ref fC);
                    //        onTrackDrawBezier(ref fC, item.bWidth);
                    //    }
                    //}
                    //else
                    //{
                    //    compressPoint(ref pointf);
                    //    onTrackDrawBezier(ref pointf, fPenWidth);
                    //}
                    compressPoint(ref pointf);
                    onTrackDrawBezier(ref pointf, fPenWidth);
                }
            }
            lastPoint = nowPoint;
        }
        private List<RobotPoint> insertCenterPoing(List<RobotPoint> _plist)
        {
            List<RobotPoint> result = new List<RobotPoint>();
            int len = _plist.Count;
            for (int i = 0; i < len; i++)
            {
                if (i == 0)
                {
                    result.Add(_plist[i]);
                    continue;
                }
                PointF pointf1 = new PointF(_plist[i - 1].bx, _plist[i - 1].by);
                PointF pointf2 = new PointF(_plist[i].bx, _plist[i].by);
                PointF pointf3 = new PointF();

                getCenterPoint(ref pointf1, ref pointf2, ref pointf3);

                float twidth = (_plist[i - 1].bWidth + _plist[i].bWidth) / 2;

                RobotPoint Point_t = new RobotPoint()
                {
                    bx = pointf3.X,
                    by = pointf3.Y,
                    bPenStatus = _plist[i].bPenStatus,
                    bWidth = twidth,
                    bIndex = -100,
                    isOptimize = true,
                };
                result.Add(Point_t);
                result.Add(_plist[i]);
            }
            return result;
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
        private void getCenterPoint(ref PointF p1, ref PointF p2, ref PointF p3)
        {
            float fx = (p1.X + p2.X) / 2;
            float fy = (p1.Y + p2.Y) / 2;
            p3.X = fx;
            p3.Y = fy;
        }
        public virtual void doBezierDrawing(ref PointF p1, ref PointF p2, ref PointF p3, float fPenWidthF)
        {
            Graphics grap = myControl.CreateGraphics();
            grap.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            grap.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            grap.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighQuality;
            //grap.DrawLine(new Pen(Color.Black, fPenWidthF), p1, p2);
            //PointF [] pointArray = {p1, p2, p3};
            //Console.WriteLine("doBezierDrawing p1={0} p2={1} p3={2} penWidth={3}", p1, p2, p3, fPenWidthF);
            grap.DrawBezier(new Pen(Color.Black, fPenWidthF), p1, p2, p2, p3);

            //Console.WriteLine(string.Format(@"s={0},x={1},y={2},w={3}", 0, p1.X, p1.Y, fPenWidthF));
            //Console.WriteLine(string.Format(@"s={0},x={1},y={2},w={3}", 0, p2.X, p2.Y, fPenWidthF));
            //Console.WriteLine(string.Format(@"s={0},x={1},y={2},w={3}", 0, p3.X, p3.Y, fPenWidthF));

            //grap.DrawEllipse(new Pen(Color.Black, 1), p1.X, p1.Y, 1, fPenWidthF);
            //grap.DrawEllipse(new Pen(Color.Black, 1), p2.X, p2.Y, 1, fPenWidthF);
            //grap.DrawEllipse(new Pen(Color.Black, 1), p3.X, p3.Y, 1, fPenWidthF);

            grap.Dispose();
        }
        public virtual void doLineDrawing(ref PointF p1, ref PointF p2, float fPenWidthF)
        {
            Graphics grap = myControl.CreateGraphics();
            grap.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            grap.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            grap.DrawLine(new Pen(Color.Black, fPenWidthF), p1, p2);
            grap.Dispose();
        }

        public delegate void DrawingCallbackBrushstroke(List<RobotPoint> _plist);
        public event DrawingCallbackBrushstroke DrawingCallbackBrushstroke_Evt;
    }

    public class RobotPoint
    {
        public int bIndex { get; set; }
        public int bPenStatus { get; set; }
        public float bx { get; set; }
        public float by { get; set; }
        public float bPress { get; set; }
        public float bWidth { get; set; }
        public float bSpeed { get; set; }
        public bool isOptimize { get; set; }
    }

    public struct CanvasItem
    {
        public PointF beginPoint { get; set; }
        public List<PointF> listpoints;
        public List<float> listPenWidthf;
    }
}
