# Webhook class

ArduinoでWebhookを使うためのライブラリ

## 使用例

```cpp
#include "Webhook.h"

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
