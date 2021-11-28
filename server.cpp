#include<handy/handy.h>

using namespace handy;

int main(int argc, const char *argv[]) {
    int threads = 1;
    if (argc > 1) {
        threads = atoi(argv[1]);
    }
    // setloglevel("TRACE");
    MultiBase base(threads);
    HttpServer sample(&base);
    int r = sample.bind("", 8081);
    exitif(r, "bind failed %d %s", errno, strerror(errno));

    sample.onRequest("GET", "/hello-get", [](const HttpConnPtr &con) {
        std::string name = con.getRequest().getArg("name");
        std::string result = "hello.sayHello(name)";
        HttpResponse resp;
        resp.body = Slice(result);
        con.sendResponse(resp);
    });


    sample.onRequest("POST", "/hello-post", [](const HttpConnPtr &con) {
            std::string body = con.getRequest().body;
            std::string data = "hello ";
            std::string result = "{\"data\": \"" + data + "\"}";
            HttpResponse resp;
            resp.headers = {std::make_pair("Content-Type", "application/json")};
            resp.body = Slice(result);
            con.sendResponse(resp);
    });

    Signal::signal(SIGINT, [&] { base.exit(); });
    base.loop();
    return 0;
}