#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include<string.h>
#include<inttypes.h>

#pragma pack(push, 1)  

int t = 0;
int t2 = 0;
int t5 = 0;
int t6 = 0;
int numArr[50000];
int numArr2[10000];

typedef struct _BITMAPFILEHEADER
{
	unsigned short bfType;
	unsigned int   bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int   bfOffBits;
} BITMAPFILEHEADER;

typedef struct _BITMAPINFOHEADER
{
	unsigned int   biSize;
	int32_t          biWidth;
	int32_t          biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int   biCompression;
	unsigned int   biSizeImage;
	int            biXPelsPerMeter;
	int            biYPelsPerMeter;
	unsigned int   biClrUsed;
	unsigned int   biClrImportant;
} BITMAPINFOHEADER;

typedef struct _RGBTRIPLE
{
	unsigned char rgbtBlue;
	unsigned char rgbtGreen;
	unsigned char rgbtRed;
} RGBTRIPLE;


#pragma pack(pop)

#define PIXEL_SIZE   1   
#define PIXEL_ALIGN  4   

int main()
{
	int iter;
	char epf[10];
	char epf2[10];

	printf("������ ����(n)�� �Է��ϼ���: 00000.bmp ~ n.bmp ");
	scanf("%d", &iter);

	printf("���� epf���� �̸��� �����ּ���: xxxxx.epf ");
	scanf("%s", &epf);
	sprintf(epf2, "%s.epf", epf);

	for (int i = 0; i <= iter; i++)
	{
		FILE *fpBmp;
		FILE *fpTxt;
		BITMAPFILEHEADER fileHeader;
		BITMAPINFOHEADER infoHeader;

		unsigned char *image;
		int size;
		int width, height;
		int padding;


		char filename[20];
		sprintf(filename, "%05d.bmp", i);
		fpBmp = fopen(filename, "rb");
		if (fpBmp == NULL)
			return 0;

		if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp) < 1)
		{
			fclose(fpBmp);
			return 0;
		}

		if (fileHeader.bfType != 'MB')
		{
			fclose(fpBmp);
			return 0;
		}

		if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp) < 1)
		{
			fclose(fpBmp);
			return 0;
		}

		if (infoHeader.biBitCount != 8)
		{
			fclose(fpBmp);
			return 0;
		}

		size = infoHeader.biSizeImage;
		width = infoHeader.biWidth;
		height = infoHeader.biHeight;

		padding = (PIXEL_ALIGN - ((width * PIXEL_SIZE) % PIXEL_ALIGN)) % PIXEL_ALIGN;

		if (size == 0)
		{
			size = (width * PIXEL_SIZE + padding) * height;
		}

		image = malloc(size);

		fseek(fpBmp, fileHeader.bfOffBits, SEEK_SET);

		if (fread(image, size, 1, fpBmp) < 1)
		{
			fclose(fpBmp);
			return 0;
		}

		fclose(fpBmp);

		fpTxt = fopen("stencil.epf", "ab+");
		if (fpTxt == NULL)
		{
			free(image);
			return 0;
		}

		int c = 0;
		int d = 128;

		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{

				int index = (x * PIXEL_SIZE) + (y * (width * PIXEL_SIZE)) + (padding * y);


				int pixel = image[index];

				fwrite(image,sizeof(char),size, fpTxt);
			}

			//fprintf(fpTxt, "\n");
		}

		//�� ���� ���ٽ� �ۼ� �ȼ� ���� �������� 0�̸� k�� ��ŭ 0k �� ������ ǥ���ϰ�
		//0���� ū �ȼ� ���� �������� ������ 128 + ������ ǥ��
		//���� �ȼ� ���� 0 ���� �������Ǹ� 0������ ������� 00(�ٸ�ħ)ǥ��
		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				int index = (x * PIXEL_SIZE) + (y * (width * PIXEL_SIZE)) + (padding * y);

				int pixel = image[index];

				if (pixel == 0)
				{
					c++;
					if (d > 128)
					{
						fprintf(fpTxt, "%02x", d);
						d = 128;
					}
					if (((index - padding * y) % width == width - 1) && c > 0)
					{
						if (c == width)
						{
							c = width;
							fprintf(fpTxt, "%02x", c);
							fprintf(fpTxt, "00");
						}
						else
						{
							c = 0;
							fprintf(fpTxt, "%02x", c);
						}

					}

				}
				else if (pixel > 0)
				{
					d++;
					if (c > 0)
					{
						fprintf(fpTxt, "%02x", c);
						c = 0;
					}

					if (((index - padding * y) % width == width - 1) && c == 0)
					{
						fprintf(fpTxt, "%02x", d);
						fprintf(fpTxt, "%02x", c);
					}

				}
			}
			c = 0;
			d = 128;
			//fprintf(fpTxt, "\n");  
		}

		fclose(fpTxt);

		free(image);
	}

	for (int i = 0; i <= iter; i++)
	{
		FILE *fpBmp;
		FILE *fpTxt;
		FILE *fpEpf;
		BITMAPFILEHEADER fileHeader;
		BITMAPINFOHEADER infoHeader;

		//size_t result;
		unsigned char *buffer;

		unsigned char *image;
		int size;
		int width, height;
		int padding;
		//unsigned char* epf_str;



		fpEpf = fopen(epf2, "rb");
		if (fpEpf == NULL)
		{
			puts(" Cannot file open ! ");
			return 1;
		}
		buffer = malloc(16);
		//epf_str = malloc(16);
		fseek(fpEpf, -16 * (iter + 1) + 16 * i, SEEK_END);

		fread(buffer, 16, 1, fpEpf);

		//fgets(epf_str, 16, fpEpf);

		fclose(fpEpf);

		char filename[20];
		sprintf(filename, "%05d.bmp", i);
		fpBmp = fopen(filename, "rb");
		if (fpBmp == NULL)
			return 0;

		if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp) < 1)
		{
			fclose(fpBmp);
			return 0;
		}

		if (fileHeader.bfType != 'MB')
		{
			fclose(fpBmp);
			return 0;
		}

		if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp) < 1)
		{
			fclose(fpBmp);
			return 0;
		}

		if (infoHeader.biBitCount != 8)
		{
			fclose(fpBmp);
			return 0;
		}

		size = infoHeader.biSizeImage;
		width = infoHeader.biWidth;
		height = infoHeader.biHeight;

		padding = (PIXEL_ALIGN - ((width * PIXEL_SIZE) % PIXEL_ALIGN)) % PIXEL_ALIGN;

		if (size == 0)
		{
			size = (width * PIXEL_SIZE + padding) * height;
		}

		image = malloc(size);

		fseek(fpBmp, fileHeader.bfOffBits, SEEK_SET);

		if (fread(image, size, 1, fpBmp) < 1)
		{
			fclose(fpBmp);
			return 0;
		}

		fclose(fpBmp);

		fpTxt = fopen("stencil.epf", "ab+");
		if (fpTxt == NULL)
		{
			free(image);
			return 0;
		}
		for (int b = 0; b <= 7; b++)
		{
			int buf = buffer[b];
			fprintf(fpTxt, "%02x", buf);
		}
		//fprintf(fpTxt, "%s ", epf_str);
		//fwrite(buffer,sizeof(unsigned int)*2,8, fpTxt);
		int c = 0;
		int d = 128;

		//�� ���� ���ٽ� �ۼ� �ȼ� ���� �������� 0�̸� k�� ��ŭ 0k �� ������ ǥ���ϰ�
		//0���� ū �ȼ� ���� �������� ������ 128 + ������ ǥ��
		//���� �ȼ� ���� 0 ���� �������Ǹ� 0������ ������� 00(�ٸ�ħ)ǥ��
		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				int index = (x * PIXEL_SIZE) + (y * (width * PIXEL_SIZE)) + (padding * y);

				int pixel = image[index];

				if (pixel == 0)
				{
					c++;
					if (d > 128)
					{
						//fprintf(fpTxt, "%02x ", d);
						d = 128;
						t++;
					}
					if (((index - padding * y) % width == width - 1) && c > 0)
					{
						if (c == width)
						{
							c = width;
							//fprintf(fpTxt, "%02x ", c);
							//fprintf(fpTxt, "00 ");
							t += 2;
						}
						else
						{
							c = 0;
							//fprintf(fpTxt, "%02x ", c);
							t++;
						}

					}

				}

				else if (pixel > 0)
				{
					d++;
					if (c > 0)
					{
						//fprintf(fpTxt, "%02x ", c);
						t++;
						c = 0;
					}

					if (((index - padding * y) % width == width - 1) && c == 0)
					{
						//fprintf(fpTxt, "%02x ", d);
						//fprintf(fpTxt, "%02x ", c);
						t += 2;
					}

				}
			}
			c = 0;
			d = 128;
			//fprintf(fpTxt, "\n");  
		}
		numArr[i + 1] = t;
		t = 0;
		numArr2[i + 1] = width * height;
		if (i == 0)
		{
			//fprintf(fpTxt, "\n");
			fprintf(fpTxt, "00000000");
			if (width * height < 256)
			{
				fprintf(fpTxt, "%02x000000", width * height);
			}
			else if (width * height < 65536)
			{
				fprintf(fpTxt, "%02x0000", width * height);
			}
			//fprintf(fpTxt, "\n");
		}
		else
		{
			int p = 0;
			int t3 = 0;
			unsigned char data[4];

			int o = 1;
			while (o <= i)
			{
				p += numArr[o];
				o++;
			}

			int z = 1;
			t2 = 0;
			while (z <= i)
			{
				t2 += numArr2[z];
				z++;
			}
			int max = 0x00;
			max = t2 + p;
			//������ġ : ���� �ִ� ���ٽ��� �� ���� (p) + ���� �̹������� ���� �� +1
			memcpy(data, &max, 4);
			int f = 0;
			for (f = 0; f < 4; f++)
			{
				fprintf(fpTxt, "%02x", data[f]);
			}
			for (f = 0; f < 4; f++)
			{
				data[f] = 0;
			}
			//����ġ : ������ġ + ����-1
			t3 = width * height;
			int max2 = 0x00;
			max2 = (max + t3);

			memcpy(data, &max2, 4);
			for (f = 0; f < 4; f++)
			{
				fprintf(fpTxt, "%02x", data[f]);
			}

			if (i == iter)
			{
				o = 1;

				while (o <= iter + 1)
				{
					t5 += numArr[o];
					o++;
				}

				z = 1;

				while (z <= iter + 1)
				{
					t6 += numArr2[z];
					z++;
				}
			}

		}

		fclose(fpTxt);

		free(image);
		free(buffer);
	}
	return 0;
}