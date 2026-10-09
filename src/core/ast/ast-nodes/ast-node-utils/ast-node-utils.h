// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-02-10.
//

#ifndef JETLANG_AST_NODE_UTILS_H
#define JETLANG_AST_NODE_UTILS_H

#include "../ast-node.h"

namespace ASTNodeUtils {
    static bool isDeclarableNode(std::shared_ptr<ASTNode> node) {
        switch (node->getNodeType()) {
            case AST_FUNCTION_DECLARATION_NODE:
            case AST_PROCEDURE_DECLARATION_NODE:
            case AST_ENUM_DECLARATION_NODE:
            case AST_CLASS_DECLARATION_NODE:
            case AST_INTERFACE_TYPE_DECLARATION_NODE:
            case AST_CUSTOM_TYPE_DECLARATION_NODE:
                return true;
            default:
                return false;
        }
    }

    static bool isTypeDeclarationNode(std::shared_ptr<ASTNode> node) {
        switch (node->getNodeType()) {
            case AST_INTERFACE_TYPE_DECLARATION_NODE:
            case AST_CUSTOM_TYPE_DECLARATION_NODE:
                return true;
            default:
                return false;
        }
    }

    static bool isDeclarationNode(std::shared_ptr<ASTNode> node) {
        switch (node->getNodeType()) {
            case AST_VARIABLE_DECLARATION_NODE:
            case AST_FUNCTION_DECLARATION_NODE:
            case AST_PROCEDURE_DECLARATION_NODE:
            case AST_ENUM_DECLARATION_NODE:
            case AST_INTERFACE_TYPE_DECLARATION_NODE:
            case AST_CUSTOM_TYPE_DECLARATION_NODE:
            case AST_MODULE_DECLARATION_NODE:
            case AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE:
            case AST_USE_SINGLE_MODULE_DECLARATION_NODE:
            case AST_IMPORT_MANY_MODULE_DECLARATION_NODE:
            case AST_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE:
            case AST_USE_MANY_MODULE_DECLARATION_NODE:
            case AST_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE:
            case AST_CLASS_DECLARATION_NODE:
            case AST_CLASS_PROPERTY_DECLARATION_NODE:
            case AST_CLASS_CONSTRUCTOR_DECLARATION_NODE:
            case AST_CLASS_METHOD_DECLARATION_NODE:
                return true;
            default:
                return false;
        }
    }

    static bool isStatementNode(std::shared_ptr<ASTNode> node) {
        if (ASTNodeUtils::isDeclarationNode(node)) {
            return true;
        }

        switch (node->getNodeType()) {
            case AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE:
            case AST_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
            case AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE:
            case AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
            case AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE:
            case AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
            case AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE:
            case AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
            case AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE:
            case AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
            case AST_IF_STATEMENT_NODE:
            case AST_WHILE_STATEMENT_NODE:
            case AST_FOR_IN_STATEMENT_NODE:
            case AST_EXPRESSION_STATEMENT_NODE:
            case AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE:
            case AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE:
            case AST_BLOCK_NODE:
            case AST_BREAK_NODE:
            case AST_SKIP_NODE:
            case AST_TRY_STATEMENT_NODE:
                return true;
            default:
                return false;
        }
    }

    static bool isStatementOrReturnExpressionNode(std::shared_ptr<ASTNode> node) {
        if (node->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
            return true;
        }
        return ASTNodeUtils::isStatementNode(node);
    }

    static bool isExpressionNode(std::shared_ptr<ASTNode> node) {
        switch (node->getNodeType()) {
            case AST_IDENTIFIER_EXPRESSION_NODE:
            case AST_LITERAL_EXPRESSION_NODE:
            case AST_BINARY_ARITHMETIC_EXPRESSION_NODE:
            case AST_LOGICAL_EXPRESSION_NODE:
            case AST_UNARY_EXPRESSION_NODE:
            case AST_OBJECT_ACCESS_EXPRESSION_NODE:
            case AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE:
            case AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE:
            case AST_MODULE_ACCESS_EXPRESSION_NODE:
            case AST_FUNCTION_INVOCATION_EXPRESSION_NODE:
            case AST_CURRY_EXPRESSION_NODE:
            case AST_FUNCTION_RETURN_EXPRESSION_NODE:
            case AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE:
            case AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE:
            case AST_THIS_EXPRESSION_NODE:
            case AST_ARRAY_ACCESS_EXPRESSION_NODE:
            case AST_ARRAY_EXPRESSION_NODE:
            case AST_STRUCT_EXPRESSION_NODE:
            case AST_TUPLE_ACCESS_EXPRESSION_NODE:
            case AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE:
            case AST_TUPLE_EXPRESSION_NODE:
            case AST_LAMBDA_EXPRESSION_NODE:
            case AST_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE:
            case AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE:
            case AST_CONCAT_EXPRESSION_NODE:
                return true;
            default:
                return false;
        }
    }
}

#endif //JETLANG_AST_NODE_UTILS_H
