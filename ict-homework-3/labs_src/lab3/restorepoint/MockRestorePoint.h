#ifndef ICT_HOMEWORK_3_MOCKRESTOREPOINT_H
#define ICT_HOMEWORK_3_MOCKRESTOREPOINT_H

#include "AbstractRestorePoint.h"

class MockRestorePoint : public AbstractRestorePoint {
private:

public:
    MockRestorePoint(std::string name);

    void save() override;
    void load() override;

    ~MockRestorePoint() = default;
};


#endif //ICT_HOMEWORK_3_MOCKRESTOREPOINT_H
