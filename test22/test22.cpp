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
#include <string>

class Configuration {
public:
	Configuration(std::string f) : m_file(f) {};
	~Configuration() {}
	// parse generic configuration file
	int parse();
private:
	std::string m_file;
	std::map <std::string, std::string> m_options;
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

int main() {
	Configuration* conf = new Configuration("configuration.cfg");

	conf->parse();

	delete conf;

	return 0;
}

