#ifndef ICT_HOMEWORK_3_STORAGEFACTORY_H
#define ICT_HOMEWORK_3_STORAGEFACTORY_H

#include "../../storage/IStorage.h"
#include "enums/StorageType.h"

class StorageFactory final{
public:
    template<class Object>
    static IStorage create(StorageType type,std::string name,Object arg,... );
};


#endif //ICT_HOMEWORK_3_STORAGEFACTORY_H
