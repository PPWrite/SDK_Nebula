using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace WindowsForms.Class
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

        public void CreateDirectory(string filePath)
        {
            if (!Directory.Exists(filePath))//判断是否存在
            {
                Directory.CreateDirectory(filePath);//创建新路径
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

        public List<string> FileRead_list(string filePath)
        {
            List<string> dicResult = new List<string>();
            CreatFile(filePath);
            StreamReader sr = new StreamReader(filePath, Encoding.UTF8, false);
            String line;
            //sr.ReadLine();//跳过第一行
            while ((line = sr.ReadLine()) != null)
            {
                dicResult.Add(line);
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

        public void FileWriteStr(string filePath, string fileName, string data)
        {
            CreateDirectory(filePath);
            FileStream fs = new FileStream(filePath + fileName, FileMode.OpenOrCreate, FileAccess.ReadWrite);
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
