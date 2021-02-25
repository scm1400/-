#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include<string.h>
#include <stdint.h> 


int main()
{
	int iter;
	int table;
	int start;
	//char epf[20];
	//char epf2[300];
	printf("\n [ Position Offest ]\n");
	printf("\n 2019.07.06 \n");
	printf("\n  바디 tbl만들자 \n");
	printf("\n 구버전 개발자 무이스 만듬. \n");
	printf("\n 몇개 인덱스 ?");
	scanf("%d", &iter);
	printf("\n");
	printf("\n 테이블 시작번호 ?");
	scanf("%d", &table);
	printf("\n");
	printf("\n y 이미지 시작넘버 ");
	scanf("%d", &start);
	printf("\n");

	//printf(" 기존 epf파일 이름을 적어주세요. xxxxx.epf ( 안적으면 픽셀 값 + 스텐실 값만 출력 )\n\n ");
	//scanf("%s", &epf);
	//sprintf(epf2, "%s.epf", epf);

	printf("\n 처리중.. 프로그램이 꺼질 때 까지 기다려주세요. \n ");

	for (int i = 0; i < iter; i++)
	{

		FILE *fpTxt;
		unsigned char *data;
		int f = 0;

		int number = start + 104 * i;

		fpTxt = fopen("tbl.txt", "at+");

		data = malloc(4);

		fprintf(fpTxt, "%02x 00 00 00 ", table+i);
		fprintf(fpTxt, "00 00 00 00 ");

		

		memcpy(data, &number, 4);
		for (f = 0; f < 4; f++)
		{
			fprintf(fpTxt, "%02x", data[f]);
		}
		for (f = 0; f < 4; f++)
		{
			data[f] = 0;
		}
		fprintf(fpTxt, "\n");
		fclose(fpTxt);

	}
}