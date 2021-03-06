#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include "camera.h"

int main(int argc, char ** argv) {
    char *dev_name = "/dev/video0";
    FILE * outf = 0;
    unsigned int image_size;
    outf = fopen("out.yuv", "wb");
    Camera *camera;
    int width=720;
    int height=480;
    unsigned char image[width*height*2];

    clock_t starttime, endtime;
    double totaltime;

    camera=new Camera(dev_name,width,height);
    if(!camera->OpenDevice()){
        return -1;
    }
    image_size=camera->getImageSize();
    starttime = clock();
    int frames=50;
    unsigned int writesize=0;
    for(int i=0;i<frames;i++){
        if(!camera->GetBuffer(image)){
            break;
        }
        writesize=fwrite(image,1,image_size,outf);
        //fflush(outf);
        printf("frame:%d,writesize:%d\n",i,writesize);
    }
    endtime = clock();
    totaltime = (double)( (endtime - starttime)/(double)CLOCKS_PER_SEC );
    printf("time :%f, rate :%f\n",totaltime,frames/totaltime);
    camera->CloseDevice();
    fclose(outf);
    return 0;
}
