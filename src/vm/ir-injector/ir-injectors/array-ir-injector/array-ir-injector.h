//
// Created by Johny Georges on 2024-08-13.
//

#ifndef JETLANG_ARRAY_IR_INJECTOR_H
#define JETLANG_ARRAY_IR_INJECTOR_H

#include "../expression-ir-injector.h"

class IRArrayExpressionNode;
class IRIdentifierExpressionNode;

class ArrayIRInjector : public ExpressionIRInjector {
    using ExpressionIRInjector::ExpressionIRInjector;
public:
    llvm::Value* inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Value* inject(IRArrayExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
    llvm::Value* inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
};

#endif //JETLANG_ARRAY_IR_INJECTOR_H
