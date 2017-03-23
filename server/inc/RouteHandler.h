class RouteHandler {
    public:
        RouteHandler(Net::Rest::Router & router);

        void testHandler(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
        void doLogin(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
        void doRegister(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
};