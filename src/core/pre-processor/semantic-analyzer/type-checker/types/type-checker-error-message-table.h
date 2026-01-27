//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
#define JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H

#include <functional>

using ErrorMessageLambda = std::function<std::string()>;

namespace TypeCheckerErrorMessageTable {
    static std::string generateMessage(ASTNode* node, std::string message) {
        return "(" + node->getLineColumn() + ") - " + message + "\n" + node->toSourceCode() + "\n";
    }
    static ErrorMessageLambda GlobalVariableNameConflictsWithBuiltInFunctionName(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "global variable name conflicts with built-in function"); };
    }
    static ErrorMessageLambda FunctionNameConflictsWithBuiltInFunctionName(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "function name conflicts with built-in function"); };
    }
    static ErrorMessageLambda ProcedureNameConflictsWithBuiltInFunctionName(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "procedure name conflicts with built-in function"); };
    }
    static ErrorMessageLambda VariableTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "variable type does not match initializer type"); };
    } 
    static ErrorMessageLambda VariableTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "variable type is unknown");  };
    } 
    static ErrorMessageLambda VariableTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "variable type is invalid");  };
    } 
    static ErrorMessageLambda VariableTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "variable type cannot be void");  };
    }

    static ErrorMessageLambda VariableAssignmentTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "variable type does not match expression type");  };
    } 
    static ErrorMessageLambda ProcedureHasReturnExpression(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "procedure cannot have return expression");  };
    } 
    static ErrorMessageLambda ParameterTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "parameter type is unknown"); };
    } 
    static ErrorMessageLambda ParameterTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "parameter type is invalid"); };
    } 
    static ErrorMessageLambda ParameterTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "parameter type cannot be void"); };
    } 
    static ErrorMessageLambda FunctionReturnTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "function return type is unknown"); };
    } 
    static ErrorMessageLambda FunctionReturnTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "function return type is invalid"); };
    } 
    static ErrorMessageLambda FunctionReturnTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "function return type cannot be void. Create a procedure instead."); };
    } 
    static ErrorMessageLambda FunctionNotAllPathsReturn(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "not all function paths return a value"); };
    } 
    static ErrorMessageLambda FunctionReturnExpressionMismatch(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "return expression type does not match function return type"); };
    } 
    static std::function<std::string()> ExpressionTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "expression type is unknown"); };
    } 
    static ErrorMessageLambda ExpressionTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "expression type is invalid"); };
    } 
    static ErrorMessageLambda ExpressionTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "expression type cannot be void"); };
    } 
    static ErrorMessageLambda EnumKeyValueTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "enum key-value type does not match enum type"); };
    } 
    static ErrorMessageLambda ControlFlowConditionNotBool(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "condition must evaluate to true or false"); };
    } 
    static ErrorMessageLambda ForInStatementSourceNotIterable(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "source of for-in loop is not iterable"); };
    }
    static ErrorMessageLambda NotInvocable(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "not invocable"); };
    }
    static ErrorMessageLambda ClassPropertyTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class property type is unknown"); };
    } 
    static ErrorMessageLambda ClassPropertyTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class property type is invalid"); };
    } 
    static ErrorMessageLambda ClassPropertyTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class property type cannot be void"); };
    } 
    static ErrorMessageLambda ClassPropertyAssignmentTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class property type does not match expression type"); };
    } 
    static ErrorMessageLambda ClassPropertyInitializerTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "type of initial value for class property does not match class property type"); };
    }
    static ErrorMessageLambda ClassPropertyInvocable(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class property cannot be invocable. Convert to class method instead"); };
    }
    static ErrorMessageLambda ClassPropertyNamesNotUnique(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class property names must be unique"); };
    } 
    static ErrorMessageLambda ClassMethodNamesAndTypeSignaturesNotUnique(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "one or more class methods have the same name and type-signature"); };
    } 
    static ErrorMessageLambda ClassConstructorsNotUnique(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class constructors must have unique parameter lists"); };
    }
    static ErrorMessageLambda ClassConstructorHasReturnExpression(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class constructor cannot have return expression"); };
    }
    static ErrorMessageLambda ClassMethodReturnTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class method return type is unknown"); };
    } 
    static ErrorMessageLambda ClassMethodReturnTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class method return type is invalid"); };
    } 
    static ErrorMessageLambda ClassMethodReturnTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class method return type cannot be void"); };
    } 
    static ErrorMessageLambda ClassMethodNotAllPathsReturn(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "not all class method paths return a value"); };
    }
    static ErrorMessageLambda ClassMethodHasReturnExpression(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class method cannot have return expression"); };
    }
    static ErrorMessageLambda ClassDoesNotImplementInterface(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "class does not satisfy interface it declared to implement"); };
    }
    static ErrorMessageLambda ArrayElementTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "not all array elements match the array element type"); };
    } 
    static ErrorMessageLambda ClassMethodCallNotEnoughArguments(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "not enough arguments provided for class method call"); };
    } 
    static ErrorMessageLambda ClassMethodCallTooManyArguments(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "too many arguments provided for class method call"); };
    } 
    static ErrorMessageLambda ClassMethodCallArgumentTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "argument type does not match parameter type for class method call"); };
    } 
    static ErrorMessageLambda NotCallableCurryType(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "curry function type is not callable"); };
    } 
    static ErrorMessageLambda CurryCallNotEnoughArguments(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "not enough arguments provided for curry call"); };
    } 
    static ErrorMessageLambda CurryCallTooManyArguments(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "too many arguments provided for curry call"); };
    } 
    static ErrorMessageLambda CurryCallArgumentTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "argument type does not match parameter type for curry call"); };
    } 
    static ErrorMessageLambda FunctionCallNotEnoughArguments(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "not enough arguments provided for function call"); };
    } 
    static ErrorMessageLambda FunctionCallTooManyArguments(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "too many arguments provided for function call"); };
    } 
    static ErrorMessageLambda FunctionCallArgumentTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "argument type does not match parameter type for function call"); };
    } 
    static ErrorMessageLambda LambdaExpressionReturnTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "lambda expression return type is unknown"); };
    } 
    static ErrorMessageLambda LambdaExpressionReturnTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "lambda expression return type is invalid"); };
    } 
    static ErrorMessageLambda LambdaExpressionNotAllPathsReturn(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "not all lambda expression paths return a value"); };
    }
    static ErrorMessageLambda LambdaExpressionHasReturnExpression(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "lambda expression cannot have return expression"); };
    }
    static ErrorMessageLambda NewClassInstanceNotClassType(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "cannot instantiate new class instance since type is not a class type"); };
    }
    static ErrorMessageLambda NewClassInstanceNoMatchingConstructor(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "cannot instantiate new class instance since no constructor found for arguments provided"); };
    }
    static ErrorMessageLambda VariableNamesNotUnique(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "variable name must be unique"); };
    }
    static ErrorMessageLambda InvalidSingleImportModuleName(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "imported module name is invalid"); };
    }
    static ErrorMessageLambda DrefExpressionTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "dref expression does not have type ref"); };
    }
    static ErrorMessageLambda SrefExpressionTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "sref expression does not have type ref"); };
    }
    static ErrorMessageLambda RefExpressionTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "ref expression cannot have type ref"); };
    }
    static ErrorMessageLambda InterfacePropertyTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "interface property type is unknown"); };
    }
    static ErrorMessageLambda InterfacePropertyTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "interface property type is invalid"); };
    }
    static ErrorMessageLambda InterfacePropertyTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "interface property type cannot be void"); };
    }
    static ErrorMessageLambda InterfacePropertyNamesNotUnique(ASTNode* node) {
      return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "interface property names must be unique"); };
    }
    static ErrorMessageLambda PrintStatementArgumentNotLiteral(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "print argument must be literal (string, bool, char, int or float)"); };
    }
    static ErrorMessageLambda ObjectAccessAssignmentTypeMismatch(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "object property type does not match expression type"); };
    }
    static ErrorMessageLambda TupleAccessAssignmentTypeMismatch(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "tuple property type does not match expression type"); };
    }
    static ErrorMessageLambda ObjectPropertyTypeUnknown(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "object property type is unknown");  };
    }
    static ErrorMessageLambda ObjectPropertyTypeInvalid(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "object property type is invalid");  };
    }
    static ErrorMessageLambda ObjectPropertyTypeVoid(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "object property type cannot be void");  };
    }
    static ErrorMessageLambda ArrayAccessAssignmentTypeMismatch(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "array element type does not match expression type"); };
    }
    static ErrorMessageLambda ArrayElementTypeUnknown(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "array element type is unknown");  };
    }
    static ErrorMessageLambda ArrayElementTypeInvalid(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "array element type is invalid");  };
    }
    static ErrorMessageLambda ArrayElementTypeVoid(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "array element type cannot be void");  };
    }
    static ErrorMessageLambda BinaryExpressionOperandsTypeMismatch(ASTNode* node) {
        return [node]() -> std::string { return TypeCheckerErrorMessageTable::generateMessage(node, "binary expression operand types (left, right) are not equivalent"); };
    }
}

#endif //JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
