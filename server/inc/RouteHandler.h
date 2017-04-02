class RouteHandler {
    public:
        RouteHandler(Net::Rest::Router & router);

        void serveApp(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
        void serveIndex(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
        void serveImage(const Net::Rest::Request& request, Net::Http::ResponseWriter response);

        void doLogin(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
        void doRegister(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
};