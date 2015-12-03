#pragma once
#include "Country_Data.h"
class Country_Data
{
public:
	Country_Data();
	~Country_Data();
	struct Value
	{
		std::string ShortName, LongName;
		in_addr from, to;
	};

	std::vector<Value> Base;
	std::string UpdateDB();
	int amount;//data size
	void print();
};

