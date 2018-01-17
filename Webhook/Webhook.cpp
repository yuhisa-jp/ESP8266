/**
 *
 * @file Webhook.cpp
 * @date 17.01.2018
 * @author yuhisa
 * This file is distributed under GNU Lesser General Public License v2.1.
 */
#include "Webhook.h"

void WebhookClass::setHost (char* host, char* endpoint)
{
  
  WebhookHost = host;
  WebhookEndpoint = endpoint;
  return;

}

/* default application/x-www-form-urlencoded */
void WebhookClass::setContentType (char* type)
{
  
  strcpy(WebhookContentType, type);
  DEBUG_WEBHOOK("[WEBHOOK] Set Content-type %s\n", type);
  return;

}

bool WebhookClass::post (String data)
{
    
  WiFiClientSecure client;
  char buffer[128];
  String response;

  data.replace("\n", "\\n");
  data.replace("\r", "\\r");
      
  if (!client.connect(WebhookHost, 443)) {
    DEBUG_WEBHOOK("[WEBHOOK] Connection Failed\n");
    return 0;
  }
  
  delay(0);

  DEBUG_WEBHOOK("[WEBHOOK] start request\n");
  DEBUG_WEBHOOK("[WEBHOOK] request %s%s\n", WebhookHost, WebhookEndpoint);
  DEBUG_WEBHOOK("[WEBHOOK] Content-Type: %s\n", WebhookContentType);
  DEBUG_WEBHOOK("[WEBHOOK] data %s\n", data.c_str());
  
  sprintf(buffer, "POST %s HTTP/1.1", WebhookEndpoint);
  client.println(buffer);
  sprintf(buffer, "Host: %s ", WebhookHost);
  client.println(buffer);
  sprintf(buffer, "Connection: close\r\nContent-Type: %s", WebhookContentType);
  client.println(buffer);
  sprintf(buffer, "Content-Length: %u\r\n", strlen(data.c_str()));
  client.println(buffer);
  client.print(data);

  DEBUG_WEBHOOK("[WEBHOOK] end request\n");

  delay(0);

  DEBUG_WEBHOOK("[WEBHOOK] waiting for response\n");
  
  while (client.connected()) {
    response = client.readString();
    if (response == "\r") break;
  }

  DEBUG_WEBHOOK("[WEBHOOK] response %s\n", response.c_str());
  DEBUG_WEBHOOK("[WEBHOOK] end response\n");
  
  client.stop();
  
  if(response.indexOf("200 OK") == -1){
    DEBUG_WEBHOOK("[WEBHOOK] Request failed\n");
    return 0;
  } else {
    DEBUG_WEBHOOK("[WEBHOOK] Request successfull\n");
  }

  return 1;
 
}

WebhookClass Webhook;
