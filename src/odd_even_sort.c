void odd_even_sort(double *data,int size)
{
    int i,j;
    double tmp;

    j=-1;
    while(j) {
        j=0;
        for(i=0;i+1<size;i+=2) {
            if(data[i] > data[i+1]) {
                tmp = data[i];
                data[i] = data[i+1];
                data[i+1] = tmp;
                j=-1;
            }
        }
        for(i=1;i+1<size;i+=2) {
            if(data[i] > data[i+1]) {
                tmp = data[i];
                data[i] = data[i+1];
                data[i+1] = tmp;
                j=-1;
            }
        }
    }

    return;
}
