#include <gtest/gtest.h>
#include "../labs_src/lab3/repository/IRepository.h"
#include "../labs_src/lab3/util/factory/RepositoryFactory.h"
#include "../labs_src/lab3/util/backupjob/BackupJob.h"
#include "../labs_src/lab3/util/factory/StorageFactory.h"

TEST(CreateBackups, TwoRestorePointsAndThreeStoragesCreated) {

    IRepository repo = RepositoryFactory::create(RepositoryType::FS,
                                                 RestorePointType::ZipSingleFS,
                                                 "myrepo",
                                                 std::filesystem::path("Z:/MUSOR/Backuptest"));

    BackupJob job = BackupJob("restore2", repo);

    std::list<IStorage> storages;

    storages.push_back(StorageFactory::create(StorageType::MEMORY,"jopa", "blya v rot ebal bekapi"));
    storages.push_back(StorageFactory::create(StorageType::MEMORY,"aye", "danya ebi menya v perdak"));
    storages.push_back(StorageFactory::create(StorageType::MEMORY,"meme", "created by Ust'-djalodyansk delegation"));

    for(IStorage stor: storages){
        job.addJob(JobObject(stor));
    }

    job.run();

}


