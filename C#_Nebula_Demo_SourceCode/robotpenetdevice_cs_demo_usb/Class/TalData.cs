using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsForms.Class
{
    public class TalData
    {
        public int code { get; set; }
        public string message { get; set; }
        public _Data data { get; set; }

    }
    public class _Data
    {
        public string stu_id { get; set; }
        public string session_id { get; set; }
        public string question_id { get; set; }
        public string[] data { get; set; }
    }
}
