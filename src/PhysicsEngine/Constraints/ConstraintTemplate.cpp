#include "ConstraintTemplate.hpp"


void ConstraintTemplate::show() {
    hidden = false;
}

void ConstraintTemplate::hide() {
    hidden = true;
}

string ConstraintTemplate::getType() const {
    return type;
}

bool ConstraintTemplate::isHidden() const {
    return hidden;
}

ConstraintTemplate::~ConstraintTemplate() {

}

