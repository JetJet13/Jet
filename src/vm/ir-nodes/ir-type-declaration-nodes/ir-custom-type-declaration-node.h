//
// Created by Johny Georges on 2025-07-07.
//

#ifndef JETLANG_IR_CUSTOM_TYPE_DECLARATION_NODE_H
#define JETLANG_IR_CUSTOM_TYPE_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "../ir-instruction-node.h"
#include "ir-type-declaration-node.h"
#include "../../ir-type/ir-struct-type.h"
#include "../../../core/ast/ast-nodes/ast-type-declaration-nodes/ast-custom-type-declaration-node.h"

class IRCustomTypeDeclarationNode : public IRTypeDeclarationNode {
private:
    std::shared_ptr<ASTCustomTypeDeclarationNode> _node;
    std::shared_ptr<IRType> _irType;
public:
    IRCustomTypeDeclarationNode(std::shared_ptr<ASTCustomTypeDeclarationNode> node, std::shared_ptr<IRType> irType);
    std::string getName();
    std::shared_ptr<IRType> getIRType();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CUSTOM_TYPE_DECLARATION_NODE_H
