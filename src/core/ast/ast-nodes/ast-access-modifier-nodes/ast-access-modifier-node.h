//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_ACCESS_MODIFIER_NODE_H
#define JETLANG_AST_ACCESS_MODIFIER_NODE_H

#include "../ast-node.h"
#include "../ast-symbol-node.h"
#include "../../../type-signature/access-modifier-type-signature/access-modifier-type-signature.h"

class ASTAccessModifierNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
private:
    AccessModifierTypeSignature* _typeSignature = new AccessModifierTypeSignature();
public:
    void setTypeSignature(AccessModifierTypeSignature* typeSignature);
    AccessModifierTypeSignature* getTypeSignature() override;
};

#endif //JETLANG_AST_ACCESS_MODIFIER_NODE_H
