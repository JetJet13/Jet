//
// Created by Johny Georges on 2024-05-13.
//

#include <catch2/catch_all.hpp>
#include "../../../../src/core/token/token-table.h"
#include "../../../../src/core/reserved-keywords/reserved-keywords.h"
#include "../../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../../src/shared/utils/logger/logger.h"
#include "../../../../src/core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/dependency-graph/dependency-graph.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/semantic-analyzer.h"
#include "resources/type-signature-factory.h"
#include "../../../../src/core/type-signature/array-type-signature/array-type-signature.h"
#include "../../../../src/core/type-signature/struct-type-signature/struct-type-signature.h"

std::unordered_map<int, TypeSignature*> expectedTypeSignature = {
        {1, TypeSignatureFactory::intLiteral},
        {2, TypeSignatureFactory::floatLiteral},
        {3, TypeSignatureFactory::stringLiteral},
        {4, TypeSignatureFactory::charLiteral},
        {5, TypeSignatureFactory::boolLiteral},
        {6, TypeSignatureFactory::boolLiteral},
        {7, TypeSignatureFactory::intLiteral},
        {8, TypeSignatureFactory::intLiteral},
        {9, TypeSignatureFactory::intLiteral},
        {10, TypeSignatureFactory::intLiteral},
        {11, TypeSignatureFactory::floatLiteral},
        {12, TypeSignatureFactory::intLiteral},
        {13, TypeSignatureFactory::stringLiteral},
        {14, TypeSignatureFactory::intLiteral},
        {15, TypeSignatureFactory::floatLiteral},
        {16, TypeSignatureFactory::intLiteral},
        {17, TypeSignatureFactory::intLiteral},
        {18, TypeSignatureFactory::intLiteral},
        {19, TypeSignatureFactory::floatLiteral},
        {20, TypeSignatureFactory::floatLiteral},
        {21, TypeSignatureFactory::intLiteral},
        {22, TypeSignatureFactory::intLiteral},
        {23, TypeSignatureFactory::intLiteral},
        {24, TypeSignatureFactory::intLiteral},
        {25, TypeSignatureFactory::floatLiteral},
        {26, TypeSignatureFactory::floatLiteral},
        {27, TypeSignatureFactory::intLiteral},
        {28, TypeSignatureFactory::boolLiteral},
        {29, TypeSignatureFactory::boolLiteral},
        {30, TypeSignatureFactory::boolLiteral},
        {31, TypeSignatureFactory::boolLiteral},
        {32, TypeSignatureFactory::boolLiteral},
        {33, TypeSignatureFactory::boolLiteral},
        {34, TypeSignatureFactory::boolLiteral},
        {35, TypeSignatureFactory::boolLiteral},
        {36, TypeSignatureFactory::boolLiteral},
        {37, TypeSignatureFactory::boolLiteral},
        {38, TypeSignatureFactory::boolLiteral},
        {39, TypeSignatureFactory::boolLiteral},
        {40, TypeSignatureFactory::boolLiteral},
        {41, TypeSignatureFactory::boolLiteral},
        {42, TypeSignatureFactory::boolLiteral},
        {43, TypeSignatureFactory::boolLiteral},
        {44, TypeSignatureFactory::boolLiteral},
        {45, TypeSignatureFactory::boolLiteral},
        {46, TypeSignatureFactory::boolLiteral},
        {47, TypeSignatureFactory::boolLiteral},
        {48, TypeSignatureFactory::boolLiteral},
        {49, TypeSignatureFactory::intLiteral},
        {50, TypeSignatureFactory::intLiteral},
        {51, TypeSignatureFactory::intLiteral},
        {52, TypeSignatureFactory::intLiteral},
        {53, TypeSignatureFactory::intLiteral},
        {54, TypeSignatureFactory::boolLiteral},
        {55, TypeSignatureFactory::boolLiteral},
        {56, TypeSignatureFactory::boolLiteral},
        {57, TypeSignatureFactory::boolLiteral},
        {58, TypeSignatureFactory::intLiteral},
        {59, TypeSignatureFactory::boolLiteral},
        {60, TypeSignatureFactory::boolLiteral},
        {61, new ArrayTypeSignature(TypeSignatureFactory::intLiteral)},
        {62, TypeSignatureFactory::intLiteral},
        {63, TypeSignatureFactory::intLiteral},
        {64, new ArrayTypeSignature(new ArrayTypeSignature(TypeSignatureFactory::intLiteral))},
        {65, new ArrayTypeSignature(new ArrayTypeSignature(TypeSignatureFactory::intLiteral))},
        {66, new ArrayTypeSignature(TypeSignatureFactory::intLiteral)},
        {67, TypeSignatureFactory::intLiteral},
        {68, TypeSignatureFactory::intLiteral},
        {69, new StructTypeSignature(
                TypeSignatureMap<TypeSignature>({
                    std::pair("i", TypeSignatureFactory::intLiteral),
                    std::pair("f", TypeSignatureFactory::floatLiteral),
                    std::pair("world", TypeSignatureFactory::boolLiteral),
                    std::pair("character", TypeSignatureFactory::boolLiteral),
                    std::pair("str", TypeSignatureFactory::boolLiteral),
                    std::pair("identifier", TypeSignatureFactory::boolLiteral),
                    std::pair("array", TypeSignatureFactory::boolLiteral),
                    std::pair("arrAccess", TypeSignatureFactory::boolLiteral),
                    std::pair("obj", new StructTypeSignature(
                        TypeSignatureMap<TypeSignature>({
                            std::pair("test", TypeSignatureFactory::intLiteral),
                            std::pair("nest", new StructTypeSignature(
                                TypeSignatureMap<TypeSignature>({
                                    std::pair("value", TypeSignatureFactory::boolLiteral),
                                })
                            )),
                        })
                    )),
                    std::pair("binary", TypeSignatureFactory::intLiteral),
                    std::pair("logical", TypeSignatureFactory::boolLiteral),
                    std::pair("unary", TypeSignatureFactory::boolLiteral),
                })
        )},
        {70, TypeSignatureFactory::boolLiteral},
        {71, TypeSignatureFactory::intLiteral},
        {72, TypeSignatureFactory::boolLiteral},


//        const structObjAccess = structObj.world;
//        const structObjNestedAccess = structObj.obj.test;
//        const structObjTripleNestedAccess = structObj.obj.nest.value;
//        const arrayStructs = [
//        { hello: "world", test: 1 } // another 1!
//        ];
//        const arrStructsAccess = arrayStructs[0].hello;
//        const structArr = {
//            array: [ { hello: "world", test: 1 } ],
//            arrNested: [  [{ hello: "world", test: 1 }] ]
//        };
//        const structArrAccess = structArr.array[0].hello;
//        const structArrNestedAccess = structArr.arrNested[0][0].hello;


};

