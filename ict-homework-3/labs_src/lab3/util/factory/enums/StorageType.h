#ifndef ICT_HOMEWORK_3_STORAGETYPE_H
#define ICT_HOMEWORK_3_STORAGETYPE_H

/**
 * Перечисление с доступными типами стораджей. Используется в соответствующей фабрике.
 * Сейчас доступны два типа стораджа: FILE в форме файла в ФС и MEMORY в виде файла
 * хранящегося в оперативной памяти (т.е. пока существует процесс с программой).
 */
enum  StorageType{
    FILES, MEMORY
};
#endif //ICT_HOMEWORK_3_STORAGETYPE_H
