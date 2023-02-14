#ifndef  POINTDEFINATION_H
#define  POINTDEFINATION_H

#include<vector>
#include<list>
#include<string>
#include <utility>
#include<memory>

#define Sample_Variance 'V'
#define Standard_Deviation 'D'
#define _PI_ 3.14159265


namespace PointDef
{
	enum COORDINATE
	{
		X, Y, Z, XY, XZ, YZ, XYZ
	};

	class LasHeader
	{
	public:
		char file_signature[4];//4
		unsigned short file_source_id;//6
		unsigned short global_encoding;//8
		unsigned  project_id_guid_data_1;//12
		unsigned short project_id_guid_data_2;//14
		unsigned short project_id_guid_data_3;//16
		unsigned char project_id_guid_data_4[8];//24
		unsigned char version_major;//25
		unsigned char version_minor;//26
		char system_identifier[32];//58
		char generating_software[32];//90
		unsigned short file_creation_day_of_year;//92
		unsigned short file_creation_year;//94
		unsigned short header_size;//96
		unsigned  offset_to_point_data;//100
		unsigned  number_of_variable_length_records;//104
		unsigned char point_data_format_id;//105
		unsigned short point_data_record_length;//107
		unsigned  number_of_point_records;//111
		unsigned  number_of_points_by_return[5];//131
		double x_scale_factor;//139
		double y_scale_factor;//147
		double z_scale_factor;//155
		double x_offset;//163
		double y_offset;//171
		double z_offset;//179
		double max_x;
		double min_x;
		double max_y;
		double min_y;
		double max_z;
		double min_z;

		LasHeader()
		{
			file_signature[0] = 'L';
			file_signature[1] = 'A';
			file_signature[2] = 'S';
			file_signature[3] = 'F';
			file_source_id = 0;
			global_encoding = 0;
			project_id_guid_data_1 = 0;
			project_id_guid_data_2 = 0;
			project_id_guid_data_3 = 0;
			system_identifier[0] = 'M';
			system_identifier[1] = 'R';
			system_identifier[2] = '.';
			system_identifier[3] = 'C';
			system_identifier[4] = 'H';
			system_identifier[5] = 'E';
			system_identifier[6] = 'N';
			generating_software[0] = 'P';
			generating_software[1] = 'o';
			generating_software[2] = 'i';
			generating_software[3] = 'n';
			generating_software[4] = 't';
			generating_software[5] = 'C';
			generating_software[6] = 'l';
			generating_software[7] = 'o';
			generating_software[8] = 'u';
			generating_software[9] = 'd';
			for (auto i = 0; i < 32; i++)
			{
				if (i > 6)
				{
					system_identifier[i] = '\0';
					if (i > 9)
					{
						generating_software[i] = '\0';
					}
				}
				if (i < 8)
				{
					if (i < 5)
					{
						number_of_points_by_return[i] = 0;
					}
					project_id_guid_data_4[i] = 0;
				}
			}
			version_major = 1;
			version_minor = 2;
			file_creation_day_of_year = 0;
			file_creation_year = 0;
			header_size = 227;
			offset_to_point_data = 227;
			number_of_variable_length_records = 0;
			point_data_format_id = 3;
			point_data_record_length = 34;
			number_of_point_records = 0;
			x_scale_factor = 0.001;
			y_scale_factor = 0.001;
			z_scale_factor = 0.001;
			x_offset = 0;
			y_offset = 0;
			z_offset = 0;
			max_x = 0;
			min_x = 0;
			max_y = 0;
			min_y = 0;
			max_z = 0;
			min_z = 0;
		}
		LasHeader(int a)
		{
			file_signature[0] = 'L';
			file_signature[1] = 'A';
			file_signature[2] = 'S';
			file_signature[3] = 'F';
			file_source_id = 0;
			global_encoding = 0;
			project_id_guid_data_1 = 0;
			project_id_guid_data_2 = 0;
			project_id_guid_data_3 = 0;
			system_identifier[0] = 'M';
			system_identifier[1] = 'R';
			system_identifier[2] = '.';
			system_identifier[3] = 'C';
			system_identifier[4] = 'H';
			system_identifier[5] = 'E';
			system_identifier[6] = 'N';
			generating_software[0] = 'P';
			generating_software[1] = 'o';
			generating_software[2] = 'i';
			generating_software[3] = 'n';
			generating_software[4] = 't';
			generating_software[5] = 'C';
			generating_software[6] = 'l';
			generating_software[7] = 'o';
			generating_software[8] = 'u';
			generating_software[9] = 'd';
			for (auto i = 0; i < 32; i++)
			{
				if (i > 6)
				{
					system_identifier[i] = '\0';
					if (i > 9)
					{
						generating_software[i] = '\0';
					}
				}
				if (i < 8)
				{
					if (i < 5)
					{
						number_of_points_by_return[i] = 0;
					}
					project_id_guid_data_4[i] = 0;
				}
			}
			version_major = 1;
			version_minor = 2;
			file_creation_day_of_year = 0;
			file_creation_year = 0;
			header_size = 227;
			offset_to_point_data = 227;
			number_of_variable_length_records = 0;
			point_data_format_id = 3;
			point_data_record_length = 34;
			number_of_point_records = 0;
			x_scale_factor = 0.001;
			y_scale_factor = 0.001;
			z_scale_factor = 0.001;
			x_offset = a;
			y_offset = a;
			z_offset = a;
			max_x = 0;
			min_x = 0;
			max_y = 0;
			min_y = 0;
			max_z = 0;
			min_z = 0;
		}
		void reset()

