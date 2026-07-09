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
#include "ast-module-nodes/ast-module-access-target-node.h"
#include "ast-module-nodes/ast-module-access-source-node.h"
#include "ast-interface-nodes/ast-interface-name-node.h"
#include "ast-interface-nodes/ast-interface-property-name-node.h"
#include "ast-type-nodes/ast-struct-type-nodes/ast-struct-type-key-node.h"
#include "ast-interface-nodes/ast-implements-interface-name-node.h"
#include "ast-interface-nodes/ast-implements-interface-name-last-node.h"
#include "ast-type-nodes/ast-type-name-node.h"
#include "../../pre-processor/syntax-analyzer/utils/syntax-analyzer-mode-utils.h"

ASTIdentifierNode::ASTIdentifierNode(std::shared_ptr<Lexeme> lexeme) {
    _lexeme = lexeme;
}

std::shared_ptr<Lexeme> ASTIdentifierNode::getLexeme() {
    return _lexeme;
}

std::string ASTIdentifierNode::getValue(TokenTable* tokenTable) {
    return tokenTable->getIdentifier(
            _lexeme->getToken()->getValueId().value()
    );
}

std::shared_ptr<ASTNode> ASTIdentifierNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({ AST_PERIOD_NODE, AST_MODULE_ACCESS_NODE })) {
        return shared_from_this();
    }

    if (SyntaxAnalyzerModeUtils::isTypeMode(mode) && nextNode && nextNode.value()->isOneOf({ AST_COLON_COLON_BASE_NODE })) {
        return std::make_shared<ASTModuleTypeSourceNode>(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->is(AST_MODULE_ACCESS_TYPE_NODE)) {
        return std::make_shared<ASTModuleTypeTargetNode>(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->is(AST_CLASS_ACCESS_NODE)) {
        if (nextNode && nextNode.value()->is(AST_GROUP_START_NODE)) {
            return std::make_shared<ASTClassMethodCallNode>(this->getLexeme(), this->getId());
        }
        return std::make_shared<ASTClassPropertyNameNode>(this->getLexeme(), this->getId());
    }

    if ((mode == SA_STRUCT_TYPE_MODE || mode == SA_TUPLE_TYPE_MODE) &&
         nextNode && nextNode.value()->isOneOf({ AST_COLON_BASE_NODE })) {
        return std::make_shared<ASTStructTypeKeyNode>(this->getLexeme(), this->getId());
    }

    if (mode == SA_LAMBDA_TYPE_PARAMETER_LIST_MODE) {
        return ASTTypeNodeFactory::createCustomTypeNode(this->getLexeme(), this->getId());
    }

    if (mode == SA_TUPLE_TYPE_MODE) {
        return ASTTypeNodeFactory::createCustomTypeNode(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_TYPE_COLON_NODE, AST_INTERFACE_COLON_NODE, AST_TYPE_ASSIGNMENT_OPERATOR_NODE, AST_STRUCT_TYPE_COLON_NODE, AST_ARRAY_TYPE_START_NODE })) {
        return ASTTypeNodeFactory::createCustomTypeNode(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_STATIC_NODE, AST_PUBLIC_NODE, AST_PROTECTED_NODE, AST_PRIVATE_NODE }) &&
        nextNode && nextNode.value()->is(AST_GROUP_START_NODE)) {
        return std::make_shared<ASTClassMethodNameNode>(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_CLASS_NODE })) {
        return std::make_shared<ASTClassNameNode>(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_NEW_NODE }) &&
        (!nextNode || !nextNode.value()->isOneOf({ AST_COLON_COLON_BASE_NODE }))) {
        return std::make_shared<ASTClassNameNode>(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_FUNCTION_NODE, AST_PROCEDURE_NODE })) {
        return std::make_shared<ASTFunctionNameNode>(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_INTERFACE_NODE })) {
        return std::make_shared<ASTInterfaceNameNode>(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_ENUM_NODE })) {
        return std::make_shared<ASTEnumNameNode>(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_FUNCTION_PARAMETER_LIST_NODE })) {
        return ASTTypeNodeFactory::createCustomTypeNode(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_TYPE_COLON_NODE }) && nextNode && nextNode.value()->isOneOf({AST_ASSIGNMENT_OPERATOR_NODE, AST_TERMINATOR_NODE })) {
        return ASTTypeNodeFactory::createCustomTypeNode(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_MODULE_NODE })) {
        return std::make_shared<ASTModuleNameNode>(std::dynamic_pointer_cast<ASTIdentifierNode>(shared_from_this()));
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_IMPORT_NODE, AST_USE_NODE })) {
        return std::make_shared<ASTImportModuleNameNode>(std::dynamic_pointer_cast<ASTIdentifierNode>(shared_from_this()));
    }


    if (mode == SA_MODULE_LIST_MODE) {
        if (prevNode && prevNode.value()->is(AST_MODULE_SPREAD_NODE) ||
            nextNode && nextNode.value()->is(AST_AS_NODE)) {
            return std::make_shared<ASTModuleNameNode>(std::dynamic_pointer_cast<ASTIdentifierNode>(shared_from_this()));
        }
        if (prevNode && prevNode.value()->is(AST_AS_NODE)) {
            return std::make_shared<ASTModuleAliasNameNode>(std::dynamic_pointer_cast<ASTIdentifierNode>(shared_from_this()));
        }
        return std::make_shared<ASTModuleListNormalItemNode>(std::make_shared<ASTModuleNameNode>(std::dynamic_pointer_cast<ASTIdentifierNode>(shared_from_this())));
    }

    if (mode == SA_IMPORT_MODULE_LIST_MODE) {
        if (prevNode && prevNode.value()->is(AST_MODULE_SPREAD_NODE) ||
            nextNode && nextNode.value()->isOneOf({ AST_AS_NODE, AST_MODULE_ACCESS_NODE })) {
            return std::make_shared<ASTImportModuleNameNode>(std::dynamic_pointer_cast<ASTIdentifierNode>(shared_from_this()));
        }
        if (prevNode && prevNode.value()->is(AST_AS_NODE)) {
            return std::make_shared<ASTImportModuleAliasNameNode>(std::dynamic_pointer_cast<ASTIdentifierNode>(shared_from_this()));
        }

        return std::make_shared<ASTImportModuleListNormalItemNode>(std::make_shared<ASTImportModuleNameNode>(std::dynamic_pointer_cast<ASTIdentifierNode>(shared_from_this())));
    }

    if (mode == SA_ENUM_KEY_VALUE_LIST_MODE) {
        return std::make_shared<ASTEnumKeyNode>(this->getLexeme(), this->getId());
    }

    if (mode == SA_INTERFACE_MODE) {
        return std::make_shared<ASTInterfacePropertyNameNode>(this->getLexeme(), this->getId());
    }

    if (mode == SA_IMPLEMENTS_INTERFACE_MODE) {
        if (nextNode && nextNode.value()->isOneOf({ AST_BLOCK_START_NODE })) {
            return std::make_shared<ASTImplementsInterfaceNameLastNode>(this->getLexeme(), this->getId());
        }
        return std::make_shared<ASTImplementsInterfaceNameNode>(this->getLexeme(), this->getId());
    }

    if (mode == SA_TYPE_PARAMETER_LIST_MODE) {
        return ASTTypeNodeFactory::createCustomTypeNode(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_CATCH_NODE })) {
        return std::make_shared<ASTCatchErrorVariableNode>(this->getLexeme(), this->getId());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_TYPE_KEYWORD_NODE })) {
        return std::make_shared<ASTTypeNameNode>(this->getLexeme(), this->getId());
    }

    return shared_from_this();
}

ASTNodeType ASTIdentifierNode::getNodeType() {
    return AST_IDENTIFIER_NODE;
}

std::string ASTIdentifierNode::toString() {
    return "IDENTIFIER";
}

std::shared_ptr<Position> ASTIdentifierNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

std::shared_ptr<Position> ASTIdentifierNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

bool ASTIdentifierNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTIdentifierNode>(other);
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTIdentifierNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString(), "|", "id:", _id);
}

std::string ASTIdentifierNode::toSourceCode() {
    return this->getId();
}