#pragma once
#include <string>

using namespace std;

class ConstraintTemplate {
protected:
    string type = "template";

public:
    string getType();
    virtual ~ConstraintTemplate();
};
