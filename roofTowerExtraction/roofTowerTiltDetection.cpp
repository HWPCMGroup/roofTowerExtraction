#include "roofTowerTiltDetection.h"

bool CRoofTowerTilt::roofTiltDetection(std::vector<wl::LASPoint>& input_pts, std::vector<int>&input_id)
{
	if (input_pts.empty())
	{
		return false;
	}

	if (input_id.empty())
	{
		for (size_t i = 0; i < input_pts.size(); ++i)
		{
			input_id.push_back(i);
		}
	}

	//��ȡ�м��
	std::vector<int>poleId;
	if (!roofLineDetect(input_pts, input_id, poleId))
	{
		return false;
	}

	//��ȡ���ĵ�
	//std::string poleFile = "F:\\��Ϊ��Ŀ\\roofTowerExtraction\\testData\\centerPts.txt";
	//ReadAndWritePC::writePtsSingleTower(input_pts,poleId, poleFile.c_str());


	//������б�Ƕȡ�������͵㡢��ߵ��ͶӰ��
	if (poleId.empty())
	{
		return false;
	}

	//������ת��pcl::PointXYZ��ʽ
	pcl::PointCloud<pcl::PointXYZ>cloud; std::vector<int>center_id;
	format_wlLASPoint_to_pclPointXYZ(input_pts, poleId, cloud);

	//line_direction_x, line_direction_y, line_direction_z��ֱ�ߵķ���������angle_between_line_plane��ֱ����ƽ��н�
	m_threePts.resize(3);
	line_filter_and_tilt_detect(m_srcPts, cloud, m_vector.x, m_vector.y, m_vector.z, m_inclination,
		m_threePts[0], m_threePts[1], m_threePts[2]);

	return true;
}

void CRoofTowerTilt::line_filter_and_tilt_detect(std::vector<wl::LASPoint>&input_tower_pts, /*const*/ pcl::PointCloud<pcl::PointXYZ>cloud,
	double &line_direction_x, double &line_direction_y, double &line_direction_z, double& inclinationAngle,
	wl::LASPoint &bottom_center_point, wl::LASPoint &top_center_point, wl::LASPoint& projection_point)
{
	if (cloud.empty())
	{
		return;
	}
	wl::LASPoint nogain_top_center_point;

	//����һ��ģ�Ͳ����������ڼ�¼���
	pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
	pcl::PointIndices::Ptr inliers(new pcl::PointIndices);  //inliers��ʾ��������̵ĵ� ��¼���ǵ��Ƶ����
	pcl::SACSegmentation<pcl::PointXYZ> seg;     // ����һ���ָ���
	seg.setOptimizeCoefficients(true);      // Optional��������ÿ���ѡ�����ƽ��չʾ�ĵ��Ƿָ���ĵ㻹�Ƿָ�ʣ�µĵ㡣
	seg.setModelType(pcl::SACMODEL_LINE);  // Mandatory-����Ŀ�꼸����״
	seg.setMethodType(pcl::SAC_RANSAC);     //�ָ�������������
	seg.setDistanceThreshold(0.001);         //����������̷�Χ��Ҳ������ֵ
	seg.setInputCloud(cloud.makeShared());               //�������
	seg.segment(*inliers, *coefficients);   //�ָ���ƣ����ƽ��ͷ�����
	line_direction_x = coefficients->values[3];
	line_direction_y = coefficients->values[4];
	line_direction_z = coefficients->values[5];

	//���ֱ�ߵ�

	//��ֱ����ƽ��н�
	///����ƽ��ķ�����
	double plane_direction_x = 0;
	double plane_direction_y = 0;
	double plane_direction_z = 1;
	///ֱ��������ƽ�淨�����н�����ֵ
	double cos_line_plane_direction = (line_direction_x*plane_direction_x + line_direction_y * plane_direction_y + line_direction_z * plane_direction_z)
		/ ((sqrt(pow(line_direction_x, 2) + pow(line_direction_y, 2) + pow(line_direction_z, 2)))*
		(sqrt(pow(plane_direction_x, 2) + pow(plane_direction_y, 2) + pow(plane_direction_z, 2))));
	double arccos_line_plane_direction = acos(cos_line_plane_direction);

	double angle_between_line_plane;
	angle_between_line_plane = (PI / 2) - arccos_line_plane_direction;
	//������ת���ɽǶ�
	inclinationAngle = angle_between_line_plane * 180 / PI;

	//����������
	pcl::PointXYZ min;//���ڴ�����������Сֵ
	pcl::PointXYZ max;//���ڴ������������ֵ
	pcl::getMinMax3D(cloud, min, max);

	//��͵�����
	bottom_center_point.x = max.x;
	bottom_center_point.y = max.y;
	bottom_center_point.z = min.z;

	//std::string bottom_center_pointFile = "F:\\��Ϊ��Ŀ\\roofTowerExtraction\\testData\\bottom.txt";
	//ReadAndWritePC::writeOnePt(bottom_center_point, bottom_center_pointFile.c_str());

	std::vector<int>inputTowerId;

	//��ߵ�z����
	double maxPtZ = max.z + 1;

	//��͵�����ߴ���ͶӰ��
	projection_point.x = max.x;
	projection_point.y = max.y;
	projection_point.z = maxPtZ;

	//std::string projectionFile = "F:\\��Ϊ��Ŀ\\roofTowerExtraction\\testData\\projection.txt";
	//ReadAndWritePC::writeOnePt(projection_point, projectionFile.c_str());

	wl::LASPoint temTopCenterPt;

	temTopCenterPt.x = bottom_center_point.x + (line_direction_x*maxPtZ / bottom_center_point.z);
	temTopCenterPt.y = bottom_center_point.y + (line_direction_y*maxPtZ / bottom_center_point.z);

	top_center_point.x = 100 * temTopCenterPt.x - 99 * projection_point.x;
	top_center_point.y = 100 * temTopCenterPt.y - 99 * projection_point.y;
	top_center_point.z = maxPtZ;

	//std::string topFile = "F:\\��Ϊ��Ŀ\\roofTowerExtraction\\testData\\topFile.txt";
	//ReadAndWritePC::writeOnePt(top_center_point, topFile.c_str());
}

