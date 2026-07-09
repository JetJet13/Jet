//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_AST_LITERAL_NODE_H
#define JETLANG_AST_LITERAL_NODE_H

#include <any>
#include "../../types/ast-node-type.h"
#include "../ast-node.h"
#include "../../../type-signature/literal-type-signature/literal-type-signature.h"

class ASTLiteralNode : public ASTNode {
protected:
    Lexeme* _lexeme;
    std::shared_ptr<LiteralTypeSignature> _typeSignature = std::make_shared<LiteralTypeSignature>();
public:
    explicit ASTLiteralNode(Lexeme* lexemeLiteral);
    Lexeme* getLiteral();
    void setTypeSignature(std::shared_ptr<LiteralTypeSignature> typeSignature);
    std::shared_ptr<LiteralTypeSignature> getLiteralTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    virtual void setValue(std::shared_ptr<TokenTable> tokenTable) = 0;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_LITERAL_NODE_H
