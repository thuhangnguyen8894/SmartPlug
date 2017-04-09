
#include <Python.h>
#include <stddef.h>

/* this block of #ifs should be kept exactly identical between
   c/_cffi_backend.c, cffi/vengine_cpy.py, cffi/vengine_gen.py */
#if defined(_MSC_VER)
# include <malloc.h>   /* for alloca() */
# if _MSC_VER < 1600   /* MSVC < 2010 */
   typedef __int8 int8_t;
   typedef __int16 int16_t;
   typedef __int32 int32_t;
   typedef __int64 int64_t;
   typedef unsigned __int8 uint8_t;
   typedef unsigned __int16 uint16_t;
   typedef unsigned __int32 uint32_t;
   typedef unsigned __int64 uint64_t;
   typedef __int8 int_least8_t;
   typedef __int16 int_least16_t;
   typedef __int32 int_least32_t;
   typedef __int64 int_least64_t;
   typedef unsigned __int8 uint_least8_t;
   typedef unsigned __int16 uint_least16_t;
   typedef unsigned __int32 uint_least32_t;
   typedef unsigned __int64 uint_least64_t;
   typedef __int8 int_fast8_t;
   typedef __int16 int_fast16_t;
   typedef __int32 int_fast32_t;
   typedef __int64 int_fast64_t;
   typedef unsigned __int8 uint_fast8_t;
   typedef unsigned __int16 uint_fast16_t;
   typedef unsigned __int32 uint_fast32_t;
   typedef unsigned __int64 uint_fast64_t;
   typedef __int64 intmax_t;
   typedef unsigned __int64 uintmax_t;
# else
#  include <stdint.h>
# endif
# if _MSC_VER < 1800   /* MSVC < 2013 */
   typedef unsigned char _Bool;
# endif
#else
# include <stdint.h>
# if (defined (__SVR4) && defined (__sun)) || defined(_AIX)
#  include <alloca.h>
# endif
#endif

#if PY_MAJOR_VERSION < 3
# undef PyCapsule_CheckExact
# undef PyCapsule_GetPointer
# define PyCapsule_CheckExact(capsule) (PyCObject_Check(capsule))
# define PyCapsule_GetPointer(capsule, name) \
    (PyCObject_AsVoidPtr(capsule))
#endif

#if PY_MAJOR_VERSION >= 3
# define PyInt_FromLong PyLong_FromLong
#endif

#define _cffi_from_c_double PyFloat_FromDouble
#define _cffi_from_c_float PyFloat_FromDouble
#define _cffi_from_c_long PyInt_FromLong
#define _cffi_from_c_ulong PyLong_FromUnsignedLong
#define _cffi_from_c_longlong PyLong_FromLongLong
#define _cffi_from_c_ulonglong PyLong_FromUnsignedLongLong

#define _cffi_to_c_double PyFloat_AsDouble
#define _cffi_to_c_float PyFloat_AsDouble

#define _cffi_from_c_int_const(x)                                        \
    (((x) > 0) ?                                                         \
        ((unsigned long long)(x) <= (unsigned long long)LONG_MAX) ?      \
            PyInt_FromLong((long)(x)) :                                  \
            PyLong_FromUnsignedLongLong((unsigned long long)(x)) :       \
        ((long long)(x) >= (long long)LONG_MIN) ?                        \
            PyInt_FromLong((long)(x)) :                                  \
            PyLong_FromLongLong((long long)(x)))

#define _cffi_from_c_int(x, type)                                        \
    (((type)-1) > 0 ? /* unsigned */                                     \
        (sizeof(type) < sizeof(long) ?                                   \
            PyInt_FromLong((long)x) :                                    \
         sizeof(type) == sizeof(long) ?                                  \
            PyLong_FromUnsignedLong((unsigned long)x) :                  \
            PyLong_FromUnsignedLongLong((unsigned long long)x)) :        \
        (sizeof(type) <= sizeof(long) ?                                  \
            PyInt_FromLong((long)x) :                                    \
            PyLong_FromLongLong((long long)x)))

