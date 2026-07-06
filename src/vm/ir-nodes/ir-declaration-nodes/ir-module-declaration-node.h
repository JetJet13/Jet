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
    std::shared_ptr<ASTModuleDeclarationNode> _node;
    std::shared_ptr<IRInstructionNode> _allocation;
    std::shared_ptr<IRModuleType> _type;
    std::vector<std::shared_ptr<IRDeclarationNode>> _exports;
public:
    IRModuleDeclarationNode(std::shared_ptr<ASTModuleDeclarationNode> node, std::shared_ptr<IRInstructionNode> allocation, std::shared_ptr<IRModuleType> type, std::vector<std::shared_ptr<IRDeclarationNode>> exports);
    std::shared_ptr<IRInstructionNode> getAllocation();
    std::shared_ptr<IRModuleType> getIRType();
    std::vector<std::shared_ptr<IRDeclarationNode>>* getExports();
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_MODULE_DECLARATION_NODE_H
