void heap_sort(double *data,int size)
{
    int i,j,k;
    double tmp;

    for(i=1;i<size;i++) {
        j = i;
        while(j>0) {
            k = (j-1)/2;
            if(data[k] < data[j]) {
                tmp = data[j];
                data[j] = data[k];
                data[k] = tmp;
                j = k;
            } else {
                break;
            }
        }
    }
    for(i=size-1;i>=0;i--) {
        tmp = data[i];
        data[i] = data[0];
        data[0] = tmp;
        j = 0;
        while(1) {
            if(2*j + 1 >= i) {
                break;
            }
            k = 2*j + 1;
            if(k+1 < i && data[k] < data[k+1]) {
                k++;
            }
            if(data[k] > data[j]) {
                tmp = dta[j];
                data[j] = data[k];
                data[k] = tmp;
                j=k;
            } else {
                break;
            }
        }
    }
    return;
}
