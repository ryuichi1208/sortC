void gnome_sort(double *data,int size)
{
    int i;
    double tmp;

    i=0;
    while(i<size-1)
    {
        if(data[i] > data[i+1]) {
            tmp = data[i];
            data[i] = data[i+1];
            data[i+1] = tmp;
            if(i) {
                i--;
            }
        } else {
            i++;
        }
    }

    return;
}
