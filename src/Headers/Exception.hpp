#pragma once
#include <exception>
#include <string>

class Exception : public std::exception
{
public:
    Exception(const std::string &msg)
        : cMsg(msg){};
    ~Exception() {}
    Exception(std::string &&msg)
        : cMsg(msg){};

    inline std::string getMsg() const
    {
        return cMsg;
    }
private:
    std::string cMsg;
};