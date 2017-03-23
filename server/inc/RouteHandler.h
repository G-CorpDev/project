class RouteHandler {
    public:
        RouteHandler(Net::Rest::Router & router);

        void testHandler(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
};