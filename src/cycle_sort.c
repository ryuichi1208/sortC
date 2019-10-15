void cycle_sort(double *data,int size)
{
    int i,j,k;
    double tmp;

    i = 0;
    while(i<size-1) {
        tmp = data[i];
        k=0;
        j=i+1;
        while(j<size) {
            if(tmp > data[j++]) k++;
        }
        if(k) {
            data[i] = data[i+k];
            data[i+k] = tmp;
        } else {
            i++;
        }
    }

    return;
}
