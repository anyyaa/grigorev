#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <dirent.h>
#include <fileapi.h>
#include <locale.h>


int matchPattern(const char* str, const char* pattern) {
    while (*str && *pattern) {
        if (*pattern == '*') {
            while (*pattern == '*')
                pattern++;
            if (*pattern == 0) 
                return 1;
            while (*str) {
                if (matchPattern(str, pattern))
                    return 1;
                str++;
            }
            return 0;
        }
        else if (*pattern == '?' || *str == *pattern) {
            str++;
            pattern++;
        }
        else {
            return 0;
        }
    }
    return *str == 0 && *pattern == 0;
}


void searchFiles(char* directory, char** patterns, int num_patterns) {
    WIN32_FIND_DATAA FindFileData;
    HANDLE hFind;

    char searchPath[MAX_PATH];
    snprintf(searchPath, MAX_PATH, "%s\\*", directory);

 
    hFind = FindFirstFileA(searchPath, &FindFileData);
    do {
        if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(FindFileData.cFileName, ".") == 0 || strcmp(FindFileData.cFileName, "..") == 0) {
                continue;
            }
            char subdirectory[MAX_PATH];
            snprintf(subdirectory, MAX_PATH, "%s\\%s", directory, FindFileData.cFileName);
            searchFiles(subdirectory, patterns, num_patterns);
        }
        else {
            
            for (int i = 0; i < num_patterns; ++i) {
                if (matchPattern(FindFileData.cFileName, patterns[i])) {
                    printf("Файл найден: %s\\%s\n", directory, FindFileData.cFileName);
                    break; 
                }
            }
        }
    } while (FindNextFileA(hFind, &FindFileData) != 0);

    FindClose(hFind);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");
    if (argc < 3 || argv[0] == "/?" || argv[0] == "-?") {
        fprintf(stderr, "Использование: %s <каталог> <шаблон1> [<шаблон2> ...]\n", argv[0]);
        return 1;
    }
    char* directory = argv[1];
    char** patterns = argv + 2; 
    int num_patterns = argc - 2;

    searchFiles(directory, patterns, num_patterns);

    return 0;
}
