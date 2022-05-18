#include <filesystem>
#include "RepositoryFactory.h"


template<class Object>
IRepository RepositoryFactory::create(RepositoryType repoType,
                          RestorePointType restoreType,
                          std::string name,
                          Object args, ...) {
    IRepository result;
    switch(repoType){
        case FS:
            result = FSRepository(name, (Object&) reinterpret_cast<std::filesystem::path*>(args[0]), restoreType);
            break;
    }
    return result;

}