#include "RestorePointFactory.h"
#include "../../restorepoint/ZipSingleFileRestorePoint.h"
#include "../../restorepoint/ZipSplitFileRestorePoint.h"

IRestorePoint RestorePointFactory::create(IRepository repo,
                                          RestorePointType type,
                                          const std::string& name) {
    IRestorePoint result;
    switch (type) {
        case ZipSingleFS:
            result = ZipSingleFileRestorePoint(name, std::filesystem::path(repo.getLocation()));
            break;
        case ZipSplitFS:
            result = ZipSplitFileRestorePoint(name,std::filesystem::path(repo.getLocation()));
            break;
    }
    repo.addRestorePoint(name, result);
    return result;
}