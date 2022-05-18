#ifndef ICT_HOMEWORK_3_ABSTRACTRESTOREPOINT_H
#define ICT_HOMEWORK_3_ABSTRACTRESTOREPOINT_H

#include "IRestorePoint.h"

class  AbstractRestorePoint : public IRestorePoint {
private:
    std::string name_;
    std::unordered_map <std::string,IStorage> storagesToCopy_;
    std::unordered_map <std::string,IStorage> actualStorages_;
protected:
    virtual std::unordered_map <std::string, IStorage> getStoragesToCopy();
    virtual void resetStoragesToCopy();
public:
    explicit AbstractRestorePoint(std::string name);

    virtual std::string getName() override;
    virtual void addNewStorage(std::string name, IStorage storage) override;
    virtual IStorage getStorage(std::string name) override;
    virtual std::unordered_map <std::string, IStorage> getStorages() override;

    virtual ~AbstractRestorePoint() = default;


};


#endif //ICT_HOMEWORK_3_ABSTRACTRESTOREPOINT_H
