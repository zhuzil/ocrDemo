/*
 * @Author: your name
 * @Date: 2023-03-02 22:36:27
 * @LastEditTime: 2023-03-02 22:58:52
 * @LastEditors: DESKTOP-2OD8ACM
 * @Description: In User Settings Edit
 * @FilePath: \OCRdemo\cppDemo\demo.cpp
 */
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <malloc.h>
#include "HTTPRequest.hpp"

using namespace std;


static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(const char* bytes_to_encode, unsigned int in_len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for (i = 0; (i < 4); i++)
            {
                ret += base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }
    if (i)
    {
        for (j = i; j < 3; j++)
        {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
        {
            ret += base64_chars[char_array_4[j]];
        }

        while ((i++ < 3))
        {
            ret += '=';
        }

    }
    return ret;
}



int main() {
    fstream f;
    f.open("test.jpg", ios::in | ios::binary);
    f.seekg(0, std::ios_base::end);     //设置偏移量至文件结尾
    std::streampos sp = f.tellg();      //获取文件大小
    int size = sp;

    char* buffer = (char*)malloc(sizeof(char) * size);
    f.seekg(0, std::ios_base::beg);     //设置偏移量至文件开头
    f.read(buffer, size);                //将文件内容读入buffer
    cout << "file size:" << size << endl;

    string imgBase64 = base64_encode(buffer, size);         //编码
    cout << "img base64 encode size:" << imgBase64.size() << endl;
    
    try
    {
        http::Request request{ "http://127.0.0.1:5000/api/paddle" };
        const std::string body = "{\"IsCorrection\": 1, \"ImageBase64\": \"" + imgBase64 + "\"}";
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
            });
        std::cout << std::string{ response.body.begin(), response.body.end() } << '\n'; // print the result
    }
    catch (const std::exception& e)
    {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }

    return 0;
}
