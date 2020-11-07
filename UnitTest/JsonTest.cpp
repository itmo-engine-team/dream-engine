#include "pch.h"

#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <filesystem>

class JsonTest /*: public ::testing::Test*/
{
    using json = nlohmann::json;

public:

   static  void JsonTest::TestJsRead()
   {
        std::ifstream file("Person.json");
        json j;

        file >> j;

        std::string objectName;
        std::string name;
        int age = 0;

        if (j.find("Object name") != j.end())
        {
            objectName = j["Object name"];
        }

        if (j.find("Name") != j.end())
        {
            name = j["Name"];
        }

        if (j.find("Age") != j.end())
        {
            age = j["Age"].get<int>();
        }

        std::cout << j << "\n";
        std::cout << objectName << "\n";
        std::cout << name << "\n";
        std::cout << age;
   }

   static void JsonTest::TestJsCreate(std::string fileRelativePath, std::string name, int age)
   {
        std::string pathToFile = fileRelativePath;
        json j;
        std::filesystem::path p(pathToFile);

        if (!std::filesystem::exists(pathToFile))
        {
            create_directories(p.parent_path());
        }
        std::cout << p.extension().string();
        j["Object name"] = p.stem().string();
        j["Name"] = name;
        j["Age"] = age;
       
        std::ofstream file(pathToFile);
        file << std::setw(4) << j << std::endl;
   }

   static void JsonTest::FindAssets()
   {
        std::string directory_name = "Content";
        std::string extension = ".asset";

        try // Exception for directories not found
        {
            for (auto& p : std::filesystem::recursive_directory_iterator(directory_name)) //For all files in folders
            {
                if (p.path().extension() != extension)
                    continue;

                std::ifstream file(p.path());
                json j;
                file >> j;
                
                std::cout << j["Name"];
            }
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << e.what() << '\n';
        }
   }
};

TEST(JsonTest, CreateTest)
{   
    JsonTest::TestJsCreate("Content/Person1.asset", "Alex", 25);
}

TEST(JsonTest, ReadTest)
{    
    JsonTest::TestJsRead();
}

TEST(JsonTest, FindTest)
{
    JsonTest::FindAssets();
}