#define _cffi_to_c_int(o, type)                                          \
    ((type)(                                                             \
     sizeof(type) == 1 ? (((type)-1) > 0 ? (type)_cffi_to_c_u8(o)        \
                                         : (type)_cffi_to_c_i8(o)) :     \
     sizeof(type) == 2 ? (((type)-1) > 0 ? (type)_cffi_to_c_u16(o)       \
                                         : (type)_cffi_to_c_i16(o)) :    \
     sizeof(type) == 4 ? (((type)-1) > 0 ? (type)_cffi_to_c_u32(o)       \
                                         : (type)_cffi_to_c_i32(o)) :    \
     sizeof(type) == 8 ? (((type)-1) > 0 ? (type)_cffi_to_c_u64(o)       \
                                         : (type)_cffi_to_c_i64(o)) :    \
     (Py_FatalError("unsupported size for type " #type), (type)0)))

#define _cffi_to_c_i8                                                    \
                 ((int(*)(PyObject *))_cffi_exports[1])
#define _cffi_to_c_u8                                                    \
                 ((int(*)(PyObject *))_cffi_exports[2])
#define _cffi_to_c_i16                                                   \
                 ((int(*)(PyObject *))_cffi_exports[3])
#define _cffi_to_c_u16                                                   \
                 ((int(*)(PyObject *))_cffi_exports[4])
#define _cffi_to_c_i32                                                   \
                 ((int(*)(PyObject *))_cffi_exports[5])
#define _cffi_to_c_u32                                                   \
                 ((unsigned int(*)(PyObject *))_cffi_exports[6])
#define _cffi_to_c_i64                                                   \
                 ((long long(*)(PyObject *))_cffi_exports[7])
#define _cffi_to_c_u64                                                   \
                 ((unsigned long long(*)(PyObject *))_cffi_exports[8])
#define _cffi_to_c_char                                                  \
                 ((int(*)(PyObject *))_cffi_exports[9])
#define _cffi_from_c_pointer                                             \
    ((PyObject *(*)(char *, CTypeDescrObject *))_cffi_exports[10])
#define _cffi_to_c_pointer                                               \
    ((char *(*)(PyObject *, CTypeDescrObject *))_cffi_exports[11])
#define _cffi_get_struct_layout                                          \
    ((PyObject *(*)(Py_ssize_t[]))_cffi_exports[12])
#define _cffi_restore_errno                                              \
    ((void(*)(void))_cffi_exports[13])
#define _cffi_save_errno                                                 \
    ((void(*)(void))_cffi_exports[14])
#define _cffi_from_c_char                                                \
    ((PyObject *(*)(char))_cffi_exports[15])
#define _cffi_from_c_deref                                               \
    ((PyObject *(*)(char *, CTypeDescrObject *))_cffi_exports[16])
#define _cffi_to_c                                                       \
    ((int(*)(char *, CTypeDescrObject *, PyObject *))_cffi_exports[17])
#define _cffi_from_c_struct                                              \
    ((PyObject *(*)(char *, CTypeDescrObject *))_cffi_exports[18])
#define _cffi_to_c_wchar_t                                               \
    ((wchar_t(*)(PyObject *))_cffi_exports[19])
#define _cffi_from_c_wchar_t                                             \
    ((PyObject *(*)(wchar_t))_cffi_exports[20])
#define _cffi_to_c_long_double                                           \
    ((long double(*)(PyObject *))_cffi_exports[21])
#define _cffi_to_c__Bool                                                 \
    ((_Bool(*)(PyObject *))_cffi_exports[22])
#define _cffi_prepare_pointer_call_argument                              \
    ((Py_ssize_t(*)(CTypeDescrObject *, PyObject *, char **))_cffi_exports[23])
#define _cffi_convert_array_from_object                                  \
    ((int(*)(char *, CTypeDescrObject *, PyObject *))_cffi_exports[24])
#define _CFFI_NUM_EXPORTS 25

typedef struct _ctypedescr CTypeDescrObject;

static void *_cffi_exports[_CFFI_NUM_EXPORTS];
static PyObject *_cffi_types, *_cffi_VerificationError;

static int _cffi_setup_custom(PyObject *lib);   /* forward */

static PyObject *_cffi_setup(PyObject *self, PyObject *args)
{
    PyObject *library;
    int was_alive = (_cffi_types != NULL);
    (void)self; /* unused */
    if (!PyArg_ParseTuple(args, "OOO", &_cffi_types, &_cffi_VerificationError,
                                       &library))
        return NULL;
    Py_INCREF(_cffi_types);
    Py_INCREF(_cffi_VerificationError);
    if (_cffi_setup_custom(library) < 0)
        return NULL;
    return PyBool_FromLong(was_alive);
}

static int _cffi_init(void)
{
    PyObject *module, *c_api_object = NULL;

    module = PyImport_ImportModule("_cffi_backend");
    if (module == NULL)
        goto failure;

    c_api_object = PyObject_GetAttrString(module, "_C_API");
    if (c_api_object == NULL)
        goto failure;
    if (!PyCapsule_CheckExact(c_api_object)) {
        PyErr_SetNone(PyExc_ImportError);
        goto failure;
    }
    memcpy(_cffi_exports, PyCapsule_GetPointer(c_api_object, "cffi"),
           _CFFI_NUM_EXPORTS * sizeof(void *));

    Py_DECREF(module);
    Py_DECREF(c_api_object);
    return 0;

  failure:
    Py_XDECREF(module);
    Py_XDECREF(c_api_object);
    return -1;
}

#define _cffi_type(num) ((CTypeDescrObject *)PyList_GET_ITEM(_cffi_types, num))

/**********/




                #include "JsonParserForC.h"

                

static void _cffi_check__Device_Timer(Device_Timer *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char(*tmp)[10] = &p->idTimer; (void)tmp; }
  { char(*tmp)[10] = &p->idSmartDevice; (void)tmp; }
  { char(*tmp)[10] = &p->stateElectric; (void)tmp; }
  { char(*tmp)[10] = &p->stateRelay; (void)tmp; }
}
static PyObject *
_cffi_layout__Device_Timer(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; Device_Timer y; };
  static Py_ssize_t nums[] = {
    sizeof(Device_Timer),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(Device_Timer, idTimer),
    sizeof(((Device_Timer *)0)->idTimer),
    offsetof(Device_Timer, idSmartDevice),
    sizeof(((Device_Timer *)0)->idSmartDevice),
    offsetof(Device_Timer, stateElectric),
    sizeof(((Device_Timer *)0)->stateElectric),
    offsetof(Device_Timer, stateRelay),
    sizeof(((Device_Timer *)0)->stateRelay),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check__Device_Timer(0);
}

static void _cffi_check__Room(Room *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char(*tmp)[10] = &p->idRoom; (void)tmp; }
  { char(*tmp)[20] = &p->nameRoom; (void)tmp; }
}
static PyObject *
_cffi_layout__Room(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; Room y; };
  static Py_ssize_t nums[] = {
    sizeof(Room),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(Room, idRoom),
    sizeof(((Room *)0)->idRoom),
    offsetof(Room, nameRoom),
    sizeof(((Room *)0)->nameRoom),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check__Room(0);
}

static void _cffi_check__Sender(Sender *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char(*tmp)[20] = &p->ip; (void)tmp; }
  (void)((p->port) << 1);
}
static PyObject *
_cffi_layout__Sender(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; Sender y; };
  static Py_ssize_t nums[] = {
    sizeof(Sender),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(Sender, ip),
    sizeof(((Sender *)0)->ip),
    offsetof(Sender, port),
    sizeof(((Sender *)0)->port),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check__Sender(0);
}

static void _cffi_check__SmartDevice(SmartDevice *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char(*tmp)[10] = &p->idSmartDevice; (void)tmp; }
  { char(*tmp)[10] = &p->idRoom; (void)tmp; }
  { char(*tmp)[20] = &p->nameSmartDevice; (void)tmp; }
  { char(*tmp)[20] = &p->ip_port; (void)tmp; }
}
static PyObject *
_cffi_layout__SmartDevice(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; SmartDevice y; };
  static Py_ssize_t nums[] = {
    sizeof(SmartDevice),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(SmartDevice, idSmartDevice),
    sizeof(((SmartDevice *)0)->idSmartDevice),
    offsetof(SmartDevice, idRoom),
    sizeof(((SmartDevice *)0)->idRoom),
    offsetof(SmartDevice, nameSmartDevice),
    sizeof(((SmartDevice *)0)->nameSmartDevice),
    offsetof(SmartDevice, ip_port),
    sizeof(((SmartDevice *)0)->ip_port),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check__SmartDevice(0);
}

