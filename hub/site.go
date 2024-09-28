package main


import (
    "bufio"
    "fmt"
    "os"
    "strings"
    "errors"    
)

	// Site has an address (URL) and a list of content items  
	type Site struct {
		Address     string
		Port        string
		Base        string
		Styles      string
		Images      string
    Scripts     string
    Attachments string
		Items  []ContentItem
	}

	// ContentItem is a page - used to generate site navigation.
	type ContentItem struct {
		Type    string
		Action  string
		Title   string
	}

	func LoadSite(filepath string) (*Site, error) {

		var site  *Site  = new(Site)
		site.Address     = ""
		site.Port        = "5001"
		site.Base        = "./content/"
		site.Styles      = "./static/css"
		site.Images      = "./static/img"
		site.Scripts     = "./static/js"
		site.Attachments = "./static/attachments"
		site.Items = nil
		var inContent bool = false  
	
		file, err := os.Open(filepath)
		if err != nil {
		  return nil, err
		}
		defer file.Close()
	
		fmt.Println("Opened " + filepath + " OK.")
	
		scanner := bufio.NewScanner(file)
		for scanner.Scan() {
			line    := strings.TrimSpace(scanner.Text())
			if len(line) > 0 {
				words   := strings.Fields(line)
				keyword := strings.ToUpper(words[0])
				if !inContent {
					if keyword        == "SITE" {
						site.Address     = words[1]
					} else if keyword == "PORT" {
						site.Port        = words[1]
					} else if keyword == "BASE" {
						site.Base        = words[1]
					} else if keyword == "STYLES" {
						site.Styles      = words[1]
					} else if keyword == "IMAGES" {
						site.Images      = words[1]
					} else if keyword == "SCRIPTS" {
						site.Scripts     = words[1]
					} else if keyword == "ATTACHMENTS" {
						site.Attachments = words[1]
					} else if keyword == "CONTENT" {
						inContent = true
					} else {
						return nil, errors.New("Illegal statement in " + filepath + ". Statement is: " + line) 	
					}
				} else {
					n := len(words)
					if n < 3 {
						return nil, errors.New("Missing values in " + filepath + ". Statement is: " + line) 	
					}				
					item := new(ContentItem)		
					item.Type   = words[0]
					item.Action = words[1]
					item.Title = UnQuote(UnSplit(words[2:]))
					site.Items  = append(site.Items, *item)
				}
			}
		}
	
		if err := scanner.Err(); err != nil {
			return nil, err
		}
	
		return site, nil
	}
	
	func PrintSite(site *Site) {
		fmt.Println("=========================")
		fmt.Println("SITE Address:     " + site.Address)
		fmt.Println("     Port:        " + site.Port)
		fmt.Println("     Base:        " + site.Base)
		fmt.Println("     Styles:      " + site.Styles)
		fmt.Println("     Images:      " + site.Images)
		fmt.Println("     Scripts:     " + site.Scripts)
		fmt.Println("     Attachments: " + site.Attachments)
		for i := range site.Items {
			fmt.Println(site.Items[i].Type + " @ " + site.Items[i].Action + " = [" + site.Items[i].Title + "]")
		}
		fmt.Println("")
	}

func UnSplit(words []string) string {
   	s := ""
    for i := 0; i < len(words); i++ {
    	if len(s) > 0 {
    	 s = s + " "
    	} 
      s = s + words[i]
    }
    return s
} 

func UnQuote(s string) string {
	n := len(s)
    if n >= 2 {
      if s[0] == '"' && s[n-1] == '"' {
		s = s[1:n-1]      	
      }
    } 

    return s
}
