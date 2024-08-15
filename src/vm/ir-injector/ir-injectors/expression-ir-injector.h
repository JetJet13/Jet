//
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_EXPRESSION_IR_INJECTOR_H
#define JETLANG_EXPRESSION_IR_INJECTOR_H

#include "ir-injector.h"

class ExpressionIRInjector : public IRInjector {
    using IRInjector::IRInjector;
public:
    virtual llvm::Value* inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) = 0;
};

#endif //JETLANG_EXPRESSION_IR_INJECTOR_H
