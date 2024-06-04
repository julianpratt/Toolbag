package main


import (
	"net/http"
	"github.com/gin-gonic/gin"
	//"html/template"
	"log"
	"bytes"
    "github.com/yuin/goldmark"
	"github.com/yuin/goldmark/extension"
    "io/ioutil"
)

func getMarkdown(filepath string, filename string) string {

	fullname := filepath + filename + ".md"

    source, err := ioutil.ReadFile(fullname)
    if err != nil {
        return ""
    }

	md := goldmark.New(goldmark.WithExtensions(extension.GFM),)

	var buf bytes.Buffer
	if err := md.Convert(source, &buf); err != nil {
		log.Fatal(err)
		return ""
		}

	return "<article class=\"markdown-body\">\n" + buf.String() + "</article>\n"
}

func writePage(c *gin.Context, html string, status int) {

	w := c.Writer
	header := w.Header()
	header.Set("Content-Type", "text/html")
	w.WriteHeader(status)
	w.Write([]byte(html))
	w.(http.Flusher).Flush()
}

func notFound(c *gin.Context, site *Site) {

	writePage(c, getHTML("Not Found", site, "<b>Not Found</b>"), http.StatusNotFound)
}

func pageOutput(c *gin.Context, site *Site, name string) {
	body := getMarkdown(site.Base, name)
	if len(body) > 0 {
		writePage(c, getHTML(name, site, body), http.StatusOK)	
	} else {
		notFound(c, site)
	}
}


func main() {
	r := gin.Default()

	site, err := LoadSite("./site.txt")
	if err != nil {
    	log.Fatal(err)
  	}
	PrintSite(site)  

	r.Static("/css",          site.Styles)
    r.Static("/img",          site.Images)
    r.Static("/js",           site.Scripts)
    r.Static("/attachments",  site.Attachments)

	r.GET("/", func(c *gin.Context) {
		pageOutput(c, site, "home")
	})

	r.GET("/home", func(c *gin.Context) {
		pageOutput(c, site, "home")
	})

	// This handler will match /article/fred but will not match /article/ or /article
	r.GET("/topic/:name", func(c *gin.Context) {
		pageOutput(c, site, c.Param("name"))
	})

	// This handler will match /article/fred but will not match /article/ or /article
	r.GET("/page/:name", func(c *gin.Context) {
		pageOutput(c, site, c.Param("name"))
	})
	
	// This handler will match /article/fred but will not match /article/ or /article
	r.GET("/:name1/:name2", func(c *gin.Context) {
		pageOutput(c, site, c.Param("name1") + "/" + c.Param("name2"))
	})

	// This handler will match /topic/subtopic/fred but will not match /topic/ or /topic/subtopic
	r.GET("/:name1/:name2/:name3", func(c *gin.Context) {
		pageOutput(c, site, c.Param("name1") + "/" + c.Param("name2")+ "/" + c.Param("name3"))
	})

	/*

	r.GET("/ping", func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{"message": "pong",})
	})

	// This handler will match /user/john but will not match /user/ or /user
	r.GET("/user/:name", func(c *gin.Context) {
		name := c.Param("name")
		writePage(c, getHTML("User Test", "<H1>Hello " + name + "</H1>"), http.StatusOK)	
	})

	// However, this one will match /user/john/ and also /user/john/send
	// If no other routers match /user/john, it will redirect to /user/john/
	r.GET("/user/:name/*action", func(c *gin.Context) {
		name := c.Param("name")
		action := c.Param("action")
		message := "User is " + name + " action is " + action[1:len(action)]
		c.String(http.StatusOK, message)
	})

	r.GET("/hi", func(c *gin.Context) {
        //n, set := c.GetPostForm("n")
        n := c.Query("n")
        if len(n) > 0 {
        	c.String(http.StatusOK,"Hello " + n)
        } else {
        	c.HTML(http.StatusOK, "fred", gin.H{"status": "success", })        	
        }
    })

    r.GET("/fred", func(c *gin.Context) {
    	script := `setInterval('n.innerHTML+="Fred Bloggs! "',100);`
    	writePage(c, getHTML("Script Test", "<p id=n></p><script>" + script + "</script>"), http.StatusOK)
    })

    r.GET("/menu/:menuname", func(c *gin.Context) {
    	menuname := c.Param("menuname")
		page, err := GetPage(menus, menuname, "Uniper", "/menu/")
  		if err != nil {
  		  notFound(c)
  		} else {
  	      writePage(c, page, http.StatusOK)
  		}
    })
*/

	r.Run(":" + site.Port) // listen and serve on 0.0.0.0:port (e.g. for windows "localhost:5001")
}
