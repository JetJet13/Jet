//
// Created by Johny Georges on 2024-07-08.
//

#ifndef JETLANG_IR_FUNCTION_DECLARATION_NODE_H
#define JETLANG_IR_FUNCTION_DECLARATION_NODE_H

#include <llvm/IR/Function.h>
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../ir-block-nodes/ir-block-node.h"
#include "../ir-function-nodes/ir-function-parameter-list-node.h"
#include "ir-declaration-node.h"
#include "../../ir-lookup-table/ir-lookup-table.h"

class IRFunctionDeclarationNode : public IRDeclarationNode {
private:
    ASTFunctionDeclarationNode* _node;
    llvm::Function* _irValue;
    IRFunctionParameterListNode* _irParameterList;
    IRBlockNode* _irBlock;
    IRLookupTable* _scope;
public:
    IRFunctionDeclarationNode(ASTFunctionDeclarationNode* node, llvm::Function* irValue, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock, IRLookupTable* scope);
    std::string getName();
    IRFunctionParameterListNode* getParameters();
    IRBlockNode* getBlock();
    IRLookupTable* getScope();
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_DECLARATION_NODE_H
