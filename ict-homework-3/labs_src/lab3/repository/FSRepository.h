#ifndef ICT_HOMEWORK_3_FSREPOSITORY_H
#define ICT_HOMEWORK_3_FSREPOSITORY_H

#include "IRepository.h"

class FSRepository : public IRepository{
private:
    std::string name_;
    std::filesystem::path path_;
    std::unordered_map<std::string, IRestorePoint> restorePoints_;
    RestorePointType type_;
public:
    explicit FSRepository(std::string name, std::filesystem::path path, RestorePointType type);

    std::string getName() override;
    void addRestorePoint(std::string name, IRestorePoint restorePoint) override;
    IRestorePoint getRestorePoint(std::string name) override;
    std::unordered_map<std::string, IRestorePoint> getRestorePoints() override;
    std::string getLocation() override;
    RestorePointType getRestorePointType() override;
    void load() override;
    void restore(std::string name, std::filesystem::path path) override;
    std::filesystem::path getPath();

    ~FSRepository() = default;

};


#endif //ICT_HOMEWORK_3_FSREPOSITORY_H
