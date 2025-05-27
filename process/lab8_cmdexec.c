#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#if 0
int main()
 {
    int status = system("ls -l");


    FILE *fp;
    char path[128];

    fp = popen("uname -a", "r");
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("Output: %s", path);
    }

    pclose(fp);


    return 0;

    
}


#else

int main() {


    return 0;
}
#endif 