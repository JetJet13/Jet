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
    std::shared_ptr<ASTIdentifierExpressionNode> _identifier;
    std::shared_ptr<ASTTypeColonNode> _colon;
    std::shared_ptr<ASTTypeNode> _type;
    std::shared_ptr<ParameterListItemTypeSignature> _typeSignature = std::make_shared<ParameterListItemTypeSignature>("_", std::make_shared<UnknownTypeSignature>());
    unsigned long _captureCount = 0;
public:
    ASTFunctionParameterNode(std::shared_ptr<ASTIdentifierExpressionNode> identifier, std::shared_ptr<ASTTypeColonNode> colon, std::shared_ptr<ASTTypeNode> type);
    std::shared_ptr<ASTIdentifierExpressionNode> getIdentifier();
    std::shared_ptr<ASTTypeNode> getType();
    void markAsCaptured();
    unsigned long getCaptureCount();
    bool isCaptured();
    void setTypeSignature(std::shared_ptr<ParameterListItemTypeSignature> typeSignature);
    std::shared_ptr<ParameterListItemTypeSignature> getParameterTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_PARAMETER_NODE_H
