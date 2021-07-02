function get(url, method) {
    return new Promise(function(succeed, fail) {
      var request = new XMLHttpRequest();
      request.open(method, url, true);
      request.addEventListener("load", function() {
        if (request.status < 400)
          succeed(request.response);
        else
          fail(new Error("Request failed: " + request.statusText));
      });
      request.addEventListener("error", function() {
        fail(new Error("Network error"));
      });
      request.send();
    });
  }
  var jsonObj = {
       obj:""
  };
  var route_sufix;
  
  var request_func = function(route, method) { get("https://localhost:44329/getnews" + route, method).then(function(response) {
    return JSON.parse(response);
  }).then(function(data) {
   jsonObj.obj = data;
   console.log("succes");
   create_element(jsonObj.obj);
  }).catch(function(error){
      let div = document.getElementById("content");
      let els = document.getElementsByClassName("com");
      els[0].remove();
    console.log("Error!!!");
    div.append(error);
  }); 
  };
   var get_news = function(param) {
     request_func("?substring=" + param, "GET");
   }
  var create_element = function(obj){
      let div = document.getElementById("content");
      let com = document.createElement("div");
      com.className = "com"
      let e = document.getElementById("count");
      e.append(obj.countOfNews);
      obj.news.forEach(element => {
          let d = document.createElement("div");
          d.className = "concrete";
          let p = document.createElement("p");
          p.append(element.title);
          d.appendChild(p);
          let p1 = document.createElement("p");
          p1.append(element.anhor);
          d.appendChild(p1);
          let p2 = document.createElement("p");
          p2.append(element.content);
          d.appendChild(p2);
          com.appendChild(d);
      });
      div.appendChild(com);
  }
  document.addEventListener('click', function(event) {
  
    if (event.target.dataset.news != undefined) {
      get_news(document.getElementById("input").value);
    }});