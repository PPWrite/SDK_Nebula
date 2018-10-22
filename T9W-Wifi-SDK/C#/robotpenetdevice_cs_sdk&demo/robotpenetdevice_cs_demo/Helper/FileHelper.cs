using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace rbt_win32_2_demo.Helper
{
    /// <summary>
    /// 文件读写器
    /// </summary>
    public class FileHelper
    {
        /// <summary>
        /// 
        /// </summary>
        public void CreatFile(string filePath)
        {
            if(!File.Exists(filePath))
            {
                File.Create(filePath);
            }
        }

        public void FileWrite(string filePath,Dictionary<string, string> _dic)
        {
            FileStream fs = new FileStream(filePath, FileMode.OpenOrCreate,FileAccess.ReadWrite);
            StreamWriter sw = new StreamWriter(fs,Encoding.UTF8);
            
            foreach (var item in _dic)
            {
                sw.WriteLine(string.Format("{0},{1}",item.Key,item.Value));
            }

            sw.Flush();
            //关闭流
            sw.Close();
            fs.Close();
        }

        public Dictionary<string,string> FileRead(string filePath)
        {
            Dictionary<string, string> dicResult = new Dictionary<string, string>();
            CreatFile(filePath);
            StreamReader sr = new StreamReader(filePath,Encoding.UTF8, false);
            String line;
            //sr.ReadLine();//跳过第一行
            while ((line = sr.ReadLine()) != null)
            {
                string[] strList = line.Split(',');
                dicResult.Add(strList[0], strList[1]);
            }
            sr.Close();
            return dicResult;
        }

        public void FileWriteForDeviceInfo(string filePath, List<DeviceSettingInfo> _dic)
        {
            FileStream fs = new FileStream(filePath, FileMode.OpenOrCreate, FileAccess.ReadWrite);
            Encoding encoding = Encoding.GetEncoding("GB2312");
            StreamWriter sw = new StreamWriter(fs, encoding);

            foreach (var item in _dic)
            {
                sw.WriteLine(string.Format("{0},{1},{2}", item.DeviceNum, "num=" + item.StudentNum, "name=" + item.StudentName));
            }

            sw.Flush();
            //关闭流
            sw.Close();
            fs.Close();
        }

        public List<DeviceSettingInfo> FileReadForDeviceInfo(string filePath)
        {
            List<DeviceSettingInfo> dicResult = new List<DeviceSettingInfo>();
            CreatFile(filePath);
            Encoding encoding = Encoding.GetEncoding("GB2312");
            StreamReader sr = new StreamReader(filePath, encoding, false);
            String line;
            //sr.ReadLine();//跳过第一行
            while ((line = sr.ReadLine()) != null)
            {
                string[] strList = line.Split(',');
                string DeviceNum = strList.Length > 0 ? strList[0] : "";
                string StudentNum = strList.Length > 1 ? strList[1].Replace("num=","") : "";
                string StudentName = strList.Length > 2 ? strList[2].Replace("name=", "") : "";
                dicResult.Add(new DeviceSettingInfo()
                {
                    DeviceNum = DeviceNum,
                    StudentNum = StudentNum,
                    StudentName = StudentName,
                });
            }
            sr.Close();
            return dicResult;
        }

        public void FileWriteStr(string filePath, string data)
        {
            FileStream fs = new FileStream(filePath, FileMode.OpenOrCreate, FileAccess.ReadWrite);
            StreamWriter sw = new StreamWriter(fs, Encoding.UTF8);

            sw.Write(data);

            sw.Flush();
            //关闭流
            sw.Close();
            fs.Close();
        }

        public string FileReadStr(string filePath)
        {
            string strResult = string.Empty;
            CreatFile(filePath);
            StreamReader sr = new StreamReader(filePath, Encoding.UTF8, false);

            strResult = sr.ReadToEnd();

            sr.Close();
            return strResult;
        }
    }
}
