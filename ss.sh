curl -X GET "https://api.screenshotapi.net/screenshot?token=YOUR_API_KEY&url=https://acas.edu.bd&width=1920&height=1080&output=image" \
  -H "origin: https://acas.edu.bd" \
  -H "referer: https://acas.edu.bd/" \
  -H "sec-ch-ua: \"Chromium\";v=\"130\", \"Brave\";v=\"130\", \"Not?A_Brand\";v=\"99\"" \
  -H "sec-ch-ua-mobile: ?0" \
  -H "sec-ch-ua-platform: \"Windows\"" \
  -H "user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36" \
  -o screenshot.png
