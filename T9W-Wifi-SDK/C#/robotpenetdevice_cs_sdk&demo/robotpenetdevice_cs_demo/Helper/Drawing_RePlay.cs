using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsForms.Class
{
    public class Drawing_RePlay: Drawing
    {
        /// <summary>
        /// 实例化画图类
        /// </summary>
        /// <param name="_control"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        public Drawing_RePlay(System.Windows.Forms.PictureBox _control, Angle _Angle, int width,int height):base(_control, _Angle, width, height)
        {
            myControl = _control;
            m_nDeviceW = width;
            m_nDeviceH = height;
            Angle = _Angle;
            CreateMyGraphics();
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
        public Drawing_RePlay(System.Windows.Forms.PictureBox _control, Angle _Angle, int width, int height, int _offsetX, int _offsetY) : base(_control, _Angle, width, height, _offsetX, _offsetY)
        {
            myControl = _control;
            m_nDeviceW = width;
            m_nDeviceH = height;
            Angle = _Angle;
            CreateMyGraphics();
        }

        private void CreateMyGraphics()
        {
            controlWidth = 630;
            controlHeight = 891;
            bt = new Bitmap(controlWidth, controlHeight);
            grap = Graphics.FromImage(bt);
            grap.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            grap.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
        }

        Graphics grap;
        public Bitmap bt;
        public System.Windows.Forms.PictureBox myControl;
        int controlWidth;
        int controlHeight;

        /// <summary>
        /// 根据点缩放比例，缩放XY轴
        /// </summary>
        /// <param name="point"></param>
        public override void compressPoint(ref PointF point)
        {
            float px = 0;
            float py = 0;
            switch (Angle)
            {
                case Angle._0:
                    {
                        px = point.X;
                        py = point.Y;

                        m_nCompress_x = (double)controlWidth / (double)m_nDeviceW;
                        m_nCompress_y = (double)controlHeight / (double)m_nDeviceH;

                        break;
                    }
                case Angle._90:
                    {
                        px = (m_nDeviceH - point.Y);
                        py = point.X;

                        m_nCompress_x = (double)controlWidth / (double)m_nDeviceH;
                        m_nCompress_y = (double)controlHeight / (double)m_nDeviceW;

                        break;
                    }
                case Angle._180:
                    {
                        px = (m_nDeviceW - point.X);
                        py = (m_nDeviceH - point.Y);

                        m_nCompress_x = (double)controlWidth / (double)m_nDeviceW;
                        m_nCompress_y = (double)controlHeight / (double)m_nDeviceH;
                        break;
                    }
                case Angle._270:
                    {
                        px = point.Y;
                        py = (m_nDeviceW - point.X);

                        m_nCompress_x = (double)controlWidth / (double)m_nDeviceH;
                        m_nCompress_y = (double)controlHeight / (double)m_nDeviceW;
                        break;
                    }
                default:
                    {
                        px = point.X;
                        py = point.Y;
                        m_nCompress_x = (double)controlWidth / (double)m_nDeviceW;
                        m_nCompress_y = (double)controlHeight / (double)m_nDeviceH;
                        break;
                    }
            }
            float nx = (float)((px + offsetX) * m_nCompress_x);
            float ny = (float)((py + offsetY) * m_nCompress_y);

            point.X = nx;
            point.Y = ny;
        }


        /// <summary>
        /// 绘制的方法
        /// </summary>
        /// <param name="pos"></param>
        /// <param name="nCompress"></param>
        public override void doDrawing(ref PointF pos, int status, float width)
        {
            Color pointc = Color.Black;
            float penW = width;
            if (status == 33)
            {
                pointc = Color.Red;
            }
            else if (status == 49)
            {
                pointc = Color.White;
                penW = 10;
            }
            grap.DrawLine(new Pen(pointc, penW), m_lastPoint, pos);
            m_lastPoint = pos;
            if(this.myControl!=null)
            {
                updatePictureBoxImg_EVT(this.myControl, bt);
            }
            
        }


        public override void doBezierDrawing(ref PointF p1, ref PointF p2, ref PointF p3, float fPenWidthF)
        {
            grap.DrawBezier(new Pen(Color.Black, fPenWidthF), p1, p2, p2, p3);

            Console.WriteLine(string.Format(@"s={0},x={1},y={2},w={3}", 0, p1.X, p1.Y, fPenWidthF));
            Console.WriteLine(string.Format(@"s={0},x={1},y={2},w={3}", 0, p2.X, p2.Y, fPenWidthF));
            Console.WriteLine(string.Format(@"s={0},x={1},y={2},w={3}", 0, p3.X, p3.Y, fPenWidthF));

            //grap.DrawEllipse(new Pen(Color.Black, 1), p1.X, p1.Y, 1, fPenWidthF);
            //grap.DrawEllipse(new Pen(Color.Black, 1), p2.X, p2.Y, 1, fPenWidthF);
            //grap.DrawEllipse(new Pen(Color.Black, 1), p3.X, p3.Y, 1, fPenWidthF);

            if (this.myControl != null)
            {
                updatePictureBoxImg_EVT(this.myControl, bt);
            }
        }
        public override void doLineDrawing(ref PointF p1, ref PointF p2, float fPenWidthF)
        {
            grap.DrawLine(new Pen(Color.Black, fPenWidthF), p1, p2);
            if (this.myControl != null)
            {
                updatePictureBoxImg_EVT(this.myControl, bt);
            }
        }

        public void clear()
        {
            CreateMyGraphics();
        }

        public void addPictureBox(System.Windows.Forms.PictureBox _control)
        {
            myControl = _control;
        }

        private delegate void updatePictureBoxImg(System.Windows.Forms.PictureBox _control, Bitmap bt);
        private void updatePictureBoxImg_EVT(System.Windows.Forms.PictureBox _control, Bitmap bt)
        {
            try
            {
                if (_control.InvokeRequired)
                {
                    while (!_control.IsHandleCreated)
                    {
                        if (_control.Disposing || _control.IsDisposed)
                        {
                            return;
                        }
                    }
                    updatePictureBoxImg uLEvt = new updatePictureBoxImg(updatePictureBoxImg_EVT);
                    _control.Invoke(uLEvt, new object[] { _control, bt });
                }
                else
                {
                    _control.Image = bt;
                    //_control.Refresh();
                }
            }
            catch(Exception ex)
            {

            }
            
        }

        public delegate void DrawingCallbackBitmap(Bitmap _bitmap);
    }
}
