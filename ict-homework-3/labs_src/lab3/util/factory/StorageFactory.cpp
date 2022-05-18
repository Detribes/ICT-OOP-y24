#include "StorageFactory.h"
#include "../../storage/MemoryStorage.h"

template<class Object>
IStorage StorageFactory::create(StorageType type,
                                std::string name,
                                Object arg, ...) {
    IStorage result;
    switch(type){
        case FILES:
            result = FileStorage(name,(Object&) reinterpret_cast<std::filesystem::path*>(arg[0]));
            break;
        case MEMORY:
            std::vector<char> bytes;
            for (char const &c: ((Object&) reinterpret_cast<std::string*>(arg[0]))) {
                bytes.push_back(c);
            }
            result = MemoryStorage(name,bytes);
            break;

    }
    return result;
}