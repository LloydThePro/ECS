#include "../include/ErrorHandling.h"
#include <iostream>
std::vector<ECS::ErrorInfo> ECS::ErrorHandling::errorLog;

void ECS::ErrorHandling::logError(std::string errorMsg, std::string className, std::string codeLine, int lineNum) {
	std::stringstream ss;
	ECS::ErrorInfo errorInfo;
	
	ss << "className: " << className << "\tLine: "<< codeLine << "\tLine number:" << lineNum << '\n';
	errorInfo.lineNum = lineNum;
	errorInfo.logInfo = ss.str();
	errorInfo.message = errorMsg;

	errorLog.push_back(std::move(errorInfo));
}

void ECS::ErrorHandling::displayAllErrors()
{
	if (errorLog.empty()) {
		std::cout << "<No error occured>\n";
	}

	for (const ECS::ErrorInfo& info : ECS::ErrorHandling::errorLog) {
		std::cout << '<' << info.message << '>' << "\n"  << info.logInfo  << '\n';
	}
}

void ECS::ErrorHandling::removeLastError()
{
	if (!errorLog.empty()) {
		errorLog.pop_back();
	}
}

void ECS::ErrorHandling::clearError()
{
	errorLog.clear();
}

bool ECS::ErrorHandling::doesAnErrorOccurred()
{
	if (!errorLog.empty())return true;

	return false;
}

uint32_t ECS::ErrorHandling::getErrorCount()
{
	return errorLog.size();
}

const ECS::ErrorInfo& ECS::ErrorHandling::getLastError()
{
	if (errorLog.empty()) {
		ECS::ErrorInfo info;
		info.lineNum = 0;
		info.message = "No error";
		info.logInfo = "No error";
		return info;
	}

	return errorLog.back();
}
