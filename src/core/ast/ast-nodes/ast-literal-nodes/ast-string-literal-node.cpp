//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-string-literal-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"

std::shared_ptr<ASTNode> ASTStringLiteralNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {

    if (prevNode && prevNode.value()->is(AST_FROM_NODE)) {
        return std::make_shared<ASTImportPathNode>(std::dynamic_pointer_cast<ASTStringLiteralNode>(shared_from_this()));
    }

    return shared_from_this();
}

ASTNodeType ASTStringLiteralNode::getNodeType() {
    return AST_STRING_LITERAL_NODE;
}

std::string ASTStringLiteralNode::toString() {
    return "STRING_LITERAL - " + _lexeme->toString();
}

void ASTStringLiteralNode::setValue(std::shared_ptr<TokenTable> tokenTable) {
    _value = tokenTable->getString(_lexeme->getToken()->getValueId().value());
}


std::string ASTStringLiteralNode::getValue() {
    return _value;
}

std::string ASTStringLiteralNode::toSourceCode() {
    return "\"" + _lexeme->getToken()->getRawValue() + "\"";
}