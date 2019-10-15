void slow_sort(double *data,int size)
{
    int i;
    double tmp;
    if(size < 2) {
        return;
    }
    i = (size-1)/2;
    slow_sort(data,i+1);
    slow_sort(data+i+1,size-i-1);
    if(data[size-1] < data[i]) {
        tmp = data[i];
        data[i] = data[size-1];
        data[size-1] = tmp;
    }
    slow_sort(data,size-1);

    return;
}
