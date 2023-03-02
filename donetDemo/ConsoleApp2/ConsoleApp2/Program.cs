using System.Net.Http;

HttpClient client = new HttpClient();
byte[] imgBytes = File.ReadAllBytes("C:\\Users\\24525\\Desktop\\CSPPT\\系统能力综合培养\\OCRdemo\\test.jpg");
string imgBase64 = Convert.ToBase64String(imgBytes);
var values = new Dictionary<string, string>
{
    { "ImageBase64", imgBase64 },
    { "IsCorrection", "1" }
};

string url = "http://127.0.0.1:5000/api/paddle";

var data = new FormUrlEncodedContent(values);
var response = await client.PostAsync(url, data);
string responseString = await response.Content.ReadAsStringAsync();
Console.WriteLine(responseString);