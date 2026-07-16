//
// Created by Johny Georges on 2024-06-15.
//

#include "ir-strategy-map.h"
#include "./literal-ir-strategies/int-literal-ir-strategy/int-literal-ir-strategy.h"
#include "./literal-ir-strategies/float-literal-ir-strategy/float-literal-ir-strategy.h"
#include "./literal-ir-strategies/char-literal-ir-strategy/char-literal-ir-strategy.h"
#include "./literal-ir-strategies/string-literal-ir-strategy/string-literal-ir-strategy.h"
#include "./literal-ir-strategies/bool-literal-ir-strategy/bool-literal-ir-strategy.h"
#include "./expression-ir-strategies/literal-expression-ir-strategy/literal-expression-ir-strategy.h"
#include "./expression-ir-strategies/binary-expression-ir-strategy/binary-expression-ir-strategy.h"
#include "./expression-ir-strategies/concat-expression-ir-strategy/concat-expression-ir-strategy.h"
#include "./expression-ir-strategies/logical-expression-ir-strategy/logical-expression-ir-strategy.h"
#include "./expression-ir-strategies/array-expression-ir-strategy/array-expression-ir-strategy.h"
#include "./expression-ir-strategies/array-access-expression-ir-strategy/array-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/array-access-invocation-expression-ir-strategy/array-access-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/struct-expression-ir-strategy/struct-expression-ir-strategy.h"
#include "./expression-ir-strategies/unary-expression-ir-strategy/unary-expression-ir-strategy.h"
#include "./expression-ir-strategies/tuple-expression-ir-strategy/tuple-expression-ir-strategy.h"
#include "./expression-ir-strategies/this-expression-ir-strategy/this-expression-ir-strategy.h"
#include "./expression-ir-strategies/identifier-expression-ir-strategy/identifier-expression-ir-strategy.h"
#include "./expression-ir-strategies/object-access-expression-ir-strategy/object-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/object-access-invocation-expression-ir-strategy/object-access-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/tuple-access-expression-ir-strategy/tuple-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/tuple-access-invocation-expression-ir-strategy/tuple-access-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/function-invocation-expression-ir-strategy/function-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/lambda-expression-ir-strategy/lambda-expression-ir-strategy.h"
#include "./expression-ir-strategies/module-access-expression-ir-strategy/module-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/class-property-access-expression-ir-strategy/class-property-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/class-method-invocation-expression-ir-strategy/class-method-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/new-class-instance-expression-ir-strategy/new-class-instance-expression-ir-strategy.h"
#include "./expression-ir-strategies/share-expression-ir-strategy/share-expression-ir-strategy.h"
#include "./expression-ir-strategies/dref-expression-ir-strategy/dref-expression-ir-strategy.h"
#include "./expression-statement-ir-strategy/expression-statement-ir-strategy.h"
#include "./class-property-assignment-statement-ir-strategy/class-property-assignment-statement-ir-strategy.h"
#include "./class-property-shared-value-assignment-statement-ir-strategy/class-property-shared-value-assignment-statement-ir-strategy.h"
#include "./shared-value-assignment-statement-ir-strategy/shared-value-assignment-statement-ir-strategy.h"
#include "./variable-assignment-statement-ir-strategy/variable-assignment-statement-ir-strategy.h"
#include "./array-access-assignment-statement-ir-strategy/array-access-assignment-statement-ir-strategy.h"
#include "./array-access-shared-value-assignment-statement-ir-strategy/array-access-shared-value-assignment-statement-ir-strategy.h"
#include "./object-access-assignment-statement-ir-strategy/object-access-assignment-statement-ir-strategy.h"
#include "./object-access-shared-value-assignment-statement-ir-strategy/object-access-shared-value-assignment-statement-ir-strategy.h"
#include "./tuple-access-assignment-statement-ir-strategy/tuple-access-assignment-statement-ir-strategy.h"
#include "./tuple-access-shared-value-assignment-statement-ir-strategy/tuple-access-shared-value-assignment-statement-ir-strategy.h"
#include "./module-access-assignment-statement-ir-strategy/module-access-assignment-statement-ir-strategy.h"
#include "./module-access-shared-value-assignment-statement-ir-strategy/module-access-shared-value-assignment-statement-ir-strategy.h"
#include "./variable-declaration-ir-strategy/variable-declaration-ir-strategy.h"
#include "./function-declaration-ir-strategy/function-declaration-ir-strategy.h"
#include "./function-parameter-list-ir-strategy/function-parameter-list-ir-strategy.h"
#include "./function-return-expression-ir-strategy/function-return-expression-ir-strategy.h"
#include "./procedure-declaration-ir-strategy/procedure-declaration-ir-strategy.h"
#include "./enum-declaration-ir-strategy/enum-declaration-ir-strategy.h"
#include "./interface-type-declaration-ir-strategy/interface-type-declaration-ir-strategy.h"
#include "./custom-type-declaration-ir-strategy/custom-type-declaration-ir-strategy.h"
#include "./module-declaration-ir-strategy/module-declaration-ir-strategy.h"
#include "./import-single-module-declaration-ir-strategy/import-single-module-declaration-ir-strategy.h"
#include "./class-declaration-ir-strategy/class-declaration-ir-strategy.h"
#include "./if-statement-ir-strategy/if-statement-ir-strategy.h"
#include "./while-statement-ir-strategy/while-statement-ir-strategy.h"
#include "./for-in-statement-ir-strategy/for-in-statement-ir-strategy.h"
#include "./type-signature-ir-strategies/array-type-signature-ir-strategy/array-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/literal-type-signature-ir-strategy/literal-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/class-type-signature-ir-strategy/class-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/new-class-instance-type-signature-ir-strategy/new-class-instance-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/class-instance-type-signature-ir-strategy/class-instance-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/enum-type-signature-ir-strategy/enum-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/interface-type-signature-ir-strategy/interface-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/invocable-type-signature-ir-strategies/function-type-signature-ir-strategy/function-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/invocable-type-signature-ir-strategies/lambda-type-signature-ir-strategy/lambda-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/invocable-type-signature-ir-strategies/procedure-type-signature-ir-strategy/procedure-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/parameter-list-type-signature-ir-strategy/parameter-list-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/parameter-list-type-signature-ir-strategy/parameter-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/struct-type-signature-ir-strategy/struct-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/tuple-type-signature-ir-strategy/tuple-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/enum-access-type-signature-ir-strategy/enum-access-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/module-type-signature-ir-strategy/module-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/pointer-type-signature-ir-strategy/pointer-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/shared-type-signature-ir-strategy/shared-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/function-invocation-type-signature-ir-strategy/function-invocation-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/class-method-type-signature-ir-strategy/class-method-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/class-property-type-signature-ir-strategy/class-property-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/lambda-scope-type-signature-ir-strategy/lambda-scope-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/void-type-signature-ir-strategy/void-type-signature-ir-strategy.h"

