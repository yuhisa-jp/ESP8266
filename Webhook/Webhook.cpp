/**
 *
 * @file Webhook.cpp
 * @date 07.01.2018
 * @author yuhisa
 * This file is distributed under GNU Lesser General Public License v2.1.
 */
#include "Webhook.h"

void WebhookClass::setHost (const char* host, const char* endpoint)
{
  
  WebhookHost = host;
  WebhookEndpoint = endpoint;
  return;

}

/* default application/x-www-form-urlencoded */
void WebhookClass::setContentType (const char* type)
{
  
  WebhookContentType = type;
  DEBUG_WEBHOOK("[WEBHOOK] Set Content-type %s\n", type);
  return;

}

bool WebhookClass::post (String data)
{
    
  WiFiClientSecure client;
  char buffer[128];
  String response;
      
  if (!client.connect(WebhookHost.c_str(), 443)) {
    DEBUG_WEBHOOK("[WEBHOOK] Connection Failed\n");
    return 0;
  }
  
  delay(0);

  DEBUG_WEBHOOK("[WEBHOOK] start request\n");
  
  sprintf(buffer, "POST %s HTTP/1.1", WebhookEndpoint.c_str());
  client.println(buffer);
  sprintf(buffer, "Host: %s ", WebhookHost.c_str());
  client.println(buffer);
  sprintf(buffer, "Connection: close\r\nContent-Type: %s", WebhookContentType.c_str());
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
