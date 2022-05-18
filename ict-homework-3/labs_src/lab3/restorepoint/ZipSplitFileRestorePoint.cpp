#include "ZipSplitFileRestorePoint.h"
#include "../../../Zipios/zipios/zipiosexceptions.hpp"
#include "../util/factory/StorageFactory.h"
#include "../../../Zipios/zipios/directoryentry.hpp"

ZipSplitFileRestorePoint::ZipSplitFileRestorePoint(std::string name, std::filesystem::path path) : AbstractFSRestorePoint(name, path){
    createNewTmpDir();
    load();
}

void ZipSplitFileRestorePoint::createNewTmpDir() {
        try{
            std::filesystem::path tmp_dir_path {std::filesystem::temp_directory_path() /= std::tmpnam("Homework3ZipSplit")};
            dirUnzipStorages_ = tmp_dir_path;
            std::filesystem::create_directory(dirUnzipStorages_);

        } catch(const std::filesystem::filesystem_error& e){
            std::cerr<<e.what()<<std::endl;
        }
}

void ZipSplitFileRestorePoint::removeTmpDir() {
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

void ZipSplitFileRestorePoint::createParentDirs(std::filesystem::path path) {
    std::filesystem::path parent = path.parent_path();
    if (!std::filesystem::exists(parent)){
        try{
            std::filesystem::create_directories(parent);
        } catch (const std::filesystem::filesystem_error& e){
            std::cerr<<e.what()<<std::endl;
        }
    }
}

zipios::ZipOutputStream ZipSplitFileRestorePoint::openZipWrite(std::filesystem::path path) {
    std::ofstream outputStream;

    if (!std::filesystem::exists(path)){
        createParentDirs(path);
        std::ofstream outStream (path, std::ios::binary);
        size_t fileSize = std::filesystem::file_size(path);
        outStream.write(reinterpret_cast<const char *>(&fileSize), sizeof(fileSize));
        return zipios::ZipOutputStream(outStream);
    } else {
        outputStream.open(path, std::ios::binary);
        size_t fileSize = std::filesystem::file_size(path);
        outputStream.write(reinterpret_cast<const char *>(&fileSize), sizeof(fileSize));
        return zipios::ZipOutputStream(outputStream);
    }

}

zipios::ZipInputStream ZipSplitFileRestorePoint::openZipRead(std::filesystem::path path) {
    std::ifstream inputStream;

    if (!std::filesystem::exists(path)) {
        createParentDirs(path);
        std::ifstream inStream(path, std::ios::binary);
        size_t fileSize = std::filesystem::file_size(path);
        while(inStream.read(reinterpret_cast<char *>(&fileSize), sizeof(fileSize))){}
        return zipios::ZipInputStream(path.string());
    } else {
        inputStream.open(path, std::ios::binary);
        size_t fileSize = std::filesystem::file_size(path);
        while(inputStream.read(reinterpret_cast<char *>(&fileSize), sizeof(fileSize))){}
        return zipios::ZipInputStream(path.string());
    }
}

void ZipSplitFileRestorePoint::load() {
    if (isLoaded_) return;
    if (!std::filesystem::exists(getPath())) {
        isLoaded_ = true;
        return;
    }

    removeTmpDir();
    createNewTmpDir();

    try{
        std::vector<std::filesystem::path> dir;
        for (std::filesystem::path dirFile: std::filesystem::directory_iterator{getPath()}){
            if(is_regular_file(dirFile)){
                dir.push_back(dirFile);
            }
        }
        for (std::filesystem::path const& dirFile : dir){
            std::filesystem::path newFile;
            std::string newFileName;
            try{
                newFile = dirUnzipStorages_.append(dirFile.filename().string());
                newFileName = newFile.filename().string();

            } catch (const std::filesystem::filesystem_error &e) {
                std::cerr << e.what() << std::endl;
            }
            try{
                zipios::ZipInputStream zis = openZipRead(dirFile);
                std::ofstream fos(newFile, std::ios::binary|std::ios::app);
                size_t fileSize = std::filesystem::file_size(newFile);
                fos.write(reinterpret_cast<const char *>(&fileSize), sizeof(fileSize));

                zis.seekg(0, std::ios::end);
                size_t fSize = zis.tellg();
                zis.seekg(0);
                char *buffer = new char[fSize];
                fos.write(buffer, fSize);
                fos.close();
                delete[] buffer;
            } catch (zipios::FileCollectionException &e) {
                std::cerr << e.what() << std::endl;
            }
            catch (const std::filesystem::filesystem_error &e) {
                std::cerr << e.what() << std::endl;
            }
            IStorage newStor = StorageFactory::create(StorageType::FILES,
                                                      newFileName,
                                                      dirUnzipStorages_.append(newFileName));
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << e.what() << std::endl;
    }
    isLoaded_ = true;
}

void ZipSplitFileRestorePoint::save() {
    load();

    std::unordered_map<std::string, IStorage> newStorages;
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
    for (std::pair<std::string, IStorage> e: newStorages){
        try{
            zipios::ZipOutputStream zos = openZipWrite(getPath().append(e.first));
            IStorage stor = e.second;

            zipios::DirectoryEntry entry(stor.getName());
            zos.putNextEntry(entry.clone());

            stor.retrieve().seekg(0, std::ios::end);
            size_t fileSize = stor.retrieve().tellg();
            stor.retrieve().seekg(0);
            char *buffer = new char[fileSize];
            zos.write(buffer, fileSize);
            zos.closeEntry();
            zos.close();
            delete[] buffer;
        } catch (zipios::FileCollectionException &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    resetStoragesToCopy();
    removeTmpDir();
    isLoaded_ = false;
    load();
}