#include "parser.hpp"
#include <string>

std::string pre_rules(std::string def_out,std::string def_in)
{
	std::string pre;
	pre+="#You may need to add the following to /etc/rc.conf:\n";
	pre+="#  firewall_enable=\"YES\"\n";
	pre+="#  firewall_logging=\"YES\"\n";
	pre+="service ipfw start\n";
	pre+="ipfw -q -f flush\n";
	pre+="ipfw -q add check-state\n";
	pre+="ipfw -q add allow ip from any to any via lo0\n";
	if(def_out=="pass")
		pre+="ipfw -q add allow all from any to any out keep-state\n";
	if(def_in=="pass")
		pre+="ipfw -q add allow all from any to any in keep-state\n";
	return pre;
}

std::string post_rules(std::string def_out,std::string def_in)
{
	return "ipfw -q add deny log ip from any to any\n";
}

std::string gen_rule(wof_t wof)
{
	std::string rule;
	rule+="ipfw -q add ";
	if(wof.action=="deny")
		rule+="deny";
	else
		rule+="allow";
	rule+=" log quick ";
	std::string dir_str=" out";
	if(wof.dir=="<")
	{
		dir_str=" in ";
		std::swap(wof.l_ip,wof.f_ip);
		std::swap(wof.l_mask,wof.f_mask);
		std::swap(wof.l_port,wof.f_port);
	}
	rule+=wof.proto;
	rule+=" from "+wof.l_ip+"/"+wof.l_mask;
	if(wof.l_port!="0")
		rule+=" "+wof.l_port;
	rule+=" to "+wof.f_ip+"/"+wof.f_mask;
	if(wof.f_port!="0")
		rule+=" "+wof.f_port;
	rule+=dir_str;
	rule+=" keep-state";

	return rule;
}
