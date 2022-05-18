#ifndef ICT_HOMEWORK_3_JOBOBJECT_H
#define ICT_HOMEWORK_3_JOBOBJECT_H

#include "../../storage/IStorage.h"

/**
 * Объект "джобы" который по сути является самой примитивной обёрткой для стораджа. Я даже
 * не знаю, по большей части он тут излишний, но в задании он нужен для бекап-джобы, поэтому
 * он тут есть.
 */
class JobObject {
private:
     IStorage storage_;
public:
    JobObject(IStorage storage);
    IStorage getStorage();
    ~JobObject() = default;
};


#endif //ICT_HOMEWORK_3_JOBOBJECT_H
