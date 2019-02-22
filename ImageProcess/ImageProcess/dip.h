//ReadBitMap
//
#define _CRT_SECURE_NO_WARNINGS
#include<math.h>   
#include<stdio.h>   
#include<stdlib.h>   
#include <malloc.h>
#include <memory.h>
#include <math.h>


#define   WIDTHBYTES(bits) (((bits)+31)/32*4)
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

#pragma pack(1) //ǿ���ڴ���1�ֽ�Ϊ��λ����

//λͼ�ļ�ͷ��Ϣ�ṹ����
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������Ҫ�Ǽ��˵Ļ���������ȷ��ȡ�ļ���Ϣ��
typedef struct tagBITMAPFILEHEADER {
	WORD   bfType;
	DWORD  bfSize;               //�ļ���С
	WORD   bfReserved1; //�����֣�������
	WORD   bfReserved2; //�����֣�ͬ��
	DWORD bfOffBits;         //ʵ��λͼ���ݵ�ƫ���ֽ�������ǰ�������ֳ���֮��
} BITMAPFILEHEADER;

//��ϢͷBITMAPINFOHEADER��Ҳ��һ���ṹ���䶨�����£�
typedef struct tagBITMAPINFOHEADER{
	//public:
	DWORD   biSize;                  //ָ���˽ṹ��ĳ��ȣ�Ϊ40
	LONG    biWidth;        //λͼ��
	LONG    biHeight;       //λͼ��
	WORD    biPlanes;        //ƽ������Ϊ1
	WORD    biBitCount;       //������ɫλ����������1��2��4��8��16��24���µĿ�����32
	DWORD   biCompression;           //ѹ����ʽ��������0��1��2������0��ʾ��ѹ��
	DWORD   biSizeImage;             //ʵ��λͼ����ռ�õ��ֽ���
	LONG    biXPelsPerMeter;   //X����ֱ���
	LONG    biYPelsPerMeter;   //Y����ֱ���
	DWORD   biClrUsed;                  //ʹ�õ���ɫ�������Ϊ0�����ʾĬ��ֵ(2^��ɫλ��)
	DWORD   biClrImportant;             //��Ҫ��ɫ�������Ϊ0�����ʾ������ɫ������Ҫ��
} BITMAPINFOHEADER;

//��ɫ��Palette����Ȼ�������Ƕ���Щ��Ҫ��ɫ���λͼ�ļ����Եġ�24λ��32λ�ǲ���Ҫ��ɫ��ġ�
//���ƺ��ǵ�ɫ��ṹ���������ʹ�õ���ɫ������
typedef struct tagRGBQUAD {
	//public:
	BYTE     rgbBlue; //����ɫ����ɫ����
	BYTE     rgbGreen; //����ɫ����ɫ����
	BYTE     rgbRed; //����ɫ�ĺ�ɫ����
	BYTE     rgbReserved; //����ֵ
} RGBQUAD;
using namespace std;


/*�������ܣ�λͼ�ļ�ͷ��ʾ
���������BITMAPFILEHEADER* pBmpHead ָ��λͼ�ļ�ͷ�ṹ��ָ��
�����ڴ��ַ��ʵ����������ʵ�κͱ��������βε��ڴ湲��
���ֵ��û��
*/

void showBmpHead(BITMAPFILEHEADER* pBmpHead)
{
	printf("λͼ�ļ�ͷ:\n");
	printf("�ļ�����:%x\n", pBmpHead->bfType);
	printf("�ļ���С:%d\n", pBmpHead->bfSize);
	printf("������:%d\n", pBmpHead->bfReserved1);
	printf("������:%d\n", pBmpHead->bfReserved2);
	printf("ʵ��λͼ���ݵ�ƫ���ֽ���:%d\n", pBmpHead->bfOffBits);
}

/*�������ܣ�λͼ��Ϣͷ��ʾ
���������BITMAPINFOHEADER* pBmpInforHead ָ��λͼ�ļ���Ϣͷ�ṹ��ָ��
�����ڴ��ַ��ʵ����������ʵ�κͱ��������βε��ڴ湲��
���ֵ��û��
*/
void showBmpInforHead(BITMAPINFOHEADER* pBmpInforHead)
{
	printf("λͼ��Ϣͷ:\n");
	printf("�ṹ��ĳ���:%d\n", pBmpInforHead->biSize);
	printf("λͼ��:%d\n", pBmpInforHead->biWidth);
	printf("λͼ��:%d\n", pBmpInforHead->biHeight);
	printf("biPlanesƽ����:%d\n", pBmpInforHead->biPlanes);
	printf("biBitCount������ɫλ��:%d\n", pBmpInforHead->biBitCount);
	printf("ѹ����ʽ:%d\n", pBmpInforHead->biCompression);
	printf("biSizeImageʵ��λͼ����ռ�õ��ֽ���:%d\n", pBmpInforHead->biSizeImage);
	printf("X����ֱ���:%d\n", pBmpInforHead->biXPelsPerMeter);
	printf("Y����ֱ���:%d\n", pBmpInforHead->biYPelsPerMeter);
	printf("ʹ�õ���ɫ��:%d\n", pBmpInforHead->biClrUsed);
	printf("��Ҫ��ɫ��:%d\n", pBmpInforHead->biClrImportant);
}

