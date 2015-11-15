#include <Python.h>

int c_setup();
int c_finish();


int c_run(const char * restrict cmd);
// int c_load_module(const char *name);

int c_get_int(const char * restrict obj, const char * restrict name, long int * restrict value);
int c_get_double(const char * restrict obj, const char * restrict name, double * restrict value);
int c_get_str(const char * restrict obj, const char * restrict name, char ** restrict value);

int c_set_int(const char * restrict obj, const char * restrict name, const int val);
int c_set_double(const char * restrict obj, const char * restrict name, const double val);
int c_set_str(const char * restrict obj, const char * restrict name, const char* restrict  val);

int c_set_double_array_1d(const char * restrict objname, const char * restrict name, const int len, double* restrict  val);

//Private functions

int _print_dict(PyObject *dict);
PyObject* _getVar(const char * restrict obj, const char * restrict name);
int _setVar(const char * restrict obj, const char * restrict name, PyObject *val);
void _print_object(PyObject *obj, const char* restrict  name);