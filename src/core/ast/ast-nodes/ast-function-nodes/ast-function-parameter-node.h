//
// Created by Johny Georges on 2024-03-20.
//

#ifndef JETLANG_AST_FUNCTION_PARAMETER_NODE_H
#define JETLANG_AST_FUNCTION_PARAMETER_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../../../type-signature/parameter-list-type-signature/parameter-list-item-type-signature/parameter-list-item-type-signature.h"
#include "../ast-base-nodes/ast-colon-base-node.h"
#include "../ast-type-nodes/ast-type-colon-node.h"

class ASTFunctionParameterNode : public ASTNode {
private:
    ASTIdentifierExpressionNode* _identifier;
    ASTTypeColonNode* _colon;
    ASTTypeNode* _type;
    ParameterListItemTypeSignature* _typeSignature = new ParameterListItemTypeSignature("_", new UnknownTypeSignature());
    bool _isReferenced = false;
    bool _isCaptured = false;
public:
    ASTFunctionParameterNode(ASTIdentifierExpressionNode* identifier, ASTTypeColonNode* colon, ASTTypeNode* type);
    ASTIdentifierExpressionNode* getIdentifier();
    ASTTypeNode* getType();
    void markAsReferenced();
    void markAsCaptured();
    bool isReferenced();
    bool isCaptured();
    void setTypeSignature(ParameterListItemTypeSignature* typeSignature);
    ParameterListItemTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_PARAMETER_NODE_H
