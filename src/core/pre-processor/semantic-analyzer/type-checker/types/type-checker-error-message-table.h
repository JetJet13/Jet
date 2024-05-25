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
    static const auto ProcedureHasReturnExpression = "procedure cannot have return expression";
}

#endif //JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
