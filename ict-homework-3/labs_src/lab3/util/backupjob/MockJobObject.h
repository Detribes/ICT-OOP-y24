#ifndef ICT_HOMEWORK_3_MOCKJOBOBJECT_H
#define ICT_HOMEWORK_3_MOCKJOBOBJECT_H

#include "IJobObject.h"
#include <filesystem>

class MockJobObject : public IJobObject {
private:
    std::string fileName_;
    std::vector<uint8_t> data_;
public:
    MockJobObject(std::string fileName, std::vector<uint8_t> data);

    std::filesystem::path getFullPath() override;
    std::vector<uint8_t> getContents() override;
    
    ~MockJobObject() = default;
};


#endif //ICT_HOMEWORK_3_MOCKJOBOBJECT_H
