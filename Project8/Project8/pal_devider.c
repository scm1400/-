#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include<string.h>

#pragma pack(push, 1)  


#pragma pack(pop)

int main()
{
	char epf[20];
	char epf2[300];
	int index;
	printf("\n [ PAL Devider ]\n");
	printf("\n 2019.07.06 \n");
	printf("\n 구버전 개발자 무이스 만듬. \n");
	printf("\n Pal파일 이름을 적어주세요 ");

	scanf("%s", &epf);

	sprintf(epf2, "%s.pal", epf);

	printf("\n Pal의 개수는? ");

	scanf("%d", &index);


	printf("\n 처리중.. 프로그램이 꺼질 때 까지 기다려주세요. \n ");


		FILE *fpPal;
		FILE *fpTxt;

		//unsigned int *buffer;

		char filename[20];

		fpPal = fopen(epf2, "rb");
		if (fpPal == NULL)
			return 0;
		//buffer = malloc(4);
		//int count = fread(buffer, sizeof(int), 1, fpPal);
		fseek(fpPal,4,SEEK_SET);
		

		for (int i = 0; i <= index; i++)
		{
			
			unsigned char *buffer2;
			buffer2 = malloc(1056);
			fread(buffer2, 1056, 1, fpPal);

			sprintf(filename, "%03d.pal", i);

			fpTxt = fopen(filename, "wb");

			fwrite(buffer2, 1056, 1, fpTxt);

			free(buffer2);

			fclose(fpTxt);

		}

		fclose(fpPal);

}

