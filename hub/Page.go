package main


func getHTML(title string, site *Site, body string) string {

	html := PageHeader(title) 
	html += PageMenu(site)
    html += body
	html += PageFooter()

	return html
}


func PageHeader(title string) string {

	style := "site"
	stylesheet := "/css/" + style + ".css"

	html := "<!DOCTYPE html>\n"
	html += "<HTML>\n"
	html += "  <HEAD>\n"
	html += "    <TITLE>" + title + "</TITLE>\n"
	html += "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
    html += "    <meta charset=\"UTF-8\">\n"
    html += "    <link   rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css\"\n"
    html += "            integrity=\"sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3\" crossorigin=\"anonymous\">\n"    
	html += "    <link rel=\"stylesheet\" type=\"text/css\" href=\"" + stylesheet + "\">\n"
  	html += "  </head>\n"
	html += "  <body class=\"container\">\n"

	return html
}

func PageMenu(site *Site) string {

	inTopic := false  
	
	html := "  	<nav class=\"navbar navbar-expand-lg navbar-light bg-light\">\n"
	//html += "    <div class=\"container\">\n"
	html += "      <a class=\"navbar-brand\" href=\"/home\">Hub</a>\n"
	html += "      <button class=\"navbar-toggler\" type=\"button\" data-bs-toggle=\"collapse\" data-bs-target=\"#menuItems\" aria-controls=\"menuItems\" aria-expanded=\"false\" aria-label=\"Toggle navigation\">\n"
	html += "          <span class=\"navbar-toggler-icon\"></span>\n"
  	html += "      </button>\n"
	html += "      <div class=\"collapse navbar-collapse\" id=\"menuItems\">\n"
	html += "        <ul class=\"navbar-nav me-auto mb-2 mb-lg-0\">\n"

	for i := range site.Items {
		pageType := site.Items[i].Type
		action   := site.Items[i].Action
		title    := site.Items[i].Title
		
		if pageType == "subtopic" && inTopic {
			html += "              <li><a class=\"dropdown-item\" href=\"/" + action + "\">" + title + "</a></li>\n"
		} else if pageType == "article" && inTopic {
			// Ignore article in topic
		} else if inTopic {
			html += "            </ul>\n"
			html += "          </li>\n"
			inTopic = false
		}
		if pageType == "page" {
			html += "          <li class=\"nav-item\"><a class=\"nav-link\" href=\"/page/" + action + "\">" + title + "</a></li>\n"
		} else if pageType == "topic" {
			html += "          <li class=\"nav-item dropdown\">\n"
			html += "            <a class=\"nav-link dropdown-toggle\" href=\"/topic/" + action + "\" role=\"button\" data-bs-toggle=\"dropdown\">" + title + "</a>\n"
			html += "            <ul class=\"dropdown-menu\">\n"
			inTopic = true
		}
	}

	html += "        </ul>\n"
	//html += "        <form class=\"d-flex\">\n"
	//html += "          <input class=\"form-control me-2\" type=\"search\" placeholder=\"Search\">\n"
	//html += "          <button class=\"btn btn-outline-primary\" type=\"submit\">Search</button>\n"
	//html += "        </form>\n"
	html += "      </div>\n"
	//html += "    </div>\n"
	html += "  </nav>\n"
	html += "  <br/>\n"  

	return html
 
}
  
func PageFooter() string {

    html := "	<SCRIPT SRC=\"https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js\"\n" 
    html += "	        INTEGRITY=\"sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p\" CROSSORIGIN=\"anonymous\"></SCRIPT>\n"
    html += "  </BODY>\n"
	html += "</HTML>"

	return html
}
