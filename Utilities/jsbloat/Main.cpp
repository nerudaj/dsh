#include <iostream>
#include <Config.hpp>

#include "IO.hpp"
#include "Usage.hpp"
#include "Logger.hpp"
#include "Obfuscation.hpp"

Logger logger; // Declaration of extern variable

int main(int argc, char *argv[]) {
	cfg::Args args;
	args.setupArguments("ho:v:H:");

	try {
		args.parse(argc, argv);
	}
	catch (...) {
		printHelp(argv[0]);
		return 1;
	}

	if (args.isSet('h')) {
		printHelp(argv[0]);
		return 1;
	}
	
	logger.setLoggingLevel(args.isSet('v') ? args.getArgumentValue('v').asInt() : 2);

	// Grab file names
	std::vector<std::string> filenames = args.getPositionalArguments();
	
	if (filenames.empty()) {
		logger.warning("jsbloat", "No input filenames given, nothing to do");
		return 0;
	}

	// Concatenate all files into one
	auto file = io::concatenateSourceFiles(filenames);
	file.replaceString(" (", "(");
	logger.debug("Loading done", "Concatenated size: " + std::to_string(file.getContent().size()));
	
	// Obfuscate everything
	obfuscateStaticIdentifiers(file);
	file.replaceString("'static';", "");
	obfuscateIds(file);
	obfuscateEnums(file);
	
	if (args.isSet('H')) {
		auto hints = io::loadHintFile(args.getArgumentValue('H').asString());
		obfuscateHinted(hints, file);
	}
	
	logger.debug("Minification done", "Minified size: " + std::to_string(file.getContent().size()));
	
	// Export
	std::string outFileName = args.isSet('o') ?
			args.getArgumentValue('o').asString() : 
			"concat.min.js";
	
	file.saveToFile(outFileName);
	
	return 0;
}