static void _cffi_check__SmartDeviceInfo(SmartDeviceInfo *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { SmartDevice *tmp = &p->device; (void)tmp; }
  { Device_Timer *tmp = &p->device_timer; (void)tmp; }
  { Sender *tmp = &p->sender; (void)tmp; }
  { Timer *tmp = &p->timer; (void)tmp; }
}
static PyObject *
_cffi_layout__SmartDeviceInfo(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; SmartDeviceInfo y; };
  static Py_ssize_t nums[] = {
    sizeof(SmartDeviceInfo),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(SmartDeviceInfo, device),
    sizeof(((SmartDeviceInfo *)0)->device),
    offsetof(SmartDeviceInfo, device_timer),
    sizeof(((SmartDeviceInfo *)0)->device_timer),
    offsetof(SmartDeviceInfo, sender),
    sizeof(((SmartDeviceInfo *)0)->sender),
    offsetof(SmartDeviceInfo, timer),
    sizeof(((SmartDeviceInfo *)0)->timer),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check__SmartDeviceInfo(0);
}

static void _cffi_check__Timer(Timer *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char(*tmp)[10] = &p->idTimer; (void)tmp; }
  (void)((p->secSD) << 1);
  (void)((p->minSD) << 1);
  (void)((p->hourSD) << 1);
  (void)((p->daySD) << 1);
  (void)((p->monthSD) << 1);
  (void)((p->yearSD) << 1);
}
static PyObject *
_cffi_layout__Timer(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; Timer y; };
  static Py_ssize_t nums[] = {
    sizeof(Timer),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(Timer, idTimer),
    sizeof(((Timer *)0)->idTimer),
    offsetof(Timer, secSD),
    sizeof(((Timer *)0)->secSD),
    offsetof(Timer, minSD),
    sizeof(((Timer *)0)->minSD),
    offsetof(Timer, hourSD),
    sizeof(((Timer *)0)->hourSD),
    offsetof(Timer, daySD),
    sizeof(((Timer *)0)->daySD),
    offsetof(Timer, monthSD),
    sizeof(((Timer *)0)->monthSD),
    offsetof(Timer, yearSD),
    sizeof(((Timer *)0)->yearSD),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check__Timer(0);
}

