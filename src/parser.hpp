#ifndef WOF_PARSER_HPP
#define WOF_PARSER_HPP

#include <string>

void wof_parse_line(std::string line,std::string& output,
	std::string& def_out,std::string& def_in);

#endif