//
// Created by Johny Georges on 2025-06-20.
//

#ifndef JETLANG_IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-access-invocation-expression-node.h"
#include "ir-tuple-access-expression-node.h"
#include "ir-object-access-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"

class IRObjectAccessInvocationExpressionNode : public IRExpressionNode {
private:
    ASTObjectAccessInvocationExpressionNode* _node;
    IRObjectAccessExpressionNode* _irObjectAccessExpression;
    IRType* _irFunctionType;
    std::vector<IRExpressionNode*> _arguments;
    IRType* _type;
public:
    IRObjectAccessInvocationExpressionNode(ASTObjectAccessInvocationExpressionNode* node, IRObjectAccessExpressionNode* irObjectAccessExpression, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type);
    void markAsGlobal() override;
    IRObjectAccessExpressionNode* getIRObjectAccessExpression();
    std::vector<IRExpressionNode*>* getIRArguments();
    llvm::Value* getValue() override;
    IRType* getFunctionIRType();
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE_H
