#pragma once
#include <iostream>
#include <string>
#include <json/json.h>
#include "../net/net.h"

using namespace std;

/**

    ����URL��

    http://api.ocrku.com/tencent
    ����ʽ��

    POST
    ������

    ������	��ѡ	����	˵��
    token	��	string	�û���Կ���������Ļ�ȡ(token)
    aid	��	string	ץ����ȡ
    asig	��	string	�ɿ�, ץ����ȡ��û�п�����
    capcd	��	string	�ɿ�, ץ����ȡ��û�п�����
    qq	��	string	�ɿ�, ץ����ȡ��û�п�����
    type	��	string	ʶ�����ͣ�����鿴��������
    referer	��	string	ҳ����Դ,���磺http://www.xxx.xxx/
    secretkey	��	string	����Key���������Ļ�ȡ
    ����ʾ��

     {
      "status": 0,
      "msg": "�ɹ�",
      "data": {
	    "ticket": "t02hSZogcM-qNFIaDyCcXHKLHCu6hV8IUJbrmUCsGeSvVDSna0yV72f_P8qnz0WhndaI2BSDy5-3oGYAPN6jVF1bpN-pgsxUBd-q84TDF5kVq-tvjWub6_Vjg**",
	    "randstr": "@OBM"
      }
    }
 */

namespace slide {
    string recognitiaon_tencent(string token, string aid, string asig, string capcd, string qq, string type, string referer, string secretkey) {
        string result;
        string postdata = "token=" + token + "&aid=" + aid + "&asig=" + asig + "&capcd=" + capcd + "&qq=" + qq +
            "&type=" + type + "&referer=" + referer;
        string str = net::http_post("http://api.ocrku.com/tencent", "", postdata, NULL);
        str = UTF8ToGB(str.c_str());
        //printf(str.c_str());
		Json::CharReaderBuilder builder;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
		Json::Value root;
		JSONCPP_STRING errs;
		bool ok = reader->parse(str.data(), str.data() + str.length(), &root, &errs);
		if (ok && errs.size() == 0)
		{
			int32_t status = root["status"].asInt();
			if (status == 0) {
				Json::Value data = root["data"];
				if (data != NULL) {
					result = data["ticket"].asString();
				}
			}
		}

        //{"status":0,"msg":"\u6210\u529F","data":{"ticket":"t02eEj6h3KwnOYlXHRdr3xB2XcQkIbesftbEDZQ8I3dd5stU_fDboHqEutoWNjGerD61LAtVLm2cGrlzAq5F_huPLwN16Yg_KjqYA_dGAZF-Vgu8ZwJhPh5Ew**","randstr":"@5uT"}}
        return result;
    }

	string recognitiaon_tencent2(string token, string aid, string asig, string capcd, string qq, string type, string referer, string secretkey) {
		string result;
		string href = net::curl_escape("https://ssl.captcha.qq.com/");
		string encode_url = net::curl_escape(referer);
		string postdata = "token=" + token + "&dev_id=1&act=qcaptcha&type=shibie" + "&aid=" + aid + "&asig=" + asig + "&cap_cd=" + capcd + "&uid=" + qq +
			"&href=" + href + "&clientype=1" + "&referer=" + encode_url;

		string str = net::http_post("https://ocr.xinby.cn/api.php", "", postdata, NULL);
		str = UTF8ToGB(str.c_str());
		//printf(str.c_str());
		Json::CharReaderBuilder builder;
		const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
		Json::Value root;
		JSONCPP_STRING errs;
		bool ok = reader->parse(str.data(), str.data() + str.length(), &root, &errs);
		if (ok && errs.size() == 0)
		{
			int32_t code = root["code"].asInt();
			if (code == 1) {
				Json::Value data = root["data"];
				if (data != NULL) {
					result = data["ticket"].asString();
				}
			}
		}

		//{"status":0,"msg":"\u6210\u529F","data":{"ticket":"t02eEj6h3KwnOYlXHRdr3xB2XcQkIbesftbEDZQ8I3dd5stU_fDboHqEutoWNjGerD61LAtVLm2cGrlzAq5F_huPLwN16Yg_KjqYA_dGAZF-Vgu8ZwJhPh5Ew**","randstr":"@5uT"}}
		return result;
	}
}
 