const axios = require('axios')
const fs = require('fs')
// Base64编码
let img_raw = fs.readFileSync("../test.jpg");
let img_b64 = img_raw.toString('base64');

// 发送请求
axios.post("http://www.7-an.com:5000/api/paddle", {
  ImageBase64:img_b64,
  IsCorrection:1,
}).then((res) => {
  console.log(res.data)
})