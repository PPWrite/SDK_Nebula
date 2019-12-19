﻿using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;

namespace WindowsForms.Class
{
    public class SerializeHelper
    {
        /// <summary>
        /// 将C#数据实体转化为xml数据
        /// </summary>
        /// <param name="obj">要转化的数据实体</param>
        /// <returns>xml格式字符串</returns>
        public static string XmlSerialize<T>(T obj)
        {
            DataContractSerializer serializer = new DataContractSerializer(typeof(T));
            MemoryStream stream = new MemoryStream();
            serializer.WriteObject(stream, obj);
            stream.Position = 0;

            StreamReader sr = new StreamReader(stream);
            string resultStr = sr.ReadToEnd();
            sr.Close();
            stream.Close();

            return resultStr;
        }

        /// <summary>
        /// 将xml数据转化为C#数据实体
        /// </summary>
        /// <param name="json">符合xml格式的字符串</param>
        /// <returns>T类型的对象</returns>
        public static T XmlDeserialize<T>(string xml)
        {

            DataContractSerializer serializer = new DataContractSerializer(typeof(T));
            MemoryStream ms = new MemoryStream(System.Text.Encoding.UTF8.GetBytes(xml.ToCharArray()));
            T obj = (T)serializer.ReadObject(ms);
            ms.Close();

            return obj;
        }

        /// <summary>
        /// JSON序列化
        /// </summary>
        public static string JsonSerializer<T>(T t)
        {
            string jsonString = null;
            try
            {
                DataContractJsonSerializer ser = new DataContractJsonSerializer(typeof(T));
                MemoryStream ms = new MemoryStream();

                ser.WriteObject(ms, t);
                jsonString = Encoding.UTF8.GetString(ms.ToArray());
                ms.Close();
            }
            catch (Exception ex)
            {
                return ex.Message;
            }

            // return (DesEncrypt(jsonString));
            return jsonString;
        }

        /// <summary>
        /// JSON序列化
        /// </summary>
        public static string JsonSerializer<T>(Type t, T obj)
        {
            string jsonString = null;
            try
            {
                DataContractJsonSerializer ser = new DataContractJsonSerializer(t);
                MemoryStream ms = new MemoryStream();
                ser.WriteObject(ms, obj);
                jsonString = Encoding.UTF8.GetString(ms.ToArray());
                ms.Close();
            }
            catch (Exception ex)
            {
                return ex.Message;
            }

            return jsonString;
            // return (DesEncrypt(jsonString));
        }

        /// <summary>
        /// JSON反序列化
        /// </summary>
        public static T JsonDeserialize<T>(string jsonString)
        {
            DataContractJsonSerializer ser = new DataContractJsonSerializer(typeof(T));
            MemoryStream ms = new MemoryStream(Encoding.UTF8.GetBytes(jsonString));
            T obj = (T)ser.ReadObject(ms);
            return obj;
        }
    }
}
