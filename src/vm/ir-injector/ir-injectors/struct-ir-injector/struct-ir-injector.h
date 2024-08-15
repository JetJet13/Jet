//
// Created by Johny Georges on 2024-08-14.
//

#ifndef JETLANG_STRUCT_IR_INJECTOR_H
#define JETLANG_STRUCT_IR_INJECTOR_H

#include "../expression-ir-injector.h"

class IRStructExpressionNode;
class IRIdentifierExpressionNode;

class StructIRInjector : public ExpressionIRInjector {
    using ExpressionIRInjector::ExpressionIRInjector;
public:
    llvm::Value* inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Value* inject(IRStructExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
    llvm::Value* inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
};

#endif //JETLANG_STRUCT_IR_INJECTOR_H
