#include <pistache/router.h>

#include <Authenticator.h>
#include <iDatabaseSource.h>
#include <Utils.h>

class RouteHandler {
    public:
        RouteHandler(Net::Rest::Router & router,iDatabaseSource & database);

        void serveApp(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
        void serveIndex(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
        void serveImage(const Net::Rest::Request& request, Net::Http::ResponseWriter response);

        void doLogin(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
        void doLogout(const Net::Rest::Request& request, Net::Http::ResponseWriter response);
        void doRegister(const Net::Rest::Request& request, Net::Http::ResponseWriter response);

        void testHandler(const Net::Rest::Request& request, Net::Http::ResponseWriter response);

    private:
        Authenticator auth;
        iDatabaseSource & database;
};