IRStrategyMap::IRStrategyMap() {
    _intLiteralIRStrategy = std::make_shared<IntLiteralIRStrategy>();
    _floatLiteralIRStrategy = std::make_shared<FloatLiteralIRStrategy>();
    _charLiteralIRStrategy = std::make_shared<CharLiteralIRStrategy>();
    _stringLiteralIRStrategy = std::make_shared<StringLiteralIRStrategy>();
    _boolLiteralIRStrategy = std::make_shared<BoolLiteralIRStrategy>();
    _literalExpressionIRStrategy = std::make_shared<LiteralExpressionIRStrategy>();
    _binaryExpressionIRStrategy = std::make_shared<BinaryExpressionIRStrategy>();
    _concatExpressionIRStrategy = std::make_shared<ConcatExpressionIRStrategy>();
    _logicalExpressionIRStrategy = std::make_shared<LogicalExpressionIRStrategy>();
    _arrayExpressionIRStrategy = std::make_shared<ArrayExpressionIRStrategy>();
    _structExpressionIRStrategy = std::make_shared<StructExpressionIRStrategy>();
    _arrayAccessExpressionIRStrategy = std::make_shared<ArrayAccessExpressionIRStrategy>();
    _arrayAccessInvocationExpressionIRStrategy = std::make_shared<ArrayAccessInvocationExpressionIRStrategy>();
    _unaryExpressionIRStrategy = std::make_shared<UnaryExpressionIRStrategy>();
    _tupleExpressionIRStrategy = std::make_shared<TupleExpressionIRStrategy>();
    _thisExpressionIRStrategy = std::make_shared<ThisExpressionIRStrategy>();
    _identifierExpressionIRStrategy = std::make_shared<IdentifierExpressionIRStrategy>();
    _variableDeclarationIRStrategy = std::make_shared<VariableDeclarationIRStrategy>();
    _functionDeclarationIRStrategy = std::make_shared<FunctionDeclarationIRStrategy>();
    _functionParameterListIRStrategy = std::make_shared<FunctionParameterListIRStrategy>();
    _functionReturnExpressionIRStrategy = std::make_shared<FunctionReturnExpressionIRStrategy>();
    _procedureDeclarationIRStrategy = std::make_shared<ProcedureDeclarationIRStrategy>();
    _enumDeclarationIRStrategy = std::make_shared<EnumDeclarationIRStrategy>();
    _interfaceTypeDeclarationIRStrategy = std::make_shared<InterfaceTypeDeclarationIRStrategy>();
    _customTypeDeclarationIRStrategy = std::make_shared<CustomTypeDeclarationIRStrategy>();
    _moduleDeclarationIRStrategy = std::make_shared<ModuleDeclarationIRStrategy>();
    _importSingleModuleDeclarationIRStrategy = std::make_shared<ImportSingleModuleDeclarationIRStrategy>();
    _objectAccessExpressionIRStrategy = std::make_shared<ObjectAccessExpressionIRStrategy>();
    _objectAccessInvocationExpressionIRStrategy = std::make_shared<ObjectAccessInvocationExpressionIRStrategy>();
    _tupleAccessExpressionIRStrategy = std::make_shared<TupleAccessExpressionIRStrategy>();
    _tupleAccessInvocationExpressionIRStrategy = std::make_shared<TupleAccessInvocationExpressionIRStrategy>();
    _functionInvocationExpressionIRStrategy = std::make_shared<FunctionInvocationExpressionIRStrategy>();
    _lambdaExpressionIRStrategy = std::make_shared<LambdaExpressionIRStrategy>();
    _moduleAccessExpressionIRStrategy = std::make_shared<ModuleAccessExpressionIRStrategy>();
    _expressionStatementIRStrategy = std::make_shared<ExpressionStatementIRStrategy>();
    _classDeclarationIRStrategy = std::make_shared<ClassDeclarationIRStrategy>();
    _classPropertyAccessExpressionIRStrategy = std::make_shared<ClassPropertyAccessExpressionIRStrategy>();
    _classMethodInvocationExpressionIRStrategy = std::make_shared<ClassMethodInvocationExpressionIRStrategy>();
    _newClassInstanceExpressionIRStrategy = std::make_shared<NewClassInstanceExpressionIRStrategy>();
    _classPropertyAssignmentStatementIRStrategy = std::make_shared<ClassPropertyAssignmentStatementIRStrategy>();
    _variableAssignmentStatementIRStrategy = std::make_shared<VariableAssignmentStatementIRStrategy>();
    _arrayAccessAssignmentStatementIRStrategy = std::make_shared<ArrayAccessAssignmentStatementIRStrategy>();
    _arrayAccessSharedValueAssignmentStatementIRStrategy = std::make_shared<ArrayAccessSharedValueAssignmentStatementIRStrategy>();
    _objectAccessAssignmentStatementIRStrategy = std::make_shared<ObjectAccessAssignmentStatementIRStrategy>();
    _objectAccessSharedValueAssignmentStatementIRStrategy = std::make_shared<ObjectAccessSharedValueAssignmentStatementIRStrategy>();
    _tupleAccessAssignmentStatementIRStrategy = std::make_shared<TupleAccessAssignmentStatementIRStrategy>();
    _tupleAccessSharedValueAssignmentStatementIRStrategy = std::make_shared<TupleAccessSharedValueAssignmentStatementIRStrategy>();
    _moduleAccessAssignmentStatementIRStrategy = std::make_shared<ModuleAccessAssignmentStatementIRStrategy>();
    _moduleAccessSharedValueAssignmentStatementIRStrategy = std::make_shared<ModuleAccessSharedValueAssignmentStatementIRStrategy>();
    _classPropertySharedValueAssignmentStatementIRStrategy = std::make_shared<ClassPropertySharedValueAssignmentStatementIRStrategy>();
    _sharedValueAssignmentStatementIRStrategy = std::make_shared<SharedValueAssignmentStatementIRStrategy>();
    _ifStatementIRStrategy = std::make_shared<IfStatementIRStrategy>();
    _whileStatementIRStrategy = std::make_shared<WhileStatementIRStrategy>();
    _forInStatementIRStrategy = std::make_shared<ForInStatementIRStrategy>();
    _shareExpressionIRStrategy = std::make_shared<ShareExpressionIRStrategy>();
    _drefExpressionIRStrategy = std::make_shared<DrefExpressionIRStrategy>();

    _arrayTypeSignatureIRStrategy = std::make_shared<ArrayTypeSignatureIRStrategy>();
    _literalTypeSignatureIRStrategy = std::make_shared<LiteralTypeSignatureIRStrategy>();
    _classTypeSignatureIRStrategy = std::make_shared<ClassTypeSignatureIRStrategy>();
    _enumTypeSignatureIRStrategy = std::make_shared<EnumTypeSignatureIRStrategy>();
    _interfaceTypeSignatureIRStrategy = std::make_shared<InterfaceTypeSignatureIRStrategy>();
    _functionTypeSignatureIRStrategy = std::make_shared<FunctionTypeSignatureIRStrategy>();
    _lambdaTypeSignatureIRStrategy = std::make_shared<LambdaTypeSignatureIRStrategy>();
    _procedureTypeSignatureIRStrategy = std::make_shared<ProcedureTypeSignatureIRStrategy>();
    _parameterListTypeSignatureIRStrategy = std::make_shared<ParameterListTypeSignatureIRStrategy>();
    _parameterTypeSignatureIRStrategy = std::make_shared<ParameterTypeSignatureIRStrategy>();
    _structTypeSignatureIRStrategy = std::make_shared<StructTypeSignatureIRStrategy>();
    _tupleTypeSignatureIRStrategy = std::make_shared<TupleTypeSignatureIRStrategy>();
    _enumAccessTypeSignatureIRStrategy = std::make_shared<EnumAccessTypeSignatureIRStrategy>();
    _moduleTypeSignatureStrategy = std::make_shared<ModuleTypeSignatureIRStrategy>();
    _pointerTypeSignatureStrategy = std::make_shared<PointerTypeSignatureIRStrategy>();
    _sharedTypeSignatureStrategy = std::make_shared<SharedTypeSignatureIRStrategy>();
    _functionInvocationTypeSignatureIRStrategy = std::make_shared<FunctionInvocationTypeSignatureIRStrategy>();
    _classMethodTypeSignatureIRStrategy = std::make_shared<ClassMethodTypeSignatureIRStrategy>();
    _classPropertyTypeSignatureIRStrategy = std::make_shared<ClassPropertyTypeSignatureIRStrategy>();
    _newClassInstanceTypeSignatureIRStrategy = std::make_shared<NewClassInstanceTypeSignatureIRStrategy>();
    _classInstanceTypeSignatureIRStrategy = std::make_shared<ClassInstanceTypeSignatureIRStrategy>();
    _lambdaScopeTypeSignatureIRStrategy = std::make_shared<LambdaScopeTypeSignatureIRStrategy>();
    _voidTypeSignatureIRStrategy = std::make_shared<VoidTypeSignatureIRStrategy>();
}

