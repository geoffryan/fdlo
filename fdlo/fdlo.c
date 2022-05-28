#include <math.h>
#include <stdio.h>
#include "integrate.h"
#include "fdlo.h"

double fd(double E, double theta, double eta)
{
    double x = E/theta - eta;
    if(x > 700)
        return 0.0;
    double f = 1.0/(exp(x) + 1.0);
    return f;
}

int errf(void *vargs)
{
    return 0;
}

double f_n_eminus(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double p = t * iomt;
    double dp = iomt * iomt;
    double E = sqrt(p*p + 1);

    return fd(E, args[0], args[1]) * p*p * dp;
}

double f_n_eplus(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double p = t * iomt;
    double dp = iomt * iomt;
    double E = sqrt(p*p + 1);

    return fd(E, args[0], -args[1]) * p*p * dp;
}

double f_P_eminus(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double p = t * iomt;
    double dp = iomt * iomt;
    double E = sqrt(p*p + 1);

    return fd(E, args[0], args[1]) * p*p*p*p / E * dp;
}

double f_P_eplus(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double p = t * iomt;
    double dp = iomt * iomt;
    double E = sqrt(p*p + 1);

    return fd(E, args[0], -args[1]) * p*p*p*p / E * dp;
}

double f_U_eminus(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double p = t * iomt;
    double dp = iomt * iomt;
    double E = sqrt(p*p + 1);

    return fd(E, args[0], args[1]) * p*p * E * dp;
}

double f_U_eplus(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double p = t * iomt;
    double dp = iomt * iomt;
    double E = sqrt(p*p + 1);

    return fd(E, args[0], -args[1]) * p*p * E * dp;
}

double f_F_nu_transp(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double E = t * iomt;
    double dE = iomt * iomt;
    double EpQ = E + QQ;

    return fd(EpQ, args[0], args[1]) * EpQ*sqrt(EpQ*EpQ-1) * E*E*E * dE;
}

double f_F_nubar_transp(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double E = QQ+1.0 + t * iomt;
    double dE = iomt * iomt;
    double EmQ = E - QQ;

    return fd(EmQ, args[0], -args[1]) * EmQ*sqrt(EmQ*EmQ-1) * E*E*E * dE;
}

double f_Ndot_nu_transp(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double E = t * iomt;
    double dE = iomt * iomt;
    double EpQ = E + QQ;

    return fd(EpQ, args[0], args[1]) * EpQ*sqrt(EpQ*EpQ-1) * E*E * dE;
}

double f_Ndot_nubar_transp(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double E = QQ+1.0 + t * iomt;
    double dE = iomt * iomt;
    double EmQ = E - QQ;

    return fd(EmQ, args[0], -args[1]) * EmQ*sqrt(EmQ*EmQ-1) * E*E * dE;
}

double f_n_nu_opaque(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double E = t * iomt;
    double dE = iomt * iomt;

    return fd(E, args[0], args[1]) * E*E * dE;
}

double f_n_nubar_opaque(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double E = t * iomt;
    double dE = iomt * iomt;

    return fd(E, args[0], -args[1]) * E*E * dE;
}

double f_U_nu_opaque(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double E = t * iomt;
    double dE = iomt * iomt;

    return fd(E, args[0], args[1]) * E*E*E * dE;
}

double f_U_nubar_opaque(double t, void *vargs)
{
    double *args = (double *)vargs;

    double iomt = 1.0 / (1.0 - t);
    double E = t * iomt;
    double dE = iomt * iomt;

    return fd(E, args[0], -args[1]) * E*E*E * dE;
}

double dispatch(double (*f)(double, void *), double *args, double fb,
                double rtol, int *Neval, double *err, int method)
{

    if(method == METH_CADRE)
        return cadre_adapt(f, 0, 1, 1000, 0.0, rtol, (void *)args,
                           Neval, err, 0, errf, NULL, &fb, NULL);
    else if(method == METH_GK0409)
        return gk49_adapt(f, 0, 1, 1000, 0.0, rtol, (void *)args,
                           Neval, err, 0, errf);
    else if(method == METH_GK0715)
        return gk715_adapt(f, 0, 1, 1000, 0.0, rtol, (void *)args,
                           Neval, err, 0, errf);
    else if(method == METH_GK1021)
        return gk1021_adapt(f, 0, 1, 1000, 0.0, rtol, (void *)args,
                           Neval, err, 0, errf);
    return 0.0;
}

double n_eminus(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method)
{
    double args[2] = {theta, eta_e};
    double val = dispatch(f_n_eminus, args, 0.0, rtol, Neval, err, method);
    return val;
}

double n_eplus(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method)
{
    double args[2] = {theta, eta_e};
    return dispatch(f_n_eplus, args, 0.0, rtol, Neval, err, method);
}

double P_eminus(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method)
{
    double args[2] = {theta, eta_e};
    double val = dispatch(f_P_eminus, args, 0.0, rtol, Neval, err, method);
    return val;
}

double P_eplus(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method)
{
    double args[2] = {theta, eta_e};
    return dispatch(f_P_eplus, args, 0.0, rtol, Neval, err, method);
}

double U_eminus(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method)
{
    double args[2] = {theta, eta_e};
    double val = dispatch(f_U_eminus, args, 0.0, rtol, Neval, err, method);
    return val;
}

double U_eplus(double theta, double eta_e, double rtol, int *Neval,
                  double *err, int method)
{
    double args[2] = {theta, eta_e};
    return dispatch(f_U_eplus, args, 0.0, rtol, Neval, err, method);
}

double Ndot_nu_transp(double theta, double eta_e, double rtol, int *Neval,
                   double *err, int method)
{
    double args[2] = {theta, eta_e};
    return dispatch(f_Ndot_nu_transp, args, 0.0, rtol, Neval, err, method);
}

double Ndot_nubar_transp(double theta, double eta_e, double rtol, int *Neval,
                      double *err, int method)
{
    double args[2] = {theta, eta_e};
    return dispatch(f_Ndot_nubar_transp, args, 0.0, rtol, Neval, err, method);
}

double F_nu_transp(double theta, double eta_e, double rtol, int *Neval,
                   double *err, int method)
{
    double args[2] = {theta, eta_e};
    return dispatch(f_F_nu_transp, args, 0.0, rtol, Neval, err, method);
}

double F_nubar_transp(double theta, double eta_e, double rtol, int *Neval,
                      double *err, int method)
{
    double args[2] = {theta, eta_e};
    return dispatch(f_F_nubar_transp, args, 0.0, rtol, Neval, err, method);
}

double n_nu_opaque(double theta, double eta_nu, double rtol, int *Neval,
                   double *err, int method)
{
    double args[2] = {theta, eta_nu};
    return dispatch(f_n_nu_opaque, args, 0.0, rtol, Neval, err, method);
}

double n_nubar_opaque(double theta, double eta_nu, double rtol, int *Neval,
                      double *err, int method)
{
    double args[2] = {theta, eta_nu};
    return dispatch(f_n_nubar_opaque, args, 0.0, rtol, Neval, err, method);
}

double U_nu_opaque(double theta, double eta_nu, double rtol, int *Neval,
                   double *err, int method)
{
    double args[2] = {theta, eta_nu};
    return dispatch(f_U_nu_opaque, args, 0.0, rtol, Neval, err, method);
}

double U_nubar_opaque(double theta, double eta_nu, double rtol, int *Neval,
                      double *err, int method)
{
    double args[2] = {theta, eta_nu};
    return dispatch(f_U_nubar_opaque, args, 0.0, rtol, Neval, err, method);
}

