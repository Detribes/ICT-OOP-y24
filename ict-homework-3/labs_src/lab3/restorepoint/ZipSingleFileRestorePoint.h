#ifndef ICT_HOMEWORK_3_ZIPSINGLEFILERESTOREPOINT_H
#define ICT_HOMEWORK_3_ZIPSINGLEFILERESTOREPOINT_H

#include "AbstractFSRestorePoint.h"
#include "../../../Zipios/src/zipoutputstream.hpp"
#include "../../../Zipios/src/zipinputstream.hpp"


class ZipSingleFileRestorePoint : public AbstractFSRestorePoint {
private:
    std::filesystem::path dirUnzipStorages_;
    bool isLoaded_ = false;

    void createNewTmpDir();
    void removeTmpDir();
    void createParentDirs(std::filesystem::path path);
    zipios::ZipOutputStream openZipWrite(std::filesystem::path path);
    zipios::ZipInputStream openZipRead(std::filesystem::path path);
public:
    ZipSingleFileRestorePoint(std::string name,std::filesystem::path path);

    void save() override;
    void load() override;


};


#endif //ICT_HOMEWORK_3_ZIPSINGLEFILERESTOREPOINT_H
