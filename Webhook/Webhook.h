/**
 *
 * @file Webhook.h
 * @date 27.01.2018
 * @author yuhisa
 * This file is distributed under GNU Lesser General Public License v2.1.
 */
#ifndef __Webhook_H_
#define __Webhook_H_

#include <WiFiClientSecure.h>

#ifdef DEBUG_ESP_PORT
#define DEBUG_WEBHOOK(...) DEBUG_ESP_PORT.printf( __VA_ARGS__ )
#endif

#ifndef DEBUG_WEBHOOK
#define DEBUG_WEBHOOK(...)
#endif

class WebhookClass
{

private:
  char* Host;
  char* Endpoint;
  char* Header;
  char ContentType[128] = "application/x-www-form-urlencoded";
  uint16_t Port = 443;
  WiFiClientSecure client;

public:
  void setHost(char* host, char* endpoint);
  void setPort(uint16_t port);
  void setContentType(char* type);
  void setHeader(char* header);
  bool post(char* host, char* path, const char* data);
  bool post(char* host, char* path, String data);
  bool get(char* host, char* path);
  bool isSecureUrl(const char* url);
  bool requestRaw(char* method, char* host, char* path);
  bool receive();
  bool postData(const char* data);
  bool errorCheck(char* host, char* path);
  void deleteCRLF(const char* str, char* content);
};

extern WebhookClass Webhook;

#endif
