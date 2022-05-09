  GNU nano 3.2                                                                                                                                                                                                                                                                                                  sortp.c                                                                                                                                                                                                                                                                                                            


//sort.c
#include <time.h> // for CPU time
#include <sys/time.h> //for gettimeofday
#include <stdio.h>
#include <omp.h>
#define max_len 400000
#define LENGTH 40
#define number_of_threads 12
main(){
int nthreads, me;
double  max, min;
int i=1,len,j,cur,prev;
double b[max_len+1],c[max_len+1],new,cnew,time;
char name[LENGTH]="1k.txt",line[LENGTH];
FILE *fp;
clock_t cpu0,cpu1,cpu2,cpu3; // clock_t defined in <time.h> and <sys/types.h> as int
struct timeval time0, time1,time2,time3; // for wall clock in s and us
double  dtime12,dtime03; // for wall clock in s (real number)

cpu0 = clock();    // assign initial CPU time (IN CPU CLOCKS)
gettimeofday(&time0, NULL); // returns structure with time in s and us (microseconds)
//printf("Input filename\n"); scanf("%s",name);
fp=fopen(name,"r");
while(1){ //1 serves as true, i.e. condition which is always true
  if(fgets(line, LENGTH,fp)==NULL)break; // finish reading when empty line is read
  if(sscanf(line, "%lf %lf",&b[i],&c[i])==-1) break; // finish reading after error
  i++;
}
len=i-1;fclose(fp);
//printf("first number is %lf\n",c[0]);
 max = b[1];
 min = b[1];
for(int i=2; i<=len; i++)
{
if(b[i] > max)
{
max = b[i];
 }
if(b[i] < min)
{
min = b[i];
}
}
double total_length=max-min;
double subrange_length=total_length/number_of_threads;
printf("Max is  %lf  min is %lf\n",max,min);
printf("Number of items to sort: %i\n",len);
cpu1 = clock();    // assign initial CPU time (IN CPU CLOCKS)
gettimeofday(&time1, NULL); // returns structure with time in s and us (microseconds)
//ind[0]=1;
omp_set_num_threads(number_of_threads);
int  Nme=0;
#pragma omp parallel private(i,j, me, Nme,new,prev,cnew,cur)
{
Nme=1;
double b_me[len+1], c_me[len+1];
double low,high;
int ind[40000];
if(omp_get_thread_num()==0)
{
low=min;
high=min+subrange_length;
}
for(int i=1;i<number_of_threads;i++)
{
if(omp_get_thread_num()==i)
{
low=min+(subrange_length*i);
high=min+subrange_length*(i+1);
}
}
printf("thread number is %i high is %lf low is %lf\n",omp_get_thread_num(),high,low);
for(int i=1;i<=len;i++)
{
if((b[i]>low-0.0001)& (b[i]<=high+0.0001))
{

b_me[Nme]=b[i];
c_me[Nme]=c[i];
Nme++;
}
}
//printf("number is %lf\n",b_me[1]);
Nme=Nme-1;
ind[0]=1;
for(j=2;j<=Nme;j++){ // start sorting with the second item
new=b_me[j];cnew=c_me[j];cur=0;
//printf("new= %lf  cnew is %lf ",new,cnew);
for(i=1;i<j;i++){
prev=cur;cur=ind[cur];
if(new==b_me[cur]){printf("Equal numbers %lf\n",new);}
if((new<b_me[cur]) | ((new==b_me[cur])&(cnew<c_me[cur]))){ind[prev]=j;ind[j]=cur;goto loop;}
}
// new number is the largest so far
ind[cur]=j;
loop: ;
}
#pragma omp for ordered

 for (i=0; i<number_of_threads; i++)
  {
#pragma omp ordered
{
if (omp_get_thread_num() == 0) {
fp = fopen("sortedp.txt", "w");
cur = 0;
for (j=1; j<=Nme; j++)
{
cur = ind[cur];
fprintf(fp, "%lf %lf\n", b_me[cur],c_me[cur]);
}
fclose(fp);
}
 else {
fp = fopen("sortedp.txt", "a");
cur = 0;
for (j=1; j<=Nme; j++)
 {
 cur = ind[cur];
fprintf(fp, "%lf %lf\n", b_me[cur], c_me[cur]);
}
fclose(fp);
}
}
}
}
cpu3 = clock();    // assign initial CPU time (IN CPU CLOCKS)
gettimeofday(&time3, NULL); // returns structure with time in s and us (microseconds)
dtime03 = ((time3.tv_sec  - time0.tv_sec)+(time3.tv_usec - time0.tv_usec)/1e6);
printf("Elapsed wall time complete is  %f\n", dtime03);
printf("cpu time is %f\n",(float) (cpu3-cpu0)/CLOCKS_PER_SEC);
}












