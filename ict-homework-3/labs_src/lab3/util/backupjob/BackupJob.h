#ifndef ICT_HOMEWORK_3_BACKUPJOB_H
#define ICT_HOMEWORK_3_BACKUPJOB_H

#include <list>
#include "JobObject.h"
#include "../../repository/IRepository.h"

/**
 * Собственно виновник торжества. Класс который создаёт на основании добавленных в него
 * JobObject'ов новый рестор поинт, добавляет его в репозиторий и через вызов
 * рестор-поинтовского метода save() сохраняет все данные туда куда умеет сохранять этот рестор-поинт.
 * Ах да, у меня за сохранение данных отвечают исключительно сами рестор-поинты. Не знаю
 * насколько это по заданию, но там вроде нигде не сказано как конкретно это должно происходить:)
 */
class BackupJob {
private:
    std::string name_;
    std::list<JobObject> jobs_;
    IRepository repo_;
public:
    /**
    * Бекап джоба при создании принимает в конструктор: имя и репозиторий с которым она работает
    * То, какой тип рестор-поинтов будет создаваться контролируется в репозитории. Да, в
    * задаче сказано, что надо через бекап-джобу, но я посчитал что можно и по другому,
    * особенно если в бекап-джобой никто не будет работать напрямую.
    */
    BackupJob(std::string name, const IRepository& repo);

    void run();
    void addJob(const JobObject& job);
    void removeJob(const JobObject& job);

    ~BackupJob()=default;
};


#endif //ICT_HOMEWORK_3_BACKUPJOB_H
