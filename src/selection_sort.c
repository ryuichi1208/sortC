void selection_sort(double *data,int size)
{
    int i,j,k;
    double tmp;
    for(i=0;i<size-1;i++) {
        tmp = data[i];
        k=i;
        for(j=i+1;j<size;j++) {
            if(tmp > data[j]) {
                tmp = data[j];
                k=j;
            }
        }
        if(k != i) {
            data[k] = data[i];
            data[i] = tmp;
        }
    }
    return;
}
