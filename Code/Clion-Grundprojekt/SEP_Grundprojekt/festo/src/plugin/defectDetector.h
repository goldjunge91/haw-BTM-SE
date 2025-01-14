//
// Created by Marco Tozzi on 14.01.25.
//

#ifndef DEFECTDETECTOR_H
#define DEFECTDETECTOR_H

#include "plugin.h"

class defectDetector : public Plugin {
public:
    defectDetector();
    ~defectDetector();
    void evalCycle() override;
    bool result() override;

private:


};



#endif //DEFECTDETECTOR_H