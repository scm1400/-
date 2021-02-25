#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include<string.h>
#include <stdint.h> 


int main()
{
	int iter;
	int offset_x;
	int offset_y;
	int count = 0;
	//char epf[20];
	//char epf2[300];
	printf("\n [ Position Offest ]\n");
	printf("\n 2019.07.06 \n");
	printf("\n  좌표값 오프셋 주기 \n");
	printf("\n 구버전 개발자 무이스 만듬. \n");
	printf("\n 사진의 개수(n)를 입력하세요: 00000.bmp ~ n.bmp ");
	scanf("%d", &iter);
	printf("\n");
	printf("\n x 오프셋을 적으세요 +는 왼쪽");
	scanf("%d", &offset_x);
	printf("\n");
	printf("\n y 오프셋을 적으세요 +는 아래 ");
	scanf("%d", &offset_y);
	printf("\n");

	//printf(" 기존 epf파일 이름을 적어주세요. xxxxx.epf ( 안적으면 픽셀 값 + 스텐실 값만 출력 )\n\n ");
	//scanf("%s", &epf);
	//sprintf(epf2, "%s.epf", epf);

	printf("\n 처리중.. 프로그램이 꺼질 때 까지 기다려주세요. \n ");

	for (int i = 0; i <= iter; i++)
	{
		
		FILE *fpBmp;
		FILE *fpTxt;

		if (count == 20)
		{
			count = 0;
		}

		char filename[20];
		sprintf(filename, "%05d.bmp", i);
		fpBmp = fopen(filename, "rb");
		if (fpBmp == NULL)
			return 0;


		unsigned char *buffer;

		fpTxt = fopen("epf.txt", "at+");

		buffer = malloc(2);

		fseek(fpBmp, -8, SEEK_END);
		short sum = 0;
		unsigned char data[2];
		int f = 0;

		short a = fread(buffer, 2, 1, fpBmp);
		sum += buffer[0] | (buffer[1] << 8);
		if (count <= 15 || count==18 || count==19 )
		{
			sum += offset_y;
		}
		else if (count ==16 || count== 17)
		{  
			sum -= 3;
		}
		else
		{
			sum -= offset_y;
		}
		memcpy(data, &sum, 2);
		for (f = 0; f < 2; f++)
		{
			fprintf(fpTxt, "%02x ", data[f]);
		}
		for (f = 0; f < 2; f++)
		{
			data[f] = 0;
		}
		//fprintf(fpTxt, "%hhx %hhx ", sum & 0xff, sum  | 0xff);
		//fprintf(fpTxt, "%d ", sum);
		sum = 0;

		short b = fread(buffer, 2, 1, fpBmp);
		sum += buffer[0] | (buffer[1] << 8);
		if (count <= 5 || count==14||count==15)
		{
			sum -= (offset_x);
		}
		if ((count > 5 && count <= 11) || count == 18 || count == 19)
		{
			sum += offset_x;
		}
		else
		{
			sum += 1;
		}
		memcpy(data, &sum, 2);
		for (f = 0; f < 2; f++)
		{
			fprintf(fpTxt, "%02x ", data[f]);
		}
		for (f = 0; f < 2; f++)
		{
			data[f] = 0;
		}
		//fprintf(fpTxt, "%hhx %hhx ", sum & 0xff, (sum / 0xff) & 0xff);
		//fprintf(fpTxt, "%02x ", sum);
		sum = 0;


		short c = fread(buffer, 2, 1, fpBmp);
		sum += buffer[0] | (buffer[1] << 8);
		if (count <= 15 || count == 18 || count == 19)
		{
			sum += offset_y;
		}
		else if (count == 16 || count == 17)
		{
			sum -= 3;
		}
		else
		{
			sum -= offset_y;
		}
		memcpy(data, &sum, 2);
		for (f = 0; f < 2; f++)
		{
			fprintf(fpTxt, "%02x ", data[f]);
		}
		for (f = 0; f < 2; f++)
		{
			data[f] = 0;
		}
		//fprintf(fpTxt, "%hhx %hhx ", sum & 0xff, (sum / 0xff) & 0xff);
		//fprintf(fpTxt, "%02x ", sum);
		sum = 0;

		short d = fread(buffer, 2, 1, fpBmp);
		sum += (buffer[0] | (buffer[1] << 8));
		if (count <= 5 || count == 14 || count == 15)
		{
			sum -= (offset_x);
		}
		if ((count > 5 && count <= 11) || count == 18 || count == 19)
		{
			sum += offset_x;
		}
		else
		{
			sum += 1;
		}
		memcpy(data, &sum, 2);
		for (f = 0; f < 2; f++)
		{
			fprintf(fpTxt, "%02x ", data[f]);
		}
		for (f = 0; f < 2; f++)
		{
			data[f] = 0;
		}
		//fprintf(fpTxt, "%hhx %hhx ", sum & 0xff, (sum / 0xff) & 0xff);
		//fprintf(fpTxt, "%02x ", sum);
		sum = 0;

		fprintf(fpTxt, "00 00 00 00 00 00 00 00");
		fprintf(fpTxt, "\n");

		count++;

		fclose(fpTxt);
		fclose(fpBmp);
	}
}