static void _cffi_check__User(User *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char(*tmp)[10] = &p->idUser; (void)tmp; }
  { char(*tmp)[20] = &p->nameUser; (void)tmp; }
  { char(*tmp)[20] = &p->password; (void)tmp; }
  { char(*tmp)[10] = &p->stateUser; (void)tmp; }
  { char(*tmp)[10] = &p->idUserStyle; (void)tmp; }
}
static PyObject *
_cffi_layout__User(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; User y; };
  static Py_ssize_t nums[] = {
    sizeof(User),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(User, idUser),
    sizeof(((User *)0)->idUser),
    offsetof(User, nameUser),
    sizeof(((User *)0)->nameUser),
    offsetof(User, password),
    sizeof(((User *)0)->password),
    offsetof(User, stateUser),
    sizeof(((User *)0)->stateUser),
    offsetof(User, idUserStyle),
    sizeof(((User *)0)->idUserStyle),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check__User(0);
}

static void _cffi_check__UserGuide(UserGuide *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char(*tmp)[10] = &p->idUserGuide; (void)tmp; }
  { char(*tmp)[20] = &p->nameUserGuide; (void)tmp; }
}
static PyObject *
_cffi_layout__UserGuide(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; UserGuide y; };
  static Py_ssize_t nums[] = {
    sizeof(UserGuide),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(UserGuide, idUserGuide),
    sizeof(((UserGuide *)0)->idUserGuide),
    offsetof(UserGuide, nameUserGuide),
    sizeof(((UserGuide *)0)->nameUserGuide),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check__UserGuide(0);
}

