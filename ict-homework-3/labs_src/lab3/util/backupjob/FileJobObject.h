#ifndef ICT_HOMEWORK_3_FILEJOBOBJECT_H
#define ICT_HOMEWORK_3_FILEJOBOBJECT_H

#include "IJobObject.h"
#include <filesystem>

class FileJobObject : public IJobObject {
private:
    std::filesystem::path fullQualifiedPath_;
public:
    FileJobObject(std::filesystem::path fullQualifiedPath);

    std::filesystem::path getFullPath() override;
    std::vector<uint8_t> getContents() override;
    
    ~FileJobObject() = default;
};


#endif //ICT_HOMEWORK_3_FILEJOBOBJECT_H
