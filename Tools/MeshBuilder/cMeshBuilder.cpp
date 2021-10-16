#include "cMeshBuilder.h"

#include <Tools/AssetBuildLibrary/Functions.h>
#include <Engine/Platform/Platform.h>

eae6320::cResult eae6320::Assets::cMeshBuilder::Build(const std::vector<std::string>& i_arguments) {
	eae6320::cResult result = Results::Success;
	std::string errorMessage;
	result = eae6320::Platform::CopyFileW(m_path_source, m_path_target, false, true, &errorMessage);
	if (result) {
		return Results::Success;
	}
	else {
		OutputErrorMessageWithFileInfo(m_path_source, errorMessage.c_str());
		return Results::Failure;
	}
}
