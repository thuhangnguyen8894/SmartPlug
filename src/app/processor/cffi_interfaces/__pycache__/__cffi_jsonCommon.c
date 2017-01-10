
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



                #include "DataDef.h"
                #include "JsonCommonForC.h"
                

static int _cffi_e__MESSAGE_TYPE(PyObject *lib)
{
  if ((MESSAGE_TYPE_DEFAULT) > 0 || (long)(MESSAGE_TYPE_DEFAULT) != -1L) {
    char buf[64];
    if ((MESSAGE_TYPE_DEFAULT) <= 0)
        snprintf(buf, 63, "%ld", (long)(MESSAGE_TYPE_DEFAULT));
    else
        snprintf(buf, 63, "%lu", (unsigned long)(MESSAGE_TYPE_DEFAULT));
    PyErr_Format(_cffi_VerificationError,
                 "%s%s has the real value %s, not %s",
                 "enum MESSAGE_TYPE: ", "MESSAGE_TYPE_DEFAULT", buf, "-1");
    return -1;
  }
  if ((MESSAGE_TYPE_SMART_PLUG_STATUS) > 0 || (long)(MESSAGE_TYPE_SMART_PLUG_STATUS) != 0L) {
    char buf[64];
    if ((MESSAGE_TYPE_SMART_PLUG_STATUS) <= 0)
        snprintf(buf, 63, "%ld", (long)(MESSAGE_TYPE_SMART_PLUG_STATUS));
    else
        snprintf(buf, 63, "%lu", (unsigned long)(MESSAGE_TYPE_SMART_PLUG_STATUS));
    PyErr_Format(_cffi_VerificationError,
                 "%s%s has the real value %s, not %s",
                 "enum MESSAGE_TYPE: ", "MESSAGE_TYPE_SMART_PLUG_STATUS", buf, "0");
    return -1;
  }
  if ((MESSAGE_TYPE_CONTROL_SMART_PLUG) <= 0 || (unsigned long)(MESSAGE_TYPE_CONTROL_SMART_PLUG) != 1UL) {
    char buf[64];
    if ((MESSAGE_TYPE_CONTROL_SMART_PLUG) <= 0)
        snprintf(buf, 63, "%ld", (long)(MESSAGE_TYPE_CONTROL_SMART_PLUG));
    else
        snprintf(buf, 63, "%lu", (unsigned long)(MESSAGE_TYPE_CONTROL_SMART_PLUG));
    PyErr_Format(_cffi_VerificationError,
                 "%s%s has the real value %s, not %s",
                 "enum MESSAGE_TYPE: ", "MESSAGE_TYPE_CONTROL_SMART_PLUG", buf, "1");
    return -1;
  }
  return ((void)lib,0);
}

static PyObject *
_cffi_f_convertArduinoMsgToInt16ForC(PyObject *self, PyObject *args)
{
  char const * x0;
  uint16_t * x1;
  Py_ssize_t datasize;
  _Bool result;
  PyObject *arg0;
  PyObject *arg1;

  if (!PyArg_ParseTuple(args, "OO:convertArduinoMsgToInt16ForC", &arg0, &arg1))
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
  { result = convertArduinoMsgToInt16ForC(x0, x1); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  return _cffi_from_c_int(result, _Bool);
}

static PyObject *
_cffi_f_convertMessageTypeToStrForC(PyObject *self, PyObject *arg0)
{
  MESSAGE_TYPE const * x0;
  Py_ssize_t datasize;
  char * result;

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg0, (char **)&x0);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x0 = alloca((size_t)datasize);
    memset((void *)x0, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x0, _cffi_type(2), arg0) < 0)
      return NULL;
  }

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { result = convertMessageTypeToStrForC(x0); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  return _cffi_from_c_pointer((char *)result, _cffi_type(3));
}

