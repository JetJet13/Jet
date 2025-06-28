//
// Created by Johny Georges on 2025-06-28.
//

#ifndef JETLANG_AST_STRUCT_TYPE_KEY_VALUE_NODE_H
#define JETLANG_AST_STRUCT_TYPE_KEY_VALUE_NODE_H

#include <string>
#include "../../ast-node.h"
#include "ast-struct-type-key-node.h"
#include "../ast-type-node.h"
#include "ast-struct-type-colon-node.h"


class ASTStructTypeKeyValueNode : public ASTNode {
private:
    ASTStructTypeKeyNode* _name;
    ASTStructTypeColonNode* _colon;
    ASTTypeNode* _type;
    TypeSignature* _typeSignature = new UnknownTypeSignature();
public:
    ASTStructTypeKeyValueNode(ASTStructTypeKeyNode* name, ASTStructTypeColonNode* colon, ASTTypeNode* type);
    ASTStructTypeKeyNode* getName();
    ASTTypeNode* getType();
    void setTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_STRUCT_TYPE_KEY_VALUE_NODE_H
