#include "roofTowerTiltDetection.h"
#include "read_laspos_file.h"

int main()
{
	std::vector<wl::LASPoint>inputPts;
	std::vector<int>inputId;
	//string inFile = "F:\\��Ϊ��Ŀ\\���Ծ��ȼ���\\�ݶ���4\\tower.txt";
	string inFile = "F:\\��Ϊ��Ŀ\\���Ծ��ȼ���\\1208�ݶ���_3\\tower1.txt";
	read_las_pos_file::read_txt_file(inputPts, inFile.c_str());

	CRoofTowerTilt croofTowerTilt;
	croofTowerTilt.roofTiltDetection(inputPts, inputId);

	system("pause");
	return 0;

}

void fileName(std::vector<string>&nameFile, std::vector<string>&centerFile)
{
	//normal
	std::string inFile1 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\Զ�������վ2_lable.txt";
	string inCenterFile1 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\Զ�������վ2_lable-center.txt";

	nameFile.push_back(inFile1);
	centerFile.push_back(inCenterFile1);

	string normalFile2 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\Զ�������վ1_lable.txt";
	string normalCenter2 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\Զ�������վ1_lable-center.txt";

	nameFile.push_back(normalFile2);
	centerFile.push_back(normalCenter2);

	string normaFile3 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\Ӳװ����15��_�Ľ���_lable.txt";
	string normalCenter3 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\Ӳװ����15��_�Ľ���_lable-centerd.txt";

	nameFile.push_back(normaFile3);
	centerFile.push_back(normalCenter3);

	string normalFile4 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\·�߹���_1203_lable.txt";
	string normalCenter4 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\·�߹���_1203_lable-center.txt";

	nameFile.push_back(normalFile4);
	centerFile.push_back(normalCenter4);

	string normalFile5 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\��·�ƹ���_���ܶ� _lable.txt";
	string normalCenter5 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\��·�ƹ���_���ܶ� _lable-center.txt";

	nameFile.push_back(normalFile5);
	centerFile.push_back(normalCenter5);

	string normalFile6 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\1208_����վ_3_lable.txt";
	string normalCenter6 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\1208_����վ_3_lable-center.txt";

	nameFile.push_back(normalFile6);
	centerFile.push_back(normalCenter6);

	string normalFile7 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\1208_����վ_2_lable.txt";
	string normalCenter7 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\1208_����վ_2_lable-center.txt";

	nameFile.push_back(normalFile7);
	centerFile.push_back(normalCenter7);

	string normalFile8 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\1208_����վ_1_lable.txt";
	string normalCenter8 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\center-1208_����վ_1_lable.txt";

	nameFile.push_back(normalFile8);
	centerFile.push_back(normalCenter8);

	string normalFile9 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\0911�Ľ���_lable.txt";
	string normalCenter9 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\0911�Ľ���_lable-center.txt";

	nameFile.push_back(normalFile9);
	centerFile.push_back(normalCenter9);

	string normalFile10 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\0911������_lable-subsampling.txt";
	string normalCenter10 = "G:\\Huawei\\RoofTower\\testData\\ͨ����\\0911������_lable - center.txt";

	nameFile.push_back(normalFile10);
	centerFile.push_back(normalCenter10);


	//roof
	//11
	string roofFile1 = "G:\\Huawei\\RoofTower\\testData\\220107_��_Ӳװ����_����վ_1.txt";
	string roofCenterFile1 = "G:\\Huawei\\RoofTower\\testData\\center-220107_��_Ӳװ����_����վ_1.txt";

	nameFile.push_back(roofFile1);
	centerFile.push_back(roofCenterFile1);
	//12
	string roofFile2 = "G:\\Huawei\\RoofTower\\testData\\220107_��_Ӳװ����_����վ_2.txt";
	string roofCenter2 = "G:\\Huawei\\RoofTower\\testData\\center-220107_��_Ӳװ����_����վ_2.txt";

	nameFile.push_back(roofFile2);
	centerFile.push_back(roofCenter2);
	//13
	string roofFile3 = "G:\\Huawei\\RoofTower\\testData\\220107_��_Ӳװ����_����վ_3.txt";
	string roofCenter3 = "G:\\Huawei\\RoofTower\\testData\\center-220107_��_Ӳװ����_����վ_3.txt";

	nameFile.push_back(roofFile3);
	centerFile.push_back(roofCenter3);
	//14
	string roofFile4 = "G:\\Huawei\\RoofTower\\testData\\�ݶ�վ1_save.txt";
	string roofCenter4 = "G:\\Huawei\\RoofTower\\testData\\center-�ݶ�վ1_save.txt";

	nameFile.push_back(roofFile4);
	centerFile.push_back(roofCenter4);
	//15
	string roofFile5 = "G:\\Huawei\\RoofTower\\testData\\�ݶ�վ4_save.txt";
	string roofCenter5 = "G:\\Huawei\\RoofTower\\testData\\center1-�ݶ�վ4_save.txt";

	nameFile.push_back(roofFile5);
	centerFile.push_back(roofCenter5);
	//16
	string roofCenter6 = "G:\\Huawei\\RoofTower\\testData\\center2-�ݶ�վ4_save.txt";
	centerFile.push_back(roofCenter6);
	//17
	string roofCenter7 = "G:\\Huawei\\RoofTower\\testData\\center3-�ݶ�վ4_save.txt";
	centerFile.push_back(roofCenter7);




}

