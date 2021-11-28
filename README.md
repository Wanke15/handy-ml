# handy-ml: Serve machine learning algorithms using C++

#### 1. Denpendency
```bash
git clone --depth 1 https://github.com/yedf/handy && cd handy && make && make install
```

### 2. Build and run
```bash
g++ -std=c++11 -lhandy server.cpp -o server && ./server
# 2021/11/28-12:37:36.305413 119559dc0 INFO handy/poller.cc:130 poller kqueue 3 created
# 2021/11/28-12:37:36.305606 119559dc0 INFO handy/conn.cc:285 fd 6 listening at 0.0.0.0:8081
```

### 2. Test
```bash
curl --location --request POST 'http://127.0.0.1:8081/hello-post' \
--header 'Content-Type: application/json' \
--data-raw '{
 "name":"Jeff"
}'

# 2021/11/28-12:41:01.823272 119559dc0 INFO handy/http.cc:197 http request: POST /hello-post HTTP/1.1

# {
#     "data": "Hello Jeff"
# }
```
