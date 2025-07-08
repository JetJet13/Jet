//
// Created by Johny Georges on 2025-07-07.
//

#ifndef JETLANG_AST_CUSTOM_TYPE_DECLARATION_NODE_H
#define JETLANG_AST_CUSTOM_TYPE_DECLARATION_NODE_H

#include "./ast-type-declaration-node.h"
#include "../ast-interface-nodes/ast-interface-definition-node.h"
#include "../ast-interface-nodes/ast-interface-property-list-node.h"
#include "../../../type-signature/interface-type-signature/interface-type-signature.h"
#include "../ast-export-node.h"
#include "../ast-type-nodes/ast-type-keyword-node.h"
#include "../ast-type-nodes/ast-type-name-node.h"
#include "../ast-type-nodes/ast-type-assignment-operator-node.h"

class ASTCustomTypeDeclarationNode : public ASTTypeDeclarationNode {
private:
    ASTTypeKeywordNode* _typeKeyword;
    ASTTypeNameNode* _typeName;
    ASTTypeAssignmentOperatorNode* _assignmentOperator;
    ASTTypeNode* _type;
    std::optional<ASTExportNode*> _exportKeyword = {};
    TypeSignature* _typeSignature = new UnknownTypeSignature();
public:
    explicit ASTCustomTypeDeclarationNode(ASTTypeKeywordNode* typeKeyword, ASTTypeNameNode* typeName, ASTTypeAssignmentOperatorNode* assignmentOperator, ASTTypeNode* type, std::optional<ASTExportNode*> exportKeyword = {});
    ASTTypeNode* getType();
    ASTTypeNameNode* getName();
    bool isExportable() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CUSTOM_TYPE_DECLARATION_NODE_H
