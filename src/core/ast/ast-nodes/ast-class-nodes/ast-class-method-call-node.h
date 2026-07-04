//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_METHOD_CALL_NODE_H
#define JETLANG_AST_CLASS_METHOD_CALL_NODE_H

#include "../ast-symbol-node.h"
#include "../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"

class ASTClassMethodCallNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
private:
    std::shared_ptr<ClassMethodTypeSignature> _typeSignature = std::make_shared<ClassMethodTypeSignature>();
public:
    void setTypeSignature(std::shared_ptr<ClassMethodTypeSignature> classMethodTypeSignature);
    std::shared_ptr<ClassMethodTypeSignature> getMethodTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_CLASS_METHOD_CALL_NODE_H
