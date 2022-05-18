#include "ZipSingleFileRestorePoint.h"
#include "../util/factory/StorageFactory.h"
#include "../../../Zipios/zipios/fileentry.hpp"
#include "../../../Zipios/zipios/directoryentry.hpp"
#include "../../../Zipios/zipios/zipiosexceptions.hpp"
#include "../../../Zipios/zipios/filepath.hpp"

ZipSingleFileRestorePoint::ZipSingleFileRestorePoint(std::string name, std::filesystem::path path) : AbstractFSRestorePoint(name, path){
    createNewTmpDir();
    load();
}

void ZipSingleFileRestorePoint::createNewTmpDir() {
    try{
        std::filesystem::path tmp_dir_path {std::filesystem::temp_directory_path() /= std::tmpnam("Homework3ZipSingle")};
        dirUnzipStorages_ = tmp_dir_path;
        std::filesystem::create_directory(dirUnzipStorages_);

    } catch(const std::filesystem::filesystem_error& e){
        std::cerr<<e.what()<<std::endl;
    }
}

void ZipSingleFileRestorePoint::removeTmpDir() {
    if(std::filesystem::exists(dirUnzipStorages_)){
        try{
            for (const auto & file : std::filesystem::directory_iterator(dirUnzipStorages_))
                try{
                    remove(file);
                } catch (const std::filesystem::filesystem_error& e){
                    std::cerr<<e.what()<<std::endl;
                }
            remove(dirUnzipStorages_);

        } catch (const std::filesystem::filesystem_error& e){
            std::cerr<<e.what()<<std::endl;
        }
    }
}

void ZipSingleFileRestorePoint::createParentDirs(std::filesystem::path path) {
    std::filesystem::path parent = path.parent_path();
    if (!std::filesystem::exists(parent)){
        try{
            std::filesystem::create_directories(parent);
        } catch (const std::filesystem::filesystem_error& e){
            std::cerr<<e.what()<<std::endl;
        }
    }
}

void ZipSingleFileRestorePoint::load() {
    if (isLoaded_) return;
    if (!std::filesystem::exists(getPath())) {
        isLoaded_ = true;
        return;
    }

        removeTmpDir();
        createNewTmpDir();

        try{
            zipios::ZipInputStream zis = openZipRead(getPath());
            zipios::FileEntry::pointer_t entry;
            while((entry = zis.getNextEntry()) != nullptr ) {

                IStorage newStor = StorageFactory::create(
                        StorageType::FILES,
                        entry->getName(),
                        dirUnzipStorages_.append(entry->getName())
                );

                getStorages().insert(std::make_pair(entry->getName(), newStor));
                zis.seekg(0, std::ios::end);
                size_t fileSize = zis.tellg();
                zis.seekg(0);
                char* buffer = new char[fileSize];
                newStor.copyInto().write(buffer, fileSize);
                zis.closeEntry();
                zis.close();
                newStor.copyInto().close();
                delete[] buffer;
            }
        } catch(zipios::FileCollectionException& e){
            std::cerr<<e.what()<<std::endl;
        }
        isLoaded_ = true;

}

void ZipSingleFileRestorePoint::save() {
    load();
    std::filesystem::path copy = std::filesystem::path(getPath().string() + "_copy");

    try {
        zipios::ZipOutputStream zos = openZipWrite(copy);

        std::unordered_map<std::string, IStorage> newStorages = getStorages();
        std::set<std::pair<std::string, IStorage>> entrySet;
        for (std::pair<std::string, IStorage> e: getStoragesToCopy()) {
            entrySet.insert(e);
        }
        getStoragesToCopy().clear();
        for (std::pair<std::string, IStorage> e: entrySet) {
            getStoragesToCopy().insert(e);
        }
        std::remove_if(getStoragesToCopy().begin(), getStoragesToCopy().end(),
                       [&newStorages](std::pair<std::string, IStorage> pair) {
                           return (newStorages.count(pair.first) != 0);
                       });
        for (std::pair<std::string, IStorage> e: getStoragesToCopy()) {
            newStorages.insert(std::make_pair(e.first, e.second));
        }
        entrySet.clear();
        for (std::pair<std::string, IStorage> e: newStorages) {
            entrySet.insert(e);
        }
        newStorages.clear();
        for (std::pair<std::string, IStorage> e: entrySet) {
            newStorages.insert(e);
        }
        for (std::pair<std::string, IStorage> e: newStorages) {
            zipios::DirectoryEntry entry(e.first);
            zos.putNextEntry(entry.clone());
            e.second.retrieve().seekg(0, std::ios::end);
            size_t fileSize = e.second.retrieve().tellg();
            e.second.retrieve().seekg(0);
            char *buffer = new char[fileSize];
            zos.write(buffer, fileSize);
            zos.closeEntry();
            zos.close();
            delete[] buffer;
        }
    } catch (zipios::FileCollectionException &e) {
        std::cerr << e.what() << std::endl;
    }
    if (std::filesystem::exists(getPath())) {
        try {
            std::filesystem::remove_all(getPath());
            std::filesystem::rename(copy, getPath());
        } catch (const std::filesystem::filesystem_error &e) {
            std::cerr << e.what() << std::endl;
        }
    } else {
        try {
            std::filesystem::rename(copy, getPath());
        } catch (const std::filesystem::filesystem_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    resetStoragesToCopy();
    removeTmpDir();
    isLoaded_ = false;
    load();
}



zipios::ZipOutputStream ZipSingleFileRestorePoint::openZipWrite(std::filesystem::path path) {
    std::ofstream outputStream;

    if (!std::filesystem::exists(path)){
        createParentDirs(path);
        std::ofstream outputStream(path, std::ios::binary);
        size_t fileSize = std::filesystem::file_size(path);
        outputStream.write(reinterpret_cast<const char *>(&fileSize), sizeof(fileSize));
    } else {
        outputStream.open(path, std::ios::binary);
        size_t fileSize = std::filesystem::file_size(path);
        outputStream.write(reinterpret_cast<const char *>(&fileSize), sizeof(fileSize));
    }
    return zipios::ZipOutputStream(outputStream);

}

zipios::ZipInputStream ZipSingleFileRestorePoint::openZipRead(std::filesystem::path path) {
    std::ifstream inputStream;

    if (!std::filesystem::exists(path)) {
        createParentDirs(path);
        std::ifstream inputStream(path, std::ios::binary);
        size_t fileSize = std::filesystem::file_size(path);
        while(inputStream.read(reinterpret_cast<char *>(&fileSize), sizeof(fileSize))){}
    } else {
        inputStream.open(path, std::ios::binary);
        size_t fileSize = std::filesystem::file_size(path);
        while(inputStream.read(reinterpret_cast<char *>(&fileSize), sizeof(fileSize))){}
    }
    return zipios::ZipInputStream(path.string());
}
