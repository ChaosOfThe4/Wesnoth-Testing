#include "Config.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

bool ReadConfig(Config& config)
{
    std::ifstream configFile("C:/Users/Nickson/Desktop/DMA-Templates-master/config.cfg");
    if (!configFile.is_open())
    {
        std::cerr << "Failed to open config.cfg" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(configFile, line))
    {
        size_t pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        if (key == "KmboxIP") config.kmboxIP = value;
        else if (key == "KmboxPort") config.kmboxPort = std::stoi(value);
        else if (key == "KmboxUUID") config.kmboxUUID = value;
        else if (key == "KmboxComPort") config.KmboxComPort = std::stoi(value);
        else if (key == "screenWidth") config.screenWidth = std::stoi(value);
        else if (key == "screenHeight") config.screenHeight = std::stoi(value);
        else if (key == "ExampleBool") config.exampleBool = (value == "1");
        else if (key == "ExampleFloat") config.exampleFloat = std::stof(value);
        else if (key == "ExampleInt") config.exampleInt = std::stoi(value);
        else if (key == "KmboxType") config.kmboxType = value;
    }

    return true;
}

bool SaveConfig(const Config& config)
{
    std::ofstream configFile("config.cfg");
    if (!configFile.is_open())
    {
        std::cerr << "Failed to open config.cfg for writing" << std::endl;
        return false;
    }

    configFile << "KmboxIP=" << config.kmboxIP << std::endl;
    configFile << "KmboxPort=" << config.kmboxPort << std::endl;
    configFile << "KmboxUUID=" << config.kmboxUUID << std::endl;
    configFile << "KmboxComPort=" << config.KmboxComPort << std::endl;
    configFile << "screenWidth=" << config.screenWidth << std::endl;
    configFile << "screenHeight=" << config.screenHeight << std::endl;
    configFile << "ExampleBool=" << (config.exampleBool ? "1" : "0") << std::endl;
    configFile << "ExampleFloat=" << config.exampleFloat << std::endl;
    configFile << "ExampleInt=" << config.exampleInt << std::endl;
    configFile << "KmboxType=" << config.kmboxType << std::endl;

    return true;
}
