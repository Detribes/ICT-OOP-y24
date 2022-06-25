#ifndef ICT_HOMEWORK_3_MEMORYSTORAGE_H
#define ICT_HOMEWORK_3_MEMORYSTORAGE_H

#include "IStorage.h"
#include "../util/backupjob/IJobObject.h"

class MemoryStorage : public IStorage {
private:
    std::filesystem::path path_;
    //std::vector<uint8_t> data_;
public:
    MemoryStorage(std::filesystem::path path);

    // путь к изначальному месту хранения
    std::filesystem::path getPath() override;
    // записывает данные в оригинальный файл
    bool restoreData() override;
    // сохраняет данные из файла
    bool updateData(std::vector<uint8_t>) override;

    ~MemoryStorage() = default;

};
#endif //ICT_HOMEWORK_3_MEMORYSTORAGE_H
