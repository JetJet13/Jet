//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
#define JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H

namespace TypeCheckerErrorMessageTable {
    static std::string VariableTypeMismatch(ASTNode* node) {
      return "variable type does not match initializer type \n" + node->toSourceCode();
    } 
    static std::string VariableTypeUnknown(ASTNode* node) {
      return "variable type is unknown \n" + node->toSourceCode();
    } 
    static std::string VariableTypeInvalid(ASTNode* node) {
      return "variable type is invalid \n" + node->toSourceCode();
    } 
    static std::string VariableTypeVoid(ASTNode* node) {
      return "variable type cannot be void \n" + node->toSourceCode();
    } 
    static std::string VariableAssignmentTypeMismatch(ASTNode* node) {
      return "variable type does not match expression type \n" + node->toSourceCode();
    } 
    static std::string ProcedureHasReturnExpression(ASTNode* node) {
      return "procedure cannot have return expression \n" + node->toSourceCode();
    } 
    static std::string ParameterTypeUnknown(ASTNode* node) {
      return "parameter type is unknown \n" + node->toSourceCode();
    } 
    static std::string ParameterTypeInvalid(ASTNode* node) {
      return "parameter type is invalid \n" + node->toSourceCode();
    } 
    static std::string ParameterTypeVoid(ASTNode* node) {
      return "parameter type cannot be void \n" + node->toSourceCode();
    } 
    static std::string FunctionReturnTypeUnknown(ASTNode* node) {
      return "function return type is unknown \n" + node->toSourceCode();
    } 
    static std::string FunctionReturnTypeInvalid(ASTNode* node) {
      return "function return type is invalid \n" + node->toSourceCode();
    } 
    static std::string FunctionReturnTypeVoid(ASTNode* node) {
      return "function return type cannot be void \n" + node->toSourceCode();
    } 
    static std::string FunctionNotAllPathsReturn(ASTNode* node) {
      return "not all function paths return a value \n" + node->toSourceCode();
    } 
    static std::string FunctionReturnExpressionMismatch(ASTNode* node) {
      return "return expression type does not match function return type \n" + node->toSourceCode();
    } 
    static std::string ExpressionTypeUnknown(ASTNode* node) {
      return "expression type is unknown \n" + node->toSourceCode();
    } 
    static std::string ExpressionTypeInvalid(ASTNode* node) {
      return "expression type is invalid \n" + node->toSourceCode();
    } 
    static std::string ExpressionTypeVoid(ASTNode* node) {
      return "expression type cannot be void \n" + node->toSourceCode();
    } 
    static std::string EnumKeyValueTypeMismatch(ASTNode* node) {
      return "enum key-value type does not match enum type \n" + node->toSourceCode();
    } 
    static std::string ControlFlowConditionNotBool(ASTNode* node) {
      return "condition must evaluate to true or false \n" + node->toSourceCode();
    } 
    static std::string ForInStatementSourceNotIterable(ASTNode* node) {
      return "source of for-in loop is not iterable \n" + node->toSourceCode();
    } 
    static std::string ClassPropertyTypeUnknown(ASTNode* node) {
      return "class property type is unknown \n" + node->toSourceCode();
    } 
    static std::string ClassPropertyTypeInvalid(ASTNode* node) {
      return "class property type is invalid \n" + node->toSourceCode();
    } 
    static std::string ClassPropertyTypeVoid(ASTNode* node) {
      return "class property type cannot be void \n" + node->toSourceCode();
    } 
    static std::string ClassPropertyAssignmentTypeMismatch(ASTNode* node) {
      return "class property type does not match expression type \n" + node->toSourceCode();
    } 
    static std::string ClassPropertyInitializerTypeMismatch(ASTNode* node) {
      return "type of initial value for class property does not match class property type \n" + node->toSourceCode();
    }
    static std::string ClassPropertyInvocable(ASTNode* node) {
        return "class property cannot be invocable. Convert to class method instead \n" + node->toSourceCode();
    }
    static std::string ClassPropertyNamesNotUnique(ASTNode* node) {
      return "class property names must be unique \n" + node->toSourceCode();
    } 
    static std::string ClassMethodNamesAndTypeSignaturesNotUnique(ASTNode* node) {
      return "one or more class methods have the same name and type-signature \n" + node->toSourceCode();
    } 
    static std::string ClassConstructorsNotUnique(ASTNode* node) {
      return "class constructors must have unique parameter lists \n" + node->toSourceCode();
    }
    static std::string ClassConstructorHasReturnExpression(ASTNode* node) {
        return "class constructor cannot have return expression \n" + node->toSourceCode();
    }
    static std::string ClassMethodReturnTypeUnknown(ASTNode* node) {
      return "class method return type is unknown \n" + node->toSourceCode();
    } 
    static std::string ClassMethodReturnTypeInvalid(ASTNode* node) {
      return "class method return type is invalid \n" + node->toSourceCode();
    } 
    static std::string ClassMethodReturnTypeVoid(ASTNode* node) {
      return "class method return type cannot be void \n" + node->toSourceCode();
    } 
    static std::string ClassMethodNotAllPathsReturn(ASTNode* node) {
      return "not all class method paths return a value \n" + node->toSourceCode();
    }
    static std::string ClassMethodHasReturnExpression(ASTNode* node) {
        return "class method cannot have return expression \n" + node->toSourceCode();
    }
    static std::string ArrayElementTypeMismatch(ASTNode* node) {
      return "not all array elements match the array element type \n" + node->toSourceCode();
    } 
    static std::string ClassMethodCallNotEnoughArguments(ASTNode* node) {
      return "not enough arguments provided for class method call \n" + node->toSourceCode();
    } 
    static std::string ClassMethodCallTooManyArguments(ASTNode* node) {
      return "too many arguments provided for class method call \n" + node->toSourceCode();
    } 
    static std::string ClassMethodCallArgumentTypeMismatch(ASTNode* node) {
      return "argument type does not match parameter type for class method call \n" + node->toSourceCode();
    } 
    static std::string NotCallableCurryType(ASTNode* node) {
      return "curry function type is not callable \n" + node->toSourceCode();
    } 
    static std::string CurryCallNotEnoughArguments(ASTNode* node) {
      return "not enough arguments provided for curry call \n" + node->toSourceCode();
    } 
    static std::string CurryCallTooManyArguments(ASTNode* node) {
      return "too many arguments provided for curry call \n" + node->toSourceCode();
    } 
    static std::string CurryCallArgumentTypeMismatch(ASTNode* node) {
      return "argument type does not match parameter type for curry call \n" + node->toSourceCode();
    } 
    static std::string FunctionCallNotEnoughArguments(ASTNode* node) {
      return "not enough arguments provided for function call \n" + node->toSourceCode();
    } 
    static std::string FunctionCallTooManyArguments(ASTNode* node) {
      return "too many arguments provided for function call \n" + node->toSourceCode();
    } 
    static std::string FunctionCallArgumentTypeMismatch(ASTNode* node) {
      return "argument type does not match parameter type for function call \n" + node->toSourceCode();
    } 
    static std::string LambdaExpressionReturnTypeUnknown(ASTNode* node) {
      return "lambda expression return type is unknown \n" + node->toSourceCode();
    } 
    static std::string LambdaExpressionReturnTypeInvalid(ASTNode* node) {
      return "lambda expression return type is invalid \n" + node->toSourceCode();
    } 
    static std::string LambdaExpressionNotAllPathsReturn(ASTNode* node) {
      return "not all lambda expression paths return a value \n" + node->toSourceCode();
    }
    static std::string LambdaExpressionHasReturnExpression(ASTNode* node) {
        return "lambda expression cannot have return expression \n" + node->toSourceCode();
    }
    static std::string NewClassInstanceNotClassType(ASTNode* node) {
      return "cannot instantiate new class instance since type is not a class type \n" + node->toSourceCode();
    }
    static std::string NewClassInstanceNoMatchingConstructor(ASTNode* node) {
        return "cannot instantiate new class instance since no constructor found for arguments provided \n" + node->toSourceCode();
    }
    static std::string VariableNamesNotUnique(ASTNode* node) {
      return "variable name must be unique \n" + node->toSourceCode();
    }
    static std::string InvalidSingleImportModuleName(ASTNode* node) {
        return "imported module name is invalid \n" + node->toSourceCode();
    }
    static std::string DrefExpressionTypeInvalid(ASTNode* node) {
        return "dref expression does not have type ref/pointer  \n" + node->toSourceCode();
    }
    static std::string SrefExpressionTypeInvalid(ASTNode* node) {
        return "sref expression does not have type ref/pointer  \n" + node->toSourceCode();
    }
    static std::string RefExpressionTypeInvalid(ASTNode* node) {
        return "ref expression cannot have type ref/pointer  \n" + node->toSourceCode();
    }
    static std::string InterfacePropertyTypeUnknown(ASTNode* node) {
        return "interface property type is unknown \n" + node->toSourceCode();
    }
    static std::string InterfacePropertyTypeInvalid(ASTNode* node) {
        return "interface property type is invalid \n" + node->toSourceCode();
    }
    static std::string InterfacePropertyTypeVoid(ASTNode* node) {
        return "interface property type cannot be void \n" + node->toSourceCode();
    }
    static std::string InterfacePropertyNamesNotUnique(ASTNode* node) {
        return "interface property names must be unique \n" + node->toSourceCode();
    }
}

#endif //JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
