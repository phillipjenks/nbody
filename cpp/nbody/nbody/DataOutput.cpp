#include "stdafx.h"

#include <experimental/filesystem>
#include <sstream>
#include <iomanip>

#include <fstream>

#include "DataOutput.h"
#include "SimBody.h"

const std::string OUT_DIRECTORY = "output";

bool DataOutput::init() const {

	std::error_code errCode;
	std::experimental::filesystem::remove_all(OUT_DIRECTORY, errCode);

	int errVal = errCode.value();
	if (errVal) {
		std::cout << "Failed to clear out old output directory '" << OUT_DIRECTORY << "' with error: " << errCode.message() << std::endl;
		return false;
	}

	std::experimental::filesystem::create_directory(OUT_DIRECTORY, errCode);

	errVal = errCode.value();
	if (errVal) {
		std::cout << "Failed to create output directory '" << OUT_DIRECTORY << "' with error: " << errCode.message() << std::endl;
		return false;
	}

	return true;
}

void DataOutput::dumpOutput(double time, const VecBody& bodies) {

	std::stringstream fileNumber;
	fileNumber << std::setfill('0') << std::setw(4) << (dumpNumber++);

	std::string outFileName = "dump_" + fileNumber.str();

	using path = std::experimental::filesystem::path;
	path outPath = path(OUT_DIRECTORY) / path(outFileName);

	std::ofstream outFile;
	outFile.open(outPath.c_str(), std::ofstream::out);

	if (outFile.is_open()) {

		outFile << "time," << time;

		for (auto& body : bodies) {

			outFile << '\n' << body.getMass() << ',';
			const Vec3& pos = body.getPos();
			const Vec3& vel = body.getVel();

			outFile << pos.x << ',' << pos.y << ',' << pos.z << ',';
			outFile << vel.x << ',' << vel.y << ',' << vel.z;
		}
	}

	outFile.close();
}