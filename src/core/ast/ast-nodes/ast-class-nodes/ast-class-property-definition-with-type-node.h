//
// Created by Johny Georges on 2024-04-24.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE_H


#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "ast-class-property-definition-node.h"

class ASTClassPropertyDefinitionWithTypeNode : public ASTNode {
private:
    ASTClassPropertyDefinitionNode* _classPropertyDefinition;
    ASTColonNode* _colon;
    ASTTypeNode* _type;
public:
    ASTClassPropertyDefinitionWithTypeNode(ASTClassPropertyDefinitionNode* classPropertyDefinition, ASTColonNode* colon, ASTTypeNode* type);
    ASTClassPropertyDefinitionNode* getClassPropertyDefinition();
    ASTColonNode* getColon();
    ASTTypeNode* getType();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE_H
