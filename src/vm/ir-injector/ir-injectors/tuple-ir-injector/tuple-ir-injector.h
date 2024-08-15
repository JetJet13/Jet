//
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_TUPLE_IR_INJECTOR_H
#define JETLANG_TUPLE_IR_INJECTOR_H

#include "../expression-ir-injector.h"

class IRTupleExpressionNode;
class IRIdentifierExpressionNode;

class TupleIRInjector : public ExpressionIRInjector {
    using ExpressionIRInjector::ExpressionIRInjector;
public:
    llvm::Value* inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Value* inject(IRTupleExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
    llvm::Value* inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
};

#endif //JETLANG_TUPLE_IR_INJECTOR_H
