#include "Makegen.hpp"
#include <Config.hpp>
#include <Strings.hpp>
#include <fstream>

bool Makegen::generateMakefile(const std::string &infile, const std::string &outfile) {
	cfg::Ini config;
	
	if (!config.loadFromFile(infile)) {
		std::cerr << "ERROR:generateMakefile: Failed to load " << infile << std::endl;
		return false;
	}
	
	try {
		std::ofstream save (outfile);
		bool isLibrary = config["Project"]["type"] == "library";
		bool isStatic = config["Project"]["subtype"] == "static";
		bool hasStaticDeps = not config["Project"]["staticlibs"].asString().empty();
		std::string name;
		std::vector<std::string> modules, installheaders, statics, libs;
		Strings::split(';', config["Modules"]["names"].asString(), modules);
		Strings::split(';', config["Modules"]["installheaders"].asString(), installheaders);
		Strings::split(';', config["Project"]["libs"].asString(), libs);
		Strings::split(';', config["Project"]["staticlibs"].asString(), statics);
		
		save << "CC=g++\n";
		save << "INSTALLDIR=C:\\tools\\utils\n";
		save << "CFLAGS=-Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)\n";
		
		// List dynamic deps
		save << "LIBS=";
		for (auto lib : libs) {
			save << lib << " ";
		}
		save << "\n";

		// List static deps
		if (hasStaticDeps) {
			save << "STATICS=-Wl,--whole-archive ";
			
			for (auto lib : statics) {
				save << "$(INSTALLDIR)\\" << lib << " ";
			}
			
			save << "-Wl,--no-whole-archive\n";
		}
		
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
		
		// List modules to add to target
		for (auto module : modules) {
			save << module << ".o ";
		}
		save << "\n";
		
		// Rules to compile it
		if (isStatic) {
			save << "\tar rvs $@ $^\n\n";
		}
		else {
			// Basic gcc setup
			save << "\t$(CC) $(CFLAGS) ";
			
			// Make it shared
			if (isLibrary) save << "-shared ";
			
			// List dependencies
			save << "$(LIBS) ";
			if (hasStaticDeps) save << "$(STATICS) ";
			
			// Finalize
			save << " $^ -o $@\n\n";
			
			// OUTPUT: $(CC) $(CFLAGS) [-shared] $(LIBS) [$(STATICS)] $^ -o $@
		}
		
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
		config["Project"]["subtype"] = "dynamic";
		config["Project"]["name"] = "dummy";
		config["Project"]["libs"] = "";
		config["Project"]["staticlibs"] = "";
		config["Project"]["install"] = "false";
		config["Modules"]["names"] = "dummy";
		config["Modules"]["installheaders"] = "";
	}
	else {
		config["Project"]["type"] = "binary";
		config["Project"]["name"] = "dummy";
		config["Project"]["libs"] = "";
		config["Project"]["staticlibs"] = "";
		config["Project"]["install"] = "false";
		config["Modules"]["names"] = "";
	}
	
	return config.saveToFile(filename);
}