static void _cffi_check__UserStyle(UserStyle *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char(*tmp)[10] = &p->idUserStyle; (void)tmp; }
  { char(*tmp)[20] = &p->nameUserStyle; (void)tmp; }
}
static PyObject *
_cffi_layout__UserStyle(PyObject *self, PyObject *noarg)
{
  struct _cffi_aligncheck { char x; UserStyle y; };
  static Py_ssize_t nums[] = {
    sizeof(UserStyle),
    offsetof(struct _cffi_aligncheck, y),
    offsetof(UserStyle, idUserStyle),
    sizeof(((UserStyle *)0)->idUserStyle),
    offsetof(UserStyle, nameUserStyle),
    sizeof(((UserStyle *)0)->nameUserStyle),
    -1
  };
  (void)self; /* unused */
  (void)noarg; /* unused */
  return _cffi_get_struct_layout(nums);
  /* the next line is not executed, but compiled */
  _cffi_check__UserStyle(0);
}

static PyObject *
_cffi_f_parseDataSmartDeviceJsonForC(PyObject *self, PyObject *args)
{
  char const * x0;
  SmartDeviceInfo * x1;
  Py_ssize_t datasize;
  _Bool result;
  PyObject *arg0;
  PyObject *arg1;

  if (!PyArg_ParseTuple(args, "OO:parseDataSmartDeviceJsonForC", &arg0, &arg1))
    return NULL;

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(0), arg0, (char **)&x0);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x0 = alloca((size_t)datasize);
    memset((void *)x0, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x0, _cffi_type(0), arg0) < 0)
      return NULL;
  }

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(1), arg1, (char **)&x1);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x1 = alloca((size_t)datasize);
    memset((void *)x1, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x1, _cffi_type(1), arg1) < 0)
      return NULL;
  }

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { result = parseDataSmartDeviceJsonForC(x0, x1); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  return _cffi_from_c_int(result, _Bool);
}

static int _cffi_setup_custom(PyObject *lib)
{
  return ((void)lib,0);
}

static PyMethodDef _cffi_methods[] = {
  {"_cffi_layout__Device_Timer", _cffi_layout__Device_Timer, METH_NOARGS, NULL},
  {"_cffi_layout__Room", _cffi_layout__Room, METH_NOARGS, NULL},
  {"_cffi_layout__Sender", _cffi_layout__Sender, METH_NOARGS, NULL},
  {"_cffi_layout__SmartDevice", _cffi_layout__SmartDevice, METH_NOARGS, NULL},
  {"_cffi_layout__SmartDeviceInfo", _cffi_layout__SmartDeviceInfo, METH_NOARGS, NULL},
  {"_cffi_layout__Timer", _cffi_layout__Timer, METH_NOARGS, NULL},
  {"_cffi_layout__User", _cffi_layout__User, METH_NOARGS, NULL},
  {"_cffi_layout__UserGuide", _cffi_layout__UserGuide, METH_NOARGS, NULL},
  {"_cffi_layout__UserStyle", _cffi_layout__UserStyle, METH_NOARGS, NULL},
  {"parseDataSmartDeviceJsonForC", _cffi_f_parseDataSmartDeviceJsonForC, METH_VARARGS, NULL},
  {"_cffi_setup", _cffi_setup, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}    /* Sentinel */
};

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef _cffi_module_def = {
  PyModuleDef_HEAD_INIT,
  "__cffi_jsonParser",
  NULL,
  -1,
  _cffi_methods,
  NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit___cffi_jsonParser(void)
{
  PyObject *lib;
  lib = PyModule_Create(&_cffi_module_def);
  if (lib == NULL)
    return NULL;
  if (((void)lib,0) < 0 || _cffi_init() < 0) {
    Py_DECREF(lib);
    return NULL;
  }
  return lib;
}

#else

PyMODINIT_FUNC
init__cffi_jsonParser(void)
{
  PyObject *lib;
  lib = Py_InitModule("__cffi_jsonParser", _cffi_methods);
  if (lib == NULL)
    return;
  if (((void)lib,0) < 0 || _cffi_init() < 0)
    return;
  return;
}

#endif
