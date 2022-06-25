#include <gtest/gtest.h>
#include "../labs_src/lab3/repository/IRepository.h"
#include "../labs_src/lab3/util/factory/RepositoryFactory.h"
#include "../labs_src/lab3/util/backupjob/BackupJob.h"
#include "../labs_src/lab3/util/backupjob/MockJobObject.h"
#include "../labs_src/lab3/util/factory/StorageFactory.h"

TEST(CreateBackups, TwoRestorePointsAndThreeJobsCreated) {
    std::cout << "Creating a repository" << std::endl;
    std::shared_ptr<IRepository> repo;
    try {
        repo = RepositoryFactory::create(RepositoryType::Mock, RestorePointType::ZipSplitFS, "myrepo", std::filesystem::path("./backuptest"));     
    }
    catch (std::exception &ex) {
        std::cerr << "Failed to create repository: " << ex.what() << std::endl;
        FAIL();
    }

    std::cout << "Creating a backup job" << std::endl;
    BackupJob job = BackupJob(repo);

    try {
        job.addJob(std::make_shared<MockJobObject>("kek1.bin", std::vector<uint8_t>{1, 2, 3, 4, 5}));
        job.addJob(std::make_shared<MockJobObject>("kek2.bin", std::vector<uint8_t>{2, 3, 4, 5, 6}));
        job.addJob(std::make_shared<MockJobObject>("kek3.bin", std::vector<uint8_t>{3, 4, 5, 6, 7}));
    }
    catch (std::exception &ex) {
        std::cerr << "Failed to add job objects: " << ex.what() << std::endl;
        FAIL();
    }

    std::cout << "Making backups/restorepoints" << std::endl;
    try {
        job.backup("jopa1");
        job.backup("jopa2");
    }
    catch (std::exception &ex) {
        std::cerr << "Failed to make a backup/restorepoint: " << ex.what() << std::endl;
        FAIL();
    }

    try {
        repo->restore("jopa1");
    }
    catch (std::exception &ex) {
        std::cerr << "Failed to restore a restorepoint: " << ex.what() << std::endl;
        FAIL();
    }
}


