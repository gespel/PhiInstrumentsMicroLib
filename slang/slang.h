#define MAX_TOKENS 128
#include <Array.h>
#include "../synths.h"
#include "token.h"

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



class Slang {
public:
    Slang(double sampleRate);
    void tokenize(String input);
    void interpret();
    Token createAlphaToken(String input);
    void printTokens();
    Array<SineSynth*, 64> getSineSynths();
private:
    Array<Token, MAX_TOKENS> tokens;
    Array<SineSynth*, 64> sineSynths;
    bool consume(TokenType input, TokenType expected, int *i);
    bool peek(TokenType input, TokenType expected);
    void createSineSynth(String freq);
    double sampleRate;
};

Slang::Slang(double sampleRate) {
    this->sampleRate = sampleRate;
}

void Slang::printTokens() {
    for(Token t : tokens) {
        Serial.println(t.typeAsString() + " -> " + t.getValue());
    }
    Serial.println("==========================================");
}
void Slang::tokenize(String input) {
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
}

bool Slang::peek(TokenType input, TokenType expected) {
    if(input == expected) {
        return true;
    }
    else {
        return false;
    }
}

bool Slang::consume(TokenType input, TokenType expected, int *i) {
    if(input == expected) {
        (*i)++;
        return true;
    }
    else {
        Serial.println("WRONG TOKEN. EXPECTED OTHER TOKEN");
        Serial.print(expected);
        Serial.print(" ");
        Serial.println(input);
        exit(-1);
        return false;
    }
}

void Slang::interpret() {
    for(int i = 0; i < this->tokens.size(); i++) {
        bool executed = false;
        if(peek(tokens[i].getType(), SINESYNTH)) {
            consume(tokens[i].getType(), SINESYNTH, &i);
            consume(tokens[i].getType(), LEFT_PARANTHESIS, &i);
            peek(tokens[i].getType(), NUMBER);
            String freq = tokens[i].getValue();
            consume(tokens[i].getType(), NUMBER, &i);
            consume(tokens[i].getType(), RIGHT_PARANTHESIS, &i);
            consume(tokens[i].getType(), SEMICOLON, &i);

            createSineSynth(freq);
            executed = true;
        }
        else if(peek(tokens[i].getType(), FUNCTION)) {
            
            executed = true;
        }
        if(executed) {
            i--;
        }
    }
}

Token Slang::createAlphaToken(String input) {
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
        
    }
    else {
        return Token(TokenType::IDENTIFIER, input);
    }
}

void Slang::createSineSynth(String freq) {
    double f = freq.toDouble();
    String pre = "Creating Sine Synthesizer with ";
    String out = pre + f;
    Serial.println(out);
    SineSynth *s = new SineSynth(f, sampleRate);
    sineSynths.push_back(s);
}

Array<SineSynth*, 64> Slang::getSineSynths() {
    return sineSynths;
}