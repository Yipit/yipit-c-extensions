#include <Python.h>
#include <string.h>

static PyObject *YipitError;

static PyObject *
yipit_run(PyObject *self, PyObject *args)
{
  const char *command;
  int sts;
  char err[128];

  if (!PyArg_ParseTuple(args, "s", &command))
    return NULL;
  sts = system(command);
  if (sts != 0) {
    sprintf(err, "Run command failed with status %d", sts);
    PyErr_SetString(YipitError, err);
    return NULL;
  }
  Py_RETURN_NONE;
}

static PyMethodDef YipitMethods[] = {
  {"run",  yipit_run, METH_VARARGS, "Execute a shell command."},
  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
inityipit(void)
{
  PyObject *m;

  m = Py_InitModule("yipit", YipitMethods);
  if (m == NULL)
    return;

  YipitError = PyErr_NewException("yipit.YipitOopsException", NULL, NULL);
  Py_INCREF(YipitError);
  PyModule_AddObject(m, "YipitOopsException", YipitError);
}
