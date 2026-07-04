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
    std::shared_ptr<AccessModifierTypeSignature> _typeSignature = std::make_shared<AccessModifierTypeSignature>();
public:
    void setTypeSignature(std::shared_ptr<AccessModifierTypeSignature> typeSignature);
    std::shared_ptr<AccessModifierTypeSignature> getAccessModifierTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
};

#endif //JETLANG_AST_ACCESS_MODIFIER_NODE_H
