#ifndef FDLO_H
#define FDLO_H

#define QQ 2.5309881879448617

enum {METH_CADRE, METH_GK0409, METH_GK0715, METH_GK1021, METH_UNDEF};

double fd(double E, double theta, double eta);
int errf(void *vargs);

double f_n_eminus(double t, void *vargs);
double f_n_eplus(double t, void *vargs);
double f_P_eminus(double t, void *vargs);
double f_P_eplus(double t, void *vargs);
double f_U_eminus(double t, void *vargs);
double f_U_eplus(double t, void *vargs);
double f_Ndot_nu_transp(double t, void *vargs);
double f_Ndot_nubar_transp(double t, void *vargs);
double f_F_nu_transp(double t, void *vargs);
double f_F_nubar_transp(double t, void *vargs);

double dispatch(double (*f)(double, void *), double *args, double fb,
                double rtol, int *Neval, double *err, int method);

double n_eminus(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method);
double n_eplus(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method);
double P_eminus(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method);
double P_eplus(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method);
double U_eminus(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method);
double U_eplus(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method);
double Ndot_nu_transp(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method);
double Ndot_nubar_transp(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method);
double F_nu_transp(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method);
double F_nubar_transp(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method);
double n_nu_opaque(double theta, double eta_nu, double rtol, int *Neval,
                  double *err, int method);
double n_nubar_opaque(double theta, double eta_nu, double rtol, int *Neval,
                  double *err, int method);
double U_nu_opaque(double theta, double eta_nu, double rtol, int *Neval,
                  double *err, int method);
double U_nubar_opaque(double theta, double eta_nu, double rtol, int *Neval,
                  double *err, int method);


#endif
