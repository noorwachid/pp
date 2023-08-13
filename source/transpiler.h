#pragma once

#include "parser.h"

class Transpiler {
public:
	void transpile(string_view content) {
		parser.parse(content);

		// visit(parser.get());
	}

	const string& get() const {
		return content;
	}

private:
	// void visit(const NodePtr& node) {
	// 	preVisit(node);
	//
	// 	for (const NodePtr& subnode : node->children) {
	// 		visit(subnode);
	// 	}
	//
	// 	postVisit(node);
	// }
	//
	// void preVisit(const NodePtr& node) {
	// 	switch (node->type) {
	// 		case NodeType::type:
	// 			generate(node->as<Type>().symbol);
	// 			generate(" ");
	// 			break;
	//
	// 		case NodeType::namespace_:
	// 			generate(node->as<Namespace>().symbol);
	// 			generate("::");
	// 			break;
	//
	// 		case NodeType::generic:
	// 			generate(node->as<Generic>().symbol);
	// 			generate("<");
	// 			break;
	// 		default: break;
	// 	}
	// }
	//
	// void postVisit(const NodePtr& node) {
	// 	switch (node->type) {
	// 		case NodeType::variable:
	// 			generate(node->as<Type>().symbol);
	// 			generate("\n");
	// 			break;
	//
	// 		case NodeType::generic:
	// 			generate("> ");
	// 			break;
	// 		default: break;
	// 	}
	// }
	//
	// void generate(const string& subcontent) {
	// 	content += subcontent;
	// }

private:
	string content;
	Parser parser;
};

