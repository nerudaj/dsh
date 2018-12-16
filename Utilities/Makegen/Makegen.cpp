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
		std::string projectName = config["Project"]["name"].asString();
		
		save << "CC=g++\n";
		save << "INSTALLDIR=C:\\tools\\utils\n";
		save << "CFLAGS=" << config["Project"]["flags"].asString() << " -I$(INSTALLDIR) -L$(INSTALLDIR)\n";
		
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
			save << name << "=lib" << projectName << ".dll\n\n";
		}
		else {
			name = "BINNAME";
			save << name << "=" << projectName << ".exe\n\n";
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
			save << "$^ -o $@ -Wl,--out-implib,lib" << config["Project"]["name"].asString() << ".lib\n\n";
			
			// OUTPUT: $(CC) $(CFLAGS) [-shared] $(LIBS) [$(STATICS)] $^ -o $@
		}

		if (isLibrary && config["Project"]["tests"].asBool()) {
			save << "test: $(LIBNAME) testrunner.exe run_test\n\n";
			save << "testrunner.exe: tests/main.cpp\n";
			save << "\t$(CC) $(CFLAGS) -I./ -L./ $^ -o $@ ";
			save << "$(LIBS) ";
			if (hasStaticDeps) save << "$(STATICS) ";
			save << "-l" << config["Project"]["name"].asString() << "\n\n";
			save << "run_test:\n";
			save << "\tcls\n\ttestrunner\n\n";
		}

		// Create clean and install targets
		save << "clean:\n\tdel $(" << name << ") ";
		
		if (isLibrary) {
			save << "lib" << projectName << ".lib";
		}
		
		save << " *.o *.gch testrunner.exe\n\n";

		if (config["Project"]["install"].asBool()) {
			save << "install:\n";
			save << "\tcopy /y $(" << name << ") $(INSTALLDIR)\n";

			if (isLibrary) {
				save << "\t copy /y lib" << config["Project"]["name"].asString() << ".lib $(INSTALLDIR)\n";
				
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
		config["Project"]["tests"] = "true";

		config["Modules"]["installheaders"] = "";
		config["Project"]["install"] = "true";
	}
	else {
		config["Project"]["type"] = "binary";
		config["Project"]["name"] = "dummy";
		config["Project"]["install"] = "false";
	}

	config["Project"]["libs"] = "";
	config["Project"]["staticlibs"] = "";
	config["Project"]["flags"] = "-std=gnu++14 -Wall -Wextra -pedantic";

	config["Modules"]["names"] = "";

	return config.saveToFile(filename);
}