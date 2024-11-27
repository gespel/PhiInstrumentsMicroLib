#pragma once
#include "token.h"
#include <Array.h>

class Function {
public:
    Function();
    Function(String name, Array<Token*, 64> tokens);
    String getName();
    Array<Token*, 64> getTokens();
private:
    String name;
    Array<Token*, 64> tokens;
};

Function::Function() {

}

Function::Function(String name, Array<Token*, 64> tokens) {
    this->name = name;
    this->tokens = tokens;
}

String Function::getName() {
    return this->name;
}

Array<Token*, 64> Function::getTokens() {
    return this->tokens;
}