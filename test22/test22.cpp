/*
 * test22.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: liu
 */

// check string operation whether have memory leakage

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

class Configuration; // forward declaration

class FileConfiguration {
	typedef enum FileParsingStatus_e {
	    SEARCHING_FILE,
	    SEARCHING_PATH
	}FileParsingStatus_t;

	friend Configuration; // debug purpose
public:
	FileConfiguration() : status(SEARCHING_FILE) {};
private:
	std::string name;
	std::string path;
	FileParsingStatus_t status;
};

typedef std::vector <FileConfiguration> FileConfigurationList;

class Configuration {
public:
	Configuration(std::string f) : m_file(f) {};
	~Configuration() {}
	// parse generic configuration file
	int parse();
	// parse duplicated record in configuration file
	// parse file configuration file
	int parse_file();
	void dump_filelist();
private:
	std::string m_file;
	// non-duplicated configuration can be put into map
	std::map <std::string, std::string> m_options;
	// duplicated configuration can not be put into map, so put class into
	// vector
	FileConfigurationList m_filelist;
};

int Configuration::parse() {
	// associate the file and open the file
	std::ifstream cfgfile (m_file.c_str(), std::ifstream::in);

	if (cfgfile.good() == false) {
	    return -1;
	}

	for (std::string line; std::getline(cfgfile, line);) {
	     std::string id, val;
	     std::size_t found;

	//std::cout << "line " << line << std::endl;
	if (line[0] == '#') {
	    continue;
	}

	found = line.find('=', 0);
	if (found != std::string::npos) {
	    //std::cout << "found '=' at " << line.find('=', 0) << std::endl;
	    id = line.substr(0, found);
	    val = line.substr(found + 1, std::string::npos);
	    m_options[id] = val;
	    }
	}

	cfgfile.close();

    // dump the configuration options
	for (std::map<std::string, std::string>::iterator it = m_options.begin(); it != m_options.end(); it++) {
	    std::cout << it->first << " => " << it->second << std::endl;
	}
	return 0;
}

int Configuration::parse_file() {
	FileConfiguration* file = NULL;

	std::ifstream cfgfile (m_file.c_str(), std::ifstream::in);
	for (std::string line; std::getline(cfgfile, line);) {
		std::string id, val;
		std::size_t found;

		//std::cout << "line " << line << std::endl;
		if (line[0] == '#') {
		    continue;
		}

		found = line.find('=', 0);
		if (found != std::string::npos) {
		    //std::cout << "found '=' at " << line.find('=', 0) << std::endl;
		    id = line.substr(0, found);
		    val = line.substr(found + 1, std::string::npos);
		    if (file == NULL) {
		    	file = new FileConfiguration();
		    }
		    switch (file->status) {
		    case FileConfiguration::SEARCHING_FILE:
		    	if (id.compare("FILE_NAME") == 0) {
		    		file->name = val;
		    		file->status = FileConfiguration::SEARCHING_PATH;
		    	} else if (id.compare("FILE_PATH") == 0) {
		    		// wrong configure file
		    		std::cout << "Unexpected Configuration " << id << " => " << val << std::endl;
		    		// reset a new record
		    		delete file;
		    		file = NULL;
		    	}
		    	break;
		    case FileConfiguration::SEARCHING_PATH:
		    	if (id.compare("FILE_PATH") == 0) {
		    		file->path = val;
		    	    // found valid pair name:path
		    		m_filelist.push_back(*file);
			    	delete file;
			    	file = NULL;
		    	} else if (id.compare("FILE_NAME") == 0) {
		    	    // wrong configure file
		    	    std::cout << "Unexpected Configuration " << id << " => " << val << std::endl;
		    	    delete file;
		    	    file = NULL;
		    	    // restart with a new record
		    	    file = new FileConfiguration();
		    	    file->name = val;
		    	    file->status = FileConfiguration::SEARCHING_PATH;
		    	}
		    	break;
		    default:
		    	break;
		    }
		}
	}

	if (file != NULL) {
		delete file;
		file = NULL;
	}

	return 0;
}

void Configuration::dump_filelist() {
	for (FileConfigurationList::iterator it = m_filelist.begin(); it != m_filelist.end(); it++) {
		std::cout << it->name << " => " << it->path << std::endl;
	}
	return;
}

int main() {
	Configuration* conf = new Configuration("configuration.cfg");

	conf->parse();

	delete conf;

	conf = new Configuration("configuration_file.cfg");
	conf->parse_file();
	// dump the file list
	conf->dump_filelist();

	delete conf;

	return 0;
}

