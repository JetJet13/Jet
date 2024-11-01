//
// Created by Johny Georges on 2024-07-08.
//

#ifndef JETLANG_IR_FUNCTION_DECLARATION_NODE_H
#define JETLANG_IR_FUNCTION_DECLARATION_NODE_H

#include <llvm/IR/Function.h>
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../ir-block-node.h"
#include "../ir-function-nodes/ir-function-parameter-list-node.h"
#include "ir-declaration-node.h"

class IRFunctionDeclarationNode : public IRDeclarationNode {
private:
    ASTFunctionDeclarationNode* _node;
    llvm::Function* _irValue;
    IRFunctionParameterListNode* _irParameterList;
    IRBlockNode* _irBlock;
public:
    IRFunctionDeclarationNode(ASTFunctionDeclarationNode* node, llvm::Function* irValue, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock);
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_DECLARATION_NODE_H
