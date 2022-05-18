#ifndef ICT_HOMEWORK_3_ABSTRACTFSRESTOREPOINT_H
#define ICT_HOMEWORK_3_ABSTRACTFSRESTOREPOINT_H

#include "AbstractRestorePoint.h"

class AbstractFSRestorePoint : public AbstractRestorePoint{
private:
    std::filesystem::path path_;
public:
    explicit AbstractFSRestorePoint(std::string name, std::filesystem::path path);
    virtual std::filesystem::path getPath();
    virtual ~AbstractFSRestorePoint() = default;
};


#endif //ICT_HOMEWORK_3_ABSTRACTFSRESTOREPOINT_H
