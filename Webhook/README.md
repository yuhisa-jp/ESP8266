# Webhook class

ArduinoでWebhookを使うためのライブラリ

## 使用例

```cpp
#include "Webhook.h"

// Content-Typeを変えたいとき
Webhook.setContentType("application/x-www-form-urlencoded");

// 接続先ポートを変えたいとき
Webhook.setPort(8080);

// 送信ヘッダーを追加したいとき
Webhook.setHeader("User-Agent: ESP8266-Webhook/0001");

// GET
Webhook.get(
    "hooks.slack.com",
    "/services/xxxxxxxxx/yyyyyyyyy/zzzzzzzzzz/"
  );

// POST
Webhook.post(
    "hooks.slack.com",
    "/services/xxxxxxxxx/yyyyyyyyy/zzzzzzzzzz/",
    "payload={\"text\": \"Webhook Test!\"}"
  );
```