std::shared_ptr<IntLiteralIRStrategy> IRStrategyMap::getIntLiteralIRStrategy() {
    return _intLiteralIRStrategy;
}

std::shared_ptr<FloatLiteralIRStrategy> IRStrategyMap::getFloatLiteralIRStrategy() {
    return _floatLiteralIRStrategy;
}

std::shared_ptr<CharLiteralIRStrategy> IRStrategyMap::getCharLiteralIRStrategy() {
    return _charLiteralIRStrategy;
}

std::shared_ptr<StringLiteralIRStrategy> IRStrategyMap::getStringLiteralIRStrategy() {
    return _stringLiteralIRStrategy;
}

std::shared_ptr<BoolLiteralIRStrategy> IRStrategyMap::getBoolLiteralIRStrategy() {
    return _boolLiteralIRStrategy;
}

std::shared_ptr<LiteralExpressionIRStrategy> IRStrategyMap::getLiteralExpressionIRStrategy() {
    return _literalExpressionIRStrategy;
}

std::shared_ptr<BinaryExpressionIRStrategy> IRStrategyMap::getBinaryExpressionIRStrategy() {
    return _binaryExpressionIRStrategy;
}

std::shared_ptr<ConcatExpressionIRStrategy> IRStrategyMap::getConcatExpressionIRStrategy() {
    return _concatExpressionIRStrategy;
}

