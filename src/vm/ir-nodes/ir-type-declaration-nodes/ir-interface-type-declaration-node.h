//
// Created by Johny Georges on 2025-07-04.
//

#ifndef JETLANG_IR_INTERFACE_TYPE_DECLARATION_NODE_H
#define JETLANG_IR_INTERFACE_TYPE_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "../ir-instruction-node.h"
#include "../../../core/ast/ast-nodes/ast-type-declaration-nodes/ast-interface-type-declaration-node.h"
#include "ir-type-declaration-node.h"
#include "../../ir-type/ir-struct-type.h"

class IRInterfaceTypeDeclarationNode : public IRTypeDeclarationNode {
private:
    std::shared_ptr<ASTInterfaceTypeDeclarationNode> _node;
    IRStructType* _irInterfaceType;
public:
    IRInterfaceTypeDeclarationNode(std::shared_ptr<ASTInterfaceTypeDeclarationNode> node, IRStructType* irInterfaceType);
    std::string getName();
    IRStructType* getIRType();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_INTERFACE_TYPE_DECLARATION_NODE_H