/*�������ܣ���ɫ������ģʽ����λͼ������������RGBֵ�����ģʽ����ʾ
���������RGBQUAD* pRGB --- RGBAlpha ��Ԫ�ؽṹ��ָ�����
DWORD num --- Ҫ��ʾ��RGBAlpha ��Ԫ�ؽṹ�������
����ɫ���Ȼ�Ҫ��ʾ�����ظ���
���ֵ��  û��
*/
void showRgbQuan(RGBQUAD* pRGB, DWORD num)
{
	for (DWORD i = 0; i<num; i++)
	{
		if (i % 5 == 0)
		{
			printf("\n");
		}
		printf("(%-3d,%-3d,%-3d)   ", (pRGB + i)->rgbRed, (pRGB + i)->rgbGreen, (pRGB + i)->rgbBlue);
	}
	printf("\n");

}

/*�������ܣ�ͼ��ɫ
���������RGBQUAD* dataOfBmp_src --- ԭͼ���������أ�����Ϊ�򣩶�Ӧ��
RGBAlpha ��Ԫ�ؽṹ��ָ�룻
RGBQUAD* dataOfBmp_dst --- ��ɫ���ͼ���������أ�����Ϊ�򣩶�Ӧ��
RGBAlpha ��Ԫ�ؽṹ��ָ�룻
DWORD width, DWORD height --- ԭͼ������ͼ��Ŀ�Ⱥ͸߶�
��������Ϊ��λ��
���ֵ��  û��
*/
void reverseColor(RGBQUAD** dataOfBmp_src, RGBQUAD** dataOfBmp_dst, DWORD width, DWORD height)
{
	for (DWORD i = 0; i<height; i++)
	for (DWORD j = 0; j<width; j++)
	{
		dataOfBmp_dst[i][j].rgbRed = 255 - dataOfBmp_src[i][j].rgbRed;
		dataOfBmp_dst[i][j].rgbGreen = 255 - dataOfBmp_src[i][j].rgbGreen;
		dataOfBmp_dst[i][j].rgbBlue = 255 - dataOfBmp_src[i][j].rgbBlue;
	}
}

/*�������ܣ���ɫͼ��ת��Ϊ�Ҷ�ͼ��
���������RGBQUAD** dataOfBmp_src --- ԭͼ���������أ�����Ϊ�򣩶�Ӧ��
RGBAlpha ��Ԫ�ؽṹ��ָ�룻
RGBQUAD** dataOfBmp_dst --- ת��Ϊ�Ҷ�ͼ����ͼ���������أ�����Ϊ�򣩶�Ӧ��RGBAlpha ��Ԫ�ؽṹ��ָ�룻
BYTE** dataOfBmp_gray --- ת��Ϊ�Ҷ�ͼ����ͼ���������أ�����Ϊ�򣩶�Ӧ�ĻҶ�ֵ��
DWORD width, DWORD height --- ԭͼ������ͼ��Ŀ�Ⱥ͸߶�
��������Ϊ��λ��
���ֵ��  û��
*/
void RGB2Gray(RGBQUAD** dataOfBmp_src, RGBQUAD** dataOfBmp_dst, BYTE** dataOfBmp_gray, DWORD width, DWORD height)
{
	double gray;

	for (DWORD i = 0; i<height; i++)
	{
		for (DWORD j = 0; j<width; j++)
		{
			gray = 0.299*dataOfBmp_src[i][j].rgbRed + 0.587*dataOfBmp_src[i][j].rgbGreen + 0.114*dataOfBmp_src[i][j].rgbBlue;
			dataOfBmp_gray[i][j] = (BYTE)gray;
			dataOfBmp_dst[i][j].rgbRed = (BYTE)gray;
			dataOfBmp_dst[i][j].rgbGreen = (BYTE)gray;
			dataOfBmp_dst[i][j].rgbBlue = (BYTE)gray;
		}
	}
}

