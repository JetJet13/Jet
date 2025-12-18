//
// Created by Johny Georges on 2025-10-25.
//

#ifndef JETLANG_IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"

class IRRefPrototypeInvocationExpressionNode : public IRExpressionNode {
private:
    ASTObjectAccessInvocationExpressionNode* _node;
    llvm::Value* _irFunction;
    IRType* _irFunctionType;
    std::vector<IRExpressionNode*> _arguments;
    IRType* _type;
    IRExpressionNode* _irRef;
public:
    IRRefPrototypeInvocationExpressionNode(ASTObjectAccessInvocationExpressionNode* node, llvm::Value* irFunction, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type, IRExpressionNode* irRef);
    void markAsGlobal() override;
    bool isReferenced() override;
    IRExpressionNode* getIRRefValue();
    std::vector<IRExpressionNode*>* getIRArguments();
    llvm::Value* getValue() override;
    IRType* getFunctionIRType();
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE_H
