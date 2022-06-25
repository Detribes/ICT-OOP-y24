#ifndef ICT_HOMEWORK_3_FILESTORAGE_H
#define ICT_HOMEWORK_3_FILESTORAGE_H

#include "IStorage.h"
#include "../util/backupjob/IJobObject.h"

class FileStorage : public IStorage {
private:
    std::filesystem::path path_;
    std::vector<uint8_t> data_;
public:
    FileStorage(std::filesystem::path path);

    // путь к изначальному месту хранения
    std::filesystem::path getPath() override;
    // записывает данные в оригинальный файл
    bool restoreData() override;
    // сохраняет данные из файла
    bool updateData(std::vector<uint8_t>) override;

    ~FileStorage() = default;

};
#endif //ICT_HOMEWORK_3_FILESTORAGE_H