std::shared_ptr<LogicalExpressionIRStrategy> IRStrategyMap::getLogicalExpressionIRStrategy() {
    return _logicalExpressionIRStrategy;
}

std::shared_ptr<ArrayExpressionIRStrategy> IRStrategyMap::getArrayExpressionIRStrategy() {
    return _arrayExpressionIRStrategy;
}

std::shared_ptr<ArrayAccessExpressionIRStrategy> IRStrategyMap::getArrayAccessExpressionIRStrategy() {
    return _arrayAccessExpressionIRStrategy;
}

std::shared_ptr<ArrayAccessInvocationExpressionIRStrategy> IRStrategyMap::getArrayAccessInvocationExpressionIRStrategy() {
    return _arrayAccessInvocationExpressionIRStrategy;
}

std::shared_ptr<StructExpressionIRStrategy> IRStrategyMap::getStructExpressionIRStrategy() {
    return _structExpressionIRStrategy;
}

std::shared_ptr<UnaryExpressionIRStrategy> IRStrategyMap::getUnaryExpressionIRStrategy() {
    return _unaryExpressionIRStrategy;
}

std::shared_ptr<TupleExpressionIRStrategy> IRStrategyMap::getTupleExpressionIRStrategy() {
    return _tupleExpressionIRStrategy;
}