static PyObject *
_cffi_f_getJSONMessageTypeForC(PyObject *self, PyObject *args)
{
  char const * x0;
  MESSAGE_TYPE * x1;
  Py_ssize_t datasize;
  PyObject *arg0;
  PyObject *arg1;

  if (!PyArg_ParseTuple(args, "OO:getJSONMessageTypeForC", &arg0, &arg1))
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
      _cffi_type(4), arg1, (char **)&x1);
  if (datasize != 0) {
    if (datasize < 0)
      return NULL;
    x1 = alloca((size_t)datasize);
    memset((void *)x1, 0, (size_t)datasize);
    if (_cffi_convert_array_from_object((char *)x1, _cffi_type(4), arg1) < 0)
      return NULL;
  }

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { getJSONMessageTypeForC(x0, x1); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *
_cffi_f_isSensorMessageForC(PyObject *self, PyObject *arg0)
{
  char const * x0;
  Py_ssize_t datasize;
  _Bool result;

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

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { result = isSensorMessageForC(x0); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  return _cffi_from_c_int(result, _Bool);
}

static int _cffi_const_ATTR_JSON_DATA(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(ATTR_JSON_DATA);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "ATTR_JSON_DATA", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_e__MESSAGE_TYPE(lib);
}

static int _cffi_const_ATTR_JSON_IP(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(ATTR_JSON_IP);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "ATTR_JSON_IP", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_ATTR_JSON_DATA(lib);
}

static int _cffi_const_ATTR_JSON_MESSAGE_TYPE(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(ATTR_JSON_MESSAGE_TYPE);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "ATTR_JSON_MESSAGE_TYPE", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_ATTR_JSON_IP(lib);
}

static int _cffi_const_ATTR_JSON_MOMENT(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(ATTR_JSON_MOMENT);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "ATTR_JSON_MOMENT", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_ATTR_JSON_MESSAGE_TYPE(lib);
}

static int _cffi_const_ATTR_JSON_PORT(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(ATTR_JSON_PORT);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "ATTR_JSON_PORT", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_ATTR_JSON_MOMENT(lib);
}

static int _cffi_const_ATTR_JSON_SENDER(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(ATTR_JSON_SENDER);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "ATTR_JSON_SENDER", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_ATTR_JSON_PORT(lib);
}

static int _cffi_const_ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_OFF(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_OFF);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_OFF", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_ATTR_JSON_SENDER(lib);
}

static int _cffi_const_ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_ON(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_ON);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_ON", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_OFF(lib);
}

static int _cffi_const_ATTR_JSON_SMART_PLUG_STATUS(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(ATTR_JSON_SMART_PLUG_STATUS);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "ATTR_JSON_SMART_PLUG_STATUS", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_ON(lib);
}

static int _cffi_const_CONTROL_SMART_PLUG_TOPIC(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(CONTROL_SMART_PLUG_TOPIC);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "CONTROL_SMART_PLUG_TOPIC", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_ATTR_JSON_SMART_PLUG_STATUS(lib);
}

static int _cffi_const_IP_PORT_TOKEN_SIZE(PyObject *lib)
{
  PyObject *o;
  int res;
  if ((IP_PORT_TOKEN_SIZE) <= 0 || (unsigned long)(IP_PORT_TOKEN_SIZE) != 2UL) {
    char buf[64];
    if ((IP_PORT_TOKEN_SIZE) <= 0)
        snprintf(buf, 63, "%ld", (long)(IP_PORT_TOKEN_SIZE));
    else
        snprintf(buf, 63, "%lu", (unsigned long)(IP_PORT_TOKEN_SIZE));
    PyErr_Format(_cffi_VerificationError,
                 "%s%s has the real value %s, not %s",
                 "", "IP_PORT_TOKEN_SIZE", buf, "2");
    return -1;
  }
  o = _cffi_from_c_int_const(IP_PORT_TOKEN_SIZE);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "IP_PORT_TOKEN_SIZE", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_CONTROL_SMART_PLUG_TOPIC(lib);
}

static int _cffi_const_LIGHT_INTENSITY_TOPIC(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(LIGHT_INTENSITY_TOPIC);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "LIGHT_INTENSITY_TOPIC", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_IP_PORT_TOKEN_SIZE(lib);
}

