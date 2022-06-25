#ifndef ICT_HOMEWORK_3_ZIPSPLITFILERESTOREPOINT_H
#define ICT_HOMEWORK_3_ZIPSPLITFILERESTOREPOINT_H

#include "AbstractFSRestorePoint.h"

#include "zipios/zipiosexceptions.hpp"
#include "zipios/directorycollection.hpp"
#include "zipios/directoryentry.hpp"
#include "zipios/zipfile.hpp"

class ZipSplitFileRestorePoint : public AbstractFSRestorePoint{
private:
    //std::filesystem::path dirUnzipStorages_;
    bool isLoaded_ = false;

    void createNewTmpDir();
    void removeTmpDir();
    void createParentDirs(std::filesystem::path path);
public:
    ZipSplitFileRestorePoint(std::string name, std::filesystem::path path);

    void save() override;
    void load() override;

    ~ZipSplitFileRestorePoint() = default;
};


#endif //ICT_HOMEWORK_3_ZIPSPLITFILERESTOREPOINT_H
