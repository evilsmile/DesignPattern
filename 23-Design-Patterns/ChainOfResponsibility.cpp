#include <iostream>
#include <string>

/*  
    通常业务代码中会有这样的结构:

    if (i == 1) {
        handler1.handle(req);
    } else if (i == 2) {
        handler2.handle(req);
    } ...

    这样的处理流程不仅显得臃肿，而且耦合度高。

    可以使用责任链模式来处理，如果不满足则向下传递.
 */

class Level {
    public:
        Level(int l) : _l(l) {}
        Level() : _l(0) {}

        bool operator>(const Level& level) { 
             if (this->_l >= level._l) {
                return true;
            }
            return false;
        }

        bool above(Level* level) {
            if (this->_l >= level->_l) {
                return true;
            }
            return false;
        }
    private:
        int _l;
};

class Request {
    public:
        Request(Level* level) : _level(level) {}
        Level* getLevel() {
            return _level;
        }

    private:
        Level* _level;
};

class Response {
    public:
        Response(const std::string& msg) : _msg(msg) {}
        Response(){}

        void setMsg(const std::string& msg) {
            this->_msg = msg;
        }

        std::string getMsg() {
            return _msg;
        }

    private:
        std::string _msg;
};

class IHandler {
    public:
        Response handleRequest(Request* req) {
            Response resp;

            if (*(this->getHandlerLevel()) > *(req->getLevel())) {
                    resp = this->handle(req);
            } else {
                if (this->_nextHandler != NULL) {
                    resp = this->_nextHandler->handleRequest(req);
                } else {
                    std::cerr << "No handler found!" << std::endl;
                }
            }
            return resp;
        }

        void setNextHandler(IHandler* handler) {
            this->_nextHandler = handler;
        }
    protected:
        virtual Level* getHandlerLevel() = 0;
    public:
        virtual Response handle(Request* req) = 0;
    private:
        IHandler* _nextHandler;
};

class Handler1 : public IHandler {
    public:
        Response handle(Request* req) {
            std::cout << "Handler 1 handled." << std::endl;
            return Response("1 handles.");
        }
    protected:
        Level* getHandlerLevel() {
            return new Level(1);
        }
};

class Handler2 : public IHandler {
    public:
        Response handle(Request* req) {
            std::cout << "Handler 2 handled." << std::endl;
            return Response("2 handles.");
        }
    protected:
        Level* getHandlerLevel() {
            return new Level(2);
        }
};

class Handler3 : public IHandler {
    public:
        Response handle(Request* req) {
            std::cout << "Handler 3 handled." << std::endl;
            return Response("3 handles.");
        }
    protected:
        Level* getHandlerLevel() {
            return new Level(3);
        }
};
int main()
{
    Handler1 *handler1 = new Handler1;
    Handler2 *handler2 = new Handler2;
    Handler3 *handler3 = new Handler3;

    handler1->setNextHandler(handler2);
    handler2->setNextHandler(handler3);

    Response response = handler1->handleRequest(new Request(new Level(1)));
    response = handler1->handleRequest(new Request(new Level(2)));
    response = handler1->handleRequest(new Request(new Level(3)));

    return 0;
}
