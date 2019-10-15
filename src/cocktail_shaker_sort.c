void cocktail_shaker_sort(double *data,int size)
{
    int i,j,k,l;
    double tmp;

    i=0;
    j=size-1;
    l=-1;
    while(l) {
        l=0;
        for(k=i;k<j;k++) {
            if(data[k] > data[k+1]) {
                tmp = data[k];
                data[k] = data[k+1];
                data[k+1] = tmp;
                l=-1;
            }
        }
        j--;
        if(!l) {
            break;
        }
        l=0;
        for(k=j;k>i;k--) {
            if(data[k] < data[k-1]) {
                tmp = data[k];
                data[k] = data[k-1];
                data[k-1] = tmp;
                l=-1;
            }
        }
        i++;
    }
    return;
}
