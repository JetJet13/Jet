//
// Created by Johny Georges on 2024-04-24.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE_H


#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "ast-class-property-definition-node.h"
#include "../ast-type-nodes/ast-type-colon-node.h"

class ASTClassPropertyDefinitionWithTypeNode : public ASTNode {
private:
    std::shared_ptr<ASTClassPropertyDefinitionNode> _classPropertyDefinition;
    std::shared_ptr<ASTTypeColonNode> _colon;
    std::shared_ptr<ASTTypeNode> _type;
public:
    ASTClassPropertyDefinitionWithTypeNode(std::shared_ptr<ASTClassPropertyDefinitionNode> classPropertyDefinition, std::shared_ptr<ASTTypeColonNode> colon, std::shared_ptr<ASTTypeNode> type);
    std::shared_ptr<ASTClassPropertyDefinitionNode> getClassPropertyDefinition();
    std::shared_ptr<ASTTypeColonNode> getColon();
    std::shared_ptr<ASTTypeNode> getType();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE_H
