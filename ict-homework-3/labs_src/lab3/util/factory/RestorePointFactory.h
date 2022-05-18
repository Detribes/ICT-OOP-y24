#ifndef ICT_HOMEWORK_3_RESTOREPOINTFACTORY_H
#define ICT_HOMEWORK_3_RESTOREPOINTFACTORY_H

#include "../../restorepoint/IRestorePoint.h"
#include "../../repository/IRepository.h"
#include "enums/RestorePointType.h"

class RestorePointFactory final{
public:
    static IRestorePoint create(IRepository repo,RestorePointType type,const std::string& name);
};


#endif //ICT_HOMEWORK_3_RESTOREPOINTFACTORY_H
