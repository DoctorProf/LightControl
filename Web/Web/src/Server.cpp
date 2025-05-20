#include "../include/Server.h"

Server::Server(std::string base_url, int port) : server(base_url, port)
{
	server.set_connection_timeout(5);
	server.set_keep_alive(true);
	server.set_read_timeout(10);
}

json Server::getSettings()
{
	std::string url = "/getSettings";
	auto res = server.Get(url.c_str());
	if (res && res->status == 200) return json::parse(res->body);
	return "";
}
void Server::setSettings(std::string parameter_name, float value)
{
	std::string url = "/setSettings?" + parameter_name + "=" + std::to_string(value);
	auto res = server.Get(url.c_str());
}
void Server::setSettings(std::string parameter_name, std::string value)
{
	std::string url = "/setSettings?" + parameter_name + "=" + value;
	auto res = server.Get(url.c_str());
}
json Server::getModes()
{
	std::string url = "/modes";
	auto res = server.Get(url.c_str());
	if (res && res->status == 200) return json::parse(res->body);
	return "";
}

json Server::getModeParams()
{
	std::string url = "/getModeParams";
	auto res = server.Get(url.c_str());
	if (res && res->status == 200) return json::parse(res->body);
	return "";
}
void Server::setModeParams(std::string parameter_name, std::string internal_param, float parameter)
{
	std::string url = "/setModeParams?parameter_name=" + parameter_name + "&" + internal_param + "=" + std::to_string(parameter);
	std::cout << url << std::endl;
	auto res = server.Get(url.c_str());
}
void Server::setModeParams(std::string parameter_name, std::string internal_param, std::string parameter)
{
	std::string url = "/setModeParams?parameter_name=" + parameter_name + "&" + internal_param + "=%23" + parameter.substr(1);
	std::cout << url << std::endl;
	auto res = server.Get(url.c_str());
	std::cout << res.error() << std::endl;
	std::cout << 1;
}