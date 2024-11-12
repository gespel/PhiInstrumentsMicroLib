#pragma once
#include <Arduino.h>

enum TokenType {
    IDENTIFIER,
    NUMBER,
    FUNCTION,
    RETURN,
    SEMICOLON,
    LEFT_PARANTHESIS,
    RIGHT_PARANTHESIS,
    LEFT_BRACKETS,
    RIGHT_BRACKETS,
    SINESYNTH,
    COMMA,
    IF,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    EQUALS
};



class Token {
public:
    Token() {

    }
    Token(TokenType t, String v) {
        this->t = t;
        this->v = v;
    }
    TokenType getType() {
        return t;
    }
    String getValue() {
        return v;
    }
    String typeAsString() {
        if(t == TokenType::FUNCTION) {
            return "FUNCTION";
        }
        else if(t == TokenType::RETURN) {
            return "RETURN";
        }
        else if(t == TokenType::IDENTIFIER) {
            return "IDENTIFIER";
        }
        else if(t == TokenType::NUMBER) {
            return "NUMBER";
        }
        else if(t == TokenType::LEFT_PARANTHESIS) {
            return "LEFT_PARANTHESIS";
        }
        else if(t == TokenType::RIGHT_PARANTHESIS) {
            return "RIGHT_PARANTHESIS";
        }
        else if(t == TokenType::LEFT_BRACKETS) {
            return "LEFT_BRACKETS";
        }
        else if(t == TokenType::RIGHT_BRACKETS) {
            return "RIGHT_BRACKETS";
        }
        else if(t == TokenType::SEMICOLON) {
            return "SEMICOLON";
        }
        else if(t == TokenType::SINESYNTH) {
            return "SINESYNTH";
        }
        else if(t == TokenType::COMMA) {
            return "COMMA";
        }
        else if(t == TokenType::IF) {
            return "IF";
        }
        return "UNKNOWN";
    }
private:
    TokenType t;
    String v;
};