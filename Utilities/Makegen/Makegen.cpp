#include "Makegen.hpp"
#include <Config.hpp>
#include <Strings.hpp>
#include <fstream>

bool Makegen::generateMakefile(const std::string &infile) {
	Config config;
	
	if (!config.loadFromFile(infile)) {
		std::cerr << "ERROR:generateMakefile: Failed to load " << infile << std::endl;
		return false;
	}
	
	try {
		std::ofstream save ("Makefile");
		bool isLibrary = config["Project"]["type"] == "library";
		std::string name;
		std::vector<std::string> modules;
		Strings::split(';', config["Modules"]["names"].asString(), modules);
		
		save << "CC=g++\n";
		save << "INSTALLDIR=C:\\tools\\libs\n";
		save << "CFLAGS=-Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)\n";
		
		if (isLibrary) {
			name = "LIBNAME";
			save << name << "=lib" << config["Project"]["name"].asString() << ".dll\n";
		}
		else {
			name = "BINNAME";
			save << "LIBS=" << config["Project"]["libs"].asString() << "\n";
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
		save << "\t$(CC) ";
		if (isLibrary) save << "-shared ";
		else save << "$(CFLAGS) $(LIBS)";
		save << "$^ -o $@\n\n";
		
		// Create clean and install targets
		save << "clean:\n\tdel $(" << name << ") *.o *.gch\n\n";
		
		if (config["Project"]["install"].asBool()) {
			save << "install:\n";
			save << "\tcopy /y $(" << name << ") $(INSTALLDIR)";
			
			if (isLibrary) {
				for (auto module : modules) {
					save << "\tcopy /y " << module << ".hpp $(INSTALLDIR)";
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
	Config config;
	
	if (mode == Makegen::Mode::Library) {
		config["Project"]["type"] = "library";
		config["Project"]["name"] = "dummy";
		config["Project"]["install"] = "false";
		config["Modules"]["names"] = "dummy";
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