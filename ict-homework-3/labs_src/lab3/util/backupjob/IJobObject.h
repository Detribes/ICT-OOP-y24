#ifndef ICT_HOMEWORK_3_IJOBOBJECT_H
#define ICT_HOMEWORK_3_IJOBOBJECT_H

#include <string>
#include <vector>
#include <filesystem>

/**
 * Объект "джобы" который по сути является самой примитивной обёрткой для стораджа. Я даже
 * не знаю, по большей части он тут излишний, но в задании он нужен для бекап-джобы, поэтому
 * он тут есть.
 */
class IJobObject {
public:
    IJobObject() = default;

    virtual std::filesystem::path getFullPath() = 0;
    virtual std::vector<uint8_t> getContents() = 0;
    
    ~IJobObject() = default;
    
    bool operator ==(IJobObject &s)
    {
        if (s.getFullPath() == getFullPath())
            return true;

        return false;
    }
};


#endif //ICT_HOMEWORK_3_IJOBOBJECT_H
