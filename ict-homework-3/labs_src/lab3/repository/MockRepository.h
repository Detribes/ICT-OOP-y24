#ifndef ICT_HOMEWORK_3_MOCKREPOSITORY_H
#define ICT_HOMEWORK_3_MOCKREPOSITORY_H

#include "IRepository.h"

class MockRepository : public IRepository {
private:
    std::string name_;
    std::filesystem::path path_;
    std::unordered_map<std::string, std::shared_ptr<IRestorePoint>> restorePoints_;
    RestorePointType type_;
public:
    explicit MockRepository(std::string name,  RestorePointType type);

    std::string getName() override;
    void addRestorePoint(std::string name, std::shared_ptr<IRestorePoint> restorePoint) override;
    std::shared_ptr<IRestorePoint> getRestorePoint(std::string name) override;
    std::unordered_map<std::string, std::shared_ptr<IRestorePoint>> getRestorePoints() override;
    std::filesystem::path getLocation() override;
    RestorePointType getRestorePointType() override;
    RepositoryType getRepositoryType() override { return RepositoryType::Mock; };
    void load() override;
    void restore(std::string name) override;

    ~MockRepository() = default;
};


#endif //ICT_HOMEWORK_3_MOCKREPOSITORY_H
