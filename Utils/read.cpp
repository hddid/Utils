#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "cJSON.h"


int main()
{
	const char* version = cJSON_Version();
	printf("version:%s\n", version);
	FILE* file = fopen("./test.json", "r");
	if (NULL == file)
	{
		printf("load file fail!\n");
		return -1;
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* tmpStr = (char*)malloc(size + 1);
	memset(tmpStr, 0, size + 1);
	size_t ret = fread(tmpStr, size, 1, file);
	tmpStr[size] = '\0';
	printf("ret = %d size = %ld str=%s\n", ret, size, tmpStr);

	cJSON* root = cJSON_Parse(tmpStr);
	cJSON* map_id = cJSON_GetObjectItem(root, "map_id");
	if (NULL != map_id)
		printf("mapid is %d\n", map_id->valueint);

	cJSON *rect = cJSON_GetObjectItem(root, "rect");
	if (NULL != rect)
	{
		if (cJSON_IsArray(rect))
		{
			int len = cJSON_GetArraySize(rect);
			for (int i = 0; i < len; i++)
			{
				cJSON* pos = cJSON_GetArrayItem(rect, i);
				printf("i=%d value = %d\n", i, pos->valueint);
			}
		}
		else
		{
			printf("the rect is not an array!\n");
		}
	}
	else
	{
		printf("rect is null\n");
	}

	cJSON *areas = cJSON_GetObjectItem(root, "areas");
	if (NULL != areas)
	{
		if (cJSON_IsArray(areas))
		{
			int num = cJSON_GetArraySize(areas);
			cJSON* area = areas->child;
			for (int i = 0; i < num; i++)
			{
				//cJSON_Print(cJSON_GetObjectItem(area,"id"));
				cJSON* id = cJSON_GetObjectItem(area, "id");
				printf("id = %d\n", id->valueint);
				cJSON* name = cJSON_GetObjectItem(area, "name");
				printf("name = %s\n", name->valuestring);
				cJSON* rect = cJSON_GetObjectItem(area, "rect");
				{
					if (cJSON_IsArray(rect))
					{
						int n = cJSON_GetArraySize(rect);
						for (int j = 0; j < n; j++)
						{
							cJSON* item = cJSON_GetArrayItem(rect, j);
							{
								printf("item = %d\n", item->valueint);
							}
						}
					}
					else
					{
						printf("not a array\n");

					}

				}
				area = area->next;
			}
		}
		else
		{
			{
				printf("the areas is not a array\n");
			}
		}

	}
	else
	{
		printf("areas is null\n");
	}


	fclose(file);
	free(tmpStr);
	system("pause");

	return 0;
}