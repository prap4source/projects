/* Program to calculate md5csum */
#include <openssl/md5.h>
#include "common.h"
/* 
 * http://stackoverflow.com/questions/7627723/how-to-create-a-md5-hash-of-a-string-in-c
 * usage str2md5(fileName, strlen(fileName))
 */
char *str2md5(const char *str, int length) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}

char *calc_md5(char *fileName) {
    FILE *fptr;
    unsigned char decrypt[16];
    int i;
    char temp[100];
    char *out = (char *)malloc(33);
    bool create_file = false;
    
    fptr = fopen(fileName,"rb+");
    /* create file if not present */
    if (!fptr) {
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	    log ("%s file not found @%s", fileName, cwd);
	create_file = true;
	fptr = fopen(fileName, "wb+");
    }

    if(fptr){
	fgets(temp,100,fptr);
	log ("%s opened file ", fileName);
	MD5_CTX md5;
	MD5_Init(&md5);
	while(!feof(fptr))
	{
	    MD5_Update(&md5,temp,strlen((char *)temp));
	    fgets(temp, 100, fptr);
	}
	MD5_Final(decrypt, &md5);
    } else{
	log ("%s fail open,this is not a file ", fileName);
	MD5_CTX md5;
	MD5_Init(&md5);
	MD5_Update(&md5,fileName,strlen((char *)fileName));
	MD5_Final(decrypt,&md5);
    }

    /* remove file */
    //if (create_file) 
    //remove(fileName);

    
    for(i = 0; i < 16; i++) {
	//log("%02x ",decrypt[i]);
	char *p = &out[i*2];
	snprintf(p, 16*2, "%02x", (unsigned int)decrypt[i]);
	if (i == 15)
	    log("\n");
    }
    return out;
}

void start_md5()
{
    char fileName[] = {'\0'};
    char *output = (char *) malloc(64);
    printf("input file name:");
    scanf("%s",fileName);
    output = calc_md5(fileName);
    
    if (output != NULL) {
	printf("md5sum(%s) len%ld\n",output, strlen(output));
	free(output);
    }
    
}
