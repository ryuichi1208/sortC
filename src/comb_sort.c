void comb_sort(double *data,int size)
{
    int i,j,k;
    double tmp;

    j=size;
    k=-1;
    while(k) {
        j=(10*j)/13;
        if(j <= 1) {
            j = 1;
            k = 0;
        }
        for(i=0;i+j<size;i++) {
            if(data[i] > data[i+j]) {
                tmp = data[i];
                data[i] = data[i+j];
                data[i+j] = tmp;
                k=-1;
            }
        }
    }

    return;
}
