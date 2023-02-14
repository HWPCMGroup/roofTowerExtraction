#ifndef READANDWRITEPC_H
#define READANDWRITEPC_H
 

#include "PointDefination.h"
#include "point_types.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


namespace ReadAndWritePC
{
	void StringSplit(const  std::string & str, const  char SplitChar[], std::vector<std::string> & strArray)
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
	
	void readPylonPosFile_(std::vector<wl::Tower> &PylonPos, std::string &PylonPosFile)
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
				StringSplit(strBuff, split, strArray);
				if (strArray.size() >= 3)
				{
					pt.x = std::atof(strArray[1].c_str());
					pt.y = std::atof(strArray[2].c_str());
					PylonPos.push_back(pt);
				}
				strBuff.clear();
			}
			fin.close();
		}
	}

	void ReadTxtData(const char* str, std::vector<wl::LASPoint>&Data)//data相当于索引(文件名，索引）
	{
		std::ifstream ReadDataTxt(str, ios::in);
		if (!ReadDataTxt.is_open()) {
			return;
		}
		while (!ReadDataTxt.eof()) {
			std::string currentLine;
			getline(ReadDataTxt, currentLine);
			//创建一个用于存储X,Y,Z的Point3D结构体
			wl::LASPoint param;
			sscanf_s(currentLine.c_str(), "%f %f %f", &param.x, &param.y, &param.z);
			//ReadDataTxt >> param.x >> param.y >> param.z;
			//std::cout << fixed<<setprecision(3)<<param.x << " " << param.y << " " << param.z << endl;
			if (param.x != 0 &&
				param.y != 0 &&
				param.z != 0) {
				Data.push_back(param);
			}
		}
		ReadDataTxt.close();
	}

	//读vector数组
	void read_vector(const char* str, std::vector<int>&vector_count)
	{
		std::ifstream ReadDataTxt(str, ios::in);
		if (!ReadDataTxt.is_open()) {
			return;
		}
		while (!ReadDataTxt.eof())
		{
			std::string currentLine;
			getline(ReadDataTxt, currentLine);
			int param;
			sscanf_s(currentLine.c_str(), "%f", &param);
			if (param!=0)
			{
				vector_count.push_back(param);
			}
		}
		ReadDataTxt.close();
	}
	
	//////////////////////////////////////////////////////////////////////////
	void writePts(const std::vector<wl::LASPoint> &Data, std::vector<std::vector<int>>&OutputIndex, const  char* str)
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
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	void writeXYZIRA(std::vector<wl::LASPoint> &cloud, const  char* str)
	{
		//输出点的x y z 强度 第几次回波  扫描角
		std::ofstream WriteTXT(str, std::ios::out | std::ios::binary);

		if (!WriteTXT.is_open())
			return;

		for (int i = 0; i < cloud.size(); ++i)
		{
			WriteTXT << std::fixed << std::setprecision(5)
				<< cloud[i].x << "," << cloud[i].y << "," << cloud[i].z<<endl;
			////扫描角
			//char ScanAngleRank_char = cloud[i].ScanAngleRank;
			//float ScanAngleRank_float = (float)ScanAngleRank_char;
			////WriteTXT<< ScanAngleRank_float << std::endl;
			////回波次数
			//char ReturnNumber_char = cloud[i].ReturnNumber;
			//float ReturnNumber_float = (float)ReturnNumber_char;
			//char NumberofReturns_char = cloud[i].NumberofReturns;
			//float NumberofReturns_float = (float)NumberofReturns_char;
			////short PointSourceID_short = cloud[i].PointSourceID;
			////float PointSourceID_float = (float)PointSourceID_short;
			//
			//WriteTXT << std::fixed << std::setprecision(0)
			//	<< "," << cloud[i].intensity << "," <<
			//	ReturnNumber_float << ","<< NumberofReturns_float << "," << 
			//	ScanAngleRank_float <<","/*<<PointSourceID_float*/;

			////////新增2
			////char ScanDirectionFlag= cloud[i].ScanDirectionFlag;
			////float ScanDirectionFlag_float = (float)ScanDirectionFlag;
			////		   
			////char EdgeofFlightLine = cloud[i].EdgeofFlightLine;
			////float EdgeofFlightLine_float = (float)EdgeofFlightLine;

			////char Classification= cloud[i].Classification;
			////float Classification_float = (float)Classification;

			////char UserData= cloud[i].UserData;
			////float UserData_float = (float)UserData;

			//double GPStime = cloud[i].GPStime;

			//////short Red= cloud[i].Red;
			////short Green= cloud[i].Green;
			////short Blue= cloud[i].Blue;
			////WriteTXT << "," << ScanDirectionFlag_float << "," <<
			////	EdgeofFlightLine_float << "," << Classification_float << "," <<
			////	UserData_float << ",";

			//WriteTXT << std::fixed << std::setprecision(15)<< GPStime<<std::endl /*<<Red<<","*/;
			////WriteTXT <<  "," <<Green << "," << Blue << std::endl;

		}

	}

	void writeXYZIRAGT(std::vector<wl::LASPoint> &cloud, std::vector<int>inputId,const  char* str,int class_id)
	{
		//输出点的x y z 强度 第几次回波  扫描角
		std::ofstream WriteTXT(str, std::ios::out | std::ios::binary);

		if (!WriteTXT.is_open())
			return;

		for (int i = 0; i < inputId.size(); ++i)
		{
			WriteTXT << std::fixed << std::setprecision(3)
				<< cloud[inputId[i]].x << "," << cloud[inputId[i]].y << "," << cloud[inputId[i]].z;
			////扫描角
			//char ScanAngleRank_char = cloud[inputId[i]].ScanAngleRank;
			//double ScanAngleRank_float = (double)ScanAngleRank_char;
			////WriteTXT<< ScanAngleRank_float << std::endl;
			////回波次数
			//char ReturnNumber_char = cloud[inputId[i]].ReturnNumber;
			//double ReturnNumber_float = (double)ReturnNumber_char;
			WriteTXT << "," << cloud[inputId[i]].intensity<< "," << /* ReturnNumber_float << "," 
				<< ScanAngleRank_float<<","<<*/class_id << std::endl;
		}

	}

	//输出双重某一种数据类型的数据集
	template<typename T>
	void writeDoubleDataVec(std::vector<std::vector<T>>input_data, const char *str)
	{
		std::ofstream WriteTXT(str, std::ios::out | std::ios::binary);

		if (!WriteTXT.is_open())
			return;

		for (int i = 0; i < input_data.size(); ++i)
		{
			for (int j=0;j<input_data[i].size();++j)
			{
				WriteTXT << std::fixed << std::setprecision(3) <<  input_data[i][j] << std::endl;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void writePtsSingleTower( std::vector<wl::LASPoint> &Data, const std::vector<int>&OutputIndex, const  char* str)
	{
		std::ofstream WriteTXT(str, std::ios::out | std::ios::binary);

		if (!WriteTXT.is_open())
			return;

		for (int i = 0; i < OutputIndex.size(); ++i)
		{
			WriteTXT << std::fixed << std::setprecision(3) << Data[OutputIndex[i]].x << " " <<
				Data[OutputIndex[i]].y << " " << Data[OutputIndex[i]].z << " " << 1<< std::endl;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//输出一个点
	void writeOnePt(const wl::LASPoint &Data,const  char* str)
	{
		std::ofstream WriteTXT(str, std::ios::out | std::ios::binary);

		if (!WriteTXT.is_open())
			return;

			WriteTXT << std::fixed << std::setprecision(3) << Data.x << " " <<
				Data.y << " " << Data.z << " " << std::endl;
	}

	void writePtsByClassify(std::vector<wl::LASPoint> &Data, std::vector<int>&OutputIndex, const  char* str)
	{
		std::ofstream WriteTXT(str, std::ios::out | std::ios::binary);

		if (!WriteTXT.is_open())
			return;

		for (int i = 0; i < OutputIndex.size(); ++i)
		{
			WriteTXT << std::fixed << std::setprecision(3) << Data[OutputIndex[i]].x << " " <<
				Data[OutputIndex[i]].y << " " << Data[OutputIndex[i]].z << " " << Data[OutputIndex[i]].classifyId << std::endl;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void writePtsForEachFile(
		std::vector<wl::LASPoint> &Data,
		std::vector<std::vector<int>>&OutputIndex)
	{
		for (size_t i = 0; i < OutputIndex.size(); i++)
		{
			std::ofstream fout("F:\\1课题组2020\\Code\\jiquan\\结果\\cluster"
				+ std::to_string(i) + ".txt");

			for (size_t j = 0; j < OutputIndex[i].size(); j++)
			{
				fout << std::fixed << std::setprecision(3) <<
					Data[OutputIndex[i][j]].x << " " <<
					Data[OutputIndex[i][j]].y << " " <<
					Data[OutputIndex[i][j]].z << " " << std::endl;
			}
			fout << std::flush;
			fout.close();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void writePtsForEachFile_int(
		std::vector<wl::LASPoint> &Data,
		std::vector<std::vector<int>>&OutputIndex)
	{
		for (size_t i = 0; i < OutputIndex.size(); i++)
		{
			//if (OutputIndex[i].size()*gridManagement._grid_width*gridManagement._grid_length < 5)
			//	continue;

			///	逐个格网输出结果
			std::ofstream fout("F:\\1课题组2020\\Code\\jiquan\\结果\\cluster"
				+ std::to_string(i) + ".txt");

			///	遍历区域生长格网块中每个格网
			for (size_t j = 0; j < OutputIndex[i].size(); j++)
			{
				////		将格网坐标数组存入点数组中
				//std::vector<int int> &ptsIndexs = gridManagement.Square2D[regionGrowGridIndexsGroup[i][j]].IdArray;

				//		遍历点索引，输出点的三维坐标
				//for (size_t m = 0; m < ptsIndexs.size(); m++)
				//{
				fout << std::fixed << std::setprecision(3) <<
					Data[OutputIndex[i][j]].x << " " <<
					Data[OutputIndex[i][j]].y << " " <<
					Data[OutputIndex[i][j]].z << " " << std::endl;
				//}
			}
			fout << std::flush;
			fout.close();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//输出双重点集
	void writeDoublePts(std::vector<std::vector<wl::LASPoint>>&pts, const  char* str)
	{
		std::ofstream WriteTXT(str, std::ios::out | std::ios::binary);

		if (!WriteTXT.is_open())
			return;

		for (int i = 0; i < pts.size(); ++i)
		{
			for (int j = 0; j < pts[i].size(); ++j)
			{
				WriteTXT << std::fixed << std::setprecision(3) << pts[i][j].x << " " <<
					pts[i][j].y << " " << pts[i][j].z << " " << j << std::endl;
			}
		}
	}

	//输出点密度
	template<typename T>
	void writePtsdensity(std::vector<T>&density, const  char* str)
	{
		std::ofstream WriteTXT(str, std::ios::out | std::ios::binary);

		if (!WriteTXT.is_open())
			return;

		for (int i = 0; i < density.size(); ++i)
		{
			WriteTXT << std::fixed << std::setprecision(3) << i << " " << density[i] << std::endl;
		}
	}

	//只输入点 从而输出文件
	void writeInPts(std::vector<wl::LASPoint>&pts, const char *str)
	{
		std::ofstream WriteTXT(str, std::ios::out | std::ios::binary);

		if (!WriteTXT.is_open())
			return;

		for (int i = 0; i < pts.size(); ++i)
		{
				WriteTXT << std::fixed << std::setprecision(3) << pts[i].x << " " <<
					pts[i].y << " " << pts[i].z << " " << pts[i].classifyId<< std::endl;
		}

	}
}
#endif//READANDWRITEPC_H