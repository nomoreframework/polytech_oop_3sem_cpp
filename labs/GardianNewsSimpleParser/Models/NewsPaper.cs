using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GardianNewsSimpleParser.Models
{
    public class NewsPaper
    {
        public int CountOfNews
        {
            get
            {
                if (News == null) throw new Exception(new NullReferenceException().Message +"\n" +  "List<News> was null");
                return News.Count;
            }
        }
        public List<News> News { get; set; }
        public NewsPaper()
        {
            News = new List<News>();
        }
    }
}