std::shared_ptr<ThisExpressionIRStrategy> IRStrategyMap::getThisExpressionIRStrategy() {
    return _thisExpressionIRStrategy;
}

std::shared_ptr<IdentifierExpressionIRStrategy> IRStrategyMap::getIdentifierExpressionIRStrategy() {
    return _identifierExpressionIRStrategy;
}

std::shared_ptr<VariableDeclarationIRStrategy> IRStrategyMap::getVariableDeclarationIRStrategy() {
    return _variableDeclarationIRStrategy;
}

std::shared_ptr<FunctionDeclarationIRStrategy> IRStrategyMap::getFunctionDeclarationIRStrategy() {
    return _functionDeclarationIRStrategy;
}

std::shared_ptr<FunctionParameterListIRStrategy> IRStrategyMap::getFunctionParameterListIRStrategy() {
    return _functionParameterListIRStrategy;
}

std::shared_ptr<FunctionReturnExpressionIRStrategy> IRStrategyMap::getFunctionReturnExpressionIRStrategy() {
    return _functionReturnExpressionIRStrategy;
}

std::shared_ptr<ProcedureDeclarationIRStrategy> IRStrategyMap::getProcedureDeclarationIRStrategy() {
    return _procedureDeclarationIRStrategy;
}

std::shared_ptr<EnumDeclarationIRStrategy> IRStrategyMap::getEnumDeclarationIRStrategy() {
    return _enumDeclarationIRStrategy;
}

