//
// Created by Johny Georges on 2026-02-06.
//

#ifndef JETLANG_IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-access-invocation-expression-node.h"
#include "ir-array-access-expression-node.h"
#include "../ir-function-nodes/ir-function-argument-node.h"

class IRArrayAccessInvocationExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTArrayAccessInvocationExpressionNode> _node;
    IRArrayAccessExpressionNode* _irArrayAccessExpression;
    llvm::CallInst* _irCallInstruction;
    IRType* _irFunctionType;
    std::vector<IRFunctionArgumentNode*> _arguments;
    IRType* _type;
public:
    IRArrayAccessInvocationExpressionNode(std::shared_ptr<ASTArrayAccessInvocationExpressionNode> node, IRArrayAccessExpressionNode* irArrayAccessExpression, llvm::CallInst* irCallInstruction, IRType* irFunctionType, std::vector<IRFunctionArgumentNode*> arguments, IRType* type);
    void markAsGlobal() override;
    IRArrayAccessExpressionNode* getIRArrayAccessExpression();
    std::vector<IRFunctionArgumentNode*>* getIRArguments();
    llvm::CallInst* getValue() override;
    IRType* getFunctionIRType();
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE_H
