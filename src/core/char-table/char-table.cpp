//
// Created by Johny Georges on 2024-01-10.
//

#include "char-table.h"

CharTable::CharTable() {
    _charMap = std::unordered_map<std::string, char>();
    this->init();
}

std::optional<char> CharTable::match(const std::string& matchTerm) {
    auto result = _charMap.find(matchTerm);
    if (result == _charMap.end()) {
        return {};
    } else {
        return result->second;
    }
}

std::optional<char> CharTable::match(std::optional<char> matchChar) {
    if (!matchChar) {
        return {};
    }
    std::string matchTerm;
    matchTerm += matchChar.value();
    return this->match(matchTerm);
}

void CharTable::init() {
    this->add("\a", '\a');
    this->add("\b", '\b');
    this->add("\f", '\f');
    this->add("\n", '\n');
    this->add("\r", '\r');
    this->add("\t", '\t');
    this->add("\v", '\v');
    this->add("\'", '\'');
    this->add("\"", '"');
    this->add("\\", '\\');
    this->add(" ", ' ');
    this->add("!", '!');
    this->add("#", '#');
    this->add("$", '$');
    this->add("%", '%');
    this->add("&", '&');
    this->add("(", '(');
    this->add(")", ')');
    this->add("*", '*');
    this->add("+", '+');
    this->add(",", ',');
    this->add("-", '-');
    this->add(".", '.');
    this->add("/", '/');
    this->add(":", ':');
    this->add(";", ';');
    this->add("<", '<');
    this->add("=", '=');
    this->add(">", '>');
    this->add("?", '?');
    this->add("@", '@');
    this->add("A", 'A');
    this->add("B", 'B');
    this->add("C", 'C');
    this->add("D", 'D');
    this->add("E", 'E');
    this->add("F", 'F');
    this->add("G", 'G');
    this->add("H", 'H');
    this->add("I", 'I');
    this->add("J", 'J');
    this->add("K", 'K');
    this->add("L", 'L');
    this->add("M", 'M');
    this->add("N", 'N');
    this->add("O", 'O');
    this->add("P", 'P');
    this->add("Q", 'Q');
    this->add("R", 'R');
    this->add("S", 'S');
    this->add("T", 'T');
    this->add("U", 'U');
    this->add("V", 'V');
    this->add("W", 'W');
    this->add("X", 'X');
    this->add("Y", 'Y');
    this->add("Z", 'Z');
    this->add("a", 'a');
    this->add("b", 'b');
    this->add("c", 'c');
    this->add("d", 'd');
    this->add("e", 'e');
    this->add("f", 'f');
    this->add("g", 'g');
    this->add("h", 'h');
    this->add("i", 'i');
    this->add("j", 'j');
    this->add("k", 'k');
    this->add("l", 'l');
    this->add("m", 'm');
    this->add("n", 'n');
    this->add("o", 'o');
    this->add("p", 'p');
    this->add("q", 'q');
    this->add("r", 'r');
    this->add("s", 's');
    this->add("t", 't');
    this->add("u", 'u');
    this->add("v", 'v');
    this->add("w", 'w');
    this->add("x", 'x');
    this->add("y", 'y');
    this->add("z", 'z');
    this->add("[", '[');
    this->add("]", ']');
    this->add("^", '^');
    this->add("_", '_');
    this->add("`", '`');
    this->add("{", '{');
    this->add("|", '|');
    this->add("}", '}');
    this->add("~", '~');
    this->add("0", '0');
    this->add("1", '1');
    this->add("2", '2');
    this->add("3", '3');
    this->add("4", '4');
    this->add("5", '5');
    this->add("6", '6');
    this->add("7", '7');
    this->add("8", '8');
    this->add("9", '9');
}

void CharTable::add(const std::string& strChar, char character) {
    _charMap.insert(std::pair<std::string, char>(strChar, character));
}