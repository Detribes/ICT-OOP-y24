#ifndef ICT_HOMEWORK_3_MEMORYSTORAGE_H
#define ICT_HOMEWORK_3_MEMORYSTORAGE_H

#include "IStorage.h"

class MemoryStorage : public IStorage{
private:
    std::vector <char> data_;
    std::string name_;
public:
    explicit MemoryStorage(std::string name, std::vector <char> data);

    std::string getName() override;
    std::ofstream copyInto() override;
    std::ifstream retrieve() override;

    ~MemoryStorage() = default;

};
#endif //ICT_HOMEWORK_3_MEMORYSTORAGE_H
