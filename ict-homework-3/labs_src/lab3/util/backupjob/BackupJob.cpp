#include "BackupJob.h"

#include <utility>
#include "../factory/RestorePointFactory.h"

BackupJob::BackupJob(std::shared_ptr<IRepository> repo) : repo_(repo)
{
}

void BackupJob::backup(std::string name) {
    if (repo_->getRestorePoints().contains(name))
        throw std::invalid_argument("Restore point with given name '" + name + "' already exists");

    /*
    Создаём новый рестор-поинт через фабрику. Какой будет создан рестор-поинт определяется
    на основании значения repo.getRestorePointType()
    */
    std::shared_ptr<IRestorePoint> restorePoint = RestorePointFactory::create(
            repo_,
            repo_->getRestorePointType(),
            name);

    // Рестор поинт добавляем в репозиторий
    repo_->addRestorePoint(name, restorePoint);

    // Считываем джобы в стораджи
    restorePoint->generate(jobs_);

    // Сохраняем ресторпоинт на диск
    restorePoint->save();
}

void BackupJob::addJob(std::shared_ptr<IJobObject> job) { jobs_.push_back(job);}

void BackupJob::removeJob(std::shared_ptr<IJobObject> job) { jobs_.remove(job); }