# -*-codeing = utf-8 -*-
'''
Author: your name
Date: 2023-03-01 23:34:53
LastEditTime: 2023-03-01 23:35:11
LastEditors: DESKTOP-2OD8ACM
Description: In User Settings Edit
FilePath: \OCRdemo\python\demo.py
'''
import base64
import requests
#image转base64
def encode_base64(file):
    with open(file,'rb') as f:
        img_data = f.read()
        base64_data = base64.b64encode(img_data)
        return base64_data

file = "./TableOCR2.jpg"
base64_data = encode_base64(file)
img_str = base64_data.decode()   #img_str是字符串类型变量，decode()对字节类型变量进行解码，bytes->str
Data = {
    "ImageBase64":img_str,
    "ImageUrl":"https://ocr-demo-1254418846.cos.ap-guangzhou.myqcloud.com/document/TableOCR/TableOCR2.jpg",
    "SecretId":"123",
    "SecretKey":"123"
}
#访问服务
result = requests.post('http://127.0.0.1:5000/ocr',data=Data)
print(result.text)

