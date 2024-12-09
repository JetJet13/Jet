//
// Created by Johny Georges on 2024-12-05.
//

#ifndef JETLANG_IR_CLASS_TYPE_H
#define JETLANG_IR_CLASS_TYPE_H

#include "ir-struct-type.h"
#include "ir-function-type.h"
#include "ir-parameter-type.h"

class IRClassType : public IRType {
private:
    IRStructType* _classProperties;
    IRParameterType* _classScopeType;
    std::unordered_map<std::string, IRFunctionType*> _classConstructors;
    std::unordered_map<std::string, IRFunctionType*> _classMethods;
public:
    IRClassType(IRStructType* classProperties, IRParameterType* classScopeType, std::unordered_map<std::string, IRFunctionType*> classConstructors, std::unordered_map<std::string, IRFunctionType*> classMethods);
    llvm::Type* getValueType();
    bool isClassType() override;
};

#endif //JETLANG_IR_CLASS_TYPE_H
