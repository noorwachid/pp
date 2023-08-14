#include "common.h"

enum class TokenType {
	symbol,

	keywordVar,
	keywordConst,

	dot,
	colon,
	equal,
	angleLeft,
	angleRight,
	parenLeft,
	parenRight,
	literalInt,
	literalFloat,
	literalChar,
	literalString,
};

string toString(TokenType type) {
	switch (type) {
		case TokenType::symbol: return "symbol";
		case TokenType::keywordVar: return "keywordVar";
		case TokenType::keywordConst: return "keywordConst";
		case TokenType::dot: return "dot";
		case TokenType::colon: return "colon";
		case TokenType::equal: return "equal";
		case TokenType::angleLeft: return "angleLeft";
		case TokenType::parenRight: return "parenRight";
		case TokenType::parenLeft: return "parenLeft";
		case TokenType::angleRight: return "angleRight";
		case TokenType::literalInt: return "literalInt";
		case TokenType::literalFloat: return "literalFloat";
		case TokenType::literalChar: return "literalChar";
		case TokenType::literalString: return "literalString";
	}
}

struct Pos {
	size_t line;
	size_t column;
};

struct Token {
	TokenType type;
	string_view value;
	Pos from;
	Pos to;
};

class Lexer {
public:
	void tokenize(string_view content) {
		this->content = content;
		this->index = 0;

		prevPos.line = 1;
		prevPos.column = 1;

		currPos.line = 1;
		currPos.column = 1;

		tokenize();

		cout << "[TOKEN]\n";
		for (const Token& token : tokens) {
			cout << token.from.line << ":" << token.from.column
				<< "," 
				<< token.to.line << ":" << token.to.column
				<< " " << toString(token.type) << " " << token.value << "\n";
		}
		cout << "\n";
	}

	const vector<Token>& get() const {
		return tokens;
	}

private:
	void tokenize() {
		while (check(0)) {
			switch (get(0)) {
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
				case 'f':
				case 'g':
				case 'h':
				case 'i':
				case 'j':
				case 'k':
				case 'l':
				case 'm':
				case 'n':
				case 'o':
				case 'p':
				case 'q':
				case 'r':
				case 's':
				case 't':
				case 'u':
				case 'v':
				case 'w':
				case 'x':
				case 'y':
				case 'z':
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'J':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'O':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'U':
				case 'V':
				case 'W':
				case 'X':
				case 'Y':
				case 'Z':
				case '_': {
					size_t offset = index;
					size_t size = 0;

					while (isSymbol(0)) {
						++size;
						advance(0);
					}

					retreat(0);

					string_view symbol = content.substr(offset, size);

					if (symbol == "var") {
						add(TokenType::keywordVar, symbol);
						advance(0);
						break;
					}

					if (symbol == "const") {
						add(TokenType::keywordConst, symbol);
						advance(0);
						break;
					}

					add(TokenType::symbol, symbol);
					advance(0);
					break;
				}

				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9': {
					size_t offset = index;
					size_t size = 0;

					while (isDigit(0)) {
						++size;
						advance(0);
					}

					add(TokenType::literalInt, content.substr(offset, size));
					break;
				}

				case '.':
					add(TokenType::dot, ".");
					advance(0);
					break;

				case ':':
					add(TokenType::colon, ":");
					advance(0);
					break;

				case '=':
					add(TokenType::equal, "=");
					advance(0);
					break;

				case '<':
					add(TokenType::angleLeft, "<");
					advance(0);
					break;
				case '>':
					add(TokenType::angleRight, ">");
					advance(0);
					break;

				case '#':
					while (check(0) && !is(0, '\n')) {
						advance(0);
					}
					break;

				case '\n': {
					prevPos.line++;
					prevPos.column = 1;
					currPos.line++;
					currPos.column = 0;
					advance(0);
					break;
				}

				case ' ': {
					advance(0);
					prevPos.column = currPos.column;
					break;
				}

				default: {
					advance(0);
					break;
				}
			}

		}
	}

	bool check(size_t rindex) {
		return index + rindex < content.size();
	}

	bool is(size_t rindex, char letter) {
		return content[index + rindex] == letter;
	}

	bool isSymbolPrefix(size_t rindex) {
		char letter = get(rindex);
		return 
			(letter >= 'a' && letter <= 'z') ||
			(letter >= 'A' && letter <= 'Z') ||
			letter == '_';
	}

	bool isSymbol(size_t rindex) {
		return isSymbolPrefix(rindex) || isDigit(rindex);
	}

	bool isDigit(size_t rindex) {
		char letter = get(rindex);
		return letter >= '0' && letter <= '9';
	}

	char get(size_t rindex) {
		return content[index + rindex];
	}

	void advance(size_t rindex) {
		currPos.column += rindex + 1;
		index += rindex + 1;
	}

	void retreat(size_t rindex) {
		currPos.column -= rindex + 1;;
		index -= rindex + 1;
	}

	void add(TokenType type, string_view value) {
		Token token;
		token.type = type;
		token.value = value;
		token.from = prevPos;
		token.to = currPos;
		tokens.push_back(token);
		prevPos = currPos;
		prevPos.column++;
	}

	Pos currPos;
	Pos prevPos;
	size_t index;
	string_view content;
	vector<Token> tokens;
};


