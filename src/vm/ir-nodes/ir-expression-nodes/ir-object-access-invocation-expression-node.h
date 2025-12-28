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
    llvm::CallInst* _irCallInstruction;
    IRInstructionNode* _irFunction;
    IRType* _irFunctionType;
    std::vector<IRExpressionNode*> _arguments;
    IRType* _type;
    std::optional<IRExpressionNode*> _scopeArgument;
public:
    IRObjectAccessInvocationExpressionNode(ASTObjectAccessInvocationExpressionNode* node, IRInstructionNode* irFunction, llvm::CallInst* irCallInstruction, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type, std::optional<IRExpressionNode*> scopeArgument = {});
    void markAsGlobal() override;
    bool isReferenced() override;
    IRInstructionNode* getFunction();
    std::optional<IRExpressionNode*> getScopeArgument();
    std::vector<IRExpressionNode*>* getIRArguments();
    llvm::CallInst* getValue() override;
    llvm::Value* getFunctionValue();
    IRType* getFunctionIRType();
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE_H