std::shared_ptr<InterfaceTypeDeclarationIRStrategy> IRStrategyMap::getInterfaceTypeDeclarationIRStrategy() {
    return _interfaceTypeDeclarationIRStrategy;
}

std::shared_ptr<CustomTypeDeclarationIRStrategy> IRStrategyMap::getCustomTypeDeclarationIRStrategy() {
    return _customTypeDeclarationIRStrategy;
}

std::shared_ptr<ModuleDeclarationIRStrategy> IRStrategyMap::getModuleDeclarationIRStrategy() {
    return _moduleDeclarationIRStrategy;
}

std::shared_ptr<ImportSingleModuleDeclarationIRStrategy> IRStrategyMap::getImportSingleModuleDeclarationIRStrategy() {
    return _importSingleModuleDeclarationIRStrategy;
}

std::shared_ptr<ObjectAccessExpressionIRStrategy> IRStrategyMap::getObjectAccessExpressionIRStrategy() {
    return _objectAccessExpressionIRStrategy;
}

std::shared_ptr<ObjectAccessInvocationExpressionIRStrategy> IRStrategyMap::getObjectAccessInvocationExpressionIRStrategy() {
    return _objectAccessInvocationExpressionIRStrategy;
}

std::shared_ptr<TupleAccessExpressionIRStrategy> IRStrategyMap::getTupleAccessExpressionIRStrategy() {
    return _tupleAccessExpressionIRStrategy;
}

std::shared_ptr<TupleAccessInvocationExpressionIRStrategy> IRStrategyMap::getTupleAccessInvocationExpressionIRStrategy() {
    return _tupleAccessInvocationExpressionIRStrategy;
}

std::shared_ptr<FunctionInvocationExpressionIRStrategy> IRStrategyMap::getFunctionInvocationExpressionIRStrategy() {
    return _functionInvocationExpressionIRStrategy;
}

std::shared_ptr<LambdaExpressionIRStrategy> IRStrategyMap::getLambdaExpressionIRStrategy() {
    return _lambdaExpressionIRStrategy;
}

std::shared_ptr<ModuleAccessExpressionIRStrategy> IRStrategyMap::getModuleAccessExpressionIRStrategy() {
    return _moduleAccessExpressionIRStrategy;
}

std::shared_ptr<ExpressionStatementIRStrategy> IRStrategyMap::getExpressionStatementIRStrategy() {
    return _expressionStatementIRStrategy;
}

std::shared_ptr<ClassDeclarationIRStrategy> IRStrategyMap::getClassDeclarationIRStrategy() {
    return _classDeclarationIRStrategy;
}

std::shared_ptr<ClassPropertyAccessExpressionIRStrategy> IRStrategyMap::getClassPropertyAccessExpressionIRStrategy() {
    return _classPropertyAccessExpressionIRStrategy;
}

std::shared_ptr<ClassMethodInvocationExpressionIRStrategy> IRStrategyMap::getClassMethodInvocationExpressionIRStrategy() {
    return _classMethodInvocationExpressionIRStrategy;
}

std::shared_ptr<NewClassInstanceExpressionIRStrategy> IRStrategyMap::getNewClassInstanceExpressionIRStrategy() {
    return _newClassInstanceExpressionIRStrategy;
}

std::shared_ptr<ClassPropertyAssignmentStatementIRStrategy> IRStrategyMap::getClassPropertyAssignmentStatementIRStrategy() {
    return _classPropertyAssignmentStatementIRStrategy;
}

std::shared_ptr<VariableAssignmentStatementIRStrategy> IRStrategyMap::getVariableAssignmentStatementIRStrategy() {
    return _variableAssignmentStatementIRStrategy;
}

