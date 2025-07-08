//
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_AST_TYPE_DECLARATION_NODE_H
#define JETLANG_AST_TYPE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../../../type-signature/unknown-type-signature/unknown-type-signature.h"

class ASTTypeDeclarationNode : public ASTNode {
protected:
    TypeSignature* _typeSignature = new UnknownTypeSignature();
public:
    virtual void setTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getTypeSignature() override;
};

#endif //JETLANG_AST_TYPE_DECLARATION_NODE_H
