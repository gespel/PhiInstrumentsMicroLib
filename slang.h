#define MAX_TOKENS 256
#include <Array.h>
#include "synths.h"

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
    COMMA
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
        return "UNKNOWN";
    }
private:
    TokenType t;
    String v;
};

class Slang {
public:
    Slang(double sampleRate);
    void tokenize(String input);
    void interpret();
    Token createAlphaToken(String input);
    void printTokens();
private:
    Array<Token, MAX_TOKENS> tokens;
    Array<Synth, 64> synths;
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
        Serial.println("WRONG TOKEN. EXPECTED OTHER TOKEN");
        exit(-1);
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
        exit(-1);
        return false;
    }
}

void Slang::interpret() {
    for(int i = 0; i < this->tokens.size(); i++) {
        if(peek(tokens[i].getType(), SINESYNTH)) {
            consume(tokens[i].getType(), SINESYNTH, &i);
            consume(tokens[i].getType(), LEFT_PARANTHESIS, &i);
            peek(tokens[i].getType(), NUMBER);
            String freq = tokens[i].getValue();
            consume(tokens[i].getType(), NUMBER, &i);
            consume(tokens[i].getType(), RIGHT_PARANTHESIS, &i);
            peek(tokens[i].getType(), SEMICOLON);

            createSineSynth(freq);
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
    SineSynth s(f, sampleRate);
    //synths.push_back(s);
}