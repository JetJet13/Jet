//
// Created by Johny Georges on 2024-08-14.
//

#ifndef JETLANG_LITERAL_IR_INJECTOR_H
#define JETLANG_LITERAL_IR_INJECTOR_H

#include "../expression-ir-injector.h"

class IRLiteralExpressionNode;
class IRIdentifierExpressionNode;
class IRObjectAccessExpressionNode;

class LiteralIRInjector : public ExpressionIRInjector {
    using ExpressionIRInjector::ExpressionIRInjector;
public:
    llvm::Value* inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Value* inject(IRLiteralExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
    llvm::Value* inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
    llvm::Value* inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
};

#endif //JETLANG_LITERAL_IR_INJECTOR_H
