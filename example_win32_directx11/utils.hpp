#pragma once
#include <filesystem> 
#include <string> 
#include <fstream>
#include "skStr.h"
#include "json.hpp"

bool IsRunAsAdmin() {
	HANDLE hToken;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION elevation;
		DWORD size;
		if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &size)) {
			CloseHandle(hToken);
			return elevation.TokenIsElevated != 0;
		}
		CloseHandle(hToken);
	}
	return false;
}

void SetScreenToBlack() {
	HWND hDesktop = GetDesktopWindow();
	HDC hdc = GetDC(hDesktop);
	RECT rect;
	GetClientRect(hDesktop, &rect);

	// Fill the screen with a black rectangle
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

	ReleaseDC(hDesktop, hdc);
}

void RestoreScreen() {
	HWND hDesktop = GetDesktopWindow();
	HDC hdc = GetDC(hDesktop);
	RECT rect;
	GetClientRect(hDesktop, &rect);

	// Fill the screen with a white rectangle (you can use any color)
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	ReleaseDC(hDesktop, hdc);
}
using json = nlohmann::json;

std::string ReadFromJson(std::string path, std::string section) 
{
	if (!std::filesystem::exists(path))
		return skCrypt("File Not Found").decrypt();
	std::ifstream file(path);
	json data = json::parse(file);
	return data[section];
}

bool CheckIfJsonKeyExists(std::string path, std::string section) 
{
	if (!std::filesystem::exists(path))
		return skCrypt("File Not Found").decrypt();
	std::ifstream file(path);
	json data = json::parse(file);
	return data.contains(section);
}

bool WriteToJson(std::string path, std::string name, std::string value, bool userpass, std::string name2, std::string value2) 
{
	json file;
	if (!userpass) 
	{
		file[name] = value;
	}
	else
	{
		file[name] = value;
		file[name2] = value2;
	}

	std::ofstream jsonfile(path, std::ios::out);
	jsonfile << file;
	jsonfile.close();
	if (!std::filesystem::exists(path))
		return false;

	return true;
}
