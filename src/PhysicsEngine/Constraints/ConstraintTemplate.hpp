#pragma once
#include <string>

using namespace std;

class ConstraintTemplate {
protected:
    string type = "template";

    bool hidden = false;
public:
    void show();
    void hide();

    string getType() const;
    bool isHidden() const;

    virtual ~ConstraintTemplate();
};
