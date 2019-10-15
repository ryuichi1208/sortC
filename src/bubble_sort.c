int bubble_sort(double *data,int size)
{
    int i,j,k;
    double tmp;

    i = size - 1;
    j = -1;
    while(i && j) {
        j = 0;
        for(k=0;k<i;k++) {
            if(data[k] > data[k+1]) {
                tmp = data[k+1];
                data[k+1] = data[k];
                data[k] = tmp;
                j = -1;
            }
        }
        i--;
    }

    return 0;
}
