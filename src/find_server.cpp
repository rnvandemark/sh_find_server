#include "sh_find_server/find_server.hpp"

#include <sh_common/ros_names.hpp>

#define HTTP_VERSION_PARAM_NAME sh::names::params::FIND_HTTP_VERSION
#define SERVER_HOST_PARAM_NAME sh::names::params::FIND_SERVER_HOST
#define SERVER_PORT_PARAM_NAME sh::names::params::FIND_SERVER_PORT

namespace sh {

FindServer::FindServer() :
    FindBaseNode("find_server")
{
}
FindServer::~FindServer()
{
}

}

int main(int argc, char** argv) 
{
    // Create our node
    rclcpp::init(argc, argv);
    auto node = std::make_shared<sh::FindServer>();

    // Get all of the values off of the parameter server
    node->declare_parameter<std::string>(HTTP_VERSION_PARAM_NAME);
    const std::string http_version = node->get_parameter(HTTP_VERSION_PARAM_NAME).as_string();
    node->declare_parameter<std::string>(SERVER_HOST_PARAM_NAME);
    const std::string server_host = node->get_parameter(SERVER_HOST_PARAM_NAME).as_string();
    node->declare_parameter<int>(SERVER_PORT_PARAM_NAME);
    const int server_port = node->get_parameter(SERVER_PORT_PARAM_NAME).as_int();

    // Init communication with the FIND server and spin the node
    assert(node->init_communication(http_version, server_host, server_port));
    rclcpp::spin(node);

    return 0;
}
