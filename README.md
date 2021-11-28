# handy-ml

#### 1. Denpendency
```bash
git clone --depth 1 https://github.com/yedf/handy && cd handy && make && make install
```

### 2. Build and run
```bash
g++ -std=c++11 -lhandy server.cpp -o server && ./server
```

### 2. Test
```bash
curl --location --request POST 'http://127.0.0.1:8081/hello-post' \
--header 'Content-Type: application/json' \
--data-raw '{
 "name":"Jeff"
}'
```