std::shared_ptr<ArrayAccessAssignmentStatementIRStrategy> IRStrategyMap::getArrayAccessAssignmentStatementIRStrategy() {
    return _arrayAccessAssignmentStatementIRStrategy;
}

std::shared_ptr<ArrayAccessSharedValueAssignmentStatementIRStrategy> IRStrategyMap::getArrayAccessSharedValueAssignmentStatementIRStrategy() {
    return _arrayAccessSharedValueAssignmentStatementIRStrategy;
}

std::shared_ptr<ObjectAccessAssignmentStatementIRStrategy> IRStrategyMap::getObjectAccessAssignmentStatementIRStrategy() {
    return _objectAccessAssignmentStatementIRStrategy;
}

std::shared_ptr<ObjectAccessSharedValueAssignmentStatementIRStrategy> IRStrategyMap::getObjectAccessSharedValueAssignmentStatementIRStrategy() {
    return _objectAccessSharedValueAssignmentStatementIRStrategy;
}

std::shared_ptr<TupleAccessAssignmentStatementIRStrategy> IRStrategyMap::getTupleAccessAssignmentStatementIRStrategy() {
    return _tupleAccessAssignmentStatementIRStrategy;
}

std::shared_ptr<TupleAccessSharedValueAssignmentStatementIRStrategy> IRStrategyMap::getTupleAccessSharedValueAssignmentStatementIRStrategy() {
    return _tupleAccessSharedValueAssignmentStatementIRStrategy;
}

std::shared_ptr<ModuleAccessAssignmentStatementIRStrategy> IRStrategyMap::getModuleAccessAssignmentStatementIRStrategy() {
    return _moduleAccessAssignmentStatementIRStrategy;
}

std::shared_ptr<ModuleAccessSharedValueAssignmentStatementIRStrategy> IRStrategyMap::getModuleAccessSharedValueAssignmentStatementIRStrategy() {
    return _moduleAccessSharedValueAssignmentStatementIRStrategy;
}

std::shared_ptr<ClassPropertySharedValueAssignmentStatementIRStrategy> IRStrategyMap::getClassPropertySharedValueAssignmentStatementIRStrategy() {
    return _classPropertySharedValueAssignmentStatementIRStrategy;
}

std::shared_ptr<SharedValueAssignmentStatementIRStrategy> IRStrategyMap::getSharedValueAssignmentStatementIRStrategy() {
    return _sharedValueAssignmentStatementIRStrategy;
}

std::shared_ptr<IfStatementIRStrategy> IRStrategyMap::getIfStatementIRStrategy() {
    return _ifStatementIRStrategy;
}

std::shared_ptr<WhileStatementIRStrategy> IRStrategyMap::getWhileStatementIRStrategy() {
    return _whileStatementIRStrategy;
}

std::shared_ptr<ForInStatementIRStrategy> IRStrategyMap::getForInStatementIRStrategy() {
    return _forInStatementIRStrategy;
}

std::shared_ptr<ShareExpressionIRStrategy> IRStrategyMap::getShareExpressionIRStrategy() {
    return _shareExpressionIRStrategy;
}

std::shared_ptr<DrefExpressionIRStrategy> IRStrategyMap::getDrefExpressionIRStrategy() {
    return _drefExpressionIRStrategy;
}

std::shared_ptr<ArrayTypeSignatureIRStrategy> IRStrategyMap::getArrayTypeSignatureIRStrategy() {
    return _arrayTypeSignatureIRStrategy;
}

std::shared_ptr<LiteralTypeSignatureIRStrategy> IRStrategyMap::getLiteralTypeSignatureIRStrategy() {
    return _literalTypeSignatureIRStrategy;
}

std::shared_ptr<ClassTypeSignatureIRStrategy> IRStrategyMap::getClassTypeSignatureIRStrategy() {
    return _classTypeSignatureIRStrategy;
}

std::shared_ptr<EnumTypeSignatureIRStrategy> IRStrategyMap::getEnumTypeSignatureIRStrategy() {
    return _enumTypeSignatureIRStrategy;
}

