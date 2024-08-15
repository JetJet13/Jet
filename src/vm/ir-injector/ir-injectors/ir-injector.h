//
// Created by Johny Georges on 2024-08-12.
//

#ifndef JETLANG_IR_INJECTOR_H
#define JETLANG_IR_INJECTOR_H

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>

class IRInjectorMap;
class IRExpressionNode;

class IRInjector {
protected:
    IRInjectorMap* _irInjectorMap;
public:
    IRInjector(IRInjectorMap* irInjectorMap);
};

#endif //JETLANG_IR_INJECTOR_H