bool CRoofTowerTilt::roofLineDetect(std::vector<wl::LASPoint>preTreatedPts, std::vector<int>preTreatedId, std::vector<int>&outputId)
{
	pcl::PointCloud<pcl::PointXYZ>preTreatedCloud;

	//�洢���е�ֱ�ߵ�
	int iteration = 0;
	std::vector<std::vector<int>>temLineIds;

	while (iteration < roofLineIterationNum)
	{
		pcl::PointCloud<pcl::PointXYZ>preTreatedCloud;
		if (preTreatedId.empty())
		{
			for (size_t i = 0; i < preTreatedPts.size(); ++i)
			{
				preTreatedId.push_back(i);
			}
		}
		int widthValue;
		widthValue = preTreatedId.size();
		preTreatedCloud.width = widthValue;
		preTreatedCloud.height = 1;
		preTreatedCloud.is_dense = false;
		preTreatedCloud.resize(preTreatedCloud.width*preTreatedCloud.height);
		for (size_t i = 0; i < preTreatedId.size(); ++i)
		{
			preTreatedCloud.points[i].x = preTreatedPts[preTreatedId[i]].x;
			preTreatedCloud.points[i].y = preTreatedPts[preTreatedId[i]].y;
			preTreatedCloud.points[i].z = preTreatedPts[preTreatedId[i]].z;
		}

		pcl::SampleConsensusModelLine<pcl::PointXYZ>::Ptr model_line(new pcl::SampleConsensusModelLine<pcl::PointXYZ>(preTreatedCloud.makeShared()));	//ָ����ϵ����뼸��ģ��
		pcl::RandomSampleConsensus<pcl::PointXYZ> ransac(model_line);	//�����������һ���Զ���
		ransac.setDistanceThreshold(0.1);	//�ڵ㵽ģ�͵�������
		ransac.setMaxIterations(1000);		//����������
		ransac.computeModel();				//ִ��RANSAC�ռ�ֱ�����

		std::vector<int> inliers;				//�洢�ڵ�����������
		ransac.getInliers(inliers);			//��ȡ�ڵ��Ӧ������

		//�洢ֱ�ߵ�
		std::vector<int>temSingleLineId;
		for (size_t i = 0; i < inliers.size(); ++i)
		{
			int index = inliers[i];
			temSingleLineId.push_back(preTreatedId[index]);
		}

		//std::string lineFile = "F:\\��Ϊ��Ŀ\\roofTowerExtraction\\testData\\centerPts"+to_string(iteration)+"_.txt";
		//ReadAndWritePC::writePtsSingleTower(preTreatedPts, temSingleLineId, lineFile.c_str());

		//����ֱ����ǣ��Դ��ߡ�����Ǹ�Ϊ׼	
		double inclination;
		roofCalcuInclination(preTreatedPts, temSingleLineId, inclination);

		if (inclination > 85)
		{
			temLineIds.push_back(temSingleLineId);
		}

		//��ֱ�ߵ�
		std::vector<int>notLine2DId;
		differenceVector(preTreatedId, temSingleLineId, notLine2DId);

		if (notLine2DId.empty())
		{
			return false;
		}

		pcl::PointCloud<pcl::PointXYZ>().swap(preTreatedCloud);

		std::vector<int>().swap(inliers);

		std::vector<int>().swap(preTreatedId);
		preTreatedId.insert(preTreatedId.end(), notLine2DId.begin(), notLine2DId.end());
		iteration = iteration + 1;
	}

	double lineLength = 0;
	int maxLengthLine = 0;
	for (size_t i = 0; i < temLineIds.size(); ++i)
	{
		double lineMaxZ, lineMinZ;
		calcuMaxMinZ(preTreatedPts, temLineIds[i], lineMaxZ, lineMinZ);
		double temLineLength = lineMaxZ - lineMinZ;

		if (lineLength < temLineLength)
		{
			lineLength = temLineLength;
			maxLengthLine = i;
		}
	}
	outputId.insert(outputId.end(), temLineIds[maxLengthLine].begin(), temLineIds[maxLengthLine].end());
	return true;
}

