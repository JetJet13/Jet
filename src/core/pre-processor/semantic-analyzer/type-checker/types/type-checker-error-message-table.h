//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
#define JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H

using ErrorMessageLambda = std::function<std::string()>;

namespace TypeCheckerErrorMessageTable {
    static ErrorMessageLambda VariableTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return  "variable type does not match initializer type \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda VariableTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return  "variable type is unknown \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda VariableTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return  "variable type is invalid \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda VariableTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return  "variable type cannot be void \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda VariableAssignmentTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return  "variable type does not match expression type \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ProcedureHasReturnExpression(ASTNode* node) {
      return [node]() -> std::string { return  "procedure cannot have return expression \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ParameterTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return  "parameter type is unknown \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ParameterTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return  "parameter type is invalid \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ParameterTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return  "parameter type cannot be void \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda FunctionReturnTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return  "function return type is unknown \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda FunctionReturnTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return  "function return type is invalid \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda FunctionReturnTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return  "function return type cannot be void \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda FunctionNotAllPathsReturn(ASTNode* node) {
      return [node]() -> std::string { return  "not all function paths return a value \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda FunctionReturnExpressionMismatch(ASTNode* node) {
      return [node]() -> std::string { return  "return expression type does not match function return type \n" + node->toSourceCode(); };
    } 
    static std::function<std::string()> ExpressionTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return  "expression type is unknown \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ExpressionTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return  "expression type is invalid \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ExpressionTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return  "expression type cannot be void \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda EnumKeyValueTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return  "enum key-value type does not match enum type \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ControlFlowConditionNotBool(ASTNode* node) {
      return [node]() -> std::string { return  "condition must evaluate to true or false \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ForInStatementSourceNotIterable(ASTNode* node) {
      return [node]() -> std::string { return  "source of for-in loop is not iterable \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassPropertyTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return  "class property type is unknown \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassPropertyTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return  "class property type is invalid \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassPropertyTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return  "class property type cannot be void \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassPropertyAssignmentTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return  "class property type does not match expression type \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassPropertyInitializerTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return  "type of initial value for class property does not match class property type \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda ClassPropertyInvocable(ASTNode* node) {
      return [node]() -> std::string { return  "class property cannot be invocable. Convert to class method instead \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda ClassPropertyNamesNotUnique(ASTNode* node) {
      return [node]() -> std::string { return  "class property names must be unique \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassMethodNamesAndTypeSignaturesNotUnique(ASTNode* node) {
      return [node]() -> std::string { return  "one or more class methods have the same name and type-signature \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassConstructorsNotUnique(ASTNode* node) {
      return [node]() -> std::string { return  "class constructors must have unique parameter lists \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda ClassConstructorHasReturnExpression(ASTNode* node) {
      return [node]() -> std::string { return  "class constructor cannot have return expression \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda ClassMethodReturnTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return  "class method return type is unknown \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassMethodReturnTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return  "class method return type is invalid \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassMethodReturnTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return  "class method return type cannot be void \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassMethodNotAllPathsReturn(ASTNode* node) {
      return [node]() -> std::string { return  "not all class method paths return a value \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda ClassMethodHasReturnExpression(ASTNode* node) {
      return [node]() -> std::string { return  "class method cannot have return expression \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda ClassDoesNotImplementInterface(ASTNode* node) {
      return [node]() -> std::string { return  "class does not satisfy interface it declared to implement \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda ArrayElementTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return  "not all array elements match the array element type \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassMethodCallNotEnoughArguments(ASTNode* node) {
      return [node]() -> std::string { return  "not enough arguments provided for class method call \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassMethodCallTooManyArguments(ASTNode* node) {
      return [node]() -> std::string { return  "too many arguments provided for class method call \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda ClassMethodCallArgumentTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return  "argument type does not match parameter type for class method call \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda NotCallableCurryType(ASTNode* node) {
      return [node]() -> std::string { return  "curry function type is not callable \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda CurryCallNotEnoughArguments(ASTNode* node) {
      return [node]() -> std::string { return  "not enough arguments provided for curry call \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda CurryCallTooManyArguments(ASTNode* node) {
      return [node]() -> std::string { return  "too many arguments provided for curry call \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda CurryCallArgumentTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return  "argument type does not match parameter type for curry call \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda FunctionCallNotEnoughArguments(ASTNode* node) {
      return [node]() -> std::string { return  "not enough arguments provided for function call \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda FunctionCallTooManyArguments(ASTNode* node) {
      return [node]() -> std::string { return  "too many arguments provided for function call \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda FunctionCallArgumentTypeMismatch(ASTNode* node) {
      return [node]() -> std::string { return  "argument type does not match parameter type for function call \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda LambdaExpressionReturnTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return  "lambda expression return type is unknown \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda LambdaExpressionReturnTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return  "lambda expression return type is invalid \n" + node->toSourceCode(); };
    } 
    static ErrorMessageLambda LambdaExpressionNotAllPathsReturn(ASTNode* node) {
      return [node]() -> std::string { return  "not all lambda expression paths return a value \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda LambdaExpressionHasReturnExpression(ASTNode* node) {
      return [node]() -> std::string { return  "lambda expression cannot have return expression \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda NewClassInstanceNotClassType(ASTNode* node) {
      return [node]() -> std::string { return  "cannot instantiate new class instance since type is not a class type \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda NewClassInstanceNoMatchingConstructor(ASTNode* node) {
      return [node]() -> std::string { return  "cannot instantiate new class instance since no constructor found for arguments provided \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda VariableNamesNotUnique(ASTNode* node) {
      return [node]() -> std::string { return  "variable name must be unique \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda InvalidSingleImportModuleName(ASTNode* node) {
      return [node]() -> std::string { return  "imported module name is invalid \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda DrefExpressionTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return  "dref expression does not have type ref/pointer  \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda SrefExpressionTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return  "sref expression does not have type ref/pointer  \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda RefExpressionTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return  "ref expression cannot have type ref/pointer  \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda InterfacePropertyTypeUnknown(ASTNode* node) {
      return [node]() -> std::string { return  "interface property type is unknown \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda InterfacePropertyTypeInvalid(ASTNode* node) {
      return [node]() -> std::string { return  "interface property type is invalid \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda InterfacePropertyTypeVoid(ASTNode* node) {
      return [node]() -> std::string { return  "interface property type cannot be void \n" + node->toSourceCode(); };
    }
    static ErrorMessageLambda InterfacePropertyNamesNotUnique(ASTNode* node) {
      return [node]() -> std::string { return  "interface property names must be unique \n" + node->toSourceCode(); };
    }
}

#endif //JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
