#pragma once
#include <Array.h>
#include <Arduino.h>
#include "token.h"

#define MAX_TOKENS 64

Array<String, MAX_TOKENS> split(String input) {
    Array<String, MAX_TOKENS> out;

    String sub = "";
    for(int i = 0; i < strlen(input.c_str()); i++) {
        if(input.charAt(i) == ' ') {
            out.push_back(sub);
            sub = "";
        }
        else {
            sub.concat(input.charAt(i));
        }
    }
    out.push_back(sub);
    return out;
}

class Tokenizer {
public:
    Array<Token, MAX_TOKENS> tokenize(String input);
    Token createAlphaToken(String input);
    void test();
private:
    Array<Token, MAX_TOKENS> tokens;
};

Token Tokenizer::createAlphaToken(String input) {
    if(input.equals("fn")) {
        return Token(TokenType::FUNCTION, "Function");
    }
    else if(input.equals("return")) {
        return Token(TokenType::RETURN, "Return");
    }
    else if(input.equals("if")) {
        return Token(TokenType::IF, "If");
    }
    else if(input.equals("sinesynth")) {
        return Token(TokenType::SINESYNTH, "Sinesynth");
    }
    else if(input.equals("sawtoothsynth")) {
        return Token(TokenType::SAWTOOTHSYNTH, "Sawtoothsynth");
    }
    else {
        return Token(TokenType::IDENTIFIER, input);
    }
}

Array<Token, MAX_TOKENS> Tokenizer::tokenize(String input) {
    Array<String, MAX_TOKENS> splited = split(input);
    for(auto ts : splited) {
        for(int i = 0; i < ts.length(); i++) {
            if(isAlpha(ts[i])) {
                String word = "";
                while(isAlpha(ts[i])) {
                    word += ts[i];
                    i++;
                }
                i--;
                this->tokens.push_back(createAlphaToken(word));
            }
            else if(isDigit(ts[i])) {
                String number = "";
                while(isDigit(ts[i])) {
                    number += ts[i];
                    i++;
                }
                Token t(TokenType::NUMBER, number);
                i--;
                this->tokens.push_back(t);
            }
            else if(ts[i] == '(') {
                Token t(TokenType::LEFT_PARANTHESIS, "Left Paranthesis");
                this->tokens.push_back(t);
            }
            else if(ts[i] == ')') {
                Token t(TokenType::RIGHT_PARANTHESIS, "Right Paranthesis");
                this->tokens.push_back(t);
            }
            else if(ts[i] == '{') {
                Token t(TokenType::LEFT_BRACKETS, "Left Brackets");
                this->tokens.push_back(t);
            }
            else if(ts[i] == '}') {
                Token t(TokenType::RIGHT_BRACKETS, "Right Brackets");
                this->tokens.push_back(t);
            }
            else if(ts[i] == ';') {
                Token t(TokenType::SEMICOLON, "Semicolon");
                this->tokens.push_back(t);
            }
            else if(ts[i] == ',') {
                Token t(TokenType::COMMA, "Comma");
                this->tokens.push_back(t);
            }
        }
    }
    return this->tokens;
}