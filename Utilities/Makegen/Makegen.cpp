#include "Makegen.hpp"
#include <Config.hpp>
#include <Strings.hpp>
#include <fstream>

bool Makegen::generateMakefile(const std::string &infile) {
	cfg::Ini config;
	
	if (!config.loadFromFile(infile)) {
		std::cerr << "ERROR:generateMakefile: Failed to load " << infile << std::endl;
		return false;
	}
	
	try {
		std::ofstream save ("Makefile");
		bool isLibrary = config["Project"]["type"] == "library";
		std::string name;
		std::vector<std::string> modules, installheaders;
		Strings::split(';', config["Modules"]["names"].asString(), modules);
		Strings::split(';', config["Modules"]["installheaders"].asString(), installheaders);
		
		save << "CC=g++\n";
		save << "INSTALLDIR=C:\\tools\\utils\n";
		save << "CFLAGS=-Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)\n";
		
		save << "LIBS=" << config["Project"]["libs"].asString() << "\n";
		if (isLibrary) {
			name = "LIBNAME";
			save << name << "=lib" << config["Project"]["name"].asString() << ".dll\n\n";
		}
		else {
			name = "BINNAME";
			save << name << "=" << config["Project"]["name"].asString() << ".exe\n\n";
		}
		
		save << "all: $(" << name << ")\n\n";
		
		// Create module targets
		for (auto module : modules) {
			save << module << ".o: " << module << ".cpp " << module << ".hpp\n";
			save << "\t$(CC) $(CFLAGS) ";
			if (isLibrary) save << "-fPIC ";
			save << "$^ -c\n\n";
		}
		
		// Create main target
		save << "$(" << name << "): ";
		if (not isLibrary) save << "Main.cpp ";
		
		for (auto module : modules) {
			save << module << ".o ";
		}
		save << "\n";
		save << "\t$(CC) $(CFLAGS) ";
		if (isLibrary) save << "-shared ";
		save << "$(LIBS) $^ -o $@\n\n";
		
		// Create clean and install targets
		save << "clean:\n\tdel $(" << name << ") *.o *.gch\n\n";
		
		if (config["Project"]["install"].asBool()) {
			save << "install:\n";
			save << "\tcopy /y $(" << name << ") $(INSTALLDIR)\n";
			
			if (isLibrary) {
				for (auto header : installheaders) {
					save << "\tcopy /y " << header << ".hpp $(INSTALLDIR)\n";
				}
				
				
			}
		}
		
		save.close();
		save.clear();
	}
	catch (std::exception &e) {
		std::cerr << "ERROR:generateMakefile: " << e.what() << std::endl;
		return false;
	}
	
	return true;
}

bool Makegen::generateInfile(const std::string &filename, Makegen::Mode mode) {
	cfg::Ini config;
	
	if (mode == Makegen::Mode::Library) {
		config["Project"]["type"] = "library";
		config["Project"]["name"] = "dummy";
		config["Project"]["libs"] = "";
		config["Project"]["install"] = "false";
		config["Modules"]["names"] = "dummy";
		config["Modules"]["installheaders"] = "";
	}
	else {
		config["Project"]["type"] = "binary";
		config["Project"]["name"] = "dummy";
		config["Project"]["libs"] = "";
		config["Project"]["install"] = "false";
		config["Modules"]["names"] = "";
	}
	
	return config.saveToFile(filename);
}