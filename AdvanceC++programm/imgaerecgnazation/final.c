#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


int width, height, total_threads;
char ** in_image;
char ** temp_image;
char ** out_image;
typedef struct{
    int x1, x2, y1, y2;
} box;
void init_box(box*b,int x, int y){
    b->x1=x;
    b->x2=x;
    b->y1=y;
    b->y2=y;
}
void expand_box(box * b, int x, int y){
    
    if(x<b->x1)b->x1=x;
    if(x>b->x2)b->x2=x;
    if(y<b->y1)b->y1=y;
    if(y>b->y2)b->y2=y;
    
}
char ** make_blank_image(){
     int n,m;
     char ** newimg = (char**)malloc(height*sizeof(char*));
     for(n=0;n<height;n++){
        newimg[n]=(char*)malloc(width/8*sizeof(char));
        for(m=0;m<width/8;m++)
            newimg[n][m]=0;
     }
    return newimg;
 }
char getpixel(int x, int y, char ** image){
    return (image[y][x/8]>>(x&7))&1;
}
void setpixel(int x, int y, char ** image){
    image[y][x/8]|=1<<(x&7);
}
void clearpixel(int x, int y, char ** image){
    image[y][x/8]&=~(1<<(x&7));
}

void write_box(box b){
    int n;
    for(n=b.x1;n<=b.x2;n++)
    {
        setpixel(n,b.y1,out_image);
        setpixel(n,b.y2,out_image);
    }
    for(n=b.y1;n<=b.y2;n++)
    {
        setpixel(b.x1,n,out_image);
        setpixel(b.x2,n,out_image);
    }
}
char readimage(char * filename, char *** image){
    FILE * fin = fopen(filename,"rb");
    char ch[100];
    char * s;
    int n;
	fscanf(fin,"%s\n%i %i\n",ch,&width,&height)  ;
	 printf("width: %i\nheight: %i\n",width,height);    
    *image = (char**)malloc(height*sizeof(char*));
    for(n=0;n<height;n++){
        (*image)[n] = (char*)malloc(width/8*sizeof(char));
        fread((*image)[n],1,width/8,fin);
    }
    
    
    fclose(fin);
    return 1;
}

void writeimage(char * filename, char ** image){
    FILE * fout = fopen(filename,"wb");
    int n;
    fprintf(fout,"P4\n%i %i\n",width,height);
    for(n=0;n<height;n++)
        fwrite(image[n],1,width/8,fout);
    fclose(fout);
}



int check_pixel(int x, int y, box * b){
    int size=0;
    int n,m;
    if(x<0 || y<0 || x>=width || y >= height)
        return 0;
    if(getpixel(x,y,in_image)&&!getpixel(x,y,temp_image)){
        setpixel(x,y,temp_image);
        expand_box(b,x,y);
        size++;
        for(n=x-3;n<=x+3;n++)
            for(m=y-3;m<=y+3;m++)
                size+=check_pixel(n,m,b);
        return size;
    }
    return 0;
}
void * parallel_func(void* v){
	int vno=*(int*)v,xth=vno/total_threads,yth=vno%total_threads,
		xmin=(xth*width)/total_threads,
		xmax=((xth+1)*width)/total_threads,
		ymin=(yth*height)/total_threads,
		ymax=((yth+1)*height)/total_threads,
		x,y,cursize;
	box b;
    for(x=xmin;x<xmax;x++)
        for(y=ymin;y<ymax;y++){
                init_box(&b,x,y);
                cursize=check_pixel(x,y,&b);
                if(cursize>100){
                    printf("Box from: (%i,%i) to: (%i,%i)\n",b.x1,b.y1,b.x2,b.y2);
                    write_box(b);
                }
            }
}
int main(int argc, char ** argv){
    
    
    int n,m,x,y,cursize;
    box b;
    char * fout;
	total_threads=atoi(argv[2]);
    // initially both input and output imaes have just the letters in black and no boxes drawn.
    readimage(argv[1],&in_image);
    readimage(argv[1],&out_image);
    // temp image is  a place to use for scratch space to store pixels that have been assigned to a letter
    temp_image = make_blank_image();
#if 0
    for(y=0;y<height;y++){
        for(x=0;x<80;x++)
            if(getpixel(x,y,in_image))
                printf("1");
            else
                printf("0");
        printf("\n");
    }
	
#endif
    fout = strcat(argv[1],".new");
    pthread_t * ptt = (pthread_t*)malloc(total_threads*total_threads*sizeof(pthread_t));
	int * threadno = (int*)malloc(total_threads*total_threads*sizeof(int));
	for(x=0;x<total_threads*total_threads;x++){
		threadno[x]=x;
		pthread_create(&ptt[x],NULL,parallel_func,&threadno[x]);
	}
	void* vp;
	for(x=0;x<total_threads*total_threads;x++)
		pthread_join(ptt[x],&vp);
    writeimage(fout,out_image);

}
