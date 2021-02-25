
#pragma once
#include <vector>
#include "EpfFile.h"

struct BmpData
{
	int m_width;
	int m_height;
	std::vector<Pixel> m_data;
};


int bmpextract(std::string fileName, BmpData* out);
