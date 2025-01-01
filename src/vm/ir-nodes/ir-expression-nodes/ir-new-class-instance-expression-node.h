//
// Created by Johny Georges on 2024-12-30.
//

#ifndef JETLANG_IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE_H
#define JETLANG_IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"
#include "../../../core/type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../ir-type/ir-class-type.h"

class IRNewClassInstanceExpressionNode : public IRExpressionNode {
private:
    ASTNewClassInstanceExpressionNode* _node;
    llvm::Value* _irConstructor;
    IRFunctionType* _irConstructorType;
    std::vector<IRExpressionNode*> _arguments;
    IRClassType* _type;
public:
    IRNewClassInstanceExpressionNode(ASTNewClassInstanceExpressionNode* node, llvm::Value* irConstructor, IRFunctionType* irConstructorType, std::vector<IRExpressionNode*> arguments, IRClassType* type);
    std::vector<IRExpressionNode*>* getIRArguments();
    llvm::Value* getValue() override;
    IRFunctionType* getConstructorIRType();
    llvm::Value* getConstructorFunction();
    IRClassType* getIRType() override;
    ClassInstanceTypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE_H
