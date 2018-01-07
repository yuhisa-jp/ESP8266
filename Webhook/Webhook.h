/**
 *
 * @file Webhook.h
 * @date 07.01.2018
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
    String WebhookHost, WebhookEndpoint;
    String WebhookContentType = "application/x-www-form-urlencoded";
  
  public:
    void setHost (const char* host, const char* endpoint);
    void setContentType (const char* type);
    bool post (String data);
    
};

extern WebhookClass Webhook;

#endif
