import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Base64;
import com.alibaba.fastjson2.JSONObject;

public class demo {
    public static String img2base64(String path) throws IOException {
        File file = new File(path);
        InputStream inputStream = new FileInputStream(file);
        byte[] buffer = new byte[(int) file.length()];
        inputStream.read(buffer);
        inputStream.close();

        // 将图片转换为 Base64 编码的字符串
        String imageBase64 = Base64.getEncoder().encodeToString(buffer);
        return imageBase64;
    }
    public static void main(String[] args) throws Exception  {
        // 创建 URL 对象
        URL url = new URL("http://127.0.0.1:5000/api/paddle");

        // 打开连接
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("POST");

        // 设置请求头信息
        connection.setRequestProperty("Content-Type", "application/json");
        connection.setRequestProperty("Accept", "application/json");

        // 启用输出流，向服务器发送数据
        connection.setDoOutput(true);

        String imgPath = "C:\\Users\\24525\\Desktop\\CSPPT\\系统能力综合培养\\OCRdemo\\JavaDemo\\test.jpg";
        String base64Img = img2base64(imgPath);
        // 创建 JSON 请求数据
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("ImageBase64", base64Img);
        jsonObject.put("IsCorrection", 1);

        String requestBody = jsonObject.toJSONString();

        // 发送请求数据
        try(OutputStream os = connection.getOutputStream()) {
            byte[] input = requestBody.getBytes("utf-8");
            os.write(input, 0, input.length);
        }

        // 读取响应
        try(BufferedReader br = new BufferedReader(
                new InputStreamReader(connection.getInputStream(), "utf-8"))) {
            StringBuilder response = new StringBuilder();
            String responseLine = null;
            while ((responseLine = br.readLine()) != null) {
                response.append(responseLine.trim());
            }
            System.out.println(response.toString());
        }
    }
}
