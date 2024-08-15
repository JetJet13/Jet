//
// Created by Johny Georges on 2024-08-12.
//

#include "ir-injector-map.h"
#include "../../shared/utils/logger/logger.h"

IRInjectorMap::IRInjectorMap() {
    _injectorMap = std::unordered_map<TypeSource, ExpressionIRInjector*, std::hash<int>>();
    _stringIRInjector = new StringIRInjector(this);
    _literalIRInjector = new LiteralIRInjector(this);
    _arrayIRInjector = new ArrayIRInjector(this);
    _structIRInjector = new StructIRInjector(this);
    _tupleIRInjector = new TupleIRInjector(this);
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

std::pair<TypeSource, ExpressionIRInjector*> IRInjectorMap::insert(TypeSource typeSignature, ExpressionIRInjector* injector) {
    return std::pair { typeSignature, injector };
}

ExpressionIRInjector* IRInjectorMap::getInjector(TypeSignature* typeSignature) {
    auto injector = _injectorMap.find(typeSignature->getTypeTarget());
    Logger::log("injectorMap", _injectorMap.size());
    if (injector == _injectorMap.end()) {
        typeSignature->print();
        throw std::invalid_argument("unable to find injector for type signature: " + std::to_string(typeSignature->getTypeTarget()));
    }
    return injector->second;
}

StringIRInjector* IRInjectorMap::getStringInjector() {
    return _stringIRInjector;
}

ArrayIRInjector* IRInjectorMap::getArrayInjector() {
    return _arrayIRInjector;
}

StructIRInjector* IRInjectorMap::getStructInjector() {
    return _structIRInjector;
}

LiteralIRInjector* IRInjectorMap::getLiteralInjector() {
    return _literalIRInjector;
}

TupleIRInjector* IRInjectorMap::getTupleInjector() {
    return _tupleIRInjector;
}
