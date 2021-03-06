#include "dip.h"

/*函数功能：写（32位）位图（即保存）
输入参数：RGBQUAD* dataOfBmp --- 待存储图像所有像素（以行为序）对应的
RGBAlpha 四元素结构体指针；
DWORD width, DWORD height --- 待存储图像的宽度和高度
（以像素为单位）
输出值：  没有
*/



// 参数：源图像、目标图像、图像宽度、图像高度、均值模板、模板k值

void MeanFiltering(RGBQUAD** dataOfBmp_src, RGBQUAD** dataOfBmp_noise, int width, int height, int template_m[3][3],double kl)
{

	double  sumR = 0.0;
	double sumG = 0.0;
	double sumB = 0.0;
	RGBQUAD template_v[3][3];

	//边框保留不变的
	for (DWORD i = 1; i<height - 1; i++)
	for (DWORD j = 1; j < width - 1; j++)
	{
		template_v[0][0] = dataOfBmp_src[i - 1][j - 1];
		template_v[0][1] = dataOfBmp_src[i - 1][j];
		template_v[0][2] = dataOfBmp_src[i - 1][j + 1];
		template_v[1][0] = dataOfBmp_src[i][j - 1];
		template_v[1][1] = dataOfBmp_src[i][j];
		template_v[1][2] = dataOfBmp_src[i][j + 1];
		template_v[2][0] = dataOfBmp_src[i + 1][j - 1];
		template_v[2][1] = dataOfBmp_src[i + 1][j];
		template_v[2][2] = dataOfBmp_src[i + 1][j + 1];



		for (int k = 0; k < 3; k++)
		for (int l = 0; l < 3; l++)
		{
			sumR += (template_m[k][l] * template_v[k][l].rgbRed);
			sumG += (template_m[k][l] * template_v[k][l].rgbGreen);
			sumB += (template_m[k][l] * template_v[k][l].rgbBlue);

		}
		dataOfBmp_noise[i][j].rgbRed = sswr(kl*sumR);
		dataOfBmp_noise[i][j].rgbGreen = sswr(kl*sumG);
		dataOfBmp_noise[i][j].rgbBlue = sswr(kl*sumB);
		sumR = 0.0;
		sumG = 0.0;
		sumB = 0.0;
	

	}




}
//参数：源图像，目标图像，图像宽度，图像高度
void MiddleFiltering(RGBQUAD** dataOfBmp_src, RGBQUAD** dataOfBmp_noise, int width, int height)
{
	//八临近坐标值
	//int left_top;
	//int left;
	//int left_bottom;
	//int bottom;
	//int right_bottom;
	//int right;
	//int right_top;
	//int top;
	double  sumR = 0.0;
	double sumG = 0.0;
	double sumB = 0.0;
	int template_v[3][9];

	//边框保留不变的
	for (DWORD i = 1; i<height - 1; i++)
	for (DWORD j = 1; j < width - 1; j++)
	{



		template_v[0][0] = dataOfBmp_src[i - 1][j - 1].rgbRed;
		template_v[0][1] = dataOfBmp_src[i - 1][j].rgbRed;
		template_v[0][2] = dataOfBmp_src[i - 1][j + 1].rgbRed;
		template_v[0][3] = dataOfBmp_src[i][j - 1].rgbRed;
		template_v[0][4] = dataOfBmp_src[i][j].rgbRed;
		template_v[0][5] = dataOfBmp_src[i][j + 1].rgbRed;
		template_v[0][6] = dataOfBmp_src[i + 1][j - 1].rgbRed;
		template_v[0][7] = dataOfBmp_src[i + 1][j].rgbRed;
		template_v[0][8] = dataOfBmp_src[i + 1][j + 1].rgbRed;

		template_v[1][0] = dataOfBmp_src[i - 1][j - 1].rgbGreen;
		template_v[1][1] = dataOfBmp_src[i - 1][j].rgbGreen;
		template_v[1][2] = dataOfBmp_src[i - 1][j + 1].rgbGreen;
		template_v[1][3] = dataOfBmp_src[i][j - 1].rgbGreen;
		template_v[1][4] = dataOfBmp_src[i][j].rgbGreen;
		template_v[1][5] = dataOfBmp_src[i][j + 1].rgbGreen;
		template_v[1][6] = dataOfBmp_src[i + 1][j - 1].rgbGreen;
		template_v[1][7] = dataOfBmp_src[i + 1][j].rgbGreen;
		template_v[1][8] = dataOfBmp_src[i + 1][j + 1].rgbGreen;

		template_v[2][0] = dataOfBmp_src[i - 1][j - 1].rgbBlue;
		template_v[2][1] = dataOfBmp_src[i - 1][j].rgbBlue;
		template_v[2][2] = dataOfBmp_src[i - 1][j + 1].rgbBlue;
		template_v[2][3] = dataOfBmp_src[i][j - 1].rgbBlue;
		template_v[2][4] = dataOfBmp_src[i][j].rgbBlue;
		template_v[2][5] = dataOfBmp_src[i][j + 1].rgbBlue;
		template_v[2][6] = dataOfBmp_src[i + 1][j - 1].rgbBlue;
		template_v[2][7] = dataOfBmp_src[i + 1][j].rgbBlue;
		template_v[2][8] = dataOfBmp_src[i + 1][j + 1].rgbBlue;



		//排序操作
		
		 sort(template_v[0], 9);
		 int middelR = template_v[0][4];
		 sort(template_v[1], 9);
		 int middelG = template_v[1][4];
		 sort(template_v[2], 9);
		 int middelB = template_v[2][4];

		dataOfBmp_noise[i][j].rgbRed =middelR;
		dataOfBmp_noise[i][j].rgbGreen = middelG;
		dataOfBmp_noise[i][j].rgbBlue = middelB;

		//printf("%d\n", dataOfBmp_noise[i][j].rgbGreen);


	}

}