std::shared_ptr<InterfaceTypeSignatureIRStrategy> IRStrategyMap::getInterfaceTypeSignatureIRStrategy() {
    return _interfaceTypeSignatureIRStrategy;
}

std::shared_ptr<FunctionTypeSignatureIRStrategy> IRStrategyMap::getFunctionTypeSignatureIRStrategy() {
    return _functionTypeSignatureIRStrategy;
}

std::shared_ptr<LambdaTypeSignatureIRStrategy> IRStrategyMap::getLambdaTypeSignatureIRStrategy() {
    return _lambdaTypeSignatureIRStrategy;
}

std::shared_ptr<ProcedureTypeSignatureIRStrategy> IRStrategyMap::getProcedureTypeSignatureIRStrategy() {
    return _procedureTypeSignatureIRStrategy;
}

std::shared_ptr<ParameterListTypeSignatureIRStrategy> IRStrategyMap::getParameterListTypeSignatureIRStrategy() {
    return _parameterListTypeSignatureIRStrategy;
}

std::shared_ptr<ParameterTypeSignatureIRStrategy> IRStrategyMap::getParameterTypeSignatureIRStrategy() {
    return _parameterTypeSignatureIRStrategy;
}

std::shared_ptr<StructTypeSignatureIRStrategy> IRStrategyMap::getStructTypeSignatureIRStrategy() {
    return _structTypeSignatureIRStrategy;
}

std::shared_ptr<TupleTypeSignatureIRStrategy> IRStrategyMap::getTupleTypeSignatureIRStrategy() {
    return _tupleTypeSignatureIRStrategy;
}

std::shared_ptr<EnumAccessTypeSignatureIRStrategy> IRStrategyMap::getEnumAccessTypeSignatureIRStrategy() {
    return _enumAccessTypeSignatureIRStrategy;
}

std::shared_ptr<ModuleTypeSignatureIRStrategy> IRStrategyMap::getModuleTypeSignatureIRStrategy() {
    return _moduleTypeSignatureStrategy;
}

std::shared_ptr<PointerTypeSignatureIRStrategy> IRStrategyMap::getPointerTypeSignatureIRStrategy() {
    return _pointerTypeSignatureStrategy;
}

std::shared_ptr<SharedTypeSignatureIRStrategy> IRStrategyMap::getSharedTypeSignatureIRStrategy() {
    return _sharedTypeSignatureStrategy;
}

std::shared_ptr<FunctionInvocationTypeSignatureIRStrategy> IRStrategyMap::getFunctionInvocationTypeSignatureIRStrategy() {
    return _functionInvocationTypeSignatureIRStrategy;
}

std::shared_ptr<ClassMethodTypeSignatureIRStrategy> IRStrategyMap::getClassMethodTypeSignatureIRStrategy() {
    return _classMethodTypeSignatureIRStrategy;
}

std::shared_ptr<ClassPropertyTypeSignatureIRStrategy> IRStrategyMap::getClassPropertyTypeSignatureIRStrategy() {
    return _classPropertyTypeSignatureIRStrategy;
}

std::shared_ptr<NewClassInstanceTypeSignatureIRStrategy> IRStrategyMap::getNewClassInstanceTypeSignatureIRStrategy() {
    return _newClassInstanceTypeSignatureIRStrategy;
}

std::shared_ptr<ClassInstanceTypeSignatureIRStrategy> IRStrategyMap::getClassInstanceTypeSignatureIRStrategy() {
    return _classInstanceTypeSignatureIRStrategy;
}

std::shared_ptr<LambdaScopeTypeSignatureIRStrategy> IRStrategyMap::getLambdaScopeTypeSignatureIRStrategy() {
    return _lambdaScopeTypeSignatureIRStrategy;
}

std::shared_ptr<VoidTypeSignatureIRStrategy> IRStrategyMap::getVoidTypeSignatureIRStrategy() {
    return _voidTypeSignatureIRStrategy;
}