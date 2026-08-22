//
// Created by Johny Georges on 2026-08-22.
//

#ifndef JETLANG_VARIABLE_CONTEXT_H
#define JETLANG_VARIABLE_CONTEXT_H

#include <memory>

class VariableContext {
private:
    bool _isConstant = false;
public:
    VariableContext();
    void markAsConstant();
    bool isConstant();
};

#endif //JETLANG_VARIABLE_CONTEXT_H
