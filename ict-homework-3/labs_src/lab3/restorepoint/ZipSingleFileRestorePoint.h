#ifndef ICT_HOMEWORK_3_ZIPSINGLEFILERESTOREPOINT_H
#define ICT_HOMEWORK_3_ZIPSINGLEFILERESTOREPOINT_H

#include "AbstractFSRestorePoint.h"

#include "zipios/fileentry.hpp"
#include "zipios/directoryentry.hpp"
#include "zipios/directorycollection.hpp"
#include "zipios/zipiosexceptions.hpp"
#include "zipios/filepath.hpp"
#include "zipios/zipfile.hpp"

class ZipSingleFileRestorePoint : public AbstractFSRestorePoint {
private:
    //std::filesystem::path dirUnzipStorages_;
    bool isLoaded_ = false;

    void createNewTmpDir();
    void removeTmpDir();
    void createParentDirs(std::filesystem::path path);
public:
    ZipSingleFileRestorePoint(std::string name, std::filesystem::path path);

    void save() override;
    void load() override;

    ~ZipSingleFileRestorePoint() = default;
};


#endif //ICT_HOMEWORK_3_ZIPSINGLEFILERESTOREPOINT_H
