# Webhook class

ArduinoでWebhookを使うためのライブラリ

## 使用例

```cpp
#include "Webhook.h"

Webhook.setHost("hooks.slack.com", "/services/xxxxxxxxx/yyyyyyyyy/zzzzzzzzzz/");
Webhook.setContentType("application/x-www-form-urlencode");
Webhook.post("payload={\"text\": \"Webhook Test!\"}");
```

## Webhook.setHost()
### 概要
送信先の設定をします。 **必ず使用前にこの関数を使用して送信先の設定をする必要があります**
### 構文
`Webhook.setHost(host, endpoint)`

### 引数
- `host`: hostname 
  - ex. `hooks.slack.com` - String
- `endpoint`: request URI
  - ex. `/services/xxxxxxxxx/yyyyyyyyy/zzzzzzzzzz/` - String

### 戻り値
`なし`

## Webhook.post()
### 概要
POSTメソッドを使用して `Webhook.setHost()` の設定値にデータを送信します。

### 構文
`Webhook.post(data)`

### 引数
- `data`: postdata
  - ex. `payload={"text": "something text."}` - String

#### 戻り値
`false`: リクエストに失敗した場合は`false`を返します。

## Webhook.setContentType()
### 概要
`Webhook.post()` で使用する Content-typeを設定できます。初期値は `application/x-www-form-urlencode` です。

### 構文
`Webhook.post(contentType)`

### 引数
- `contentType`: Content-type
  - ex. `application/x-www-form-urlencoded` - String

### 戻り値
`なし`