void CRoofTowerTilt::roofCalcuInclination(std::vector <wl::LASPoint>inputPts, std::vector<int>inputId, double &inclinationAngle)
{
	pcl::PointCloud<pcl::PointXYZ>cloud;
	format_wlLASPoint_to_pclPointXYZ(inputPts, inputId, cloud);

	double line_direction_x, line_direction_y, line_direction_z;
	//����һ��ģ�Ͳ����������ڼ�¼���
	pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
	pcl::PointIndices::Ptr inliersModel(new pcl::PointIndices);  //inliers��ʾ��������̵ĵ� ��¼���ǵ��Ƶ����
	pcl::SACSegmentation<pcl::PointXYZ> seg;     // ����һ���ָ���
	seg.setOptimizeCoefficients(true);      // Optional��������ÿ���ѡ�����ƽ��չʾ�ĵ��Ƿָ���ĵ㻹�Ƿָ�ʣ�µĵ㡣
	seg.setModelType(pcl::SACMODEL_LINE);  // Mandatory-����Ŀ�꼸����״
	seg.setMethodType(pcl::SAC_RANSAC);     //�ָ�������������
	seg.setDistanceThreshold(0.001);         //����������̷�Χ��Ҳ������ֵ
	seg.setInputCloud(cloud.makeShared());               //�������
	seg.segment(*inliersModel, *coefficients);   //�ָ���ƣ����ƽ��ͷ�����
	line_direction_x = coefficients->values[3];
	line_direction_y = coefficients->values[4];
	line_direction_z = coefficients->values[5];

	//��ֱ����ƽ��н�
	double plane_direction_x = 0;
	double plane_direction_y = 0;
	double plane_direction_z = 1;
	///ֱ��������ƽ�淨�����н�����ֵ
	double cos_line_plane_direction = (line_direction_x*plane_direction_x + line_direction_y * plane_direction_y + line_direction_z * plane_direction_z)
		/ ((sqrt(pow(line_direction_x, 2) + pow(line_direction_y, 2) + pow(line_direction_z, 2)))*
		(sqrt(pow(plane_direction_x, 2) + pow(plane_direction_y, 2) + pow(plane_direction_z, 2))));
	double arccos_line_plane_direction = acos(cos_line_plane_direction);

	double angle_between_line_plane;
	angle_between_line_plane = (PI / 2) - arccos_line_plane_direction;
	//������ת���ɽǶ�
	inclinationAngle = angle_between_line_plane * 180 / PI;

}

//general function
void CRoofTowerTilt::calcuMaxMinZ(std::vector<wl::LASPoint>&inputPts, std::vector<int>&inputId, double& towermaxZ, double& towerminZ)
{
	if (inputId.empty())
	{
		for (size_t i = 0; i < inputPts.size(); ++i)
		{
			inputId.push_back(i);
		}
	}
	towermaxZ = -99999999;
	towerminZ = 99999999;

	for (size_t i = 0; i < inputId.size(); ++i)
	{
		if (towerminZ > inputPts[inputId[i]].z)
		{
			towerminZ = inputPts[inputId[i]].z;
		}
		if (towermaxZ < inputPts[inputId[i]].z)
		{
			towermaxZ = inputPts[inputId[i]].z;
		}
	}
}

void CRoofTowerTilt::differenceVector(std::vector<int> v1, std::vector<int> v2, std::vector<int>&out)
{
	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());

	std::vector<int> v_intersection;

	std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v_intersection));

	std::vector<int> v_difference;

	set_difference(v1.begin(), v1.end(), v_intersection.begin(), v_intersection.end(), inserter(v_difference, v_difference.begin()));

	for (int n : v_difference)
	{
		out.push_back(n);
	}
}

void CRoofTowerTilt::format_wlLASPoint_to_pclPointXYZ(std::vector<wl::LASPoint>&input_pts, std::vector<int>&input_id, pcl::PointCloud<pcl::PointXYZ>&cloud)
{
	if (input_id.empty())
	{
		for (size_t i = 0; i < input_pts.size(); ++i)
		{
			input_id.push_back(i);
		}
	}
	cloud.width = input_id.size();
	cloud.height = 1;
	cloud.is_dense = false;
	cloud.resize(cloud.width*cloud.height);
	for (size_t i = 0; i < input_id.size(); ++i)
	{
		cloud.points[i].x = input_pts[input_id[i]].x;
		cloud.points[i].y = input_pts[input_id[i]].y;
		cloud.points[i].z = input_pts[input_id[i]].z;
	}
}

void CRoofTowerTilt::format_pclPointXYZ_to_wlLASPoint(pcl::PointCloud<pcl::PointXYZ>&cloud, std::vector<wl::LASPoint>&output_pts)
{
	output_pts.resize(cloud.points.size());
	for (size_t i = 0; i < cloud.points.size(); ++i)
	{
		output_pts[i].x = cloud.points[i].x;
		output_pts[i].y = cloud.points[i].y;
		output_pts[i].z = cloud.points[i].z;
	}
}