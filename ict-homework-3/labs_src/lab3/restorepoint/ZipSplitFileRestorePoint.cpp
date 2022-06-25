#include "ZipSplitFileRestorePoint.h"

#include "../util/factory/StorageFactory.h"

ZipSplitFileRestorePoint::ZipSplitFileRestorePoint(std::string name, std::filesystem::path path) : AbstractFSRestorePoint(name, path) {
}

void ZipSplitFileRestorePoint::createNewTmpDir() {
}

void ZipSplitFileRestorePoint::removeTmpDir() {
}

void ZipSplitFileRestorePoint::createParentDirs(std::filesystem::path path) {
}

void ZipSplitFileRestorePoint::load() {
    if (!std::filesystem::exists(getPath())) 
        throw std::invalid_argument("RestorePoint load path " + getPath().string() + " does not exist");
    if (isLoaded_)
        throw std::invalid_argument("RestorePoint " + getName() + " is already loaded");

    std::string filename = "";
    try {
        for (auto &f : std::filesystem::directory_iterator(getPath()))
        {
            if (!std::filesystem::is_regular_file(f)) continue;
            filename = f.path().string();

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
        }
        isLoaded_ = true;
    }
    catch (std::exception &e) {
        std::cerr << "Failed to read zipfile" << filename << " due to " << e.what() << std::endl;
    }
}

void ZipSplitFileRestorePoint::save() {
    for (auto &s : getStorages())
    {
        std::string filename = getPath().string() + s.second->getPath().filename().string() + ".zip";
        zipios::DirectoryCollection dc(s.second->getPath());
        // Записываем стораджи напрямую в зипфайл
        std::ofstream ofStream(filename, std::ios_base::binary | std::ios::out);
        zipios::ZipFile::saveCollectionToArchive(ofStream, dc);
    }
}