/*
1. If i is variable and p points to i, which of the following expressions are aliases for i?
(a) *p (b) &p (c) *&p (d) &*p (e) *i (f) (&i) (g) *&i (h) &*i

My answer is :
(a), (g) and (d)


2. If i is an int variable and p and q are pointers to int, which of the following assignments are legal?
(a) p = i; (b) *p = &i; (c) &p = q; (d) p = &q; (e) p = *&q; (f) p = q;
(g) p = *q; (h)*p = q; (i) *p = *q;

My answer is :
(e), (f), (i)

3. The following function suppsedly computes the sum and average of the numbers in the array a, which has length n, avg, and sum point to variables
that the function should modify. Unfortunately, the function contains serveral errors; find and correct them

void avg_sum(double a[], int n, double *avg, double *sum)
{
    int i;

    sum = 0.0;
    for (i = 0; i < n; i++)
        sum += a[i];
    avg = sum / n;
}

My answer is :
void avg_sum(double a[], int n, double *avg, double *sum)
{
    int i;

    *sum = 0.0;
    for (i = 0; i < n; i++)
        *sum += a[i];
    *avg = (*sum) / n;
}

*/