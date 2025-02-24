//
// Created by Johny Georges on 2024-10-29.
//

#ifndef JETLANG_IR_MODULE_DECLARATION_NODE_H
#define JETLANG_IR_MODULE_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "ir-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"
#include "../../ir-type/ir-module-type.h"
#include "../ir-instruction-node.h"

class IRModuleDeclarationNode : public IRDeclarationNode {
private:
    ASTModuleDeclarationNode* _node;
    IRInstructionNode* _allocation;
    IRModuleType* _type;
    std::vector<IRDeclarationNode*> _exports;
public:
    IRModuleDeclarationNode(ASTModuleDeclarationNode* node, IRInstructionNode* allocation, IRModuleType* type, std::vector<IRDeclarationNode*> exports);
    IRInstructionNode* getAllocation();
    IRModuleType* getIRType();
    std::vector<IRDeclarationNode*>* getExports();
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_MODULE_DECLARATION_NODE_H