/*�������ܣ��Ҷ�ͼ���Ľ��ڣ�flag=0����˽��ڣ�flag=1���Աȶ�
���������BYTE* dataOfBmp_gray --- �Ҷ�ͼ���������أ�����Ϊ�򣩶�Ӧ�ĻҶ�ֵ��
DWORD width, DWORD height --- ԭͼ������ͼ��Ŀ�Ⱥ͸߶�
��������Ϊ��λ��
bool flag --- �Ľ��ڻ�˽��ڱ�־�� flag=0Ϊ�Ľ��ڣ�flag=1Ϊ�˽���
���ֵ��  �Ľ��ڣ�flag=0����˽��ڣ�flag=1���Աȶ�
*/
double contrast(BYTE** dataOfBmp_gray, DWORD width, DWORD height, bool flag)
{
	DWORD i, j;
	double contrast_sum = 0;
	int tmp0 = 2, tmp1 = 3, tmp2 = 4;
	int num = 0;

	if (flag)
	{
		tmp0 = 3;
		tmp1 = 5;
		tmp2 = 8;
	}
	num = 4 * tmp0 + ((width - 2) + (height - 2)) * 2 * tmp1 + ((width - 2)*(height - 2))*tmp2;

	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			if (i>0)
			{
				contrast_sum += pow((dataOfBmp_gray[i - 1][j] - dataOfBmp_gray[i][j]), 2.0);
				if (flag)
				{
					if (j>0)
					{
						contrast_sum += pow((dataOfBmp_gray[i - 1][j - 1] - dataOfBmp_gray[i][j]), 2.0);
					}
					if (j<width - 1)
					{
						contrast_sum += pow((dataOfBmp_gray[i - 1][j + 1] - dataOfBmp_gray[i][j]), 2.0);
					}
				}
			}
			if (i<height - 1)
			{
				contrast_sum += pow((dataOfBmp_gray[i + 1][j] - dataOfBmp_gray[i][j]), 2.0);
				if (flag)
				{
					if (j>0)
					{
						contrast_sum += pow((dataOfBmp_gray[i + 1][j - 1] - dataOfBmp_gray[i][j]), 2.0);
					}
					if (j<width - 1)
					{
						contrast_sum += pow((dataOfBmp_gray[i + 1][j + 1] - dataOfBmp_gray[i][j]), 2.0);
					}
				}
			}

			if (j>0)
			{
				contrast_sum += pow((dataOfBmp_gray[i][j - 1] - dataOfBmp_gray[i][j]), 2.0);
			}

			if (j<width - 1)
			{
				contrast_sum += pow((dataOfBmp_gray[i][j + 1] - dataOfBmp_gray[i][j]), 2.0);
			}

		}
	}

	return contrast_sum / num;
}

int sswr(double num)
{

	if (num - (int)num > 0.5)
	{
		num = (int)num + 1;
	}
	else
	{
		num = (int)num;
	}

	return num;
}

void sort  (int a[], int n)
{
	int temp;

	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (a[i] > a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

/*�������ܣ�д��32λ��λͼ�������棩
���������RGBQUAD* dataOfBmp --- ���洢ͼ���������أ�����Ϊ�򣩶�Ӧ��
RGBAlpha ��Ԫ�ؽṹ��ָ�룻
DWORD width, DWORD height --- ���洢ͼ��Ŀ�Ⱥ͸߶�
��������Ϊ��λ��
���ֵ��  û��
*/
void saveBmp(RGBQUAD** dataOfBmp, DWORD width, DWORD height)
{
	DWORD i, j;
	BITMAPFILEHEADER   bitHead;
	BITMAPINFOHEADER bitInfoHead;
	WORD biBitCount = 32;
	FILE* pfile;
	char strFile[50];
	printf("please input the .bmp destination file name:\n");
	scanf("%s", strFile);
	pfile = fopen(strFile, "wb");//���ļ�
	if (pfile != NULL)
	{
		printf("file %s open success.\n", strFile);
		//дλͼ�ļ�ͷ��Ϣ
		bitHead.bfType = 0x4d42;
		bitHead.bfSize = 0;
		bitHead.bfReserved1 = 0;
		bitHead.bfReserved2 = 0;
		bitHead.bfOffBits = 54;
		if (biBitCount <= 8)
			bitHead.bfOffBits += (DWORD)pow(2.0, biBitCount) * 4;
		fwrite(&bitHead, 1, sizeof(tagBITMAPFILEHEADER), pfile);

		bitInfoHead.biSize = 40;
		bitInfoHead.biWidth = width;
		bitInfoHead.biHeight = height;
		bitInfoHead.biPlanes = 1;
		bitInfoHead.biBitCount = biBitCount;
		bitInfoHead.biCompression = 0;
		bitInfoHead.biSizeImage = 0;
		bitInfoHead.biXPelsPerMeter = 0;
		bitInfoHead.biYPelsPerMeter = 0;
		bitInfoHead.biClrImportant = 0;
		bitInfoHead.biClrUsed = 0;
		fwrite(&bitInfoHead, 1, sizeof(tagBITMAPINFOHEADER), pfile);

		if (biBitCount <= 8)
		{
			BYTE tmp = 0;

			for (i = 0; i<(DWORD)pow(2.0, biBitCount); i++)
			{
				tmp = (BYTE)i;
				fwrite(&tmp, 1, 4, pfile);
			}
		}

		int l_width = WIDTHBYTES(width * biBitCount) - width * 4;//����Ϊȷ��λͼ��������ʵ�ʿ��Ϊ32�ֽڵ�����������ӵ�0�ֽڸ���

		for (i = 0; i<height; i++)
		{
			for (j = 0; j<width; j += 1)
			{
				fwrite(&dataOfBmp[height - i - 1][j], 1, 4, pfile);

			}

			BYTE tmp = 0;
			for (j = 0; j<l_width; j++)
				fwrite(&tmp, 1, 1, pfile);

		}
	}

	fclose(pfile);

}