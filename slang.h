#define MAX_TOKENS 256
#include <Array.h>

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
        return "UNKNOWN";
    }
private:
    TokenType t;
    String v;
};

class Slang {
public:
    Slang();
    void tokenize(String input);
    void interpret();
    Token createAlphaToken(String input);
    void printTokens();
private:
    Array<Token, MAX_TOKENS> tokens;
};

Slang::Slang() {
    
}

void Slang::printTokens() {
    for(Token t : tokens) {
        Serial.println(t.typeAsString() + " -> " + t.getValue());
    }
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
