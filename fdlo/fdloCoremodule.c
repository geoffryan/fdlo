#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "fdlo.h"

static const double rtol_default = 1.0e-12;
static const int method_default = METH_GK1021;

static char mod_docstring[] = 
    "This module computes some specific useful Fermi-Dirac integrals"
    " in a relatively lo-tech way.";

static char n_eminus_docstring[] = 
    "Density of an electron gas at given temperature and degeneracy.";

static char n_eplus_docstring[] = 
    "Density of a positron gas at given temperature and degeneracy.";

static char P_eminus_docstring[] = 
    "Pressure of an electron gas at given temperature and degeneracy.";

static char P_eplus_docstring[] = 
    "Pressure of a positron gas at given temperature and degeneracy.";

static char U_eminus_docstring[] = 
    "Internal energy of an electron gas at given temperature and degeneracy.";

static char U_eplus_docstring[] = 
    "Internal energy of a positron gas at given temperature and degeneracy.";

static char Ndot_nu_transp_docstring[] = 
    "Neutrino number flux in transparent regime given temperature and "
    "electron degeneracy";

static char Ndot_nubar_transp_docstring[] = 
    "Anti-neutrino number flux in transparent regime given temperature and "
    "electron degeneracy";

static char F_nu_transp_docstring[] = 
    "Neutrino energy flux in transparent regime given temperature and "
    "electron degeneracy";

static char F_nubar_transp_docstring[] = 
    "Anti-neutrino energy flux in transparent regime given temperature and "
    "electron degeneracy";

static char n_nu_opaque_docstring[] = 
    "Neutrino number density in opaque regime given temperature and "
    "neutrino degeneracy";

static char n_nubar_opaque_docstring[] = 
    "Anti-neutrino number density in opaque regime given temperature and "
    "neutrino degeneracy";

static char U_nu_opaque_docstring[] = 
    "Neutrino energy density in opaque regime given temperature and "
    "neutrino degeneracy";

static char U_nubar_opaque_docstring[] = 
    "Anti-neutrino energy density in opaque regime given temperature and "
    "neutrino degeneracy";


static PyObject *fdloCore_n_eminus(PyObject *self, PyObject *args,
                               PyObject *kwargs);
static PyObject *fdloCore_n_eplus(PyObject *self, PyObject *args,
                               PyObject *kwargs);
static PyObject *fdloCore_P_eminus(PyObject *self, PyObject *args,
                               PyObject *kwargs);
static PyObject *fdloCore_P_eplus(PyObject *self, PyObject *args,
                               PyObject *kwargs);
static PyObject *fdloCore_U_eminus(PyObject *self, PyObject *args,
                               PyObject *kwargs);
static PyObject *fdloCore_U_eplus(PyObject *self, PyObject *args,
                               PyObject *kwargs);
static PyObject *fdloCore_Ndot_nu_transp(PyObject *self, PyObject *args,
                                         PyObject *kwargs);
static PyObject *fdloCore_Ndot_nubar_transp(PyObject *self, PyObject *args,
                                         PyObject *kwargs);
static PyObject *fdloCore_F_nu_transp(PyObject *self, PyObject *args,
                                         PyObject *kwargs);
static PyObject *fdloCore_F_nubar_transp(PyObject *self, PyObject *args,
                                         PyObject *kwargs);
static PyObject *fdloCore_n_nu_opaque(PyObject *self, PyObject *args,
                                         PyObject *kwargs);
static PyObject *fdloCore_n_nubar_opaque(PyObject *self, PyObject *args,
                                         PyObject *kwargs);
static PyObject *fdloCore_U_nu_opaque(PyObject *self, PyObject *args,
                                         PyObject *kwargs);
static PyObject *fdloCore_U_nubar_opaque(PyObject *self, PyObject *args,
                                         PyObject *kwargs);