void KNNFitering(RGBQUAD** dataOfBmp_src, RGBQUAD** dataOfBmp_noise, int width, int height, int k)
{
	double sumB = 0.0;
	double sumG = 0.0;
	double sumR = 0.0;
	int template_v[3][9];

	//边框保留不变的
	for (DWORD i = 1; i < height - 1; i++)
	for (DWORD j = 1; j < width - 1; j++)
	{



		template_v[0][0] = abs(dataOfBmp_src[i - 1][j - 1].rgbRed - dataOfBmp_src[i][j].rgbRed);
		template_v[0][1] = abs(dataOfBmp_src[i - 1][j].rgbRed - dataOfBmp_src[i][j].rgbRed);
		template_v[0][2] = abs(dataOfBmp_src[i - 1][j + 1].rgbRed - dataOfBmp_src[i][j].rgbRed);
		template_v[0][3] = abs(dataOfBmp_src[i][j - 1].rgbRed - dataOfBmp_src[i][j].rgbRed);
		template_v[0][4] = abs(dataOfBmp_src[i][j].rgbRed - dataOfBmp_src[i][j].rgbRed);
		template_v[0][5] = abs(dataOfBmp_src[i][j + 1].rgbRed - dataOfBmp_src[i][j].rgbRed);
		template_v[0][6] = abs(dataOfBmp_src[i + 1][j - 1].rgbRed - dataOfBmp_src[i][j].rgbRed);
		template_v[0][7] = abs(dataOfBmp_src[i + 1][j].rgbRed - dataOfBmp_src[i][j].rgbRed);
		template_v[0][8] = abs(dataOfBmp_src[i + 1][j + 1].rgbRed - dataOfBmp_src[i][j].rgbRed);

		template_v[1][0] = abs(dataOfBmp_src[i - 1][j - 1].rgbGreen - dataOfBmp_src[i][j].rgbGreen);
		template_v[1][1] = abs(dataOfBmp_src[i - 1][j].rgbGreen - dataOfBmp_src[i][j].rgbGreen);
		template_v[1][2] = abs(dataOfBmp_src[i - 1][j + 1].rgbGreen - dataOfBmp_src[i][j].rgbGreen);
		template_v[1][3] = abs(dataOfBmp_src[i][j - 1].rgbGreen - dataOfBmp_src[i][j].rgbGreen);
		template_v[1][4] = abs(dataOfBmp_src[i][j].rgbGreen - dataOfBmp_src[i][j].rgbGreen);
		template_v[1][5] = abs(dataOfBmp_src[i][j + 1].rgbGreen - dataOfBmp_src[i][j].rgbGreen);
		template_v[1][6] = abs(dataOfBmp_src[i + 1][j - 1].rgbGreen - dataOfBmp_src[i][j].rgbGreen);
		template_v[1][7] = abs(dataOfBmp_src[i + 1][j].rgbGreen - dataOfBmp_src[i][j].rgbGreen);
		template_v[1][8] = abs(dataOfBmp_src[i + 1][j + 1].rgbGreen - dataOfBmp_src[i][j].rgbGreen);

		template_v[2][0] = abs(dataOfBmp_src[i - 1][j - 1].rgbBlue - dataOfBmp_src[i][j].rgbBlue);
		template_v[2][1] = abs(dataOfBmp_src[i - 1][j].rgbBlue - dataOfBmp_src[i][j].rgbBlue);
		template_v[2][2] = abs(dataOfBmp_src[i - 1][j + 1].rgbBlue - dataOfBmp_src[i][j].rgbBlue);
		template_v[2][3] = abs(dataOfBmp_src[i][j - 1].rgbBlue - dataOfBmp_src[i][j].rgbBlue);
		template_v[2][4] = abs(dataOfBmp_src[i][j].rgbBlue - dataOfBmp_src[i][j].rgbBlue);
		template_v[2][5] = abs(dataOfBmp_src[i][j + 1].rgbBlue - dataOfBmp_src[i][j].rgbBlue);
		template_v[2][6] = abs(dataOfBmp_src[i + 1][j - 1].rgbBlue - dataOfBmp_src[i][j].rgbBlue);
		template_v[2][7] = abs(dataOfBmp_src[i + 1][j].rgbBlue - dataOfBmp_src[i][j].rgbBlue);
		template_v[2][8] = abs(dataOfBmp_src[i + 1][j + 1].rgbBlue - dataOfBmp_src[i][j].rgbBlue);



		//排序操作

		sort(template_v[0], 9);
		double sumR = 0.0;
		for (int l = 0; l < k; l++)
		{
			sumR += template_v[0][l];
		}

		sort(template_v[1], 9);


		for (int l = 0; l < k; l++)
		{
			sumG += template_v[1][l];
		}

		sort(template_v[2], 9);


		for (int l = 0; l < k; l++)
		{
			sumB += template_v[2][l];
		}

		dataOfBmp_noise[i][j].rgbRed = sswr(sumR / k);
		dataOfBmp_noise[i][j].rgbGreen = sswr(sumG / k);
		dataOfBmp_noise[i][j].rgbBlue = sswr(sumB / k);
		sumB = 0.0;
		sumG = 0.0;
		sumR = 0.0;

	}
}


