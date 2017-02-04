
#include <json.h>
#include <stdio.h>
#include "../include/route4me.h"


int deserialize(const char* szFile, char** strJson)
{
    char* buffer = NULL;
    size_t len = 0;
    int nRet = 0;

    FILE* fp = fopen(szFile, "r");
    if (!fp)
    {
        nRet = -1;
    }
    else
    {
        while (nRet = getline(&buffer, &len, fp) != -1)
        {
            *strJson = realloc(*strJson, len);
            if (**strJson == '\0')
                strcpy(*strJson, buffer);
            else
                strcat(*strJson, buffer);
        }
        fclose(fp);
    }
    return nRet;
}
