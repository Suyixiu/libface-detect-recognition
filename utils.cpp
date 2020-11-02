#include"utils.h"

void getAllFiles(string path, vector<string>& files)   ///windowsϵͳ������ļ������ȫ���ļ���Ŀ¼, �����linuxϵͳ���Ҫ�޸ĺ�����Ĵ���
{
	intptr_t hFile = 0;//�ļ����  64λ��long ��Ϊ intptr_t
	struct _finddata_t fileinfo;//�ļ���Ϣ 
	string p;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1) //�ļ�����
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))//�ж��Ƿ�Ϊ�ļ���
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)//�ļ������в���"."��".."
				{
					//files.push_back(p.assign(path).append("/").append(fileinfo.name)); //�����ļ�����
					getAllFiles(p.assign(path).append("/").append(fileinfo.name), files); //�ݹ�����ļ�������ļ�
				}
			}
			else
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));//��������ļ��У������ļ���
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

int write_face_feature_name2bin(int num_face, int len_feature, const float* output, const vector<string> names, const char* bin_name)
{
	FILE* fp = fopen(bin_name, "wb");
	fwrite(&num_face, sizeof(int), 1, fp);
	fwrite(&len_feature, sizeof(int), 1, fp);
	fwrite(output, sizeof(float), num_face * len_feature, fp);
	for (int i = 0; i < names.size(); i++)   //// num_face == names.size();
	{
		int len_s = names[i].length();
		fwrite(&len_s, sizeof(int), 1, fp);
		fwrite(names[i].c_str(), sizeof(char), len_s + 1, fp);   ///�ַ���ĩβ'\0'Ҳ��һ���ַ���
	}
	fclose(fp);
	return 0;
}

float* read_face_feature_name2bin(int* num_face, int* len_feature, vector<string>& names, const char* bin_name)
{
	FILE* fp = fopen(bin_name, "rb");
	fread(num_face, sizeof(int), 1, fp);
	fread(len_feature, sizeof(int), 1, fp);
	int len = (*num_face) * (*len_feature);
	float* output = new float[len];
	fread(output, sizeof(float), len, fp);//��������
	for (int i = 0; i < *num_face; i++)
	{
		int len_s = 0;
		fread(&len_s, sizeof(int), 1, fp);
		char* name = new char[len_s + 1];   ///�ַ���ĩβ'\0'Ҳ��һ���ַ���
		fread(name, sizeof(char), len_s + 1, fp);//��������
		//cout << name << endl;
		names.push_back(name);
		delete[] name;
	}

	fclose(fp);//�ر��ļ���
	return output;
}

int Get_Min_Euclid_Dist(float* face_features, vector<float> out_feature, int num_face, int len_feature, float* dist_feature) ////ŷ����þ���ֵԽС,��������Խ����
{
	int i = 0, j = 0, min_ind = 0;
	float euclid_dist = 0, square = 0, min_dist = 10000;
	for (i = 0; i < num_face; i++)
	{
		euclid_dist = 0;
		for (j = 0; j < len_feature; j++)
		{
			square = (out_feature[j] - face_features[i * len_feature + j]) * (out_feature[j] - face_features[i * len_feature + j]);
			euclid_dist += square;
		}
		euclid_dist = sqrt(euclid_dist);
		dist_feature[i] = euclid_dist;
		if (euclid_dist < min_dist)
		{
			min_dist = euclid_dist;
			min_ind = i;
		}
	}
	return min_ind;
}

/*���Ҿ���ֵԽ��,��������Խ����
* ��������a������b
����ֵcos(theta) = (a * b) / (|a| * |b|)
|a|��|b|��ʾ����a������b��ģ
�ڼ�������ֵ֮ǰ���Ѿ����������˵�λ��һ�������|a| = |b| = 1
��ôcos(theta) = (a * b)
*/
int Get_Max_Cos_Dist(float* face_features, vector<float> out_feature, int num_face, int len_feature, float* dist_feature)   ////���Ҿ���ֵԽ��,��������Խ����
{
	int i = 0, j = 0, max_ind = 0;
	float cos_dist = 0, max_dist = -10000;
	for (i = 0; i < num_face; i++)
	{
		cos_dist = 0;
		for (j = 0; j < len_feature; j++)
		{
			cos_dist = cos_dist + (out_feature[j] * face_features[i * len_feature + j]);
		}
		dist_feature[i] = cos_dist;
		if (cos_dist > max_dist)
		{
			max_dist = cos_dist;
			max_ind = i;
		}
	}
	return max_ind;
}
