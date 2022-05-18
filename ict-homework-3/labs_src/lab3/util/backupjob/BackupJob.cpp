#include "BackupJob.h"

#include <utility>
#include "../factory/RestorePointFactory.h"

BackupJob::BackupJob(std::string name, const IRepository& repo) {
    this->name_=std::move(name);
    this->repo_=repo;
}

void BackupJob::run() {

     /*
     Создаём новый рестор-поинт через фабрику. Какой будет создан рестор-поинт определяется
     на основании значения repo.getRestorePointType()
     */
    IRestorePoint restorePoint = RestorePointFactory::create(
            repo_,
            repo_.getRestorePointType(),
            name_);

    //Добавляем рестор-поинт в репозиторий.
    repo_.addRestorePoint(restorePoint.getName(),
                          restorePoint);
    //Добавляем в рестор-поинт новые стораджи который вытаскиеваем из списка JobObject'ов в переменной jobs_
    for(JobObject j: jobs_){
        restorePoint.addNewStorage(j.getStorage().getName(),j.getStorage());
    }
    /*
    Вызывает у рестор-поинта метод save() чтобы сам же рестор-поинт как он умеет записал
    их туда куда ему надо
    */
    restorePoint.save();
}

void BackupJob::addJob(const JobObject& job) { jobs_.push_back(job);}

void BackupJob::removeJob(const JobObject& job) { jobs_.remove(job);}