void main()
{

	#pragma region 读取图像
	BITMAPFILEHEADER   bitHead;
	BITMAPINFOHEADER bitInfoHead;
	int i, j;

	FILE* pfile;
	char strFile[50];
	printf("please input the .bmp source file name:\n");
	scanf("%s", strFile);
	pfile = fopen(strFile, "rb");//打开文件
	if (pfile != NULL)
	{
		printf("file %s open success.\n", strFile);
		//读取位图文件头信息
		fread(&bitHead, 1, sizeof(BITMAPFILEHEADER), pfile);
		if (bitHead.bfType != 0x4d42)
		{
			printf("file is not .bmp file!");
			return;
		}

		showBmpHead(&bitHead);
		printf("\n\n");
		//读取位图信息头信息
		fread(&bitInfoHead, 1, sizeof(BITMAPINFOHEADER), pfile);
		showBmpInforHead(&bitInfoHead);
		printf("\n");
	}
	else
	{
		printf("file open fail!\n");
		return;
	}

	RGBQUAD* pRgb = NULL;

	if (bitInfoHead.biBitCount < 24)//有调色板
	{
		//读取调色盘结信息
		long nPlantNum = bitInfoHead.biClrUsed;
		if (!nPlantNum)
			nPlantNum = long(pow(2.0, double(bitInfoHead.biBitCount)));    //   Mix color Plant Number;
		pRgb = new RGBQUAD[nPlantNum*sizeof(RGBQUAD)];
		memset(pRgb, 0, nPlantNum*sizeof(RGBQUAD));
		int num = fread(pRgb, 4, nPlantNum, pfile);

		printf("Color Plate Number: %d\n", nPlantNum);
		printf("颜色板信息:\n");
		showRgbQuan(pRgb, nPlantNum);

	}

	int width = bitInfoHead.biWidth;
	int height = bitInfoHead.biHeight;
	//分配内存空间把源图存入内存   
	int l_width = WIDTHBYTES(width* bitInfoHead.biBitCount);//计算位图的实际宽度并确保它为32的倍数
	long nData = height*l_width;
	BYTE    *pColorData = new BYTE[nData];
	memset(pColorData, 0, nData);

	//把位图数据信息读到数组里   
	fread(pColorData, 1, nData, pfile);

	//将位图数据转化为RGB数据
	RGBQUAD** dataOfBmp_src = NULL; //用于保存各像素对应的RGB数据

	dataOfBmp_src = new RGBQUAD*[height];
	for (i = 0; i < height; i++)
		dataOfBmp_src[i] = new RGBQUAD[width];

	if (bitInfoHead.biBitCount<24)//有调色板，即位图为非真彩色 
	{
		int k;

		if (bitInfoHead.biBitCount <= 8 && !bitInfoHead.biCompression)
		{

			int pnum = 8 / bitInfoHead.biBitCount;
			int mbnum = 8 - bitInfoHead.biBitCount;

			for (int i = 0; i<height; i++)
			{
				int k0 = (height - i - 1)*l_width;//k:取得该像素颜色数据在实际数据数组中的序号
				for (int j = 0; j<width; j++)
				{
					BYTE mixIndex = 0;
					k = k0 + (j / pnum);
					mixIndex = pColorData[k];
					//mixIndex:提取当前像素的颜色的在颜色表中的索引值    
					if (bitInfoHead.biBitCount < 8)
					{
						mixIndex = mixIndex << ((j%pnum)*bitInfoHead.biBitCount);
						mixIndex = mixIndex >> mbnum;
					}

					//将像素颜色数据（RGBA）保存到数组中对应的位置
					dataOfBmp_src[i][j].rgbRed = pRgb[mixIndex].rgbRed;
					dataOfBmp_src[i][j].rgbGreen = pRgb[mixIndex].rgbGreen;
					dataOfBmp_src[i][j].rgbBlue = pRgb[mixIndex].rgbBlue;
					dataOfBmp_src[i][j].rgbReserved = pRgb[mixIndex].rgbReserved;
				}

			}
		}


		if (bitInfoHead.biBitCount == 16)
		{
			if (!bitInfoHead.biCompression)
			{
				for (i = 0; i<height; i++)
				{
					int k0 = (height - i - 1)*l_width;
					for (j = 0; j<width; j++)
					{
						WORD mixIndex = 0;
						k = k0 + j * 2;
						WORD shortTemp;
						shortTemp = pColorData[k + 1];
						shortTemp = shortTemp << 8;

						mixIndex = pColorData[k] + shortTemp;
						dataOfBmp_src[i][j].rgbRed = pRgb[mixIndex].rgbRed;
						dataOfBmp_src[i][j].rgbGreen = pRgb[mixIndex].rgbGreen;
						dataOfBmp_src[i][j].rgbBlue = pRgb[mixIndex].rgbBlue;
						dataOfBmp_src[i][j].rgbReserved = pRgb[mixIndex].rgbReserved;
					}
				}
			}
		}
	}
	else//位图为24/32位真彩色
	{
		int k;
		int index = 0;

		if (bitInfoHead.biBitCount == 16)
		{
			for (i = 0; i<height; i++)
			{
				int k0 = (height - i - 1)*l_width;
				for (j = 0; j<width; j++)
				{
					k = k0 + j * 2;
					if (!bitInfoHead.biCompression)//555格式
					{
						dataOfBmp_src[i][j].rgbBlue = pColorData[k] & 0x1F;
						dataOfBmp_src[i][j].rgbGreen = (((pColorData[k + 1] << 6) & 0xFF) >> 3) + (pColorData[k] >> 5);
						dataOfBmp_src[i][j].rgbRed = (pColorData[k + 1] << 1) >> 3;
						dataOfBmp_src[i][j].rgbReserved = 0;

					}
				}
			}
		}
		if (bitInfoHead.biBitCount == 24 && !bitInfoHead.biCompression)
		{
			for (i = 0; i<height; i++)
			{
				int k0 = (height - i - 1)*l_width;
				for (j = 0; j<width; j++)
				{
					k = k0 + (j * 3);
					dataOfBmp_src[i][j].rgbRed = pColorData[k + 2];
					dataOfBmp_src[i][j].rgbGreen = pColorData[k + 1];
					dataOfBmp_src[i][j].rgbBlue = pColorData[k];
					dataOfBmp_src[i][j].rgbReserved = 0;

				}
			}
		}
		if (bitInfoHead.biBitCount == 32 && !bitInfoHead.biCompression)
		{
			for (i = 0; i<height; i++)
			{
				int k0 = (height - i - 1)*l_width;
				for (j = 0; j<width; j++)
				{
					k = k0 + (j * 4);
					dataOfBmp_src[i][j].rgbRed = pColorData[k + 2];
					dataOfBmp_src[i][j].rgbGreen = pColorData[k + 1];
					dataOfBmp_src[i][j].rgbBlue = pColorData[k];
					dataOfBmp_src[i][j].rgbReserved = pColorData[k + 3];

				}
			}

		}

	}

#pragma endregion

	RGBQUAD** dataOfBmp_noise = NULL;
	dataOfBmp_noise = new RGBQUAD*[height];
	for (i = 0; i<height; i++)
		dataOfBmp_noise[i] = new RGBQUAD[width];


	#pragma region 均值滤波器

	int template_m[3][3] = {1,1,1,1,1,1,1,1,1};

	double k = 1.0 / 9.0;

	//double template_m[3][3] = { 0, 1.0 / 8, 0, 1.0 / 8, 1, 1.0 / 8, 0, 1.0 / 8 ,0};





	//MeanFiltering(dataOfBmp_src, dataOfBmp_noise, width, height, template_m,k);

	
	#pragma endregion

	#pragma region 中值滤波器


	//MiddleFiltering(dataOfBmp_src, dataOfBmp_noise, width, height);
	#pragma endregion

	#pragma region KNN

	KNNFitering(dataOfBmp_src, dataOfBmp_noise, width, height,5);
	
	#pragma endregion


	saveBmp(dataOfBmp_noise, width, height);	


	BYTE** dataOfBmp_gray = NULL;
	dataOfBmp_gray = new BYTE*[height];
	for (i = 0; i<height; i++)
		dataOfBmp_gray[i] = new BYTE[width];


	//reverseColor(dataOfBmp_src, dataOfBmp_dst, width, height);

	//RGB2Gray(dataOfBmp_src, dataOfBmp_dst, dataOfBmp_gray, width, height);
	//double contrast8nn = contrast(dataOfBmp_gray, width, height, 1);

	//printf("the 8nn contrast of the gray image is %f\n", contrast8nn);


	fclose(pfile);
	if (bitInfoHead.biBitCount<24 && pRgb)
	{
		delete[]pRgb;
	}
	for (i = 0; i<height; i++)
	if (dataOfBmp_src[i])
		delete dataOfBmp_src[i];
	if (dataOfBmp_src)
		delete dataOfBmp_src;

	for (i = 0; i<height; i++)
	if (dataOfBmp_noise[i])
		delete dataOfBmp_noise[i];
	if (dataOfBmp_noise)
		delete dataOfBmp_noise;

	for (i = 0; i<height; i++)
	if (dataOfBmp_gray[i])
		delete dataOfBmp_gray[i];
	if (dataOfBmp_gray)
		delete dataOfBmp_gray;

	if (pColorData)
		delete[]pColorData;


}
