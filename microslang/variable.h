#pragma once
#include "Arduino.h"

class Variable {
public:
    Variable(String name, float value);
    float getValue();
    String getName();
private:
    String name;
    float value;
};

Variable::Variable(String name, float value) {
    this->name = name;
    this->value = value;
}

String Variable::getName() {
    return name;
}

float Variable::getValue() {
    return value;
}
