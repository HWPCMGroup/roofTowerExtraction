#pragma once
#include "PointDefination.h"
#include "point_types.h"

#include <iostream>
#include <vector>
#include <fstream>
namespace read_las_pos_file
{
	void String_Split(const  std::string & str, const  char SplitChar[], std::vector<std::string> & strArray)
	{
		strArray.clear();
		std::string tempStr;
		bool Is_Split = false;
		int Num = strlen(SplitChar);
		if (str.size() > 0 && Num > 0)
		{
			for (auto & c : str)
			{
				for (int i = 0; i < Num; i++)
				{
					if (c == SplitChar[i])
					{
						Is_Split = true;
						break;
					}
				}
				if (Is_Split)
				{
					Is_Split = false;
					if (tempStr.size() > 0)
					{
						strArray.push_back(tempStr);
						tempStr.clear();
					}
				}
				else
				{
					tempStr.push_back(c);
				}
			}
			if (tempStr.size() > 0)
			{
				strArray.push_back(tempStr);
				tempStr.clear();
			}
		}
	}
	void read_pos_file(std::vector<wl::Tower> &PylonPos, std::string &PylonPosFile)
	{
		PylonPos.clear();
		std::ifstream fin;
		fin.open(PylonPosFile, std::ios_base::in);
		char split[6] = { ' ', '\n', '\t', ',' };
		if (fin.is_open())
		{
			std::vector<string> strArray;
			wl::Tower pt;
			string strBuff;
			while (std::getline(fin, strBuff, '\n'))
			{
				String_Split(strBuff, split, strArray);
				if (strArray.size() >= 3)
				{
					pt.x = std::atof(strArray[0].c_str());
					pt.y = std::atof(strArray[1].c_str());
					PylonPos.push_back(pt);
				}
				strBuff.clear();
			}
			fin.close();
		}
	}
	void read_txt_file(std::vector<wl::LASPoint> &inputPts, std::string inputFile)
	{
		inputPts.clear();
		std::ifstream fin;
		fin.open(inputFile, std::ios_base::in);
		char split[6] = { ' ', '\n', '\t', ',' };
		if (fin.is_open())
		{
			std::vector<string> strArray;
			wl::LASPoint pt;
			string strBuff;
			while (std::getline(fin, strBuff, '\n'))
			{
				String_Split(strBuff, split, strArray);
				if (strArray.size() >= 3)
				{
					pt.x = std::atof(strArray[0].c_str());
					pt.y = std::atof(strArray[1].c_str());
					pt.z = std::atof(strArray[2].c_str());
					inputPts.push_back(pt);
				}
				strBuff.clear();
			}
			fin.close();
		}

	}

	void write_pii_file(const std::vector<wl::LASPoint> &Data, std::vector<std::vector<int>>&OutputIndex, const  char* str)
	{
		std::ofstream WriteTXT(str, std::ios::out | std::ios::binary);

		if (!WriteTXT.is_open())
			return;

		for (int i = 0; i < OutputIndex.size(); ++i)
		{
			for (int j = 0; j < OutputIndex[i].size(); ++j)
			{
				WriteTXT << std::fixed << std::setprecision(3) << Data[OutputIndex[i][j]].x << " " <<
					Data[OutputIndex[i][j]].y << " " << Data[OutputIndex[i][j]].z << " " << j << std::endl;
			}
		}
	}
	void write_pi_file(const std::vector<wl::LASPoint> &Data,const std::vector<int>&OutputIndex, const  char* str)
	{
		std::ofstream WriteTXT(str, std::ios::out | std::ios::binary);

		if (!WriteTXT.is_open())
			return;

		for (int i = 0; i < OutputIndex.size(); ++i)
		{
			WriteTXT << std::fixed << std::setprecision(3) << Data[OutputIndex[i]].x << " " <<
				Data[OutputIndex[i]].y << " " << Data[OutputIndex[i]].z << " " << 1 << std::endl;
		}
	}
	void write_p_file(const std::vector<wl::LASPoint> &Data, const  char* str)
	{
		std::ofstream WriteTXT(str, std::ios::out | std::ios::binary);

		if (!WriteTXT.is_open())
			return;

		for (int i = 0; i < Data.size(); ++i)
		{
			WriteTXT << std::fixed << std::setprecision(3) << Data[i].x << " " <<
				Data[i].y << " " << Data[i].z << " " << 1 << std::endl;
		}
	}

}