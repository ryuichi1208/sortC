void insertion_sort(double *data,int size)
{
    int i,j;
    double tmp;
    for(i=1;i<size;i++) {
        tmp=data[i];
        for(j=i;j>0 && data[j-1]>tmp;j--) 
            data[j]=data[j-1];
        data[j] = tmp;
    }
}
