//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_TYPE_BASE_NODE_H
#define JETLANG_AST_TYPE_BASE_NODE_H

#include "../ast-node.h"
#include "../../../type-signature/type-signature.h"
#include "../../../type-signature/unknown-type-signature/unknown-type-signature.h"

class ASTTypeBaseNode : public ASTNode {
private:
    std::shared_ptr<TypeSignature> _typeSignature = std::make_shared<UnknownTypeSignature>();
public:
    void setTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
};

#endif //JETLANG_AST_TYPE_BASE_NODE_H
