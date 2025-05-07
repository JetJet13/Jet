//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_VARIABLE_DECLARATION_NODE_H
#define JETLANG_IR_VARIABLE_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-declaration-node.h"
#include "../ir-instruction-node.h"

class IRVariableDeclarationNode : public IRDeclarationNode {
private:
    ASTVariableDeclarationNode* _node;
    IRInstructionNode* _irValue;
    IRExpressionNode* _irExpression;
    std::optional<IRInstructionNode*> _irGlobalVariable;
public:
    IRVariableDeclarationNode(ASTVariableDeclarationNode* astNode, IRInstructionNode* irValue, IRExpressionNode* irExpression, std::optional<IRInstructionNode*> irGlobalVariable = {});
    bool requiresFreeing();
    std::string getVariableName();
    llvm::Value* getValue() override;
    llvm::Type* getAllocatedType();
    IRType* getAllocatedIRType();
    IRInstructionNode* getIRValue();
    IRExpressionNode* getIRExpression();
    std::optional<IRInstructionNode*> getGlobalVariable();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_VARIABLE_DECLARATION_NODE_H
