#ifndef ICT_HOMEWORK_3_RESTOREPOINTFACTORY_H
#define ICT_HOMEWORK_3_RESTOREPOINTFACTORY_H

#include "../../restorepoint/IRestorePoint.h"
#include "../../repository/IRepository.h"
#include "enums/RestorePointType.h"
#include "../../restorepoint/ZipSingleFileRestorePoint.h"
#include "../../restorepoint/ZipSplitFileRestorePoint.h"
#include "../../restorepoint/MockRestorePoint.h"

class RestorePointFactory final {
public:
    static std::shared_ptr<IRestorePoint> create(std::shared_ptr<IRepository> repo, RestorePointType type, const std::string& name) {
        // Mock репа может содержать только Mock ресторпоинты
        if (repo->getRepositoryType() == RepositoryType::Mock) {
            std::cout << "Created MOCK restorepoint " << name << std::endl;
            return std::make_shared<MockRestorePoint>(name);
        }

        std::shared_ptr<IRestorePoint> result;
        switch (type) {
            case ZipSingleFS:
                result = std::make_shared<ZipSingleFileRestorePoint>(name, std::filesystem::path(repo->getLocation()));
                break;
            case ZipSplitFS:
                result = std::make_shared<ZipSplitFileRestorePoint>(name, std::filesystem::path(repo->getLocation()));
                break;
        }
        std::cout << "Created restorepoint " << result->getName() << std::endl;
        return result;
    }
};


#endif //ICT_HOMEWORK_3_RESTOREPOINTFACTORY_H
