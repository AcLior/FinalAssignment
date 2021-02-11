//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//
//void main() {
//	char** childrenPtr;
//	int size = 0;
//
//	printf("Enter size\n");
//	scanf("%d", &size);
//
//	childrenPtr = (char**)malloc(size*sizeof(char));
//	
//	for (int i = 0; i < size; i++) {
//		childrenPtr[i] =(char*)malloc(10*sizeof(char));
//		printf("Enter a children\n");
//		scanf("%s", &(*childrenPtr[i]));
//		printf("child: %s\n", &(*childrenPtr[i]));
//	}
//	printf("child: %s\n", &(*childrenPtr[0]));
//	printf("child: %s\n", &(*childrenPtr[1]));
//
//}