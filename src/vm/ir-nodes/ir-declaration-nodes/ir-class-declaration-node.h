//
// Created by Johny Georges on 2024-12-05.
//

#ifndef JETLANG_IR_CLASS_DECLARATION_NODE_H
#define JETLANG_IR_CLASS_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "ir-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../ir-type/ir-class-type.h"
#include "../ir-class-nodes/ir-class-constructor-node.h"
#include "../ir-class-nodes/ir-class-method-node.h"

class IRClassDeclarationNode : public IRDeclarationNode {
private:
    ASTClassDeclarationNode* _node;
    IRClassType* _type;
    std::vector<IRClassConstructorNode*> _constructors;
    std::vector<IRClassMethodNode*> _methods;
public:
    IRClassDeclarationNode(ASTClassDeclarationNode* node, IRClassType* type, std::vector<IRClassConstructorNode*> constructors, std::vector<IRClassMethodNode*> methods);
    IRClassType* getIRType();
    std::vector<IRClassConstructorNode*>* getConstructors();
    std::vector<IRClassMethodNode*>* getMethods();
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CLASS_DECLARATION_NODE_H
