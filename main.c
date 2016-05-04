//
//  main.c
//  video-bender
//
//  Created by fairy-slipper on 5/4/16.
//  Copyright © 2016 fairy-slipper. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char filename[1000];
char newFilename[1000];
int injectScale;

int main(int argc, const char * argv[]) {

    srand(time(NULL));
    
    if (argc < 5) {
        perror("Use the following format: ./vbend -f <filename> -i <inject value>\n");
        exit(0);
    }
    
    for (int i=1; i<argc; i++) {
        if (!strcmp(argv[i], "-f")) {
            if (argv[i+1] != NULL) {
                strcpy(filename, argv[i+1]);
                i++;
            } else {
                perror("Please enter filename.\n");
                exit(0);
            }
        }
        if (!strcmp(argv[i], "-i")) {
            if (argv[i+1] != NULL) {
                injectScale = atoi(argv[i+1]);
                i++;
            } else {
                perror("Please enter inject value.\n");
                exit(0);
            }
        }
    }
    
    FILE *filefd = fopen(filename, "r+");
    if (filefd == NULL) {
        perror("Error opening file.\n");
    }
    
    int b = 0;
    for (int i=0; i<strlen(filename); i++) {
        
        if (b) {
            char tmpstr[100];
            sprintf(tmpstr, "%c", filename[i]);
            strcat(newFilename, tmpstr);
        }
        
        if (filename[i]=='.') {
            b = 1;
            int n = rand()%1000;
            sprintf(newFilename, "%i.", n);
        }
    }
    
    FILE *newfd = fopen(newFilename, "w");
    
    int c = 0;
    int idx = 0;
    while ((c = fgetc(filefd)) != EOF) {
        
        int r = rand()%injectScale;
        int n = rand()%256;
        if (r == 0) {
            c = n;
        }
        fputc(c, newfd);
        
        idx++;
    }
    printf("\n");
    fclose(filefd);
    fclose(newfd);
    
    return 0;
}
