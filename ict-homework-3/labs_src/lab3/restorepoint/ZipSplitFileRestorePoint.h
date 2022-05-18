#ifndef ICT_HOMEWORK_3_ZIPSPLITFILERESTOREPOINT_H
#define ICT_HOMEWORK_3_ZIPSPLITFILERESTOREPOINT_H

#include "AbstractFSRestorePoint.h"
#include "../../../Zipios/src/zipoutputstream.hpp"
#include "../../../Zipios/src/zipinputstream.hpp"


class ZipSplitFileRestorePoint : public AbstractFSRestorePoint{
private:
    std::filesystem::path dirUnzipStorages_;
    bool isLoaded_;

    void createNewTmpDir();
    void removeTmpDir();
    void createParentDirs(std::filesystem::path path);
    zipios::ZipOutputStream openZipWrite(std::filesystem::path path);
    zipios::ZipInputStream openZipRead(std::filesystem::path path);
public:
    ZipSplitFileRestorePoint(std::string name, std::filesystem::path path);

    void save() override;
    void load() override;

    ~ZipSplitFileRestorePoint() = default;
};


#endif //ICT_HOMEWORK_3_ZIPSPLITFILERESTOREPOINT_H
