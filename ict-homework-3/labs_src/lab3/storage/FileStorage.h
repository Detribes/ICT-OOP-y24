#ifndef ICT_HOMEWORK_3_FILESTORAGE_H
#define ICT_HOMEWORK_3_FILESTORAGE_H

#include "IStorage.h"

class FileStorage : public IStorage{
private:
    std::filesystem::path path_;
    std::string name_;
public:
   explicit FileStorage(std::string name,std::string path);

   std::filesystem::path getPath();
   std::string getName() override;
   std::ifstream retrieve() override;
   std::ofstream copyInto() override;

   ~FileStorage() = default;

};
#endif //ICT_HOMEWORK_3_FILESTORAGE_H