		{
			file_signature[0] = 'L';
			file_signature[1] = 'A';
			file_signature[2] = 'S';
			file_signature[3] = 'F';
			file_source_id = 0;
			global_encoding = 0;
			project_id_guid_data_1 = 0;
			project_id_guid_data_2 = 0;
			project_id_guid_data_3 = 0;
			for (auto i = 0; i < 32; i++)
			{
				if (i < 8)
				{
					if (i < 5)
					{
						number_of_points_by_return[i] = 0;
					}
					project_id_guid_data_4[i] = 0;
				}
				system_identifier[i] = 0;
				generating_software[i] = 0;
			}
			version_major = 0;
			version_minor = 0;
			file_creation_day_of_year = 0;
			file_creation_year = 0;
			header_size = 0;
			offset_to_point_data = 0;
			number_of_variable_length_records = 0;
			point_data_format_id = 0;
			point_data_record_length = 0;
			number_of_point_records = 0;
			x_scale_factor = 0;
			y_scale_factor = 0;
			z_scale_factor = 0;
			x_offset = 0;
			y_offset = 0;
			z_offset = 0;
			max_x = 0;
			min_x = 0;
			max_y = 0;
			min_y = 0;
			max_z = 0;
			min_z = 0;
		}
	};

	class Point_LasV12
	{
	public:
		int x;
		int y;
		int z;
		unsigned short Intensity;
		unsigned char ReturnNumber : 3;//第几次回波
		unsigned char NumberofReturns : 3;// 总的回波数量
		unsigned char ScanDirectionFlag : 1;
		unsigned char EdgeofFlightLine : 1;
		unsigned char Classification;
		char ScanAngleRank;
		unsigned char UserData;
		unsigned short PointSourceID;
		double GPStime;
		unsigned short Red;
		unsigned short Green;
		unsigned short Blue;

		Point_LasV12()
		{
			x = y = z = 0;
			Intensity = 0;
			ReturnNumber = NumberofReturns = ScanDirectionFlag = EdgeofFlightLine = 0;
			Classification = 0;
			ScanAngleRank = 0;
			UserData = 0;
			PointSourceID = 0;
			GPStime = 0;
			Red = Green = Blue = 0;
		}
		Point_LasV12(int a)
		{
			x = y = z = a;
			Intensity = 0;
			ReturnNumber = NumberofReturns = ScanDirectionFlag = EdgeofFlightLine = 0;
			Classification = 0;
			ScanAngleRank = 0;
			UserData = 0;
			PointSourceID = 0;
			GPStime = 0;
			Red = Green = Blue = 0;
		}
		Point_LasV12(int a, int b, int c)
		{
			x = a;
			y = b;
			z = c;
			Intensity = 0;
			ReturnNumber = NumberofReturns = ScanDirectionFlag = EdgeofFlightLine = 0;
			Classification = 0;
			ScanAngleRank = 0;
			UserData = 0;
			PointSourceID = 0;
			GPStime = 0;
			Red = Green = Blue = 0;
		}
		void operator=(const Point_LasV12 & p)
		{
			x = p.x;
			y = p.y;
			x = p.z;
			Intensity = p.Intensity;
			ReturnNumber = p.ReturnNumber;
			NumberofReturns = p.NumberofReturns;
			ScanDirectionFlag = p.ScanDirectionFlag;
			EdgeofFlightLine = p.EdgeofFlightLine;
			Classification = p.Classification;
			ScanAngleRank = p.ScanAngleRank;
			UserData = p.UserData;
			PointSourceID = p.PointSourceID;
			GPStime = p.GPStime;
			Red = p.Red;
			Green = p.Green;
			Blue = p.Blue;
		}

