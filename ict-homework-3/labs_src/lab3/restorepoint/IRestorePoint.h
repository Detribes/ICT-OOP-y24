#ifndef ICT_HOMEWORK_3_IRESTOREPOINT_H
#define ICT_HOMEWORK_3_IRESTOREPOINT_H

#include <unordered_map>
#include <map>
#include <set>
#include <list>
#include "../util/backupjob/IJobObject.h"
#include "../storage/IStorage.h"


class IRestorePoint {
public:
    IRestorePoint() = default;

    virtual std::string getName() = 0;
    
    virtual void addNewStorage(std::string name, std::shared_ptr<IStorage> storage) = 0;

    virtual std::shared_ptr<IStorage> getStorage(std::string name) = 0;

    virtual std::unordered_map<std::string, std::shared_ptr<IStorage>> getStorages() = 0;

    //virtual std::time_t getCreationDate() = 0;

    
    // сохраняет данные из стораджей в оригинальную точку восстановления
    virtual void save() = 0;
    // загружает ресторпоинт из указанного пути (с зипами например)
    virtual void load() = 0;
    // заполняет ресторпоинт данными из джоб, создает зипфайл
    virtual void generate(std::list<std::shared_ptr<IJobObject>> jobs) = 0;

    virtual ~IRestorePoint() = default;
};
#endif //ICT_HOMEWORK_3_IRESTOREPOINT_H
