
// #include <user_interface.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include "main.h"
#include "HashMap.h"

#define SITE_PATH "/site"
#define TEMPLATE_EXT "tpl"
#define TEMPLATE_TAG_BEGIN "<%"
#define TEMPLATE_TAG_END "%>"
#define TEMPLATE_DATATYPE "text/html"

File web_UploadFile;
File web_UpgradeFile;

CreateHashMap(webDataTypes, String, char*, 20);
CreateHashMap(webInsertionStrings, String, String, 20); 
ESP8266WebServer server(80);

String readStringUntilStr(Stream* src, String searchString)
{
	String retvalue = "";
	do
	{
		retvalue += (char)src->read();
		if (retvalue.substring(retvalue.length() - searchString.length()) == searchString)
		{
			retvalue = retvalue.substring(0, retvalue.length() - searchString.length());
			break;
	}
} while (src->available() > 0);
return retvalue;
}

void web_HandleUpload()
{
	int i;
	String filename;
	HTTPUpload& upload = server.upload();
	switch (upload.status)
	{
	case UPLOAD_FILE_START:
		filename = upload.name;
#ifdef SERIAL_DEBUG
		Serial.println("WEB: File Upload");
		Serial.print("WEB: Filename - ");
		Serial.println(filename);
#endif
		web_UploadFile = SPIFFS.open(filename, "w");
		if (!web_UploadFile)
		{
			Serial.println("File open failed");
		}
		break;
	case UPLOAD_FILE_WRITE:
		if (web_UploadFile)
		{
			web_UploadFile.write(upload.buf, upload.currentSize);
			Serial.print("Write bytes - ");
			Serial.println(upload.currentSize);
		}
		break;
	case UPLOAD_FILE_END:
		if (web_UploadFile)
		{
			web_UploadFile.close();
			Serial.print("Total - ");
			Serial.println(upload.totalSize);
			Serial.println("File Closed");
		}
		break;
	}
}

void web_HandleUpgrade()
{
	int filesize;
	//  int i;
	//  String filename;
	HTTPUpload& upload = server.upload();
	switch (upload.status)
	{
	case UPLOAD_FILE_START:
		//      filename = upload.name;
#ifdef SERIAL_DEBUG
		Serial.println("WEB: Firmware Upgrade");
#endif
		web_UpgradeFile = SPIFFS.open("/firmware.bin", "w");
		if (!web_UpgradeFile)
		{
			Serial.println("File open failed");
		}
		break;
	case UPLOAD_FILE_WRITE:
		if (web_UpgradeFile)
		{
			web_UpgradeFile.write(upload.buf, upload.currentSize);
			//    #ifdef SERIAL_DEBUG
			//        Serial.print("Write bytes - ");
			//        Serial.println(upload.currentSize);
			//    #endif
		}
		break;
	case UPLOAD_FILE_END:
		if (web_UpgradeFile)
		{
			filesize = upload.totalSize;
			web_UpgradeFile.close();
#ifdef SERIAL_DEBUG  
			Serial.println("File Closed");
			Serial.print("Uploaded Firmware Size - ");
			Serial.println(filesize);
#endif
			// reopen for reading
			web_UpgradeFile = SPIFFS.open("/firmware.bin", "r");
			if (web_UpgradeFile)
			{
				if (!ESP.updateSketch(web_UpgradeFile, filesize))
				{
#ifdef SERIAL_DEBUG
					Serial.println("Update failed");
#endif
				}
			}
			else
			{
#ifdef SERIAL_DEBUG
				Serial.println("Can't open upgradefile");
#endif
			}
		}
		break;
	}
}

void web_HandleFiles()
{
#ifdef SERIAL_DEBUG
	Serial.print("WEB: File request - ");
	Serial.println(server.uri());
#endif
	String path = SITE_PATH + server.uri();
	String extension = path.substring(path.lastIndexOf(".") + 1);
	String dataType = "text/plain";
	String content = "";
	String template_tag;
	signed int keyindex;

#ifdef SERIAL_DEBUG
	Serial.print("WEB: Extension - ");
	Serial.println(extension);
	Serial.println(keyindex);
	Serial.println(webDataTypes[extension]);
	Serial.println(path);
#endif
	File dataFile = SPIFFS.open(path.c_str(), "r");
	if (dataFile)
	{
		if (extension == TEMPLATE_EXT)
		{
			dataType = TEMPLATE_DATATYPE;
			Serial.println("WEB - Process template");
			// read file
			do
			{
				content += readStringUntilStr(&dataFile, TEMPLATE_TAG_BEGIN);
				// ContentDebug = false;
				if (dataFile.position() >= dataFile.size())
				{
					break;
				}
				template_tag = readStringUntilStr(&dataFile, TEMPLATE_TAG_END);
				Serial.print("WEB - Insertiontag: ");
				Serial.println(template_tag);
				keyindex = webInsertionStrings.indexOf(template_tag);
				if (keyindex > -1)
				{
					Serial.println("Tag found");
					content += webInsertionStrings[template_tag];
				}
			} while (dataFile.position() < dataFile.size());

			server.send(200, dataType, content);
		}
		else
		{
			keyindex = webDataTypes.indexOf(extension);
			if (keyindex > -1)
			{
				Serial.println("Extension found");
				dataType = webDataTypes[extension];
			}
#ifdef SERIAL_DEBUG
			Serial.print("WEB: DataType - ");
			Serial.println(dataType);
#endif
			server.streamFile(dataFile, dataType);
		}
		dataFile.close();
	}
}

/*
void SetVal()
{
	// #ifdef SERIAL_DEBUG
	Serial.print("WEB: File request - ");
	Serial.println(web_GetUri());
	// #endif
}
*/

void web_Init()
{
#ifdef SERIAL_DEBUG
	Serial.println("WEB: Initialize Server");
#endif
	// Read config from file


	server.on("/uploadfile", HTTP_POST, []() { server.send(200, "text/plain", ""); }, web_HandleUpload);
	server.on("/upgrade", HTTP_POST, []() { server.send(200, "text/plain", ""); }, web_HandleUpgrade);

	// server.on("/setval", HTTP_GET, []() { server.send(200, "text/plain", ""); }, SetVal);

	server.onNotFound(web_HandleFiles);
	server.begin();

	webDataTypes["htm"] = "text/html";
	webDataTypes["html"] = "text/html";
	webDataTypes["css"] = "text/css";
	webDataTypes["js"] = "application/javascript";
	webDataTypes["png"] = "image/png";
	webDataTypes["gif"] = "image/gif";
	webDataTypes["jpg"] = "image/jpeg";
	webDataTypes["ico"] = "image/x-icon";
	webDataTypes["xml"] = "text/xml";
	webDataTypes["pdf"] = "application/pdf";
	webDataTypes["zip"] = "application/zip";

}

/*
void web_RegisterUrl(const char* uri, HTTPMethod method, std::function<void(void)> ufn)
{
	server.on(uri, method, []() { server.send(200, "text/plain", ""); }, ufn);
}
*/

void web_RegisterGetUrl(const char* uri, std::function<void(void)> ufn)
{
	server.on(uri, HTTP_GET, ufn);
}

void web_RegisterPostUrl(const char* uri, std::function<void(void)> ufn)
{
	server.on(uri, HTTP_POST, ufn);
}

String web_GetUri()
{
	return server.uri();
}

void web_Worker()
{
	server.handleClient();
}
