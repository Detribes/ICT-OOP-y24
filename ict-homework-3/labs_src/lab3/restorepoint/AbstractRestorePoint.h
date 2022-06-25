#ifndef ICT_HOMEWORK_3_ABSTRACTRESTOREPOINT_H
#define ICT_HOMEWORK_3_ABSTRACTRESTOREPOINT_H

#include "IRestorePoint.h"

class  AbstractRestorePoint : public IRestorePoint {
private:
    std::string name_;
    std::unordered_map <std::string, std::shared_ptr<IStorage>> actualStorages_;
public:
    explicit AbstractRestorePoint(std::string name);

    virtual std::string getName() override;
    virtual void addNewStorage(std::string name, std::shared_ptr<IStorage> storage) override;
    virtual std::shared_ptr<IStorage> getStorage(std::string name) override;
    virtual std::unordered_map <std::string, std::shared_ptr<IStorage>> getStorages() override;
    virtual void generate(std::list<std::shared_ptr<IJobObject>> jobs) override;

    virtual ~AbstractRestorePoint() = default;
};


#endif //ICT_HOMEWORK_3_ABSTRACTRESTOREPOINT_H
