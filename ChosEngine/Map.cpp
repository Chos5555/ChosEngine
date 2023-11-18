#include <iostream>
#include <fstream>
#include <string>

#include "Map.h"

Map::Map(const char* fileName)
{
    LoadFromFile(fileName);
}

void Map::LoadFromFile(const char* name)
{
    std::string line;
    std::ifstream mapFile(name);
    if (mapFile.is_open())
    {
        while (std::getline(mapFile, line))
        {
            if (line.starts_with("Size"))
            {
                size_t start = line.find("Size");
                line.erase(start, sizeof("Size"));

                size = std::stoi(line);
            }
            else if (line.starts_with("Data"))
            {
                data = new uint8_t[size * size];

                for (size_t i = 0; i < size; i++)
                {
                    std::getline(mapFile, line);

                    size_t pos = 0;
                    size_t j = 0;
                    std::string token;
                    while ((pos = line.find(",")) != std::string::npos) {
                        token = line.substr(0, pos);
                        data[(i * size) + j] = std::stoi(token);

                        line.erase(0, pos + 2);

                        ++j;
                    }
                }
            }
            else if (line.starts_with("StartPos"))
            {
                size_t start = line.find("StartPos");
                line.erase(start, sizeof("StartPos"));

                size_t comma = line.find(", ");
                std::string x = line.substr(0, comma);
                std::string y = line.substr(comma + 2, line.length() - x.length() - 2);

                startPosition = VectorFloat(std::stof(x), std::stof(y));
            }
            else if (line.starts_with("StartDir"))
            {
                size_t start = line.find("StartDir");
                line.erase(start, sizeof("StartDir"));

                size_t comma = line.find(", ");
                std::string x = line.substr(0, comma);
                std::string y = line.substr(comma + 2, line.length() - x.length() - 2);

                startDirection = VectorFloat(std::stof(x), std::stof(y));
                
                startDirection.Normalize();
            }
            else if (line.starts_with("StartVPl"))
            {
                size_t start = line.find("StartVPl");
                line.erase(start, sizeof("StartVPl"));

                size_t comma = line.find(", ");
                std::string x = line.substr(0, comma);
                std::string y = line.substr(comma + 2, line.length() - x.length() - 2);

                startViewPlane = VectorFloat(std::stof(x), std::stof(y));
            }
        }
        mapFile.close();
    }
}
