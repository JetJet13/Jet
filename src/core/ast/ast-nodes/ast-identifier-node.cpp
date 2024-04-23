//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-identifier-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "ast-function-nodes/ast-function-name-node.h"
#include "ast-enum-nodes/ast-enum-name-node.h"
#include "ast-enum-nodes/ast-enum-key-node.h"
#include "ast-function-nodes/ast-function-call-node.h"
#include "ast-object-nodes/ast-object-access-source-node.h"
#include "ast-control-flow-nodes/try-catch-finally/ast-catch-error-variable-node.h"
#include "ast-type-nodes/ast-type-node-factory.h"
#include "ast-module-nodes/ast-module-name-node.h"
#include "ast-module-nodes/ast-module-list-items/ast-module-list-normal-item-node.h"
#include "ast-module-nodes/ast-module-alias-name-node.h"
#include "ast-import-nodes/ast-import-module-name-node.h"
#include "ast-import-nodes/ast-import-list-items/ast-import-module-list-normal-item-node.h"
#include "ast-import-nodes/ast-import-module-alias-name-node.h"
#include "ast-class-nodes/ast-class-name-node.h"
#include "ast-class-nodes/ast-class-property-name-node.h"
#include "ast-class-nodes/ast-class-method-name-node.h"
#include "ast-class-nodes/ast-class-method-call-node.h"

ASTIdentifierNode::ASTIdentifierNode(Lexeme *lexeme) {
    _identifier = lexeme;
}

Lexeme* ASTIdentifierNode::getIdentifier() {
    return _identifier;
}

ASTNode * ASTIdentifierNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode,
                                                  SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({ AST_FUNCTION_NODE, AST_PROCEDURE_NODE })) {
        return new ASTFunctionNameNode(this->getIdentifier());
    }

    if (nextNode && nextNode.value()->isOneOf({ AST_GROUP_START_NODE, AST_FUNCTION_ARGUMENT_LIST_START_NODE })) {
        return new ASTFunctionCallNode(this->getIdentifier());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_ENUM_NODE })) {
        return new ASTEnumNameNode(this->getIdentifier());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_CLASS_NODE })) {
        return new ASTClassNameNode(this->getIdentifier());
    }

    if (mode == SA_CLASS_BLOCK_MODE) {
        if (nextNode && nextNode.value()->is(AST_GROUP_START_NODE) &&
            prevNode && prevNode.value()->isOneOf({ AST_STATIC_NODE, AST_PUBLIC_NODE, AST_PROTECTED_NODE, AST_PRIVATE_NODE })) {
            return new ASTClassMethodNameNode(this->getIdentifier());
        }

        if (prevNode && prevNode.value()->isOneOf({ AST_CONST_NODE, AST_STATIC_NODE, AST_PUBLIC_NODE, AST_PROTECTED_NODE, AST_PRIVATE_NODE })) {
            return new ASTClassPropertyNameNode(this->getIdentifier());
        }
    }

    if (prevNode && prevNode.value()->is(AST_THIS_ACCESS_NODE)) {
        if (nextNode && nextNode.value()->is(AST_GROUP_START_NODE)) {
            return new ASTClassMethodCallNode(this->getIdentifier());
        }
        return new ASTClassPropertyNameNode(this->getIdentifier());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_COLON_NODE }) && mode == SA_FUNCTION_PARAMETER_LIST_MODE) {
        return ASTTypeNodeFactory::createCustomTypeNode(this);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_FUNCTION_PARAMETER_LIST_NODE })) {
        return ASTTypeNodeFactory::createCustomTypeNode(this);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_COLON_NODE }) && nextNode && nextNode.value()->isOneOf({ AST_ASSIGNMENT_OPERATOR_NODE })) {
        return ASTTypeNodeFactory::createCustomTypeNode(this);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_MODULE_NODE })) {
        return new ASTModuleNameNode(this);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_IMPORT_NODE, AST_USE_NODE })) {
        return new ASTImportModuleNameNode(this);
    }


    if (mode == SA_MODULE_LIST_MODE) {
        if (prevNode && prevNode.value()->is(AST_MODULE_SPREAD_NODE) ||
            nextNode && nextNode.value()->is(AST_AS_NODE)) {
            return new ASTModuleNameNode(this);
        }
        if (prevNode && prevNode.value()->is(AST_AS_NODE)) {
            return new ASTModuleAliasNameNode(this);
        }
        return new ASTModuleListNormalItemNode(new ASTModuleNameNode(this));
    }

    if (mode == SA_IMPORT_MODULE_LIST_MODE) {
        if (prevNode && prevNode.value()->is(AST_MODULE_SPREAD_NODE) ||
            nextNode && nextNode.value()->isOneOf({ AST_AS_NODE, AST_MODULE_ACCESS_NODE })) {
            return new ASTImportModuleNameNode(this);
        }
        if (prevNode && prevNode.value()->is(AST_AS_NODE)) {
            return new ASTImportModuleAliasNameNode(this);
        }

        return new ASTImportModuleListNormalItemNode(new ASTImportModuleNameNode(this));
    }

    if (mode == SA_ENUM_KEY_VALUE_LIST_MODE) {
        return new ASTEnumKeyNode(this->getIdentifier());
    }

    if (mode == SA_TYPE_PARAMETER_LIST_MODE) {
        return ASTTypeNodeFactory::createCustomTypeNode(this);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_CATCH_NODE })) {
        return new ASTCatchErrorVariableNode(this);
    }

    return this;
}

ASTNodeType ASTIdentifierNode::getNodeType() {
    return AST_IDENTIFIER_NODE;
}

std::string ASTIdentifierNode::toString() {
    return "IDENTIFIER";
}

bool ASTIdentifierNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTIdentifierNode*)other;
    return this->getIdentifier()->hasSameSymbolTypeAs(otherNode->getIdentifier());
}

void ASTIdentifierNode::print() {
    Logger::log(this->toString(), "-", _identifier->toString());
}