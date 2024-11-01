//
// Created by Johny Georges on 2024-08-12.
//

#include "ir-injector-map.h"
#include "../../shared/utils/logger/logger.h"

IRInjectorMap::IRInjectorMap() {
    _injectorMap = std::unordered_map<TypeSource, IRInjectorStrategy*, std::hash<int>>();
    _stringIRInjector = new StringIRInjectorStrategy();
    _literalIRInjector = new LiteralIRInjectorStrategy();
    _arrayIRInjector = new ArrayIRInjectorStrategy();
    _structIRInjector = new StructIRInjectorStrategy();
    _tupleIRInjector = new TupleIRInjectorStrategy();
    _variableIRInjector = new VariableIRInjectorStrategy();
    _functionReturnIRInjector = new FunctionReturnIRInjectorStrategy();
    this->init();
}

void IRInjectorMap::init() {
    _injectorMap.insert(this->insert(ARRAY_TYPE_SOURCE, _arrayIRInjector));
    _injectorMap.insert(this->insert(STRUCT_TYPE_SOURCE, _structIRInjector));
    _injectorMap.insert(this->insert(STRING_LITERAL_TYPE_SOURCE, _stringIRInjector));
    _injectorMap.insert(this->insert(INT_LITERAL_TYPE_SOURCE, _literalIRInjector));
    _injectorMap.insert(this->insert(FLOAT_LITERAL_TYPE_SOURCE, _literalIRInjector));
    _injectorMap.insert(this->insert(BOOL_LITERAL_TYPE_SOURCE, _literalIRInjector));
    _injectorMap.insert(this->insert(CHAR_LITERAL_TYPE_SOURCE, _literalIRInjector));
    _injectorMap.insert(this->insert(TUPLE_TYPE_SOURCE, _tupleIRInjector));
}

std::pair<TypeSource, IRInjectorStrategy*> IRInjectorMap::insert(TypeSource typeSignature, IRInjectorStrategy* injector) {
    return std::pair { typeSignature, injector };
}

IRInjectorStrategy* IRInjectorMap::getInjector(TypeSignature* typeSignature) {
    auto injector = _injectorMap.find(typeSignature->getTypeTarget());
    if (injector == _injectorMap.end()) {
        typeSignature->print();
        throw std::invalid_argument("unable to find injector for type signature: " + std::to_string(typeSignature->getTypeTarget()));
    }
    return injector->second;
}

StringIRInjectorStrategy* IRInjectorMap::getStringInjector() {
    return _stringIRInjector;
}

ArrayIRInjectorStrategy* IRInjectorMap::getArrayInjector() {
    return _arrayIRInjector;
}

StructIRInjectorStrategy* IRInjectorMap::getStructInjector() {
    return _structIRInjector;
}

LiteralIRInjectorStrategy* IRInjectorMap::getLiteralInjector() {
    return _literalIRInjector;
}

TupleIRInjectorStrategy* IRInjectorMap::getTupleInjector() {
    return _tupleIRInjector;
}

VariableIRInjectorStrategy* IRInjectorMap::getVariableInjector() {
    return _variableIRInjector;
}

ModuleIRInjectorStrategy* IRInjectorMap::getModuleInjector() {
    return _moduleIRInjector;
}

FunctionParameterIRInjectorStrategy* IRInjectorMap::getFunctionParameterInjector() {
    return _functionParameterIRInjector;
}

FunctionReturnIRInjectorStrategy* IRInjectorMap::getFunctionReturnInjector() {
    return _functionReturnIRInjector;
}