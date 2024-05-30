//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
#define JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H

namespace TypeCheckerErrorMessageTable {
    static std::string VariableTypeMismatch(Lexeme* lexeme) {
      return "variable type does not match initializer type" + lexeme->toString();  
    } 
    static std::string VariableTypeUnknown(Lexeme* lexeme) {
      return "variable type is unknown" + lexeme->toString();  
    } 
    static std::string VariableTypeInvalid(Lexeme* lexeme) {
      return "variable type is invalid" + lexeme->toString();  
    } 
    static std::string VariableTypeVoid(Lexeme* lexeme) {
      return "variable type cannot be void" + lexeme->toString();  
    } 
    static std::string VariableAssignmentTypeMismatch(Lexeme* lexeme) {
      return "variable type does not match expression type" + lexeme->toString();  
    } 
    static std::string ProcedureHasReturnExpression(Lexeme* lexeme) {
      return "procedure cannot have return expression" + lexeme->toString();  
    } 
    static std::string ParameterTypeUnknown(Lexeme* lexeme) {
      return "parameter type is unknown" + lexeme->toString();  
    } 
    static std::string ParameterTypeInvalid(Lexeme* lexeme) {
      return "parameter type is invalid" + lexeme->toString();  
    } 
    static std::string ParameterTypeVoid(Lexeme* lexeme) {
      return "parameter type cannot be void" + lexeme->toString();  
    } 
    static std::string FunctionReturnTypeUnknown(Lexeme* lexeme) {
      return "function return type is unknown" + lexeme->toString();  
    } 
    static std::string FunctionReturnTypeInvalid(Lexeme* lexeme) {
      return "function return type is invalid" + lexeme->toString();  
    } 
    static std::string FunctionReturnTypeVoid(Lexeme* lexeme) {
      return "function return type cannot be void" + lexeme->toString();  
    } 
    static std::string FunctionNotAllPathsReturn(Lexeme* lexeme) {
      return "not all function paths return a value" + lexeme->toString();  
    } 
    static std::string FunctionReturnExpressionMismatch(Lexeme* lexeme) {
      return "return expression type does not match function return type" + lexeme->toString();  
    } 
    static std::string ExpressionTypeUnknown(Lexeme* lexeme) {
      return "expression type is unknown" + lexeme->toString();  
    } 
    static std::string ExpressionTypeInvalid(Lexeme* lexeme) {
      return "expression type is invalid" + lexeme->toString();  
    } 
    static std::string ExpressionTypeVoid(Lexeme* lexeme) {
      return "expression type cannot be void" + lexeme->toString();  
    } 
    static std::string EnumKeyValueTypeMismatch(Lexeme* lexeme) {
      return "enum key-value type does not match enum type" + lexeme->toString();  
    } 
    static std::string ControlFlowConditionNotBool(Lexeme* lexeme) {
      return "condition must evaluate to true or false" + lexeme->toString();  
    } 
    static std::string ForStatementSourceNotIterable(Lexeme* lexeme) {
      return "source of for-loop is not iterable" + lexeme->toString();  
    } 
    static std::string ClassPropertyTypeUnknown(Lexeme* lexeme) {
      return "class property type is unknown" + lexeme->toString();  
    } 
    static std::string ClassPropertyTypeInvalid(Lexeme* lexeme) {
      return "class property type is invalid" + lexeme->toString();  
    } 
    static std::string ClassPropertyTypeVoid(Lexeme* lexeme) {
      return "class property type cannot be void" + lexeme->toString();  
    } 
    static std::string ClassPropertyAssignmentTypeMismatch(Lexeme* lexeme) {
      return "class property type does not match expression type" + lexeme->toString();  
    } 
    static std::string ClassPropertyInitializerTypeMismatch(Lexeme* lexeme) {
      return "type of initial value for class property does not match class property type" + lexeme->toString();  
    } 
    static std::string ClassPropertyNamesNotUnique(Lexeme* lexeme) {
      return "class property names must be unique" + lexeme->toString();  
    } 
    static std::string ClassMethodNamesAndTypeSignaturesNotUnique(Lexeme* lexeme) {
      return "one or more class methods have the same name and type-signature" + lexeme->toString();  
    } 
    static std::string ClassConstructorsNotUnique(Lexeme* lexeme) {
      return "class constructors must have unique parameter lists" + lexeme->toString();  
    }
    static std::string ClassConstructorHasReturnExpression(Lexeme* lexeme) {
        return "class constructor cannot have return expression" + lexeme->toString();
    }
    static std::string ClassMethodReturnTypeUnknown(Lexeme* lexeme) {
      return "class method return type is unknown" + lexeme->toString();  
    } 
    static std::string ClassMethodReturnTypeInvalid(Lexeme* lexeme) {
      return "class method return type is invalid" + lexeme->toString();  
    } 
    static std::string ClassMethodReturnTypeVoid(Lexeme* lexeme) {
      return "class method return type cannot be void" + lexeme->toString();  
    } 
    static std::string ClassMethodNotAllPathsReturn(Lexeme* lexeme) {
      return "not all class method paths return a value" + lexeme->toString();  
    }
    static std::string ClassMethodHasReturnExpression(Lexeme* lexeme) {
        return "class method cannot have return expression" + lexeme->toString();
    }
    static std::string ArrayElementTypeMismatch(Lexeme* lexeme) {
      return "not all array elements match the array element type" + lexeme->toString();  
    } 
    static std::string ClassMethodCallNotEnoughArguments(Lexeme* lexeme) {
      return "not enough arguments provided for class method call" + lexeme->toString();  
    } 
    static std::string ClassMethodCallTooManyArguments(Lexeme* lexeme) {
      return "too many arguments provided for class method call" + lexeme->toString();  
    } 
    static std::string ClassMethodCallArgumentTypeMismatch(Lexeme* lexeme) {
      return "argument type does not match parameter type for class method call" + lexeme->toString();  
    } 
    static std::string NotCallableCurryType(Lexeme* lexeme) {
      return "curry function type is not callable" + lexeme->toString();  
    } 
    static std::string CurryCallNotEnoughArguments(Lexeme* lexeme) {
      return "not enough arguments provided for curry call" + lexeme->toString();  
    } 
    static std::string CurryCallTooManyArguments(Lexeme* lexeme) {
      return "too many arguments provided for curry call" + lexeme->toString();  
    } 
    static std::string CurryCallArgumentTypeMismatch(Lexeme* lexeme) {
      return "argument type does not match parameter type for curry call" + lexeme->toString();  
    } 
    static std::string FunctionCallNotEnoughArguments(Lexeme* lexeme) {
      return "not enough arguments provided for function call" + lexeme->toString();  
    } 
    static std::string FunctionCallTooManyArguments(Lexeme* lexeme) {
      return "too many arguments provided for function call" + lexeme->toString();  
    } 
    static std::string FunctionCallArgumentTypeMismatch(Lexeme* lexeme) {
      return "argument type does not match parameter type for function call" + lexeme->toString();  
    } 
    static std::string LambdaExpressionReturnTypeUnknown(Lexeme* lexeme) {
      return "lambda expression return type is unknown" + lexeme->toString();  
    } 
    static std::string LambdaExpressionReturnTypeInvalid(Lexeme* lexeme) {
      return "lambda expression return type is invalid" + lexeme->toString();  
    } 
    static std::string LambdaExpressionNotAllPathsReturn(Lexeme* lexeme) {
      return "not all lambda expression paths return a value" + lexeme->toString();  
    }
    static std::string LambdaExpressionHasReturnExpression(Lexeme* lexeme) {
        return "lambda expression cannot have return expression" + lexeme->toString();
    }
    static std::string NewClassInstanceNotClassType(Lexeme* lexeme) {
      return "cannot instantiate new class instance since type is not a class type" + lexeme->toString();  
    }
    // todo: figure out how to have a function return a function that takes a lexeme as a parameter
    // and returns a string (a closure)
    static std::string VariableNamesNotUnique(Lexeme* lexeme) {
      return "variable name must be unique" + lexeme->toString();
    } 
}

#endif //JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
