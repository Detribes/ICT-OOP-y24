#ifndef ICT_HOMEWORK_3_STORAGEFACTORY_H
#define ICT_HOMEWORK_3_STORAGEFACTORY_H

#include "../../storage/MemoryStorage.h"
#include "../../storage/FileStorage.h"
#include "enums/StorageType.h"

class StorageFactory final {
public:
    template<class Object>
    static std::shared_ptr<IStorage> create(StorageType type, Object arg) {
        std::shared_ptr<IStorage> result;

        switch (type) {
            case FILES:
                result = std::make_shared<FileStorage>(static_cast<std::filesystem::path>(arg));
                break;
            case MEMORY:
                result = std::make_shared<MemoryStorage>(static_cast<std::filesystem::path>(arg));
                break;
        }
        std::cout << "Created storage " << result->getPath() << std::endl;
        return result;
    }
};


#endif //ICT_HOMEWORK_3_STORAGEFACTORY_H
