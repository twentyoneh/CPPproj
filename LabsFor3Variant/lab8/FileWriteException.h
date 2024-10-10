#ifndef FILEWRITEEXCEPTION_H
#define FILEWRITEEXCEPTION_H

#include <exception>
#include <string>

class FileWriteException : public std::exception {
private:
    std::string message;

public:
    explicit FileWriteException(const std::string& msg) : message(msg) {}
    
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // FILEWRITEEXCEPTION_H
