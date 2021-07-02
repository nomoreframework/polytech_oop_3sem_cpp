using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Threading.Tasks;
using System.Net.Http;
using AngleSharp.Html.Dom;
using AngleSharp.Html.Parser;
using System.Text;
using GardianNewsSimpleParser.Models;
using System.Linq;

namespace GardianNewsSimpleParser.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class GetNewsController : ControllerBase
    {

        private readonly ILogger<GetNewsController> _logger;
        private readonly HttpClient httpClient;
        private NewsPaper newsPaper;
        private News news;

        public GetNewsController(ILogger<GetNewsController> logger)
        {
            _logger = logger;
            httpClient = new HttpClient();
            newsPaper = new NewsPaper();
        }

        [HttpGet]
        public async Task<IActionResult> GetNews(string substring)
        {
            if (String.IsNullOrWhiteSpace(substring)) return NotFound("Empty string is not valid argument!");
            HttpResponseMessage message = await httpClient.GetAsync("https://www.theguardian.com/uk/rss");
            string content = await message.Content.ReadAsStringAsync();
            IHtmlDocument angle = new HtmlParser().ParseDocument(content);
            int id = 0;
            foreach(var el in angle.GetElementsByTagName("item"))
            {
                if (!el.TextContent.Contains(substring)) continue;
                news = new News();
                var title = el.FirstElementChild;
                var link = title.NextElementSibling;
                var discription = link.NextElementSibling;

                news.Id = id;
                news.Title = title.TextContent;
                news.Anhor = link.TextContent;
                news.Content = discription.TextContent;

                newsPaper.News.Add(news);
                id++;
            }
            return Ok(newsPaper);
        }
    }
}