TEST_CASE( "should print the expected type signatures" ) {
    std::string filePath = "./semantic-analyzer-test-file.jet";
    auto tokenTable = new TokenTable();
    auto reservedKeywords = new ReservedKeywords();
    auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
    auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
    auto fileNodeResult = syntaxAnalyzer.analyze(filePath);
    auto dependencyGraph = new DependencyGraph();
    auto typeSignatureLookupTable = new TypeSignatureLookupTable();
    auto semanticAnalyzer = SemanticAnalyzer(dependencyGraph, tokenTable, typeSignatureLookupTable);
    semanticAnalyzer.analyze(fileNodeResult);
    Logger::log("===== TEST LOGS =====");
    typeSignatureLookupTable->dump();
//    REQUIRE(fileNodeResult->getBody()->size() == 118);
    for (int i = 0; i < 72; i++) {
        auto declaration = fileNodeResult->getBody()->getContents()[i];
        auto typeSignature = typeSignatureLookupTable->find(declaration->getId());
        Logger::log("=====", i + 1, declaration->toString(), "=====");
        Logger::log("ID -", declaration->getId());
        typeSignature->print();
        Logger::log("RESULT =", typeSignature->isEqualTo(expectedTypeSignature[i + 1]));
        REQUIRE(typeSignature->isEqualTo(expectedTypeSignature[i + 1]));
        Logger::log("====================================");
    }
}