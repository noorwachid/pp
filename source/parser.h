#pragma once

#include "lexer.h"
#include <exception>

class Node;
using NodePtr = shared_ptr<Node>;

enum class NodeType {
	file,
	variable,
	namespace_,
	generic,
	type,
	assignment,
	literalInt,
};

string toString(NodeType type) {
	switch (type) {
		case NodeType::file: return "file";
		case NodeType::variable: return "variable";
		case NodeType::namespace_: return "namespace";
		case NodeType::generic: return "generic";
		case NodeType::type: return "type";
		case NodeType::assignment: return "assignment";
		case NodeType::literalInt: return "literalInt";
	}
}

class Node {
public:
	NodeType type;

	virtual string toString() const {
		return ::toString(type);
	}

	template <class T>
	T& as() {
		return *static_cast<T*>(this);
	}
};

class File : public Node {
public:
	File() {
		type = NodeType::file;
	}
};

class Literal : public Node {
};

class IntLiteral : public Literal {
public:
	int value;

	IntLiteral() {
		type = NodeType::literalInt;
	}

	virtual string toString() const {
		return ::toString(type) + " " + std::to_string(value);
	}
};

class Variable : public Node {
public:
	string symbol;

	Variable() {
		type = NodeType::variable;
	}

	virtual string toString() const {
		return ::toString(type) + " " + symbol;
	}
};

class Assignment : public Node {
public:
	Assignment() {
		type = NodeType::assignment;
	}
};

class Namespace : public Node {
public:
	string symbol;

	Namespace() {
		type = NodeType::namespace_;
	}

	virtual string toString() const {
		return ::toString(type) + " " + symbol;
	}
};

class Generic : public Node {
public:
	string symbol;

	Generic() {
		type = NodeType::generic;
	}

	virtual string toString() const {
		return ::toString(type) + " " + symbol;
	}
};

class Type : public Node {
public:
	string symbol;

	Type() {
		type = NodeType::type;
	}

	virtual string toString() const {
		return ::toString(type) + " " + symbol;
	}
};

class ParserException : public std::exception {
public:
	ParserException(const string& message) {
		this->message = message;
	}

	const char* what() const throw() {
		return message.c_str();
	}

private:
	string message;
};

class Parser {
public:
	void parse(string_view content) {
		index = 0;
		lexer.tokenize(content);

		root = make_shared<File>();
		stack.clear();
		stack.push_back(root);

		while (check(0)) {
			parseExpression();
		}

		cout << "\n[ast]\n";
		print(root, 0);
	}

	const NodePtr& get() {
		return root;
	}

	void print(const NodePtr& node, size_t depth) {
		cout << string(depth * 2, ' ') << node->toString() << '\n';

		for (const NodePtr& subnode : node->children) {
			print(subnode, depth + 1);
		}
	}

private:
	void parseExpression() {
		switch (get(0).type) {
			case TokenType::keywordVar:
				parseVariableDef();
				break;

			case TokenType::literalInt: {
				IntLiteral& literal = add<IntLiteral>();
				literal.value = std::stoi(string(get(0).value));
				advance(0);
				break;
			}

			default:
				advance(0);
				break;
		}
	}

	void parseVariableDef() {
		advance(0);

		if (!check(0) || !is(0, TokenType::symbol)) {
			expectToken(TokenType::symbol);
		}

		Variable& variable = pushStack<Variable>();
		variable.symbol = get(0).value;

		if (check(2) && is(1, TokenType::colon)) {
			if (is(2, TokenType::symbol)) {
				advance(1);
				parseType();
			} else if (is(2, TokenType::equal)) {
				advance(1);
				// deducing type
			} else {
				throw ParserException("expecting <symbol> or <equal>");
			}
		}

		if (check(0) && is(0, TokenType::equal)) {
			pushStack<Assignment>();
			advance(0);
			parseExpression();
			popStack();
		}

		popStack();
	}

	void parseType() {
		if (!is(0, TokenType::symbol)) {
			expectToken(TokenType::symbol);
		}

		// namespaced symbol
		if (check(1)) {
			if (is(1, TokenType::dot)) {
				Namespace& namespace_ = pushStack<Namespace>();
				namespace_.symbol = get(0).value;
				advance(1);
				parseType();
				popStack();
				return;
			} else if (is(1, TokenType::angleLeft)) {
				Generic& generic = pushStack<Generic>();
				generic.symbol = get(0).value;
				advance(1);
				parseType();

				// check for comma
				
				if (!is(0, TokenType::angleRight)) {
					expectToken(TokenType::angleRight);
				}

				popStack();
				advance(0);
				return;
			}
		}

		Type& type = add<Type>();
		type.symbol = get(0).value;
		advance(0);
	}

private:
	string unexpectToken(TokenType type) {
		throw ParserException("unexpected token: " + toString(type));
	}

	string expectToken(TokenType type) {
		throw ParserException("expected token: " + toString(type));
	}

private:
	bool check(size_t rindex) {
		return index + rindex < lexer.get().size();
	}

	bool is(size_t rindex, TokenType type) {
		return lexer.get()[index + rindex].type == type;
	}

	const Token& get(size_t rindex) {
		return lexer.get()[index + rindex];
	}

	void advance(size_t rindex) {
		index += rindex + 1;
	}

	template <class T>
	T& add() {
		shared_ptr<T> node = make_shared<T>();
		stack.back()->add(node);
		return *node.get();
	}

	template <class T>
	T& pushStack() {
		shared_ptr<T> node = make_shared<T>();
		stack.back()->add(node);
		stack.push_back(node);
		return *node.get();
	}

	void popStack() {
		if (stack.size() > 1) {
			stack.pop_back();
		}
	}

private:
	size_t index;
	Lexer lexer;
	vector<NodePtr> stack;
	NodePtr root;
};


