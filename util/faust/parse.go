package main

import "encoding/json"
import "io/ioutil"
import "fmt"
import "os"
import "text/template"

type Blah struct {
	Count int
	Name string
	Params []string
}

func main() {
	
	if len(os.Args) == 1 {
		fmt.Println("Please specify a file")
		os.Exit(1)
	}

	var cnt Blah	
	
	tmpl, err := template.ParseFiles("sp_faust.c.template")
	
	if err != nil { panic(err) }	
	
	byt, _ := ioutil.ReadFile(os.Args[1])

	var dat map[string]interface{}

	if err := json.Unmarshal(byt, &dat); err != nil {
		panic(err)
	}

	
	items := dat["ui"].([]interface{})[0].(map[string]interface{})["items"].([]interface{})

	cnt.Count = len(items)
	cnt.Name = "saw" 
	for _, val := range items {
		mymap := val.(map[string]interface{})
		fmt.Println(mymap["label"])
		cnt.Params = append(cnt.Params, mymap["label"].(string))
	}

	tmpl.ExecuteTemplate(os.Stdout, "sp_faust.c.template", cnt)
}
