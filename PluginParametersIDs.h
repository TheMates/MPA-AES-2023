#pragma once

#include <string>

// Enum for fast identification
enum ePluginParameters
{
	ParamFloat,
	ParamInt,

	NumPluginParameters
};

// Parameter IDs, used by DAW
static std::string PARAMETER_IDS[NumPluginParameters]
{
	"ParFloat1",
	"ParInt1",
};

// Parameter names - just for display
static std::string PARAMETER_NAMES[NumPluginParameters]
{
	"Parameter float 1",
	"Parameter int 1",
};

