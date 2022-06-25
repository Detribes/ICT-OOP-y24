#include "ZipSingleFileRestorePoint.h"
#include "../util/factory/StorageFactory.h"


ZipSingleFileRestorePoint::ZipSingleFileRestorePoint(std::string name, std::filesystem::path path) : AbstractFSRestorePoint(name, path) {
}

void ZipSingleFileRestorePoint::createNewTmpDir() {
}

void ZipSingleFileRestorePoint::removeTmpDir() {
}

void ZipSingleFileRestorePoint::createParentDirs(std::filesystem::path path) {
}

void ZipSingleFileRestorePoint::load() {
    std::string filename = getPath().string() + getName();

    if (!std::filesystem::exists(filename))
        throw std::invalid_argument("RestorePoint at path " + filename + " does not exist");
    if (isLoaded_)
        throw std::invalid_argument("RestorePoint " + getName() + " is already loaded");
    
    try {
        zipios::ZipFile zf = zipios::ZipFile(filename);
        auto entries(zf.entries());

        for (auto it = entries.begin(); it != entries.end(); ++it)
        {
            auto entry = it->get();
            // директории нафиг
            if (entry->isDirectory()) continue;
            
            std::shared_ptr<IStorage> newStor = StorageFactory::create(
                    StorageType::FILES,
                    getPath().append(entry->getName())
            );

            auto stream = zf.getInputStream(entry->getName());
            // Считываем файл из зипа в энтри
            std::vector<uint8_t> data;
            std::for_each(std::istreambuf_iterator<char>(stream->rdbuf()),
                std::istreambuf_iterator<char>(),
                [&data](const char c){
                data.push_back(c);
            });
            zf.close();
            // Запихиваем данные в сторадж
            newStor->updateData(data);
            getStorages().insert(std::make_pair(entry->getName(), newStor));
        }
        isLoaded_ = true;
    }
    catch (std::exception &e) {
        std::cerr << "Failed to read zipfile" << filename << " due to " << e.what() << std::endl;
    }
}

void ZipSingleFileRestorePoint::save() {
    zipios::DirectoryCollection dc;
    // имя зипфайла в который хотим записать
    std::string filename = getPath().string() + getName() + ".zip";
    for (auto &s : getStorages())
    {
        // лютая конструкция
        zipios::DirectoryEntry de = zipios::DirectoryEntry(s.second->getPath());
        dc.addEntry(de);
    }
    std::ofstream ofStream(filename, std::ios_base::binary | std::ios::out);
    zipios::ZipFile::saveCollectionToArchive(ofStream, dc);
}