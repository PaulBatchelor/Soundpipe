package main

import "encoding/json"
import "io/ioutil"
import "fmt"

func main() {
	byt, _ := ioutil.ReadFile("my_zita.dsp.json")
	var dat map[string]interface{}

	if err := json.Unmarshal(byt, &dat); err != nil {
		panic(err)
	}

	items := dat["ui"].([]interface{})[0].(map[string]interface{})["items"].([]interface{})

	for _, val := range items {
		mymap := val.(map[string]interface{})
		fmt.Println(mymap["items"])
	}
}
