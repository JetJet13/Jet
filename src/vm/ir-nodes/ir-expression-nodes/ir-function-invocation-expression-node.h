//
// Created by Johny Georges on 2024-11-08.
//

#ifndef JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"

class IRFunctionInvocationExpressionNode : public IRExpressionNode {
private:
    ASTFunctionInvocationExpressionNode* _node;
    llvm::CallInst* _irFunctionCall;
    IRType* _type;
public:
    IRFunctionInvocationExpressionNode(ASTFunctionInvocationExpressionNode* node, llvm::CallInst* irFunctionCall, IRType* type);
    llvm::Value* getValue() override;
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H
