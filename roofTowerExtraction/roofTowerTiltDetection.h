#pragma once
//pcl
#include <pcl/point_types.h>
#include <pcl/common/common.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/impl/extract_clusters.hpp>
#include <pcl/sample_consensus/sac_model_line.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/don.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/voxel_grid.h>

#include<pcl/sample_consensus/sac_model_plane.h>
#include<pcl/sample_consensus/ransac.h>

#include<vector>
#include "point_types.h"

class CRoofTowerTilt
{
private:
	int roofLineIterationNum = 3;//提取直线
	std::vector<wl::LASPoint> m_threePts;
	std::vector<wl::LASPoint>  m_srcPts;
	wl::LASPoint m_vector;//塔矢量
	double m_inclination;//倾斜度
	double PI = 3.14159265359;//pai

public:
	//extract center pole
	bool roofTiltDetection(std::vector<wl::LASPoint>& input_pts, std::vector<int>&input_id);

	void line_filter_and_tilt_detect(std::vector<wl::LASPoint>&input_tower_pts, /*const*/ pcl::PointCloud<pcl::PointXYZ>cloud,
		double &line_direction_x, double &line_direction_y, double &line_direction_z, double& inclinationAngle,
		wl::LASPoint &bottom_center_point, wl::LASPoint &top_center_point, wl::LASPoint& projection_point);

	bool roofLineDetect(std::vector<wl::LASPoint>preTreatedPts, std::vector<int>preTreatedId, std::vector<int>&outputId);

	void roofCalcuInclination(std::vector <wl::LASPoint>inputPts, std::vector<int>inputId, double &inclinationAngle);

	//general function
	void calcuMaxMinZ(std::vector<wl::LASPoint>&inputPts, std::vector<int>&inputId, double& towermaxZ, double& towerminZ);

	void differenceVector(std::vector<int> v1, std::vector<int> v2, std::vector<int>&out);

	void format_wlLASPoint_to_pclPointXYZ(std::vector<wl::LASPoint>&input_pts, std::vector<int>&input_id, pcl::PointCloud<pcl::PointXYZ>&cloud);

	void format_pclPointXYZ_to_wlLASPoint(pcl::PointCloud<pcl::PointXYZ>&cloud, std::vector<wl::LASPoint>&output_pts);
};