		void SetRedColor()
		{
			Red = 255;
			Green = 0;
			Blue = 0;
		}
		void SetBlackColor()
		{
			Red = 0;
			Green = 0;
			Blue = 0;
		}
		void SetYellowColor()
		{
			Red = 255;
			Green = 255;
			Blue = 0;
		}
		void SetBlueColor()
		{
			Red = 0;
			Green = 0;
			Blue = 255;
		}
		void SetGreenColor()
		{
			Red = 0;
			Green = 255;
			Blue = 0;
		}
		void SetBrownColor()
		{
			Red = 170;
			Green = 85;
			Blue = 0;
		}
		void SetSilverColor()
		{
			Red = 200;
			Green = 200;
			Blue = 200;
		}

	};

	class LASPointSet
	{
	public:
		std::string filename;
		LasHeader head;
		std::vector<Point_LasV12> * point;

		LASPointSet()
		{
			filename = "LIDAR";
			head = 0;
			point = nullptr;
		}
		~LASPointSet()
		{
			Reset();
		}

		void Reset()
		{
			filename = "LIDAR";
			head = 0;
			if (point != nullptr)
			{
				//point->swap(std::vector<Point_LasV12>());

				std::vector<Point_LasV12>().swap(*point);


				delete point;
				point = nullptr;
			}
		}
		double GetCoordinate(unsigned id, const COORDINATE mode)
		{
			if (id < point->size())
			{
				switch (mode)
				{
				case X:
				{
					return (*point)[id].x*head.x_scale_factor + head.x_offset;
				}
				case Y:
				{
					return (*point)[id].y*head.y_scale_factor + head.y_offset;
				}
				case Z:
				{
					return (*point)[id].z*head.z_scale_factor + head.z_offset;
				}
				default:
				{
					return NAN;
				}
				}
			}
			else
			{
				return NAN;
			}
		}
	};

	class Point3dHeader
	{
	public:
		double x_offset;
		double y_offset;
		double z_offset;
		double max_x;
		double min_x;
		double max_y;
		double min_y;
		double max_z;
		double min_z;

		Point3dHeader()
		{
			x_offset = 0;
			y_offset = 0;
			z_offset = 0;
			max_x = 0;
			min_x = 0;
			max_y = 0;
			min_y = 0;
			max_z = 0;
			min_z = 0;
		}

		Point3dHeader(double x, double y, double z)
		{
			x_offset = x;
			y_offset = y;
			z_offset = z;
			max_x = 0;
			min_x = 0;
			max_y = 0;
			min_y = 0;
			max_z = 0;
			min_z = 0;
		}

		Point3dHeader(const Point3dHeader & _h)
		{
			x_offset = _h.x_offset;
			y_offset = _h.y_offset;
			z_offset = _h.z_offset;
			max_x = _h.max_x;
			min_x = _h.min_x;
			max_y = _h.max_y;
			min_y = _h.min_y;
			max_z = _h.max_z;
			min_z = _h.min_z;
		}

		void operator=(const Point3dHeader & _h)
		{
			x_offset = _h.x_offset;
			y_offset = _h.y_offset;
			z_offset = _h.z_offset;
			max_x = _h.max_x;
			min_x = _h.min_x;
			max_y = _h.max_y;
			min_y = _h.min_y;
			max_z = _h.max_z;
			min_z = _h.min_z;
		}

