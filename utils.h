#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <io.h>
#include <iostream>
#include <string.h>
#include<fstream>

using namespace std;
/*����ļ��������������ļ���, ÿ�����ļ��е�����������. 
���ļ������������˵�����ͼƬ, 
ͼƬ��Ф����, ����ֻ��һ������*/
void getAllFiles(string path, vector<string>& files);  ///windowsϵͳ������ļ������ȫ���ļ���Ŀ¼

inline int MinInt(int a, int b)    //��������a��b�н�С��һ��
{
	return (a < b) * a + (1 - (a < b)) * b;
}

inline int MaxInt(int a, int b)    //��������a��b�нϴ��һ��
{
	return (a > b) * a + (1 - (a > b)) * b;
}

inline string fromPath_Getname(string filepath)
{
	size_t pos_end = filepath.rfind("/");    ////������1��·��������� ·���ָ�����/
	size_t pos_start = filepath.substr(0, pos_end).rfind("/");   ////������2��·�������
	return filepath.substr(pos_start + 1, pos_end - pos_start - 1);
}

inline string fromPath_Get_imgname(string filepath)
{
	size_t pos_end = filepath.rfind("/");    ////������1��·�������
	return filepath.substr(pos_end + 1);
}

int write_face_feature_name2bin(int num_face, int len_feature, const float* output, const vector<string> names, const char* bin_name);

float* read_face_feature_name2bin(int* num_face, int* len_feature, vector<string>& names, const char* bin_name);

int Get_Min_Euclid_Dist(float* face_features, vector<float> out_feature, int num_face, int len_feature, float* dist_feature);

int Get_Max_Cos_Dist(float* face_features, vector<float> out_feature, int num_face, int len_feature, float* dist_feature);

typedef struct Rec_thresh
{
	float thresh;
	string type;
} Rec_thresh;