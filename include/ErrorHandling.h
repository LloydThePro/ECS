#pragma once
#include <vector>
#include <sstream>
#include "Types.h"
namespace ECS {

	

	class ErrorHandling {

	public:
		
		static void logError(std::string errorMsg, std::string className, std::string codeLine, int lineNum);
		static void displayAllErrors();
		static void removeLastError();
		static void clearError();
		static bool doesAnErrorOccurred();
		static uint32_t getErrorCount();
		const ECS::ErrorInfo& getLastError();

	private:
		static std::vector<ECS::ErrorInfo> errorLog;




	};

}