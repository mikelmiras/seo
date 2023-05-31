void funtzioa(double *t, double *k, double *l)
{
    (*t) += (*l)/(*k);
    (*k) += 2.0;
    (*l) *= -1.0;
}
