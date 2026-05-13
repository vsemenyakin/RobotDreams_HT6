#include <cstring>
#include <iostream>
#include <fstream>
#include "ballistics.hpp"

#define DebugPrint

constexpr char inputFileName[]{ "input.txt" };

constexpr char outputFileName[]{ "output.txt" };
constexpr char outputDelimiter{ ' ' };

int main() {

	//--- Input ---

	float xd, yd, zd;
	float targetX, targetY;
	float attackSpeed;
	float accelerationPath;

	//NB: We assume that length of string is long enough for
	// all supported ammo names. It should be controlled
	char ammo_name[20];
	{
		std::ifstream inputFile{ inputFileName };
		if (!inputFile) {
			std::cerr << "Unable to open input file [" << inputFileName << "]";
			return 1;
		}

		inputFile >> xd;
		inputFile >> yd;
		inputFile >> zd;

		inputFile >> targetX;
		inputFile >> targetY;

		inputFile >> attackSpeed;

		inputFile >> accelerationPath;

		inputFile >> ammo_name;

		inputFile.close();
	}

#ifdef DebugPrint

	std::cout << "--- Input ---" << std::endl;

	std::cout << "xd: " << xd << std::endl;
	std::cout << "yd: " << yd << std::endl;
	std::cout << "zd: " << zd << std::endl;

	std::cout << "targetX: " << targetX << std::endl;
	std::cout << "targetY: " << targetY << std::endl;

	std::cout << "attackSpeed: " << attackSpeed << std::endl;

	std::cout << "accelerationPath: " << accelerationPath << std::endl;

	std::cout << "ammo_name: " << ammo_name << std::endl;

#endif //DebugPrint

	//--- Ammo params filling ---

	float ammo_m;
	float ammo_d;
	float ammo_l;
	if (strcmp(ammo_name, "VOG-17") == 0) {
		ammo_m = 0.35f;
		ammo_d = 0.07f;
		ammo_l = 0.0f;
	}
	else if (strcmp(ammo_name, "M67") == 0) {
		ammo_m = 0.6f;
		ammo_d = 0.1f;
		ammo_l = 0.0f;
	}
	else if (strcmp(ammo_name, "RKG-3") == 0) {
		ammo_m = 1.2f;
		ammo_d = 0.1f;
		ammo_l = 0.0f;
	}
	else if (strcmp(ammo_name, "GLIDING-VOG") == 0) {
		ammo_m = 0.45f;
		ammo_d = 0.1f;
		ammo_l = 1.0f;
	}
	else if (strcmp(ammo_name, "GLIDING-RKG") == 0) {
		ammo_m = 1.4f;
		ammo_d = 0.1f;
		ammo_l = 1.0f;
	}
	else {
		std::cerr << "Type of ammo [" << ammo_name << "] is unknown";
		return 1;
	}

#ifdef DebugPrint

	std::cout << "==========================={{{" << std::endl;

	std::cout << "attackSpeed: " << attackSpeed << std::endl;
	std::cout << "zd: " << zd << std::endl;
	std::cout << "ammo_m: " << ammo_m << std::endl;
	std::cout << "ammo_d: " << ammo_d << std::endl;
	std::cout << "ammo_l: " << ammo_l << std::endl;

#endif //DebugPrint

	float ammo_fligthTime;
	float h;
	computeAmmoDrop(ammo_fligthTime, h, attackSpeed, zd, ammo_m, ammo_d, ammo_l);

#ifdef DebugPrint

	std::cout << "ammo_fligthTime: " << ammo_fligthTime << std::endl;
	std::cout << "h: " << h << std::endl;

	std::cout << "===========================}}}" << std::endl;

#endif //DebugPrint

	//--- Drop point ---

	float fireX, fireY;
	bool maneuverUsed;
	float maneuverX, maneuverY;
	{
		const float deltaX = targetX - xd;
		const float deltaY = targetY - yd;
		const float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

		//Special case for zero distance
		float deltaNormalX, deltaNormalY;
		{
			const bool isDistanceZero = (deltaX == 0.0f && deltaY == 0.0f);
			if (!isDistanceZero) {
				deltaNormalX = deltaX / distance;
				deltaNormalY = deltaY / distance;
			}
			else {
				deltaNormalX = 1.0f;
				deltaNormalY = 0.0f;
			}
		}

		if (distance > h + accelerationPath) {
			maneuverUsed = false;

			const float distanceToDropPoint = (distance - h);

			fireX = xd + deltaNormalX * distanceToDropPoint;
			fireY = yd + deltaNormalY * distanceToDropPoint;
		}
		else {
			maneuverUsed = true;

			const float distanceFromTargetToManeuverPoint = h + accelerationPath;
			maneuverX = targetX - distanceFromTargetToManeuverPoint * deltaNormalX;
			maneuverY = targetY - distanceFromTargetToManeuverPoint * deltaNormalY;

			fireX = maneuverX + deltaNormalX * accelerationPath;
			fireY = maneuverY + deltaNormalY * accelerationPath;
		}
	}

	//--- Output ---

	{
		std::ofstream outputFile{ outputFileName };
		if (!outputFile) {
			std::cerr << "Unable to create output file [" << outputFileName << "]";
			return 1;
		}

		if (maneuverUsed) {
			outputFile << maneuverX << outputDelimiter;
			outputFile << maneuverY << outputDelimiter;
		}

		outputFile << fireX << outputDelimiter;
		outputFile << fireY << outputDelimiter;

		outputFile.close();
	}

#ifdef DebugPrint

	std::cout << "--- Output ---" << std::endl;

	if (maneuverUsed) {
		std::cout << "maneuverX: " << maneuverX << std::endl;
		std::cout << "maneuverY: " << maneuverY << std::endl;
	}

	std::cout << "fireX: " << fireX << std::endl;
	std::cout << "fireY: " << fireY << std::endl;

#endif //DebugPrint

	return 0;
}
