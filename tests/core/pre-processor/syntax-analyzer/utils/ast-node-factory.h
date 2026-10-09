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
// Created by Johny Georges on 2024-03-01.
//

#ifndef JETLANG_AST_NODE_FACTORY_H
#define JETLANG_AST_NODE_FACTORY_H

#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../../../src/core/symbol/symbol-factory.h"
#include "../../../../../src/core/ast/ast-nodes/ast-variable-nodes/ast-variable-init-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-share-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-logical-operators/ast-logical-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-binary-arithmetic-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-array-nodes/ast-array-access-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-variable-nodes/ast-variable-assignment-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-key-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-tuple-nodes/ast-tuple-access-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-object-nodes/ast-object-access-source-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-object-nodes/ast-object-access-target-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-for-in-variable-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-for-in-source-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-skip-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-break-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-alias-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-list-items/ast-module-list-alias-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-list-items/ast-module-list-spread-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-list-items/ast-module-list-normal-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-list-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-path-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-module-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-wildcard-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-module-list-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-module-alias-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-alias-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-normal-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-spread-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-module-list-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-group-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-wildcard-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-property-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-access-modifier-nodes/ast-public-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-access-modifier-nodes/ast-protected-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-access-modifier-nodes/ast-private-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-method-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-property-access-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-this-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-property-assignment-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-method-call-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-constructor-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-catch-error-variable-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-start-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-end-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-return-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-block-nodes/ast-block-start-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-block-nodes/ast-block-end-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-struct-nodes/ast-struct-start-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-struct-nodes/ast-struct-end-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-period-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-struct-nodes/ast-struct-key-value-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-block-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-block-nodes/ast-block-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-list-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-argument-list-start-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-argument-list-end-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-argument-list-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-control-flow-block-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-if-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-else-if-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-try-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-catch-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-finally-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-for-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-for-in-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-while-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-list-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-package-node/ast-use-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-from-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-static-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-const-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-new-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-block-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-lambda-nodes/ast-lambda-fat-arrow-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-type-nodes/ast-type-colon-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-definition-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-export-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-procedure-nodes/ast-procedure-definition-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-access-source-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-access-target-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-module-access-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-dref-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-share-nodes/ast-share-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-share-nodes/ast-shared-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-callable-identifier-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-dref-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-concat-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-interface-nodes/ast-interface-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-interface-nodes/ast-interface-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-interface-nodes/ast-interface-start-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-interface-nodes/ast-interface-end-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-interface-nodes/ast-interface-definition-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-interface-nodes/ast-interface-property-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-interface-nodes/ast-interface-property-list-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-interface-nodes/ast-interface-property-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-interface-nodes/ast-implements-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-interface-nodes/ast-implements-interface-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-interface-nodes/ast-implements-interface-list-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-type-nodes/ast-type-keyword-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-type-nodes/ast-type-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-type-nodes/ast-type-assignment-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-type-declaration-nodes/ast-custom-type-declaration-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-statement-nodes/ast-expression-statement-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-binary-comparator-operator-node.h"