		void operator=(const double a)
		{
			x_offset = a;
			y_offset = a;
			z_offset = 0;
			max_x = 0;
			min_x = 0;
			max_y = 0;
			min_y = 0;
			max_z = 0;
			min_z = 0;
		}

	};

	class Point3D
	{
	public:
		double x;
		double y;
		double z;
		unsigned PointSourceID;
		unsigned short Red;
		unsigned short Green;
		unsigned short Blue;
		char Classification;

		Point3D()
		{
			x = y = z = 0;
			PointSourceID = 0;
			Red = Green = Blue = 0;
			Classification = 0;
		}
		Point3D(double _x, double _y, double _z)
		{
			x = _x;
			y = _y;
			z = _z;
			PointSourceID = 0;
			Red = Green = Blue = 0;
			Classification = 0;
		}
		Point3D(const Point3D & _p)
		{
			x = _p.x;
			y = _p.y;
			z = _p.z;
			PointSourceID = _p.PointSourceID;
			Red = _p.Red;
			Green = _p.Green;
			Blue = _p.Blue;
			Classification = _p.Classification;
		}
		Point3D operator=(const Point3D & _p)
		{
			x = _p.x;
			y = _p.y;
			z = _p.z;
			PointSourceID = _p.PointSourceID;
			Red = _p.Red;
			Green = _p.Green;
			Blue = _p.Blue;
			Classification = _p.Classification;

			return *this;
		}

