package main

import (
	"bytes"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
	"unsafe"
)

func main() {
	// 读取本地图片文件
	fileData, err := ioutil.ReadFile("../test.jpg")
	if err != nil {
		panic(err)
	}
	// 将图片文件转换成base64编码
	imageBase64 := base64.StdEncoding.EncodeToString(fileData)

	song := make(map[string]string)
	song["ImageBase64"] = imageBase64
	song["IsCorrection"] = "1"
	bytesData, _ := json.Marshal(song)

	res, err := http.Post("http://127.0.0.1:5000/api/paddle",
		"application/json;charset=utf-8", bytes.NewBuffer([]byte(bytesData)))
	if err != nil {
		fmt.Println("Fatal error ", err.Error())
	}

	defer res.Body.Close()

	content, err := ioutil.ReadAll(res.Body)
	if err != nil {
		fmt.Println("Fatal error ", err.Error())
	}

	str := (*string)(unsafe.Pointer(&content)) //转化为string,优化内存
	fmt.Println(*str)

}
