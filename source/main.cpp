#include "transpiler.h"

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

	try {
		ifstream file(path);
		size_t fileSize = fs::file_size(path);
		string fileContent(fileSize, '\0');
		file.read(fileContent.data(), fileSize);
		
		Transpiler transpiler;
		transpiler.transpile(string_view(fileContent.data(), fileContent.size()));
		
		std::cout << "\n[cpp]\n";
		std::cout << transpiler.get() << "\n";
	} catch (const ParserException& exception) {
		std::cout << "parsing failed: " << exception.what() << "\n";
	} catch (const std::exception& exception) {
		std::cout << "exception is throwed: " << exception.what() << "\n";
	}

	return 0;
}
