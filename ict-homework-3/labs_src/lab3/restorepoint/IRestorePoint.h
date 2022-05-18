#ifndef ICT_HOMEWORK_3_IRESTOREPOINT_H
#define ICT_HOMEWORK_3_IRESTOREPOINT_H

#include <unordered_map>
#include <map>
#include <set>
#include "../storage/IStorage.h"


class IRestorePoint{
public:
    IRestorePoint();

    virtual std::string getName();
    virtual void addNewStorage(std::string name, IStorage storage);
    virtual IStorage getStorage(std::string name);
    virtual std::unordered_map <std::string, IStorage> getStorages();

    virtual void save();
    virtual void load();

    virtual ~IRestorePoint();

};
#endif //ICT_HOMEWORK_3_IRESTOREPOINT_H