static PyMethodDef fdloMethods[] = {
    {"n_eminus", (PyCFunction)fdloCore_n_eminus, METH_VARARGS|METH_KEYWORDS,
        n_eminus_docstring},
    {"n_eplus", (PyCFunction)fdloCore_n_eplus, METH_VARARGS|METH_KEYWORDS,
        n_eplus_docstring},
    {"P_eminus", (PyCFunction)fdloCore_P_eminus, METH_VARARGS|METH_KEYWORDS,
        P_eminus_docstring},
    {"P_eplus", (PyCFunction)fdloCore_P_eplus, METH_VARARGS|METH_KEYWORDS,
        P_eplus_docstring},
    {"U_eminus", (PyCFunction)fdloCore_U_eminus, METH_VARARGS|METH_KEYWORDS,
        U_eminus_docstring},
    {"U_eplus", (PyCFunction)fdloCore_U_eplus, METH_VARARGS|METH_KEYWORDS,
        U_eplus_docstring},
    {"Ndot_nu_transp", (PyCFunction)fdloCore_Ndot_nu_transp, 
        METH_VARARGS|METH_KEYWORDS, Ndot_nu_transp_docstring},
    {"Ndot_nubar_transp", (PyCFunction)fdloCore_Ndot_nubar_transp, 
        METH_VARARGS|METH_KEYWORDS, Ndot_nubar_transp_docstring},
    {"F_nu_transp", (PyCFunction)fdloCore_F_nu_transp, 
        METH_VARARGS|METH_KEYWORDS, F_nu_transp_docstring},
    {"F_nubar_transp", (PyCFunction)fdloCore_F_nubar_transp, 
        METH_VARARGS|METH_KEYWORDS, F_nubar_transp_docstring},
    {"n_nu_opaque", (PyCFunction)fdloCore_n_nu_opaque, 
        METH_VARARGS|METH_KEYWORDS, n_nu_opaque_docstring},
    {"n_nubar_opaque", (PyCFunction)fdloCore_n_nubar_opaque, 
        METH_VARARGS|METH_KEYWORDS, n_nubar_opaque_docstring},
    {"U_nu_opaque", (PyCFunction)fdloCore_U_nu_opaque, 
        METH_VARARGS|METH_KEYWORDS, U_nu_opaque_docstring},
    {"U_nubar_opaque", (PyCFunction)fdloCore_U_nubar_opaque, 
        METH_VARARGS|METH_KEYWORDS, U_nubar_opaque_docstring},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef fdloModule = {
    PyModuleDef_HEAD_INIT,
    "fdloCore",
    mod_docstring,
    -1,
    fdloMethods
};

PyMODINIT_FUNC PyInit_fdloCore(void)
{
    PyObject *module = PyModule_Create(&fdloModule);
    if(module == NULL)
        return NULL;

    PyModule_AddIntConstant(module, "cadre", METH_CADRE);
    PyModule_AddIntConstant(module, "gk0409", METH_GK0409);
    PyModule_AddIntConstant(module, "gk0715", METH_GK0715);
    PyModule_AddIntConstant(module, "gk1021", METH_GK1021);

    return module;
}

int parseArgs(PyObject *args, PyObject *kwargs, double *theta, double *eta,
              double *rtol, int *method)
{
    static char *kwlist[] = {"theta", "eta_e", "rtol", "method", NULL};
    
    if(!PyArg_ParseTupleAndKeywords(args, kwargs, "dd|di", kwlist,
            theta, eta, rtol, method))
    {
        PyErr_SetString(PyExc_RuntimeError, "Could not parse arguments.");
        return 0;
    }
    if(*method < 0 || *method >= METH_UNDEF)
    {
        PyErr_SetString(PyExc_RuntimeError, "Bad Integrator Method Choice.");
        return 0;
    }

    if(*rtol <= 0.0)
    {
        PyErr_SetString(PyExc_RuntimeError,
                "Bad value for rtol. Must be > 0.");
        return 0;
    }

    if(*theta <= 0.0)
    {
        PyErr_SetString(PyExc_RuntimeError,
                "Bad value for theta. Must be > 0.");
        return 0;
    }

    return 1;
}

static PyObject *fdloCore_n_eminus(PyObject *self, PyObject *args,
                               PyObject *kwargs)
{
    double theta;
    double eta_e;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_e, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = n_eminus(theta, eta_e, rtol, &Neval, &err, method);

    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_n_eplus(PyObject *self, PyObject *args,
                               PyObject *kwargs)
{
    double theta;
    double eta_e;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_e, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = n_eplus(theta, eta_e, rtol, &Neval, &err, method);
    
    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_P_eminus(PyObject *self, PyObject *args,
                               PyObject *kwargs)
{
    double theta;
    double eta_e;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_e, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = P_eminus(theta, eta_e, rtol, &Neval, &err, method);

    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_P_eplus(PyObject *self, PyObject *args,
                               PyObject *kwargs)
{
    double theta;
    double eta_e;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_e, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = P_eplus(theta, eta_e, rtol, &Neval, &err, method);
    
    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_U_eminus(PyObject *self, PyObject *args,
                               PyObject *kwargs)
{
    double theta;
    double eta_e;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_e, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = U_eminus(theta, eta_e, rtol, &Neval, &err, method);

    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_U_eplus(PyObject *self, PyObject *args,
                               PyObject *kwargs)
{
    double theta;
    double eta_e;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_e, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = U_eplus(theta, eta_e, rtol, &Neval, &err, method);
    
    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_Ndot_nu_transp(PyObject *self, PyObject *args,
                                        PyObject *kwargs)
{
    double theta;
    double eta_e;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_e, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = Ndot_nu_transp(theta, eta_e, rtol, &Neval, &err, method);
    
    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_Ndot_nubar_transp(PyObject *self, PyObject *args,
                                        PyObject *kwargs)
{
    double theta;
    double eta_e;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_e, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = Ndot_nubar_transp(theta, eta_e, rtol, &Neval, &err, method);
    
    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_F_nu_transp(PyObject *self, PyObject *args,
                                        PyObject *kwargs)
{
    double theta;
    double eta_e;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_e, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = F_nu_transp(theta, eta_e, rtol, &Neval, &err, method);
    
    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_F_nubar_transp(PyObject *self, PyObject *args,
                                        PyObject *kwargs)
{
    double theta;
    double eta_e;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_e, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = F_nubar_transp(theta, eta_e, rtol, &Neval, &err, method);
    
    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_n_nu_opaque(PyObject *self, PyObject *args,
                                        PyObject *kwargs)
{
    double theta;
    double eta_nu;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_nu, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = n_nu_opaque(theta, eta_nu, rtol, &Neval, &err, method);
    
    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_n_nubar_opaque(PyObject *self, PyObject *args,
                                        PyObject *kwargs)
{
    double theta;
    double eta_nu;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_nu, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = n_nubar_opaque(theta, eta_nu, rtol, &Neval, &err, method);
    
    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_U_nu_opaque(PyObject *self, PyObject *args,
                                        PyObject *kwargs)
{
    double theta;
    double eta_nu;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_nu, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = U_nu_opaque(theta, eta_nu, rtol, &Neval, &err, method);
    
    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}

static PyObject *fdloCore_U_nubar_opaque(PyObject *self, PyObject *args,
                                        PyObject *kwargs)
{
    double theta;
    double eta_nu;
    double rtol = rtol_default;
    int method = method_default;

    int status = parseArgs(args, kwargs, &theta, &eta_nu, &rtol, &method);
    if(!status)
        return NULL;

    int Neval;
    double err;
    double f = U_nubar_opaque(theta, eta_nu, rtol, &Neval, &err, method);
    
    PyObject *ret = Py_BuildValue("ddi", f, err, Neval);

    return ret;
}
