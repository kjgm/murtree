﻿//Distributed under the MIT license, see License.txt
//Copyright © 2022 Emir Demirović

#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <limits>

//import feature vector binary
#include "../Data Structures/feature_vector_binary.h"

//reserve special keyword for help

//todo better error handling; also include these checks: 
//-parameters with the same name but different type can be defined...
//-need to ensure the default parameter value for strings is allowed...

namespace MurTree
{
class ParameterHandler
{
public:
	// This parameter is needed for the solver to not depend exclusively on a file read 
	// To be able to call the Solver, the default value is nullptr
	void SetData(const std::vector<std::vector<FeatureVectorBinary>>& feature_vectors_ = {} ) {
        data_ = feature_vectors_;
    }
	
	const std::vector<std::vector<FeatureVectorBinary>>& GetData() const {
        return data_;
    }

	void DefineNewCategory(const std::string& category_name, const std::string short_description = "");
	void DefineStringParameter(const std::string& parameter_name, const std::string& short_description, const std::string& default_value,
		const std::string& category_name, const std::vector<std::string>& allowed_values = std::vector<std::string>()); //empty vector of allowed values means all values are allowed
	void DefineIntegerParameter(const std::string& parameter_name, const std::string& short_description, int64_t default_value, const std::string& category_name, int64_t min_value = INT64_MIN, int64_t max_value = INT64_MAX);
	void DefineBooleanParameter(const std::string& parameter_name, const std::string& short_description, bool default_value, const std::string& category_name);
	void DefineFloatParameter(const std::string& parameter_name, const std::string& short_description, double default_value, const std::string& category_name, double min_value = std::numeric_limits<double>::min(), double max_value = std::numeric_limits<double>::max());

	void SetStringParameter(const std::string& parameter_name, const std::string& new_value);
	void SetIntegerParameter(const std::string& parameter_name, int64_t new_value);
	void SetBooleanParameter(const std::string& parameter_name, bool new_value);
	void SetFloatParameter(const std::string& parameter_name, double new_value);

	std::string GetStringParameter(const std::string& parameter_name) const;
	int64_t GetIntegerParameter(const std::string& parameter_name) const;
	bool GetBooleanParameter(const std::string& parameter_name) const;
	double GetFloatParameter(const std::string& parameter_name) const;

	//parameters are expected in the following form "-[parameter_name] [parameter_value]"
	void ParseCommandLineArguments(int argc, char* argv[]);

	void PrintParametersDifferentFromDefault(std::ostream& out = std::cout);
	void PrintParameterValues(std::ostream& out = std::cout);
	void PrintHelpSummary(std::ostream& out = std::cout);

private:
	std::vector<std::vector<FeatureVectorBinary>> data_;
	void CheckStringParameter(const std::string& parameter_name, const std::string& value);
	void CheckIntegerParameter(const std::string& parameter_name, int64_t value);
	void CheckBooleanParameter(const std::string& parameter_name, bool value);
	void CheckFloatParameter(const std::string& parameter_name, double value);

	struct StringEntry { std::string name, short_description, default_value, current_value, category_name; std::vector<std::string> allowed_values; };
	struct IntegerEntry { std::string name, short_description, category_name; int64_t default_value, current_value, min_value, max_value; };
	struct BooleanEntry { std::string name, short_description, category_name; bool default_value, current_value; };
	struct FloatEntry { std::string name, short_description, category_name; double default_value, current_value, min_value, max_value; };
	struct PairNameType { std::string name, type; bool operator==(const std::string& param_name) { return this->name == param_name; }; };
	struct Category { std::string name, short_description; std::vector<PairNameType> parameters; bool operator==(const std::string& category_name) { return this->name == category_name; } };

	std::vector<Category> categories_;
	std::map<std::string, StringEntry> parameters_string_;
	std::map<std::string, IntegerEntry> parameters_integer_;
	std::map<std::string, BooleanEntry> parameters_boolean_;
	std::map<std::string, FloatEntry> parameters_float_;
};
}