		bool operator==(const Point3D & _p)
		{
			if (x == _p.x && y == _p.y && z == _p.z)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool operator!=(const Point3D & _p)
		{
			if (x != _p.x || y != _p.y || z != _p.z)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void SetRedColor()
		{
			Red = 255;
			Green = 0;
			Blue = 0;
		}
		void SetBlackColor()
		{
			Red = 0;
			Green = 0;
			Blue = 0;
		}
		void SetYellowColor()
		{
			Red = 255;
			Green = 255;
			Blue = 0;
		}
		void SetBlueColor()
		{
			Red = 0;
			Green = 0;
			Blue = 255;
		}
		void SetGreenColor()
		{
			Red = 0;
			Green = 255;
			Blue = 0;
		}
		void SetBrownColor()
		{
			Red = 170;
			Green = 85;
			Blue = 0;
		}
		void SetSilverColor()
		{
			Red = 200;
			Green = 200;
			Blue = 200;
		}
	};

	class Point3DSet
	{
	public:
		std::string filename;
		std::vector<Point3D>* point;
		Point3dHeader head;
		bool Is_UpdateHead;
		bool Is_DeletePointPtr; // if Is_DeletePointPtr is true, point need to be deleted

		Point3DSet() : head(0, 0, 0)
		{
			filename = "LIDAR";
			point = nullptr;
			Is_UpdateHead = false;
			Is_DeletePointPtr = false;
		}

		Point3DSet(const Point3DSet & _p3)
		{
			filename = _p3.filename;
			point = _p3.point;
			head = _p3.head;
			Is_UpdateHead = _p3.Is_UpdateHead;
		}

		void operator=(const Point3DSet & _p3)
		{
			filename = _p3.filename;
			point = _p3.point;
			head = _p3.head;
			Is_UpdateHead = _p3.Is_UpdateHead;
		}

		void operator=(std::vector<Point3D> & _p3)
		{
			head.max_x = -100000000;
			head.min_x = 100000000;
			head.max_y = -100000000;
			head.min_y = 100000000;
			head.max_z = -100000000;
			head.min_z = 100000000;
			for (unsigned i = 0; i < _p3.size(); i++)
			{
				if (_p3[i].x < head.min_x) head.min_x = _p3[i].x;
				else
				{
					if (_p3[i].x > head.max_x) head.max_x = _p3[i].x;
				}
				if (_p3[i].y < head.min_y) head.min_y = _p3[i].y;
				else
				{
					if (_p3[i].y > head.max_y) head.max_y = _p3[i].y;
				}
				if (_p3[i].z < head.min_z) head.min_z = _p3[i].z;
				else
				{
					if (_p3[i].z > head.max_z) head.max_z = _p3[i].z;
				}
			}
			Is_UpdateHead = true;
			if (point != nullptr)
			{
				//point->swap(std::vector<Point3D>());

				std::vector<Point3D>().swap(*point);



				point->swap(_p3);
			}
			else
			{
				point = new std::vector<Point3D>;
				point->swap(_p3);
			}
		}

		~Point3DSet()
		{
			Reset();
		}

		void Reset()
		{
			filename.clear();
			head = 0;
			Is_UpdateHead = false;
			if (Is_DeletePointPtr)
			{
				if (point != nullptr)
				{
					//point->swap(std::vector<Point3D>());

					std::vector<Point3D>().swap(*point);

					delete point;
					point = nullptr;
				}
			}
			else
			{
				point = nullptr;
			}
		}

		void UpdateHead()
		{
			if (Is_UpdateHead == false && point != nullptr)
			{
				head.max_x = -100000000;
				head.min_x = 100000000;
				head.max_y = -100000000;
				head.min_y = 100000000;
				head.max_z = -100000000;
				head.min_z = 100000000;
				for (auto & i : *point)
				{
					if (i.x < head.min_x) head.min_x = i.x;
					else
					{
						if (i.x > head.max_x) head.max_x = i.x;
					}
					if (i.y < head.min_y) head.min_y = i.y;
					else
					{
						if (i.y > head.max_y) head.max_y = i.y;
					}
					if (i.z < head.min_z) head.min_z = i.z;
					else
					{
						if (i.z > head.max_z) head.max_z = i.z;
					}
				}
				head.max_x += head.x_offset;
				head.min_x += head.x_offset;
				head.max_y += head.y_offset;
				head.min_y += head.y_offset;
				head.max_z += head.z_offset;
				head.min_z += head.z_offset;
				Is_UpdateHead = true;
			}
		}

		double GetAbsoluteCoordinate(unsigned id, const COORDINATE Coordinate)
		{
			if (id < point->size())
			{
				switch (Coordinate)
				{
				case X:
				{
					return (*point)[id].x + head.x_offset;
				}
				case Y:
				{
					return (*point)[id].y + head.y_offset;
				}
				case Z:
				{
					return (*point)[id].z + head.z_offset;
				}
				default:
				{
					return NAN;
				}
				}
			}
			else
			{
				return NAN;
			}
		}
	};

	class SortPoint3D
	{
	public:
		static std::vector<Point3D> * set;
		unsigned PointId;

		SortPoint3D()
		{
			PointId = 0;
		}

		SortPoint3D(unsigned id)
		{
			PointId = id;
		}

		SortPoint3D(const SortPoint3D & p)
		{
			PointId = p.PointId;
		}

		void operator=(const SortPoint3D & p)
		{
			PointId = p.PointId;
		}
		PointDef::Point3D point()
		{
			if (PointId < set->size() && set != nullptr)
			{
				return (*set)[PointId];
			}
			else
			{
				return PointDef::Point3D(NAN, NAN, NAN);
			}
		}
	};

	class PolarPoint
	{
	public:
		double range;
		double theta; //vertical angle
		double phi; // horizontal angle
		unsigned char ReturnNumber : 3;
		unsigned char NumberofReturns : 3;
		unsigned short intensity;
		unsigned short red;
		unsigned short green;
		unsigned short blue;
		unsigned PointSourceID;

		PolarPoint()
		{
			range = theta = phi = 0;
			intensity = 0;
			red = green = blue = ReturnNumber = NumberofReturns = 0;
			PointSourceID = 0;
		}
		PolarPoint(int a)
		{
			range = theta = phi = a;
			intensity = 0;
			red = green = blue = ReturnNumber = NumberofReturns = 0;
			PointSourceID = 0;
		}
		void operator=(const PolarPoint & p)
		{
			range = p.range;
			theta = p.theta;
			phi = p.phi;
			intensity = p.intensity;
			red = p.red;
			green = p.green;
			blue = p.blue;
			ReturnNumber = p.ReturnNumber;
			NumberofReturns = p.NumberofReturns;
			PointSourceID = p.PointSourceID;
		}
	};

	std::pair<void *, void *> ReadFile(std::string _FileName);

	bool ReadLasFile(std::string _FileName, LASPointSet & _lp);

	bool WriteLasFile(LASPointSet & _lp);

	bool WriteLasFileFromPoint3DSet(Point3DSet & _p3);

	bool WriteLasFileFromPoint3D(std::string _FileName, std::vector<PointDef::Point3D> & _p3);

	void LasToPoint3DSet(LASPointSet & _lp, Point3DSet & _p3, double Xoffset = 0, double Yoffset = 0, double Zoffset = 0);

	void LasToPolar(LASPointSet & _lp, std::vector<PolarPoint> & _p, double & IntStd);

	void PolarToLas(std::vector<PolarPoint> & _p, LASPointSet & _lp);

	void Point3DSetToLas(Point3DSet & _p3, LASPointSet & _lp);

	template<typename PointType>
	double EuclideanDistance(const PointType & a, const PointType & b, const COORDINATE mode)
	{
		switch (mode)
		{
		case X:
		{
			return abs(a.x - b.x);
		}
		case Y:
		{
			return abs(a.y - b.y);
		}
		case Z:
		{
			return abs(a.z - b.z);
		}
		case XY:
		{
			return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
		}
		case XZ:
		{
			return sqrt(pow(a.x - b.x, 2) + pow(a.z - b.z, 2));
		}
		case YZ:
		{
			return sqrt(pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
		}
		case XYZ:
		{
			return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
		}
		default:
		{
			return NAN;
		}
		}
	}

	template<typename PointType>
	double GetCoordinateAverageValue(const std::vector<PointType> & set, const COORDINATE mode)
	{
		double res = 0;
		switch (mode)
		{
		case X:
		{
			for (auto & p : set)
			{
				res += p.x;
			}
			break;
		}
		case Y:
		{
			for (auto & p : set)
			{
				res += p.y;
			}
			break;
		}
		case Z:
		{
			for (auto & p : set)
			{
				res += p.z;
			}
			break;
		}
		default:
			return NAN;
		}
		if (set.size() > 0)
		{
			return res / set.size();
		}
		else
		{
			return NAN;
		}
	}

	template<typename PointType>
	PointType IsometricDivisionPoint(const PointType & Begin, const PointType & End, double Ratio)
	{
		double _x = End.x - Begin.x, _y = End.y - Begin.y, _z = End.z - Begin.z;
		PointType _point;
		_point.x = Begin.x + _x * Ratio;
		_point.y = Begin.y + _y * Ratio;
		_point.z = Begin.z + _z * Ratio;
		return _point;
	}

	template<typename PointType>
	bool compX(const PointType & i, const PointType & j)
	{
		return i.x < j.x;
	}

	template<typename PointType>
	bool compY(const PointType & i, const PointType & j)
	{
		return i.y < j.y;
	}

	template<typename PointType>
	bool compZ(const PointType & i, const PointType & j)
	{
		return i.z < j.z;
	}

	template<typename PointType>
	bool compID(const PointType & i, const PointType & j)
	{
		return i.PointSourceID < j.PointSourceID;
	}

	template<typename PointType>
	bool compSize(const std::vector<PointType> & i, const std::vector<PointType> & j)
	{
		return i.size() < j.size();
	}

	bool compPhi(const PolarPoint & i, const PolarPoint & j);

	bool compTheta(const PolarPoint & i, const PolarPoint & j);

	bool compRange(const PolarPoint & i, const PolarPoint & j);

	bool compXminmax(const SortPoint3D & i, const SortPoint3D & j);

	bool compYminmax(const SortPoint3D & i, const SortPoint3D & j);

	bool compZminmax(const SortPoint3D & i, const SortPoint3D & j);

	bool compIDminmax(const SortPoint3D & i, const SortPoint3D & j);

	bool compXmaxmin(const SortPoint3D & i, const SortPoint3D & j);

	bool compYmaxmin(const SortPoint3D & i, const SortPoint3D & j);

	bool compZmaxmin(const SortPoint3D & i, const SortPoint3D & j);

	bool compIDmaxmin(const SortPoint3D & i, const SortPoint3D & j);

}

typedef std::vector<PointDef::Point3D> VPoint3D;
typedef std::list<std::vector<PointDef::Point3D>> LVPoint3D;
using std::string;

#endif//POINTDEFINATION_H