//
// Created by Johny Georges on 2024-04-25.
//

#ifndef JETLANG_AST_CLASS_ACCESS_NODE_H
#define JETLANG_AST_CLASS_ACCESS_NODE_H

#include <string>
#include "ast-class-property-name-node.h"
#include "../ast-node.h"
#include "ast-this-access-node.h"
#include "ast-this-node.h"
#include "../../../type-signature/class-type-signature/class-type-signature.h"

class ASTClassAccessNode : public ASTNode {
private:
    std::shared_ptr<ASTThisNode> _this;
    std::shared_ptr<ASTThisAccessNode> _thisAccess;
    std::shared_ptr<ClassTypeSignature> _typeSignature = std::make_shared<ClassTypeSignature>();
public:
    ASTClassAccessNode(std::shared_ptr<ASTThisNode> thisNode, std::shared_ptr<ASTThisAccessNode> thisAccess);
    std::shared_ptr<ASTThisNode> getThis();
    std::shared_ptr<ASTThisAccessNode> getThisAccess();
    void setTypeSignature(std::shared_ptr<ClassTypeSignature> typeSignature);
    std::shared_ptr<ClassTypeSignature> getClassTypeSignature();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_ACCESS_NODE_H
