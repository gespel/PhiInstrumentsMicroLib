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
    Array<Token*, MAX_TOKENS> tokenize(String input);
    Token* createAlphaToken(String input);
    void test();
private:
};

Token* Tokenizer::createAlphaToken(String input) {
    if(input.equals("fn")) {
        return new Token(TokenType::FUNCTION, "Function");
    }
    else if(input.equals("return")) {
        return new Token(TokenType::RETURN, "Return");
    }
    else if(input.equals("if")) {
        return new Token(TokenType::IF, "If");
    }
    else if(input.equals("sinesynth")) {
        return new Token(TokenType::SINESYNTH, "Sinesynth");
    }
    else if(input.equals("sawtoothsynth")) {
        return new Token(TokenType::SAWTOOTHSYNTH, "Sawtoothsynth");
    }
    else if(input.equals("dyn")) {
        return new Token(TokenType::DYN, "Dynamic");
    }
    else {
        return new Token(TokenType::IDENTIFIER, input);
    }
}

Array<Token*, MAX_TOKENS> Tokenizer::tokenize(String input) {
    Array<Token*, MAX_TOKENS> tokens;
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
                tokens.push_back(createAlphaToken(word));
            }
            else if(isDigit(ts[i])) {
                String number = "";
                while(isDigit(ts[i])) {
                    number += ts[i];
                    i++;
                }
                Token* t = new Token(TokenType::NUMBER, number);
                i--;
                tokens.push_back(t);
            }
            else if(ts[i] == '(') {
                Token* t = new Token(TokenType::LEFT_PARANTHESIS, "Left Paranthesis");
                tokens.push_back(t);
            }
            else if(ts[i] == ')') {
                Token* t = new Token(TokenType::RIGHT_PARANTHESIS, "Right Paranthesis");
                tokens.push_back(t);
            }
            else if(ts[i] == '{') {
                Token* t = new Token(TokenType::LEFT_BRACKETS, "Left Brackets");
                tokens.push_back(t);
            }
            else if(ts[i] == '}') {
                Token* t = new Token(TokenType::RIGHT_BRACKETS, "Right Brackets");
                tokens.push_back(t);
            }
            else if(ts[i] == ';') {
                Token* t = new Token(TokenType::SEMICOLON, "Semicolon");
                tokens.push_back(t);
            }
            else if(ts[i] == ',') {
                Token* t = new Token(TokenType::COMMA, "Comma");
                tokens.push_back(t);
            }
        }
    }
    return tokens;
}