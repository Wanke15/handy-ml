#include<handy/handy.h>
#include "include/nlohmann/json.hpp"

using namespace handy;
using json = nlohmann::json;

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
        // parse request data
        std::string body = con.getRequest().body;
        json req_data = json::parse(body);

        // business logic
        std::string name = req_data.at("name");
        std::string data = "Hello " + name;
        json resp_data {
            {"data", data}
        };
        std::string result = resp_data.dump();

        // response
        HttpResponse resp;
        resp.headers = {std::make_pair("Content-Type", "application/json")};
        resp.body = Slice(result);
        con.sendResponse(resp);
    });

    Signal::signal(SIGINT, [&] { base.exit(); });
    base.loop();
    return 0;
}