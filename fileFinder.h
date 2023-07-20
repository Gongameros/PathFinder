#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>

void findPathToFile(const std::filesystem::path& directory, const std::string& filename);
void initial(const std::filesystem::path& directory, const std::string& filename);