//
// Created by Johny Georges on 2024-03-01.
//

#ifndef JETLANG_AST_NODE_FACTORY_H
#define JETLANG_AST_NODE_FACTORY_H

#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../../../src/core/symbol/symbol-factory.h"
#include "../../../../../src/core/ast/ast-nodes/ast-variable-nodes/ast-variable-init-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-logical-operators/ast-logical-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-binary-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-array-nodes/ast-array-access-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-variable-nodes/ast-variable-assignment-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-key-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-call-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-tuple-nodes/ast-tuple-access-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-object-nodes/ast-object-access-source-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-object-nodes/ast-object-access-target-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-for-variable-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-for-source-node.h"
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

namespace ASTNodeFactory {
    Lexeme* createLexeme(Symbol* symbol) {
        return new Lexeme(new Token(symbol), 1, 0);
    }
    static ASTIdentifierNode* id = new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static ASTIdentifierExpressionNode* idExpression = new ASTIdentifierExpressionNode(
        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );

    static ASTVariableInitNode* letInit = new ASTVariableInitNode(
                new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );
    static ASTVariableInitNode* constInit = new ASTVariableInitNode(
            new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
            new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );
    static ASTVariableInitNode* createConstInitWithType(ASTTypeNode* type) {
        return new ASTVariableInitNode(
                new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())),
                type
        );
    }
    static ASTIntLiteralNode* intLiteral = new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()));
    static ASTFloatLiteralNode* floatLiteral = new ASTFloatLiteralNode(createLexeme(SymbolFactory::createFloatSymbol()));
    static ASTStringLiteralNode* stringLiteral = new ASTStringLiteralNode(createLexeme(SymbolFactory::createStringSymbol()));
    static ASTCharLiteralNode* charLiteral = new ASTCharLiteralNode(createLexeme(SymbolFactory::createCharSymbol()));
    static ASTBooleanLiteralNode* trueLiteral = new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()));
    static ASTBooleanLiteralNode* falseLiteral = new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()));

    static ASTLiteralExpressionNode* intExpression = new ASTLiteralExpressionNode(
            new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
    );
    static ASTLiteralExpressionNode* floatExpression = new ASTLiteralExpressionNode(
            new ASTFloatLiteralNode(createLexeme(SymbolFactory::createFloatSymbol()))
    );
    static ASTLiteralExpressionNode* stringExpression = new ASTLiteralExpressionNode(
            new ASTStringLiteralNode(createLexeme(SymbolFactory::createStringSymbol()))
    );
    static ASTLiteralExpressionNode* charExpression = new ASTLiteralExpressionNode(
            new ASTCharLiteralNode(createLexeme(SymbolFactory::createCharSymbol()))
    );
    static ASTLiteralExpressionNode* trueExpression = new ASTLiteralExpressionNode(
            new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
    );
    static ASTLiteralExpressionNode* falseExpression = new ASTLiteralExpressionNode(
            new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
    );
    static ASTBinaryOperatorNode* greaterThan = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createGreaterThanSymbol()));
    static ASTBinaryOperatorNode* greaterThanOrEqual = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createGreaterThanOrEqualSymbol()));
    static ASTBinaryOperatorNode* lessThan = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createLessThanSymbol()));
    static ASTBinaryOperatorNode* lessThanOrEqual = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createLessThanOrEqualSymbol()));
    static ASTBinaryOperatorNode* plus = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createPlusSymbol()));
    static ASTBinaryOperatorNode* minus = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createMinusSymbol()));
    static ASTBinaryOperatorNode* star = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createStarSymbol()));
    static ASTBinaryOperatorNode* slash = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createSlashSymbol()));
    static ASTBinaryOperatorNode* modulo = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createModuloSymbol()));
    static ASTBinaryOperatorNode* equality = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createEqualEqualSymbol()));
    static ASTUnaryOperatorNode* unaryMinus = new ASTUnaryOperatorNode(createLexeme(SymbolFactory::createMinusSymbol()));
    static ASTUnaryOperatorNode* unaryPlus = new ASTUnaryOperatorNode(createLexeme(SymbolFactory::createPlusSymbol()));
    static ASTUnaryOperatorNode* bang = new ASTUnaryOperatorNode(createLexeme(SymbolFactory::createBangSymbol()));
    static ASTLogicalOperatorNode* andOperator = new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createAndSymbol()));
    static ASTLogicalOperatorNode* orOperator = new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createOrSymbol()));
    static ASTUnaryExpressionNode* bangTrue = new ASTUnaryExpressionNode(
            ASTNodeFactory::bang,
            ASTNodeFactory::trueExpression
    );
    static ASTUnaryExpressionNode* bangFalse = new ASTUnaryExpressionNode(
            ASTNodeFactory::bang,
            ASTNodeFactory::falseExpression
    );
    static ASTUnaryExpressionNode* bangId = new ASTUnaryExpressionNode(
            ASTNodeFactory::bang,
            ASTNodeFactory::idExpression
    );
    static ASTUnaryExpressionNode* bangInt = new ASTUnaryExpressionNode(
            ASTNodeFactory::bang,
            ASTNodeFactory::intExpression
    );
    static ASTUnaryExpressionNode* negativeInt = new ASTUnaryExpressionNode(
            ASTNodeFactory::unaryMinus,
            ASTNodeFactory::intExpression
    );
    static ASTUnaryExpressionNode* positiveInt = new ASTUnaryExpressionNode(
            ASTNodeFactory::unaryPlus,
            ASTNodeFactory::intExpression
    );
    static ASTUnaryExpressionNode* negativeId = new ASTUnaryExpressionNode(
            ASTNodeFactory::unaryMinus,
            ASTNodeFactory::idExpression
    );
    static ASTUnaryExpressionNode* positiveId = new ASTUnaryExpressionNode(
            ASTNodeFactory::unaryPlus,
            ASTNodeFactory::idExpression
    );
    static ASTUnaryExpressionNode* negativeFloat = new ASTUnaryExpressionNode(
            ASTNodeFactory::unaryMinus,
            ASTNodeFactory::floatExpression
    );
    static ASTUnaryExpressionNode* positiveFloat = new ASTUnaryExpressionNode(
            ASTNodeFactory::unaryPlus,
            ASTNodeFactory::floatExpression
    );
    static ASTArrayAccessNode* arrayAccessInt =  new ASTArrayAccessNode(
            ASTNodeFactory::intExpression
    );
    static ASTArrayAccessNode* arrayAccessId =  new ASTArrayAccessNode(
            ASTNodeFactory::idExpression
    );
    static ASTTypeNode* intLiteralType = ASTTypeNodeFactory::createIntLiteralTypeNode(createLexeme(SymbolFactory::createIntSymbol()));
    static ASTTypeNode* intType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createIntTypeSymbol()));
    static ASTTypeNode* floatType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createFloatTypeSymbol()));
    static ASTTypeNode* stringType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createStringTypeSymbol()));
    static ASTTypeNode* charType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createCharTypeSymbol()));
    static ASTTypeNode* booleanType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createBooleanTypeSymbol()));
    static ASTTypeNode* arrayType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createArrayTypeSymbol()));
    static ASTTypeNode* idType = ASTTypeNodeFactory::createCustomTypeNode(ASTNodeFactory::id);
    static ASTFunctionNameNode* functionName =  new ASTFunctionNameNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTFunctionCallNode* functionCall =  new ASTFunctionCallNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTFunctionParameterNode* intFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::intType
    );
    static ASTFunctionParameterNode* floatFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::floatType
    );
    static ASTFunctionParameterNode* stringFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::stringType
    );
    static ASTFunctionParameterNode* charFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::charType
    );
    static ASTFunctionParameterNode* booleanFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::booleanType
    );
    static ASTFunctionParameterNode* arrayFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::arrayType
    );
    static ASTFunctionParameterNode* idFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::idType
    );
    static ASTVariableAssignmentNode* varAssignment =  new ASTVariableAssignmentNode(
            new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );
    static ASTEnumNameNode* enumName =  new ASTEnumNameNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTEnumKeyNode* enumKey =  new ASTEnumKeyNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTEnumKeyValueNode* enumKeyOnly =  new ASTEnumKeyValueNode(
            ASTNodeFactory::enumKey
    );
    static ASTTupleAccessNode* tupleAccess =  new ASTTupleAccessNode(
            createLexeme(SymbolFactory::createIntSymbol())
    );
    static ASTObjectAccessSourceNode* objectAccessSourceId = new ASTObjectAccessSourceNode(
            ASTNodeFactory::idExpression
    );
    static ASTObjectAccessTargetNode* objectAccessTargetId = new ASTObjectAccessTargetNode(
            ASTNodeFactory::idExpression
    );
    static ASTForVariableNode* forVariable = new ASTForVariableNode(
            ASTNodeFactory::idExpression
    );
    static ASTForSourceNode* forSourceId = new ASTForSourceNode(
            ASTNodeFactory::idExpression
    );
    static ASTBreakNode* breakStatement = new ASTBreakNode(
            createLexeme(SymbolFactory::createBreakSymbol())
    );
    static ASTSkipNode* skipStatement = new ASTSkipNode(
            createLexeme(SymbolFactory::createSkipSymbol())
    );
    static ASTModuleNameNode* moduleName = new ASTModuleNameNode(
            ASTNodeFactory::id
    );
    static ASTModuleAliasNameNode* moduleAliasName = new ASTModuleAliasNameNode(
            ASTNodeFactory::id
    );
    static ASTModuleListItemNode* moduleNormalItem = new ASTModuleListItemNode(
            new ASTModuleListNormalItemNode(moduleName)
    );
    static ASTModuleListItemNode* moduleAliasItem = new ASTModuleListItemNode(
            new ASTModuleListAliasItemNode(moduleName, moduleAliasName)
    );
    static ASTModuleListItemNode* moduleSpreadItem = new ASTModuleListItemNode(
            new ASTModuleListSpreadItemNode(moduleName)
    );
    static ASTImportModuleNameNode* importModuleName = new ASTImportModuleNameNode(
            ASTNodeFactory::id
    );
    static ASTImportModuleAliasNameNode* importModuleAliasName = new ASTImportModuleAliasNameNode(
            ASTNodeFactory::id
    );
    static ASTImportWildcardNode* importModuleWildcard = new ASTImportWildcardNode(
            createLexeme(SymbolFactory::createStarSymbol())
    );
    static ASTImportModuleListItemNode* importModuleNormalItem = new ASTImportModuleListItemNode(
            new ASTImportModuleListNormalItemNode(importModuleName)
    );
    static ASTImportModuleListItemNode* importModuleAliasItem = new ASTImportModuleListItemNode(
            new ASTImportModuleListAliasItemNode(importModuleName, importModuleAliasName)
    );
    static ASTImportModuleListItemNode* importModuleSpreadItem = new ASTImportModuleListItemNode(
            new ASTImportModuleListSpreadItemNode(importModuleName)
    );
    static ASTImportModuleListItemNode* importModuleWildcardItem = new ASTImportModuleListItemNode(
            new ASTImportModuleListWildcardItemNode(createLexeme(SymbolFactory::createStarSymbol()))
    );
    static ASTImportModuleListItemNode* importModuleByWildcardItem = new ASTImportModuleListItemNode(
            new ASTImportModuleListByWildcardItemNode(importModuleName, importModuleWildcard)
    );
    static ASTImportModuleListItemNode* createImportModuleByGroupItem(ASTImportModuleListNode* importModuleList) {
         return new ASTImportModuleListItemNode(
                 new ASTImportModuleListByGroupItemNode(importModuleName, importModuleList)
         );
    }
    static ASTImportPathNode* importPath = new ASTImportPathNode(
            ASTNodeFactory::stringLiteral
    );
};

#endif //JETLANG_AST_NODE_FACTORY_H
