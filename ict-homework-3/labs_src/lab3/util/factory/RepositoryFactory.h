#ifndef ICT_HOMEWORK_3_REPOSITORYFACTORY_H
#define ICT_HOMEWORK_3_REPOSITORYFACTORY_H

#include "../../repository/IRepository.h"
#include "enums/RepositoryType.h"
#include "enums/RestorePointType.h"

/**
 * Фабрика используемая для создания репозиториев.
 * Доступен всего 1 вид. Для создания нужно дополнительно передать в качестве аргумента
 * объект типа fs::path который хранит путь к корню репозитория.
 * Т.к. "невозможно" заранее узнать типы передаваемых аргументов - используется темплейт класса Object,
 * эт замена примитивная дженериков, а от него уже внутри всё дальше кастится обратно к ожидаемым типам.
 * По хорошему, тут должны быть проверки на эти типы, но дабы упростить понимание кода я их опустил.
 * Я хз насколько это адекватное решение с точки зрения профессиональных программистов,
 * но фабрика с var-args'ами для меня выглядит самым простым решением
 *(но я понимаю, что оно далеко не самое безопасное). Собственно, то же самое относится к другим фабрикам.
 **/
class RepositoryFactory final {
public:
    template<class Object>
    static IRepository create(RepositoryType repoType, RestorePointType restoreType, std::string name, Object args,...);
};


#endif //ICT_HOMEWORK_3_REPOSITORYFACTORY_H
