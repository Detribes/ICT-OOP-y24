#ifndef ICT_HOMEWORK_3_IREPOSITORY_H
#define ICT_HOMEWORK_3_IREPOSITORY_H

#include <string>
#include "../restorepoint/IRestorePoint.h"
#include "../util/factory/enums/RestorePointType.h"

class IRepository{
public:
    IRepository();

    virtual std::string getName();
    virtual void addRestorePoint(std::string name, IRestorePoint restorePoint);
    virtual IRestorePoint getRestorePoint(std::string name);
    virtual std::unordered_map<std::string, IRestorePoint> getRestorePoints();
    virtual std::string getLocation();
    virtual RestorePointType getRestorePointType();
    virtual void load();
    virtual void restore(std::string name, std::filesystem::path path);

    virtual ~IRepository();
};
#endif //ICT_HOMEWORK_3_IREPOSITORY_H