static int _cffi_const_MAX_SENSOR_MESSAGE_LENGTH(PyObject *lib)
{
  PyObject *o;
  int res;
  if ((MAX_SENSOR_MESSAGE_LENGTH) <= 0 || (unsigned long)(MAX_SENSOR_MESSAGE_LENGTH) != 5UL) {
    char buf[64];
    if ((MAX_SENSOR_MESSAGE_LENGTH) <= 0)
        snprintf(buf, 63, "%ld", (long)(MAX_SENSOR_MESSAGE_LENGTH));
    else
        snprintf(buf, 63, "%lu", (unsigned long)(MAX_SENSOR_MESSAGE_LENGTH));
    PyErr_Format(_cffi_VerificationError,
                 "%s%s has the real value %s, not %s",
                 "", "MAX_SENSOR_MESSAGE_LENGTH", buf, "5");
    return -1;
  }
  o = _cffi_from_c_int_const(MAX_SENSOR_MESSAGE_LENGTH);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "MAX_SENSOR_MESSAGE_LENGTH", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_LIGHT_INTENSITY_TOPIC(lib);
}

static int _cffi_const_MESSAGE_TYPE_CONTROL_SMART_PLUG_STR(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(MESSAGE_TYPE_CONTROL_SMART_PLUG_STR);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "MESSAGE_TYPE_CONTROL_SMART_PLUG_STR", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_MAX_SENSOR_MESSAGE_LENGTH(lib);
}

static int _cffi_const_MESSAGE_TYPE_SMART_PLUG_STATUS_STR(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(MESSAGE_TYPE_SMART_PLUG_STATUS_STR);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "MESSAGE_TYPE_SMART_PLUG_STATUS_STR", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_MESSAGE_TYPE_CONTROL_SMART_PLUG_STR(lib);
}

static int _cffi_const_SMART_PLUG_MESSAGE_TYPE(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(SMART_PLUG_MESSAGE_TYPE);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "SMART_PLUG_MESSAGE_TYPE", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_MESSAGE_TYPE_SMART_PLUG_STATUS_STR(lib);
}

static int _cffi_const_SMART_PLUG_MESSAGE_VALUE_OFF(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(SMART_PLUG_MESSAGE_VALUE_OFF);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "SMART_PLUG_MESSAGE_VALUE_OFF", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_SMART_PLUG_MESSAGE_TYPE(lib);
}

static int _cffi_const_SMART_PLUG_MESSAGE_VALUE_ON(PyObject *lib)
{
  PyObject *o;
  int res;
  o = _cffi_from_c_int_const(SMART_PLUG_MESSAGE_VALUE_ON);
  if (o == NULL)
    return -1;
  res = PyObject_SetAttrString(lib, "SMART_PLUG_MESSAGE_VALUE_ON", o);
  Py_DECREF(o);
  if (res < 0)
    return -1;
  return _cffi_const_SMART_PLUG_MESSAGE_VALUE_OFF(lib);
}

static int _cffi_setup_custom(PyObject *lib)
{
  return _cffi_const_SMART_PLUG_MESSAGE_VALUE_ON(lib);
}

static PyMethodDef _cffi_methods[] = {
  {"convertArduinoMsgToInt16ForC", _cffi_f_convertArduinoMsgToInt16ForC, METH_VARARGS, NULL},
  {"convertMessageTypeToStrForC", _cffi_f_convertMessageTypeToStrForC, METH_O, NULL},
  {"getJSONMessageTypeForC", _cffi_f_getJSONMessageTypeForC, METH_VARARGS, NULL},
  {"isSensorMessageForC", _cffi_f_isSensorMessageForC, METH_O, NULL},
  {"_cffi_setup", _cffi_setup, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}    /* Sentinel */
};

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef _cffi_module_def = {
  PyModuleDef_HEAD_INIT,
  "__cffi_jsonCommon",
  NULL,
  -1,
  _cffi_methods,
  NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit___cffi_jsonCommon(void)
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
init__cffi_jsonCommon(void)
{
  PyObject *lib;
  lib = Py_InitModule("__cffi_jsonCommon", _cffi_methods);
  if (lib == NULL)
    return;
  if (((void)lib,0) < 0 || _cffi_init() < 0)
    return;
  return;
}

#endif
