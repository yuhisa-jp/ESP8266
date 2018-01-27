/**
 *
 * @file Webhook.cpp
 * @date 27.01.2018
 * @author yuhisa
 * This file is distributed under GNU Lesser General Public License v2.1.
 */
#include "Webhook.h"

void WebhookClass::setHost(char* host, char* endpoint) {

  Host = host;
  Endpoint = endpoint;

  return;

}

void WebhookClass::setPort(uint16_t port) {

  Port = port;

  return;

}

void WebhookClass::setContentType(char* type) {

  strcpy(ContentType, type);

  return;

}

void WebhookClass::setHeader(char* header) {

  Header = header;

  return;

}

bool WebhookClass::get(char* host, char* path) {

  if (!client.connect(host, Port)) {
    DEBUG_WEBHOOK("[WEBHOOK] The connection to the server failed.\n");
    return false;
  }

  WebhookClass::errorCheck(host, path);
  WebhookClass::requestRaw("GET", host, path);
  
  if (WebhookClass::receive()) {
    return true;
  } else {
    return false;
  }

}

bool WebhookClass::post(char* host, char* path, const char* data) {

  if (!client.connect(host, Port)) {
    DEBUG_WEBHOOK("[WEBHOOK] The connection to the server failed.\n");
    return false;
  }

  DEBUG_WEBHOOK("[WEBHOOK] %s - %s\n", host, path);
  WebhookClass::errorCheck(host, path);
  WebhookClass::requestRaw("POST", host, path);

  DEBUG_WEBHOOK("[WEBHOOK] %s\n", data);
  WebhookClass::postData(data);

  if (WebhookClass::receive()) {
    return true;
  } else {
    return false;
  }

}

bool WebhookClass::post(char* host, char* path, String data) {

  if (!client.connect(host, Port)) {
    DEBUG_WEBHOOK("[WEBHOOK] The connection to the server failed.\n");
    return false;
  }

  DEBUG_WEBHOOK("[WEBHOOK] %s - %s\n", host, path);
  WebhookClass::errorCheck(host, path);
  WebhookClass::requestRaw("POST", host, path);

  DEBUG_WEBHOOK("[WEBHOOK] %s\n", data.c_str());
  WebhookClass::postData(data.c_str());

  if (WebhookClass::receive()) {
    return true;
  } else {
    return false;
  }

}

bool WebhookClass::receive() {

  String response;

  while (client.connected()) {
    response = client.readString();
    if (response == "\r") break;
  }

  DEBUG_WEBHOOK("[WEBHOOK] response %s\n", response.c_str());
  DEBUG_WEBHOOK("[WEBHOOK] end response\n");
  
  client.stop();
  
  if(response.indexOf("200 OK") == -1){
    DEBUG_WEBHOOK("[WEBHOOK] Request failed.\n");
    return false;
    
  }
  
  DEBUG_WEBHOOK("[WEBHOOK] Request successfull.\n");
  return true;
  
}

bool WebhookClass::requestRaw(char* method, char* host, char* path) {

  char buffer[192];

  sprintf(buffer, "%s %s HTTP/1.1", method, path);
  client.println(buffer);
  DEBUG_WEBHOOK("[WEBHOOK] %s\n", buffer);

  sprintf(buffer, "Host: %s:%u", host, Port);
  client.println(buffer);
  DEBUG_WEBHOOK("[WEBHOOK] %s\n", buffer);

  sprintf(buffer, "Connection: close");
  client.println(buffer);
  DEBUG_WEBHOOK("[WEBHOOK] %s\n", buffer);

  sprintf(buffer, "Content-Type: %s", ContentType);
  client.println(buffer);
  DEBUG_WEBHOOK("[WEBHOOK] %s\n", buffer);

  if (Header) {
    sprintf(buffer, "%s\r\n", Header);
    client.println(buffer);
    DEBUG_WEBHOOK("[WEBHOOK] %s\n", buffer);
  }

  return true;

}

bool WebhookClass::postData(const char* data) {

  char buffer[256];
  char content[256];
  WebhookClass::deleteCRLF(data, content);

  //printf("Content-Length: %u\r\n", strlen(content));
  sprintf(buffer, "Content-Length: %u\r\n", strlen(content));
  client.println(buffer);
  DEBUG_WEBHOOK("[WEBHOOK] %s\n", buffer);

  //printf("%s\r\n", content);
  sprintf(buffer, "%s\r\n", content);
  client.println(buffer);
  DEBUG_WEBHOOK("[WEBHOOK] %s\n", buffer);

  return true;

}

bool WebhookClass::isSecureUrl(const char* url) {

  char* protocol = (char*)malloc(6 * sizeof(char*));
  char* colon;
  strcpy(protocol, url);
  colon = strtok(protocol,":");

  if (strcmp(protocol, "https")) {
    return false;
  } else {
    return true;
  }

}

void WebhookClass::deleteCRLF(const char* str, char* content) {

  char output[240];
  int textLength = strlen(str);
  int j = 0;

  for (int i = 0; i < textLength; i++) {

    if (str[i] == '\n') {
      //output[j];
    } else if (str[i] == '\r') {
      output[j] = '\\';
      j++;
    } else {
      output[j] = str[i];
      j++;
    }

  }

  output[j] = '\0';
  strcpy(content, output);
  
  DEBUG_WEBHOOK("[WEBHOOK] %s\n", output);

  return;

}

bool WebhookClass::errorCheck(char* host, char* path) {

  if (!host || !path)
    return false;

  return true;

}



WebhookClass Webhook;
