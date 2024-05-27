//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
#define JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H

namespace TypeCheckerErrorMessageTable {
    static const auto VariableTypeMismatch = "variable type does not match initializer type";
    static const auto VariableTypeUnknown = "variable type is unknown";
    static const auto VariableTypeInvalid = "variable type is invalid";
    static const auto VariableTypeVoid = "variable type cannot be void";
    static const auto VariableAssignmentTypeMismatch = "variable type does not match expression type";
    static const auto ProcedureHasReturnExpression = "procedure cannot have return expression";
    static const auto ParameterTypeUnknown = "parameter type is unknown";
    static const auto ParameterTypeInvalid = "parameter type is invalid";
    static const auto ParameterTypeVoid = "parameter type cannot be void";
    static const auto FunctionReturnTypeUnknown = "function return type is unknown";
    static const auto FunctionReturnTypeInvalid = "function return type is invalid";
    static const auto FunctionReturnTypeVoid = "function return type cannot be void";
    static const auto FunctionNotAllPathsReturn = "not all function paths return a value";
    static const auto FunctionReturnExpressionMismatch = "return expression type does not match function return type";
    static const auto ExpressionTypeUnknown = "expression type is unknown";
    static const auto ExpressionTypeInvalid = "expression type is invalid";
    static const auto ExpressionTypeVoid = "expression type cannot be void";
    static const auto EnumKeyValueTypeMismatch = "enum key-value type does not match enum type";
    static const auto ControlFlowConditionNotBool = "condition must evaluate to true or false";
    static const auto ForStatementSourceNotIterable = "source of for-loop is not iterable";
}

#endif //JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