namespace ASTNodeFactory {
    std::shared_ptr<Lexeme> createLexeme(std::shared_ptr<Symbol> symbol, std::optional<std::string> rawValue = {}) {
        return std::make_shared<Lexeme>(std::make_shared<Token>(symbol, rawValue.value_or(symbol->toString())));
    }
    static std::shared_ptr<ASTShareNode> shareKeyword = std::make_shared<ASTShareNode>(createLexeme(SymbolFactory::createShareSymbol()));
    static std::shared_ptr<ASTSharedNode> sharedTypeKeyword = std::make_shared<ASTSharedNode>(createLexeme(SymbolFactory::createShareSymbol()));
    static std::shared_ptr<ASTDrefNode> drefKeyword = std::make_shared<ASTDrefNode>(createLexeme(SymbolFactory::createDrefSymbol()));
    static std::shared_ptr<ASTExportNode> exportKeyword = std::make_shared<ASTExportNode>(createLexeme(SymbolFactory::createExportSymbol()));
    static std::shared_ptr<ASTBlockStartNode> blockStart = std::make_shared<ASTBlockStartNode>(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static std::shared_ptr<ASTBlockEndNode> blockEnd = std::make_shared<ASTBlockEndNode>(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static std::shared_ptr<ASTStructStartNode> structStart = std::make_shared<ASTStructStartNode>(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static std::shared_ptr<ASTStructEndNode> structEnd = std::make_shared<ASTStructEndNode>(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static std::shared_ptr<ASTLeftBracketNode> leftBracket = std::make_shared<ASTLeftBracketNode>(createLexeme(SymbolFactory::createLeftBracketSymbol()));
    static std::shared_ptr<ASTRightBracketNode> rightBracket = std::make_shared<ASTRightBracketNode>(createLexeme(SymbolFactory::createRightBracketSymbol()));
    static std::shared_ptr<ASTFunctionParameterListStartNode> functionParameterListStart =  std::make_shared<ASTFunctionParameterListStartNode>(createLexeme(SymbolFactory::createLeftParenSymbol()));
    static std::shared_ptr<ASTFunctionParameterListEndNode> functionParameterListEnd =  std::make_shared<ASTFunctionParameterListEndNode>(createLexeme(SymbolFactory::createRightParenSymbol()));
    static std::shared_ptr<ASTFunctionArgumentListStartNode> functionArgumentListStart =  std::make_shared<ASTFunctionArgumentListStartNode>(createLexeme(SymbolFactory::createLeftParenSymbol()));
    static std::shared_ptr<ASTFunctionArgumentListEndNode> functionArgumentListEnd =  std::make_shared<ASTFunctionArgumentListEndNode>(createLexeme(SymbolFactory::createRightParenSymbol()));
    static std::shared_ptr<ASTEnumKeyValueListStartNode> enumKeyValueListStart =  std::make_shared<ASTEnumKeyValueListStartNode>(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static std::shared_ptr<ASTEnumKeyValueListEndNode> enumKeyValueListEnd =  std::make_shared<ASTEnumKeyValueListEndNode>(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static std::shared_ptr<ASTTupleListStartNode> tupleListStart =  std::make_shared<ASTTupleListStartNode>(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static std::shared_ptr<ASTTupleListEndNode> tupleListEnd =  std::make_shared<ASTTupleListEndNode>(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static std::shared_ptr<ASTTypeParameterListStartNode> typeParameterListStart = std::make_shared<ASTTypeParameterListStartNode>(createLexeme(SymbolFactory::createLessThanSymbol()));
    static std::shared_ptr<ASTTypeParameterListEndNode> typeParameterListEnd = std::make_shared<ASTTypeParameterListEndNode>(createLexeme(SymbolFactory::createGreaterThanSymbol()));
    static std::shared_ptr<ASTModuleListStartNode> moduleListStart = std::make_shared<ASTModuleListStartNode>(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static std::shared_ptr<ASTModuleListEndNode> moduleListEnd = std::make_shared<ASTModuleListEndNode>(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static std::shared_ptr<ASTImportModuleListStartNode> importModuleListStart = std::make_shared<ASTImportModuleListStartNode>(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static std::shared_ptr<ASTImportModuleListEndNode> importModuleListEnd = std::make_shared<ASTImportModuleListEndNode>(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static std::shared_ptr<ASTPeriodNode> period = std::make_shared<ASTPeriodNode>(createLexeme(SymbolFactory::createPeriodSymbol()));
    static std::shared_ptr<ASTLambdaFatArrowNode> lambdaFatArrow = std::make_shared<ASTLambdaFatArrowNode>(createLexeme(SymbolFactory::createFatArrowSymbol()));
    static std::shared_ptr<ASTLambdaArrowNode> lambdaArrow = std::make_shared<ASTLambdaArrowNode>(createLexeme(SymbolFactory::createFatArrowSymbol()));
    static std::shared_ptr<ASTVoidNode> voidNode = std::make_shared<ASTVoidNode>(createLexeme(SymbolFactory::createVoidSymbol()));
    static std::shared_ptr<ASTLambdaTypeParameterListStartNode> lambdaTypeParameterListStart = std::make_shared<ASTLambdaTypeParameterListStartNode>(createLexeme(SymbolFactory::createLeftParenSymbol()));
    static std::shared_ptr<ASTLambdaTypeParameterListEndNode> lambdaTypeParameterListEnd = std::make_shared<ASTLambdaTypeParameterListEndNode>(createLexeme(SymbolFactory::createRightParenSymbol()));
    static std::shared_ptr<ASTModuleAccessNode> moduleAccess = std::make_shared<ASTModuleAccessNode>(createLexeme(SymbolFactory::createColonColonSymbol()));
    static std::shared_ptr<ASTModuleSpreadNode> moduleSpread = std::make_shared<ASTModuleSpreadNode>(
            createLexeme(SymbolFactory::createDotDotDotSymbol())
    );
    static std::shared_ptr<ASTAssignmentOperatorNode> assignment = std::make_shared<ASTAssignmentOperatorNode>(
            createLexeme(SymbolFactory::createEqualSymbol())
    );
    static std::shared_ptr<ASTIfNode> ifKeyword = std::make_shared<ASTIfNode>(createLexeme(SymbolFactory::createIfSymbol()));
    static std::shared_ptr<ASTElseNode> elseKeyword = std::make_shared<ASTElseNode>(createLexeme(SymbolFactory::createElseSymbol()));
    static std::shared_ptr<ASTElseIfNode> elseIfKeyword = std::make_shared<ASTElseIfNode>(ASTNodeFactory::elseKeyword, ASTNodeFactory::ifKeyword);
    static std::shared_ptr<ASTTryNode> tryKeyword = std::make_shared<ASTTryNode>(createLexeme(SymbolFactory::createTrySymbol()));
    static std::shared_ptr<ASTCatchNode> catchKeyword = std::make_shared<ASTCatchNode>(createLexeme(SymbolFactory::createCatchSymbol()));
    static std::shared_ptr<ASTFinallyNode> finallyKeyword = std::make_shared<ASTFinallyNode>(createLexeme(SymbolFactory::createFinallySymbol()));
    static std::shared_ptr<ASTForNode> forKeyword = std::make_shared<ASTForNode>(createLexeme(SymbolFactory::createForSymbol()));
    static std::shared_ptr<ASTForInNode> forInKeyword = std::make_shared<ASTForInNode>(createLexeme(SymbolFactory::createInSymbol()));
    static std::shared_ptr<ASTWhileNode> whileKeyword = std::make_shared<ASTWhileNode>(createLexeme(SymbolFactory::createWhileSymbol()));
    static std::shared_ptr<ASTIdentifierNode> id = std::make_shared<ASTIdentifierNode>(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static std::shared_ptr<ASTIdentifierExpressionNode> idExpression = std::make_shared<ASTIdentifierExpressionNode>(
        std::make_shared<ASTIdentifierNode>(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );
    static std::shared_ptr<ASTCallableIdentifierExpressionNode> callableIdExpression = std::make_shared<ASTCallableIdentifierExpressionNode>(
            std::make_shared<ASTIdentifierNode>(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );
    static std::shared_ptr<ASTImportSpreadNode> importSpread = std::make_shared<ASTImportSpreadNode>(
            createLexeme(SymbolFactory::createDotDotDotSymbol())
    );
    static std::shared_ptr<ASTModuleAccessSourceNode> moduleAccessSource = std::make_shared<ASTModuleAccessSourceNode>(ASTNodeFactory::idExpression);
    static std::shared_ptr<ASTModuleAccessTargetNode> moduleAccessTarget = std::make_shared<ASTModuleAccessTargetNode>(ASTNodeFactory::idExpression);
    static std::shared_ptr<ASTModuleAccessTargetNode> callableModuleAccessTarget = std::make_shared<ASTModuleAccessTargetNode>(ASTNodeFactory::callableIdExpression);
    static std::shared_ptr<ASTModuleAccessExpressionNode> moduleAccessExpression = std::make_shared<ASTModuleAccessExpressionNode>(
            ASTNodeFactory::moduleAccessSource,
            ASTNodeFactory::moduleAccess,
            ASTNodeFactory::moduleAccessTarget
    );
    static std::shared_ptr<ASTModuleAccessExpressionNode> callableModuleAccessExpression = std::make_shared<ASTModuleAccessExpressionNode>(
            ASTNodeFactory::moduleAccessSource,
            ASTNodeFactory::moduleAccess,
            ASTNodeFactory::callableModuleAccessTarget
    );
    static std::shared_ptr<ASTColonBaseNode> colon = std::make_shared<ASTColonBaseNode>(createLexeme(SymbolFactory::createColonSymbol()));
    static std::shared_ptr<ASTStructColonNode> structColon = std::make_shared<ASTStructColonNode>(createLexeme(SymbolFactory::createColonSymbol()));
    static std::shared_ptr<ASTTypeColonNode> typeColon = std::make_shared<ASTTypeColonNode>(createLexeme(SymbolFactory::createColonSymbol()));
    static std::shared_ptr<ASTVariableInitNode> letInit = std::make_shared<ASTVariableInitNode>(
                std::make_shared<ASTVariableTypeNode>(createLexeme(SymbolFactory::createLetSymbol())),
                std::make_shared<ASTIdentifierNode>(createLexeme(SymbolFactory::createIdentifierSymbol())),
                ASTNodeFactory::assignment
    );
    static std::shared_ptr<ASTVariableInitNode> constInit = std::make_shared<ASTVariableInitNode>(
            std::make_shared<ASTVariableTypeNode>(createLexeme(SymbolFactory::createConstSymbol())),
            std::make_shared<ASTIdentifierNode>(createLexeme(SymbolFactory::createIdentifierSymbol())),
            ASTNodeFactory::assignment
    );
    static std::shared_ptr<ASTVariableInitNode> createConstInitWithType(std::shared_ptr<ASTTypeNode> type) {
        return std::make_shared<ASTVariableInitNode>(
                std::make_shared<ASTVariableTypeNode>(createLexeme(SymbolFactory::createConstSymbol())),
                std::make_shared<ASTIdentifierNode>(createLexeme(SymbolFactory::createIdentifierSymbol())),
                ASTNodeFactory::assignment,
                ASTNodeFactory::typeColon,
                type
        );
    }
    static std::shared_ptr<ASTIntLiteralNode> intLiteral = std::make_shared<ASTIntLiteralNode>(createLexeme(SymbolFactory::createIntSymbol()));
    static std::shared_ptr<ASTFloatLiteralNode> floatLiteral = std::make_shared<ASTFloatLiteralNode>(createLexeme(SymbolFactory::createFloatSymbol()));
    static std::shared_ptr<ASTStringLiteralNode> stringLiteral = std::make_shared<ASTStringLiteralNode>(createLexeme(SymbolFactory::createStringSymbol()));
    static std::shared_ptr<ASTCharLiteralNode> charLiteral = std::make_shared<ASTCharLiteralNode>(createLexeme(SymbolFactory::createCharSymbol()));
    static std::shared_ptr<ASTBooleanLiteralNode> trueLiteral = std::make_shared<ASTBooleanLiteralNode>(createLexeme(SymbolFactory::createTrueSymbol()));
    static std::shared_ptr<ASTBooleanLiteralNode> falseLiteral = std::make_shared<ASTBooleanLiteralNode>(createLexeme(SymbolFactory::createFalseSymbol()));

    static std::shared_ptr<ASTLiteralExpressionNode> intExpression = std::make_shared<ASTLiteralExpressionNode>(
            std::make_shared<ASTIntLiteralNode>(createLexeme(SymbolFactory::createIntSymbol()))
    );
    static std::shared_ptr<ASTLiteralExpressionNode> floatExpression = std::make_shared<ASTLiteralExpressionNode>(
            std::make_shared<ASTFloatLiteralNode>(createLexeme(SymbolFactory::createFloatSymbol()))
    );
    static std::shared_ptr<ASTLiteralExpressionNode> stringExpression = std::make_shared<ASTLiteralExpressionNode>(
            std::make_shared<ASTStringLiteralNode>(createLexeme(SymbolFactory::createStringSymbol()))
    );
    static std::shared_ptr<ASTLiteralExpressionNode> charExpression = std::make_shared<ASTLiteralExpressionNode>(
            std::make_shared<ASTCharLiteralNode>(createLexeme(SymbolFactory::createCharSymbol()))
    );
    static std::shared_ptr<ASTLiteralExpressionNode> trueExpression = std::make_shared<ASTLiteralExpressionNode>(
            std::make_shared<ASTBooleanLiteralNode>(createLexeme(SymbolFactory::createTrueSymbol()))
    );
    static std::shared_ptr<ASTLiteralExpressionNode> falseExpression = std::make_shared<ASTLiteralExpressionNode>(
            std::make_shared<ASTBooleanLiteralNode>(createLexeme(SymbolFactory::createFalseSymbol()))
    );
    static std::shared_ptr<ASTBinaryComparatorOperatorNode> greaterThan = std::make_shared<ASTBinaryComparatorOperatorNode>(createLexeme(SymbolFactory::createGreaterThanSymbol()));
    static std::shared_ptr<ASTBinaryComparatorOperatorNode> greaterThanOrEqual = std::make_shared<ASTBinaryComparatorOperatorNode>(createLexeme(SymbolFactory::createGreaterThanOrEqualSymbol()));
    static std::shared_ptr<ASTBinaryComparatorOperatorNode> lessThan = std::make_shared<ASTBinaryComparatorOperatorNode>(createLexeme(SymbolFactory::createLessThanSymbol()));
    static std::shared_ptr<ASTBinaryComparatorOperatorNode> lessThanOrEqual = std::make_shared<ASTBinaryComparatorOperatorNode>(createLexeme(SymbolFactory::createLessThanOrEqualSymbol()));
    static std::shared_ptr<ASTBinaryArithmeticOperatorNode> plus = std::make_shared<ASTBinaryArithmeticOperatorNode>(createLexeme(SymbolFactory::createPlusSymbol()));
    static std::shared_ptr<ASTBinaryArithmeticOperatorNode> minus = std::make_shared<ASTBinaryArithmeticOperatorNode>(createLexeme(SymbolFactory::createMinusSymbol()));
    static std::shared_ptr<ASTBinaryArithmeticOperatorNode> star = std::make_shared<ASTBinaryArithmeticOperatorNode>(createLexeme(SymbolFactory::createStarSymbol()));
    static std::shared_ptr<ASTBinaryArithmeticOperatorNode> slash = std::make_shared<ASTBinaryArithmeticOperatorNode>(createLexeme(SymbolFactory::createSlashSymbol()));
    static std::shared_ptr<ASTBinaryArithmeticOperatorNode> modulo = std::make_shared<ASTBinaryArithmeticOperatorNode>(createLexeme(SymbolFactory::createModuloSymbol()));
    static std::shared_ptr<ASTBinaryComparatorOperatorNode> equality = std::make_shared<ASTBinaryComparatorOperatorNode>(createLexeme(SymbolFactory::createEqualEqualSymbol()));
    static std::shared_ptr<ASTUnaryOperatorNode> unaryMinus = std::make_shared<ASTUnaryOperatorNode>(createLexeme(SymbolFactory::createMinusSymbol()));
    static std::shared_ptr<ASTUnaryOperatorNode> unaryPlus = std::make_shared<ASTUnaryOperatorNode>(createLexeme(SymbolFactory::createPlusSymbol()));
    static std::shared_ptr<ASTUnaryOperatorNode> bang = std::make_shared<ASTUnaryOperatorNode>(createLexeme(SymbolFactory::createBangSymbol()));
    static std::shared_ptr<ASTLogicalOperatorNode> andOperator = std::make_shared<ASTLogicalOperatorNode>(createLexeme(SymbolFactory::createAndSymbol()));
    static std::shared_ptr<ASTLogicalOperatorNode> orOperator = std::make_shared<ASTLogicalOperatorNode>(createLexeme(SymbolFactory::createOrSymbol()));
    static std::shared_ptr<ASTConcatNode> concatOperator = std::make_shared<ASTConcatNode>(createLexeme(SymbolFactory::createConcatSymbol()));
    static std::shared_ptr<ASTInterfaceNode> interfaceKeyword = std::make_shared<ASTInterfaceNode>(createLexeme(SymbolFactory::createInterfaceSymbol()));
    static std::shared_ptr<ASTImplementsNode> implementsKeyword = std::make_shared<ASTImplementsNode>(createLexeme(SymbolFactory::createImplementsSymbol()));
    static std::shared_ptr<ASTImplementsInterfaceNameNode> implementsInterfaceName = std::make_shared<ASTImplementsInterfaceNameNode>(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static std::shared_ptr<ASTUnaryExpressionNode> bangTrue = std::make_shared<ASTUnaryExpressionNode>(
            ASTNodeFactory::bang,
            ASTNodeFactory::trueExpression
    );
    static std::shared_ptr<ASTUnaryExpressionNode> bangFalse = std::make_shared<ASTUnaryExpressionNode>(
            ASTNodeFactory::bang,
            ASTNodeFactory::falseExpression
    );
    static std::shared_ptr<ASTUnaryExpressionNode> bangId = std::make_shared<ASTUnaryExpressionNode>(
            ASTNodeFactory::bang,
            ASTNodeFactory::idExpression
    );
    static std::shared_ptr<ASTUnaryExpressionNode> bangInt = std::make_shared<ASTUnaryExpressionNode>(
            ASTNodeFactory::bang,
            ASTNodeFactory::intExpression
    );
    static std::shared_ptr<ASTUnaryExpressionNode> negativeInt = std::make_shared<ASTUnaryExpressionNode>(
            ASTNodeFactory::unaryMinus,
            ASTNodeFactory::intExpression
    );
    static std::shared_ptr<ASTUnaryExpressionNode> positiveInt = std::make_shared<ASTUnaryExpressionNode>(
            ASTNodeFactory::unaryPlus,
            ASTNodeFactory::intExpression
    );
    static std::shared_ptr<ASTUnaryExpressionNode> negativeId = std::make_shared<ASTUnaryExpressionNode>(
            ASTNodeFactory::unaryMinus,
            ASTNodeFactory::idExpression
    );
    static std::shared_ptr<ASTUnaryExpressionNode> positiveId = std::make_shared<ASTUnaryExpressionNode>(
            ASTNodeFactory::unaryPlus,
            ASTNodeFactory::idExpression
    );
    static std::shared_ptr<ASTUnaryExpressionNode> negativeFloat = std::make_shared<ASTUnaryExpressionNode>(
            ASTNodeFactory::unaryMinus,
            ASTNodeFactory::floatExpression
    );
    static std::shared_ptr<ASTUnaryExpressionNode> positiveFloat = std::make_shared<ASTUnaryExpressionNode>(
            ASTNodeFactory::unaryPlus,
            ASTNodeFactory::floatExpression
    );
    static std::shared_ptr<ASTArrayAccessNode> arrayAccessInt =  std::make_shared<ASTArrayAccessNode>(
            ASTNodeFactory::leftBracket,
            ASTNodeFactory::intExpression,
            ASTNodeFactory::rightBracket
    );
    static std::shared_ptr<ASTArrayAccessNode> arrayAccessId =  std::make_shared<ASTArrayAccessNode>(
            ASTNodeFactory::leftBracket,
            ASTNodeFactory::idExpression,
            ASTNodeFactory::rightBracket
    );
    static std::shared_ptr<ASTThisNode> thisNode = std::make_shared<ASTThisNode>(
            createLexeme(SymbolFactory::createThisSymbol())
    );
    static std::shared_ptr<ASTCatchErrorVariableNode> catchErrorVariable = std::make_shared<ASTCatchErrorVariableNode>(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static std::shared_ptr<ASTTypeNode> intType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createIntTypeSymbol()));
    static std::shared_ptr<ASTTypeNode> floatType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createFloatTypeSymbol()));
    static std::shared_ptr<ASTTypeNode> stringType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createStringTypeSymbol()));
    static std::shared_ptr<ASTTypeNode> charType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createCharTypeSymbol()));
    static std::shared_ptr<ASTTypeNode> booleanType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createBooleanTypeSymbol()));
    static std::shared_ptr<ASTTypeNode> idType = ASTTypeNodeFactory::createCustomTypeNode(createLexeme(SymbolFactory::createIdentifierSymbol()), "id");
    static std::shared_ptr<ASTTypeNode> thisType = ASTTypeNodeFactory::createThisTypeNode(ASTNodeFactory::thisNode);
    static std::shared_ptr<ASTTypeNode> voidType = ASTTypeNodeFactory::createVoidTypeNode(ASTNodeFactory::voidNode);

    static std::shared_ptr<ASTFunctionNode> functionKeyword =  std::make_shared<ASTFunctionNode>(
            createLexeme(SymbolFactory::createFunctionSymbol())
    );
    static std::shared_ptr<ASTProcedureNode> procedureKeyword =  std::make_shared<ASTProcedureNode>(
            createLexeme(SymbolFactory::createProcedureSymbol())
    );
    static std::shared_ptr<ASTFunctionNameNode> functionName =  std::make_shared<ASTFunctionNameNode>(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static std::shared_ptr<ASTFunctionReturnNode> functionReturn =  std::make_shared<ASTFunctionReturnNode>(
            createLexeme(SymbolFactory::createReturnSymbol())
    );
    static std::shared_ptr<ASTFunctionReturnNode> functionReturnFatArrow =  std::make_shared<ASTFunctionReturnNode>(
            createLexeme(SymbolFactory::createFatArrowSymbol())
    );
    static std::shared_ptr<ASTFunctionParameterListStartNode> leftParen = std::make_shared<ASTFunctionParameterListStartNode>(
            createLexeme(SymbolFactory::createLeftParenSymbol())
    );
    static std::shared_ptr<ASTFunctionParameterListEndNode> rightParen = std::make_shared<ASTFunctionParameterListEndNode>(
            createLexeme(SymbolFactory::createRightParenSymbol())
    );
    static std::shared_ptr<ASTFunctionParameterNode> intFunctionParameter =  std::make_shared<ASTFunctionParameterNode>(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::typeColon,
            ASTNodeFactory::intType
    );

    static std::shared_ptr<ASTFunctionParameterNode> floatFunctionParameter =  std::make_shared<ASTFunctionParameterNode>(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::typeColon,
            ASTNodeFactory::floatType
    );
    static std::shared_ptr<ASTFunctionParameterNode> stringFunctionParameter =  std::make_shared<ASTFunctionParameterNode>(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::typeColon,
            ASTNodeFactory::stringType
    );
    static std::shared_ptr<ASTFunctionParameterNode> charFunctionParameter =  std::make_shared<ASTFunctionParameterNode>(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::typeColon,
            ASTNodeFactory::charType
    );
    static std::shared_ptr<ASTFunctionParameterNode> booleanFunctionParameter =  std::make_shared<ASTFunctionParameterNode>(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::typeColon,
            ASTNodeFactory::booleanType
    );
    static std::shared_ptr<ASTFunctionParameterNode> idFunctionParameter =  std::make_shared<ASTFunctionParameterNode>(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::typeColon,
            ASTNodeFactory::idType
    );
    static std::vector<std::shared_ptr<ASTCommaNode>> createCommaList(unsigned long size) {
        auto commas = std::vector<std::shared_ptr<ASTCommaNode>>();
        for (int i = 0; i < size; ++i) {
            commas.push_back(std::make_shared<ASTCommaNode>(createLexeme(SymbolFactory::createCommaSymbol())));
        }
        return commas;
    }
    static std::shared_ptr<ASTFunctionParameterNode> createFunctionParameter(std::shared_ptr<ASTTypeNode> typeNode) {
        return std::make_shared<ASTFunctionParameterNode>(
                ASTNodeFactory::idExpression,
                ASTNodeFactory::typeColon,
                typeNode
        );
    }
    static std::shared_ptr<ASTFunctionDefinitionNode> createFunctionDefinition(std::shared_ptr<ASTFunctionNameNode> name, std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTTypeNode> returnType) {
        return std::make_shared<ASTFunctionDefinitionNode>(ASTNodeFactory::functionKeyword, name, parameters, ASTNodeFactory::typeColon, returnType);
    }
    static std::shared_ptr<ASTProcedureDefinitionNode> createProcedureDefinition(std::shared_ptr<ASTFunctionNameNode> name, std::shared_ptr<ASTFunctionParameterListNode> parameters) {
        return std::make_shared<ASTProcedureDefinitionNode>(ASTNodeFactory::procedureKeyword, name, parameters);
    }
    static std::shared_ptr<ASTShareExpressionNode> createShareExpression(std::shared_ptr<ASTExpressionNode> expression) {
        return std::make_shared<ASTShareExpressionNode>(ASTNodeFactory::shareKeyword, expression);
    }
    static std::shared_ptr<ASTDrefExpressionNode> createDrefExpression(std::shared_ptr<ASTExpressionNode> expression) {
        return std::make_shared<ASTDrefExpressionNode>(ASTNodeFactory::drefKeyword, expression);
    }
    static std::shared_ptr<ASTConcatExpressionNode> createConcatExpression(std::shared_ptr<ASTExpressionNode> leftExpression, std::shared_ptr<ASTExpressionNode> rightExpression) {
        return std::make_shared<ASTConcatExpressionNode>(leftExpression, ASTNodeFactory::concatOperator, rightExpression);
    }
    static std::shared_ptr<ASTShareExpressionNode> shareIntExpression = ASTNodeFactory::createShareExpression(ASTNodeFactory::intExpression);
    static std::shared_ptr<ASTShareExpressionNode> shareFloatExpression = ASTNodeFactory::createShareExpression(ASTNodeFactory::floatExpression);
    static std::shared_ptr<ASTShareExpressionNode> shareStringExpression = ASTNodeFactory::createShareExpression(ASTNodeFactory::stringExpression);
    static std::shared_ptr<ASTShareExpressionNode> shareCharExpression = ASTNodeFactory::createShareExpression(ASTNodeFactory::charExpression);
    static std::shared_ptr<ASTShareExpressionNode> shareTrueExpression = ASTNodeFactory::createShareExpression(ASTNodeFactory::trueExpression);
    static std::shared_ptr<ASTShareExpressionNode> shareFalseExpression = ASTNodeFactory::createShareExpression(ASTNodeFactory::falseExpression);
    static std::shared_ptr<ASTVariableAssignmentNode> varAssignment =  std::make_shared<ASTVariableAssignmentNode>(
            std::make_shared<ASTIdentifierNode>(createLexeme(SymbolFactory::createIdentifierSymbol())),
            ASTNodeFactory::assignment
    );
    static std::shared_ptr<ASTEnumNode> enumKeyword =  std::make_shared<ASTEnumNode>(
            createLexeme(SymbolFactory::createEnumSymbol())
    );
    static std::shared_ptr<ASTEnumNameNode> enumName =  std::make_shared<ASTEnumNameNode>(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static std::shared_ptr<ASTEnumKeyNode> enumKey =  std::make_shared<ASTEnumKeyNode>(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static std::shared_ptr<ASTEnumKeyValueNode> enumKeyOnly =  std::make_shared<ASTEnumKeyValueNode>(
            ASTNodeFactory::enumKey
    );
    static std::shared_ptr<ASTTupleAccessNode> tupleAccess =  std::make_shared<ASTTupleAccessNode>(
            createLexeme(SymbolFactory::createIntSymbol())
    );
    static std::shared_ptr<ASTObjectAccessSourceNode> objectAccessSourceId = std::make_shared<ASTObjectAccessSourceNode>(
            ASTNodeFactory::idExpression
    );
    static std::shared_ptr<ASTObjectAccessTargetNode> objectAccessTargetId = std::make_shared<ASTObjectAccessTargetNode>(
            ASTNodeFactory::idExpression
    );
    static std::shared_ptr<ASTObjectAccessTargetNode> objectAccessTargetCallableId = std::make_shared<ASTObjectAccessTargetNode>(
            ASTNodeFactory::callableIdExpression
    );
    static std::shared_ptr<ASTForInVariableNode> forVariable = std::make_shared<ASTForInVariableNode>(
            ASTNodeFactory::idExpression
    );
    static std::shared_ptr<ASTForInSourceNode> forSourceId = std::make_shared<ASTForInSourceNode>(
            ASTNodeFactory::idExpression
    );
    static std::shared_ptr<ASTBreakNode> breakStatement = std::make_shared<ASTBreakNode>(
            createLexeme(SymbolFactory::createBreakSymbol())
    );
    static std::shared_ptr<ASTSkipNode> skipStatement = std::make_shared<ASTSkipNode>(
            createLexeme(SymbolFactory::createSkipSymbol())
    );
    static std::shared_ptr<ASTModuleNode> moduleKeyword = std::make_shared<ASTModuleNode>(createLexeme(SymbolFactory::createModuleSymbol()));
    static std::shared_ptr<ASTModuleNameNode> moduleName = std::make_shared<ASTModuleNameNode>(
            ASTNodeFactory::id
    );
    static std::shared_ptr<ASTModuleAliasNameNode> moduleAliasName = std::make_shared<ASTModuleAliasNameNode>(
            ASTNodeFactory::id
    );
    static std::shared_ptr<ASTModuleListItemNode> moduleNormalItem = std::make_shared<ASTModuleListItemNode>(
            std::make_shared<ASTModuleListNormalItemNode>(moduleName)
    );
    static std::shared_ptr<ASTAsNode> as = std::make_shared<ASTAsNode>(
            createLexeme(SymbolFactory::createAsSymbol())
    );
    static std::shared_ptr<ASTModuleListItemNode> moduleAliasItem = std::make_shared<ASTModuleListItemNode>(
            std::make_shared<ASTModuleListAliasItemNode>(moduleName, ASTNodeFactory::as, moduleAliasName)
    );
    static std::shared_ptr<ASTModuleListItemNode> moduleSpreadItem = std::make_shared<ASTModuleListItemNode>(
            std::make_shared<ASTModuleListSpreadItemNode>(moduleName, ASTNodeFactory::moduleSpread)
    );
    static std::shared_ptr<ASTImportNode> importKeyword = std::make_shared<ASTImportNode>(
            createLexeme(SymbolFactory::createImportSymbol())
    );
    static std::shared_ptr<ASTUseNode> useKeyword = std::make_shared<ASTUseNode>(
            createLexeme(SymbolFactory::createUseSymbol())
    );
    static std::shared_ptr<ASTFromNode> fromKeyword = std::make_shared<ASTFromNode>(
            createLexeme(SymbolFactory::createFromSymbol())
    );
    static std::shared_ptr<ASTImportModuleNameNode> importModuleName = std::make_shared<ASTImportModuleNameNode>(
            ASTNodeFactory::id
    );
    static std::shared_ptr<ASTImportModuleAliasNameNode> importModuleAliasName = std::make_shared<ASTImportModuleAliasNameNode>(
            ASTNodeFactory::id
    );
    static std::shared_ptr<ASTImportWildcardNode> importModuleWildcard = std::make_shared<ASTImportWildcardNode>(
            createLexeme(SymbolFactory::createStarSymbol())
    );
    static std::shared_ptr<ASTImportModuleListItemNode> importModuleNormalItem = std::make_shared<ASTImportModuleListItemNode>(
            std::make_shared<ASTImportModuleListNormalItemNode>(importModuleName)
    );
    static std::shared_ptr<ASTImportModuleListItemNode> importModuleAliasItem = std::make_shared<ASTImportModuleListItemNode>(
            std::make_shared<ASTImportModuleListAliasItemNode>(importModuleName, ASTNodeFactory::as, importModuleAliasName)
    );
    static std::shared_ptr<ASTImportModuleListItemNode> importModuleSpreadItem = std::make_shared<ASTImportModuleListItemNode>(
            std::make_shared<ASTImportModuleListSpreadItemNode>(ASTNodeFactory::importSpread, importModuleName)
    );
    static std::shared_ptr<ASTImportModuleListItemNode> importModuleWildcardItem = std::make_shared<ASTImportModuleListItemNode>(
            std::make_shared<ASTImportModuleListWildcardItemNode>(createLexeme(SymbolFactory::createStarSymbol()))
    );

    static std::shared_ptr<ASTImportModuleListItemNode> importModuleByWildcardItem = std::make_shared<ASTImportModuleListItemNode>(
            std::make_shared<ASTImportModuleListByWildcardItemNode>(importModuleName, ASTNodeFactory::moduleAccess, importModuleWildcard)
    );
    static std::shared_ptr<ASTImportPathNode> importPath = std::make_shared<ASTImportPathNode>(
            ASTNodeFactory::stringLiteral
    );
    static std::shared_ptr<ASTNewNode> newKeyword = std::make_shared<ASTNewNode>(
            createLexeme(SymbolFactory::createNewSymbol())
    );
    static std::shared_ptr<ASTClassNode> classKeyword = std::make_shared<ASTClassNode>(
            createLexeme(SymbolFactory::createClassSymbol())
    );
    static std::shared_ptr<ASTClassNameNode> createClassName(std::string name) {
        auto className = std::make_shared<ASTClassNameNode>(createLexeme(SymbolFactory::createIdentifierSymbol()));
        className->setId(name);
        return className;
    }
    static std::shared_ptr<ASTClassPropertyNameNode> classPropertyName = std::make_shared<ASTClassPropertyNameNode>(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static std::shared_ptr<ASTClassMethodNameNode> classMethodName = std::make_shared<ASTClassMethodNameNode>(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static std::shared_ptr<ASTClassMethodCallNode> classMethodCall = std::make_shared<ASTClassMethodCallNode>(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static std::shared_ptr<ASTConstructorNode> classConstructor = std::make_shared<ASTConstructorNode>(
            createLexeme(SymbolFactory::createConstructorSymbol())
    );
    static std::shared_ptr<ASTClassAccessNode> classAccess = std::make_shared<ASTClassAccessNode>(
            ASTNodeFactory::thisNode,
            std::make_shared<ASTThisAccessNode>(createLexeme(SymbolFactory::createPeriodSymbol()))
    );
    static std::shared_ptr<ASTClassPropertyAccessNode> classPropertyAccess = std::make_shared<ASTClassPropertyAccessNode>(
            ASTNodeFactory::classAccess,
            ASTNodeFactory::classPropertyName
    );
    static std::shared_ptr<ASTClassPropertyAssignmentNode> classPropertyAssignment = std::make_shared<ASTClassPropertyAssignmentNode>(
            ASTNodeFactory::classPropertyAccess,
            ASTNodeFactory::assignment
    );
    static std::shared_ptr<ASTClassPropertyAccessExpressionNode> classPropertyAccessExpression = std::make_shared<ASTClassPropertyAccessExpressionNode>(
            ASTNodeFactory::classPropertyAccess
    );
    static std::shared_ptr<ASTThisExpressionNode> thisExpression = std::make_shared<ASTThisExpressionNode>(
            ASTNodeFactory::thisNode
    );
    static std::shared_ptr<ASTPublicNode> publicModifier = std::make_shared<ASTPublicNode>(
            createLexeme(SymbolFactory::createPublicSymbol())
    );
    static std::shared_ptr<ASTProtectedNode> protectedModifier = std::make_shared<ASTProtectedNode>(
            createLexeme(SymbolFactory::createProtectedSymbol())
    );
    static std::shared_ptr<ASTPrivateNode> privateModifier = std::make_shared<ASTPrivateNode>(
            createLexeme(SymbolFactory::createPrivateSymbol())
    );
    static std::shared_ptr<ASTStaticNode> staticKeyword = std::make_shared<ASTStaticNode>(
            createLexeme(SymbolFactory::createStaticSymbol())
    );
    static std::shared_ptr<ASTConstNode> constKeyword = std::make_shared<ASTConstNode>(
            createLexeme(SymbolFactory::createConstSymbol())
    );
    static std::shared_ptr<ASTInterfaceNameNode> interfaceName =  std::make_shared<ASTInterfaceNameNode>(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static std::shared_ptr<ASTInterfaceDefinitionNode> interfaceDefinition =  std::make_shared<ASTInterfaceDefinitionNode>(
            ASTNodeFactory::interfaceKeyword,
            ASTNodeFactory::interfaceName
    );
    static std::shared_ptr<ASTInterfaceStartNode> interfaceStart = std::make_shared<ASTInterfaceStartNode>(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static std::shared_ptr<ASTInterfaceEndNode> interfaceEnd = std::make_shared<ASTInterfaceEndNode>(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static std::shared_ptr<ASTInterfaceColonNode> interfaceColon = std::make_shared<ASTInterfaceColonNode>(createLexeme(SymbolFactory::createColonSymbol()));
    static std::shared_ptr<ASTInterfacePropertyNameNode> interfacePropertyName = std::make_shared<ASTInterfacePropertyNameNode>(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static std::shared_ptr<ASTInterfacePropertyNode> createInterfaceProperty(std::shared_ptr<ASTTypeNode> type) {
        return std::make_shared<ASTInterfacePropertyNode>(
            ASTNodeFactory::interfacePropertyName,
            ASTNodeFactory::interfaceColon,
            type
        );
    }
    static std::shared_ptr<ASTInterfacePropertyListNode> createInterfacePropertyList(std::vector<std::shared_ptr<ASTInterfacePropertyNode>> properties) {
        return std::make_shared<ASTInterfacePropertyListNode>(
                ASTNodeFactory::interfaceStart,
                properties,
                ASTNodeFactory::createCommaList(properties.size()),
                ASTNodeFactory::interfaceEnd
        );
    }
    static std::shared_ptr<ASTTupleTypeStartNode> tupleTypeStart = std::make_shared<ASTTupleTypeStartNode>(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static std::shared_ptr<ASTTupleTypeEndNode> tupleTypeEnd = std::make_shared<ASTTupleTypeEndNode>(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static std::shared_ptr<ASTStructTypeStartNode> structTypeStart = std::make_shared<ASTStructTypeStartNode>(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static std::shared_ptr<ASTStructTypeEndNode> structTypeEnd = std::make_shared<ASTStructTypeEndNode>(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static std::shared_ptr<ASTStructTypeKeyNode> structTypeKey = std::make_shared<ASTStructTypeKeyNode>(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static std::shared_ptr<ASTStructTypeColonNode> structTypeColon = std::make_shared<ASTStructTypeColonNode>(createLexeme(SymbolFactory::createColonSymbol()));
    static std::shared_ptr<ASTTypeKeywordNode> typeKeyword = std::make_shared<ASTTypeKeywordNode>(createLexeme(SymbolFactory::createTypeSymbol()));
    static std::shared_ptr<ASTTypeNameNode> typeName = std::make_shared<ASTTypeNameNode>(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static std::shared_ptr<ASTTypeAssignmentOperatorNode> typeAssignmentOperator = std::make_shared<ASTTypeAssignmentOperatorNode>(createLexeme(SymbolFactory::createEqualSymbol()));
    static std::shared_ptr<ASTCustomTypeDeclarationNode> createCustomType(std::shared_ptr<ASTTypeNode> type, std::optional<std::shared_ptr<ASTExportNode>> exportKeyword = {}) {
        return std::make_shared<ASTCustomTypeDeclarationNode>(
               ASTNodeFactory::typeKeyword,
               ASTNodeFactory::typeName,
               ASTNodeFactory::typeAssignmentOperator,
               type,
               exportKeyword
        );
    }
    static std::shared_ptr<ASTArrayNode> createArray(std::vector<std::shared_ptr<ASTExpressionNode>> elements) {
        return std::make_shared<ASTArrayNode>(
            ASTNodeFactory::leftBracket,
            elements,
            ASTNodeFactory::createCommaList(elements.size()),
            ASTNodeFactory::rightBracket
        );
    }
    static std::shared_ptr<ASTArrayExpressionNode> createArrayExpression(std::vector<std::shared_ptr<ASTExpressionNode>> elements) {
        return std::make_shared<ASTArrayExpressionNode>(
                    std::make_shared<ASTArrayNode>(
                        ASTNodeFactory::leftBracket,
                        elements,
                        ASTNodeFactory::createCommaList(elements.size()),
                        ASTNodeFactory::rightBracket
        ));
    }
    static std::shared_ptr<ASTArrayAccessNode> createArrayAccess(std::shared_ptr<ASTExpressionNode> element) {
        return std::make_shared<ASTArrayAccessNode>(
                ASTNodeFactory::leftBracket,
                element,
                ASTNodeFactory::rightBracket
        );
    }
    static std::shared_ptr<ASTStructKeyValueNode> createStructKeyValue(std::shared_ptr<ASTExpressionNode> value) {
        return std::make_shared<ASTStructKeyValueNode>(
                ASTNodeFactory::idExpression,
                ASTNodeFactory::structColon,
                value
        );
    }
    static std::shared_ptr<ASTStructExpressionNode> createStructExpression(std::vector<std::shared_ptr<ASTStructKeyValueNode>> fields) {
        return std::make_shared<ASTStructExpressionNode>(
                ASTNodeFactory::structStart,
                fields,
                ASTNodeFactory::createCommaList(fields.size()),
                ASTNodeFactory::structEnd
        );
    }
    static std::shared_ptr<ASTObjectAccessExpressionNode> createObjectAccessExpression(std::shared_ptr<ASTObjectAccessSourceNode> source, std::shared_ptr<ASTObjectAccessTargetNode> target) {
        return std::make_shared<ASTObjectAccessExpressionNode>(
                source,
                ASTNodeFactory::period,
                target
        );
    }
    static std::shared_ptr<ASTTupleAccessExpressionNode> createTupleAccessExpression(std::shared_ptr<ASTObjectAccessSourceNode> source, std::shared_ptr<ASTTupleAccessNode> target) {
        return std::make_shared<ASTTupleAccessExpressionNode>(
                source,
                ASTNodeFactory::period,
                target
        );
    }
    static std::shared_ptr<ASTFunctionParameterNode> createFunctionParameter(std::shared_ptr<ASTIdentifierExpressionNode> name, std::shared_ptr<ASTTypeNode> type) {
        return std::make_shared<ASTFunctionParameterNode>(
                name,
                ASTNodeFactory::typeColon,
                type
        );
    }
    static std::shared_ptr<ASTFunctionParameterListNode> createFunctionParameterList(std::vector<std::shared_ptr<ASTFunctionParameterNode>> parameters = {}) {
        return std::make_shared<ASTFunctionParameterListNode>(
                ASTNodeFactory::functionParameterListStart,
                parameters,
                ASTNodeFactory::createCommaList(parameters.size()),
                ASTNodeFactory::functionParameterListEnd
        );
    }
    static std::shared_ptr<ASTFunctionBlockNode> createFunctionBlock(std::vector<std::shared_ptr<ASTNode>> contents) {
        return std::make_shared<ASTFunctionBlockNode>(
                ASTNodeFactory::blockStart,
                contents,
                ASTNodeFactory::blockEnd
        );
    }
    static std::shared_ptr<ASTBlockNode> createBlock(std::vector<std::shared_ptr<ASTNode>> contents) {
        return std::make_shared<ASTBlockNode>(
                ASTNodeFactory::blockStart,
                contents,
                ASTNodeFactory::blockEnd
        );
    }
    static std::shared_ptr<ASTControlFlowBlockNode> createControlFlowBlock(std::vector<std::shared_ptr<ASTNode>> contents) {
        return std::make_shared<ASTControlFlowBlockNode>(
                ASTNodeFactory::blockStart,
                contents,
                ASTNodeFactory::blockEnd
        );
    }
    static std::shared_ptr<ASTImplementsInterfaceListNode> createImplementsInterfaceList(std::vector<std::shared_ptr<ASTImplementsInterfaceNameNode>> interfaceNames) {
        return std::make_shared<ASTImplementsInterfaceListNode>(
                ASTNodeFactory::implementsKeyword,
                interfaceNames,
                ASTNodeFactory::createCommaList(interfaceNames.size())
        );
    }
    static std::shared_ptr<ASTClassBlockNode> createClassBlock(std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>> properties, std::vector<std::shared_ptr<ASTClassMethodDeclarationNode>> methods, std::vector<std::shared_ptr<ASTClassConstructorDeclarationNode>> constructors) {
        return std::make_shared<ASTClassBlockNode>(
                ASTNodeFactory::blockStart,
                properties,
                methods,
                constructors,
                ASTNodeFactory::blockEnd
        );
    }
    static std::shared_ptr<ASTEnumKeyValueListNode> createEnumKeyValueList(std::vector<std::shared_ptr<ASTEnumKeyValueNode>> contents) {
        return std::make_shared<ASTEnumKeyValueListNode>(
                ASTNodeFactory::enumKeyValueListStart,
                contents,
                ASTNodeFactory::createCommaList(contents.size()),
                ASTNodeFactory::enumKeyValueListEnd
        );
    }
    static std::shared_ptr<ASTFunctionArgumentListNode> createFunctionArgumentList(std::vector<std::shared_ptr<ASTFunctionArgumentNode>> contents = {}) {
        return std::make_shared<ASTFunctionArgumentListNode>(
                ASTNodeFactory::functionArgumentListStart,
                contents,
                ASTNodeFactory::createCommaList(contents.size()),
                ASTNodeFactory::functionArgumentListEnd
        );
    }
    static std::shared_ptr<ASTTupleExpressionNode> createTupleExpression(std::vector<std::shared_ptr<ASTExpressionNode>> expressions = {}) {
        auto tupleItems = std::vector<std::shared_ptr<ASTTupleItemNode>>();
        for (auto expression : expressions) {
            tupleItems.push_back(std::make_shared<ASTTupleItemNode>(expression));
        }
        return std::make_shared<ASTTupleExpressionNode>(
                ASTNodeFactory::tupleListStart,
                tupleItems,
                ASTNodeFactory::createCommaList(tupleItems.size()),
                ASTNodeFactory::tupleListEnd
        );
    }
    static std::shared_ptr<ASTTypeParameterListNode> createTypeParameterList(std::vector<std::shared_ptr<ASTTypeNode>> items = {}) {
        return std::make_shared<ASTTypeParameterListNode>(ASTNodeFactory::typeParameterListStart, items, ASTNodeFactory::createCommaList(items.size()), ASTNodeFactory::typeParameterListEnd);
    }
    static std::shared_ptr<ASTLambdaTypeParameterListNode> createLambdaTypeParameterList(std::vector<std::shared_ptr<ASTTypeNode>> items = {}) {
        return std::make_shared<ASTLambdaTypeParameterListNode>(
                ASTNodeFactory::lambdaTypeParameterListStart,
                items,
                ASTNodeFactory::createCommaList(items.size()),
                ASTNodeFactory::lambdaTypeParameterListEnd
        );
    }
    static std::shared_ptr<ASTTypeNode> createTupleType(std::vector<std::shared_ptr<ASTTypeNode>> items = {}) {
        return ASTTypeNodeFactory::createTupleTypeNode(
                std::make_shared<ASTTupleTypeNode>(
                        ASTNodeFactory::tupleTypeStart,
                        items,
                        ASTNodeFactory::createCommaList(items.size()),
                        ASTNodeFactory::tupleTypeEnd
                )
        );
    }
    static std::shared_ptr<ASTStructTypeKeyValueNode> createStructTypeKeyValue(std::shared_ptr<ASTTypeNode> type) {
        return std::make_shared<ASTStructTypeKeyValueNode>(
                ASTNodeFactory::structTypeKey,
                ASTNodeFactory::structTypeColon,
                type
        );
    }
    static std::shared_ptr<ASTTypeNode> createStructType(std::vector<std::shared_ptr<ASTStructTypeKeyValueNode>> items = {}) {
        return ASTTypeNodeFactory::createStructTypeNode(std::make_shared<ASTStructTypeNode>(
                ASTNodeFactory::structTypeStart,
                items,
                ASTNodeFactory::createCommaList(items.size()),
                ASTNodeFactory::structTypeEnd
        ));
    }
    static std::shared_ptr<ASTTypeNode> createLambdaType(std::vector<std::shared_ptr<ASTTypeNode>> items, std::shared_ptr<ASTTypeNode> returnType) {
        return ASTTypeNodeFactory::createLambdaTypeNode(std::make_shared<ASTLambdaTypeNode>(
                ASTNodeFactory::createLambdaTypeParameterList(items),
                ASTNodeFactory::lambdaArrow,
                returnType
        ));
    }
    static std::shared_ptr<ASTTypeNode> createLambdaType(std::shared_ptr<ASTTypeNode> returnType) {
        return ASTTypeNodeFactory::createLambdaTypeNode(std::make_shared<ASTLambdaTypeNode>(
                ASTNodeFactory::createLambdaTypeParameterList(),
                ASTNodeFactory::lambdaArrow,
                returnType
        ));
    }
    static std::shared_ptr<ASTTypeNode> createLambdaTypeWithVoidReturn(std::vector<std::shared_ptr<ASTTypeNode>> items = {}) {
        return ASTTypeNodeFactory::createLambdaTypeNode(std::make_shared<ASTLambdaTypeNode>(
                ASTNodeFactory::createLambdaTypeParameterList(items),
                ASTNodeFactory::lambdaArrow,
                ASTNodeFactory::voidType
        ));
    }
    static std::shared_ptr<ASTArrayTypeStartNode> arrayTypeStart = std::make_shared<ASTArrayTypeStartNode>(createLexeme(SymbolFactory::createLeftBracketSymbol()));
    static std::shared_ptr<ASTArrayTypeEndNode> arrayTypeEnd = std::make_shared<ASTArrayTypeEndNode>(createLexeme(SymbolFactory::createRightBracketSymbol()));
    static std::shared_ptr<ASTTypeNode> createArrayType(std::shared_ptr<ASTTypeNode> elementType) {
        return ASTTypeNodeFactory::createArrayTypeNode(
            std::make_shared<ASTArrayTypeNode>(
                ASTNodeFactory::arrayTypeStart,
                elementType,
                ASTNodeFactory::arrayTypeEnd
        ));
    }
    static std::shared_ptr<ASTTypeNode> createSharedType(std::shared_ptr<ASTTypeNode> refType) {
        return ASTTypeNodeFactory::createSharedTypeNode(
                std::make_shared<ASTSharedTypeNode>(
                    ASTNodeFactory::sharedTypeKeyword,
                    ASTNodeFactory::createTypeParameterList({ refType })
                ));
    }
    static std::shared_ptr<ASTImportModuleListNode> createImportModuleList(std::vector<std::shared_ptr<ASTImportModuleListItemNode>> items = {}) {
        return std::make_shared<ASTImportModuleListNode>(
                ASTNodeFactory::importModuleListStart,
                items,
                ASTNodeFactory::importModuleListEnd
        );
    }
    static std::shared_ptr<ASTImportModuleListByGroupItemNode> createImportModuleByGroupItem(std::vector<std::shared_ptr<ASTImportModuleListItemNode>> items) {
        return std::make_shared<ASTImportModuleListByGroupItemNode>(
                ASTNodeFactory::importModuleName,
                ASTNodeFactory::moduleAccess,
                ASTNodeFactory::createImportModuleList(items)
        );
    }
    static std::shared_ptr<ASTImportModuleListByWildcardItemNode> createImportModuleByWildcard() {
        return std::make_shared<ASTImportModuleListByWildcardItemNode>(
                ASTNodeFactory::importModuleName,
                ASTNodeFactory::moduleAccess,
                ASTNodeFactory::importModuleWildcard
        );
    }
}

#endif //JETLANG_AST_NODE_FACTORY_H
