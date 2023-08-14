#include "lexer.h"

int main(int argc, char** argv) {
	if (argc == 1) {
		cout << "please specify the input file\n";
		return 1;
	}

	fs::path path(argv[1]);
	
	if (!fs::exists(path)) {
		cout << "file does not exist\n";
		return 1;
	}

	if (fs::is_directory(path)) {
		cout << "not a file\n";
		return 1;
	}

	size_t fileSize = fs::file_size(path);
	ifstream fileStream(path);
	string fileContent(fileSize, '\0');
	fileStream.read(fileContent.data(), fileSize);

	Lexer lexer;
	lexer.tokenize(fileContent);

	return 0;
}
