//#include "dip.h"
//
//void Binarization(RGBQUAD** dataOfBmp_src,RGBQUAD** dataOfBmp_dst,int width,int height)
//{
//
//}
//
//void main()
//{
//
//	#pragma region ��ȡͼ��
//
//	BITMAPFILEHEADER   bitHead;
//	BITMAPINFOHEADER bitInfoHead;
//	int i, j;
//
//	FILE* pfile;
//	char strFile[50];
//	printf("please input the .bmp source file name:\n");
//	scanf("%s", strFile);
//	pfile = fopen(strFile, "rb");//���ļ�
//	if (pfile != NULL)
//	{
//		printf("file %s open success.\n", strFile);
//		//��ȡλͼ�ļ�ͷ��Ϣ
//		fread(&bitHead, 1, sizeof(BITMAPFILEHEADER), pfile);
//		if (bitHead.bfType != 0x4d42)
//		{
//			printf("file is not .bmp file!");
//			return;
//		}
//
//		showBmpHead(&bitHead);
//		printf("\n\n");
//		//��ȡλͼ��Ϣͷ��Ϣ
//		fread(&bitInfoHead, 1, sizeof(BITMAPINFOHEADER), pfile);
//		showBmpInforHead(&bitInfoHead);
//		printf("\n");
//	}
//	else
//	{
//		printf("file open fail!\n");
//		return;
//	}
//
//	RGBQUAD* pRgb = NULL;
//
//	if (bitInfoHead.biBitCount < 24)//�е�ɫ��
//	{
//		//��ȡ��ɫ�̽���Ϣ
//		long nPlantNum = bitInfoHead.biClrUsed;
//		if (!nPlantNum)
//			nPlantNum = long(pow(2, double(bitInfoHead.biBitCount)));    //   Mix color Plant Number;
//		pRgb = new RGBQUAD[nPlantNum*sizeof(RGBQUAD)];
//		memset(pRgb, 0, nPlantNum*sizeof(RGBQUAD));
//		int num = fread(pRgb, 4, nPlantNum, pfile);
//
//		printf("Color Plate Number: %d\n", nPlantNum);
//		printf("��ɫ����Ϣ:\n");
//		showRgbQuan(pRgb, nPlantNum);
//
//	}
//
//	int width = bitInfoHead.biWidth;
//	int height = bitInfoHead.biHeight;
//	//�����ڴ�ռ��Դͼ�����ڴ�   
//	int l_width = WIDTHBYTES(width* bitInfoHead.biBitCount);//����λͼ��ʵ�ʿ�Ȳ�ȷ����Ϊ32�ı���
//	long nData = height*l_width;
//	BYTE    *pColorData = new BYTE[nData];
//	memset(pColorData, 0, nData);
//
//	//��λͼ������Ϣ����������   
//	fread(pColorData, 1, nData, pfile);
//
//	//��λͼ����ת��ΪRGB����
//	RGBQUAD** dataOfBmp_src = NULL; //���ڱ�������ض�Ӧ��RGB����
//
//	dataOfBmp_src = new RGBQUAD*[height];
//	for (i = 0; i < height; i++)
//		dataOfBmp_src[i] = new RGBQUAD[width];
//
//	if (bitInfoHead.biBitCount<24)//�е�ɫ�壬��λͼΪ�����ɫ 
//	{
//		int k;
//
//		if (bitInfoHead.biBitCount <= 8 && !bitInfoHead.biCompression)
//		{
//
//			int pnum = 8 / bitInfoHead.biBitCount;
//			int mbnum = 8 - bitInfoHead.biBitCount;
//
//			for (int i = 0; i<height; i++)
//			{
//				int k0 = (height - i - 1)*l_width;//k:ȡ�ø�������ɫ������ʵ�����������е����
//				for (int j = 0; j<width; j++)
//				{
//					BYTE mixIndex = 0;
//					k = k0 + (j / pnum);
//					mixIndex = pColorData[k];
//					//mixIndex:��ȡ��ǰ���ص���ɫ������ɫ���е�����ֵ    
//					if (bitInfoHead.biBitCount < 8)
//					{
//						mixIndex = mixIndex << ((j%pnum)*bitInfoHead.biBitCount);
//						mixIndex = mixIndex >> mbnum;
//					}
//
//					//��������ɫ���ݣ�RGBA�����浽�����ж�Ӧ��λ��
//					dataOfBmp_src[i][j].rgbRed = pRgb[mixIndex].rgbRed;
//					dataOfBmp_src[i][j].rgbGreen = pRgb[mixIndex].rgbGreen;
//					dataOfBmp_src[i][j].rgbBlue = pRgb[mixIndex].rgbBlue;
//					dataOfBmp_src[i][j].rgbReserved = pRgb[mixIndex].rgbReserved;
//				}
//
//			}
//		}
//
//
//		if (bitInfoHead.biBitCount == 16)
//		{
//			if (!bitInfoHead.biCompression)
//			{
//				for (i = 0; i<height; i++)
//				{
//					int k0 = (height - i - 1)*l_width;
//					for (j = 0; j<width; j++)
//					{
//						WORD mixIndex = 0;
//						k = k0 + j * 2;
//						WORD shortTemp;
//						shortTemp = pColorData[k + 1];
//						shortTemp = shortTemp << 8;
//
//						mixIndex = pColorData[k] + shortTemp;
//						dataOfBmp_src[i][j].rgbRed = pRgb[mixIndex].rgbRed;
//						dataOfBmp_src[i][j].rgbGreen = pRgb[mixIndex].rgbGreen;
//						dataOfBmp_src[i][j].rgbBlue = pRgb[mixIndex].rgbBlue;
//						dataOfBmp_src[i][j].rgbReserved = pRgb[mixIndex].rgbReserved;
//					}
//				}
//			}
//		}
//	}
//	else//λͼΪ24/32λ���ɫ
//	{
//		int k;
//		int index = 0;
//
//		if (bitInfoHead.biBitCount == 16)
//		{
//			for (i = 0; i<height; i++)
//			{
//				int k0 = (height - i - 1)*l_width;
//				for (j = 0; j<width; j++)
//				{
//					k = k0 + j * 2;
//					if (!bitInfoHead.biCompression)//555��ʽ
//					{
//						dataOfBmp_src[i][j].rgbBlue = pColorData[k] & 0x1F;
//						dataOfBmp_src[i][j].rgbGreen = (((pColorData[k + 1] << 6) & 0xFF) >> 3) + (pColorData[k] >> 5);
//						dataOfBmp_src[i][j].rgbRed = (pColorData[k + 1] << 1) >> 3;
//						dataOfBmp_src[i][j].rgbReserved = 0;
//
//					}
//				}
//			}
//		}
//		if (bitInfoHead.biBitCount == 24 && !bitInfoHead.biCompression)
//		{
//			for (i = 0; i<height; i++)
//			{
//				int k0 = (height - i - 1)*l_width;
//				for (j = 0; j<width; j++)
//				{
//					k = k0 + (j * 3);
//					dataOfBmp_src[i][j].rgbRed = pColorData[k + 2];
//					dataOfBmp_src[i][j].rgbGreen = pColorData[k + 1];
//					dataOfBmp_src[i][j].rgbBlue = pColorData[k];
//					dataOfBmp_src[i][j].rgbReserved = 0;
//
//				}
//			}
//		}
//		if (bitInfoHead.biBitCount == 32 && !bitInfoHead.biCompression)
//		{
//			for (i = 0; i<height; i++)
//			{
//				int k0 = (height - i - 1)*l_width;
//				for (j = 0; j<width; j++)
//				{
//					k = k0 + (j * 4);
//					dataOfBmp_src[i][j].rgbRed = pColorData[k + 2];
//					dataOfBmp_src[i][j].rgbGreen = pColorData[k + 1];
//					dataOfBmp_src[i][j].rgbBlue = pColorData[k];
//					dataOfBmp_src[i][j].rgbReserved = pColorData[k + 3];
//
//				}
//			}
//
//		}
//
//	}
//
//
//#pragma endregion
//
//
//	RGBQUAD** dataOfBmp_dst = NULL;
//	dataOfBmp_dst = new RGBQUAD*[height];
//	for (i = 0; i<height; i++)
//		dataOfBmp_dst[i] = new RGBQUAD[width];
//
//
//
//
//	saveBmp(dataOfBmp_dst, width, height);
//
//	fclose(pfile);
//	if (bitInfoHead.biBitCount<24 && pRgb)
//	{
//		delete[]pRgb;
//	}
//	for (i = 0; i<height; i++)
//	if (dataOfBmp_src[i])
//		delete dataOfBmp_src[i];
//	if (dataOfBmp_src)
//		delete dataOfBmp_src;
//
//	for (i = 0; i<height; i++)
//	if (dataOfBmp_dst[i])
//		delete dataOfBmp_dst[i];
//	if (dataOfBmp_dst)
//		delete dataOfBmp_dst;
//
//
//	if (pColorData)
//		delete[]pColorData;
//
//
//}
