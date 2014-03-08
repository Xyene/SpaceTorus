#define PY_SSIZE_T_CLEAN
#ifndef CYTHON_USE_PYLONG_INTERNALS
#ifdef PYLONG_BITS_IN_DIGIT
#define CYTHON_USE_PYLONG_INTERNALS 0
#else
#include "pyconfig.h"
#ifdef PYLONG_BITS_IN_DIGIT
#define CYTHON_USE_PYLONG_INTERNALS 1
#else
#define CYTHON_USE_PYLONG_INTERNALS 0
#endif
#endif
#endif
#include "Python.h"
#ifndef Py_PYTHON_H
    #error Python headers needed to compile C extensions, please install development version of Python.
#elif PY_VERSION_HEX < 0x02040000
    #error Cython requires Python 2.4+.
#else
#include <stddef.h> /* For offsetof */
#ifndef offsetof
#define offsetof(type, member) ( (size_t) & ((type*)0) -> member )
#endif
#if !defined(WIN32) && !defined(MS_WINDOWS)
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
  #ifndef __fastcall
    #define __fastcall
  #endif
#endif
#ifndef DL_IMPORT
  #define DL_IMPORT(t) t
#endif
#ifndef DL_EXPORT
  #define DL_EXPORT(t) t
#endif
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#ifndef Py_HUGE_VAL
  #define Py_HUGE_VAL HUGE_VAL
#endif
#ifdef PYPY_VERSION
#define CYTHON_COMPILING_IN_PYPY 1
#define CYTHON_COMPILING_IN_CPYTHON 0
#else
#define CYTHON_COMPILING_IN_PYPY 0
#define CYTHON_COMPILING_IN_CPYTHON 1
#endif
#if PY_VERSION_HEX < 0x02050000
  typedef int Py_ssize_t;
  #define PY_SSIZE_T_MAX INT_MAX
  #define PY_SSIZE_T_MIN INT_MIN
  #define PY_FORMAT_SIZE_T ""
  #define CYTHON_FORMAT_SSIZE_T ""
  #define PyInt_FromSsize_t(z) PyInt_FromLong(z)
  #define PyInt_AsSsize_t(o)   __Pyx_PyInt_AsInt(o)
  #define PyNumber_Index(o)    ((PyNumber_Check(o) && !PyFloat_Check(o)) ? PyNumber_Int(o) : \
                                (PyErr_Format(PyExc_TypeError, \
                                              "expected index value, got %.200s", Py_TYPE(o)->tp_name), \
                                 (PyObject*)0))
  #define __Pyx_PyIndex_Check(o) (PyNumber_Check(o) && !PyFloat_Check(o) && \
                                  !PyComplex_Check(o))
  #define PyIndex_Check __Pyx_PyIndex_Check
  #define PyErr_WarnEx(category, message, stacklevel) PyErr_Warn(category, message)
  #define __PYX_BUILD_PY_SSIZE_T "i"
#else
  #define __PYX_BUILD_PY_SSIZE_T "n"
  #define CYTHON_FORMAT_SSIZE_T "z"
  #define __Pyx_PyIndex_Check PyIndex_Check
#endif
#if PY_VERSION_HEX < 0x02060000
  #define Py_REFCNT(ob) (((PyObject*)(ob))->ob_refcnt)
  #define Py_TYPE(ob)   (((PyObject*)(ob))->ob_type)
  #define Py_SIZE(ob)   (((PyVarObject*)(ob))->ob_size)
  #define PyVarObject_HEAD_INIT(type, size) \
          PyObject_HEAD_INIT(type) size,
  #define PyType_Modified(t)
  typedef struct {
     void *buf;
     PyObject *obj;
     Py_ssize_t len;
     Py_ssize_t itemsize;
     int readonly;
     int ndim;
     char *format;
     Py_ssize_t *shape;
     Py_ssize_t *strides;
     Py_ssize_t *suboffsets;
     void *internal;
  } Py_buffer;
  #define PyBUF_SIMPLE 0
  #define PyBUF_WRITABLE 0x0001
  #define PyBUF_FORMAT 0x0004
  #define PyBUF_ND 0x0008
  #define PyBUF_STRIDES (0x0010 | PyBUF_ND)
  #define PyBUF_C_CONTIGUOUS (0x0020 | PyBUF_STRIDES)
  #define PyBUF_F_CONTIGUOUS (0x0040 | PyBUF_STRIDES)
  #define PyBUF_ANY_CONTIGUOUS (0x0080 | PyBUF_STRIDES)
  #define PyBUF_INDIRECT (0x0100 | PyBUF_STRIDES)
  #define PyBUF_RECORDS (PyBUF_STRIDES | PyBUF_FORMAT | PyBUF_WRITABLE)
  #define PyBUF_FULL (PyBUF_INDIRECT | PyBUF_FORMAT | PyBUF_WRITABLE)
  typedef int (*getbufferproc)(PyObject *, Py_buffer *, int);
  typedef void (*releasebufferproc)(PyObject *, Py_buffer *);
#endif
#if PY_MAJOR_VERSION < 3
  #define __Pyx_BUILTIN_MODULE_NAME "__builtin__"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos) \
          PyCode_New(a, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
#else
  #define __Pyx_BUILTIN_MODULE_NAME "builtins"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos) \
          PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
#endif
#if PY_MAJOR_VERSION < 3 && PY_MINOR_VERSION < 6
  #define PyUnicode_FromString(s) PyUnicode_Decode(s, strlen(s), "UTF-8", "strict")
#endif
#if PY_MAJOR_VERSION >= 3
  #define Py_TPFLAGS_CHECKTYPES 0
  #define Py_TPFLAGS_HAVE_INDEX 0
#endif
#if (PY_VERSION_HEX < 0x02060000) || (PY_MAJOR_VERSION >= 3)
  #define Py_TPFLAGS_HAVE_NEWBUFFER 0
#endif
#if PY_VERSION_HEX < 0x02060000
  #define Py_TPFLAGS_HAVE_VERSION_TAG 0
#endif
#if PY_VERSION_HEX > 0x03030000 && defined(PyUnicode_KIND)
  #define CYTHON_PEP393_ENABLED 1
  #define __Pyx_PyUnicode_READY(op)       (likely(PyUnicode_IS_READY(op)) ? \
                                              0 : _PyUnicode_Ready((PyObject *)(op)))
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_LENGTH(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) PyUnicode_READ_CHAR(u, i)
  #define __Pyx_PyUnicode_READ(k, d, i)   PyUnicode_READ(k, d, i)
#else
  #define CYTHON_PEP393_ENABLED 0
  #define __Pyx_PyUnicode_READY(op)       (0)
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_SIZE(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) ((Py_UCS4)(PyUnicode_AS_UNICODE(u)[i]))
  #define __Pyx_PyUnicode_READ(k, d, i)   ((k=k), (Py_UCS4)(((Py_UNICODE*)d)[i]))
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBaseString_Type            PyUnicode_Type
  #define PyStringObject               PyUnicodeObject
  #define PyString_Type                PyUnicode_Type
  #define PyString_Check               PyUnicode_Check
  #define PyString_CheckExact          PyUnicode_CheckExact
#endif
#if PY_VERSION_HEX < 0x02060000
  #define PyBytesObject                PyStringObject
  #define PyBytes_Type                 PyString_Type
  #define PyBytes_Check                PyString_Check
  #define PyBytes_CheckExact           PyString_CheckExact
  #define PyBytes_FromString           PyString_FromString
  #define PyBytes_FromStringAndSize    PyString_FromStringAndSize
  #define PyBytes_FromFormat           PyString_FromFormat
  #define PyBytes_DecodeEscape         PyString_DecodeEscape
  #define PyBytes_AsString             PyString_AsString
  #define PyBytes_AsStringAndSize      PyString_AsStringAndSize
  #define PyBytes_Size                 PyString_Size
  #define PyBytes_AS_STRING            PyString_AS_STRING
  #define PyBytes_GET_SIZE             PyString_GET_SIZE
  #define PyBytes_Repr                 PyString_Repr
  #define PyBytes_Concat               PyString_Concat
  #define PyBytes_ConcatAndDel         PyString_ConcatAndDel
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyBaseString_Check(obj) PyUnicode_Check(obj)
  #define __Pyx_PyBaseString_CheckExact(obj) PyUnicode_CheckExact(obj)
#else
  #define __Pyx_PyBaseString_Check(obj) (PyString_CheckExact(obj) || PyUnicode_CheckExact(obj) || \
                                         PyString_Check(obj) || PyUnicode_Check(obj))
  #define __Pyx_PyBaseString_CheckExact(obj) (Py_TYPE(obj) == &PyBaseString_Type)
#endif
#if PY_VERSION_HEX < 0x02060000
  #define PySet_Check(obj)             PyObject_TypeCheck(obj, &PySet_Type)
  #define PyFrozenSet_Check(obj)       PyObject_TypeCheck(obj, &PyFrozenSet_Type)
#endif
#ifndef PySet_CheckExact
  #define PySet_CheckExact(obj)        (Py_TYPE(obj) == &PySet_Type)
#endif
#define __Pyx_TypeCheck(obj, type) PyObject_TypeCheck(obj, (PyTypeObject *)type)
#if PY_MAJOR_VERSION >= 3
  #define PyIntObject                  PyLongObject
  #define PyInt_Type                   PyLong_Type
  #define PyInt_Check(op)              PyLong_Check(op)
  #define PyInt_CheckExact(op)         PyLong_CheckExact(op)
  #define PyInt_FromString             PyLong_FromString
  #define PyInt_FromUnicode            PyLong_FromUnicode
  #define PyInt_FromLong               PyLong_FromLong
  #define PyInt_FromSize_t             PyLong_FromSize_t
  #define PyInt_FromSsize_t            PyLong_FromSsize_t
  #define PyInt_AsLong                 PyLong_AsLong
  #define PyInt_AS_LONG                PyLong_AS_LONG
  #define PyInt_AsSsize_t              PyLong_AsSsize_t
  #define PyInt_AsUnsignedLongMask     PyLong_AsUnsignedLongMask
  #define PyInt_AsUnsignedLongLongMask PyLong_AsUnsignedLongLongMask
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBoolObject                 PyLongObject
#endif
#if PY_VERSION_HEX < 0x03020000
  typedef long Py_hash_t;
  #define __Pyx_PyInt_FromHash_t PyInt_FromLong
  #define __Pyx_PyInt_AsHash_t   PyInt_AsLong
#else
  #define __Pyx_PyInt_FromHash_t PyInt_FromSsize_t
  #define __Pyx_PyInt_AsHash_t   PyInt_AsSsize_t
#endif
#if (PY_MAJOR_VERSION < 3) || (PY_VERSION_HEX >= 0x03010300)
  #define __Pyx_PySequence_GetSlice(obj, a, b) PySequence_GetSlice(obj, a, b)
  #define __Pyx_PySequence_SetSlice(obj, a, b, value) PySequence_SetSlice(obj, a, b, value)
  #define __Pyx_PySequence_DelSlice(obj, a, b) PySequence_DelSlice(obj, a, b)
#else
  #define __Pyx_PySequence_GetSlice(obj, a, b) (unlikely(!(obj)) ? \
        (PyErr_SetString(PyExc_SystemError, "null argument to internal routine"), (PyObject*)0) : \
        (likely((obj)->ob_type->tp_as_mapping) ? (PySequence_GetSlice(obj, a, b)) : \
            (PyErr_Format(PyExc_TypeError, "'%.200s' object is unsliceable", (obj)->ob_type->tp_name), (PyObject*)0)))
  #define __Pyx_PySequence_SetSlice(obj, a, b, value) (unlikely(!(obj)) ? \
        (PyErr_SetString(PyExc_SystemError, "null argument to internal routine"), -1) : \
        (likely((obj)->ob_type->tp_as_mapping) ? (PySequence_SetSlice(obj, a, b, value)) : \
            (PyErr_Format(PyExc_TypeError, "'%.200s' object doesn't support slice assignment", (obj)->ob_type->tp_name), -1)))
  #define __Pyx_PySequence_DelSlice(obj, a, b) (unlikely(!(obj)) ? \
        (PyErr_SetString(PyExc_SystemError, "null argument to internal routine"), -1) : \
        (likely((obj)->ob_type->tp_as_mapping) ? (PySequence_DelSlice(obj, a, b)) : \
            (PyErr_Format(PyExc_TypeError, "'%.200s' object doesn't support slice deletion", (obj)->ob_type->tp_name), -1)))
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyMethod_New(func, self, klass) ((self) ? PyMethod_New(func, self) : PyInstanceMethod_New(func))
#endif
#if PY_VERSION_HEX < 0x02050000
  #define __Pyx_GetAttrString(o,n)   PyObject_GetAttrString((o),((char *)(n)))
  #define __Pyx_SetAttrString(o,n,a) PyObject_SetAttrString((o),((char *)(n)),(a))
  #define __Pyx_DelAttrString(o,n)   PyObject_DelAttrString((o),((char *)(n)))
#else
  #define __Pyx_GetAttrString(o,n)   PyObject_GetAttrString((o),(n))
  #define __Pyx_SetAttrString(o,n,a) PyObject_SetAttrString((o),(n),(a))
  #define __Pyx_DelAttrString(o,n)   PyObject_DelAttrString((o),(n))
#endif
#if PY_VERSION_HEX < 0x02050000
  #define __Pyx_NAMESTR(n) ((char *)(n))
  #define __Pyx_DOCSTR(n)  ((char *)(n))
#else
  #define __Pyx_NAMESTR(n) (n)
  #define __Pyx_DOCSTR(n)  (n)
#endif
#ifndef CYTHON_INLINE
  #if defined(__GNUC__)
    #define CYTHON_INLINE __inline__
  #elif defined(_MSC_VER)
    #define CYTHON_INLINE __inline
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_INLINE inline
  #else
    #define CYTHON_INLINE
  #endif
#endif
#ifndef CYTHON_RESTRICT
  #if defined(__GNUC__)
    #define CYTHON_RESTRICT __restrict__
  #elif defined(_MSC_VER) && _MSC_VER >= 1400
    #define CYTHON_RESTRICT __restrict
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_RESTRICT restrict
  #else
    #define CYTHON_RESTRICT
  #endif
#endif
#ifdef NAN
#define __PYX_NAN() ((float) NAN)
#else
static CYTHON_INLINE float __PYX_NAN() {
  /* Initialize NaN. The sign is irrelevant, an exponent with all bits 1 and
   a nonzero mantissa means NaN. If the first bit in the mantissa is 1, it is
   a quiet NaN. */
  float value;
  memset(&value, 0xFF, sizeof(value));
  return value;
}
#endif


#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_TrueDivide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceTrueDivide(x,y)
#else
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_Divide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceDivide(x,y)
#endif

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

#if defined(WIN32) || defined(MS_WINDOWS)
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#define __PYX_HAVE__space_torus__cmodel
#define __PYX_HAVE_API__space_torus__cmodel
#include "string.h"
#include "stdlib.h"
#include "windows.h"
#include "GL/gl.h"
#ifdef _OPENMP
#include <omp.h>
#endif /* _OPENMP */

#ifdef PYREX_WITHOUT_ASSERTIONS
#define CYTHON_WITHOUT_ASSERTIONS
#endif

#ifndef CYTHON_UNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define CYTHON_UNUSED __attribute__ ((__unused__))
#   else
#     define CYTHON_UNUSED
#   endif
# elif defined(__ICC) || (defined(__INTEL_COMPILER) && !defined(_MSC_VER))
#   define CYTHON_UNUSED __attribute__ ((__unused__))
# else
#   define CYTHON_UNUSED
# endif
#endif
typedef struct {PyObject **p; char *s; const Py_ssize_t n; const char* encoding;
                const char is_unicode; const char is_str; const char intern; } __Pyx_StringTabEntry; /*proto*/

#define __PYX_DEFAULT_STRING_ENCODING_IS_ASCII 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT 0
#define __PYX_DEFAULT_STRING_ENCODING ""
#define __Pyx_PyObject_FromString __Pyx_PyBytes_FromString
#define __Pyx_PyObject_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject*);
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject*, Py_ssize_t* length);
#define __Pyx_PyBytes_FromString        PyBytes_FromString
#define __Pyx_PyBytes_FromStringAndSize PyBytes_FromStringAndSize
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(char*);
#if PY_MAJOR_VERSION < 3
    #define __Pyx_PyStr_FromString        __Pyx_PyBytes_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#else
    #define __Pyx_PyStr_FromString        __Pyx_PyUnicode_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyUnicode_FromStringAndSize
#endif
#define __Pyx_PyObject_AsUString(s)    ((unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_FromUString(s)  __Pyx_PyObject_FromString((char*)s)
#define __Pyx_PyBytes_FromUString(s)   __Pyx_PyBytes_FromString((char*)s)
#define __Pyx_PyStr_FromUString(s)     __Pyx_PyStr_FromString((char*)s)
#define __Pyx_PyUnicode_FromUString(s) __Pyx_PyUnicode_FromString((char*)s)
#if PY_MAJOR_VERSION < 3
static CYTHON_INLINE size_t __Pyx_Py_UNICODE_strlen(const Py_UNICODE *u)
{
    const Py_UNICODE *u_end = u;
    while (*u_end++) ;
    return u_end - u - 1;
}
#else
#define __Pyx_Py_UNICODE_strlen Py_UNICODE_strlen
#endif
#define __Pyx_PyUnicode_FromUnicode(u)       PyUnicode_FromUnicode(u, __Pyx_Py_UNICODE_strlen(u))
#define __Pyx_PyUnicode_FromUnicodeAndLength PyUnicode_FromUnicode
#define __Pyx_PyUnicode_AsUnicode            PyUnicode_AsUnicode
#define __Pyx_Owned_Py_None(b) (Py_INCREF(Py_None), Py_None)
#define __Pyx_PyBool_FromLong(b) ((b) ? (Py_INCREF(Py_True), Py_True) : (Py_INCREF(Py_False), Py_False))
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject*);
static CYTHON_INLINE PyObject* __Pyx_PyNumber_Int(PyObject* x);
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject*);
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t);
static CYTHON_INLINE size_t __Pyx_PyInt_AsSize_t(PyObject*);
#if CYTHON_COMPILING_IN_CPYTHON
#define __pyx_PyFloat_AsDouble(x) (PyFloat_CheckExact(x) ? PyFloat_AS_DOUBLE(x) : PyFloat_AsDouble(x))
#else
#define __pyx_PyFloat_AsDouble(x) PyFloat_AsDouble(x)
#endif
#define __pyx_PyFloat_AsFloat(x) ((float) __pyx_PyFloat_AsDouble(x))
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
static int __Pyx_sys_getdefaultencoding_not_ascii;
static int __Pyx_init_sys_getdefaultencoding_params() {
    PyObject* sys = NULL;
    PyObject* default_encoding = NULL;
    PyObject* ascii_chars_u = NULL;
    PyObject* ascii_chars_b = NULL;
    sys = PyImport_ImportModule("sys");
    if (sys == NULL) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) (const char*) "getdefaultencoding", NULL);
    if (default_encoding == NULL) goto bad;
    if (strcmp(PyBytes_AsString(default_encoding), "ascii") == 0) {
        __Pyx_sys_getdefaultencoding_not_ascii = 0;
    } else {
        const char* default_encoding_c = PyBytes_AS_STRING(default_encoding);
        char ascii_chars[128];
        int c;
        for (c = 0; c < 128; c++) {
            ascii_chars[c] = c;
        }
        __Pyx_sys_getdefaultencoding_not_ascii = 1;
        ascii_chars_u = PyUnicode_DecodeASCII(ascii_chars, 128, NULL);
        if (ascii_chars_u == NULL) goto bad;
        ascii_chars_b = PyUnicode_AsEncodedString(ascii_chars_u, default_encoding_c, NULL);
        if (ascii_chars_b == NULL || strncmp(ascii_chars, PyBytes_AS_STRING(ascii_chars_b), 128) != 0) {
            PyErr_Format(
                PyExc_ValueError,
                "This module compiled with c_string_encoding=ascii, but default encoding '%s' is not a superset of ascii.",
                default_encoding_c);
            goto bad;
        }
    }
    Py_XDECREF(sys);
    Py_XDECREF(default_encoding);
    Py_XDECREF(ascii_chars_u);
    Py_XDECREF(ascii_chars_b);
    return 0;
bad:
    Py_XDECREF(sys);
    Py_XDECREF(default_encoding);
    Py_XDECREF(ascii_chars_u);
    Py_XDECREF(ascii_chars_b);
    return -1;
}
#endif
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT && PY_MAJOR_VERSION >= 3
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_DecodeUTF8(c_str, size, NULL)
#else
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_Decode(c_str, size, __PYX_DEFAULT_STRING_ENCODING, NULL)
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
static char* __PYX_DEFAULT_STRING_ENCODING;
static int __Pyx_init_sys_getdefaultencoding_params() {
    PyObject* sys = NULL;
    PyObject* default_encoding = NULL;
    char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (sys == NULL) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) (const char*) "getdefaultencoding", NULL);
    if (default_encoding == NULL) goto bad;
    default_encoding_c = PyBytes_AS_STRING(default_encoding);
    __PYX_DEFAULT_STRING_ENCODING = (char*) malloc(strlen(default_encoding_c));
    strcpy(__PYX_DEFAULT_STRING_ENCODING, default_encoding_c);
    Py_DECREF(sys);
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(sys);
    Py_XDECREF(default_encoding);
    return -1;
}
#endif
#endif


#ifdef __GNUC__
  /* Test for GCC > 2.95 */
  #if __GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95))
    #define likely(x)   __builtin_expect(!!(x), 1)
    #define unlikely(x) __builtin_expect(!!(x), 0)
  #else /* __GNUC__ > 2 ... */
    #define likely(x)   (x)
    #define unlikely(x) (x)
  #endif /* __GNUC__ > 2 ... */
#else /* __GNUC__ */
  #define likely(x)   (x)
  #define unlikely(x) (x)
#endif /* __GNUC__ */

static PyObject *__pyx_m;
static PyObject *__pyx_d;
static PyObject *__pyx_b;
static PyObject *__pyx_empty_tuple;
static PyObject *__pyx_empty_bytes;
static int __pyx_lineno;
static int __pyx_clineno = 0;
static const char * __pyx_cfilenm= __FILE__;
static const char *__pyx_filename;


static const char *__pyx_f[] = {
  "cmodel.pyx",
};

/*--- Type declarations ---*/
struct __pyx_obj_11space_torus_6cmodel_Group;
struct __pyx_obj_11space_torus_6cmodel_WavefrontObject;
struct __pyx_obj_11space_torus_6cmodel_Face;
struct __pyx_obj_11space_torus_6cmodel_Material;
struct __pyx_opt_args_11space_torus_6cmodel_model_list;

/* "C:\Users\Tudor\PycharmProjects\Space Torus\space_torus\_cyopengl.pxi":390
 *     void glInterleavedArrays(GLenum format, GLsizei stride, GLvoid *pointer)
 * 
 * cdef enum:             # <<<<<<<<<<<<<<
 *     GL_FALSE =                              0x0
 *     GL_TRUE =                               0x1
 */
enum  {
  __pyx_e_11space_torus_6cmodel_GL_FALSE = 0x0,
  __pyx_e_11space_torus_6cmodel_GL_TRUE = 0x1,
  __pyx_e_11space_torus_6cmodel_GL_BYTE = 0x1400,
  __pyx_e_11space_torus_6cmodel_GL_UNSIGNED_BYTE = 0x1401,
  __pyx_e_11space_torus_6cmodel_GL_SHORT = 0x1402,
  __pyx_e_11space_torus_6cmodel_GL_UNSIGNED_SHORT = 0x1403,
  __pyx_e_11space_torus_6cmodel_GL_INT = 0x1404,
  __pyx_e_11space_torus_6cmodel_GL_UNSIGNED_INT = 0x1405,
  __pyx_e_11space_torus_6cmodel_GL_FLOAT = 0x1406,
  __pyx_e_11space_torus_6cmodel_GL_DOUBLE = 0x140A,
  __pyx_e_11space_torus_6cmodel_GL_2_BYTES = 0x1407,
  __pyx_e_11space_torus_6cmodel_GL_3_BYTES = 0x1408,
  __pyx_e_11space_torus_6cmodel_GL_4_BYTES = 0x1409,
  __pyx_e_11space_torus_6cmodel_GL_POINTS = 0x0000,
  __pyx_e_11space_torus_6cmodel_GL_LINES = 0x0001,
  __pyx_e_11space_torus_6cmodel_GL_LINE_LOOP = 0x0002,
  __pyx_e_11space_torus_6cmodel_GL_LINE_STRIP = 0x0003,
  __pyx_e_11space_torus_6cmodel_GL_TRIANGLES = 0x0004,
  __pyx_e_11space_torus_6cmodel_GL_TRIANGLE_STRIP = 0x0005,
  __pyx_e_11space_torus_6cmodel_GL_TRIANGLE_FAN = 0x0006,
  __pyx_e_11space_torus_6cmodel_GL_QUADS = 0x0007,
  __pyx_e_11space_torus_6cmodel_GL_QUAD_STRIP = 0x0008,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON = 0x0009,
  __pyx_e_11space_torus_6cmodel_GL_VERTEX_ARRAY = 0x8074,
  __pyx_e_11space_torus_6cmodel_GL_NORMAL_ARRAY = 0x8075,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_ARRAY = 0x8076,
  __pyx_e_11space_torus_6cmodel_GL_INDEX_ARRAY = 0x8077,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_COORD_ARRAY = 0x8078,
  __pyx_e_11space_torus_6cmodel_GL_EDGE_FLAG_ARRAY = 0x8079,
  __pyx_e_11space_torus_6cmodel_GL_VERTEX_ARRAY_SIZE = 0x807A,
  __pyx_e_11space_torus_6cmodel_GL_VERTEX_ARRAY_TYPE = 0x807B,
  __pyx_e_11space_torus_6cmodel_GL_VERTEX_ARRAY_STRIDE = 0x807C,
  __pyx_e_11space_torus_6cmodel_GL_NORMAL_ARRAY_TYPE = 0x807E,
  __pyx_e_11space_torus_6cmodel_GL_NORMAL_ARRAY_STRIDE = 0x807F,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_ARRAY_SIZE = 0x8081,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_ARRAY_TYPE = 0x8082,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_ARRAY_STRIDE = 0x8083,
  __pyx_e_11space_torus_6cmodel_GL_INDEX_ARRAY_TYPE = 0x8085,
  __pyx_e_11space_torus_6cmodel_GL_INDEX_ARRAY_STRIDE = 0x8086,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_COORD_ARRAY_SIZE = 0x8088,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_COORD_ARRAY_TYPE = 0x8089,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_COORD_ARRAY_STRIDE = 0x808A,
  __pyx_e_11space_torus_6cmodel_GL_EDGE_FLAG_ARRAY_STRIDE = 0x808C,
  __pyx_e_11space_torus_6cmodel_GL_VERTEX_ARRAY_POINTER = 0x808E,
  __pyx_e_11space_torus_6cmodel_GL_NORMAL_ARRAY_POINTER = 0x808F,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_ARRAY_POINTER = 0x8090,
  __pyx_e_11space_torus_6cmodel_GL_INDEX_ARRAY_POINTER = 0x8091,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_COORD_ARRAY_POINTER = 0x8092,
  __pyx_e_11space_torus_6cmodel_GL_EDGE_FLAG_ARRAY_POINTER = 0x8093,
  __pyx_e_11space_torus_6cmodel_GL_V2F = 0x2A20,
  __pyx_e_11space_torus_6cmodel_GL_V3F = 0x2A21,
  __pyx_e_11space_torus_6cmodel_GL_C4UB_V2F = 0x2A22,
  __pyx_e_11space_torus_6cmodel_GL_C4UB_V3F = 0x2A23,
  __pyx_e_11space_torus_6cmodel_GL_C3F_V3F = 0x2A24,
  __pyx_e_11space_torus_6cmodel_GL_N3F_V3F = 0x2A25,
  __pyx_e_11space_torus_6cmodel_GL_C4F_N3F_V3F = 0x2A26,
  __pyx_e_11space_torus_6cmodel_GL_T2F_V3F = 0x2A27,
  __pyx_e_11space_torus_6cmodel_GL_T4F_V4F = 0x2A28,
  __pyx_e_11space_torus_6cmodel_GL_T2F_C4UB_V3F = 0x2A29,
  __pyx_e_11space_torus_6cmodel_GL_T2F_C3F_V3F = 0x2A2A,
  __pyx_e_11space_torus_6cmodel_GL_T2F_N3F_V3F = 0x2A2B,
  __pyx_e_11space_torus_6cmodel_GL_T2F_C4F_N3F_V3F = 0x2A2C,
  __pyx_e_11space_torus_6cmodel_GL_T4F_C4F_N3F_V4F = 0x2A2D,
  __pyx_e_11space_torus_6cmodel_GL_MATRIX_MODE = 0x0BA0,
  __pyx_e_11space_torus_6cmodel_GL_MODELVIEW = 0x1700,
  __pyx_e_11space_torus_6cmodel_GL_PROJECTION = 0x1701,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE = 0x1702,
  __pyx_e_11space_torus_6cmodel_GL_POINT_SMOOTH = 0x0B10,
  __pyx_e_11space_torus_6cmodel_GL_POINT_SIZE = 0x0B11,
  __pyx_e_11space_torus_6cmodel_GL_POINT_SIZE_GRANULARITY = 0x0B13,
  __pyx_e_11space_torus_6cmodel_GL_POINT_SIZE_RANGE = 0x0B12,
  __pyx_e_11space_torus_6cmodel_GL_LINE_SMOOTH = 0x0B20,
  __pyx_e_11space_torus_6cmodel_GL_LINE_STIPPLE = 0x0B24,
  __pyx_e_11space_torus_6cmodel_GL_LINE_STIPPLE_PATTERN = 0x0B25,
  __pyx_e_11space_torus_6cmodel_GL_LINE_STIPPLE_REPEAT = 0x0B26,
  __pyx_e_11space_torus_6cmodel_GL_LINE_WIDTH = 0x0B21,
  __pyx_e_11space_torus_6cmodel_GL_LINE_WIDTH_GRANULARITY = 0x0B23,
  __pyx_e_11space_torus_6cmodel_GL_LINE_WIDTH_RANGE = 0x0B22,
  __pyx_e_11space_torus_6cmodel_GL_POINT = 0x1B00,
  __pyx_e_11space_torus_6cmodel_GL_LINE = 0x1B01,
  __pyx_e_11space_torus_6cmodel_GL_FILL = 0x1B02,
  __pyx_e_11space_torus_6cmodel_GL_CW = 0x0900,
  __pyx_e_11space_torus_6cmodel_GL_CCW = 0x0901,
  __pyx_e_11space_torus_6cmodel_GL_FRONT = 0x0404,
  __pyx_e_11space_torus_6cmodel_GL_BACK = 0x0405,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON_MODE = 0x0B40,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON_SMOOTH = 0x0B41,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON_STIPPLE = 0x0B42,
  __pyx_e_11space_torus_6cmodel_GL_EDGE_FLAG = 0x0B43,
  __pyx_e_11space_torus_6cmodel_GL_CULL_FACE = 0x0B44,
  __pyx_e_11space_torus_6cmodel_GL_CULL_FACE_MODE = 0x0B45,
  __pyx_e_11space_torus_6cmodel_GL_FRONT_FACE = 0x0B46,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON_OFFSET_FACTOR = 0x8038,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON_OFFSET_UNITS = 0x2A00,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON_OFFSET_POINT = 0x2A01,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON_OFFSET_LINE = 0x2A02,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON_OFFSET_FILL = 0x8037,
  __pyx_e_11space_torus_6cmodel_GL_COMPILE = 0x1300,
  __pyx_e_11space_torus_6cmodel_GL_COMPILE_AND_EXECUTE = 0x1301,
  __pyx_e_11space_torus_6cmodel_GL_LIST_BASE = 0x0B32,
  __pyx_e_11space_torus_6cmodel_GL_LIST_INDEX = 0x0B33,
  __pyx_e_11space_torus_6cmodel_GL_LIST_MODE = 0x0B30,
  __pyx_e_11space_torus_6cmodel_GL_NEVER = 0x0200,
  __pyx_e_11space_torus_6cmodel_GL_LESS = 0x0201,
  __pyx_e_11space_torus_6cmodel_GL_EQUAL = 0x0202,
  __pyx_e_11space_torus_6cmodel_GL_LEQUAL = 0x0203,
  __pyx_e_11space_torus_6cmodel_GL_GREATER = 0x0204,
  __pyx_e_11space_torus_6cmodel_GL_NOTEQUAL = 0x0205,
  __pyx_e_11space_torus_6cmodel_GL_GEQUAL = 0x0206,
  __pyx_e_11space_torus_6cmodel_GL_ALWAYS = 0x0207,
  __pyx_e_11space_torus_6cmodel_GL_DEPTH_TEST = 0x0B71,
  __pyx_e_11space_torus_6cmodel_GL_DEPTH_BITS = 0x0D56,
  __pyx_e_11space_torus_6cmodel_GL_DEPTH_CLEAR_VALUE = 0x0B73,
  __pyx_e_11space_torus_6cmodel_GL_DEPTH_FUNC = 0x0B74,
  __pyx_e_11space_torus_6cmodel_GL_DEPTH_RANGE = 0x0B70,
  __pyx_e_11space_torus_6cmodel_GL_DEPTH_WRITEMASK = 0x0B72,
  __pyx_e_11space_torus_6cmodel_GL_DEPTH_COMPONENT = 0x1902,
  __pyx_e_11space_torus_6cmodel_GL_LIGHTING = 0x0B50,
  __pyx_e_11space_torus_6cmodel_GL_LIGHT0 = 0x4000,
  __pyx_e_11space_torus_6cmodel_GL_LIGHT1 = 0x4001,
  __pyx_e_11space_torus_6cmodel_GL_LIGHT2 = 0x4002,
  __pyx_e_11space_torus_6cmodel_GL_LIGHT3 = 0x4003,
  __pyx_e_11space_torus_6cmodel_GL_LIGHT4 = 0x4004,
  __pyx_e_11space_torus_6cmodel_GL_LIGHT5 = 0x4005,
  __pyx_e_11space_torus_6cmodel_GL_LIGHT6 = 0x4006,
  __pyx_e_11space_torus_6cmodel_GL_LIGHT7 = 0x4007,
  __pyx_e_11space_torus_6cmodel_GL_SPOT_EXPONENT = 0x1205,
  __pyx_e_11space_torus_6cmodel_GL_SPOT_CUTOFF = 0x1206,
  __pyx_e_11space_torus_6cmodel_GL_CONSTANT_ATTENUATION = 0x1207,
  __pyx_e_11space_torus_6cmodel_GL_LINEAR_ATTENUATION = 0x1208,
  __pyx_e_11space_torus_6cmodel_GL_QUADRATIC_ATTENUATION = 0x1209,
  __pyx_e_11space_torus_6cmodel_GL_AMBIENT = 0x1200,
  __pyx_e_11space_torus_6cmodel_GL_DIFFUSE = 0x1201,
  __pyx_e_11space_torus_6cmodel_GL_SPECULAR = 0x1202,
  __pyx_e_11space_torus_6cmodel_GL_SHININESS = 0x1601,
  __pyx_e_11space_torus_6cmodel_GL_EMISSION = 0x1600,
  __pyx_e_11space_torus_6cmodel_GL_POSITION = 0x1203,
  __pyx_e_11space_torus_6cmodel_GL_SPOT_DIRECTION = 0x1204,
  __pyx_e_11space_torus_6cmodel_GL_AMBIENT_AND_DIFFUSE = 0x1602,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_INDEXES = 0x1603,
  __pyx_e_11space_torus_6cmodel_GL_LIGHT_MODEL_TWO_SIDE = 0x0B52,
  __pyx_e_11space_torus_6cmodel_GL_LIGHT_MODEL_LOCAL_VIEWER = 0x0B51,
  __pyx_e_11space_torus_6cmodel_GL_LIGHT_MODEL_AMBIENT = 0x0B53,
  __pyx_e_11space_torus_6cmodel_GL_FRONT_AND_BACK = 0x0408,
  __pyx_e_11space_torus_6cmodel_GL_SHADE_MODEL = 0x0B54,
  __pyx_e_11space_torus_6cmodel_GL_FLAT = 0x1D00,
  __pyx_e_11space_torus_6cmodel_GL_SMOOTH = 0x1D01,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_MATERIAL = 0x0B57,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_MATERIAL_FACE = 0x0B55,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_MATERIAL_PARAMETER = 0x0B56,
  __pyx_e_11space_torus_6cmodel_GL_NORMALIZE = 0x0BA1,
  __pyx_e_11space_torus_6cmodel_GL_CLIP_PLANE0 = 0x3000,
  __pyx_e_11space_torus_6cmodel_GL_CLIP_PLANE1 = 0x3001,
  __pyx_e_11space_torus_6cmodel_GL_CLIP_PLANE2 = 0x3002,
  __pyx_e_11space_torus_6cmodel_GL_CLIP_PLANE3 = 0x3003,
  __pyx_e_11space_torus_6cmodel_GL_CLIP_PLANE4 = 0x3004,
  __pyx_e_11space_torus_6cmodel_GL_CLIP_PLANE5 = 0x3005,
  __pyx_e_11space_torus_6cmodel_GL_ACCUM_RED_BITS = 0x0D58,
  __pyx_e_11space_torus_6cmodel_GL_ACCUM_GREEN_BITS = 0x0D59,
  __pyx_e_11space_torus_6cmodel_GL_ACCUM_BLUE_BITS = 0x0D5A,
  __pyx_e_11space_torus_6cmodel_GL_ACCUM_ALPHA_BITS = 0x0D5B,
  __pyx_e_11space_torus_6cmodel_GL_ACCUM_CLEAR_VALUE = 0x0B80,
  __pyx_e_11space_torus_6cmodel_GL_ACCUM = 0x0100,
  __pyx_e_11space_torus_6cmodel_GL_ADD = 0x0104,
  __pyx_e_11space_torus_6cmodel_GL_LOAD = 0x0101,
  __pyx_e_11space_torus_6cmodel_GL_MULT = 0x0103,
  __pyx_e_11space_torus_6cmodel_GL_RETURN = 0x0102,
  __pyx_e_11space_torus_6cmodel_GL_ALPHA_TEST = 0x0BC0,
  __pyx_e_11space_torus_6cmodel_GL_ALPHA_TEST_REF = 0x0BC2,
  __pyx_e_11space_torus_6cmodel_GL_ALPHA_TEST_FUNC = 0x0BC1,
  __pyx_e_11space_torus_6cmodel_GL_BLEND = 0x0BE2,
  __pyx_e_11space_torus_6cmodel_GL_BLEND_SRC = 0x0BE1,
  __pyx_e_11space_torus_6cmodel_GL_BLEND_DST = 0x0BE0,
  __pyx_e_11space_torus_6cmodel_GL_ZERO = 0x0,
  __pyx_e_11space_torus_6cmodel_GL_ONE = 0x1,
  __pyx_e_11space_torus_6cmodel_GL_SRC_COLOR = 0x0300,
  __pyx_e_11space_torus_6cmodel_GL_ONE_MINUS_SRC_COLOR = 0x0301,
  __pyx_e_11space_torus_6cmodel_GL_SRC_ALPHA = 0x0302,
  __pyx_e_11space_torus_6cmodel_GL_ONE_MINUS_SRC_ALPHA = 0x0303,
  __pyx_e_11space_torus_6cmodel_GL_DST_ALPHA = 0x0304,
  __pyx_e_11space_torus_6cmodel_GL_ONE_MINUS_DST_ALPHA = 0x0305,
  __pyx_e_11space_torus_6cmodel_GL_DST_COLOR = 0x0306,
  __pyx_e_11space_torus_6cmodel_GL_ONE_MINUS_DST_COLOR = 0x0307,
  __pyx_e_11space_torus_6cmodel_GL_SRC_ALPHA_SATURATE = 0x0308,
  __pyx_e_11space_torus_6cmodel_GL_CONSTANT_COLOR = 0x8001,
  __pyx_e_11space_torus_6cmodel_GL_ONE_MINUS_CONSTANT_COLOR = 0x8002,
  __pyx_e_11space_torus_6cmodel_GL_CONSTANT_ALPHA = 0x8003,
  __pyx_e_11space_torus_6cmodel_GL_ONE_MINUS_CONSTANT_ALPHA = 0x8004,
  __pyx_e_11space_torus_6cmodel_GL_FEEDBACK = 0x1C01,
  __pyx_e_11space_torus_6cmodel_GL_RENDER = 0x1C00,
  __pyx_e_11space_torus_6cmodel_GL_SELECT = 0x1C02,
  __pyx_e_11space_torus_6cmodel_GL_2D = 0x0600,
  __pyx_e_11space_torus_6cmodel_GL_3D = 0x0601,
  __pyx_e_11space_torus_6cmodel_GL_3D_COLOR = 0x0602,
  __pyx_e_11space_torus_6cmodel_GL_3D_COLOR_TEXTURE = 0x0603,
  __pyx_e_11space_torus_6cmodel_GL_4D_COLOR_TEXTURE = 0x0604,
  __pyx_e_11space_torus_6cmodel_GL_POINT_TOKEN = 0x0701,
  __pyx_e_11space_torus_6cmodel_GL_LINE_TOKEN = 0x0702,
  __pyx_e_11space_torus_6cmodel_GL_LINE_RESET_TOKEN = 0x0707,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON_TOKEN = 0x0703,
  __pyx_e_11space_torus_6cmodel_GL_BITMAP_TOKEN = 0x0704,
  __pyx_e_11space_torus_6cmodel_GL_DRAW_PIXEL_TOKEN = 0x0705,
  __pyx_e_11space_torus_6cmodel_GL_COPY_PIXEL_TOKEN = 0x0706,
  __pyx_e_11space_torus_6cmodel_GL_PASS_THROUGH_TOKEN = 0x0700,
  __pyx_e_11space_torus_6cmodel_GL_FEEDBACK_BUFFER_POINTER = 0x0DF0,
  __pyx_e_11space_torus_6cmodel_GL_FEEDBACK_BUFFER_SIZE = 0x0DF1,
  __pyx_e_11space_torus_6cmodel_GL_FEEDBACK_BUFFER_TYPE = 0x0DF2,
  __pyx_e_11space_torus_6cmodel_GL_SELECTION_BUFFER_POINTER = 0x0DF3,
  __pyx_e_11space_torus_6cmodel_GL_SELECTION_BUFFER_SIZE = 0x0DF4,
  __pyx_e_11space_torus_6cmodel_GL_FOG = 0x0B60,
  __pyx_e_11space_torus_6cmodel_GL_FOG_MODE = 0x0B65,
  __pyx_e_11space_torus_6cmodel_GL_FOG_DENSITY = 0x0B62,
  __pyx_e_11space_torus_6cmodel_GL_FOG_COLOR = 0x0B66,
  __pyx_e_11space_torus_6cmodel_GL_FOG_INDEX = 0x0B61,
  __pyx_e_11space_torus_6cmodel_GL_FOG_START = 0x0B63,
  __pyx_e_11space_torus_6cmodel_GL_FOG_END = 0x0B64,
  __pyx_e_11space_torus_6cmodel_GL_LINEAR = 0x2601,
  __pyx_e_11space_torus_6cmodel_GL_EXP = 0x0800,
  __pyx_e_11space_torus_6cmodel_GL_EXP2 = 0x0801,
  __pyx_e_11space_torus_6cmodel_GL_LOGIC_OP = 0x0BF1,
  __pyx_e_11space_torus_6cmodel_GL_INDEX_LOGIC_OP = 0x0BF1,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_LOGIC_OP = 0x0BF2,
  __pyx_e_11space_torus_6cmodel_GL_LOGIC_OP_MODE = 0x0BF0,
  __pyx_e_11space_torus_6cmodel_GL_CLEAR = 0x1500,
  __pyx_e_11space_torus_6cmodel_GL_SET = 0x150F,
  __pyx_e_11space_torus_6cmodel_GL_COPY = 0x1503,
  __pyx_e_11space_torus_6cmodel_GL_COPY_INVERTED = 0x150C,
  __pyx_e_11space_torus_6cmodel_GL_NOOP = 0x1505,
  __pyx_e_11space_torus_6cmodel_GL_INVERT = 0x150A,
  __pyx_e_11space_torus_6cmodel_GL_AND = 0x1501,
  __pyx_e_11space_torus_6cmodel_GL_NAND = 0x150E,
  __pyx_e_11space_torus_6cmodel_GL_OR = 0x1507,
  __pyx_e_11space_torus_6cmodel_GL_NOR = 0x1508,
  __pyx_e_11space_torus_6cmodel_GL_XOR = 0x1506,
  __pyx_e_11space_torus_6cmodel_GL_EQUIV = 0x1509,
  __pyx_e_11space_torus_6cmodel_GL_AND_REVERSE = 0x1502,
  __pyx_e_11space_torus_6cmodel_GL_AND_INVERTED = 0x1504,
  __pyx_e_11space_torus_6cmodel_GL_OR_REVERSE = 0x150B,
  __pyx_e_11space_torus_6cmodel_GL_OR_INVERTED = 0x150D,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL_TEST = 0x0B90,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL_WRITEMASK = 0x0B98,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL_BITS = 0x0D57,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL_FUNC = 0x0B92,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL_VALUE_MASK = 0x0B93,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL_REF = 0x0B97,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL_FAIL = 0x0B94,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL_PASS_DEPTH_PASS = 0x0B96,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL_PASS_DEPTH_FAIL = 0x0B95,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL_CLEAR_VALUE = 0x0B91,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL_INDEX = 0x1901,
  __pyx_e_11space_torus_6cmodel_GL_KEEP = 0x1E00,
  __pyx_e_11space_torus_6cmodel_GL_REPLACE = 0x1E01,
  __pyx_e_11space_torus_6cmodel_GL_INCR = 0x1E02,
  __pyx_e_11space_torus_6cmodel_GL_DECR = 0x1E03,
  __pyx_e_11space_torus_6cmodel_GL_NONE = 0x0,
  __pyx_e_11space_torus_6cmodel_GL_LEFT = 0x0406,
  __pyx_e_11space_torus_6cmodel_GL_RIGHT = 0x0407,
  __pyx_e_11space_torus_6cmodel_GL_FRONT_LEFT = 0x0400,
  __pyx_e_11space_torus_6cmodel_GL_FRONT_RIGHT = 0x0401,
  __pyx_e_11space_torus_6cmodel_GL_BACK_LEFT = 0x0402,
  __pyx_e_11space_torus_6cmodel_GL_BACK_RIGHT = 0x0403,
  __pyx_e_11space_torus_6cmodel_GL_AUX0 = 0x0409,
  __pyx_e_11space_torus_6cmodel_GL_AUX1 = 0x040A,
  __pyx_e_11space_torus_6cmodel_GL_AUX2 = 0x040B,
  __pyx_e_11space_torus_6cmodel_GL_AUX3 = 0x040C,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_INDEX = 0x1900,
  __pyx_e_11space_torus_6cmodel_GL_RED = 0x1903,
  __pyx_e_11space_torus_6cmodel_GL_GREEN = 0x1904,
  __pyx_e_11space_torus_6cmodel_GL_BLUE = 0x1905,
  __pyx_e_11space_torus_6cmodel_GL_ALPHA = 0x1906,
  __pyx_e_11space_torus_6cmodel_GL_LUMINANCE = 0x1909,
  __pyx_e_11space_torus_6cmodel_GL_LUMINANCE_ALPHA = 0x190A,
  __pyx_e_11space_torus_6cmodel_GL_ALPHA_BITS = 0x0D55,
  __pyx_e_11space_torus_6cmodel_GL_RED_BITS = 0x0D52,
  __pyx_e_11space_torus_6cmodel_GL_GREEN_BITS = 0x0D53,
  __pyx_e_11space_torus_6cmodel_GL_BLUE_BITS = 0x0D54,
  __pyx_e_11space_torus_6cmodel_GL_INDEX_BITS = 0x0D51,
  __pyx_e_11space_torus_6cmodel_GL_SUBPIXEL_BITS = 0x0D50,
  __pyx_e_11space_torus_6cmodel_GL_AUX_BUFFERS = 0x0C00,
  __pyx_e_11space_torus_6cmodel_GL_READ_BUFFER = 0x0C02,
  __pyx_e_11space_torus_6cmodel_GL_DRAW_BUFFER = 0x0C01,
  __pyx_e_11space_torus_6cmodel_GL_DOUBLEBUFFER = 0x0C32,
  __pyx_e_11space_torus_6cmodel_GL_STEREO = 0x0C33,
  __pyx_e_11space_torus_6cmodel_GL_BITMAP = 0x1A00,
  __pyx_e_11space_torus_6cmodel_GL_COLOR = 0x1800,
  __pyx_e_11space_torus_6cmodel_GL_DEPTH = 0x1801,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL = 0x1802,
  __pyx_e_11space_torus_6cmodel_GL_DITHER = 0x0BD0,
  __pyx_e_11space_torus_6cmodel_GL_RGB = 0x1907,
  __pyx_e_11space_torus_6cmodel_GL_RGBA = 0x1908,
  __pyx_e_11space_torus_6cmodel_GL_MAX_LIST_NESTING = 0x0B31,
  __pyx_e_11space_torus_6cmodel_GL_MAX_ATTRIB_STACK_DEPTH = 0x0D35,
  __pyx_e_11space_torus_6cmodel_GL_MAX_MODELVIEW_STACK_DEPTH = 0x0D36,
  __pyx_e_11space_torus_6cmodel_GL_MAX_NAME_STACK_DEPTH = 0x0D37,
  __pyx_e_11space_torus_6cmodel_GL_MAX_PROJECTION_STACK_DEPTH = 0x0D38,
  __pyx_e_11space_torus_6cmodel_GL_MAX_TEXTURE_STACK_DEPTH = 0x0D39,
  __pyx_e_11space_torus_6cmodel_GL_MAX_EVAL_ORDER = 0x0D30,
  __pyx_e_11space_torus_6cmodel_GL_MAX_LIGHTS = 0x0D31,
  __pyx_e_11space_torus_6cmodel_GL_MAX_CLIP_PLANES = 0x0D32,
  __pyx_e_11space_torus_6cmodel_GL_MAX_TEXTURE_SIZE = 0x0D33,
  __pyx_e_11space_torus_6cmodel_GL_MAX_PIXEL_MAP_TABLE = 0x0D34,
  __pyx_e_11space_torus_6cmodel_GL_MAX_VIEWPORT_DIMS = 0x0D3A,
  __pyx_e_11space_torus_6cmodel_GL_MAX_CLIENT_ATTRIB_STACK_DEPTH = 0x0D3B,
  __pyx_e_11space_torus_6cmodel_GL_ATTRIB_STACK_DEPTH = 0x0BB0,
  __pyx_e_11space_torus_6cmodel_GL_CLIENT_ATTRIB_STACK_DEPTH = 0x0BB1,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_CLEAR_VALUE = 0x0C22,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_WRITEMASK = 0x0C23,
  __pyx_e_11space_torus_6cmodel_GL_CURRENT_INDEX = 0x0B01,
  __pyx_e_11space_torus_6cmodel_GL_CURRENT_COLOR = 0x0B00,
  __pyx_e_11space_torus_6cmodel_GL_CURRENT_NORMAL = 0x0B02,
  __pyx_e_11space_torus_6cmodel_GL_CURRENT_RASTER_COLOR = 0x0B04,
  __pyx_e_11space_torus_6cmodel_GL_CURRENT_RASTER_DISTANCE = 0x0B09,
  __pyx_e_11space_torus_6cmodel_GL_CURRENT_RASTER_INDEX = 0x0B05,
  __pyx_e_11space_torus_6cmodel_GL_CURRENT_RASTER_POSITION = 0x0B07,
  __pyx_e_11space_torus_6cmodel_GL_CURRENT_RASTER_TEXTURE_COORDS = 0x0B06,
  __pyx_e_11space_torus_6cmodel_GL_CURRENT_RASTER_POSITION_VALID = 0x0B08,
  __pyx_e_11space_torus_6cmodel_GL_CURRENT_TEXTURE_COORDS = 0x0B03,
  __pyx_e_11space_torus_6cmodel_GL_INDEX_CLEAR_VALUE = 0x0C20,
  __pyx_e_11space_torus_6cmodel_GL_INDEX_MODE = 0x0C30,
  __pyx_e_11space_torus_6cmodel_GL_INDEX_WRITEMASK = 0x0C21,
  __pyx_e_11space_torus_6cmodel_GL_MODELVIEW_MATRIX = 0x0BA6,
  __pyx_e_11space_torus_6cmodel_GL_MODELVIEW_STACK_DEPTH = 0x0BA3,
  __pyx_e_11space_torus_6cmodel_GL_NAME_STACK_DEPTH = 0x0D70,
  __pyx_e_11space_torus_6cmodel_GL_PROJECTION_MATRIX = 0x0BA7,
  __pyx_e_11space_torus_6cmodel_GL_PROJECTION_STACK_DEPTH = 0x0BA4,
  __pyx_e_11space_torus_6cmodel_GL_RENDER_MODE = 0x0C40,
  __pyx_e_11space_torus_6cmodel_GL_RGBA_MODE = 0x0C31,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_MATRIX = 0x0BA8,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_STACK_DEPTH = 0x0BA5,
  __pyx_e_11space_torus_6cmodel_GL_VIEWPORT = 0x0BA2,
  __pyx_e_11space_torus_6cmodel_GL_AUTO_NORMAL = 0x0D80,
  __pyx_e_11space_torus_6cmodel_GL_MAP1_COLOR_4 = 0x0D90,
  __pyx_e_11space_torus_6cmodel_GL_MAP1_GRID_DOMAIN = 0x0DD0,
  __pyx_e_11space_torus_6cmodel_GL_MAP1_GRID_SEGMENTS = 0x0DD1,
  __pyx_e_11space_torus_6cmodel_GL_MAP1_INDEX = 0x0D91,
  __pyx_e_11space_torus_6cmodel_GL_MAP1_NORMAL = 0x0D92,
  __pyx_e_11space_torus_6cmodel_GL_MAP1_TEXTURE_COORD_1 = 0x0D93,
  __pyx_e_11space_torus_6cmodel_GL_MAP1_TEXTURE_COORD_2 = 0x0D94,
  __pyx_e_11space_torus_6cmodel_GL_MAP1_TEXTURE_COORD_3 = 0x0D95,
  __pyx_e_11space_torus_6cmodel_GL_MAP1_TEXTURE_COORD_4 = 0x0D96,
  __pyx_e_11space_torus_6cmodel_GL_MAP1_VERTEX_3 = 0x0D97,
  __pyx_e_11space_torus_6cmodel_GL_MAP1_VERTEX_4 = 0x0D98,
  __pyx_e_11space_torus_6cmodel_GL_MAP2_COLOR_4 = 0x0DB0,
  __pyx_e_11space_torus_6cmodel_GL_MAP2_GRID_DOMAIN = 0x0DD2,
  __pyx_e_11space_torus_6cmodel_GL_MAP2_GRID_SEGMENTS = 0x0DD3,
  __pyx_e_11space_torus_6cmodel_GL_MAP2_INDEX = 0x0DB1,
  __pyx_e_11space_torus_6cmodel_GL_MAP2_NORMAL = 0x0DB2,
  __pyx_e_11space_torus_6cmodel_GL_MAP2_TEXTURE_COORD_1 = 0x0DB3,
  __pyx_e_11space_torus_6cmodel_GL_MAP2_TEXTURE_COORD_2 = 0x0DB4,
  __pyx_e_11space_torus_6cmodel_GL_MAP2_TEXTURE_COORD_3 = 0x0DB5,
  __pyx_e_11space_torus_6cmodel_GL_MAP2_TEXTURE_COORD_4 = 0x0DB6,
  __pyx_e_11space_torus_6cmodel_GL_MAP2_VERTEX_3 = 0x0DB7,
  __pyx_e_11space_torus_6cmodel_GL_MAP2_VERTEX_4 = 0x0DB8,
  __pyx_e_11space_torus_6cmodel_GL_COEFF = 0x0A00,
  __pyx_e_11space_torus_6cmodel_GL_DOMAIN = 0x0A02,
  __pyx_e_11space_torus_6cmodel_GL_ORDER = 0x0A01,
  __pyx_e_11space_torus_6cmodel_GL_FOG_HINT = 0x0C54,
  __pyx_e_11space_torus_6cmodel_GL_LINE_SMOOTH_HINT = 0x0C52,
  __pyx_e_11space_torus_6cmodel_GL_PERSPECTIVE_CORRECTION_HINT = 0x0C50,
  __pyx_e_11space_torus_6cmodel_GL_POINT_SMOOTH_HINT = 0x0C51,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON_SMOOTH_HINT = 0x0C53,
  __pyx_e_11space_torus_6cmodel_GL_DONT_CARE = 0x1100,
  __pyx_e_11space_torus_6cmodel_GL_FASTEST = 0x1101,
  __pyx_e_11space_torus_6cmodel_GL_NICEST = 0x1102,
  __pyx_e_11space_torus_6cmodel_GL_SCISSOR_TEST = 0x0C11,
  __pyx_e_11space_torus_6cmodel_GL_SCISSOR_BOX = 0x0C10,
  __pyx_e_11space_torus_6cmodel_GL_MAP_COLOR = 0x0D10,
  __pyx_e_11space_torus_6cmodel_GL_MAP_STENCIL = 0x0D11,
  __pyx_e_11space_torus_6cmodel_GL_INDEX_SHIFT = 0x0D12,
  __pyx_e_11space_torus_6cmodel_GL_INDEX_OFFSET = 0x0D13,
  __pyx_e_11space_torus_6cmodel_GL_RED_SCALE = 0x0D14,
  __pyx_e_11space_torus_6cmodel_GL_RED_BIAS = 0x0D15,
  __pyx_e_11space_torus_6cmodel_GL_GREEN_SCALE = 0x0D18,
  __pyx_e_11space_torus_6cmodel_GL_GREEN_BIAS = 0x0D19,
  __pyx_e_11space_torus_6cmodel_GL_BLUE_SCALE = 0x0D1A,
  __pyx_e_11space_torus_6cmodel_GL_BLUE_BIAS = 0x0D1B,
  __pyx_e_11space_torus_6cmodel_GL_ALPHA_SCALE = 0x0D1C,
  __pyx_e_11space_torus_6cmodel_GL_ALPHA_BIAS = 0x0D1D,
  __pyx_e_11space_torus_6cmodel_GL_DEPTH_SCALE = 0x0D1E,
  __pyx_e_11space_torus_6cmodel_GL_DEPTH_BIAS = 0x0D1F,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_S_TO_S_SIZE = 0x0CB1,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_I_TO_I_SIZE = 0x0CB0,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_I_TO_R_SIZE = 0x0CB2,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_I_TO_G_SIZE = 0x0CB3,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_I_TO_B_SIZE = 0x0CB4,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_I_TO_A_SIZE = 0x0CB5,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_R_TO_R_SIZE = 0x0CB6,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_G_TO_G_SIZE = 0x0CB7,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_B_TO_B_SIZE = 0x0CB8,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_A_TO_A_SIZE = 0x0CB9,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_S_TO_S = 0x0C71,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_I_TO_I = 0x0C70,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_I_TO_R = 0x0C72,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_I_TO_G = 0x0C73,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_I_TO_B = 0x0C74,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_I_TO_A = 0x0C75,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_R_TO_R = 0x0C76,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_G_TO_G = 0x0C77,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_B_TO_B = 0x0C78,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MAP_A_TO_A = 0x0C79,
  __pyx_e_11space_torus_6cmodel_GL_PACK_ALIGNMENT = 0x0D05,
  __pyx_e_11space_torus_6cmodel_GL_PACK_LSB_FIRST = 0x0D01,
  __pyx_e_11space_torus_6cmodel_GL_PACK_ROW_LENGTH = 0x0D02,
  __pyx_e_11space_torus_6cmodel_GL_PACK_SKIP_PIXELS = 0x0D04,
  __pyx_e_11space_torus_6cmodel_GL_PACK_SKIP_ROWS = 0x0D03,
  __pyx_e_11space_torus_6cmodel_GL_PACK_SWAP_BYTES = 0x0D00,
  __pyx_e_11space_torus_6cmodel_GL_UNPACK_ALIGNMENT = 0x0CF5,
  __pyx_e_11space_torus_6cmodel_GL_UNPACK_LSB_FIRST = 0x0CF1,
  __pyx_e_11space_torus_6cmodel_GL_UNPACK_ROW_LENGTH = 0x0CF2,
  __pyx_e_11space_torus_6cmodel_GL_UNPACK_SKIP_PIXELS = 0x0CF4,
  __pyx_e_11space_torus_6cmodel_GL_UNPACK_SKIP_ROWS = 0x0CF3,
  __pyx_e_11space_torus_6cmodel_GL_UNPACK_SWAP_BYTES = 0x0CF0,
  __pyx_e_11space_torus_6cmodel_GL_ZOOM_X = 0x0D16,
  __pyx_e_11space_torus_6cmodel_GL_ZOOM_Y = 0x0D17,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_ENV = 0x2300,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_ENV_MODE = 0x2200,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_1D = 0x0DE0,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_2D = 0x0DE1,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_WRAP_S = 0x2802,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_WRAP_T = 0x2803,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_MAG_FILTER = 0x2800,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_MIN_FILTER = 0x2801,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_ENV_COLOR = 0x2201,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_GEN_S = 0x0C60,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_GEN_T = 0x0C61,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_GEN_MODE = 0x2500,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_BORDER_COLOR = 0x1004,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_WIDTH = 0x1000,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_HEIGHT = 0x1001,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_BORDER = 0x1005,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_COMPONENTS = 0x1003,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_RED_SIZE = 0x805C,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_GREEN_SIZE = 0x805D,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_BLUE_SIZE = 0x805E,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_ALPHA_SIZE = 0x805F,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_LUMINANCE_SIZE = 0x8060,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_INTENSITY_SIZE = 0x8061,
  __pyx_e_11space_torus_6cmodel_GL_NEAREST_MIPMAP_NEAREST = 0x2700,
  __pyx_e_11space_torus_6cmodel_GL_NEAREST_MIPMAP_LINEAR = 0x2702,
  __pyx_e_11space_torus_6cmodel_GL_LINEAR_MIPMAP_NEAREST = 0x2701,
  __pyx_e_11space_torus_6cmodel_GL_LINEAR_MIPMAP_LINEAR = 0x2703,
  __pyx_e_11space_torus_6cmodel_GL_OBJECT_LINEAR = 0x2401,
  __pyx_e_11space_torus_6cmodel_GL_OBJECT_PLANE = 0x2501,
  __pyx_e_11space_torus_6cmodel_GL_EYE_LINEAR = 0x2400,
  __pyx_e_11space_torus_6cmodel_GL_EYE_PLANE = 0x2502,
  __pyx_e_11space_torus_6cmodel_GL_SPHERE_MAP = 0x2402,
  __pyx_e_11space_torus_6cmodel_GL_DECAL = 0x2101,
  __pyx_e_11space_torus_6cmodel_GL_MODULATE = 0x2100,
  __pyx_e_11space_torus_6cmodel_GL_NEAREST = 0x2600,
  __pyx_e_11space_torus_6cmodel_GL_REPEAT = 0x2901,
  __pyx_e_11space_torus_6cmodel_GL_CLAMP = 0x2900,
  __pyx_e_11space_torus_6cmodel_GL_S = 0x2000,
  __pyx_e_11space_torus_6cmodel_GL_T = 0x2001,
  __pyx_e_11space_torus_6cmodel_GL_R = 0x2002,
  __pyx_e_11space_torus_6cmodel_GL_Q = 0x2003,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_GEN_R = 0x0C62,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_GEN_Q = 0x0C63,
  __pyx_e_11space_torus_6cmodel_GL_VENDOR = 0x1F00,
  __pyx_e_11space_torus_6cmodel_GL_RENDERER = 0x1F01,
  __pyx_e_11space_torus_6cmodel_GL_VERSION = 0x1F02,
  __pyx_e_11space_torus_6cmodel_GL_EXTENSIONS = 0x1F03,
  __pyx_e_11space_torus_6cmodel_GL_NO_ERROR = 0x0,
  __pyx_e_11space_torus_6cmodel_GL_INVALID_VALUE = 0x0501,
  __pyx_e_11space_torus_6cmodel_GL_INVALID_ENUM = 0x0500,
  __pyx_e_11space_torus_6cmodel_GL_INVALID_OPERATION = 0x0502,
  __pyx_e_11space_torus_6cmodel_GL_STACK_OVERFLOW = 0x0503,
  __pyx_e_11space_torus_6cmodel_GL_STACK_UNDERFLOW = 0x0504,
  __pyx_e_11space_torus_6cmodel_GL_OUT_OF_MEMORY = 0x0505,
  __pyx_e_11space_torus_6cmodel_GL_CURRENT_BIT = 0x00000001,
  __pyx_e_11space_torus_6cmodel_GL_POINT_BIT = 0x00000002,
  __pyx_e_11space_torus_6cmodel_GL_LINE_BIT = 0x00000004,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON_BIT = 0x00000008,
  __pyx_e_11space_torus_6cmodel_GL_POLYGON_STIPPLE_BIT = 0x00000010,
  __pyx_e_11space_torus_6cmodel_GL_PIXEL_MODE_BIT = 0x00000020,
  __pyx_e_11space_torus_6cmodel_GL_LIGHTING_BIT = 0x00000040,
  __pyx_e_11space_torus_6cmodel_GL_FOG_BIT = 0x00000080,
  __pyx_e_11space_torus_6cmodel_GL_DEPTH_BUFFER_BIT = 0x00000100,
  __pyx_e_11space_torus_6cmodel_GL_ACCUM_BUFFER_BIT = 0x00000200,
  __pyx_e_11space_torus_6cmodel_GL_STENCIL_BUFFER_BIT = 0x00000400,
  __pyx_e_11space_torus_6cmodel_GL_VIEWPORT_BIT = 0x00000800,
  __pyx_e_11space_torus_6cmodel_GL_TRANSFORM_BIT = 0x00001000,
  __pyx_e_11space_torus_6cmodel_GL_ENABLE_BIT = 0x00002000,
  __pyx_e_11space_torus_6cmodel_GL_COLOR_BUFFER_BIT = 0x00004000,
  __pyx_e_11space_torus_6cmodel_GL_HINT_BIT = 0x00008000,
  __pyx_e_11space_torus_6cmodel_GL_EVAL_BIT = 0x00010000,
  __pyx_e_11space_torus_6cmodel_GL_LIST_BIT = 0x00020000,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_BIT = 0x00040000,
  __pyx_e_11space_torus_6cmodel_GL_SCISSOR_BIT = 0x00080000,
  __pyx_e_11space_torus_6cmodel_GL_ALL_ATTRIB_BITS = 0x000FFFFF,
  __pyx_e_11space_torus_6cmodel_GL_PROXY_TEXTURE_1D = 0x8063,
  __pyx_e_11space_torus_6cmodel_GL_PROXY_TEXTURE_2D = 0x8064,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_PRIORITY = 0x8066,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_RESIDENT = 0x8067,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_BINDING_1D = 0x8068,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_BINDING_2D = 0x8069,
  __pyx_e_11space_torus_6cmodel_GL_TEXTURE_INTERNAL_FORMAT = 0x1003,
  __pyx_e_11space_torus_6cmodel_GL_ALPHA4 = 0x803B,
  __pyx_e_11space_torus_6cmodel_GL_ALPHA8 = 0x803C,
  __pyx_e_11space_torus_6cmodel_GL_ALPHA12 = 0x803D,
  __pyx_e_11space_torus_6cmodel_GL_ALPHA16 = 0x803E,
  __pyx_e_11space_torus_6cmodel_GL_LUMINANCE4 = 0x803F,
  __pyx_e_11space_torus_6cmodel_GL_LUMINANCE8 = 0x8040,
  __pyx_e_11space_torus_6cmodel_GL_LUMINANCE12 = 0x8041,
  __pyx_e_11space_torus_6cmodel_GL_LUMINANCE16 = 0x8042,
  __pyx_e_11space_torus_6cmodel_GL_LUMINANCE4_ALPHA4 = 0x8043,
  __pyx_e_11space_torus_6cmodel_GL_LUMINANCE6_ALPHA2 = 0x8044,
  __pyx_e_11space_torus_6cmodel_GL_LUMINANCE8_ALPHA8 = 0x8045,
  __pyx_e_11space_torus_6cmodel_GL_LUMINANCE12_ALPHA4 = 0x8046,
  __pyx_e_11space_torus_6cmodel_GL_LUMINANCE12_ALPHA12 = 0x8047,
  __pyx_e_11space_torus_6cmodel_GL_LUMINANCE16_ALPHA16 = 0x8048,
  __pyx_e_11space_torus_6cmodel_GL_INTENSITY = 0x8049,
  __pyx_e_11space_torus_6cmodel_GL_INTENSITY4 = 0x804A,
  __pyx_e_11space_torus_6cmodel_GL_INTENSITY8 = 0x804B,
  __pyx_e_11space_torus_6cmodel_GL_INTENSITY12 = 0x804C,
  __pyx_e_11space_torus_6cmodel_GL_INTENSITY16 = 0x804D,
  __pyx_e_11space_torus_6cmodel_GL_R3_G3_B2 = 0x2A10,
  __pyx_e_11space_torus_6cmodel_GL_RGB4 = 0x804F,
  __pyx_e_11space_torus_6cmodel_GL_RGB5 = 0x8050,
  __pyx_e_11space_torus_6cmodel_GL_RGB8 = 0x8051,
  __pyx_e_11space_torus_6cmodel_GL_RGB10 = 0x8052,
  __pyx_e_11space_torus_6cmodel_GL_RGB12 = 0x8053,
  __pyx_e_11space_torus_6cmodel_GL_RGB16 = 0x8054,
  __pyx_e_11space_torus_6cmodel_GL_RGBA2 = 0x8055,
  __pyx_e_11space_torus_6cmodel_GL_RGBA4 = 0x8056,
  __pyx_e_11space_torus_6cmodel_GL_RGB5_A1 = 0x8057,
  __pyx_e_11space_torus_6cmodel_GL_RGBA8 = 0x8058,
  __pyx_e_11space_torus_6cmodel_GL_RGB10_A2 = 0x8059,
  __pyx_e_11space_torus_6cmodel_GL_RGBA12 = 0x805A,
  __pyx_e_11space_torus_6cmodel_GL_RGBA16 = 0x805B,
  __pyx_e_11space_torus_6cmodel_GL_CLIENT_PIXEL_STORE_BIT = 0x00000001,
  __pyx_e_11space_torus_6cmodel_GL_CLIENT_VERTEX_ARRAY_BIT = 0x00000002,
  __pyx_e_11space_torus_6cmodel_GL_ALL_CLIENT_ATTRIB_BITS = 0xFFFFFFFF,
  __pyx_e_11space_torus_6cmodel_GL_CLIENT_ALL_ATTRIB_BITS = 0xFFFFFFFF
};

/* "space_torus\cmodel.pyx":11
 * from space_torus.texture import load_texture
 * 
 * cdef enum:             # <<<<<<<<<<<<<<
 *     FACE_TRIANGLES
 *     FACE_QUADS
 */
enum  {
  __pyx_e_11space_torus_6cmodel_FACE_TRIANGLES,
  __pyx_e_11space_torus_6cmodel_FACE_QUADS
};

/* "space_torus\cmodel.pyx":26
 *     glVertex3f(x * sx, y * sy, z * sz)
 * 
 * cpdef model_list(WavefrontObject model, float sx=1, float sy=1, float sz=1, tuple rotation=(0, 0, 0)):             # <<<<<<<<<<<<<<
 *     for m, text in model.materials.iteritems():
 *         if text.texture:
 */
struct __pyx_opt_args_11space_torus_6cmodel_model_list {
  int __pyx_n;
  float sx;
  float sy;
  float sz;
  PyObject *rotation;
};

/* "space_torus\cmodel.pyx":271
 *         self.dispatch(path)
 * 
 * cdef class Group(object):             # <<<<<<<<<<<<<<
 *     cdef public str name
 *     cdef public tuple min
 */
struct __pyx_obj_11space_torus_6cmodel_Group {
  PyObject_HEAD
  PyObject *name;
  PyObject *min;
  struct __pyx_obj_11space_torus_6cmodel_Material *material;
  PyObject *faces;
  PyObject *indices;
  PyObject *vertices;
  PyObject *normals;
  PyObject *textures;
  int idx_count;
};


/* "space_torus\cmodel.pyx":107
 *     return WavefrontObject(os.path.join(os.path.dirname(__file__), 'assets', 'models', path))
 * 
 * cdef class WavefrontObject(object):             # <<<<<<<<<<<<<<
 *     cdef public str root
 *     cdef public list vertices, normals, textures, groups
 */
struct __pyx_obj_11space_torus_6cmodel_WavefrontObject {
  PyObject_HEAD
  struct __pyx_vtabstruct_11space_torus_6cmodel_WavefrontObject *__pyx_vtab;
  PyObject *root;
  PyObject *vertices;
  PyObject *normals;
  PyObject *textures;
  PyObject *groups;
  PyObject *materials;
  struct __pyx_obj_11space_torus_6cmodel_Material *current_material;
  PyObject *type;
};


/* "space_torus\cmodel.pyx":290
 *         self.idx_count = 0
 * 
 * cdef class Face(object):             # <<<<<<<<<<<<<<
 *     cdef public int type
 *     cdef public list verts, norms, texs, vertices, normals, textures
 */
struct __pyx_obj_11space_torus_6cmodel_Face {
  PyObject_HEAD
  int type;
  PyObject *verts;
  PyObject *norms;
  PyObject *texs;
  PyObject *vertices;
  PyObject *normals;
  PyObject *textures;
};


/* "space_torus\cmodel.pyx":303
 *         self.textures = textures
 * 
 * cdef class Material(object):             # <<<<<<<<<<<<<<
 *     cdef public str name, texture
 *     cdef public tuple Ka, Kd, Ks
 */
struct __pyx_obj_11space_torus_6cmodel_Material {
  PyObject_HEAD
  PyObject *name;
  PyObject *texture;
  PyObject *Ka;
  PyObject *Kd;
  PyObject *Ks;
  double shininess;
};



/* "space_torus\cmodel.pyx":107
 *     return WavefrontObject(os.path.join(os.path.dirname(__file__), 'assets', 'models', path))
 * 
 * cdef class WavefrontObject(object):             # <<<<<<<<<<<<<<
 *     cdef public str root
 *     cdef public list vertices, normals, textures, groups
 */

struct __pyx_vtabstruct_11space_torus_6cmodel_WavefrontObject {
  PyObject *(*dispatch)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*newmtl)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*Ka)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*Kd)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*Ks)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*Ns)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*map_Kd)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*v)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*vn)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*vt)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*f)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*mtllib)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*usemtl)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
  PyObject *(*g)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
};
static struct __pyx_vtabstruct_11space_torus_6cmodel_WavefrontObject *__pyx_vtabptr_11space_torus_6cmodel_WavefrontObject;
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_dispatch(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_newmtl(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_Ka(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_Kd(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_Ks(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_Ns(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_map_Kd(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_v(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_vn(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_vt(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_f(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_mtllib(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_usemtl(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_g(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *);
#ifndef CYTHON_REFNANNY
  #define CYTHON_REFNANNY 0
#endif
#if CYTHON_REFNANNY
  typedef struct {
    void (*INCREF)(void*, PyObject*, int);
    void (*DECREF)(void*, PyObject*, int);
    void (*GOTREF)(void*, PyObject*, int);
    void (*GIVEREF)(void*, PyObject*, int);
    void* (*SetupContext)(const char*, int, const char*);
    void (*FinishContext)(void**);
  } __Pyx_RefNannyAPIStruct;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNanny = NULL;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname); /*proto*/
  #define __Pyx_RefNannyDeclarations void *__pyx_refnanny = NULL;
#ifdef WITH_THREAD
  #define __Pyx_RefNannySetupContext(name, acquire_gil) \
          if (acquire_gil) { \
              PyGILState_STATE __pyx_gilstate_save = PyGILState_Ensure(); \
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__); \
              PyGILState_Release(__pyx_gilstate_save); \
          } else { \
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__); \
          }
#else
  #define __Pyx_RefNannySetupContext(name, acquire_gil) \
          __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__)
#endif
  #define __Pyx_RefNannyFinishContext() \
          __Pyx_RefNanny->FinishContext(&__pyx_refnanny)
  #define __Pyx_INCREF(r)  __Pyx_RefNanny->INCREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_DECREF(r)  __Pyx_RefNanny->DECREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GOTREF(r)  __Pyx_RefNanny->GOTREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GIVEREF(r) __Pyx_RefNanny->GIVEREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_XINCREF(r)  do { if((r) != NULL) {__Pyx_INCREF(r); }} while(0)
  #define __Pyx_XDECREF(r)  do { if((r) != NULL) {__Pyx_DECREF(r); }} while(0)
  #define __Pyx_XGOTREF(r)  do { if((r) != NULL) {__Pyx_GOTREF(r); }} while(0)
  #define __Pyx_XGIVEREF(r) do { if((r) != NULL) {__Pyx_GIVEREF(r);}} while(0)
#else
  #define __Pyx_RefNannyDeclarations
  #define __Pyx_RefNannySetupContext(name, acquire_gil)
  #define __Pyx_RefNannyFinishContext()
  #define __Pyx_INCREF(r) Py_INCREF(r)
  #define __Pyx_DECREF(r) Py_DECREF(r)
  #define __Pyx_GOTREF(r)
  #define __Pyx_GIVEREF(r)
  #define __Pyx_XINCREF(r) Py_XINCREF(r)
  #define __Pyx_XDECREF(r) Py_XDECREF(r)
  #define __Pyx_XGOTREF(r)
  #define __Pyx_XGIVEREF(r)
#endif /* CYTHON_REFNANNY */
#define __Pyx_XDECREF_SET(r, v) do {                            \
        PyObject *tmp = (PyObject *) r;                         \
        r = v; __Pyx_XDECREF(tmp);                              \
    } while (0)
#define __Pyx_DECREF_SET(r, v) do {                             \
        PyObject *tmp = (PyObject *) r;                         \
        r = v; __Pyx_DECREF(tmp);                               \
    } while (0)
#define __Pyx_CLEAR(r)    do { PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);} while(0)
#define __Pyx_XCLEAR(r)   do { if((r) != NULL) {PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);}} while(0)

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStr(PyObject* obj, PyObject* attr_name) {
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_getattro))
        return tp->tp_getattro(obj, attr_name);
#if PY_MAJOR_VERSION < 3
    if (likely(tp->tp_getattr))
        return tp->tp_getattr(obj, PyString_AS_STRING(attr_name));
#endif
    return PyObject_GetAttr(obj, attr_name);
}
#else
#define __Pyx_PyObject_GetAttrStr(o,n) PyObject_GetAttr(o,n)
#endif

static PyObject *__Pyx_GetBuiltinName(PyObject *name); /*proto*/

#define __Pyx_GetItemInt(o, i, size, to_py_func, is_list, wraparound, boundscheck) \
    (((size) <= sizeof(Py_ssize_t)) ? \
    __Pyx_GetItemInt_Fast(o, i, is_list, wraparound, boundscheck) : \
    __Pyx_GetItemInt_Generic(o, to_py_func(i)))
#define __Pyx_GetItemInt_List(o, i, size, to_py_func, is_list, wraparound, boundscheck) \
    (((size) <= sizeof(Py_ssize_t)) ? \
    __Pyx_GetItemInt_List_Fast(o, i, wraparound, boundscheck) : \
    __Pyx_GetItemInt_Generic(o, to_py_func(i)))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
#define __Pyx_GetItemInt_Tuple(o, i, size, to_py_func, is_list, wraparound, boundscheck) \
    (((size) <= sizeof(Py_ssize_t)) ? \
    __Pyx_GetItemInt_Tuple_Fast(o, i, wraparound, boundscheck) : \
    __Pyx_GetItemInt_Generic(o, to_py_func(i)))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                                     int is_list, int wraparound, int boundscheck);

static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected);

static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index);

static CYTHON_INLINE int __Pyx_IterFinish(void); /*proto*/

static int __Pyx_IternextUnpackEndCheck(PyObject *retval, Py_ssize_t expected); /*proto*/

static PyObject* __Pyx_PyObject_CallMethodTuple(PyObject* obj, PyObject* method_name, PyObject* args) {
    PyObject *method, *result = NULL;
    if (unlikely(!args)) return NULL;
    method = __Pyx_PyObject_GetAttrStr(obj, method_name);
    if (unlikely(!method)) goto bad;
    result = PyObject_Call(method, args, NULL);
    Py_DECREF(method);
bad:
    Py_DECREF(args);
    return result;
}
#define __Pyx_PyObject_CallMethod3(obj, name, arg1, arg2, arg3) \
    __Pyx_PyObject_CallMethodTuple(obj, name, PyTuple_Pack(3, arg1, arg2, arg3))
#define __Pyx_PyObject_CallMethod2(obj, name, arg1, arg2) \
    __Pyx_PyObject_CallMethodTuple(obj, name, PyTuple_Pack(2, arg1, arg2))
#define __Pyx_PyObject_CallMethod1(obj, name, arg1) \
    __Pyx_PyObject_CallMethodTuple(obj, name, PyTuple_Pack(1, arg1))
#define __Pyx_PyObject_CallMethod0(obj, name) \
    __Pyx_PyObject_CallMethodTuple(obj, name, (Py_INCREF(__pyx_empty_tuple), __pyx_empty_tuple))

static CYTHON_INLINE void __Pyx_RaiseNoneNotIterableError(void);

static void __Pyx_UnpackTupleError(PyObject *, Py_ssize_t index); /*proto*/

static CYTHON_INLINE int __Pyx_unpack_tuple2(PyObject* tuple, PyObject** value1, PyObject** value2,
                                             int is_tuple, int has_known_size, int decref_tuple);

static CYTHON_INLINE PyObject* __Pyx_dict_iterator(PyObject* dict, int is_dict, PyObject* method_name,
                                                   Py_ssize_t* p_orig_length, int* p_is_dict);
static CYTHON_INLINE int __Pyx_dict_iter_next(PyObject* dict_or_iter, Py_ssize_t orig_length, Py_ssize_t* ppos,
                                              PyObject** pkey, PyObject** pvalue, PyObject** pitem, int is_dict);

static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name); /*proto*/

static CYTHON_INLINE int __Pyx_TypeTest(PyObject *obj, PyTypeObject *type); /*proto*/

static void __Pyx_RaiseDoubleKeywordsError(const char* func_name, PyObject* kw_name); /*proto*/

static int __Pyx_ParseOptionalKeywords(PyObject *kwds, PyObject **argnames[], \
    PyObject *kwds2, PyObject *values[], Py_ssize_t num_pos_args, \
    const char* function_name); /*proto*/

static void __Pyx_RaiseArgtupleInvalid(const char* func_name, int exact,
    Py_ssize_t num_min, Py_ssize_t num_max, Py_ssize_t num_found); /*proto*/

static int __Pyx_ArgTypeTest(PyObject *obj, PyTypeObject *type, int none_allowed,
    const char *name, int exact); /*proto*/

static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb); /*proto*/

static CYTHON_INLINE void __Pyx_ErrRestore(PyObject *type, PyObject *value, PyObject *tb); /*proto*/
static CYTHON_INLINE void __Pyx_ErrFetch(PyObject **type, PyObject **value, PyObject **tb); /*proto*/

static double __Pyx__PyObject_AsDouble(PyObject* obj); /* proto */
#if CYTHON_COMPILING_IN_PYPY
#define __Pyx_PyObject_AsDouble(obj) \
(likely(PyFloat_CheckExact(obj)) ? PyFloat_AS_DOUBLE(obj) : \
 likely(PyInt_CheckExact(obj)) ? \
 PyFloat_AsDouble(obj) : __Pyx__PyObject_AsDouble(obj))
#else
#define __Pyx_PyObject_AsDouble(obj) \
((likely(PyFloat_CheckExact(obj))) ? \
 PyFloat_AS_DOUBLE(obj) : __Pyx__PyObject_AsDouble(obj))
#endif

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE int __Pyx_PyList_Append(PyObject* list, PyObject* x) {
    PyListObject* L = (PyListObject*) list;
    Py_ssize_t len = Py_SIZE(list);
    if (likely(L->allocated > len) & likely(len > (L->allocated >> 1))) {
        Py_INCREF(x);
        PyList_SET_ITEM(list, len, x);
        Py_SIZE(list) = len+1;
        return 0;
    }
    return PyList_Append(list, x);
}
#else
#define __Pyx_PyList_Append(L,x) PyList_Append(L,x)
#endif

#if CYTHON_COMPILING_IN_CPYTHON
#define __Pyx_PyObject_DelAttrStr(o,n) __Pyx_PyObject_SetAttrStr(o,n,NULL)
static CYTHON_INLINE int __Pyx_PyObject_SetAttrStr(PyObject* obj, PyObject* attr_name, PyObject* value) {
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_setattro))
        return tp->tp_setattro(obj, attr_name, value);
#if PY_MAJOR_VERSION < 3
    if (likely(tp->tp_setattr))
        return tp->tp_setattr(obj, PyString_AS_STRING(attr_name), value);
#endif
    return PyObject_SetAttr(obj, attr_name, value);
}
#else
#define __Pyx_PyObject_DelAttrStr(o,n)   PyObject_DelAttr(o,n)
#define __Pyx_PyObject_SetAttrStr(o,n,v) PyObject_SetAttr(o,n,v)
#endif

static CYTHON_INLINE PyObject* __Pyx_PyObject_Append(PyObject* L, PyObject* x); /*proto*/

static CYTHON_INLINE int __Pyx_PyDict_Contains(PyObject* item, PyObject* dict, int eq) {
    int result = PyDict_Contains(dict, item);
    return unlikely(result < 0) ? result : (result == (eq == Py_EQ));
}

#if PY_MAJOR_VERSION >= 3
static PyObject *__Pyx_PyDict_GetItem(PyObject *d, PyObject* key) {
    PyObject *value;
    value = PyDict_GetItemWithError(d, key);
    if (unlikely(!value)) {
        if (!PyErr_Occurred()) {
            PyObject* args = PyTuple_Pack(1, key);
            if (likely(args))
                PyErr_SetObject(PyExc_KeyError, args);
            Py_XDECREF(args);
        }
        return NULL;
    }
    Py_INCREF(value);
    return value;
}
#else
    #define __Pyx_PyDict_GetItem(d, key) PyObject_GetItem(d, key)
#endif

static int __Pyx_SetVtable(PyObject *dict, void *vtable); /*proto*/

static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name); /*proto*/

static CYTHON_INLINE void __Pyx_ExceptionSave(PyObject **type, PyObject **value, PyObject **tb); /*proto*/
static void __Pyx_ExceptionReset(PyObject *type, PyObject *value, PyObject *tb); /*proto*/

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level); /*proto*/

static CYTHON_INLINE GLuint __Pyx_PyInt_from_py_GLuint(PyObject *);

static CYTHON_INLINE PyObject *__Pyx_PyInt_to_py_GLuint(GLuint);

static int __Pyx_Print(PyObject*, PyObject *, int); /*proto*/
#if CYTHON_COMPILING_IN_PYPY || PY_MAJOR_VERSION >= 3
static PyObject* __pyx_print = 0;
static PyObject* __pyx_print_kwargs = 0;
#endif

static int __Pyx_PrintOne(PyObject* stream, PyObject *o); /*proto*/

static CYTHON_INLINE unsigned char __Pyx_PyInt_AsUnsignedChar(PyObject *);

static CYTHON_INLINE unsigned short __Pyx_PyInt_AsUnsignedShort(PyObject *);

static CYTHON_INLINE unsigned int __Pyx_PyInt_AsUnsignedInt(PyObject *);

static CYTHON_INLINE char __Pyx_PyInt_AsChar(PyObject *);

static CYTHON_INLINE short __Pyx_PyInt_AsShort(PyObject *);

static CYTHON_INLINE int __Pyx_PyInt_AsInt(PyObject *);

static CYTHON_INLINE signed char __Pyx_PyInt_AsSignedChar(PyObject *);

static CYTHON_INLINE signed short __Pyx_PyInt_AsSignedShort(PyObject *);

static CYTHON_INLINE signed int __Pyx_PyInt_AsSignedInt(PyObject *);

static CYTHON_INLINE int __Pyx_PyInt_AsLongDouble(PyObject *);

static CYTHON_INLINE unsigned long __Pyx_PyInt_AsUnsignedLong(PyObject *);

static CYTHON_INLINE unsigned PY_LONG_LONG __Pyx_PyInt_AsUnsignedLongLong(PyObject *);

static CYTHON_INLINE long __Pyx_PyInt_AsLong(PyObject *);

static CYTHON_INLINE PY_LONG_LONG __Pyx_PyInt_AsLongLong(PyObject *);

static CYTHON_INLINE signed long __Pyx_PyInt_AsSignedLong(PyObject *);

static CYTHON_INLINE signed PY_LONG_LONG __Pyx_PyInt_AsSignedLongLong(PyObject *);

static int __Pyx_check_binary_version(void);

typedef struct {
    int code_line;
    PyCodeObject* code_object;
} __Pyx_CodeObjectCacheEntry;
struct __Pyx_CodeObjectCache {
    int count;
    int max_count;
    __Pyx_CodeObjectCacheEntry* entries;
};
static struct __Pyx_CodeObjectCache __pyx_code_cache = {0,0,NULL};
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line);
static PyCodeObject *__pyx_find_code_object(int code_line);
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object);

static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename); /*proto*/

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t); /*proto*/


/* Module declarations from 'libc.string' */

/* Module declarations from 'libc.stdlib' */

/* Module declarations from 'space_torus.cmodel' */
static PyTypeObject *__pyx_ptype_11space_torus_6cmodel_Group = 0;
static PyTypeObject *__pyx_ptype_11space_torus_6cmodel_WavefrontObject = 0;
static PyTypeObject *__pyx_ptype_11space_torus_6cmodel_Face = 0;
static PyTypeObject *__pyx_ptype_11space_torus_6cmodel_Material = 0;
static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_point(struct __pyx_obj_11space_torus_6cmodel_Face *, PyObject *, PyObject *, PyObject *, float, float, float, int, int); /*proto*/
static PyObject *__pyx_f_11space_torus_6cmodel_model_list(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, int __pyx_skip_dispatch, struct __pyx_opt_args_11space_torus_6cmodel_model_list *__pyx_optional_args); /*proto*/
#define __Pyx_MODULE_NAME "space_torus.cmodel"
int __pyx_module_is_main_space_torus__cmodel = 0;

/* Implementation of 'space_torus.cmodel' */
static PyObject *__pyx_builtin_open;
static PyObject *__pyx_builtin_xrange;
static PyObject *__pyx_pf_11space_torus_6cmodel_model_list(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_model, float __pyx_v_sx, float __pyx_v_sy, float __pyx_v_sz, PyObject *__pyx_v_rotation); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_2load_model(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_path); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject___init__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_path); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_15WavefrontObject_4root___get__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_4root_2__set__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_4root_4__del__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_15WavefrontObject_8vertices___get__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8vertices_2__set__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8vertices_4__del__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_15WavefrontObject_7normals___get__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_7normals_2__set__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_7normals_4__del__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_15WavefrontObject_8textures___get__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8textures_2__set__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8textures_4__del__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_15WavefrontObject_6groups___get__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_6groups_2__set__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_6groups_4__del__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_15WavefrontObject_9materials___get__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_9materials_2__set__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_9materials_4__del__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group___init__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_name); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_4name___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_4name_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_4name_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_3min___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_3min_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_3min_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_8material___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_8material_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_8material_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_5faces___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_5faces_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_5faces_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_7indices___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_7indices_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_7indices_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_8vertices___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_8vertices_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_8vertices_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_7normals___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_7normals_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_7normals_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_8textures___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_8textures_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_8textures_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_9idx_count___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_5Group_9idx_count_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face___init__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, int __pyx_v_type, PyObject *__pyx_v_verts, PyObject *__pyx_v_norms, PyObject *__pyx_v_texs, PyObject *__pyx_v_vertices, PyObject *__pyx_v_normals, PyObject *__pyx_v_textures); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_4type___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_4type_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_5verts___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_5verts_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_5verts_4__del__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_5norms___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_5norms_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_5norms_4__del__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_4texs___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_4texs_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_4texs_4__del__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_8vertices___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_8vertices_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_8vertices_4__del__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_7normals___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_7normals_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_7normals_4__del__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_8textures___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_8textures_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_4Face_8textures_4__del__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_8Material___init__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_name, PyObject *__pyx_v_texture, PyObject *__pyx_v_Ka, PyObject *__pyx_v_Kd, PyObject *__pyx_v_Ks, double __pyx_v_shininess); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_8Material_4name___get__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_8Material_4name_2__set__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_8Material_4name_4__del__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_8Material_7texture___get__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_8Material_7texture_2__set__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_8Material_7texture_4__del__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_8Material_2Ka___get__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_8Material_2Ka_2__set__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_8Material_2Ka_4__del__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_8Material_2Kd___get__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_8Material_2Kd_2__set__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_8Material_2Kd_4__del__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_8Material_2Ks___get__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_8Material_2Ks_2__set__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static int __pyx_pf_11space_torus_6cmodel_8Material_2Ks_4__del__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self); /* proto */
static PyObject *__pyx_pf_11space_torus_6cmodel_8Material_9shininess___get__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self); /* proto */
static int __pyx_pf_11space_torus_6cmodel_8Material_9shininess_2__set__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_value); /* proto */
static PyObject *__pyx_tp_new_11space_torus_6cmodel_Group(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_11space_torus_6cmodel_WavefrontObject(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_11space_torus_6cmodel_Face(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static PyObject *__pyx_tp_new_11space_torus_6cmodel_Material(PyTypeObject *t, PyObject *a, PyObject *k); /*proto*/
static char __pyx_k_3[] = "Loading model %s...";
static char __pyx_k_4[] = "#";
static char __pyx_k_6[] = "/";
static char __pyx_k_8[] = "Warning: material %s undefined.";
static char __pyx_k_12[] = "os.path";
static char __pyx_k_13[] = "space_torus.texture";
static char __pyx_k_16[] = "C:\\Users\\Tudor\\PycharmProjects\\Space Torus\\space_torus\\cmodel.pyx";
static char __pyx_k_17[] = "space_torus.cmodel";
static char __pyx_k__f[] = "f";
static char __pyx_k__g[] = "g";
static char __pyx_k__n[] = "n";
static char __pyx_k__o[] = "o";
static char __pyx_k__r[] = "r";
static char __pyx_k__t[] = "t";
static char __pyx_k__v[] = "v";
static char __pyx_k__Ka[] = "Ka";
static char __pyx_k__Kd[] = "Kd";
static char __pyx_k__Ks[] = "Ks";
static char __pyx_k__Ns[] = "Ns";
static char __pyx_k__os[] = "os";
static char __pyx_k__sx[] = "sx";
static char __pyx_k__sy[] = "sy";
static char __pyx_k__sz[] = "sz";
static char __pyx_k__end[] = "end";
static char __pyx_k__file[] = "file";
static char __pyx_k__join[] = "join";
static char __pyx_k__name[] = "name";
static char __pyx_k__open[] = "open";
static char __pyx_k__path[] = "path";
static char __pyx_k__texs[] = "texs";
static char __pyx_k__time[] = "time";
static char __pyx_k__type[] = "type";
static char __pyx_k__clock[] = "clock";
static char __pyx_k__faces[] = "faces";
static char __pyx_k__model[] = "model";
static char __pyx_k__norms[] = "norms";
static char __pyx_k__print[] = "print";
static char __pyx_k__range[] = "range";
static char __pyx_k__split[] = "split";
static char __pyx_k__strip[] = "strip";
static char __pyx_k__verts[] = "verts";
static char __pyx_k__append[] = "append";
static char __pyx_k__assets[] = "assets";
static char __pyx_k__map_Kd[] = "map_Kd";
static char __pyx_k__models[] = "models";
static char __pyx_k__mtllib[] = "mtllib";
static char __pyx_k__newmtl[] = "newmtl";
static char __pyx_k__usemtl[] = "usemtl";
static char __pyx_k__xrange[] = "xrange";
static char __pyx_k__dirname[] = "dirname";
static char __pyx_k__indices[] = "indices";
static char __pyx_k__normals[] = "normals";
static char __pyx_k__texture[] = "texture";
static char __pyx_k____exit__[] = "__exit__";
static char __pyx_k____file__[] = "__file__";
static char __pyx_k____main__[] = "__main__";
static char __pyx_k____test__[] = "__test__";
static char __pyx_k__material[] = "material";
static char __pyx_k__rotation[] = "rotation";
static char __pyx_k__textures[] = "textures";
static char __pyx_k__vertices[] = "vertices";
static char __pyx_k____enter__[] = "__enter__";
static char __pyx_k__idx_count[] = "idx_count";
static char __pyx_k__iteritems[] = "iteritems";
static char __pyx_k__shininess[] = "shininess";
static char __pyx_k____import__[] = "__import__";
static char __pyx_k__load_model[] = "load_model";
static char __pyx_k__load_texture[] = "load_texture";
static char __pyx_k____pyx_vtable__[] = "__pyx_vtable__";
static PyObject *__pyx_n_s_12;
static PyObject *__pyx_n_s_13;
static PyObject *__pyx_kp_s_16;
static PyObject *__pyx_n_s_17;
static PyObject *__pyx_kp_s_3;
static PyObject *__pyx_kp_s_4;
static PyObject *__pyx_kp_s_6;
static PyObject *__pyx_kp_s_8;
static PyObject *__pyx_n_s__Ka;
static PyObject *__pyx_n_s__Kd;
static PyObject *__pyx_n_s__Ks;
static PyObject *__pyx_n_s____enter__;
static PyObject *__pyx_n_s____exit__;
static PyObject *__pyx_n_s____file__;
static PyObject *__pyx_n_s____import__;
static PyObject *__pyx_n_s____main__;
static PyObject *__pyx_n_s____pyx_vtable__;
static PyObject *__pyx_n_s____test__;
static PyObject *__pyx_n_s__append;
static PyObject *__pyx_n_s__assets;
static PyObject *__pyx_n_s__clock;
static PyObject *__pyx_n_s__dirname;
static PyObject *__pyx_n_s__end;
static PyObject *__pyx_n_s__faces;
static PyObject *__pyx_n_s__file;
static PyObject *__pyx_n_s__idx_count;
static PyObject *__pyx_n_s__indices;
static PyObject *__pyx_n_s__iteritems;
static PyObject *__pyx_n_s__join;
static PyObject *__pyx_n_s__load_model;
static PyObject *__pyx_n_s__load_texture;
static PyObject *__pyx_n_s__material;
static PyObject *__pyx_n_s__model;
static PyObject *__pyx_n_s__models;
static PyObject *__pyx_n_s__name;
static PyObject *__pyx_n_s__normals;
static PyObject *__pyx_n_s__norms;
static PyObject *__pyx_n_s__open;
static PyObject *__pyx_n_s__os;
static PyObject *__pyx_n_s__path;
static PyObject *__pyx_n_s__print;
static PyObject *__pyx_n_s__r;
static PyObject *__pyx_n_s__range;
static PyObject *__pyx_n_s__rotation;
static PyObject *__pyx_n_s__shininess;
static PyObject *__pyx_n_s__split;
static PyObject *__pyx_n_s__strip;
static PyObject *__pyx_n_s__sx;
static PyObject *__pyx_n_s__sy;
static PyObject *__pyx_n_s__sz;
static PyObject *__pyx_n_s__texs;
static PyObject *__pyx_n_s__texture;
static PyObject *__pyx_n_s__textures;
static PyObject *__pyx_n_s__time;
static PyObject *__pyx_n_s__type;
static PyObject *__pyx_n_s__vertices;
static PyObject *__pyx_n_s__verts;
static PyObject *__pyx_n_s__xrange;
static PyObject *__pyx_int_0;
static PyObject *__pyx_int_1;
static PyObject *__pyx_int_2;
static PyObject *__pyx_int_3;
static PyObject *__pyx_int_4;
static PyObject *__pyx_k_tuple_1;
static PyObject *__pyx_k_tuple_2;
static PyObject *__pyx_k_tuple_5;
static PyObject *__pyx_k_tuple_7;
static PyObject *__pyx_k_tuple_9;
static PyObject *__pyx_k_tuple_10;
static PyObject *__pyx_k_tuple_11;
static PyObject *__pyx_k_tuple_14;
static PyObject *__pyx_k_codeobj_15;

/* "space_torus\cmodel.pyx":15
 *     FACE_QUADS
 * 
 * cdef inline point(Face f, list vertices, list normals, list textures, float sx, float sy, float sz, int n, int tex_id):             # <<<<<<<<<<<<<<
 *     if f.norms:
 *         normal = normals[f.norms[n]]
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_point(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_f, PyObject *__pyx_v_vertices, PyObject *__pyx_v_normals, PyObject *__pyx_v_textures, float __pyx_v_sx, float __pyx_v_sy, float __pyx_v_sz, int __pyx_v_n, int __pyx_v_tex_id) {
  PyObject *__pyx_v_normal = NULL;
  PyObject *__pyx_v_tex = NULL;
  PyObject *__pyx_v_x = NULL;
  PyObject *__pyx_v_y = NULL;
  PyObject *__pyx_v_z = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  GLfloat __pyx_t_4;
  GLfloat __pyx_t_5;
  GLfloat __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  PyObject *(*__pyx_t_10)(PyObject *);
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("point", 0);

  /* "space_torus\cmodel.pyx":16
 * 
 * cdef inline point(Face f, list vertices, list normals, list textures, float sx, float sy, float sz, int n, int tex_id):
 *     if f.norms:             # <<<<<<<<<<<<<<
 *         normal = normals[f.norms[n]]
 *         glNormal3f(normal[0], normal[1], normal[2])
 */
  __pyx_t_1 = (((PyObject *)__pyx_v_f->norms) != Py_None) && (PyList_GET_SIZE(((PyObject *)__pyx_v_f->norms)) != 0);
  if (__pyx_t_1) {

    /* "space_torus\cmodel.pyx":17
 * cdef inline point(Face f, list vertices, list normals, list textures, float sx, float sy, float sz, int n, int tex_id):
 *     if f.norms:
 *         normal = normals[f.norms[n]]             # <<<<<<<<<<<<<<
 *         glNormal3f(normal[0], normal[1], normal[2])
 *     if tex_id:
 */
    if (unlikely(((PyObject *)__pyx_v_normals) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 17; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    if (unlikely(((PyObject *)__pyx_v_f->norms) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 17; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_f->norms), __pyx_v_n, sizeof(int), PyInt_FromLong, 1, 1, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 17; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = PyObject_GetItem(((PyObject *)__pyx_v_normals), __pyx_t_2); if (!__pyx_t_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 17; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_v_normal = __pyx_t_3;
    __pyx_t_3 = 0;

    /* "space_torus\cmodel.pyx":18
 *     if f.norms:
 *         normal = normals[f.norms[n]]
 *         glNormal3f(normal[0], normal[1], normal[2])             # <<<<<<<<<<<<<<
 *     if tex_id:
 *         tex = textures[f.texs[n]]
 */
    __pyx_t_3 = __Pyx_GetItemInt(__pyx_v_normal, 0, sizeof(long), PyInt_FromLong, 0, 0, 1); if (!__pyx_t_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 18; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = __pyx_PyFloat_AsFloat(__pyx_t_3); if (unlikely((__pyx_t_4 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 18; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_GetItemInt(__pyx_v_normal, 1, sizeof(long), PyInt_FromLong, 0, 0, 1); if (!__pyx_t_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 18; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_5 = __pyx_PyFloat_AsFloat(__pyx_t_3); if (unlikely((__pyx_t_5 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 18; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_GetItemInt(__pyx_v_normal, 2, sizeof(long), PyInt_FromLong, 0, 0, 1); if (!__pyx_t_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 18; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_6 = __pyx_PyFloat_AsFloat(__pyx_t_3); if (unlikely((__pyx_t_6 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 18; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    glNormal3f(__pyx_t_4, __pyx_t_5, __pyx_t_6);
    goto __pyx_L3;
  }
  __pyx_L3:;

  /* "space_torus\cmodel.pyx":19
 *         normal = normals[f.norms[n]]
 *         glNormal3f(normal[0], normal[1], normal[2])
 *     if tex_id:             # <<<<<<<<<<<<<<
 *         tex = textures[f.texs[n]]
 *         glTexCoord2f(tex[0], tex[1])
 */
  __pyx_t_1 = (__pyx_v_tex_id != 0);
  if (__pyx_t_1) {

    /* "space_torus\cmodel.pyx":20
 *         glNormal3f(normal[0], normal[1], normal[2])
 *     if tex_id:
 *         tex = textures[f.texs[n]]             # <<<<<<<<<<<<<<
 *         glTexCoord2f(tex[0], tex[1])
 * 
 */
    if (unlikely(((PyObject *)__pyx_v_textures) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    if (unlikely(((PyObject *)__pyx_v_f->texs) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_3 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_f->texs), __pyx_v_n, sizeof(int), PyInt_FromLong, 1, 1, 1); if (!__pyx_t_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_2 = PyObject_GetItem(((PyObject *)__pyx_v_textures), __pyx_t_3); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 20; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_v_tex = __pyx_t_2;
    __pyx_t_2 = 0;

    /* "space_torus\cmodel.pyx":21
 *     if tex_id:
 *         tex = textures[f.texs[n]]
 *         glTexCoord2f(tex[0], tex[1])             # <<<<<<<<<<<<<<
 * 
 *     x, y, z = vertices[f.verts[n]]
 */
    __pyx_t_2 = __Pyx_GetItemInt(__pyx_v_tex, 0, sizeof(long), PyInt_FromLong, 0, 0, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 21; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = __pyx_PyFloat_AsFloat(__pyx_t_2); if (unlikely((__pyx_t_6 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 21; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = __Pyx_GetItemInt(__pyx_v_tex, 1, sizeof(long), PyInt_FromLong, 0, 0, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 21; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_5 = __pyx_PyFloat_AsFloat(__pyx_t_2); if (unlikely((__pyx_t_5 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 21; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    glTexCoord2f(__pyx_t_6, __pyx_t_5);
    goto __pyx_L4;
  }
  __pyx_L4:;

  /* "space_torus\cmodel.pyx":23
 *         glTexCoord2f(tex[0], tex[1])
 * 
 *     x, y, z = vertices[f.verts[n]]             # <<<<<<<<<<<<<<
 *     glVertex3f(x * sx, y * sy, z * sz)
 * 
 */
  if (unlikely(((PyObject *)__pyx_v_vertices) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  if (unlikely(((PyObject *)__pyx_v_f->verts) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_f->verts), __pyx_v_n, sizeof(int), PyInt_FromLong, 1, 1, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyObject_GetItem(((PyObject *)__pyx_v_vertices), __pyx_t_2); if (!__pyx_t_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if ((likely(PyTuple_CheckExact(__pyx_t_3))) || (PyList_CheckExact(__pyx_t_3))) {
    PyObject* sequence = __pyx_t_3;
    #if CYTHON_COMPILING_IN_CPYTHON
    Py_ssize_t size = Py_SIZE(sequence);
    #else
    Py_ssize_t size = PySequence_Size(sequence);
    #endif
    if (unlikely(size != 3)) {
      if (size > 3) __Pyx_RaiseTooManyValuesError(3);
      else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    #if CYTHON_COMPILING_IN_CPYTHON
    if (likely(PyTuple_CheckExact(sequence))) {
      __pyx_t_2 = PyTuple_GET_ITEM(sequence, 0); 
      __pyx_t_7 = PyTuple_GET_ITEM(sequence, 1); 
      __pyx_t_8 = PyTuple_GET_ITEM(sequence, 2); 
    } else {
      __pyx_t_2 = PyList_GET_ITEM(sequence, 0); 
      __pyx_t_7 = PyList_GET_ITEM(sequence, 1); 
      __pyx_t_8 = PyList_GET_ITEM(sequence, 2); 
    }
    __Pyx_INCREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_t_7);
    __Pyx_INCREF(__pyx_t_8);
    #else
    __pyx_t_2 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_7 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_7)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_8 = PySequence_ITEM(sequence, 2); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_8);
    #endif
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  } else
  {
    Py_ssize_t index = -1;
    __pyx_t_9 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_9);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_10 = Py_TYPE(__pyx_t_9)->tp_iternext;
    index = 0; __pyx_t_2 = __pyx_t_10(__pyx_t_9); if (unlikely(!__pyx_t_2)) goto __pyx_L5_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_2);
    index = 1; __pyx_t_7 = __pyx_t_10(__pyx_t_9); if (unlikely(!__pyx_t_7)) goto __pyx_L5_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_7);
    index = 2; __pyx_t_8 = __pyx_t_10(__pyx_t_9); if (unlikely(!__pyx_t_8)) goto __pyx_L5_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_8);
    if (__Pyx_IternextUnpackEndCheck(__pyx_t_10(__pyx_t_9), 3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_10 = NULL;
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    goto __pyx_L6_unpacking_done;
    __pyx_L5_unpacking_failed:;
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    __pyx_t_10 = NULL;
    if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_L6_unpacking_done:;
  }
  __pyx_v_x = __pyx_t_2;
  __pyx_t_2 = 0;
  __pyx_v_y = __pyx_t_7;
  __pyx_t_7 = 0;
  __pyx_v_z = __pyx_t_8;
  __pyx_t_8 = 0;

  /* "space_torus\cmodel.pyx":24
 * 
 *     x, y, z = vertices[f.verts[n]]
 *     glVertex3f(x * sx, y * sy, z * sz)             # <<<<<<<<<<<<<<
 * 
 * cpdef model_list(WavefrontObject model, float sx=1, float sy=1, float sz=1, tuple rotation=(0, 0, 0)):
 */
  __pyx_t_3 = PyFloat_FromDouble(__pyx_v_sx); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_8 = PyNumber_Multiply(__pyx_v_x, __pyx_t_3); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_5 = __pyx_PyFloat_AsFloat(__pyx_t_8); if (unlikely((__pyx_t_5 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  __pyx_t_8 = PyFloat_FromDouble(__pyx_v_sy); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_8);
  __pyx_t_3 = PyNumber_Multiply(__pyx_v_y, __pyx_t_8); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  __pyx_t_6 = __pyx_PyFloat_AsFloat(__pyx_t_3); if (unlikely((__pyx_t_6 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyFloat_FromDouble(__pyx_v_sz); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_8 = PyNumber_Multiply(__pyx_v_z, __pyx_t_3); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_8);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_4 = __pyx_PyFloat_AsFloat(__pyx_t_8); if (unlikely((__pyx_t_4 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_8); __pyx_t_8 = 0;
  glVertex3f(__pyx_t_5, __pyx_t_6, __pyx_t_4);

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("space_torus.cmodel.point", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_normal);
  __Pyx_XDECREF(__pyx_v_tex);
  __Pyx_XDECREF(__pyx_v_x);
  __Pyx_XDECREF(__pyx_v_y);
  __Pyx_XDECREF(__pyx_v_z);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":26
 *     glVertex3f(x * sx, y * sy, z * sz)
 * 
 * cpdef model_list(WavefrontObject model, float sx=1, float sy=1, float sz=1, tuple rotation=(0, 0, 0)):             # <<<<<<<<<<<<<<
 *     for m, text in model.materials.iteritems():
 *         if text.texture:
 */

static PyObject *__pyx_pw_11space_torus_6cmodel_1model_list(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyObject *__pyx_f_11space_torus_6cmodel_model_list(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_model, CYTHON_UNUSED int __pyx_skip_dispatch, struct __pyx_opt_args_11space_torus_6cmodel_model_list *__pyx_optional_args) {
  float __pyx_v_sx = ((float)1.0);
  float __pyx_v_sy = ((float)1.0);
  float __pyx_v_sz = ((float)1.0);
  PyObject *__pyx_v_rotation = ((PyObject*)__pyx_k_tuple_1);
  CYTHON_UNUSED PyObject *__pyx_v_m = NULL;
  PyObject *__pyx_v_text = NULL;
  GLuint __pyx_v_display;
  float __pyx_v_pitch;
  float __pyx_v_yaw;
  float __pyx_v_roll;
  PyObject *__pyx_v_kx = 0;
  PyObject *__pyx_v_ky = 0;
  PyObject *__pyx_v_kz = 0;
  struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_f = 0;
  PyObject *__pyx_v_vertices = NULL;
  PyObject *__pyx_v_textures = NULL;
  PyObject *__pyx_v_normals = NULL;
  PyObject *__pyx_v_g = NULL;
  PyObject *__pyx_v_material = NULL;
  PyObject *__pyx_v_tex_id = NULL;
  long __pyx_v_type;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  Py_ssize_t __pyx_t_2;
  Py_ssize_t __pyx_t_3;
  int __pyx_t_4;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_t_7;
  int __pyx_t_8;
  PyObject *__pyx_t_9 = NULL;
  PyObject *__pyx_t_10 = NULL;
  PyObject *(*__pyx_t_11)(PyObject *);
  float __pyx_t_12;
  float __pyx_t_13;
  float __pyx_t_14;
  int __pyx_t_15;
  int __pyx_t_16;
  PyObject *__pyx_t_17 = NULL;
  GLuint __pyx_t_18;
  GLfloat __pyx_t_19;
  GLfloat __pyx_t_20;
  GLfloat __pyx_t_21;
  GLfloat __pyx_t_22[4];
  GLfloat __pyx_t_23[4];
  GLfloat __pyx_t_24[4];
  PyObject *(*__pyx_t_25)(PyObject *);
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("model_list", 0);
  if (__pyx_optional_args) {
    if (__pyx_optional_args->__pyx_n > 0) {
      __pyx_v_sx = __pyx_optional_args->sx;
      if (__pyx_optional_args->__pyx_n > 1) {
        __pyx_v_sy = __pyx_optional_args->sy;
        if (__pyx_optional_args->__pyx_n > 2) {
          __pyx_v_sz = __pyx_optional_args->sz;
          if (__pyx_optional_args->__pyx_n > 3) {
            __pyx_v_rotation = __pyx_optional_args->rotation;
          }
        }
      }
    }
  }

  /* "space_torus\cmodel.pyx":27
 * 
 * cpdef model_list(WavefrontObject model, float sx=1, float sy=1, float sz=1, tuple rotation=(0, 0, 0)):
 *     for m, text in model.materials.iteritems():             # <<<<<<<<<<<<<<
 *         if text.texture:
 *             load_texture(os.path.join(model.root, text.texture))
 */
  __pyx_t_2 = 0;
  if (unlikely(((PyObject *)__pyx_v_model->materials) == Py_None)) {
    PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%s'", "iteritems");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 27; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_5 = __Pyx_dict_iterator(((PyObject *)__pyx_v_model->materials), 1, ((PyObject *)__pyx_n_s__iteritems), (&__pyx_t_3), (&__pyx_t_4)); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 27; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_1);
  __pyx_t_1 = __pyx_t_5;
  __pyx_t_5 = 0;
  while (1) {
    __pyx_t_7 = __Pyx_dict_iter_next(__pyx_t_1, __pyx_t_3, &__pyx_t_2, &__pyx_t_5, &__pyx_t_6, NULL, __pyx_t_4);
    if (unlikely(__pyx_t_7 == 0)) break;
    if (unlikely(__pyx_t_7 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 27; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_5);
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_XDECREF_SET(__pyx_v_m, __pyx_t_5);
    __pyx_t_5 = 0;
    __Pyx_XDECREF_SET(__pyx_v_text, __pyx_t_6);
    __pyx_t_6 = 0;

    /* "space_torus\cmodel.pyx":28
 * cpdef model_list(WavefrontObject model, float sx=1, float sy=1, float sz=1, tuple rotation=(0, 0, 0)):
 *     for m, text in model.materials.iteritems():
 *         if text.texture:             # <<<<<<<<<<<<<<
 *             load_texture(os.path.join(model.root, text.texture))
 * 
 */
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_text, __pyx_n_s__texture); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 28; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_8 = __Pyx_PyObject_IsTrue(__pyx_t_6); if (unlikely(__pyx_t_8 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 28; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    if (__pyx_t_8) {

      /* "space_torus\cmodel.pyx":29
 *     for m, text in model.materials.iteritems():
 *         if text.texture:
 *             load_texture(os.path.join(model.root, text.texture))             # <<<<<<<<<<<<<<
 * 
 *     display = glGenLists(1)
 */
      __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s__load_texture); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_5 = __Pyx_GetModuleGlobalName(__pyx_n_s__os); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s__path); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_9, __pyx_n_s__join); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_text, __pyx_n_s__texture); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_10 = PyTuple_New(2); if (unlikely(!__pyx_t_10)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_10);
      __Pyx_INCREF(((PyObject *)__pyx_v_model->root));
      PyTuple_SET_ITEM(__pyx_t_10, 0, ((PyObject *)__pyx_v_model->root));
      __Pyx_GIVEREF(((PyObject *)__pyx_v_model->root));
      PyTuple_SET_ITEM(__pyx_t_10, 1, __pyx_t_9);
      __Pyx_GIVEREF(__pyx_t_9);
      __pyx_t_9 = 0;
      __pyx_t_9 = PyObject_Call(__pyx_t_5, ((PyObject *)__pyx_t_10), NULL); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __Pyx_DECREF(((PyObject *)__pyx_t_10)); __pyx_t_10 = 0;
      __pyx_t_10 = PyTuple_New(1); if (unlikely(!__pyx_t_10)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_10);
      PyTuple_SET_ITEM(__pyx_t_10, 0, __pyx_t_9);
      __Pyx_GIVEREF(__pyx_t_9);
      __pyx_t_9 = 0;
      __pyx_t_9 = PyObject_Call(__pyx_t_6, ((PyObject *)__pyx_t_10), NULL); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 29; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_DECREF(((PyObject *)__pyx_t_10)); __pyx_t_10 = 0;
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      goto __pyx_L5;
    }
    __pyx_L5:;
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "space_torus\cmodel.pyx":31
 *             load_texture(os.path.join(model.root, text.texture))
 * 
 *     display = glGenLists(1)             # <<<<<<<<<<<<<<
 * 
 *     glNewList(display, GL_COMPILE)
 */
  __pyx_v_display = glGenLists(1);

  /* "space_torus\cmodel.pyx":33
 *     display = glGenLists(1)
 * 
 *     glNewList(display, GL_COMPILE)             # <<<<<<<<<<<<<<
 *     glPushMatrix()
 *     glPushAttrib(GL_CURRENT_BIT)
 */
  glNewList(__pyx_v_display, __pyx_e_11space_torus_6cmodel_GL_COMPILE);

  /* "space_torus\cmodel.pyx":34
 * 
 *     glNewList(display, GL_COMPILE)
 *     glPushMatrix()             # <<<<<<<<<<<<<<
 *     glPushAttrib(GL_CURRENT_BIT)
 * 
 */
  glPushMatrix();

  /* "space_torus\cmodel.pyx":35
 *     glNewList(display, GL_COMPILE)
 *     glPushMatrix()
 *     glPushAttrib(GL_CURRENT_BIT)             # <<<<<<<<<<<<<<
 * 
 *     cdef float pitch, yaw, roll
 */
  glPushAttrib(__pyx_e_11space_torus_6cmodel_GL_CURRENT_BIT);

  /* "space_torus\cmodel.pyx":41
 *     cdef Face f
 * 
 *     pitch, yaw, roll = rotation             # <<<<<<<<<<<<<<
 *     glPushAttrib(GL_TRANSFORM_BIT)
 *     glRotatef(pitch, 1, 0, 0)
 */
  if (likely(PyTuple_CheckExact(((PyObject *)__pyx_v_rotation)))) {
    PyObject* sequence = ((PyObject *)__pyx_v_rotation);
    #if CYTHON_COMPILING_IN_CPYTHON
    Py_ssize_t size = Py_SIZE(sequence);
    #else
    Py_ssize_t size = PySequence_Size(sequence);
    #endif
    if (unlikely(size != 3)) {
      if (size > 3) __Pyx_RaiseTooManyValuesError(3);
      else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 41; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    #if CYTHON_COMPILING_IN_CPYTHON
    __pyx_t_1 = PyTuple_GET_ITEM(sequence, 0); 
    __pyx_t_9 = PyTuple_GET_ITEM(sequence, 1); 
    __pyx_t_10 = PyTuple_GET_ITEM(sequence, 2); 
    __Pyx_INCREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_t_9);
    __Pyx_INCREF(__pyx_t_10);
    #else
    __pyx_t_1 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 41; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_9 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 41; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_9);
    __pyx_t_10 = PySequence_ITEM(sequence, 2); if (unlikely(!__pyx_t_10)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 41; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_10);
    #endif
  } else if (1) {
    __Pyx_RaiseNoneNotIterableError(); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 41; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  } else
  {
    Py_ssize_t index = -1;
    __pyx_t_6 = PyObject_GetIter(((PyObject *)__pyx_v_rotation)); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 41; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_11 = Py_TYPE(__pyx_t_6)->tp_iternext;
    index = 0; __pyx_t_1 = __pyx_t_11(__pyx_t_6); if (unlikely(!__pyx_t_1)) goto __pyx_L6_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_1);
    index = 1; __pyx_t_9 = __pyx_t_11(__pyx_t_6); if (unlikely(!__pyx_t_9)) goto __pyx_L6_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_9);
    index = 2; __pyx_t_10 = __pyx_t_11(__pyx_t_6); if (unlikely(!__pyx_t_10)) goto __pyx_L6_unpacking_failed;
    __Pyx_GOTREF(__pyx_t_10);
    if (__Pyx_IternextUnpackEndCheck(__pyx_t_11(__pyx_t_6), 3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 41; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_11 = NULL;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    goto __pyx_L7_unpacking_done;
    __pyx_L6_unpacking_failed:;
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_11 = NULL;
    if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 41; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_L7_unpacking_done:;
  }
  __pyx_t_12 = __pyx_PyFloat_AsFloat(__pyx_t_1); if (unlikely((__pyx_t_12 == (float)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 41; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_13 = __pyx_PyFloat_AsFloat(__pyx_t_9); if (unlikely((__pyx_t_13 == (float)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 41; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
  __pyx_t_14 = __pyx_PyFloat_AsFloat(__pyx_t_10); if (unlikely((__pyx_t_14 == (float)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 41; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
  __pyx_v_pitch = __pyx_t_12;
  __pyx_v_yaw = __pyx_t_13;
  __pyx_v_roll = __pyx_t_14;

  /* "space_torus\cmodel.pyx":42
 * 
 *     pitch, yaw, roll = rotation
 *     glPushAttrib(GL_TRANSFORM_BIT)             # <<<<<<<<<<<<<<
 *     glRotatef(pitch, 1, 0, 0)
 *     glRotatef(yaw, 0, 1, 0)
 */
  glPushAttrib(__pyx_e_11space_torus_6cmodel_GL_TRANSFORM_BIT);

  /* "space_torus\cmodel.pyx":43
 *     pitch, yaw, roll = rotation
 *     glPushAttrib(GL_TRANSFORM_BIT)
 *     glRotatef(pitch, 1, 0, 0)             # <<<<<<<<<<<<<<
 *     glRotatef(yaw, 0, 1, 0)
 *     glRotatef(roll, 0, 0, 1)
 */
  glRotatef(__pyx_v_pitch, 1.0, 0.0, 0.0);

  /* "space_torus\cmodel.pyx":44
 *     glPushAttrib(GL_TRANSFORM_BIT)
 *     glRotatef(pitch, 1, 0, 0)
 *     glRotatef(yaw, 0, 1, 0)             # <<<<<<<<<<<<<<
 *     glRotatef(roll, 0, 0, 1)
 *     glPopAttrib()
 */
  glRotatef(__pyx_v_yaw, 0.0, 1.0, 0.0);

  /* "space_torus\cmodel.pyx":45
 *     glRotatef(pitch, 1, 0, 0)
 *     glRotatef(yaw, 0, 1, 0)
 *     glRotatef(roll, 0, 0, 1)             # <<<<<<<<<<<<<<
 *     glPopAttrib()
 * 
 */
  glRotatef(__pyx_v_roll, 0.0, 0.0, 1.0);

  /* "space_torus\cmodel.pyx":46
 *     glRotatef(yaw, 0, 1, 0)
 *     glRotatef(roll, 0, 0, 1)
 *     glPopAttrib()             # <<<<<<<<<<<<<<
 * 
 *     vertices = model.vertices
 */
  glPopAttrib();

  /* "space_torus\cmodel.pyx":48
 *     glPopAttrib()
 * 
 *     vertices = model.vertices             # <<<<<<<<<<<<<<
 *     textures = model.textures
 *     normals = model.normals
 */
  __pyx_t_10 = ((PyObject *)__pyx_v_model->vertices);
  __Pyx_INCREF(__pyx_t_10);
  __pyx_v_vertices = ((PyObject*)__pyx_t_10);
  __pyx_t_10 = 0;

  /* "space_torus\cmodel.pyx":49
 * 
 *     vertices = model.vertices
 *     textures = model.textures             # <<<<<<<<<<<<<<
 *     normals = model.normals
 * 
 */
  __pyx_t_10 = ((PyObject *)__pyx_v_model->textures);
  __Pyx_INCREF(__pyx_t_10);
  __pyx_v_textures = ((PyObject*)__pyx_t_10);
  __pyx_t_10 = 0;

  /* "space_torus\cmodel.pyx":50
 *     vertices = model.vertices
 *     textures = model.textures
 *     normals = model.normals             # <<<<<<<<<<<<<<
 * 
 *     for g in model.groups:
 */
  __pyx_t_10 = ((PyObject *)__pyx_v_model->normals);
  __Pyx_INCREF(__pyx_t_10);
  __pyx_v_normals = ((PyObject*)__pyx_t_10);
  __pyx_t_10 = 0;

  /* "space_torus\cmodel.pyx":52
 *     normals = model.normals
 * 
 *     for g in model.groups:             # <<<<<<<<<<<<<<
 *         material = g.material
 * 
 */
  if (unlikely(((PyObject *)__pyx_v_model->groups) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_10 = ((PyObject *)__pyx_v_model->groups); __Pyx_INCREF(__pyx_t_10); __pyx_t_3 = 0;
  for (;;) {
    if (__pyx_t_3 >= PyList_GET_SIZE(__pyx_t_10)) break;
    #if CYTHON_COMPILING_IN_CPYTHON
    __pyx_t_9 = PyList_GET_ITEM(__pyx_t_10, __pyx_t_3); __Pyx_INCREF(__pyx_t_9); __pyx_t_3++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    #else
    __pyx_t_9 = PySequence_ITEM(__pyx_t_10, __pyx_t_3); __pyx_t_3++; if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    #endif
    __Pyx_XDECREF_SET(__pyx_v_g, __pyx_t_9);
    __pyx_t_9 = 0;

    /* "space_torus\cmodel.pyx":53
 * 
 *     for g in model.groups:
 *         material = g.material             # <<<<<<<<<<<<<<
 * 
 *         tex_id = 0
 */
    __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_g, __pyx_n_s__material); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_9);
    __Pyx_XDECREF_SET(__pyx_v_material, __pyx_t_9);
    __pyx_t_9 = 0;

    /* "space_torus\cmodel.pyx":55
 *         material = g.material
 * 
 *         tex_id = 0             # <<<<<<<<<<<<<<
 *         tex_id = load_texture(os.path.join(model.root, material.texture)) if (material and material.texture) else 0
 * 
 */
    __Pyx_INCREF(__pyx_int_0);
    __Pyx_XDECREF_SET(__pyx_v_tex_id, __pyx_int_0);

    /* "space_torus\cmodel.pyx":56
 * 
 *         tex_id = 0
 *         tex_id = load_texture(os.path.join(model.root, material.texture)) if (material and material.texture) else 0             # <<<<<<<<<<<<<<
 * 
 *         if tex_id:
 */
    __pyx_t_8 = __Pyx_PyObject_IsTrue(__pyx_v_material); if (unlikely(__pyx_t_8 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    if (__pyx_t_8) {
      __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_material, __pyx_n_s__texture); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_15 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_15 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_16 = __pyx_t_15;
    } else {
      __pyx_t_16 = __pyx_t_8;
    }
    if (__pyx_t_16) {
      __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s__load_texture); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s__os); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_6);
      __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s__path); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_5, __pyx_n_s__join); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_5); __pyx_t_5 = 0;
      __pyx_t_5 = __Pyx_PyObject_GetAttrStr(__pyx_v_material, __pyx_n_s__texture); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __pyx_t_17 = PyTuple_New(2); if (unlikely(!__pyx_t_17)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_17);
      __Pyx_INCREF(((PyObject *)__pyx_v_model->root));
      PyTuple_SET_ITEM(__pyx_t_17, 0, ((PyObject *)__pyx_v_model->root));
      __Pyx_GIVEREF(((PyObject *)__pyx_v_model->root));
      PyTuple_SET_ITEM(__pyx_t_17, 1, __pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __pyx_t_5 = PyObject_Call(__pyx_t_6, ((PyObject *)__pyx_t_17), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_DECREF(((PyObject *)__pyx_t_17)); __pyx_t_17 = 0;
      __pyx_t_17 = PyTuple_New(1); if (unlikely(!__pyx_t_17)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_17);
      PyTuple_SET_ITEM(__pyx_t_17, 0, __pyx_t_5);
      __Pyx_GIVEREF(__pyx_t_5);
      __pyx_t_5 = 0;
      __pyx_t_5 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_t_17), NULL); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 56; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_5);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __Pyx_DECREF(((PyObject *)__pyx_t_17)); __pyx_t_17 = 0;
      __pyx_t_9 = __pyx_t_5;
      __pyx_t_5 = 0;
    } else {
      __Pyx_INCREF(__pyx_int_0);
      __pyx_t_9 = __pyx_int_0;
    }
    __Pyx_DECREF_SET(__pyx_v_tex_id, __pyx_t_9);
    __pyx_t_9 = 0;

    /* "space_torus\cmodel.pyx":58
 *         tex_id = load_texture(os.path.join(model.root, material.texture)) if (material and material.texture) else 0
 * 
 *         if tex_id:             # <<<<<<<<<<<<<<
 *             glEnable(GL_TEXTURE_2D)
 *             glBindTexture(GL_TEXTURE_2D, tex_id)
 */
    __pyx_t_16 = __Pyx_PyObject_IsTrue(__pyx_v_tex_id); if (unlikely(__pyx_t_16 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 58; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    if (__pyx_t_16) {

      /* "space_torus\cmodel.pyx":59
 * 
 *         if tex_id:
 *             glEnable(GL_TEXTURE_2D)             # <<<<<<<<<<<<<<
 *             glBindTexture(GL_TEXTURE_2D, tex_id)
 *         else:
 */
      glEnable(__pyx_e_11space_torus_6cmodel_GL_TEXTURE_2D);

      /* "space_torus\cmodel.pyx":60
 *         if tex_id:
 *             glEnable(GL_TEXTURE_2D)
 *             glBindTexture(GL_TEXTURE_2D, tex_id)             # <<<<<<<<<<<<<<
 *         else:
 *             glBindTexture(GL_TEXTURE_2D, 0)
 */
      __pyx_t_18 = __Pyx_PyInt_from_py_GLuint(__pyx_v_tex_id); if (unlikely((__pyx_t_18 == (GLuint)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 60; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      glBindTexture(__pyx_e_11space_torus_6cmodel_GL_TEXTURE_2D, __pyx_t_18);
      goto __pyx_L10;
    }
    /*else*/ {

      /* "space_torus\cmodel.pyx":62
 *             glBindTexture(GL_TEXTURE_2D, tex_id)
 *         else:
 *             glBindTexture(GL_TEXTURE_2D, 0)             # <<<<<<<<<<<<<<
 *             glDisable(GL_TEXTURE_2D)
 * 
 */
      glBindTexture(__pyx_e_11space_torus_6cmodel_GL_TEXTURE_2D, 0);

      /* "space_torus\cmodel.pyx":63
 *         else:
 *             glBindTexture(GL_TEXTURE_2D, 0)
 *             glDisable(GL_TEXTURE_2D)             # <<<<<<<<<<<<<<
 * 
 *         if material:
 */
      glDisable(__pyx_e_11space_torus_6cmodel_GL_TEXTURE_2D);
    }
    __pyx_L10:;

    /* "space_torus\cmodel.pyx":65
 *             glDisable(GL_TEXTURE_2D)
 * 
 *         if material:             # <<<<<<<<<<<<<<
 *             if material.Ka:
 *                 kx, ky, kz = material.Ka
 */
    __pyx_t_16 = __Pyx_PyObject_IsTrue(__pyx_v_material); if (unlikely(__pyx_t_16 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 65; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    if (__pyx_t_16) {

      /* "space_torus\cmodel.pyx":66
 * 
 *         if material:
 *             if material.Ka:             # <<<<<<<<<<<<<<
 *                 kx, ky, kz = material.Ka
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [kx, ky, kz, 1])
 */
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_material, __pyx_n_s__Ka); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 66; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_16 = __Pyx_PyObject_IsTrue(__pyx_t_9); if (unlikely(__pyx_t_16 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 66; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      if (__pyx_t_16) {

        /* "space_torus\cmodel.pyx":67
 *         if material:
 *             if material.Ka:
 *                 kx, ky, kz = material.Ka             # <<<<<<<<<<<<<<
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [kx, ky, kz, 1])
 *             if material.Kd:
 */
        __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_material, __pyx_n_s__Ka); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 67; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_9);
        if ((likely(PyTuple_CheckExact(__pyx_t_9))) || (PyList_CheckExact(__pyx_t_9))) {
          PyObject* sequence = __pyx_t_9;
          #if CYTHON_COMPILING_IN_CPYTHON
          Py_ssize_t size = Py_SIZE(sequence);
          #else
          Py_ssize_t size = PySequence_Size(sequence);
          #endif
          if (unlikely(size != 3)) {
            if (size > 3) __Pyx_RaiseTooManyValuesError(3);
            else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
            {__pyx_filename = __pyx_f[0]; __pyx_lineno = 67; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          }
          #if CYTHON_COMPILING_IN_CPYTHON
          if (likely(PyTuple_CheckExact(sequence))) {
            __pyx_t_5 = PyTuple_GET_ITEM(sequence, 0); 
            __pyx_t_17 = PyTuple_GET_ITEM(sequence, 1); 
            __pyx_t_1 = PyTuple_GET_ITEM(sequence, 2); 
          } else {
            __pyx_t_5 = PyList_GET_ITEM(sequence, 0); 
            __pyx_t_17 = PyList_GET_ITEM(sequence, 1); 
            __pyx_t_1 = PyList_GET_ITEM(sequence, 2); 
          }
          __Pyx_INCREF(__pyx_t_5);
          __Pyx_INCREF(__pyx_t_17);
          __Pyx_INCREF(__pyx_t_1);
          #else
          __pyx_t_5 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 67; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_5);
          __pyx_t_17 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_17)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 67; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_17);
          __pyx_t_1 = PySequence_ITEM(sequence, 2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 67; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_1);
          #endif
          __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
        } else
        {
          Py_ssize_t index = -1;
          __pyx_t_6 = PyObject_GetIter(__pyx_t_9); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 67; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
          __pyx_t_11 = Py_TYPE(__pyx_t_6)->tp_iternext;
          index = 0; __pyx_t_5 = __pyx_t_11(__pyx_t_6); if (unlikely(!__pyx_t_5)) goto __pyx_L13_unpacking_failed;
          __Pyx_GOTREF(__pyx_t_5);
          index = 1; __pyx_t_17 = __pyx_t_11(__pyx_t_6); if (unlikely(!__pyx_t_17)) goto __pyx_L13_unpacking_failed;
          __Pyx_GOTREF(__pyx_t_17);
          index = 2; __pyx_t_1 = __pyx_t_11(__pyx_t_6); if (unlikely(!__pyx_t_1)) goto __pyx_L13_unpacking_failed;
          __Pyx_GOTREF(__pyx_t_1);
          if (__Pyx_IternextUnpackEndCheck(__pyx_t_11(__pyx_t_6), 3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 67; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __pyx_t_11 = NULL;
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          goto __pyx_L14_unpacking_done;
          __pyx_L13_unpacking_failed:;
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          __pyx_t_11 = NULL;
          if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
          {__pyx_filename = __pyx_f[0]; __pyx_lineno = 67; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __pyx_L14_unpacking_done:;
        }
        __Pyx_XDECREF_SET(__pyx_v_kx, __pyx_t_5);
        __pyx_t_5 = 0;
        __Pyx_XDECREF_SET(__pyx_v_ky, __pyx_t_17);
        __pyx_t_17 = 0;
        __Pyx_XDECREF_SET(__pyx_v_kz, __pyx_t_1);
        __pyx_t_1 = 0;

        /* "space_torus\cmodel.pyx":68
 *             if material.Ka:
 *                 kx, ky, kz = material.Ka
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [kx, ky, kz, 1])             # <<<<<<<<<<<<<<
 *             if material.Kd:
 *                 kx, ky, kz = material.Kd
 */
        __pyx_t_19 = __pyx_PyFloat_AsFloat(__pyx_v_kx); if (unlikely((__pyx_t_19 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __pyx_t_20 = __pyx_PyFloat_AsFloat(__pyx_v_ky); if (unlikely((__pyx_t_20 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __pyx_t_21 = __pyx_PyFloat_AsFloat(__pyx_v_kz); if (unlikely((__pyx_t_21 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __pyx_t_22[0] = __pyx_t_19;
        __pyx_t_22[1] = __pyx_t_20;
        __pyx_t_22[2] = __pyx_t_21;
        __pyx_t_22[3] = 1.0;
        glMaterialfv(__pyx_e_11space_torus_6cmodel_GL_FRONT_AND_BACK, __pyx_e_11space_torus_6cmodel_GL_AMBIENT, __pyx_t_22);
        goto __pyx_L12;
      }
      __pyx_L12:;

      /* "space_torus\cmodel.pyx":69
 *                 kx, ky, kz = material.Ka
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [kx, ky, kz, 1])
 *             if material.Kd:             # <<<<<<<<<<<<<<
 *                 kx, ky, kz = material.Kd
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [kx, ky, kz, 1])
 */
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_material, __pyx_n_s__Kd); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 69; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_16 = __Pyx_PyObject_IsTrue(__pyx_t_9); if (unlikely(__pyx_t_16 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 69; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      if (__pyx_t_16) {

        /* "space_torus\cmodel.pyx":70
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, [kx, ky, kz, 1])
 *             if material.Kd:
 *                 kx, ky, kz = material.Kd             # <<<<<<<<<<<<<<
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [kx, ky, kz, 1])
 *             if material.Ks:
 */
        __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_material, __pyx_n_s__Kd); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 70; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_9);
        if ((likely(PyTuple_CheckExact(__pyx_t_9))) || (PyList_CheckExact(__pyx_t_9))) {
          PyObject* sequence = __pyx_t_9;
          #if CYTHON_COMPILING_IN_CPYTHON
          Py_ssize_t size = Py_SIZE(sequence);
          #else
          Py_ssize_t size = PySequence_Size(sequence);
          #endif
          if (unlikely(size != 3)) {
            if (size > 3) __Pyx_RaiseTooManyValuesError(3);
            else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
            {__pyx_filename = __pyx_f[0]; __pyx_lineno = 70; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          }
          #if CYTHON_COMPILING_IN_CPYTHON
          if (likely(PyTuple_CheckExact(sequence))) {
            __pyx_t_1 = PyTuple_GET_ITEM(sequence, 0); 
            __pyx_t_17 = PyTuple_GET_ITEM(sequence, 1); 
            __pyx_t_5 = PyTuple_GET_ITEM(sequence, 2); 
          } else {
            __pyx_t_1 = PyList_GET_ITEM(sequence, 0); 
            __pyx_t_17 = PyList_GET_ITEM(sequence, 1); 
            __pyx_t_5 = PyList_GET_ITEM(sequence, 2); 
          }
          __Pyx_INCREF(__pyx_t_1);
          __Pyx_INCREF(__pyx_t_17);
          __Pyx_INCREF(__pyx_t_5);
          #else
          __pyx_t_1 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 70; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_1);
          __pyx_t_17 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_17)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 70; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_17);
          __pyx_t_5 = PySequence_ITEM(sequence, 2); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 70; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_5);
          #endif
          __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
        } else
        {
          Py_ssize_t index = -1;
          __pyx_t_6 = PyObject_GetIter(__pyx_t_9); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 70; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
          __pyx_t_11 = Py_TYPE(__pyx_t_6)->tp_iternext;
          index = 0; __pyx_t_1 = __pyx_t_11(__pyx_t_6); if (unlikely(!__pyx_t_1)) goto __pyx_L16_unpacking_failed;
          __Pyx_GOTREF(__pyx_t_1);
          index = 1; __pyx_t_17 = __pyx_t_11(__pyx_t_6); if (unlikely(!__pyx_t_17)) goto __pyx_L16_unpacking_failed;
          __Pyx_GOTREF(__pyx_t_17);
          index = 2; __pyx_t_5 = __pyx_t_11(__pyx_t_6); if (unlikely(!__pyx_t_5)) goto __pyx_L16_unpacking_failed;
          __Pyx_GOTREF(__pyx_t_5);
          if (__Pyx_IternextUnpackEndCheck(__pyx_t_11(__pyx_t_6), 3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 70; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __pyx_t_11 = NULL;
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          goto __pyx_L17_unpacking_done;
          __pyx_L16_unpacking_failed:;
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          __pyx_t_11 = NULL;
          if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
          {__pyx_filename = __pyx_f[0]; __pyx_lineno = 70; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __pyx_L17_unpacking_done:;
        }
        __Pyx_XDECREF_SET(__pyx_v_kx, __pyx_t_1);
        __pyx_t_1 = 0;
        __Pyx_XDECREF_SET(__pyx_v_ky, __pyx_t_17);
        __pyx_t_17 = 0;
        __Pyx_XDECREF_SET(__pyx_v_kz, __pyx_t_5);
        __pyx_t_5 = 0;

        /* "space_torus\cmodel.pyx":71
 *             if material.Kd:
 *                 kx, ky, kz = material.Kd
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [kx, ky, kz, 1])             # <<<<<<<<<<<<<<
 *             if material.Ks:
 *                 kx, ky, kz = material.Ks
 */
        __pyx_t_21 = __pyx_PyFloat_AsFloat(__pyx_v_kx); if (unlikely((__pyx_t_21 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 71; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __pyx_t_20 = __pyx_PyFloat_AsFloat(__pyx_v_ky); if (unlikely((__pyx_t_20 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 71; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __pyx_t_19 = __pyx_PyFloat_AsFloat(__pyx_v_kz); if (unlikely((__pyx_t_19 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 71; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __pyx_t_23[0] = __pyx_t_21;
        __pyx_t_23[1] = __pyx_t_20;
        __pyx_t_23[2] = __pyx_t_19;
        __pyx_t_23[3] = 1.0;
        glMaterialfv(__pyx_e_11space_torus_6cmodel_GL_FRONT_AND_BACK, __pyx_e_11space_torus_6cmodel_GL_DIFFUSE, __pyx_t_23);
        goto __pyx_L15;
      }
      __pyx_L15:;

      /* "space_torus\cmodel.pyx":72
 *                 kx, ky, kz = material.Kd
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [kx, ky, kz, 1])
 *             if material.Ks:             # <<<<<<<<<<<<<<
 *                 kx, ky, kz = material.Ks
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [kx, ky, kz, 1])
 */
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_material, __pyx_n_s__Ks); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 72; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_16 = __Pyx_PyObject_IsTrue(__pyx_t_9); if (unlikely(__pyx_t_16 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 72; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      if (__pyx_t_16) {

        /* "space_torus\cmodel.pyx":73
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, [kx, ky, kz, 1])
 *             if material.Ks:
 *                 kx, ky, kz = material.Ks             # <<<<<<<<<<<<<<
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [kx, ky, kz, 1])
 *             glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess)
 */
        __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_material, __pyx_n_s__Ks); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_9);
        if ((likely(PyTuple_CheckExact(__pyx_t_9))) || (PyList_CheckExact(__pyx_t_9))) {
          PyObject* sequence = __pyx_t_9;
          #if CYTHON_COMPILING_IN_CPYTHON
          Py_ssize_t size = Py_SIZE(sequence);
          #else
          Py_ssize_t size = PySequence_Size(sequence);
          #endif
          if (unlikely(size != 3)) {
            if (size > 3) __Pyx_RaiseTooManyValuesError(3);
            else if (size >= 0) __Pyx_RaiseNeedMoreValuesError(size);
            {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          }
          #if CYTHON_COMPILING_IN_CPYTHON
          if (likely(PyTuple_CheckExact(sequence))) {
            __pyx_t_5 = PyTuple_GET_ITEM(sequence, 0); 
            __pyx_t_17 = PyTuple_GET_ITEM(sequence, 1); 
            __pyx_t_1 = PyTuple_GET_ITEM(sequence, 2); 
          } else {
            __pyx_t_5 = PyList_GET_ITEM(sequence, 0); 
            __pyx_t_17 = PyList_GET_ITEM(sequence, 1); 
            __pyx_t_1 = PyList_GET_ITEM(sequence, 2); 
          }
          __Pyx_INCREF(__pyx_t_5);
          __Pyx_INCREF(__pyx_t_17);
          __Pyx_INCREF(__pyx_t_1);
          #else
          __pyx_t_5 = PySequence_ITEM(sequence, 0); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_5);
          __pyx_t_17 = PySequence_ITEM(sequence, 1); if (unlikely(!__pyx_t_17)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_17);
          __pyx_t_1 = PySequence_ITEM(sequence, 2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_1);
          #endif
          __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
        } else
        {
          Py_ssize_t index = -1;
          __pyx_t_6 = PyObject_GetIter(__pyx_t_9); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
          __pyx_t_11 = Py_TYPE(__pyx_t_6)->tp_iternext;
          index = 0; __pyx_t_5 = __pyx_t_11(__pyx_t_6); if (unlikely(!__pyx_t_5)) goto __pyx_L19_unpacking_failed;
          __Pyx_GOTREF(__pyx_t_5);
          index = 1; __pyx_t_17 = __pyx_t_11(__pyx_t_6); if (unlikely(!__pyx_t_17)) goto __pyx_L19_unpacking_failed;
          __Pyx_GOTREF(__pyx_t_17);
          index = 2; __pyx_t_1 = __pyx_t_11(__pyx_t_6); if (unlikely(!__pyx_t_1)) goto __pyx_L19_unpacking_failed;
          __Pyx_GOTREF(__pyx_t_1);
          if (__Pyx_IternextUnpackEndCheck(__pyx_t_11(__pyx_t_6), 3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __pyx_t_11 = NULL;
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          goto __pyx_L20_unpacking_done;
          __pyx_L19_unpacking_failed:;
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          __pyx_t_11 = NULL;
          if (__Pyx_IterFinish() == 0) __Pyx_RaiseNeedMoreValuesError(index);
          {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          __pyx_L20_unpacking_done:;
        }
        __Pyx_XDECREF_SET(__pyx_v_kx, __pyx_t_5);
        __pyx_t_5 = 0;
        __Pyx_XDECREF_SET(__pyx_v_ky, __pyx_t_17);
        __pyx_t_17 = 0;
        __Pyx_XDECREF_SET(__pyx_v_kz, __pyx_t_1);
        __pyx_t_1 = 0;

        /* "space_torus\cmodel.pyx":74
 *             if material.Ks:
 *                 kx, ky, kz = material.Ks
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [kx, ky, kz, 1])             # <<<<<<<<<<<<<<
 *             glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess)
 * 
 */
        __pyx_t_19 = __pyx_PyFloat_AsFloat(__pyx_v_kx); if (unlikely((__pyx_t_19 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 74; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __pyx_t_20 = __pyx_PyFloat_AsFloat(__pyx_v_ky); if (unlikely((__pyx_t_20 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 74; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __pyx_t_21 = __pyx_PyFloat_AsFloat(__pyx_v_kz); if (unlikely((__pyx_t_21 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 74; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __pyx_t_24[0] = __pyx_t_19;
        __pyx_t_24[1] = __pyx_t_20;
        __pyx_t_24[2] = __pyx_t_21;
        __pyx_t_24[3] = 1.0;
        glMaterialfv(__pyx_e_11space_torus_6cmodel_GL_FRONT_AND_BACK, __pyx_e_11space_torus_6cmodel_GL_SPECULAR, __pyx_t_24);
        goto __pyx_L18;
      }
      __pyx_L18:;

      /* "space_torus\cmodel.pyx":75
 *                 kx, ky, kz = material.Ks
 *                 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, [kx, ky, kz, 1])
 *             glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess)             # <<<<<<<<<<<<<<
 * 
 *         type = -1
 */
      __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_material, __pyx_n_s__shininess); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 75; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __pyx_t_21 = __pyx_PyFloat_AsFloat(__pyx_t_9); if (unlikely((__pyx_t_21 == (GLfloat)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 75; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
      glMaterialf(__pyx_e_11space_torus_6cmodel_GL_FRONT_AND_BACK, __pyx_e_11space_torus_6cmodel_GL_SHININESS, __pyx_t_21);
      goto __pyx_L11;
    }
    __pyx_L11:;

    /* "space_torus\cmodel.pyx":77
 *             glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess)
 * 
 *         type = -1             # <<<<<<<<<<<<<<
 * 
 *         for f in g.faces:
 */
    __pyx_v_type = -1;

    /* "space_torus\cmodel.pyx":79
 *         type = -1
 * 
 *         for f in g.faces:             # <<<<<<<<<<<<<<
 *             if type != f.type:
 *                 if type != -1:
 */
    __pyx_t_9 = __Pyx_PyObject_GetAttrStr(__pyx_v_g, __pyx_n_s__faces); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 79; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_9);
    if (PyList_CheckExact(__pyx_t_9) || PyTuple_CheckExact(__pyx_t_9)) {
      __pyx_t_1 = __pyx_t_9; __Pyx_INCREF(__pyx_t_1); __pyx_t_2 = 0;
      __pyx_t_25 = NULL;
    } else {
      __pyx_t_2 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_t_9); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 79; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_25 = Py_TYPE(__pyx_t_1)->tp_iternext;
    }
    __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
    for (;;) {
      if (!__pyx_t_25 && PyList_CheckExact(__pyx_t_1)) {
        if (__pyx_t_2 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_9 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_9); __pyx_t_2++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 79; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        #else
        __pyx_t_9 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 79; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        #endif
      } else if (!__pyx_t_25 && PyTuple_CheckExact(__pyx_t_1)) {
        if (__pyx_t_2 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_COMPILING_IN_CPYTHON
        __pyx_t_9 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_2); __Pyx_INCREF(__pyx_t_9); __pyx_t_2++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 79; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        #else
        __pyx_t_9 = PySequence_ITEM(__pyx_t_1, __pyx_t_2); __pyx_t_2++; if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 79; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        #endif
      } else {
        __pyx_t_9 = __pyx_t_25(__pyx_t_1);
        if (unlikely(!__pyx_t_9)) {
          if (PyErr_Occurred()) {
            if (likely(PyErr_ExceptionMatches(PyExc_StopIteration))) PyErr_Clear();
            else {__pyx_filename = __pyx_f[0]; __pyx_lineno = 79; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_9);
      }
      if (!(likely(((__pyx_t_9) == Py_None) || likely(__Pyx_TypeTest(__pyx_t_9, __pyx_ptype_11space_torus_6cmodel_Face))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 79; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_XDECREF_SET(__pyx_v_f, ((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_t_9));
      __pyx_t_9 = 0;

      /* "space_torus\cmodel.pyx":80
 * 
 *         for f in g.faces:
 *             if type != f.type:             # <<<<<<<<<<<<<<
 *                 if type != -1:
 *                     pass#glEnd()
 */
      __pyx_t_16 = ((__pyx_v_type != __pyx_v_f->type) != 0);
      if (__pyx_t_16) {

        /* "space_torus\cmodel.pyx":81
 *         for f in g.faces:
 *             if type != f.type:
 *                 if type != -1:             # <<<<<<<<<<<<<<
 *                     pass#glEnd()
 *             glBegin(GL_TRIANGLES)
 */
        __pyx_t_16 = ((__pyx_v_type != -1) != 0);
        if (__pyx_t_16) {
          goto __pyx_L24;
        }
        __pyx_L24:;
        goto __pyx_L23;
      }
      __pyx_L23:;

      /* "space_torus\cmodel.pyx":83
 *                 if type != -1:
 *                     pass#glEnd()
 *             glBegin(GL_TRIANGLES)             # <<<<<<<<<<<<<<
 *             type = f.type
 * 
 */
      glBegin(__pyx_e_11space_torus_6cmodel_GL_TRIANGLES);

      /* "space_torus\cmodel.pyx":84
 *                     pass#glEnd()
 *             glBegin(GL_TRIANGLES)
 *             type = f.type             # <<<<<<<<<<<<<<
 * 
 *             point(f, vertices, normals, textures, sx, sy, sz, 0, tex_id)
 */
      __pyx_t_4 = __pyx_v_f->type;
      __pyx_v_type = __pyx_t_4;

      /* "space_torus\cmodel.pyx":86
 *             type = f.type
 * 
 *             point(f, vertices, normals, textures, sx, sy, sz, 0, tex_id)             # <<<<<<<<<<<<<<
 *             point(f, vertices, normals, textures, sx, sy, sz, 1, tex_id)
 *             point(f, vertices, normals, textures, sx, sy, sz, 2, tex_id)
 */
      __pyx_t_4 = __Pyx_PyInt_AsInt(__pyx_v_tex_id); if (unlikely((__pyx_t_4 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 86; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __pyx_t_9 = __pyx_f_11space_torus_6cmodel_point(__pyx_v_f, __pyx_v_vertices, __pyx_v_normals, __pyx_v_textures, __pyx_v_sx, __pyx_v_sy, __pyx_v_sz, 0, __pyx_t_4); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 86; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;

      /* "space_torus\cmodel.pyx":87
 * 
 *             point(f, vertices, normals, textures, sx, sy, sz, 0, tex_id)
 *             point(f, vertices, normals, textures, sx, sy, sz, 1, tex_id)             # <<<<<<<<<<<<<<
 *             point(f, vertices, normals, textures, sx, sy, sz, 2, tex_id)
 * 
 */
      __pyx_t_4 = __Pyx_PyInt_AsInt(__pyx_v_tex_id); if (unlikely((__pyx_t_4 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 87; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __pyx_t_9 = __pyx_f_11space_torus_6cmodel_point(__pyx_v_f, __pyx_v_vertices, __pyx_v_normals, __pyx_v_textures, __pyx_v_sx, __pyx_v_sy, __pyx_v_sz, 1, __pyx_t_4); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 87; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;

      /* "space_torus\cmodel.pyx":88
 *             point(f, vertices, normals, textures, sx, sy, sz, 0, tex_id)
 *             point(f, vertices, normals, textures, sx, sy, sz, 1, tex_id)
 *             point(f, vertices, normals, textures, sx, sy, sz, 2, tex_id)             # <<<<<<<<<<<<<<
 * 
 *             if type == FACE_QUADS:
 */
      __pyx_t_4 = __Pyx_PyInt_AsInt(__pyx_v_tex_id); if (unlikely((__pyx_t_4 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 88; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __pyx_t_9 = __pyx_f_11space_torus_6cmodel_point(__pyx_v_f, __pyx_v_vertices, __pyx_v_normals, __pyx_v_textures, __pyx_v_sx, __pyx_v_sy, __pyx_v_sz, 2, __pyx_t_4); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 88; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_9);
      __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;

      /* "space_torus\cmodel.pyx":90
 *             point(f, vertices, normals, textures, sx, sy, sz, 2, tex_id)
 * 
 *             if type == FACE_QUADS:             # <<<<<<<<<<<<<<
 *                 point(f, vertices, normals, textures, sx, sy, sz, 2, tex_id)
 *                 point(f, vertices, normals, textures, sx, sy, sz, 3, tex_id)
 */
      __pyx_t_16 = ((__pyx_v_type == __pyx_e_11space_torus_6cmodel_FACE_QUADS) != 0);
      if (__pyx_t_16) {

        /* "space_torus\cmodel.pyx":91
 * 
 *             if type == FACE_QUADS:
 *                 point(f, vertices, normals, textures, sx, sy, sz, 2, tex_id)             # <<<<<<<<<<<<<<
 *                 point(f, vertices, normals, textures, sx, sy, sz, 3, tex_id)
 *                 point(f, vertices, normals, textures, sx, sy, sz, 0, tex_id)
 */
        __pyx_t_4 = __Pyx_PyInt_AsInt(__pyx_v_tex_id); if (unlikely((__pyx_t_4 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 91; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __pyx_t_9 = __pyx_f_11space_torus_6cmodel_point(__pyx_v_f, __pyx_v_vertices, __pyx_v_normals, __pyx_v_textures, __pyx_v_sx, __pyx_v_sy, __pyx_v_sz, 2, __pyx_t_4); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 91; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_9);
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;

        /* "space_torus\cmodel.pyx":92
 *             if type == FACE_QUADS:
 *                 point(f, vertices, normals, textures, sx, sy, sz, 2, tex_id)
 *                 point(f, vertices, normals, textures, sx, sy, sz, 3, tex_id)             # <<<<<<<<<<<<<<
 *                 point(f, vertices, normals, textures, sx, sy, sz, 0, tex_id)
 *             glEnd()
 */
        __pyx_t_4 = __Pyx_PyInt_AsInt(__pyx_v_tex_id); if (unlikely((__pyx_t_4 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 92; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __pyx_t_9 = __pyx_f_11space_torus_6cmodel_point(__pyx_v_f, __pyx_v_vertices, __pyx_v_normals, __pyx_v_textures, __pyx_v_sx, __pyx_v_sy, __pyx_v_sz, 3, __pyx_t_4); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 92; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_9);
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;

        /* "space_torus\cmodel.pyx":93
 *                 point(f, vertices, normals, textures, sx, sy, sz, 2, tex_id)
 *                 point(f, vertices, normals, textures, sx, sy, sz, 3, tex_id)
 *                 point(f, vertices, normals, textures, sx, sy, sz, 0, tex_id)             # <<<<<<<<<<<<<<
 *             glEnd()
 *         #glEnd()
 */
        __pyx_t_4 = __Pyx_PyInt_AsInt(__pyx_v_tex_id); if (unlikely((__pyx_t_4 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 93; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __pyx_t_9 = __pyx_f_11space_torus_6cmodel_point(__pyx_v_f, __pyx_v_vertices, __pyx_v_normals, __pyx_v_textures, __pyx_v_sx, __pyx_v_sy, __pyx_v_sz, 0, __pyx_t_4); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 93; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_9);
        __Pyx_DECREF(__pyx_t_9); __pyx_t_9 = 0;
        goto __pyx_L25;
      }
      __pyx_L25:;

      /* "space_torus\cmodel.pyx":94
 *                 point(f, vertices, normals, textures, sx, sy, sz, 3, tex_id)
 *                 point(f, vertices, normals, textures, sx, sy, sz, 0, tex_id)
 *             glEnd()             # <<<<<<<<<<<<<<
 *         #glEnd()
 * 
 */
      glEnd();
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  }
  __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;

  /* "space_torus\cmodel.pyx":97
 *         #glEnd()
 * 
 *     glPopAttrib()             # <<<<<<<<<<<<<<
 *     glPopMatrix()
 * 
 */
  glPopAttrib();

  /* "space_torus\cmodel.pyx":98
 * 
 *     glPopAttrib()
 *     glPopMatrix()             # <<<<<<<<<<<<<<
 * 
 *     glEndList()
 */
  glPopMatrix();

  /* "space_torus\cmodel.pyx":100
 *     glPopMatrix()
 * 
 *     glEndList()             # <<<<<<<<<<<<<<
 *     return display
 * 
 */
  glEndList();

  /* "space_torus\cmodel.pyx":101
 * 
 *     glEndList()
 *     return display             # <<<<<<<<<<<<<<
 * 
 * def load_model(path):
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_10 = __Pyx_PyInt_to_py_GLuint(__pyx_v_display); if (unlikely(!__pyx_t_10)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 101; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_10);
  __pyx_r = __pyx_t_10;
  __pyx_t_10 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_XDECREF(__pyx_t_17);
  __Pyx_AddTraceback("space_torus.cmodel.model_list", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_m);
  __Pyx_XDECREF(__pyx_v_text);
  __Pyx_XDECREF(__pyx_v_kx);
  __Pyx_XDECREF(__pyx_v_ky);
  __Pyx_XDECREF(__pyx_v_kz);
  __Pyx_XDECREF((PyObject *)__pyx_v_f);
  __Pyx_XDECREF(__pyx_v_vertices);
  __Pyx_XDECREF(__pyx_v_textures);
  __Pyx_XDECREF(__pyx_v_normals);
  __Pyx_XDECREF(__pyx_v_g);
  __Pyx_XDECREF(__pyx_v_material);
  __Pyx_XDECREF(__pyx_v_tex_id);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_1model_list(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_1model_list(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_model = 0;
  float __pyx_v_sx;
  float __pyx_v_sy;
  float __pyx_v_sz;
  PyObject *__pyx_v_rotation = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("model_list (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__model,&__pyx_n_s__sx,&__pyx_n_s__sy,&__pyx_n_s__sz,&__pyx_n_s__rotation,0};
    PyObject* values[5] = {0,0,0,0,0};

    /* "space_torus\cmodel.pyx":26
 *     glVertex3f(x * sx, y * sy, z * sz)
 * 
 * cpdef model_list(WavefrontObject model, float sx=1, float sy=1, float sz=1, tuple rotation=(0, 0, 0)):             # <<<<<<<<<<<<<<
 *     for m, text in model.materials.iteritems():
 *         if text.texture:
 */
    values[4] = ((PyObject*)__pyx_k_tuple_2);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__model)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__sx);
          if (value) { values[1] = value; kw_args--; }
        }
        case  2:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__sy);
          if (value) { values[2] = value; kw_args--; }
        }
        case  3:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__sz);
          if (value) { values[3] = value; kw_args--; }
        }
        case  4:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__rotation);
          if (value) { values[4] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "model_list") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_model = ((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)values[0]);
    if (values[1]) {
      __pyx_v_sx = __pyx_PyFloat_AsFloat(values[1]); if (unlikely((__pyx_v_sx == (float)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
    } else {
      __pyx_v_sx = ((float)1.0);
    }
    if (values[2]) {
      __pyx_v_sy = __pyx_PyFloat_AsFloat(values[2]); if (unlikely((__pyx_v_sy == (float)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
    } else {
      __pyx_v_sy = ((float)1.0);
    }
    if (values[3]) {
      __pyx_v_sz = __pyx_PyFloat_AsFloat(values[3]); if (unlikely((__pyx_v_sz == (float)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
    } else {
      __pyx_v_sz = ((float)1.0);
    }
    __pyx_v_rotation = ((PyObject*)values[4]);
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("model_list", 0, 1, 5, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("space_torus.cmodel.model_list", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return NULL;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_model), __pyx_ptype_11space_torus_6cmodel_WavefrontObject, 1, "model", 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_rotation), (&PyTuple_Type), 1, "rotation", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_r = __pyx_pf_11space_torus_6cmodel_model_list(__pyx_self, __pyx_v_model, __pyx_v_sx, __pyx_v_sy, __pyx_v_sz, __pyx_v_rotation);
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_model_list(CYTHON_UNUSED PyObject *__pyx_self, struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_model, float __pyx_v_sx, float __pyx_v_sy, float __pyx_v_sz, PyObject *__pyx_v_rotation) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  struct __pyx_opt_args_11space_torus_6cmodel_model_list __pyx_t_2;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("model_list", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_2.__pyx_n = 4;
  __pyx_t_2.sx = __pyx_v_sx;
  __pyx_t_2.sy = __pyx_v_sy;
  __pyx_t_2.sz = __pyx_v_sz;
  __pyx_t_2.rotation = __pyx_v_rotation;
  __pyx_t_1 = __pyx_f_11space_torus_6cmodel_model_list(__pyx_v_model, 0, &__pyx_t_2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("space_torus.cmodel.model_list", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_3load_model(PyObject *__pyx_self, PyObject *__pyx_v_path); /*proto*/
static PyMethodDef __pyx_mdef_11space_torus_6cmodel_3load_model = {__Pyx_NAMESTR("load_model"), (PyCFunction)__pyx_pw_11space_torus_6cmodel_3load_model, METH_O, __Pyx_DOCSTR(0)};
static PyObject *__pyx_pw_11space_torus_6cmodel_3load_model(PyObject *__pyx_self, PyObject *__pyx_v_path) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("load_model (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_2load_model(__pyx_self, ((PyObject *)__pyx_v_path));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":103
 *     return display
 * 
 * def load_model(path):             # <<<<<<<<<<<<<<
 *     print "Loading model %s..." % path
 *     return WavefrontObject(os.path.join(os.path.dirname(__file__), 'assets', 'models', path))
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_2load_model(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_path) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("load_model", 0);

  /* "space_torus\cmodel.pyx":104
 * 
 * def load_model(path):
 *     print "Loading model %s..." % path             # <<<<<<<<<<<<<<
 *     return WavefrontObject(os.path.join(os.path.dirname(__file__), 'assets', 'models', path))
 * 
 */
  __pyx_t_1 = PyNumber_Remainder(((PyObject *)__pyx_kp_s_3), __pyx_v_path); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 104; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_1));
  if (__Pyx_PrintOne(0, ((PyObject *)__pyx_t_1)) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 104; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;

  /* "space_torus\cmodel.pyx":105
 * def load_model(path):
 *     print "Loading model %s..." % path
 *     return WavefrontObject(os.path.join(os.path.dirname(__file__), 'assets', 'models', path))             # <<<<<<<<<<<<<<
 * 
 * cdef class WavefrontObject(object):
 */
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s__os); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s__path); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s__join); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s__os); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s__path); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s__dirname); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s____file__); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_t_4), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
  __pyx_t_4 = PyTuple_New(4); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__assets));
  PyTuple_SET_ITEM(__pyx_t_4, 1, ((PyObject *)__pyx_n_s__assets));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__assets));
  __Pyx_INCREF(((PyObject *)__pyx_n_s__models));
  PyTuple_SET_ITEM(__pyx_t_4, 2, ((PyObject *)__pyx_n_s__models));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__models));
  __Pyx_INCREF(__pyx_v_path);
  PyTuple_SET_ITEM(__pyx_t_4, 3, __pyx_v_path);
  __Pyx_GIVEREF(__pyx_v_path);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_t_4), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
  __pyx_t_4 = PyTuple_New(1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  __pyx_t_3 = 0;
  __pyx_t_3 = PyObject_Call(((PyObject *)((PyObject*)__pyx_ptype_11space_torus_6cmodel_WavefrontObject)), ((PyObject *)__pyx_t_4), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 105; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
  __pyx_r = __pyx_t_3;
  __pyx_t_3 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("space_torus.cmodel.load_model", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":115
 * 
 * 
 *     cdef inline dispatch(self, str p):             # <<<<<<<<<<<<<<
 *         with open(p, 'r') as file:
 *             for line in file:
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_dispatch(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_p) {
  PyObject *__pyx_v_file = NULL;
  PyObject *__pyx_v_line = NULL;
  PyObject *__pyx_v_words = NULL;
  PyObject *__pyx_v_type = NULL;
  PyObject *__pyx_v_lt = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  Py_ssize_t __pyx_t_8;
  PyObject *(*__pyx_t_9)(PyObject *);
  int __pyx_t_10;
  int __pyx_t_11;
  int __pyx_t_12;
  Py_ssize_t __pyx_t_13;
  char const *__pyx_t_14;
  PyObject *__pyx_t_15 = NULL;
  PyObject *__pyx_t_16 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("dispatch", 0);

  /* "space_torus\cmodel.pyx":116
 * 
 *     cdef inline dispatch(self, str p):
 *         with open(p, 'r') as file:             # <<<<<<<<<<<<<<
 *             for line in file:
 *                 line = line.strip()
 */
  /*with:*/ {
    __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(((PyObject *)__pyx_v_p));
    PyTuple_SET_ITEM(__pyx_t_1, 0, ((PyObject *)__pyx_v_p));
    __Pyx_GIVEREF(((PyObject *)__pyx_v_p));
    __Pyx_INCREF(((PyObject *)__pyx_n_s__r));
    PyTuple_SET_ITEM(__pyx_t_1, 1, ((PyObject *)__pyx_n_s__r));
    __Pyx_GIVEREF(((PyObject *)__pyx_n_s__r));
    __pyx_t_2 = PyObject_Call(__pyx_builtin_open, ((PyObject *)__pyx_t_1), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s____exit__); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s____enter__); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_4 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    /*try:*/ {
      {
        __Pyx_ExceptionSave(&__pyx_t_5, &__pyx_t_6, &__pyx_t_7);
        __Pyx_XGOTREF(__pyx_t_5);
        __Pyx_XGOTREF(__pyx_t_6);
        __Pyx_XGOTREF(__pyx_t_7);
        /*try:*/ {
          __Pyx_INCREF(__pyx_t_4);
          __pyx_v_file = __pyx_t_4;
          __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

          /* "space_torus\cmodel.pyx":117
 *     cdef inline dispatch(self, str p):
 *         with open(p, 'r') as file:
 *             for line in file:             # <<<<<<<<<<<<<<
 *                 line = line.strip()
 *                 if not line or line[0] == '#':
 */
          if (PyList_CheckExact(__pyx_v_file) || PyTuple_CheckExact(__pyx_v_file)) {
            __pyx_t_4 = __pyx_v_file; __Pyx_INCREF(__pyx_t_4); __pyx_t_8 = 0;
            __pyx_t_9 = NULL;
          } else {
            __pyx_t_8 = -1; __pyx_t_4 = PyObject_GetIter(__pyx_v_file); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 117; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __Pyx_GOTREF(__pyx_t_4);
            __pyx_t_9 = Py_TYPE(__pyx_t_4)->tp_iternext;
          }
          for (;;) {
            if (!__pyx_t_9 && PyList_CheckExact(__pyx_t_4)) {
              if (__pyx_t_8 >= PyList_GET_SIZE(__pyx_t_4)) break;
              #if CYTHON_COMPILING_IN_CPYTHON
              __pyx_t_2 = PyList_GET_ITEM(__pyx_t_4, __pyx_t_8); __Pyx_INCREF(__pyx_t_2); __pyx_t_8++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 117; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              #else
              __pyx_t_2 = PySequence_ITEM(__pyx_t_4, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 117; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              #endif
            } else if (!__pyx_t_9 && PyTuple_CheckExact(__pyx_t_4)) {
              if (__pyx_t_8 >= PyTuple_GET_SIZE(__pyx_t_4)) break;
              #if CYTHON_COMPILING_IN_CPYTHON
              __pyx_t_2 = PyTuple_GET_ITEM(__pyx_t_4, __pyx_t_8); __Pyx_INCREF(__pyx_t_2); __pyx_t_8++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 117; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              #else
              __pyx_t_2 = PySequence_ITEM(__pyx_t_4, __pyx_t_8); __pyx_t_8++; if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 117; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              #endif
            } else {
              __pyx_t_2 = __pyx_t_9(__pyx_t_4);
              if (unlikely(!__pyx_t_2)) {
                if (PyErr_Occurred()) {
                  if (likely(PyErr_ExceptionMatches(PyExc_StopIteration))) PyErr_Clear();
                  else {__pyx_filename = __pyx_f[0]; __pyx_lineno = 117; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
                }
                break;
              }
              __Pyx_GOTREF(__pyx_t_2);
            }
            __Pyx_XDECREF_SET(__pyx_v_line, __pyx_t_2);
            __pyx_t_2 = 0;

            /* "space_torus\cmodel.pyx":118
 *         with open(p, 'r') as file:
 *             for line in file:
 *                 line = line.strip()             # <<<<<<<<<<<<<<
 *                 if not line or line[0] == '#':
 *                     continue # Empty or comment
 */
            __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_line, __pyx_n_s__strip); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 118; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __Pyx_GOTREF(__pyx_t_2);
            __pyx_t_1 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 118; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
            __Pyx_DECREF_SET(__pyx_v_line, __pyx_t_1);
            __pyx_t_1 = 0;

            /* "space_torus\cmodel.pyx":119
 *             for line in file:
 *                 line = line.strip()
 *                 if not line or line[0] == '#':             # <<<<<<<<<<<<<<
 *                     continue # Empty or comment
 *                 words = line.split()
 */
            __pyx_t_10 = __Pyx_PyObject_IsTrue(__pyx_v_line); if (unlikely(__pyx_t_10 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 119; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __pyx_t_11 = (!__pyx_t_10);
            if (!__pyx_t_11) {
              __pyx_t_1 = __Pyx_GetItemInt(__pyx_v_line, 0, sizeof(long), PyInt_FromLong, 0, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 119; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __pyx_t_2 = PyObject_RichCompare(__pyx_t_1, ((PyObject *)__pyx_kp_s_4), Py_EQ); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 119; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              __pyx_t_10 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_10 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 119; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
              __pyx_t_12 = __pyx_t_10;
            } else {
              __pyx_t_12 = __pyx_t_11;
            }
            if (__pyx_t_12) {

              /* "space_torus\cmodel.pyx":120
 *                 line = line.strip()
 *                 if not line or line[0] == '#':
 *                     continue # Empty or comment             # <<<<<<<<<<<<<<
 *                 words = line.split()
 *                 type = words[0]
 */
              goto __pyx_L16_continue;
              goto __pyx_L18;
            }
            __pyx_L18:;

            /* "space_torus\cmodel.pyx":121
 *                 if not line or line[0] == '#':
 *                     continue # Empty or comment
 *                 words = line.split()             # <<<<<<<<<<<<<<
 *                 type = words[0]
 *                 lt = len(type)
 */
            __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_line, __pyx_n_s__split); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 121; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __Pyx_GOTREF(__pyx_t_2);
            __pyx_t_1 = PyObject_Call(__pyx_t_2, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 121; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
            __Pyx_XDECREF_SET(__pyx_v_words, __pyx_t_1);
            __pyx_t_1 = 0;

            /* "space_torus\cmodel.pyx":122
 *                     continue # Empty or comment
 *                 words = line.split()
 *                 type = words[0]             # <<<<<<<<<<<<<<
 *                 lt = len(type)
 *                 if not strcmp(type[0], 'v'):
 */
            __pyx_t_1 = __Pyx_GetItemInt(__pyx_v_words, 0, sizeof(long), PyInt_FromLong, 0, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 122; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_XDECREF_SET(__pyx_v_type, __pyx_t_1);
            __pyx_t_1 = 0;

            /* "space_torus\cmodel.pyx":123
 *                 words = line.split()
 *                 type = words[0]
 *                 lt = len(type)             # <<<<<<<<<<<<<<
 *                 if not strcmp(type[0], 'v'):
 *                     if lt == 1:
 */
            __pyx_t_13 = PyObject_Length(__pyx_v_type); if (unlikely(__pyx_t_13 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 123; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __pyx_t_1 = PyInt_FromSsize_t(__pyx_t_13); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 123; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_XDECREF_SET(__pyx_v_lt, __pyx_t_1);
            __pyx_t_1 = 0;

            /* "space_torus\cmodel.pyx":124
 *                 type = words[0]
 *                 lt = len(type)
 *                 if not strcmp(type[0], 'v'):             # <<<<<<<<<<<<<<
 *                     if lt == 1:
 *                         self.v(words)
 */
            __pyx_t_1 = __Pyx_GetItemInt(__pyx_v_type, 0, sizeof(long), PyInt_FromLong, 0, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 124; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __Pyx_GOTREF(__pyx_t_1);
            __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_t_1); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 124; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            __pyx_t_12 = ((!(strcmp(__pyx_t_14, __pyx_k__v) != 0)) != 0);
            if (__pyx_t_12) {

              /* "space_torus\cmodel.pyx":125
 *                 lt = len(type)
 *                 if not strcmp(type[0], 'v'):
 *                     if lt == 1:             # <<<<<<<<<<<<<<
 *                         self.v(words)
 *                     elif not strcmp(type[1], 'n'):
 */
              __pyx_t_1 = PyObject_RichCompare(__pyx_v_lt, __pyx_int_1, Py_EQ); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 125; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __pyx_t_12 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_12 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 125; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              if (__pyx_t_12) {

                /* "space_torus\cmodel.pyx":126
 *                 if not strcmp(type[0], 'v'):
 *                     if lt == 1:
 *                         self.v(words)             # <<<<<<<<<<<<<<
 *                     elif not strcmp(type[1], 'n'):
 *                         self.vn(words)
 */
                if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 126; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
                __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_v(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 126; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
                __Pyx_GOTREF(__pyx_t_1);
                __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
                goto __pyx_L20;
              }

              /* "space_torus\cmodel.pyx":127
 *                     if lt == 1:
 *                         self.v(words)
 *                     elif not strcmp(type[1], 'n'):             # <<<<<<<<<<<<<<
 *                         self.vn(words)
 *                     elif not strcmp(type[1], 't'):
 */
              __pyx_t_1 = __Pyx_GetItemInt(__pyx_v_type, 1, sizeof(long), PyInt_FromLong, 0, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_t_1); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              __pyx_t_12 = ((!(strcmp(__pyx_t_14, __pyx_k__n) != 0)) != 0);
              if (__pyx_t_12) {

                /* "space_torus\cmodel.pyx":128
 *                         self.v(words)
 *                     elif not strcmp(type[1], 'n'):
 *                         self.vn(words)             # <<<<<<<<<<<<<<
 *                     elif not strcmp(type[1], 't'):
 *                         self.vt(words)
 */
                if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 128; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
                __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_vn(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 128; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
                __Pyx_GOTREF(__pyx_t_1);
                __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
                goto __pyx_L20;
              }

              /* "space_torus\cmodel.pyx":129
 *                     elif not strcmp(type[1], 'n'):
 *                         self.vn(words)
 *                     elif not strcmp(type[1], 't'):             # <<<<<<<<<<<<<<
 *                         self.vt(words)
 *                 elif not strcmp(type, 'f'):
 */
              __pyx_t_1 = __Pyx_GetItemInt(__pyx_v_type, 1, sizeof(long), PyInt_FromLong, 0, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 129; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_t_1); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 129; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              __pyx_t_12 = ((!(strcmp(__pyx_t_14, __pyx_k__t) != 0)) != 0);
              if (__pyx_t_12) {

                /* "space_torus\cmodel.pyx":130
 *                         self.vn(words)
 *                     elif not strcmp(type[1], 't'):
 *                         self.vt(words)             # <<<<<<<<<<<<<<
 *                 elif not strcmp(type, 'f'):
 *                     self.f(words)
 */
                if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 130; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
                __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_vt(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 130; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
                __Pyx_GOTREF(__pyx_t_1);
                __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
                goto __pyx_L20;
              }
              __pyx_L20:;
              goto __pyx_L19;
            }

            /* "space_torus\cmodel.pyx":131
 *                     elif not strcmp(type[1], 't'):
 *                         self.vt(words)
 *                 elif not strcmp(type, 'f'):             # <<<<<<<<<<<<<<
 *                     self.f(words)
 *                 elif not strcmp(type, 'mtllib'):
 */
            __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_v_type); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 131; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __pyx_t_12 = ((!(strcmp(__pyx_t_14, __pyx_k__f) != 0)) != 0);
            if (__pyx_t_12) {

              /* "space_torus\cmodel.pyx":132
 *                         self.vt(words)
 *                 elif not strcmp(type, 'f'):
 *                     self.f(words)             # <<<<<<<<<<<<<<
 *                 elif not strcmp(type, 'mtllib'):
 *                     self.mtllib(words)
 */
              if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 132; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_f(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 132; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              goto __pyx_L19;
            }

            /* "space_torus\cmodel.pyx":133
 *                 elif not strcmp(type, 'f'):
 *                     self.f(words)
 *                 elif not strcmp(type, 'mtllib'):             # <<<<<<<<<<<<<<
 *                     self.mtllib(words)
 *                 elif not strcmp(type, 'usemtl'):
 */
            __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_v_type); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 133; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __pyx_t_12 = ((!(strcmp(__pyx_t_14, __pyx_k__mtllib) != 0)) != 0);
            if (__pyx_t_12) {

              /* "space_torus\cmodel.pyx":134
 *                     self.f(words)
 *                 elif not strcmp(type, 'mtllib'):
 *                     self.mtllib(words)             # <<<<<<<<<<<<<<
 *                 elif not strcmp(type, 'usemtl'):
 *                     self.usemtl(words)
 */
              if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 134; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_mtllib(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 134; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              goto __pyx_L19;
            }

            /* "space_torus\cmodel.pyx":135
 *                 elif not strcmp(type, 'mtllib'):
 *                     self.mtllib(words)
 *                 elif not strcmp(type, 'usemtl'):             # <<<<<<<<<<<<<<
 *                     self.usemtl(words)
 *                 elif not strcmp(type, 'g') or not strcmp(type, 'o'):
 */
            __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_v_type); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 135; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __pyx_t_12 = ((!(strcmp(__pyx_t_14, __pyx_k__usemtl) != 0)) != 0);
            if (__pyx_t_12) {

              /* "space_torus\cmodel.pyx":136
 *                     self.mtllib(words)
 *                 elif not strcmp(type, 'usemtl'):
 *                     self.usemtl(words)             # <<<<<<<<<<<<<<
 *                 elif not strcmp(type, 'g') or not strcmp(type, 'o'):
 *                     self.g(words)
 */
              if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 136; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_usemtl(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 136; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              goto __pyx_L19;
            }

            /* "space_torus\cmodel.pyx":137
 *                 elif not strcmp(type, 'usemtl'):
 *                     self.usemtl(words)
 *                 elif not strcmp(type, 'g') or not strcmp(type, 'o'):             # <<<<<<<<<<<<<<
 *                     self.g(words)
 *                 elif not strcmp(type, 'newmtl'):
 */
            __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_v_type); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 137; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __pyx_t_12 = ((!(strcmp(__pyx_t_14, __pyx_k__g) != 0)) != 0);
            if (!__pyx_t_12) {
              __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_v_type); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 137; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __pyx_t_11 = ((!(strcmp(__pyx_t_14, __pyx_k__o) != 0)) != 0);
              __pyx_t_10 = __pyx_t_11;
            } else {
              __pyx_t_10 = __pyx_t_12;
            }
            if (__pyx_t_10) {

              /* "space_torus\cmodel.pyx":138
 *                     self.usemtl(words)
 *                 elif not strcmp(type, 'g') or not strcmp(type, 'o'):
 *                     self.g(words)             # <<<<<<<<<<<<<<
 *                 elif not strcmp(type, 'newmtl'):
 *                     self.newmtl(words)
 */
              if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 138; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_g(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 138; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              goto __pyx_L19;
            }

            /* "space_torus\cmodel.pyx":139
 *                 elif not strcmp(type, 'g') or not strcmp(type, 'o'):
 *                     self.g(words)
 *                 elif not strcmp(type, 'newmtl'):             # <<<<<<<<<<<<<<
 *                     self.newmtl(words)
 *                 elif not strcmp(type, 'Ka'):
 */
            __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_v_type); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 139; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __pyx_t_10 = ((!(strcmp(__pyx_t_14, __pyx_k__newmtl) != 0)) != 0);
            if (__pyx_t_10) {

              /* "space_torus\cmodel.pyx":140
 *                     self.g(words)
 *                 elif not strcmp(type, 'newmtl'):
 *                     self.newmtl(words)             # <<<<<<<<<<<<<<
 *                 elif not strcmp(type, 'Ka'):
 *                     self.Ka(words)
 */
              if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 140; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_newmtl(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 140; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              goto __pyx_L19;
            }

            /* "space_torus\cmodel.pyx":141
 *                 elif not strcmp(type, 'newmtl'):
 *                     self.newmtl(words)
 *                 elif not strcmp(type, 'Ka'):             # <<<<<<<<<<<<<<
 *                     self.Ka(words)
 *                 elif not strcmp(type, 'Kd'):
 */
            __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_v_type); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 141; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __pyx_t_10 = ((!(strcmp(__pyx_t_14, __pyx_k__Ka) != 0)) != 0);
            if (__pyx_t_10) {

              /* "space_torus\cmodel.pyx":142
 *                     self.newmtl(words)
 *                 elif not strcmp(type, 'Ka'):
 *                     self.Ka(words)             # <<<<<<<<<<<<<<
 *                 elif not strcmp(type, 'Kd'):
 *                     self.Kd(words)
 */
              if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_Ka(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              goto __pyx_L19;
            }

            /* "space_torus\cmodel.pyx":143
 *                 elif not strcmp(type, 'Ka'):
 *                     self.Ka(words)
 *                 elif not strcmp(type, 'Kd'):             # <<<<<<<<<<<<<<
 *                     self.Kd(words)
 *                 elif not strcmp(type, 'Ks'):
 */
            __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_v_type); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 143; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __pyx_t_10 = ((!(strcmp(__pyx_t_14, __pyx_k__Kd) != 0)) != 0);
            if (__pyx_t_10) {

              /* "space_torus\cmodel.pyx":144
 *                     self.Ka(words)
 *                 elif not strcmp(type, 'Kd'):
 *                     self.Kd(words)             # <<<<<<<<<<<<<<
 *                 elif not strcmp(type, 'Ks'):
 *                     self.Ks(words)
 */
              if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 144; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_Kd(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 144; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              goto __pyx_L19;
            }

            /* "space_torus\cmodel.pyx":145
 *                 elif not strcmp(type, 'Kd'):
 *                     self.Kd(words)
 *                 elif not strcmp(type, 'Ks'):             # <<<<<<<<<<<<<<
 *                     self.Ks(words)
 *                 elif not strcmp(type, 'Ns'):
 */
            __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_v_type); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 145; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __pyx_t_10 = ((!(strcmp(__pyx_t_14, __pyx_k__Ks) != 0)) != 0);
            if (__pyx_t_10) {

              /* "space_torus\cmodel.pyx":146
 *                     self.Kd(words)
 *                 elif not strcmp(type, 'Ks'):
 *                     self.Ks(words)             # <<<<<<<<<<<<<<
 *                 elif not strcmp(type, 'Ns'):
 *                     self.Ns(words)
 */
              if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 146; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_Ks(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 146; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              goto __pyx_L19;
            }

            /* "space_torus\cmodel.pyx":147
 *                 elif not strcmp(type, 'Ks'):
 *                     self.Ks(words)
 *                 elif not strcmp(type, 'Ns'):             # <<<<<<<<<<<<<<
 *                     self.Ns(words)
 *                 elif not strcmp(type, 'map_Kd'):
 */
            __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_v_type); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 147; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __pyx_t_10 = ((!(strcmp(__pyx_t_14, __pyx_k__Ns) != 0)) != 0);
            if (__pyx_t_10) {

              /* "space_torus\cmodel.pyx":148
 *                     self.Ks(words)
 *                 elif not strcmp(type, 'Ns'):
 *                     self.Ns(words)             # <<<<<<<<<<<<<<
 *                 elif not strcmp(type, 'map_Kd'):
 *                     self.map_Kd(words)
 */
              if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 148; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_Ns(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 148; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              goto __pyx_L19;
            }

            /* "space_torus\cmodel.pyx":149
 *                 elif not strcmp(type, 'Ns'):
 *                     self.Ns(words)
 *                 elif not strcmp(type, 'map_Kd'):             # <<<<<<<<<<<<<<
 *                     self.map_Kd(words)
 * 
 */
            __pyx_t_14 = __Pyx_PyObject_AsString(__pyx_v_type); if (unlikely((!__pyx_t_14) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 149; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
            __pyx_t_10 = ((!(strcmp(__pyx_t_14, __pyx_k__map_Kd) != 0)) != 0);
            if (__pyx_t_10) {

              /* "space_torus\cmodel.pyx":150
 *                     self.Ns(words)
 *                 elif not strcmp(type, 'map_Kd'):
 *                     self.map_Kd(words)             # <<<<<<<<<<<<<<
 * 
 *     cdef inline newmtl(self, list words):
 */
              if (!(likely(PyList_CheckExact(__pyx_v_words))||((__pyx_v_words) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_words)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 150; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __pyx_t_1 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_map_Kd(__pyx_v_self, ((PyObject*)__pyx_v_words)); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 150; __pyx_clineno = __LINE__; goto __pyx_L7_error;}
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              goto __pyx_L19;
            }
            __pyx_L19:;
            __pyx_L16_continue:;
          }
          __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
        }
        __Pyx_XDECREF(__pyx_t_5); __pyx_t_5 = 0;
        __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
        __Pyx_XDECREF(__pyx_t_7); __pyx_t_7 = 0;
        goto __pyx_L14_try_end;
        __pyx_L7_error:;
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_XDECREF(__pyx_t_4); __pyx_t_4 = 0;

        /* "space_torus\cmodel.pyx":116
 * 
 *     cdef inline dispatch(self, str p):
 *         with open(p, 'r') as file:             # <<<<<<<<<<<<<<
 *             for line in file:
 *                 line = line.strip()
 */
        /*except:*/ {
          __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.dispatch", __pyx_clineno, __pyx_lineno, __pyx_filename);
          if (__Pyx_GetException(&__pyx_t_4, &__pyx_t_1, &__pyx_t_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L9_except_error;}
          __Pyx_GOTREF(__pyx_t_4);
          __Pyx_GOTREF(__pyx_t_1);
          __Pyx_GOTREF(__pyx_t_2);
          __pyx_t_15 = PyTuple_New(3); if (unlikely(!__pyx_t_15)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L9_except_error;}
          __Pyx_GOTREF(__pyx_t_15);
          __Pyx_INCREF(__pyx_t_4);
          PyTuple_SET_ITEM(__pyx_t_15, 0, __pyx_t_4);
          __Pyx_GIVEREF(__pyx_t_4);
          __Pyx_INCREF(__pyx_t_1);
          PyTuple_SET_ITEM(__pyx_t_15, 1, __pyx_t_1);
          __Pyx_GIVEREF(__pyx_t_1);
          __Pyx_INCREF(__pyx_t_2);
          PyTuple_SET_ITEM(__pyx_t_15, 2, __pyx_t_2);
          __Pyx_GIVEREF(__pyx_t_2);
          __pyx_t_16 = PyObject_Call(__pyx_t_3, __pyx_t_15, NULL);
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          if (unlikely(!__pyx_t_16)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L9_except_error;}
          __Pyx_GOTREF(__pyx_t_16);
          __pyx_t_10 = __Pyx_PyObject_IsTrue(__pyx_t_16);
          __Pyx_DECREF(__pyx_t_16); __pyx_t_16 = 0;
          if (__pyx_t_10 < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L9_except_error;}
          __pyx_t_12 = ((!(__pyx_t_10 != 0)) != 0);
          if (__pyx_t_12) {
            __Pyx_GIVEREF(__pyx_t_4);
            __Pyx_GIVEREF(__pyx_t_1);
            __Pyx_GIVEREF(__pyx_t_2);
            __Pyx_ErrRestore(__pyx_t_4, __pyx_t_1, __pyx_t_2);
            __pyx_t_4 = 0; __pyx_t_1 = 0; __pyx_t_2 = 0; 
            {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L9_except_error;}
            goto __pyx_L23;
          }
          __pyx_L23:;
          __Pyx_DECREF(((PyObject *)__pyx_t_15)); __pyx_t_15 = 0;
          __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
          goto __pyx_L8_exception_handled;
        }
        __pyx_L9_except_error:;
        __Pyx_XGIVEREF(__pyx_t_5);
        __Pyx_XGIVEREF(__pyx_t_6);
        __Pyx_XGIVEREF(__pyx_t_7);
        __Pyx_ExceptionReset(__pyx_t_5, __pyx_t_6, __pyx_t_7);
        goto __pyx_L1_error;
        __pyx_L8_exception_handled:;
        __Pyx_XGIVEREF(__pyx_t_5);
        __Pyx_XGIVEREF(__pyx_t_6);
        __Pyx_XGIVEREF(__pyx_t_7);
        __Pyx_ExceptionReset(__pyx_t_5, __pyx_t_6, __pyx_t_7);
        __pyx_L14_try_end:;
      }
    }
    /*finally:*/ {
      if (__pyx_t_3) {
        __pyx_t_7 = PyObject_Call(__pyx_t_3, __pyx_k_tuple_5, NULL);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        if (unlikely(!__pyx_t_7)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_7);
        __pyx_t_12 = __Pyx_PyObject_IsTrue(__pyx_t_7);
        __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
        if (__pyx_t_12 < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      }
    }
    goto __pyx_L24;
    __pyx_L3_error:;
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    goto __pyx_L1_error;
    __pyx_L24:;
  }

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_15);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.dispatch", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_file);
  __Pyx_XDECREF(__pyx_v_line);
  __Pyx_XDECREF(__pyx_v_words);
  __Pyx_XDECREF(__pyx_v_type);
  __Pyx_XDECREF(__pyx_v_lt);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":152
 *                     self.map_Kd(words)
 * 
 *     cdef inline newmtl(self, list words):             # <<<<<<<<<<<<<<
 *         material = Material(words[1])
 *         self.materials[words[1]] = material
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_newmtl(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_material = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("newmtl", 0);

  /* "space_torus\cmodel.pyx":153
 * 
 *     cdef inline newmtl(self, list words):
 *         material = Material(words[1])             # <<<<<<<<<<<<<<
 *         self.materials[words[1]] = material
 *         self.current_material = material
 */
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 153; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 153; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 153; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_Call(((PyObject *)((PyObject*)__pyx_ptype_11space_torus_6cmodel_Material)), ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 153; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  __pyx_v_material = ((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_t_1);
  __pyx_t_1 = 0;

  /* "space_torus\cmodel.pyx":154
 *     cdef inline newmtl(self, list words):
 *         material = Material(words[1])
 *         self.materials[words[1]] = material             # <<<<<<<<<<<<<<
 *         self.current_material = material
 * 
 */
  if (unlikely(((PyObject *)__pyx_v_self->materials) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 154; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 154; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 154; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(((PyObject *)__pyx_v_self->materials), __pyx_t_1, ((PyObject *)__pyx_v_material)) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 154; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "space_torus\cmodel.pyx":155
 *         material = Material(words[1])
 *         self.materials[words[1]] = material
 *         self.current_material = material             # <<<<<<<<<<<<<<
 * 
 *     cdef inline Ka(self, list words):
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_material));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_material));
  __Pyx_GOTREF(__pyx_v_self->current_material);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->current_material));
  __pyx_v_self->current_material = __pyx_v_material;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.newmtl", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF((PyObject *)__pyx_v_material);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":157
 *         self.current_material = material
 * 
 *     cdef inline Ka(self, list words):             # <<<<<<<<<<<<<<
 *         self.current_material.Ka = (float(words[1]), float(words[2]), float(words[3]))
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_Ka(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  double __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("Ka", 0);

  /* "space_torus\cmodel.pyx":158
 * 
 *     cdef inline Ka(self, list words):
 *         self.current_material.Ka = (float(words[1]), float(words[2]), float(words[3]))             # <<<<<<<<<<<<<<
 * 
 *     cdef inline Kd(self, list words):
 */
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_1); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_3 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 2, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_3); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_4 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 3, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_4); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = PyTuple_New(3); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 158; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_5, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  __pyx_t_1 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __Pyx_GIVEREF(((PyObject *)__pyx_t_5));
  __Pyx_GOTREF(__pyx_v_self->current_material->Ka);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->current_material->Ka));
  __pyx_v_self->current_material->Ka = ((PyObject*)__pyx_t_5);
  __pyx_t_5 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.Ka", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":160
 *         self.current_material.Ka = (float(words[1]), float(words[2]), float(words[3]))
 * 
 *     cdef inline Kd(self, list words):             # <<<<<<<<<<<<<<
 *         self.current_material.Kd = (float(words[1]), float(words[2]), float(words[3]))
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_Kd(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  double __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("Kd", 0);

  /* "space_torus\cmodel.pyx":161
 * 
 *     cdef inline Kd(self, list words):
 *         self.current_material.Kd = (float(words[1]), float(words[2]), float(words[3]))             # <<<<<<<<<<<<<<
 * 
 *     cdef inline Ks(self, list words):
 */
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_1); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_3 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 2, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_3); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_4 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 3, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_4); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = PyTuple_New(3); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 161; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_5, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  __pyx_t_1 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __Pyx_GIVEREF(((PyObject *)__pyx_t_5));
  __Pyx_GOTREF(__pyx_v_self->current_material->Kd);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->current_material->Kd));
  __pyx_v_self->current_material->Kd = ((PyObject*)__pyx_t_5);
  __pyx_t_5 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.Kd", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":163
 *         self.current_material.Kd = (float(words[1]), float(words[2]), float(words[3]))
 * 
 *     cdef inline Ks(self, list words):             # <<<<<<<<<<<<<<
 *         self.current_material.Ks = (float(words[1]), float(words[2]), float(words[3]))
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_Ks(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  double __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("Ks", 0);

  /* "space_torus\cmodel.pyx":164
 * 
 *     cdef inline Ks(self, list words):
 *         self.current_material.Ks = (float(words[1]), float(words[2]), float(words[3]))             # <<<<<<<<<<<<<<
 * 
 *     cdef inline Ns(self, list words):
 */
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_1); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_3 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 2, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_3); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_4 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 3, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_4); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = PyTuple_New(3); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 164; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_5, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  __pyx_t_1 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __Pyx_GIVEREF(((PyObject *)__pyx_t_5));
  __Pyx_GOTREF(__pyx_v_self->current_material->Ks);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->current_material->Ks));
  __pyx_v_self->current_material->Ks = ((PyObject*)__pyx_t_5);
  __pyx_t_5 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.Ks", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":166
 *         self.current_material.Ks = (float(words[1]), float(words[2]), float(words[3]))
 * 
 *     cdef inline Ns(self, list words):             # <<<<<<<<<<<<<<
 *         self.current_material.shininess = min(float(words[1]), 125) # Seems to sometimes be > 125. TODO: find out why
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_Ns(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  long __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  double __pyx_t_3;
  double __pyx_t_4;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("Ns", 0);

  /* "space_torus\cmodel.pyx":167
 * 
 *     cdef inline Ns(self, list words):
 *         self.current_material.shininess = min(float(words[1]), 125) # Seems to sometimes be > 125. TODO: find out why             # <<<<<<<<<<<<<<
 * 
 *     cdef inline map_Kd(self, list words):
 */
  __pyx_t_1 = 125;
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_AsDouble(__pyx_t_2); if (unlikely(__pyx_t_3 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (((__pyx_t_1 < __pyx_t_3) != 0)) {
    __pyx_t_4 = __pyx_t_1;
  } else {
    __pyx_t_4 = __pyx_t_3;
  }
  __pyx_v_self->current_material->shininess = __pyx_t_4;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.Ns", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":169
 *         self.current_material.shininess = min(float(words[1]), 125) # Seems to sometimes be > 125. TODO: find out why
 * 
 *     cdef inline map_Kd(self, list words):             # <<<<<<<<<<<<<<
 *         self.current_material.texture = words[-1]
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_map_Kd(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("map_Kd", 0);

  /* "space_torus\cmodel.pyx":170
 * 
 *     cdef inline map_Kd(self, list words):
 *         self.current_material.texture = words[-1]             # <<<<<<<<<<<<<<
 * 
 *     cdef inline v(self, list words):
 */
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 170; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), -1, sizeof(long), PyInt_FromLong, 1, 1, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 170; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (!(likely(PyString_CheckExact(__pyx_t_1))||((__pyx_t_1) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected str, got %.200s", Py_TYPE(__pyx_t_1)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 170; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GIVEREF(__pyx_t_1);
  __Pyx_GOTREF(__pyx_v_self->current_material->texture);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->current_material->texture));
  __pyx_v_self->current_material->texture = ((PyObject*)__pyx_t_1);
  __pyx_t_1 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.map_Kd", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":172
 *         self.current_material.texture = words[-1]
 * 
 *     cdef inline v(self, list words):             # <<<<<<<<<<<<<<
 *         self.vertices.append((float(words[1]), float(words[2]), float(words[3])))
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_v(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  double __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("v", 0);

  /* "space_torus\cmodel.pyx":173
 * 
 *     cdef inline v(self, list words):
 *         self.vertices.append((float(words[1]), float(words[2]), float(words[3])))             # <<<<<<<<<<<<<<
 * 
 *     cdef inline vn(self, list words):
 */
  if (unlikely(((PyObject *)__pyx_v_self->vertices) == Py_None)) {
    PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%s'", "append");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_1); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_3 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 2, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_3); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_4 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 3, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_4); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = PyTuple_New(3); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_5, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  __pyx_t_1 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_6 = __Pyx_PyList_Append(__pyx_v_self->vertices, ((PyObject *)__pyx_t_5)); if (unlikely(__pyx_t_6 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(((PyObject *)__pyx_t_5)); __pyx_t_5 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.v", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":175
 *         self.vertices.append((float(words[1]), float(words[2]), float(words[3])))
 * 
 *     cdef inline vn(self, list words):             # <<<<<<<<<<<<<<
 *         self.normals.append((float(words[1]), float(words[2]), float(words[3])))
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_vn(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  double __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  PyObject *__pyx_t_5 = NULL;
  int __pyx_t_6;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("vn", 0);

  /* "space_torus\cmodel.pyx":176
 * 
 *     cdef inline vn(self, list words):
 *         self.normals.append((float(words[1]), float(words[2]), float(words[3])))             # <<<<<<<<<<<<<<
 * 
 *     cdef inline vt(self, list words):
 */
  if (unlikely(((PyObject *)__pyx_v_self->normals) == Py_None)) {
    PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%s'", "append");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_1); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_3 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 2, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_3); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_4 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 3, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = __Pyx_PyObject_AsDouble(__pyx_t_4); if (unlikely(__pyx_t_2 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  __pyx_t_4 = PyFloat_FromDouble(__pyx_t_2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_5 = PyTuple_New(3); if (unlikely(!__pyx_t_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_5);
  PyTuple_SET_ITEM(__pyx_t_5, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  PyTuple_SET_ITEM(__pyx_t_5, 1, __pyx_t_3);
  __Pyx_GIVEREF(__pyx_t_3);
  PyTuple_SET_ITEM(__pyx_t_5, 2, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  __pyx_t_1 = 0;
  __pyx_t_3 = 0;
  __pyx_t_4 = 0;
  __pyx_t_6 = __Pyx_PyList_Append(__pyx_v_self->normals, ((PyObject *)__pyx_t_5)); if (unlikely(__pyx_t_6 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 176; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(((PyObject *)__pyx_t_5)); __pyx_t_5 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_5);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.vn", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":178
 *         self.normals.append((float(words[1]), float(words[2]), float(words[3])))
 * 
 *     cdef inline vt(self, list words):             # <<<<<<<<<<<<<<
 *         l = len(words)
 *         x, y, z = 0, 0, 0
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_vt(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  PyObject *__pyx_v_l = NULL;
  double __pyx_v_x;
  double __pyx_v_y;
  double __pyx_v_z;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  Py_ssize_t __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  double __pyx_t_3;
  double __pyx_t_4;
  double __pyx_t_5;
  int __pyx_t_6;
  PyObject *__pyx_t_7 = NULL;
  PyObject *__pyx_t_8 = NULL;
  PyObject *__pyx_t_9 = NULL;
  int __pyx_t_10;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("vt", 0);

  /* "space_torus\cmodel.pyx":179
 * 
 *     cdef inline vt(self, list words):
 *         l = len(words)             # <<<<<<<<<<<<<<
 *         x, y, z = 0, 0, 0
 *         if l >= 2:
 */
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 179; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = PyList_GET_SIZE(((PyObject *)__pyx_v_words)); if (unlikely(__pyx_t_1 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 179; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_2 = PyInt_FromSsize_t(__pyx_t_1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 179; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_l = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":180
 *     cdef inline vt(self, list words):
 *         l = len(words)
 *         x, y, z = 0, 0, 0             # <<<<<<<<<<<<<<
 *         if l >= 2:
 *             x = float(words[1])
 */
  __pyx_t_3 = 0.0;
  __pyx_t_4 = 0.0;
  __pyx_t_5 = 0.0;
  __pyx_v_x = __pyx_t_3;
  __pyx_v_y = __pyx_t_4;
  __pyx_v_z = __pyx_t_5;

  /* "space_torus\cmodel.pyx":181
 *         l = len(words)
 *         x, y, z = 0, 0, 0
 *         if l >= 2:             # <<<<<<<<<<<<<<
 *             x = float(words[1])
 *         if l >= 3:
 */
  __pyx_t_2 = PyObject_RichCompare(__pyx_v_l, __pyx_int_2, Py_GE); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 181; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_6 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 181; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (__pyx_t_6) {

    /* "space_torus\cmodel.pyx":182
 *         x, y, z = 0, 0, 0
 *         if l >= 2:
 *             x = float(words[1])             # <<<<<<<<<<<<<<
 *         if l >= 3:
 *             # OBJ origin is at upper left, OpenGL origin is at lower left
 */
    if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 182; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 182; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_5 = __Pyx_PyObject_AsDouble(__pyx_t_2); if (unlikely(__pyx_t_5 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 182; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_v_x = __pyx_t_5;
    goto __pyx_L3;
  }
  __pyx_L3:;

  /* "space_torus\cmodel.pyx":183
 *         if l >= 2:
 *             x = float(words[1])
 *         if l >= 3:             # <<<<<<<<<<<<<<
 *             # OBJ origin is at upper left, OpenGL origin is at lower left
 *             y = 1 - float(words[2])
 */
  __pyx_t_2 = PyObject_RichCompare(__pyx_v_l, __pyx_int_3, Py_GE); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 183; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_6 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 183; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (__pyx_t_6) {

    /* "space_torus\cmodel.pyx":185
 *         if l >= 3:
 *             # OBJ origin is at upper left, OpenGL origin is at lower left
 *             y = 1 - float(words[2])             # <<<<<<<<<<<<<<
 *         if l >= 4:
 *             z = float(words[3])
 */
    if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 185; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 2, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 185; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_5 = __Pyx_PyObject_AsDouble(__pyx_t_2); if (unlikely(__pyx_t_5 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 185; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_v_y = (1.0 - __pyx_t_5);
    goto __pyx_L4;
  }
  __pyx_L4:;

  /* "space_torus\cmodel.pyx":186
 *             # OBJ origin is at upper left, OpenGL origin is at lower left
 *             y = 1 - float(words[2])
 *         if l >= 4:             # <<<<<<<<<<<<<<
 *             z = float(words[3])
 *         self.textures.append((x, y, z))
 */
  __pyx_t_2 = PyObject_RichCompare(__pyx_v_l, __pyx_int_4, Py_GE); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 186; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_6 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_6 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 186; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (__pyx_t_6) {

    /* "space_torus\cmodel.pyx":187
 *             y = 1 - float(words[2])
 *         if l >= 4:
 *             z = float(words[3])             # <<<<<<<<<<<<<<
 *         self.textures.append((x, y, z))
 * 
 */
    if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 187; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 3, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 187; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_5 = __Pyx_PyObject_AsDouble(__pyx_t_2); if (unlikely(__pyx_t_5 == ((double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 187; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_v_z = __pyx_t_5;
    goto __pyx_L5;
  }
  __pyx_L5:;

  /* "space_torus\cmodel.pyx":188
 *         if l >= 4:
 *             z = float(words[3])
 *         self.textures.append((x, y, z))             # <<<<<<<<<<<<<<
 * 
 *     cdef inline f(self, list words):
 */
  if (unlikely(((PyObject *)__pyx_v_self->textures) == Py_None)) {
    PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%s'", "append");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 188; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_2 = PyFloat_FromDouble(__pyx_v_x); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 188; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_7 = PyFloat_FromDouble(__pyx_v_y); if (unlikely(!__pyx_t_7)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 188; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_7);
  __pyx_t_8 = PyFloat_FromDouble(__pyx_v_z); if (unlikely(!__pyx_t_8)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 188; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_8);
  __pyx_t_9 = PyTuple_New(3); if (unlikely(!__pyx_t_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 188; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_9);
  PyTuple_SET_ITEM(__pyx_t_9, 0, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_9, 1, __pyx_t_7);
  __Pyx_GIVEREF(__pyx_t_7);
  PyTuple_SET_ITEM(__pyx_t_9, 2, __pyx_t_8);
  __Pyx_GIVEREF(__pyx_t_8);
  __pyx_t_2 = 0;
  __pyx_t_7 = 0;
  __pyx_t_8 = 0;
  __pyx_t_10 = __Pyx_PyList_Append(__pyx_v_self->textures, ((PyObject *)__pyx_t_9)); if (unlikely(__pyx_t_10 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 188; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(((PyObject *)__pyx_t_9)); __pyx_t_9 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_XDECREF(__pyx_t_8);
  __Pyx_XDECREF(__pyx_t_9);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.vt", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_l);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":190
 *         self.textures.append((x, y, z))
 * 
 *     cdef inline f(self, list words):             # <<<<<<<<<<<<<<
 *         l = len(words)
 *         type = -1
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_f(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  PyObject *__pyx_v_l = NULL;
  long __pyx_v_type;
  PyObject *__pyx_v_face_vertices = 0;
  PyObject *__pyx_v_face_normals = 0;
  PyObject *__pyx_v_face_textures = 0;
  PyObject *__pyx_v_raw_faces = 0;
  PyObject *__pyx_v_vindices = 0;
  PyObject *__pyx_v_nindices = 0;
  int __pyx_v_current_value;
  PyObject *__pyx_v_vertex_count = NULL;
  PyObject *__pyx_v_tindices = NULL;
  PyObject *__pyx_v_i = NULL;
  PyObject *__pyx_v_group = NULL;
  PyObject *__pyx_v_idx_count = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  Py_ssize_t __pyx_t_1;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  PyObject *(*__pyx_t_5)(PyObject *);
  PyObject *__pyx_t_6 = NULL;
  Py_ssize_t __pyx_t_7;
  int __pyx_t_8;
  int __pyx_t_9;
  long __pyx_t_10;
  int __pyx_t_11;
  int __pyx_t_12;
  PyObject *__pyx_t_13 = NULL;
  PyObject *__pyx_t_14 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("f", 0);

  /* "space_torus\cmodel.pyx":191
 * 
 *     cdef inline f(self, list words):
 *         l = len(words)             # <<<<<<<<<<<<<<
 *         type = -1
 *         cdef list face_vertices, face_normals, face_textures, raw_faces, vindices, nindices, tindicies
 */
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 191; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = PyList_GET_SIZE(((PyObject *)__pyx_v_words)); if (unlikely(__pyx_t_1 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 191; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_2 = PyInt_FromSsize_t(__pyx_t_1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 191; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_l = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":192
 *     cdef inline f(self, list words):
 *         l = len(words)
 *         type = -1             # <<<<<<<<<<<<<<
 *         cdef list face_vertices, face_normals, face_textures, raw_faces, vindices, nindices, tindicies
 *         cdef int current_value
 */
  __pyx_v_type = -1;

  /* "space_torus\cmodel.pyx":196
 *         cdef int current_value
 * 
 *         face_vertices = []             # <<<<<<<<<<<<<<
 *         face_normals = []
 *         face_textures = []
 */
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 196; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_face_vertices = ((PyObject*)__pyx_t_2);
  __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":197
 * 
 *         face_vertices = []
 *         face_normals = []             # <<<<<<<<<<<<<<
 *         face_textures = []
 * 
 */
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 197; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_face_normals = ((PyObject*)__pyx_t_2);
  __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":198
 *         face_vertices = []
 *         face_normals = []
 *         face_textures = []             # <<<<<<<<<<<<<<
 * 
 *         vertex_count = l - 1
 */
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 198; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_face_textures = ((PyObject*)__pyx_t_2);
  __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":200
 *         face_textures = []
 * 
 *         vertex_count = l - 1             # <<<<<<<<<<<<<<
 *         if vertex_count == 3:
 *             type = FACE_TRIANGLES
 */
  __pyx_t_2 = PyNumber_Subtract(__pyx_v_l, __pyx_int_1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 200; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_vertex_count = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":201
 * 
 *         vertex_count = l - 1
 *         if vertex_count == 3:             # <<<<<<<<<<<<<<
 *             type = FACE_TRIANGLES
 *         else:
 */
  __pyx_t_2 = PyObject_RichCompare(__pyx_v_vertex_count, __pyx_int_3, Py_EQ); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 201; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_3 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 201; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (__pyx_t_3) {

    /* "space_torus\cmodel.pyx":202
 *         vertex_count = l - 1
 *         if vertex_count == 3:
 *             type = FACE_TRIANGLES             # <<<<<<<<<<<<<<
 *         else:
 *             type = FACE_QUADS
 */
    __pyx_v_type = __pyx_e_11space_torus_6cmodel_FACE_TRIANGLES;
    goto __pyx_L3;
  }
  /*else*/ {

    /* "space_torus\cmodel.pyx":204
 *             type = FACE_TRIANGLES
 *         else:
 *             type = FACE_QUADS             # <<<<<<<<<<<<<<
 * 
 *         raw_faces = []
 */
    __pyx_v_type = __pyx_e_11space_torus_6cmodel_FACE_QUADS;
  }
  __pyx_L3:;

  /* "space_torus\cmodel.pyx":206
 *             type = FACE_QUADS
 * 
 *         raw_faces = []             # <<<<<<<<<<<<<<
 *         current_value = -1
 *         vindices = []
 */
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 206; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_raw_faces = ((PyObject*)__pyx_t_2);
  __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":207
 * 
 *         raw_faces = []
 *         current_value = -1             # <<<<<<<<<<<<<<
 *         vindices = []
 *         nindices = []
 */
  __pyx_v_current_value = -1;

  /* "space_torus\cmodel.pyx":208
 *         raw_faces = []
 *         current_value = -1
 *         vindices = []             # <<<<<<<<<<<<<<
 *         nindices = []
 *         tindices = []
 */
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_vindices = ((PyObject*)__pyx_t_2);
  __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":209
 *         current_value = -1
 *         vindices = []
 *         nindices = []             # <<<<<<<<<<<<<<
 *         tindices = []
 * 
 */
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 209; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_nindices = ((PyObject*)__pyx_t_2);
  __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":210
 *         vindices = []
 *         nindices = []
 *         tindices = []             # <<<<<<<<<<<<<<
 * 
 *         for i in xrange(1, vertex_count + 1):
 */
  __pyx_t_2 = PyList_New(0); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 210; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_tindices = ((PyObject*)__pyx_t_2);
  __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":212
 *         tindices = []
 * 
 *         for i in xrange(1, vertex_count + 1):             # <<<<<<<<<<<<<<
 *             raw_faces = words[i].split('/')
 *             l = len(raw_faces)
 */
  __pyx_t_2 = PyNumber_Add(__pyx_v_vertex_count, __pyx_int_1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = PyTuple_New(2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_INCREF(__pyx_int_1);
  PyTuple_SET_ITEM(__pyx_t_4, 0, __pyx_int_1);
  __Pyx_GIVEREF(__pyx_int_1);
  PyTuple_SET_ITEM(__pyx_t_4, 1, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_Call(__pyx_builtin_xrange, ((PyObject *)__pyx_t_4), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
  if (PyList_CheckExact(__pyx_t_2) || PyTuple_CheckExact(__pyx_t_2)) {
    __pyx_t_4 = __pyx_t_2; __Pyx_INCREF(__pyx_t_4); __pyx_t_1 = 0;
    __pyx_t_5 = NULL;
  } else {
    __pyx_t_1 = -1; __pyx_t_4 = PyObject_GetIter(__pyx_t_2); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_t_5 = Py_TYPE(__pyx_t_4)->tp_iternext;
  }
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  for (;;) {
    if (!__pyx_t_5 && PyList_CheckExact(__pyx_t_4)) {
      if (__pyx_t_1 >= PyList_GET_SIZE(__pyx_t_4)) break;
      #if CYTHON_COMPILING_IN_CPYTHON
      __pyx_t_2 = PyList_GET_ITEM(__pyx_t_4, __pyx_t_1); __Pyx_INCREF(__pyx_t_2); __pyx_t_1++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      #else
      __pyx_t_2 = PySequence_ITEM(__pyx_t_4, __pyx_t_1); __pyx_t_1++; if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      #endif
    } else if (!__pyx_t_5 && PyTuple_CheckExact(__pyx_t_4)) {
      if (__pyx_t_1 >= PyTuple_GET_SIZE(__pyx_t_4)) break;
      #if CYTHON_COMPILING_IN_CPYTHON
      __pyx_t_2 = PyTuple_GET_ITEM(__pyx_t_4, __pyx_t_1); __Pyx_INCREF(__pyx_t_2); __pyx_t_1++; if (unlikely(0 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      #else
      __pyx_t_2 = PySequence_ITEM(__pyx_t_4, __pyx_t_1); __pyx_t_1++; if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      #endif
    } else {
      __pyx_t_2 = __pyx_t_5(__pyx_t_4);
      if (unlikely(!__pyx_t_2)) {
        if (PyErr_Occurred()) {
          if (likely(PyErr_ExceptionMatches(PyExc_StopIteration))) PyErr_Clear();
          else {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_2);
    }
    __Pyx_XDECREF_SET(__pyx_v_i, __pyx_t_2);
    __pyx_t_2 = 0;

    /* "space_torus\cmodel.pyx":213
 * 
 *         for i in xrange(1, vertex_count + 1):
 *             raw_faces = words[i].split('/')             # <<<<<<<<<<<<<<
 *             l = len(raw_faces)
 * 
 */
    if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_2 = PyObject_GetItem(((PyObject *)__pyx_v_words), __pyx_v_i); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s__split); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = PyObject_Call(__pyx_t_6, ((PyObject *)__pyx_k_tuple_7), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    if (!(likely(PyList_CheckExact(__pyx_t_2))||((__pyx_t_2) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_t_2)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF_SET(__pyx_v_raw_faces, ((PyObject*)__pyx_t_2));
    __pyx_t_2 = 0;

    /* "space_torus\cmodel.pyx":214
 *         for i in xrange(1, vertex_count + 1):
 *             raw_faces = words[i].split('/')
 *             l = len(raw_faces)             # <<<<<<<<<<<<<<
 * 
 *             current_value = int(raw_faces[0])
 */
    if (unlikely(((PyObject *)__pyx_v_raw_faces) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 214; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_7 = PyList_GET_SIZE(((PyObject *)__pyx_v_raw_faces)); if (unlikely(__pyx_t_7 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 214; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_2 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 214; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF_SET(__pyx_v_l, __pyx_t_2);
    __pyx_t_2 = 0;

    /* "space_torus\cmodel.pyx":216
 *             l = len(raw_faces)
 * 
 *             current_value = int(raw_faces[0])             # <<<<<<<<<<<<<<
 * 
 *             vindices.append(current_value - 1)
 */
    if (unlikely(((PyObject *)__pyx_v_raw_faces) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 216; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_raw_faces), 0, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 216; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = PyTuple_New(1); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 216; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
    __Pyx_GIVEREF(__pyx_t_2);
    __pyx_t_2 = 0;
    __pyx_t_2 = PyObject_Call(((PyObject *)((PyObject*)(&PyInt_Type))), ((PyObject *)__pyx_t_6), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 216; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(((PyObject *)__pyx_t_6)); __pyx_t_6 = 0;
    __pyx_t_8 = __Pyx_PyInt_AsInt(__pyx_t_2); if (unlikely((__pyx_t_8 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 216; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_v_current_value = __pyx_t_8;

    /* "space_torus\cmodel.pyx":218
 *             current_value = int(raw_faces[0])
 * 
 *             vindices.append(current_value - 1)             # <<<<<<<<<<<<<<
 *             face_vertices.append(self.vertices[current_value - 1])
 * 
 */
    __pyx_t_2 = PyInt_FromLong((__pyx_v_current_value - 1)); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 218; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_9 = __Pyx_PyList_Append(__pyx_v_vindices, __pyx_t_2); if (unlikely(__pyx_t_9 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 218; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "space_torus\cmodel.pyx":219
 * 
 *             vindices.append(current_value - 1)
 *             face_vertices.append(self.vertices[current_value - 1])             # <<<<<<<<<<<<<<
 * 
 *             if l == 1:
 */
    if (unlikely(((PyObject *)__pyx_v_self->vertices) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_10 = (__pyx_v_current_value - 1);
    __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_self->vertices), __pyx_t_10, sizeof(long), PyInt_FromLong, 1, 1, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_9 = __Pyx_PyList_Append(__pyx_v_face_vertices, __pyx_t_2); if (unlikely(__pyx_t_9 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 219; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "space_torus\cmodel.pyx":221
 *             face_vertices.append(self.vertices[current_value - 1])
 * 
 *             if l == 1:             # <<<<<<<<<<<<<<
 *                 continue
 * 
 */
    __pyx_t_2 = PyObject_RichCompare(__pyx_v_l, __pyx_int_1, Py_EQ); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 221; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_3 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 221; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if (__pyx_t_3) {

      /* "space_torus\cmodel.pyx":222
 * 
 *             if l == 1:
 *                 continue             # <<<<<<<<<<<<<<
 * 
 *             if l >= 2 and raw_faces[1]:
 */
      goto __pyx_L4_continue;
      goto __pyx_L6;
    }
    __pyx_L6:;

    /* "space_torus\cmodel.pyx":224
 *                 continue
 * 
 *             if l >= 2 and raw_faces[1]:             # <<<<<<<<<<<<<<
 *                 current_value = int(raw_faces[1])
 *                 if current_value <= len(self.textures):
 */
    __pyx_t_2 = PyObject_RichCompare(__pyx_v_l, __pyx_int_2, Py_GE); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 224; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_3 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 224; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if (__pyx_t_3) {
      if (unlikely(((PyObject *)__pyx_v_raw_faces) == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
        {__pyx_filename = __pyx_f[0]; __pyx_lineno = 224; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      }
      __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_raw_faces), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 224; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_11 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_11 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 224; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_12 = __pyx_t_11;
    } else {
      __pyx_t_12 = __pyx_t_3;
    }
    if (__pyx_t_12) {

      /* "space_torus\cmodel.pyx":225
 * 
 *             if l >= 2 and raw_faces[1]:
 *                 current_value = int(raw_faces[1])             # <<<<<<<<<<<<<<
 *                 if current_value <= len(self.textures):
 *                     tindices.append(current_value - 1)
 */
      if (unlikely(((PyObject *)__pyx_v_raw_faces) == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
        {__pyx_filename = __pyx_f[0]; __pyx_lineno = 225; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      }
      __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_raw_faces), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 225; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_6 = PyTuple_New(1); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 225; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_6);
      PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
      __Pyx_GIVEREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_t_2 = PyObject_Call(((PyObject *)((PyObject*)(&PyInt_Type))), ((PyObject *)__pyx_t_6), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 225; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(((PyObject *)__pyx_t_6)); __pyx_t_6 = 0;
      __pyx_t_8 = __Pyx_PyInt_AsInt(__pyx_t_2); if (unlikely((__pyx_t_8 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 225; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_v_current_value = __pyx_t_8;

      /* "space_torus\cmodel.pyx":226
 *             if l >= 2 and raw_faces[1]:
 *                 current_value = int(raw_faces[1])
 *                 if current_value <= len(self.textures):             # <<<<<<<<<<<<<<
 *                     tindices.append(current_value - 1)
 *                     face_textures.append(self.textures[current_value - 1])
 */
      __pyx_t_2 = ((PyObject *)__pyx_v_self->textures);
      __Pyx_INCREF(__pyx_t_2);
      if (unlikely(__pyx_t_2 == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
        {__pyx_filename = __pyx_f[0]; __pyx_lineno = 226; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      }
      __pyx_t_7 = PyList_GET_SIZE(__pyx_t_2); if (unlikely(__pyx_t_7 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 226; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_12 = ((__pyx_v_current_value <= __pyx_t_7) != 0);
      if (__pyx_t_12) {

        /* "space_torus\cmodel.pyx":227
 *                 current_value = int(raw_faces[1])
 *                 if current_value <= len(self.textures):
 *                     tindices.append(current_value - 1)             # <<<<<<<<<<<<<<
 *                     face_textures.append(self.textures[current_value - 1])
 *             if l >= 3 and raw_faces[2]:
 */
        __pyx_t_2 = PyInt_FromLong((__pyx_v_current_value - 1)); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 227; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_2);
        __pyx_t_9 = __Pyx_PyList_Append(__pyx_v_tindices, __pyx_t_2); if (unlikely(__pyx_t_9 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 227; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

        /* "space_torus\cmodel.pyx":228
 *                 if current_value <= len(self.textures):
 *                     tindices.append(current_value - 1)
 *                     face_textures.append(self.textures[current_value - 1])             # <<<<<<<<<<<<<<
 *             if l >= 3 and raw_faces[2]:
 *                 current_value = int(raw_faces[2])
 */
        if (unlikely(((PyObject *)__pyx_v_self->textures) == Py_None)) {
          PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
          {__pyx_filename = __pyx_f[0]; __pyx_lineno = 228; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        }
        __pyx_t_10 = (__pyx_v_current_value - 1);
        __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_self->textures), __pyx_t_10, sizeof(long), PyInt_FromLong, 1, 1, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 228; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_GOTREF(__pyx_t_2);
        __pyx_t_9 = __Pyx_PyList_Append(__pyx_v_face_textures, __pyx_t_2); if (unlikely(__pyx_t_9 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 228; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
        goto __pyx_L8;
      }
      __pyx_L8:;
      goto __pyx_L7;
    }
    __pyx_L7:;

    /* "space_torus\cmodel.pyx":229
 *                     tindices.append(current_value - 1)
 *                     face_textures.append(self.textures[current_value - 1])
 *             if l >= 3 and raw_faces[2]:             # <<<<<<<<<<<<<<
 *                 current_value = int(raw_faces[2])
 *                 nindices.append(current_value - 1)
 */
    __pyx_t_2 = PyObject_RichCompare(__pyx_v_l, __pyx_int_3, Py_GE); __Pyx_XGOTREF(__pyx_t_2); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 229; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __pyx_t_12 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_12 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 229; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    if (__pyx_t_12) {
      if (unlikely(((PyObject *)__pyx_v_raw_faces) == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
        {__pyx_filename = __pyx_f[0]; __pyx_lineno = 229; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      }
      __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_raw_faces), 2, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 229; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_3 = __Pyx_PyObject_IsTrue(__pyx_t_2); if (unlikely(__pyx_t_3 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 229; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_t_11 = __pyx_t_3;
    } else {
      __pyx_t_11 = __pyx_t_12;
    }
    if (__pyx_t_11) {

      /* "space_torus\cmodel.pyx":230
 *                     face_textures.append(self.textures[current_value - 1])
 *             if l >= 3 and raw_faces[2]:
 *                 current_value = int(raw_faces[2])             # <<<<<<<<<<<<<<
 *                 nindices.append(current_value - 1)
 *                 face_normals.append(self.normals[current_value - 1])
 */
      if (unlikely(((PyObject *)__pyx_v_raw_faces) == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
        {__pyx_filename = __pyx_f[0]; __pyx_lineno = 230; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      }
      __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_raw_faces), 2, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 230; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_6 = PyTuple_New(1); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 230; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_6);
      PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2);
      __Pyx_GIVEREF(__pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_t_2 = PyObject_Call(((PyObject *)((PyObject*)(&PyInt_Type))), ((PyObject *)__pyx_t_6), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 230; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(((PyObject *)__pyx_t_6)); __pyx_t_6 = 0;
      __pyx_t_8 = __Pyx_PyInt_AsInt(__pyx_t_2); if (unlikely((__pyx_t_8 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 230; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      __pyx_v_current_value = __pyx_t_8;

      /* "space_torus\cmodel.pyx":231
 *             if l >= 3 and raw_faces[2]:
 *                 current_value = int(raw_faces[2])
 *                 nindices.append(current_value - 1)             # <<<<<<<<<<<<<<
 *                 face_normals.append(self.normals[current_value - 1])
 * 
 */
      __pyx_t_2 = PyInt_FromLong((__pyx_v_current_value - 1)); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 231; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_9 = __Pyx_PyList_Append(__pyx_v_nindices, __pyx_t_2); if (unlikely(__pyx_t_9 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 231; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

      /* "space_torus\cmodel.pyx":232
 *                 current_value = int(raw_faces[2])
 *                 nindices.append(current_value - 1)
 *                 face_normals.append(self.normals[current_value - 1])             # <<<<<<<<<<<<<<
 * 
 *         if not self.groups:
 */
      if (unlikely(((PyObject *)__pyx_v_self->normals) == Py_None)) {
        PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
        {__pyx_filename = __pyx_f[0]; __pyx_lineno = 232; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      }
      __pyx_t_10 = (__pyx_v_current_value - 1);
      __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_self->normals), __pyx_t_10, sizeof(long), PyInt_FromLong, 1, 1, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 232; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_GOTREF(__pyx_t_2);
      __pyx_t_9 = __Pyx_PyList_Append(__pyx_v_face_normals, __pyx_t_2); if (unlikely(__pyx_t_9 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 232; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      goto __pyx_L9;
    }
    __pyx_L9:;
    __pyx_L4_continue:;
  }
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "space_torus\cmodel.pyx":234
 *                 face_normals.append(self.normals[current_value - 1])
 * 
 *         if not self.groups:             # <<<<<<<<<<<<<<
 *             group = Group()
 *             self.groups.append(group)
 */
  __pyx_t_11 = (((PyObject *)__pyx_v_self->groups) != Py_None) && (PyList_GET_SIZE(((PyObject *)__pyx_v_self->groups)) != 0);
  __pyx_t_12 = ((!__pyx_t_11) != 0);
  if (__pyx_t_12) {

    /* "space_torus\cmodel.pyx":235
 * 
 *         if not self.groups:
 *             group = Group()             # <<<<<<<<<<<<<<
 *             self.groups.append(group)
 *         else:
 */
    __pyx_t_4 = PyObject_Call(((PyObject *)((PyObject*)__pyx_ptype_11space_torus_6cmodel_Group)), ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 235; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_v_group = __pyx_t_4;
    __pyx_t_4 = 0;

    /* "space_torus\cmodel.pyx":236
 *         if not self.groups:
 *             group = Group()
 *             self.groups.append(group)             # <<<<<<<<<<<<<<
 *         else:
 *             group = self.groups[-1]
 */
    if (unlikely(((PyObject *)__pyx_v_self->groups) == Py_None)) {
      PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%s'", "append");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 236; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_9 = __Pyx_PyList_Append(__pyx_v_self->groups, __pyx_v_group); if (unlikely(__pyx_t_9 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 236; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    goto __pyx_L10;
  }
  /*else*/ {

    /* "space_torus\cmodel.pyx":238
 *             self.groups.append(group)
 *         else:
 *             group = self.groups[-1]             # <<<<<<<<<<<<<<
 *         group.vertices += face_vertices
 *         group.normals += face_normals
 */
    if (unlikely(((PyObject *)__pyx_v_self->groups) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 238; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_4 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_self->groups), -1, sizeof(long), PyInt_FromLong, 1, 1, 1); if (!__pyx_t_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 238; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __pyx_v_group = __pyx_t_4;
    __pyx_t_4 = 0;
  }
  __pyx_L10:;

  /* "space_torus\cmodel.pyx":239
 *         else:
 *             group = self.groups[-1]
 *         group.vertices += face_vertices             # <<<<<<<<<<<<<<
 *         group.normals += face_normals
 *         group.textures += face_textures
 */
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_group, __pyx_n_s__vertices); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 239; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = PyNumber_InPlaceAdd(__pyx_t_4, ((PyObject *)__pyx_v_face_vertices)); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 239; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_group, __pyx_n_s__vertices, __pyx_t_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 239; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":240
 *             group = self.groups[-1]
 *         group.vertices += face_vertices
 *         group.normals += face_normals             # <<<<<<<<<<<<<<
 *         group.textures += face_textures
 * 
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_group, __pyx_n_s__normals); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 240; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = PyNumber_InPlaceAdd(__pyx_t_2, ((PyObject *)__pyx_v_face_normals)); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 240; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_group, __pyx_n_s__normals, __pyx_t_4) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 240; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;

  /* "space_torus\cmodel.pyx":241
 *         group.vertices += face_vertices
 *         group.normals += face_normals
 *         group.textures += face_textures             # <<<<<<<<<<<<<<
 * 
 *         idx_count = group.idx_count
 */
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_v_group, __pyx_n_s__textures); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 241; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_2 = PyNumber_InPlaceAdd(__pyx_t_4, ((PyObject *)__pyx_v_face_textures)); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 241; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_group, __pyx_n_s__textures, __pyx_t_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 241; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":243
 *         group.textures += face_textures
 * 
 *         idx_count = group.idx_count             # <<<<<<<<<<<<<<
 *         group.indices += (idx_count + 1, idx_count + 2, idx_count + 3)
 *         group.idx_count += 3
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_group, __pyx_n_s__idx_count); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 243; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_v_idx_count = __pyx_t_2;
  __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":244
 * 
 *         idx_count = group.idx_count
 *         group.indices += (idx_count + 1, idx_count + 2, idx_count + 3)             # <<<<<<<<<<<<<<
 *         group.idx_count += 3
 * 
 */
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_group, __pyx_n_s__indices); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = PyNumber_Add(__pyx_v_idx_count, __pyx_int_1); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __pyx_t_6 = PyNumber_Add(__pyx_v_idx_count, __pyx_int_2); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_13 = PyNumber_Add(__pyx_v_idx_count, __pyx_int_3); if (unlikely(!__pyx_t_13)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_13);
  __pyx_t_14 = PyTuple_New(3); if (unlikely(!__pyx_t_14)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_14);
  PyTuple_SET_ITEM(__pyx_t_14, 0, __pyx_t_4);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_14, 1, __pyx_t_6);
  __Pyx_GIVEREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_14, 2, __pyx_t_13);
  __Pyx_GIVEREF(__pyx_t_13);
  __pyx_t_4 = 0;
  __pyx_t_6 = 0;
  __pyx_t_13 = 0;
  __pyx_t_13 = PyNumber_InPlaceAdd(__pyx_t_2, ((PyObject *)__pyx_t_14)); if (unlikely(!__pyx_t_13)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_13);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_14)); __pyx_t_14 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_group, __pyx_n_s__indices, __pyx_t_13) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 244; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;

  /* "space_torus\cmodel.pyx":245
 *         idx_count = group.idx_count
 *         group.indices += (idx_count + 1, idx_count + 2, idx_count + 3)
 *         group.idx_count += 3             # <<<<<<<<<<<<<<
 * 
 *         group.faces.append(Face(type, vindices, nindices, tindices, face_vertices, face_normals, face_textures))
 */
  __pyx_t_13 = __Pyx_PyObject_GetAttrStr(__pyx_v_group, __pyx_n_s__idx_count); if (unlikely(!__pyx_t_13)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 245; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_13);
  __pyx_t_14 = PyNumber_InPlaceAdd(__pyx_t_13, __pyx_int_3); if (unlikely(!__pyx_t_14)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 245; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_14);
  __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;
  if (__Pyx_PyObject_SetAttrStr(__pyx_v_group, __pyx_n_s__idx_count, __pyx_t_14) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 245; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;

  /* "space_torus\cmodel.pyx":247
 *         group.idx_count += 3
 * 
 *         group.faces.append(Face(type, vindices, nindices, tindices, face_vertices, face_normals, face_textures))             # <<<<<<<<<<<<<<
 * 
 *     cdef inline mtllib(self, list words):
 */
  __pyx_t_14 = __Pyx_PyObject_GetAttrStr(__pyx_v_group, __pyx_n_s__faces); if (unlikely(!__pyx_t_14)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 247; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_14);
  __pyx_t_13 = PyInt_FromLong(__pyx_v_type); if (unlikely(!__pyx_t_13)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 247; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_13);
  __pyx_t_2 = PyTuple_New(7); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 247; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_13);
  __Pyx_GIVEREF(__pyx_t_13);
  __Pyx_INCREF(((PyObject *)__pyx_v_vindices));
  PyTuple_SET_ITEM(__pyx_t_2, 1, ((PyObject *)__pyx_v_vindices));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_vindices));
  __Pyx_INCREF(((PyObject *)__pyx_v_nindices));
  PyTuple_SET_ITEM(__pyx_t_2, 2, ((PyObject *)__pyx_v_nindices));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_nindices));
  __Pyx_INCREF(((PyObject *)__pyx_v_tindices));
  PyTuple_SET_ITEM(__pyx_t_2, 3, ((PyObject *)__pyx_v_tindices));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_tindices));
  __Pyx_INCREF(((PyObject *)__pyx_v_face_vertices));
  PyTuple_SET_ITEM(__pyx_t_2, 4, ((PyObject *)__pyx_v_face_vertices));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_face_vertices));
  __Pyx_INCREF(((PyObject *)__pyx_v_face_normals));
  PyTuple_SET_ITEM(__pyx_t_2, 5, ((PyObject *)__pyx_v_face_normals));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_face_normals));
  __Pyx_INCREF(((PyObject *)__pyx_v_face_textures));
  PyTuple_SET_ITEM(__pyx_t_2, 6, ((PyObject *)__pyx_v_face_textures));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_face_textures));
  __pyx_t_13 = 0;
  __pyx_t_13 = PyObject_Call(((PyObject *)((PyObject*)__pyx_ptype_11space_torus_6cmodel_Face)), ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_13)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 247; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_13);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_Append(__pyx_t_14, __pyx_t_13); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 247; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
  __Pyx_DECREF(__pyx_t_13); __pyx_t_13 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_13);
  __Pyx_XDECREF(__pyx_t_14);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.f", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_l);
  __Pyx_XDECREF(__pyx_v_face_vertices);
  __Pyx_XDECREF(__pyx_v_face_normals);
  __Pyx_XDECREF(__pyx_v_face_textures);
  __Pyx_XDECREF(__pyx_v_raw_faces);
  __Pyx_XDECREF(__pyx_v_vindices);
  __Pyx_XDECREF(__pyx_v_nindices);
  __Pyx_XDECREF(__pyx_v_vertex_count);
  __Pyx_XDECREF(__pyx_v_tindices);
  __Pyx_XDECREF(__pyx_v_i);
  __Pyx_XDECREF(__pyx_v_group);
  __Pyx_XDECREF(__pyx_v_idx_count);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":249
 *         group.faces.append(Face(type, vindices, nindices, tindices, face_vertices, face_normals, face_textures))
 * 
 *     cdef inline mtllib(self, list words):             # <<<<<<<<<<<<<<
 *         self.dispatch(os.path.join(self.root, words[1]))
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_mtllib(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("mtllib", 0);

  /* "space_torus\cmodel.pyx":250
 * 
 *     cdef inline mtllib(self, list words):
 *         self.dispatch(os.path.join(self.root, words[1]))             # <<<<<<<<<<<<<<
 * 
 *     cdef inline usemtl(self, list words):
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s__os); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s__path); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s__join); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_2 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = PyTuple_New(2); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->root));
  PyTuple_SET_ITEM(__pyx_t_3, 0, ((PyObject *)__pyx_v_self->root));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_self->root));
  PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_2);
  __Pyx_GIVEREF(__pyx_t_2);
  __pyx_t_2 = 0;
  __pyx_t_2 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_t_3), NULL); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_3)); __pyx_t_3 = 0;
  if (!(likely(PyString_CheckExact(__pyx_t_2))||((__pyx_t_2) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected str, got %.200s", Py_TYPE(__pyx_t_2)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_3 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_dispatch(__pyx_v_self, ((PyObject*)__pyx_t_2)); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 250; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.mtllib", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":252
 *         self.dispatch(os.path.join(self.root, words[1]))
 * 
 *     cdef inline usemtl(self, list words):             # <<<<<<<<<<<<<<
 *         mat = words[1]
 *         if mat in self.materials:
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_usemtl(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  PyObject *__pyx_v_mat = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_t_2;
  int __pyx_t_3;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("usemtl", 0);

  /* "space_torus\cmodel.pyx":253
 * 
 *     cdef inline usemtl(self, list words):
 *         mat = words[1]             # <<<<<<<<<<<<<<
 *         if mat in self.materials:
 *             self.groups[-1].material = self.materials[mat]
 */
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 253; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 253; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_v_mat = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "space_torus\cmodel.pyx":254
 *     cdef inline usemtl(self, list words):
 *         mat = words[1]
 *         if mat in self.materials:             # <<<<<<<<<<<<<<
 *             self.groups[-1].material = self.materials[mat]
 *         else:
 */
  if (unlikely(((PyObject *)__pyx_v_self->materials) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 254; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_2 = (__Pyx_PyDict_Contains(__pyx_v_mat, ((PyObject *)__pyx_v_self->materials), Py_EQ)); if (unlikely(__pyx_t_2 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 254; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_3 = (__pyx_t_2 != 0);
  if (__pyx_t_3) {

    /* "space_torus\cmodel.pyx":255
 *         mat = words[1]
 *         if mat in self.materials:
 *             self.groups[-1].material = self.materials[mat]             # <<<<<<<<<<<<<<
 *         else:
 *             print "Warning: material %s undefined." % mat
 */
    if (unlikely(((PyObject *)__pyx_v_self->materials) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 255; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_1 = __Pyx_PyDict_GetItem(((PyObject *)__pyx_v_self->materials), __pyx_v_mat); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 255; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_1);
    if (unlikely(((PyObject *)__pyx_v_self->groups) == Py_None)) {
      PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 255; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
    __pyx_t_4 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_self->groups), -1, sizeof(long), PyInt_FromLong, 1, 1, 1); if (!__pyx_t_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 255; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    if (__Pyx_PyObject_SetAttrStr(__pyx_t_4, __pyx_n_s__material, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 255; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF(__pyx_t_4); __pyx_t_4 = 0;
    goto __pyx_L3;
  }
  /*else*/ {

    /* "space_torus\cmodel.pyx":257
 *             self.groups[-1].material = self.materials[mat]
 *         else:
 *             print "Warning: material %s undefined." % mat             # <<<<<<<<<<<<<<
 * 
 *     cdef inline g(self, list words):
 */
    __pyx_t_4 = PyNumber_Remainder(((PyObject *)__pyx_kp_s_8), __pyx_v_mat); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 257; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(((PyObject *)__pyx_t_4));
    if (__Pyx_PrintOne(0, ((PyObject *)__pyx_t_4)) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 257; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF(((PyObject *)__pyx_t_4)); __pyx_t_4 = 0;
  }
  __pyx_L3:;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.usemtl", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_mat);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":259
 *             print "Warning: material %s undefined." % mat
 * 
 *     cdef inline g(self, list words):             # <<<<<<<<<<<<<<
 *         self.groups.append(Group(words[1]))
 * 
 */

static CYTHON_INLINE PyObject *__pyx_f_11space_torus_6cmodel_15WavefrontObject_g(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_words) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_t_3;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("g", 0);

  /* "space_torus\cmodel.pyx":260
 * 
 *     cdef inline g(self, list words):
 *         self.groups.append(Group(words[1]))             # <<<<<<<<<<<<<<
 * 
 *     def __init__(self, str path):
 */
  if (unlikely(((PyObject *)__pyx_v_self->groups) == Py_None)) {
    PyErr_Format(PyExc_AttributeError, "'NoneType' object has no attribute '%s'", "append");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  if (unlikely(((PyObject *)__pyx_v_words) == Py_None)) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  }
  __pyx_t_1 = __Pyx_GetItemInt_List(((PyObject *)__pyx_v_words), 1, sizeof(long), PyInt_FromLong, 1, 0, 1); if (!__pyx_t_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_1);
  __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_Call(((PyObject *)((PyObject*)__pyx_ptype_11space_torus_6cmodel_Group)), ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  __pyx_t_3 = __Pyx_PyList_Append(__pyx_v_self->groups, __pyx_t_1); if (unlikely(__pyx_t_3 == -1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 260; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.g", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_path = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__path,0};
    PyObject* values[1] = {0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__path)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__init__") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 262; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 1) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
    }
    __pyx_v_path = ((PyObject*)values[0]);
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 1, 1, 1, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 262; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return -1;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_path), (&PyString_Type), 1, "path", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 262; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject___init__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self), __pyx_v_path);
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":262
 *         self.groups.append(Group(words[1]))
 * 
 *     def __init__(self, str path):             # <<<<<<<<<<<<<<
 *         self.root = os.path.dirname(path)
 *         self.vertices = []
 */

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject___init__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_path) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__init__", 0);

  /* "space_torus\cmodel.pyx":263
 * 
 *     def __init__(self, str path):
 *         self.root = os.path.dirname(path)             # <<<<<<<<<<<<<<
 *         self.vertices = []
 *         self.normals = []
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s__os); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 263; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s__path); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 263; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s__dirname); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 263; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 263; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(((PyObject *)__pyx_v_path));
  PyTuple_SET_ITEM(__pyx_t_2, 0, ((PyObject *)__pyx_v_path));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_path));
  __pyx_t_3 = PyObject_Call(__pyx_t_1, ((PyObject *)__pyx_t_2), NULL); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 263; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  if (!(likely(PyString_CheckExact(__pyx_t_3))||((__pyx_t_3) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected str, got %.200s", Py_TYPE(__pyx_t_3)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 263; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GIVEREF(__pyx_t_3);
  __Pyx_GOTREF(__pyx_v_self->root);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->root));
  __pyx_v_self->root = ((PyObject*)__pyx_t_3);
  __pyx_t_3 = 0;

  /* "space_torus\cmodel.pyx":264
 *     def __init__(self, str path):
 *         self.root = os.path.dirname(path)
 *         self.vertices = []             # <<<<<<<<<<<<<<
 *         self.normals = []
 *         self.textures = []
 */
  __pyx_t_3 = PyList_New(0); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 264; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(((PyObject *)__pyx_t_3));
  __Pyx_GOTREF(__pyx_v_self->vertices);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->vertices));
  __pyx_v_self->vertices = ((PyObject*)__pyx_t_3);
  __pyx_t_3 = 0;

  /* "space_torus\cmodel.pyx":265
 *         self.root = os.path.dirname(path)
 *         self.vertices = []
 *         self.normals = []             # <<<<<<<<<<<<<<
 *         self.textures = []
 *         self.groups = []
 */
  __pyx_t_3 = PyList_New(0); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 265; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(((PyObject *)__pyx_t_3));
  __Pyx_GOTREF(__pyx_v_self->normals);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->normals));
  __pyx_v_self->normals = ((PyObject*)__pyx_t_3);
  __pyx_t_3 = 0;

  /* "space_torus\cmodel.pyx":266
 *         self.vertices = []
 *         self.normals = []
 *         self.textures = []             # <<<<<<<<<<<<<<
 *         self.groups = []
 *         self.materials = {}
 */
  __pyx_t_3 = PyList_New(0); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 266; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(((PyObject *)__pyx_t_3));
  __Pyx_GOTREF(__pyx_v_self->textures);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->textures));
  __pyx_v_self->textures = ((PyObject*)__pyx_t_3);
  __pyx_t_3 = 0;

  /* "space_torus\cmodel.pyx":267
 *         self.normals = []
 *         self.textures = []
 *         self.groups = []             # <<<<<<<<<<<<<<
 *         self.materials = {}
 *         self.dispatch(path)
 */
  __pyx_t_3 = PyList_New(0); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 267; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_GIVEREF(((PyObject *)__pyx_t_3));
  __Pyx_GOTREF(__pyx_v_self->groups);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->groups));
  __pyx_v_self->groups = ((PyObject*)__pyx_t_3);
  __pyx_t_3 = 0;

  /* "space_torus\cmodel.pyx":268
 *         self.textures = []
 *         self.groups = []
 *         self.materials = {}             # <<<<<<<<<<<<<<
 *         self.dispatch(path)
 * 
 */
  __pyx_t_3 = PyDict_New(); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 268; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_3));
  __Pyx_GIVEREF(((PyObject *)__pyx_t_3));
  __Pyx_GOTREF(__pyx_v_self->materials);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->materials));
  __pyx_v_self->materials = ((PyObject*)__pyx_t_3);
  __pyx_t_3 = 0;

  /* "space_torus\cmodel.pyx":269
 *         self.groups = []
 *         self.materials = {}
 *         self.dispatch(path)             # <<<<<<<<<<<<<<
 * 
 * cdef class Group(object):
 */
  __pyx_t_3 = __pyx_f_11space_torus_6cmodel_15WavefrontObject_dispatch(__pyx_v_self, __pyx_v_path); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 269; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_15WavefrontObject_4root_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_15WavefrontObject_4root_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_4root___get__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":108
 * 
 * cdef class WavefrontObject(object):
 *     cdef public str root             # <<<<<<<<<<<<<<
 *     cdef public list vertices, normals, textures, groups
 *     cdef public dict materials
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_15WavefrontObject_4root___get__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->root));
  __pyx_r = ((PyObject *)__pyx_v_self->root);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_4root_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_4root_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_4root_2__set__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_4root_2__set__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyString_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected str, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 108; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->root);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->root));
  __pyx_v_self->root = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.root.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_4root_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_4root_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_4root_4__del__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_4root_4__del__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->root);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->root));
  __pyx_v_self->root = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_15WavefrontObject_8vertices_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_15WavefrontObject_8vertices_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8vertices___get__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":109
 * cdef class WavefrontObject(object):
 *     cdef public str root
 *     cdef public list vertices, normals, textures, groups             # <<<<<<<<<<<<<<
 *     cdef public dict materials
 *     cdef Material current_material
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_15WavefrontObject_8vertices___get__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->vertices));
  __pyx_r = ((PyObject *)__pyx_v_self->vertices);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8vertices_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8vertices_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8vertices_2__set__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8vertices_2__set__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 109; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->vertices);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->vertices));
  __pyx_v_self->vertices = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.vertices.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8vertices_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8vertices_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8vertices_4__del__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8vertices_4__del__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->vertices);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->vertices));
  __pyx_v_self->vertices = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_15WavefrontObject_7normals_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_15WavefrontObject_7normals_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_7normals___get__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_15WavefrontObject_7normals___get__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->normals));
  __pyx_r = ((PyObject *)__pyx_v_self->normals);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_7normals_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_7normals_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_7normals_2__set__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_7normals_2__set__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 109; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->normals);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->normals));
  __pyx_v_self->normals = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.normals.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_7normals_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_7normals_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_7normals_4__del__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_7normals_4__del__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->normals);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->normals));
  __pyx_v_self->normals = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_15WavefrontObject_8textures_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_15WavefrontObject_8textures_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8textures___get__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_15WavefrontObject_8textures___get__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->textures));
  __pyx_r = ((PyObject *)__pyx_v_self->textures);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8textures_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8textures_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8textures_2__set__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8textures_2__set__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 109; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->textures);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->textures));
  __pyx_v_self->textures = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.textures.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8textures_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8textures_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8textures_4__del__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_8textures_4__del__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->textures);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->textures));
  __pyx_v_self->textures = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_15WavefrontObject_6groups_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_15WavefrontObject_6groups_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_6groups___get__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_15WavefrontObject_6groups___get__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->groups));
  __pyx_r = ((PyObject *)__pyx_v_self->groups);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_6groups_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_6groups_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_6groups_2__set__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_6groups_2__set__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 109; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->groups);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->groups));
  __pyx_v_self->groups = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.groups.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_6groups_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_6groups_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_6groups_4__del__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_6groups_4__del__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->groups);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->groups));
  __pyx_v_self->groups = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_15WavefrontObject_9materials_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_15WavefrontObject_9materials_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_9materials___get__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":110
 *     cdef public str root
 *     cdef public list vertices, normals, textures, groups
 *     cdef public dict materials             # <<<<<<<<<<<<<<
 *     cdef Material current_material
 *     cdef str type
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_15WavefrontObject_9materials___get__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->materials));
  __pyx_r = ((PyObject *)__pyx_v_self->materials);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_9materials_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_9materials_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_9materials_2__set__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_9materials_2__set__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyDict_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected dict, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 110; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->materials);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->materials));
  __pyx_v_self->materials = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.WavefrontObject.materials.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_9materials_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_15WavefrontObject_9materials_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_15WavefrontObject_9materials_4__del__(((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_15WavefrontObject_9materials_4__del__(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->materials);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->materials));
  __pyx_v_self->materials = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_name = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__name,0};
    PyObject* values[1] = {0};

    /* "space_torus\cmodel.pyx":278
 *     cdef public int idx_count
 * 
 *     def __init__(self, str name=None):             # <<<<<<<<<<<<<<
 *         if not name:
 *             name = clock()
 */
    values[0] = ((PyObject*)Py_None);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__name);
          if (value) { values[0] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__init__") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 278; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_name = ((PyObject*)values[0]);
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 0, 0, 1, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 278; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Group.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return -1;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_name), (&PyString_Type), 1, "name", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 278; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group___init__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self), __pyx_v_name);
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group___init__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_name) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__init__", 0);
  __Pyx_INCREF(__pyx_v_name);

  /* "space_torus\cmodel.pyx":279
 * 
 *     def __init__(self, str name=None):
 *         if not name:             # <<<<<<<<<<<<<<
 *             name = clock()
 *         self.name = name
 */
  __pyx_t_1 = __Pyx_PyObject_IsTrue(((PyObject *)__pyx_v_name)); if (unlikely(__pyx_t_1 < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 279; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_t_2 = ((!__pyx_t_1) != 0);
  if (__pyx_t_2) {

    /* "space_torus\cmodel.pyx":280
 *     def __init__(self, str name=None):
 *         if not name:
 *             name = clock()             # <<<<<<<<<<<<<<
 *         self.name = name
 *         self.material = None
 */
    __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s__clock); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_4 = PyObject_Call(__pyx_t_3, ((PyObject *)__pyx_empty_tuple), NULL); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_GOTREF(__pyx_t_4);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    if (!(likely(PyString_CheckExact(__pyx_t_4))||((__pyx_t_4) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected str, got %.200s", Py_TYPE(__pyx_t_4)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 280; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    __Pyx_DECREF_SET(__pyx_v_name, ((PyObject*)__pyx_t_4));
    __pyx_t_4 = 0;
    goto __pyx_L3;
  }
  __pyx_L3:;

  /* "space_torus\cmodel.pyx":281
 *         if not name:
 *             name = clock()
 *         self.name = name             # <<<<<<<<<<<<<<
 *         self.material = None
 *         self.faces = []
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_name));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_name));
  __Pyx_GOTREF(__pyx_v_self->name);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->name));
  __pyx_v_self->name = __pyx_v_name;

  /* "space_torus\cmodel.pyx":282
 *             name = clock()
 *         self.name = name
 *         self.material = None             # <<<<<<<<<<<<<<
 *         self.faces = []
 *         self.indices = []
 */
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->material);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->material));
  __pyx_v_self->material = ((struct __pyx_obj_11space_torus_6cmodel_Material *)Py_None);

  /* "space_torus\cmodel.pyx":283
 *         self.name = name
 *         self.material = None
 *         self.faces = []             # <<<<<<<<<<<<<<
 *         self.indices = []
 *         self.vertices = []
 */
  __pyx_t_4 = PyList_New(0); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 283; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(((PyObject *)__pyx_t_4));
  __Pyx_GOTREF(__pyx_v_self->faces);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->faces));
  __pyx_v_self->faces = ((PyObject*)__pyx_t_4);
  __pyx_t_4 = 0;

  /* "space_torus\cmodel.pyx":284
 *         self.material = None
 *         self.faces = []
 *         self.indices = []             # <<<<<<<<<<<<<<
 *         self.vertices = []
 *         self.normals = []
 */
  __pyx_t_4 = PyList_New(0); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 284; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(((PyObject *)__pyx_t_4));
  __Pyx_GOTREF(__pyx_v_self->indices);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->indices));
  __pyx_v_self->indices = ((PyObject*)__pyx_t_4);
  __pyx_t_4 = 0;

  /* "space_torus\cmodel.pyx":285
 *         self.faces = []
 *         self.indices = []
 *         self.vertices = []             # <<<<<<<<<<<<<<
 *         self.normals = []
 *         self.textures = []
 */
  __pyx_t_4 = PyList_New(0); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 285; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(((PyObject *)__pyx_t_4));
  __Pyx_GOTREF(__pyx_v_self->vertices);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->vertices));
  __pyx_v_self->vertices = ((PyObject*)__pyx_t_4);
  __pyx_t_4 = 0;

  /* "space_torus\cmodel.pyx":286
 *         self.indices = []
 *         self.vertices = []
 *         self.normals = []             # <<<<<<<<<<<<<<
 *         self.textures = []
 *         self.idx_count = 0
 */
  __pyx_t_4 = PyList_New(0); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 286; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(((PyObject *)__pyx_t_4));
  __Pyx_GOTREF(__pyx_v_self->normals);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->normals));
  __pyx_v_self->normals = ((PyObject*)__pyx_t_4);
  __pyx_t_4 = 0;

  /* "space_torus\cmodel.pyx":287
 *         self.vertices = []
 *         self.normals = []
 *         self.textures = []             # <<<<<<<<<<<<<<
 *         self.idx_count = 0
 * 
 */
  __pyx_t_4 = PyList_New(0); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 287; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_GIVEREF(((PyObject *)__pyx_t_4));
  __Pyx_GOTREF(__pyx_v_self->textures);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->textures));
  __pyx_v_self->textures = ((PyObject*)__pyx_t_4);
  __pyx_t_4 = 0;

  /* "space_torus\cmodel.pyx":288
 *         self.normals = []
 *         self.textures = []
 *         self.idx_count = 0             # <<<<<<<<<<<<<<
 * 
 * cdef class Face(object):
 */
  __pyx_v_self->idx_count = 0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_AddTraceback("space_torus.cmodel.Group.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_name);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_4name_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_4name_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_4name___get__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":272
 * 
 * cdef class Group(object):
 *     cdef public str name             # <<<<<<<<<<<<<<
 *     cdef public tuple min
 *     cdef public Material material
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_4name___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->name));
  __pyx_r = ((PyObject *)__pyx_v_self->name);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_4name_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_4name_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_4name_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_4name_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyString_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected str, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 272; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->name);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->name));
  __pyx_v_self->name = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Group.name.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_4name_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_4name_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_4name_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_4name_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->name);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->name));
  __pyx_v_self->name = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_3min_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_3min_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_3min___get__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":273
 * cdef class Group(object):
 *     cdef public str name
 *     cdef public tuple min             # <<<<<<<<<<<<<<
 *     cdef public Material material
 *     cdef public list faces, indices, vertices, normals, textures
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_3min___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->min));
  __pyx_r = ((PyObject *)__pyx_v_self->min);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_3min_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_3min_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_3min_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_3min_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyTuple_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected tuple, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 273; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->min);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->min));
  __pyx_v_self->min = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Group.min.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_3min_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_3min_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_3min_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_3min_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->min);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->min));
  __pyx_v_self->min = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_8material_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_8material_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_8material___get__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":274
 *     cdef public str name
 *     cdef public tuple min
 *     cdef public Material material             # <<<<<<<<<<<<<<
 *     cdef public list faces, indices, vertices, normals, textures
 *     cdef public int idx_count
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_8material___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->material));
  __pyx_r = ((PyObject *)__pyx_v_self->material);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_8material_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_8material_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_8material_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_8material_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(((__pyx_v_value) == Py_None) || likely(__Pyx_TypeTest(__pyx_v_value, __pyx_ptype_11space_torus_6cmodel_Material))))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 274; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->material);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->material));
  __pyx_v_self->material = ((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Group.material.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_8material_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_8material_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_8material_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_8material_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->material);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->material));
  __pyx_v_self->material = ((struct __pyx_obj_11space_torus_6cmodel_Material *)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_5faces_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_5faces_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_5faces___get__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":275
 *     cdef public tuple min
 *     cdef public Material material
 *     cdef public list faces, indices, vertices, normals, textures             # <<<<<<<<<<<<<<
 *     cdef public int idx_count
 * 
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_5faces___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->faces));
  __pyx_r = ((PyObject *)__pyx_v_self->faces);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_5faces_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_5faces_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_5faces_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_5faces_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 275; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->faces);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->faces));
  __pyx_v_self->faces = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Group.faces.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_5faces_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_5faces_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_5faces_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_5faces_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->faces);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->faces));
  __pyx_v_self->faces = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_7indices_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_7indices_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_7indices___get__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_7indices___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->indices));
  __pyx_r = ((PyObject *)__pyx_v_self->indices);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_7indices_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_7indices_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_7indices_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_7indices_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 275; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->indices);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->indices));
  __pyx_v_self->indices = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Group.indices.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_7indices_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_7indices_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_7indices_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_7indices_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->indices);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->indices));
  __pyx_v_self->indices = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_8vertices_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_8vertices_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_8vertices___get__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_8vertices___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->vertices));
  __pyx_r = ((PyObject *)__pyx_v_self->vertices);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_8vertices_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_8vertices_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_8vertices_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_8vertices_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 275; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->vertices);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->vertices));
  __pyx_v_self->vertices = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Group.vertices.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_8vertices_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_8vertices_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_8vertices_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_8vertices_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->vertices);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->vertices));
  __pyx_v_self->vertices = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_7normals_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_7normals_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_7normals___get__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_7normals___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->normals));
  __pyx_r = ((PyObject *)__pyx_v_self->normals);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_7normals_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_7normals_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_7normals_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_7normals_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 275; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->normals);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->normals));
  __pyx_v_self->normals = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Group.normals.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_7normals_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_7normals_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_7normals_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_7normals_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->normals);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->normals));
  __pyx_v_self->normals = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_8textures_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_8textures_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_8textures___get__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_8textures___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->textures));
  __pyx_r = ((PyObject *)__pyx_v_self->textures);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_8textures_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_8textures_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_8textures_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_8textures_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 275; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->textures);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->textures));
  __pyx_v_self->textures = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Group.textures.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_8textures_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_8textures_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_8textures_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_8textures_4__del__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->textures);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->textures));
  __pyx_v_self->textures = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_9idx_count_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_5Group_9idx_count_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_9idx_count___get__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":276
 *     cdef public Material material
 *     cdef public list faces, indices, vertices, normals, textures
 *     cdef public int idx_count             # <<<<<<<<<<<<<<
 * 
 *     def __init__(self, str name=None):
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_5Group_9idx_count___get__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyInt_FromLong(__pyx_v_self->idx_count); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("space_torus.cmodel.Group.idx_count.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_5Group_9idx_count_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_5Group_9idx_count_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_5Group_9idx_count_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Group *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_5Group_9idx_count_2__set__(struct __pyx_obj_11space_torus_6cmodel_Group *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __Pyx_PyInt_AsInt(__pyx_v_value); if (unlikely((__pyx_t_1 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 276; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_v_self->idx_count = __pyx_t_1;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Group.idx_count.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  int __pyx_v_type;
  PyObject *__pyx_v_verts = 0;
  PyObject *__pyx_v_norms = 0;
  PyObject *__pyx_v_texs = 0;
  PyObject *__pyx_v_vertices = 0;
  PyObject *__pyx_v_normals = 0;
  PyObject *__pyx_v_textures = 0;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__type,&__pyx_n_s__verts,&__pyx_n_s__norms,&__pyx_n_s__texs,&__pyx_n_s__vertices,&__pyx_n_s__normals,&__pyx_n_s__textures,0};
    PyObject* values[7] = {0,0,0,0,0,0,0};
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  7: values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__type)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (likely((values[1] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__verts)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__init__", 1, 7, 7, 1); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
        case  2:
        if (likely((values[2] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__norms)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__init__", 1, 7, 7, 2); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
        case  3:
        if (likely((values[3] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__texs)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__init__", 1, 7, 7, 3); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
        case  4:
        if (likely((values[4] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__vertices)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__init__", 1, 7, 7, 4); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
        case  5:
        if (likely((values[5] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__normals)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__init__", 1, 7, 7, 5); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
        case  6:
        if (likely((values[6] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__textures)) != 0)) kw_args--;
        else {
          __Pyx_RaiseArgtupleInvalid("__init__", 1, 7, 7, 6); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__init__") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else if (PyTuple_GET_SIZE(__pyx_args) != 7) {
      goto __pyx_L5_argtuple_error;
    } else {
      values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
      values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
      values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
      values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
      values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
      values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
      values[6] = PyTuple_GET_ITEM(__pyx_args, 6);
    }
    __pyx_v_type = __Pyx_PyInt_AsInt(values[0]); if (unlikely((__pyx_v_type == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
    __pyx_v_verts = ((PyObject*)values[1]);
    __pyx_v_norms = ((PyObject*)values[2]);
    __pyx_v_texs = ((PyObject*)values[3]);
    __pyx_v_vertices = ((PyObject*)values[4]);
    __pyx_v_normals = ((PyObject*)values[5]);
    __pyx_v_textures = ((PyObject*)values[6]);
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 1, 7, 7, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Face.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return -1;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_verts), (&PyList_Type), 1, "verts", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_norms), (&PyList_Type), 1, "norms", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_texs), (&PyList_Type), 1, "texs", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_vertices), (&PyList_Type), 1, "vertices", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_normals), (&PyList_Type), 1, "normals", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_textures), (&PyList_Type), 1, "textures", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 294; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face___init__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self), __pyx_v_type, __pyx_v_verts, __pyx_v_norms, __pyx_v_texs, __pyx_v_vertices, __pyx_v_normals, __pyx_v_textures);
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":294
 *     cdef public list verts, norms, texs, vertices, normals, textures
 * 
 *     def __init__(self, int type, list verts, list norms, list texs, list vertices, list normals, list textures):             # <<<<<<<<<<<<<<
 *         self.type = type
 *         self.verts = verts
 */

static int __pyx_pf_11space_torus_6cmodel_4Face___init__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, int __pyx_v_type, PyObject *__pyx_v_verts, PyObject *__pyx_v_norms, PyObject *__pyx_v_texs, PyObject *__pyx_v_vertices, PyObject *__pyx_v_normals, PyObject *__pyx_v_textures) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__", 0);

  /* "space_torus\cmodel.pyx":295
 * 
 *     def __init__(self, int type, list verts, list norms, list texs, list vertices, list normals, list textures):
 *         self.type = type             # <<<<<<<<<<<<<<
 *         self.verts = verts
 *         self.norms = norms
 */
  __pyx_v_self->type = __pyx_v_type;

  /* "space_torus\cmodel.pyx":296
 *     def __init__(self, int type, list verts, list norms, list texs, list vertices, list normals, list textures):
 *         self.type = type
 *         self.verts = verts             # <<<<<<<<<<<<<<
 *         self.norms = norms
 *         self.texs = texs
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_verts));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_verts));
  __Pyx_GOTREF(__pyx_v_self->verts);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->verts));
  __pyx_v_self->verts = __pyx_v_verts;

  /* "space_torus\cmodel.pyx":297
 *         self.type = type
 *         self.verts = verts
 *         self.norms = norms             # <<<<<<<<<<<<<<
 *         self.texs = texs
 *         self.vertices = vertices
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_norms));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_norms));
  __Pyx_GOTREF(__pyx_v_self->norms);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->norms));
  __pyx_v_self->norms = __pyx_v_norms;

  /* "space_torus\cmodel.pyx":298
 *         self.verts = verts
 *         self.norms = norms
 *         self.texs = texs             # <<<<<<<<<<<<<<
 *         self.vertices = vertices
 *         self.normals = normals
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_texs));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_texs));
  __Pyx_GOTREF(__pyx_v_self->texs);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->texs));
  __pyx_v_self->texs = __pyx_v_texs;

  /* "space_torus\cmodel.pyx":299
 *         self.norms = norms
 *         self.texs = texs
 *         self.vertices = vertices             # <<<<<<<<<<<<<<
 *         self.normals = normals
 *         self.textures = textures
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_vertices));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_vertices));
  __Pyx_GOTREF(__pyx_v_self->vertices);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->vertices));
  __pyx_v_self->vertices = __pyx_v_vertices;

  /* "space_torus\cmodel.pyx":300
 *         self.texs = texs
 *         self.vertices = vertices
 *         self.normals = normals             # <<<<<<<<<<<<<<
 *         self.textures = textures
 * 
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_normals));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_normals));
  __Pyx_GOTREF(__pyx_v_self->normals);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->normals));
  __pyx_v_self->normals = __pyx_v_normals;

  /* "space_torus\cmodel.pyx":301
 *         self.vertices = vertices
 *         self.normals = normals
 *         self.textures = textures             # <<<<<<<<<<<<<<
 * 
 * cdef class Material(object):
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_textures));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_textures));
  __Pyx_GOTREF(__pyx_v_self->textures);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->textures));
  __pyx_v_self->textures = __pyx_v_textures;

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_4type_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_4type_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_4type___get__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":291
 * 
 * cdef class Face(object):
 *     cdef public int type             # <<<<<<<<<<<<<<
 *     cdef public list verts, norms, texs, vertices, normals, textures
 * 
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_4type___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyInt_FromLong(__pyx_v_self->type); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 291; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("space_torus.cmodel.Face.type.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_4type_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_4type_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_4type_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_4type_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __Pyx_PyInt_AsInt(__pyx_v_value); if (unlikely((__pyx_t_1 == (int)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 291; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_v_self->type = __pyx_t_1;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Face.type.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_5verts_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_5verts_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_5verts___get__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":292
 * cdef class Face(object):
 *     cdef public int type
 *     cdef public list verts, norms, texs, vertices, normals, textures             # <<<<<<<<<<<<<<
 * 
 *     def __init__(self, int type, list verts, list norms, list texs, list vertices, list normals, list textures):
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_5verts___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->verts));
  __pyx_r = ((PyObject *)__pyx_v_self->verts);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_5verts_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_5verts_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_5verts_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_5verts_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->verts);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->verts));
  __pyx_v_self->verts = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Face.verts.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_5verts_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_5verts_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_5verts_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_5verts_4__del__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->verts);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->verts));
  __pyx_v_self->verts = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_5norms_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_5norms_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_5norms___get__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_5norms___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->norms));
  __pyx_r = ((PyObject *)__pyx_v_self->norms);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_5norms_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_5norms_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_5norms_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_5norms_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->norms);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->norms));
  __pyx_v_self->norms = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Face.norms.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_5norms_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_5norms_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_5norms_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_5norms_4__del__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->norms);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->norms));
  __pyx_v_self->norms = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_4texs_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_4texs_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_4texs___get__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_4texs___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->texs));
  __pyx_r = ((PyObject *)__pyx_v_self->texs);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_4texs_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_4texs_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_4texs_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_4texs_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->texs);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->texs));
  __pyx_v_self->texs = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Face.texs.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_4texs_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_4texs_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_4texs_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_4texs_4__del__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->texs);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->texs));
  __pyx_v_self->texs = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_8vertices_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_8vertices_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_8vertices___get__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_8vertices___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->vertices));
  __pyx_r = ((PyObject *)__pyx_v_self->vertices);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_8vertices_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_8vertices_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_8vertices_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_8vertices_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->vertices);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->vertices));
  __pyx_v_self->vertices = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Face.vertices.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_8vertices_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_8vertices_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_8vertices_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_8vertices_4__del__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->vertices);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->vertices));
  __pyx_v_self->vertices = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_7normals_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_7normals_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_7normals___get__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_7normals___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->normals));
  __pyx_r = ((PyObject *)__pyx_v_self->normals);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_7normals_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_7normals_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_7normals_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_7normals_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->normals);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->normals));
  __pyx_v_self->normals = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Face.normals.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_7normals_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_7normals_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_7normals_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_7normals_4__del__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->normals);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->normals));
  __pyx_v_self->normals = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_8textures_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_4Face_8textures_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_8textures___get__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_4Face_8textures___get__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->textures));
  __pyx_r = ((PyObject *)__pyx_v_self->textures);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_8textures_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_8textures_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_8textures_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_8textures_2__set__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyList_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected list, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 292; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->textures);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->textures));
  __pyx_v_self->textures = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Face.textures.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_4Face_8textures_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_4Face_8textures_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_4Face_8textures_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Face *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_4Face_8textures_4__del__(struct __pyx_obj_11space_torus_6cmodel_Face *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->textures);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->textures));
  __pyx_v_self->textures = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_8Material_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_8Material_1__init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_name = 0;
  PyObject *__pyx_v_texture = 0;
  PyObject *__pyx_v_Ka = 0;
  PyObject *__pyx_v_Kd = 0;
  PyObject *__pyx_v_Ks = 0;
  double __pyx_v_shininess;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__ (wrapper)", 0);
  {
    static PyObject **__pyx_pyargnames[] = {&__pyx_n_s__name,&__pyx_n_s__texture,&__pyx_n_s__Ka,&__pyx_n_s__Kd,&__pyx_n_s__Ks,&__pyx_n_s__shininess,0};
    PyObject* values[6] = {0,0,0,0,0,0};

    /* "space_torus\cmodel.pyx":308
 *     cdef public double shininess
 * 
 *     def __init__(self, str name, str texture=None, tuple Ka=(0, 0, 0), tuple Kd=(0, 0, 0), tuple Ks=(0, 0, 0),             # <<<<<<<<<<<<<<
 *                  double shininess=0.0):
 *         self.name = name
 */
    values[1] = ((PyObject*)Py_None);
    values[2] = ((PyObject*)__pyx_k_tuple_9);
    values[3] = ((PyObject*)__pyx_k_tuple_10);
    values[4] = ((PyObject*)__pyx_k_tuple_11);
    if (unlikely(__pyx_kwds)) {
      Py_ssize_t kw_args;
      const Py_ssize_t pos_args = PyTuple_GET_SIZE(__pyx_args);
      switch (pos_args) {
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        case  0: break;
        default: goto __pyx_L5_argtuple_error;
      }
      kw_args = PyDict_Size(__pyx_kwds);
      switch (pos_args) {
        case  0:
        if (likely((values[0] = PyDict_GetItem(__pyx_kwds, __pyx_n_s__name)) != 0)) kw_args--;
        else goto __pyx_L5_argtuple_error;
        case  1:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__texture);
          if (value) { values[1] = value; kw_args--; }
        }
        case  2:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__Ka);
          if (value) { values[2] = value; kw_args--; }
        }
        case  3:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__Kd);
          if (value) { values[3] = value; kw_args--; }
        }
        case  4:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__Ks);
          if (value) { values[4] = value; kw_args--; }
        }
        case  5:
        if (kw_args > 0) {
          PyObject* value = PyDict_GetItem(__pyx_kwds, __pyx_n_s__shininess);
          if (value) { values[5] = value; kw_args--; }
        }
      }
      if (unlikely(kw_args > 0)) {
        if (unlikely(__Pyx_ParseOptionalKeywords(__pyx_kwds, __pyx_pyargnames, 0, values, pos_args, "__init__") < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
      }
    } else {
      switch (PyTuple_GET_SIZE(__pyx_args)) {
        case  6: values[5] = PyTuple_GET_ITEM(__pyx_args, 5);
        case  5: values[4] = PyTuple_GET_ITEM(__pyx_args, 4);
        case  4: values[3] = PyTuple_GET_ITEM(__pyx_args, 3);
        case  3: values[2] = PyTuple_GET_ITEM(__pyx_args, 2);
        case  2: values[1] = PyTuple_GET_ITEM(__pyx_args, 1);
        case  1: values[0] = PyTuple_GET_ITEM(__pyx_args, 0);
        break;
        default: goto __pyx_L5_argtuple_error;
      }
    }
    __pyx_v_name = ((PyObject*)values[0]);
    __pyx_v_texture = ((PyObject*)values[1]);
    __pyx_v_Ka = ((PyObject*)values[2]);
    __pyx_v_Kd = ((PyObject*)values[3]);
    __pyx_v_Ks = ((PyObject*)values[4]);
    if (values[5]) {
      __pyx_v_shininess = __pyx_PyFloat_AsDouble(values[5]); if (unlikely((__pyx_v_shininess == (double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 309; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
    } else {

      /* "space_torus\cmodel.pyx":309
 * 
 *     def __init__(self, str name, str texture=None, tuple Ka=(0, 0, 0), tuple Kd=(0, 0, 0), tuple Ks=(0, 0, 0),
 *                  double shininess=0.0):             # <<<<<<<<<<<<<<
 *         self.name = name
 *         self.texture = texture
 */
      __pyx_v_shininess = ((double)0.0);
    }
  }
  goto __pyx_L4_argument_unpacking_done;
  __pyx_L5_argtuple_error:;
  __Pyx_RaiseArgtupleInvalid("__init__", 0, 1, 6, PyTuple_GET_SIZE(__pyx_args)); {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L3_error;}
  __pyx_L3_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Material.__init__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __Pyx_RefNannyFinishContext();
  return -1;
  __pyx_L4_argument_unpacking_done:;
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_name), (&PyString_Type), 1, "name", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_texture), (&PyString_Type), 1, "texture", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_Ka), (&PyTuple_Type), 1, "Ka", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_Kd), (&PyTuple_Type), 1, "Kd", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (unlikely(!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_Ks), (&PyTuple_Type), 1, "Ks", 1))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material___init__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self), __pyx_v_name, __pyx_v_texture, __pyx_v_Ka, __pyx_v_Kd, __pyx_v_Ks, __pyx_v_shininess);
  goto __pyx_L0;
  __pyx_L1_error:;
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":308
 *     cdef public double shininess
 * 
 *     def __init__(self, str name, str texture=None, tuple Ka=(0, 0, 0), tuple Kd=(0, 0, 0), tuple Ks=(0, 0, 0),             # <<<<<<<<<<<<<<
 *                  double shininess=0.0):
 *         self.name = name
 */

static int __pyx_pf_11space_torus_6cmodel_8Material___init__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_name, PyObject *__pyx_v_texture, PyObject *__pyx_v_Ka, PyObject *__pyx_v_Kd, PyObject *__pyx_v_Ks, double __pyx_v_shininess) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__init__", 0);

  /* "space_torus\cmodel.pyx":310
 *     def __init__(self, str name, str texture=None, tuple Ka=(0, 0, 0), tuple Kd=(0, 0, 0), tuple Ks=(0, 0, 0),
 *                  double shininess=0.0):
 *         self.name = name             # <<<<<<<<<<<<<<
 *         self.texture = texture
 *         self.Ka = Ka
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_name));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_name));
  __Pyx_GOTREF(__pyx_v_self->name);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->name));
  __pyx_v_self->name = __pyx_v_name;

  /* "space_torus\cmodel.pyx":311
 *                  double shininess=0.0):
 *         self.name = name
 *         self.texture = texture             # <<<<<<<<<<<<<<
 *         self.Ka = Ka
 *         self.Kd = Kd
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_texture));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_texture));
  __Pyx_GOTREF(__pyx_v_self->texture);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->texture));
  __pyx_v_self->texture = __pyx_v_texture;

  /* "space_torus\cmodel.pyx":312
 *         self.name = name
 *         self.texture = texture
 *         self.Ka = Ka             # <<<<<<<<<<<<<<
 *         self.Kd = Kd
 *         self.Ks = Ks
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_Ka));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_Ka));
  __Pyx_GOTREF(__pyx_v_self->Ka);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->Ka));
  __pyx_v_self->Ka = __pyx_v_Ka;

  /* "space_torus\cmodel.pyx":313
 *         self.texture = texture
 *         self.Ka = Ka
 *         self.Kd = Kd             # <<<<<<<<<<<<<<
 *         self.Ks = Ks
 *         self.shininess = shininess
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_Kd));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_Kd));
  __Pyx_GOTREF(__pyx_v_self->Kd);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->Kd));
  __pyx_v_self->Kd = __pyx_v_Kd;

  /* "space_torus\cmodel.pyx":314
 *         self.Ka = Ka
 *         self.Kd = Kd
 *         self.Ks = Ks             # <<<<<<<<<<<<<<
 *         self.shininess = shininess
 */
  __Pyx_INCREF(((PyObject *)__pyx_v_Ks));
  __Pyx_GIVEREF(((PyObject *)__pyx_v_Ks));
  __Pyx_GOTREF(__pyx_v_self->Ks);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->Ks));
  __pyx_v_self->Ks = __pyx_v_Ks;

  /* "space_torus\cmodel.pyx":315
 *         self.Kd = Kd
 *         self.Ks = Ks
 *         self.shininess = shininess             # <<<<<<<<<<<<<<
 */
  __pyx_v_self->shininess = __pyx_v_shininess;

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_8Material_4name_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_8Material_4name_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_4name___get__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":304
 * 
 * cdef class Material(object):
 *     cdef public str name, texture             # <<<<<<<<<<<<<<
 *     cdef public tuple Ka, Kd, Ks
 *     cdef public double shininess
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_8Material_4name___get__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->name));
  __pyx_r = ((PyObject *)__pyx_v_self->name);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_8Material_4name_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_8Material_4name_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_4name_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_8Material_4name_2__set__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyString_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected str, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->name);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->name));
  __pyx_v_self->name = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Material.name.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_8Material_4name_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_8Material_4name_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_4name_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_8Material_4name_4__del__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->name);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->name));
  __pyx_v_self->name = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_8Material_7texture_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_8Material_7texture_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_7texture___get__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_8Material_7texture___get__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->texture));
  __pyx_r = ((PyObject *)__pyx_v_self->texture);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_8Material_7texture_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_8Material_7texture_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_7texture_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_8Material_7texture_2__set__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyString_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected str, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->texture);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->texture));
  __pyx_v_self->texture = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Material.texture.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_8Material_7texture_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_8Material_7texture_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_7texture_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_8Material_7texture_4__del__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->texture);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->texture));
  __pyx_v_self->texture = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_8Material_2Ka_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_8Material_2Ka_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_2Ka___get__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":305
 * cdef class Material(object):
 *     cdef public str name, texture
 *     cdef public tuple Ka, Kd, Ks             # <<<<<<<<<<<<<<
 *     cdef public double shininess
 * 
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_8Material_2Ka___get__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->Ka));
  __pyx_r = ((PyObject *)__pyx_v_self->Ka);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_8Material_2Ka_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_8Material_2Ka_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_2Ka_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_8Material_2Ka_2__set__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyTuple_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected tuple, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 305; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->Ka);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->Ka));
  __pyx_v_self->Ka = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Material.Ka.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_8Material_2Ka_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_8Material_2Ka_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_2Ka_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_8Material_2Ka_4__del__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->Ka);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->Ka));
  __pyx_v_self->Ka = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_8Material_2Kd_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_8Material_2Kd_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_2Kd___get__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_8Material_2Kd___get__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->Kd));
  __pyx_r = ((PyObject *)__pyx_v_self->Kd);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_8Material_2Kd_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_8Material_2Kd_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_2Kd_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_8Material_2Kd_2__set__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyTuple_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected tuple, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 305; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->Kd);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->Kd));
  __pyx_v_self->Kd = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Material.Kd.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_8Material_2Kd_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_8Material_2Kd_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_2Kd_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_8Material_2Kd_4__del__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->Kd);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->Kd));
  __pyx_v_self->Kd = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_8Material_2Ks_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_8Material_2Ks_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_2Ks___get__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_11space_torus_6cmodel_8Material_2Ks___get__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __Pyx_INCREF(((PyObject *)__pyx_v_self->Ks));
  __pyx_r = ((PyObject *)__pyx_v_self->Ks);
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_8Material_2Ks_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_8Material_2Ks_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_2Ks_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_8Material_2Ks_2__set__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  if (!(likely(PyTuple_CheckExact(__pyx_v_value))||((__pyx_v_value) == Py_None)||(PyErr_Format(PyExc_TypeError, "Expected tuple, got %.200s", Py_TYPE(__pyx_v_value)->tp_name), 0))) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 305; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_INCREF(__pyx_v_value);
  __Pyx_GIVEREF(__pyx_v_value);
  __Pyx_GOTREF(__pyx_v_self->Ks);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->Ks));
  __pyx_v_self->Ks = ((PyObject*)__pyx_v_value);

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Material.Ks.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_8Material_2Ks_5__del__(PyObject *__pyx_v_self); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_8Material_2Ks_5__del__(PyObject *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_2Ks_4__del__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_8Material_2Ks_4__del__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__del__", 0);
  __Pyx_INCREF(Py_None);
  __Pyx_GIVEREF(Py_None);
  __Pyx_GOTREF(__pyx_v_self->Ks);
  __Pyx_DECREF(((PyObject *)__pyx_v_self->Ks));
  __pyx_v_self->Ks = ((PyObject*)Py_None);

  __pyx_r = 0;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static PyObject *__pyx_pw_11space_torus_6cmodel_8Material_9shininess_1__get__(PyObject *__pyx_v_self); /*proto*/
static PyObject *__pyx_pw_11space_torus_6cmodel_8Material_9shininess_1__get__(PyObject *__pyx_v_self) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__get__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_9shininess___get__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "space_torus\cmodel.pyx":306
 *     cdef public str name, texture
 *     cdef public tuple Ka, Kd, Ks
 *     cdef public double shininess             # <<<<<<<<<<<<<<
 * 
 *     def __init__(self, str name, str texture=None, tuple Ka=(0, 0, 0), tuple Kd=(0, 0, 0), tuple Ks=(0, 0, 0),
 */

static PyObject *__pyx_pf_11space_torus_6cmodel_8Material_9shininess___get__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self) {
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__get__", 0);
  __Pyx_XDECREF(__pyx_r);
  __pyx_t_1 = PyFloat_FromDouble(__pyx_v_self->shininess); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 306; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_r = __pyx_t_1;
  __pyx_t_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_AddTraceback("space_torus.cmodel.Material.shininess.__get__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* Python wrapper */
static int __pyx_pw_11space_torus_6cmodel_8Material_9shininess_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value); /*proto*/
static int __pyx_pw_11space_torus_6cmodel_8Material_9shininess_3__set__(PyObject *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__set__ (wrapper)", 0);
  __pyx_r = __pyx_pf_11space_torus_6cmodel_8Material_9shininess_2__set__(((struct __pyx_obj_11space_torus_6cmodel_Material *)__pyx_v_self), ((PyObject *)__pyx_v_value));
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static int __pyx_pf_11space_torus_6cmodel_8Material_9shininess_2__set__(struct __pyx_obj_11space_torus_6cmodel_Material *__pyx_v_self, PyObject *__pyx_v_value) {
  int __pyx_r;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannySetupContext("__set__", 0);
  __pyx_t_1 = __pyx_PyFloat_AsDouble(__pyx_v_value); if (unlikely((__pyx_t_1 == (double)-1) && PyErr_Occurred())) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 306; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_v_self->shininess = __pyx_t_1;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_AddTraceback("space_torus.cmodel.Material.shininess.__set__", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = -1;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_tp_new_11space_torus_6cmodel_Group(PyTypeObject *t, CYTHON_UNUSED PyObject *a, CYTHON_UNUSED PyObject *k) {
  struct __pyx_obj_11space_torus_6cmodel_Group *p;
  PyObject *o;
  o = (*t->tp_alloc)(t, 0);
  if (unlikely(!o)) return 0;
  p = ((struct __pyx_obj_11space_torus_6cmodel_Group *)o);
  p->name = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->min = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->material = ((struct __pyx_obj_11space_torus_6cmodel_Material *)Py_None); Py_INCREF(Py_None);
  p->faces = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->indices = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->vertices = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->normals = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->textures = ((PyObject*)Py_None); Py_INCREF(Py_None);
  return o;
}

static void __pyx_tp_dealloc_11space_torus_6cmodel_Group(PyObject *o) {
  struct __pyx_obj_11space_torus_6cmodel_Group *p = (struct __pyx_obj_11space_torus_6cmodel_Group *)o;
  PyObject_GC_UnTrack(o);
  Py_CLEAR(p->name);
  Py_CLEAR(p->min);
  Py_CLEAR(p->material);
  Py_CLEAR(p->faces);
  Py_CLEAR(p->indices);
  Py_CLEAR(p->vertices);
  Py_CLEAR(p->normals);
  Py_CLEAR(p->textures);
  (*Py_TYPE(o)->tp_free)(o);
}

static int __pyx_tp_traverse_11space_torus_6cmodel_Group(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_11space_torus_6cmodel_Group *p = (struct __pyx_obj_11space_torus_6cmodel_Group *)o;
  if (p->name) {
    e = (*v)(p->name, a); if (e) return e;
  }
  if (p->min) {
    e = (*v)(p->min, a); if (e) return e;
  }
  if (p->material) {
    e = (*v)(((PyObject*)p->material), a); if (e) return e;
  }
  if (p->faces) {
    e = (*v)(p->faces, a); if (e) return e;
  }
  if (p->indices) {
    e = (*v)(p->indices, a); if (e) return e;
  }
  if (p->vertices) {
    e = (*v)(p->vertices, a); if (e) return e;
  }
  if (p->normals) {
    e = (*v)(p->normals, a); if (e) return e;
  }
  if (p->textures) {
    e = (*v)(p->textures, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_11space_torus_6cmodel_Group(PyObject *o) {
  struct __pyx_obj_11space_torus_6cmodel_Group *p = (struct __pyx_obj_11space_torus_6cmodel_Group *)o;
  PyObject* tmp;
  tmp = ((PyObject*)p->name);
  p->name = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->min);
  p->min = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->material);
  p->material = ((struct __pyx_obj_11space_torus_6cmodel_Material *)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->faces);
  p->faces = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->indices);
  p->indices = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->vertices);
  p->vertices = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->normals);
  p->normals = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->textures);
  p->textures = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  return 0;
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_5Group_name(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_5Group_4name_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_5Group_name(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_5Group_4name_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_5Group_4name_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_5Group_min(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_5Group_3min_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_5Group_min(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_5Group_3min_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_5Group_3min_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_5Group_material(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_5Group_8material_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_5Group_material(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_5Group_8material_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_5Group_8material_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_5Group_faces(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_5Group_5faces_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_5Group_faces(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_5Group_5faces_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_5Group_5faces_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_5Group_indices(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_5Group_7indices_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_5Group_indices(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_5Group_7indices_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_5Group_7indices_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_5Group_vertices(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_5Group_8vertices_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_5Group_vertices(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_5Group_8vertices_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_5Group_8vertices_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_5Group_normals(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_5Group_7normals_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_5Group_normals(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_5Group_7normals_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_5Group_7normals_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_5Group_textures(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_5Group_8textures_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_5Group_textures(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_5Group_8textures_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_5Group_8textures_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_5Group_idx_count(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_5Group_9idx_count_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_5Group_idx_count(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_5Group_9idx_count_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyMethodDef __pyx_methods_11space_torus_6cmodel_Group[] = {
  {0, 0, 0, 0}
};

static struct PyGetSetDef __pyx_getsets_11space_torus_6cmodel_Group[] = {
  {(char *)"name", __pyx_getprop_11space_torus_6cmodel_5Group_name, __pyx_setprop_11space_torus_6cmodel_5Group_name, 0, 0},
  {(char *)"min", __pyx_getprop_11space_torus_6cmodel_5Group_min, __pyx_setprop_11space_torus_6cmodel_5Group_min, 0, 0},
  {(char *)"material", __pyx_getprop_11space_torus_6cmodel_5Group_material, __pyx_setprop_11space_torus_6cmodel_5Group_material, 0, 0},
  {(char *)"faces", __pyx_getprop_11space_torus_6cmodel_5Group_faces, __pyx_setprop_11space_torus_6cmodel_5Group_faces, 0, 0},
  {(char *)"indices", __pyx_getprop_11space_torus_6cmodel_5Group_indices, __pyx_setprop_11space_torus_6cmodel_5Group_indices, 0, 0},
  {(char *)"vertices", __pyx_getprop_11space_torus_6cmodel_5Group_vertices, __pyx_setprop_11space_torus_6cmodel_5Group_vertices, 0, 0},
  {(char *)"normals", __pyx_getprop_11space_torus_6cmodel_5Group_normals, __pyx_setprop_11space_torus_6cmodel_5Group_normals, 0, 0},
  {(char *)"textures", __pyx_getprop_11space_torus_6cmodel_5Group_textures, __pyx_setprop_11space_torus_6cmodel_5Group_textures, 0, 0},
  {(char *)"idx_count", __pyx_getprop_11space_torus_6cmodel_5Group_idx_count, __pyx_setprop_11space_torus_6cmodel_5Group_idx_count, 0, 0},
  {0, 0, 0, 0, 0}
};

static PyTypeObject __pyx_type_11space_torus_6cmodel_Group = {
  PyVarObject_HEAD_INIT(0, 0)
  __Pyx_NAMESTR("space_torus.cmodel.Group"), /*tp_name*/
  sizeof(struct __pyx_obj_11space_torus_6cmodel_Group), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_11space_torus_6cmodel_Group, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  #if PY_MAJOR_VERSION < 3
  0, /*tp_compare*/
  #else
  0, /*reserved*/
  #endif
  0, /*tp_repr*/
  0, /*tp_as_number*/
  0, /*tp_as_sequence*/
  0, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  0, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_VERSION_TAG|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, /*tp_flags*/
  0, /*tp_doc*/
  __pyx_tp_traverse_11space_torus_6cmodel_Group, /*tp_traverse*/
  __pyx_tp_clear_11space_torus_6cmodel_Group, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_11space_torus_6cmodel_Group, /*tp_methods*/
  0, /*tp_members*/
  __pyx_getsets_11space_torus_6cmodel_Group, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_pw_11space_torus_6cmodel_5Group_1__init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_11space_torus_6cmodel_Group, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
  0, /*tp_del*/
  #if PY_VERSION_HEX >= 0x02060000
  0, /*tp_version_tag*/
  #endif
  #if PY_VERSION_HEX >= 0x030400a1 && defined(Py_TPFLAGS_HAVE_FINALIZE)
  0, /*tp_finalize*/
  #endif
};
static struct __pyx_vtabstruct_11space_torus_6cmodel_WavefrontObject __pyx_vtable_11space_torus_6cmodel_WavefrontObject;

static PyObject *__pyx_tp_new_11space_torus_6cmodel_WavefrontObject(PyTypeObject *t, CYTHON_UNUSED PyObject *a, CYTHON_UNUSED PyObject *k) {
  struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *p;
  PyObject *o;
  o = (*t->tp_alloc)(t, 0);
  if (unlikely(!o)) return 0;
  p = ((struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)o);
  p->__pyx_vtab = __pyx_vtabptr_11space_torus_6cmodel_WavefrontObject;
  p->root = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->vertices = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->normals = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->textures = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->groups = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->materials = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->current_material = ((struct __pyx_obj_11space_torus_6cmodel_Material *)Py_None); Py_INCREF(Py_None);
  p->type = ((PyObject*)Py_None); Py_INCREF(Py_None);
  return o;
}

static void __pyx_tp_dealloc_11space_torus_6cmodel_WavefrontObject(PyObject *o) {
  struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *p = (struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)o;
  PyObject_GC_UnTrack(o);
  Py_CLEAR(p->root);
  Py_CLEAR(p->vertices);
  Py_CLEAR(p->normals);
  Py_CLEAR(p->textures);
  Py_CLEAR(p->groups);
  Py_CLEAR(p->materials);
  Py_CLEAR(p->current_material);
  Py_CLEAR(p->type);
  (*Py_TYPE(o)->tp_free)(o);
}

static int __pyx_tp_traverse_11space_torus_6cmodel_WavefrontObject(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *p = (struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)o;
  if (p->root) {
    e = (*v)(p->root, a); if (e) return e;
  }
  if (p->vertices) {
    e = (*v)(p->vertices, a); if (e) return e;
  }
  if (p->normals) {
    e = (*v)(p->normals, a); if (e) return e;
  }
  if (p->textures) {
    e = (*v)(p->textures, a); if (e) return e;
  }
  if (p->groups) {
    e = (*v)(p->groups, a); if (e) return e;
  }
  if (p->materials) {
    e = (*v)(p->materials, a); if (e) return e;
  }
  if (p->current_material) {
    e = (*v)(((PyObject*)p->current_material), a); if (e) return e;
  }
  if (p->type) {
    e = (*v)(p->type, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_11space_torus_6cmodel_WavefrontObject(PyObject *o) {
  struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *p = (struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *)o;
  PyObject* tmp;
  tmp = ((PyObject*)p->root);
  p->root = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->vertices);
  p->vertices = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->normals);
  p->normals = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->textures);
  p->textures = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->groups);
  p->groups = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->materials);
  p->materials = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->current_material);
  p->current_material = ((struct __pyx_obj_11space_torus_6cmodel_Material *)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->type);
  p->type = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  return 0;
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_15WavefrontObject_root(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_4root_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_15WavefrontObject_root(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_4root_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_4root_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_15WavefrontObject_vertices(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8vertices_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_15WavefrontObject_vertices(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8vertices_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8vertices_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_15WavefrontObject_normals(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_7normals_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_15WavefrontObject_normals(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_7normals_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_7normals_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_15WavefrontObject_textures(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8textures_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_15WavefrontObject_textures(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8textures_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_8textures_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_15WavefrontObject_groups(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_6groups_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_15WavefrontObject_groups(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_6groups_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_6groups_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_15WavefrontObject_materials(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_9materials_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_15WavefrontObject_materials(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_9materials_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_15WavefrontObject_9materials_5__del__(o);
  }
}

static PyMethodDef __pyx_methods_11space_torus_6cmodel_WavefrontObject[] = {
  {0, 0, 0, 0}
};

static struct PyGetSetDef __pyx_getsets_11space_torus_6cmodel_WavefrontObject[] = {
  {(char *)"root", __pyx_getprop_11space_torus_6cmodel_15WavefrontObject_root, __pyx_setprop_11space_torus_6cmodel_15WavefrontObject_root, 0, 0},
  {(char *)"vertices", __pyx_getprop_11space_torus_6cmodel_15WavefrontObject_vertices, __pyx_setprop_11space_torus_6cmodel_15WavefrontObject_vertices, 0, 0},
  {(char *)"normals", __pyx_getprop_11space_torus_6cmodel_15WavefrontObject_normals, __pyx_setprop_11space_torus_6cmodel_15WavefrontObject_normals, 0, 0},
  {(char *)"textures", __pyx_getprop_11space_torus_6cmodel_15WavefrontObject_textures, __pyx_setprop_11space_torus_6cmodel_15WavefrontObject_textures, 0, 0},
  {(char *)"groups", __pyx_getprop_11space_torus_6cmodel_15WavefrontObject_groups, __pyx_setprop_11space_torus_6cmodel_15WavefrontObject_groups, 0, 0},
  {(char *)"materials", __pyx_getprop_11space_torus_6cmodel_15WavefrontObject_materials, __pyx_setprop_11space_torus_6cmodel_15WavefrontObject_materials, 0, 0},
  {0, 0, 0, 0, 0}
};

static PyTypeObject __pyx_type_11space_torus_6cmodel_WavefrontObject = {
  PyVarObject_HEAD_INIT(0, 0)
  __Pyx_NAMESTR("space_torus.cmodel.WavefrontObject"), /*tp_name*/
  sizeof(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_11space_torus_6cmodel_WavefrontObject, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  #if PY_MAJOR_VERSION < 3
  0, /*tp_compare*/
  #else
  0, /*reserved*/
  #endif
  0, /*tp_repr*/
  0, /*tp_as_number*/
  0, /*tp_as_sequence*/
  0, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  0, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_VERSION_TAG|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, /*tp_flags*/
  0, /*tp_doc*/
  __pyx_tp_traverse_11space_torus_6cmodel_WavefrontObject, /*tp_traverse*/
  __pyx_tp_clear_11space_torus_6cmodel_WavefrontObject, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_11space_torus_6cmodel_WavefrontObject, /*tp_methods*/
  0, /*tp_members*/
  __pyx_getsets_11space_torus_6cmodel_WavefrontObject, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_pw_11space_torus_6cmodel_15WavefrontObject_1__init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_11space_torus_6cmodel_WavefrontObject, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
  0, /*tp_del*/
  #if PY_VERSION_HEX >= 0x02060000
  0, /*tp_version_tag*/
  #endif
  #if PY_VERSION_HEX >= 0x030400a1 && defined(Py_TPFLAGS_HAVE_FINALIZE)
  0, /*tp_finalize*/
  #endif
};

static PyObject *__pyx_tp_new_11space_torus_6cmodel_Face(PyTypeObject *t, CYTHON_UNUSED PyObject *a, CYTHON_UNUSED PyObject *k) {
  struct __pyx_obj_11space_torus_6cmodel_Face *p;
  PyObject *o;
  o = (*t->tp_alloc)(t, 0);
  if (unlikely(!o)) return 0;
  p = ((struct __pyx_obj_11space_torus_6cmodel_Face *)o);
  p->verts = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->norms = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->texs = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->vertices = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->normals = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->textures = ((PyObject*)Py_None); Py_INCREF(Py_None);
  return o;
}

static void __pyx_tp_dealloc_11space_torus_6cmodel_Face(PyObject *o) {
  struct __pyx_obj_11space_torus_6cmodel_Face *p = (struct __pyx_obj_11space_torus_6cmodel_Face *)o;
  PyObject_GC_UnTrack(o);
  Py_CLEAR(p->verts);
  Py_CLEAR(p->norms);
  Py_CLEAR(p->texs);
  Py_CLEAR(p->vertices);
  Py_CLEAR(p->normals);
  Py_CLEAR(p->textures);
  (*Py_TYPE(o)->tp_free)(o);
}

static int __pyx_tp_traverse_11space_torus_6cmodel_Face(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_11space_torus_6cmodel_Face *p = (struct __pyx_obj_11space_torus_6cmodel_Face *)o;
  if (p->verts) {
    e = (*v)(p->verts, a); if (e) return e;
  }
  if (p->norms) {
    e = (*v)(p->norms, a); if (e) return e;
  }
  if (p->texs) {
    e = (*v)(p->texs, a); if (e) return e;
  }
  if (p->vertices) {
    e = (*v)(p->vertices, a); if (e) return e;
  }
  if (p->normals) {
    e = (*v)(p->normals, a); if (e) return e;
  }
  if (p->textures) {
    e = (*v)(p->textures, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_11space_torus_6cmodel_Face(PyObject *o) {
  struct __pyx_obj_11space_torus_6cmodel_Face *p = (struct __pyx_obj_11space_torus_6cmodel_Face *)o;
  PyObject* tmp;
  tmp = ((PyObject*)p->verts);
  p->verts = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->norms);
  p->norms = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->texs);
  p->texs = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->vertices);
  p->vertices = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->normals);
  p->normals = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->textures);
  p->textures = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  return 0;
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_4Face_type(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_4Face_4type_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_4Face_type(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_4Face_4type_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_4Face_verts(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_4Face_5verts_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_4Face_verts(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_4Face_5verts_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_4Face_5verts_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_4Face_norms(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_4Face_5norms_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_4Face_norms(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_4Face_5norms_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_4Face_5norms_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_4Face_texs(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_4Face_4texs_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_4Face_texs(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_4Face_4texs_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_4Face_4texs_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_4Face_vertices(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_4Face_8vertices_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_4Face_vertices(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_4Face_8vertices_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_4Face_8vertices_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_4Face_normals(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_4Face_7normals_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_4Face_normals(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_4Face_7normals_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_4Face_7normals_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_4Face_textures(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_4Face_8textures_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_4Face_textures(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_4Face_8textures_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_4Face_8textures_5__del__(o);
  }
}

static PyMethodDef __pyx_methods_11space_torus_6cmodel_Face[] = {
  {0, 0, 0, 0}
};

static struct PyGetSetDef __pyx_getsets_11space_torus_6cmodel_Face[] = {
  {(char *)"type", __pyx_getprop_11space_torus_6cmodel_4Face_type, __pyx_setprop_11space_torus_6cmodel_4Face_type, 0, 0},
  {(char *)"verts", __pyx_getprop_11space_torus_6cmodel_4Face_verts, __pyx_setprop_11space_torus_6cmodel_4Face_verts, 0, 0},
  {(char *)"norms", __pyx_getprop_11space_torus_6cmodel_4Face_norms, __pyx_setprop_11space_torus_6cmodel_4Face_norms, 0, 0},
  {(char *)"texs", __pyx_getprop_11space_torus_6cmodel_4Face_texs, __pyx_setprop_11space_torus_6cmodel_4Face_texs, 0, 0},
  {(char *)"vertices", __pyx_getprop_11space_torus_6cmodel_4Face_vertices, __pyx_setprop_11space_torus_6cmodel_4Face_vertices, 0, 0},
  {(char *)"normals", __pyx_getprop_11space_torus_6cmodel_4Face_normals, __pyx_setprop_11space_torus_6cmodel_4Face_normals, 0, 0},
  {(char *)"textures", __pyx_getprop_11space_torus_6cmodel_4Face_textures, __pyx_setprop_11space_torus_6cmodel_4Face_textures, 0, 0},
  {0, 0, 0, 0, 0}
};

static PyTypeObject __pyx_type_11space_torus_6cmodel_Face = {
  PyVarObject_HEAD_INIT(0, 0)
  __Pyx_NAMESTR("space_torus.cmodel.Face"), /*tp_name*/
  sizeof(struct __pyx_obj_11space_torus_6cmodel_Face), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_11space_torus_6cmodel_Face, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  #if PY_MAJOR_VERSION < 3
  0, /*tp_compare*/
  #else
  0, /*reserved*/
  #endif
  0, /*tp_repr*/
  0, /*tp_as_number*/
  0, /*tp_as_sequence*/
  0, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  0, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_VERSION_TAG|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, /*tp_flags*/
  0, /*tp_doc*/
  __pyx_tp_traverse_11space_torus_6cmodel_Face, /*tp_traverse*/
  __pyx_tp_clear_11space_torus_6cmodel_Face, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_11space_torus_6cmodel_Face, /*tp_methods*/
  0, /*tp_members*/
  __pyx_getsets_11space_torus_6cmodel_Face, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_pw_11space_torus_6cmodel_4Face_1__init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_11space_torus_6cmodel_Face, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
  0, /*tp_del*/
  #if PY_VERSION_HEX >= 0x02060000
  0, /*tp_version_tag*/
  #endif
  #if PY_VERSION_HEX >= 0x030400a1 && defined(Py_TPFLAGS_HAVE_FINALIZE)
  0, /*tp_finalize*/
  #endif
};

static PyObject *__pyx_tp_new_11space_torus_6cmodel_Material(PyTypeObject *t, CYTHON_UNUSED PyObject *a, CYTHON_UNUSED PyObject *k) {
  struct __pyx_obj_11space_torus_6cmodel_Material *p;
  PyObject *o;
  o = (*t->tp_alloc)(t, 0);
  if (unlikely(!o)) return 0;
  p = ((struct __pyx_obj_11space_torus_6cmodel_Material *)o);
  p->name = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->texture = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->Ka = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->Kd = ((PyObject*)Py_None); Py_INCREF(Py_None);
  p->Ks = ((PyObject*)Py_None); Py_INCREF(Py_None);
  return o;
}

static void __pyx_tp_dealloc_11space_torus_6cmodel_Material(PyObject *o) {
  struct __pyx_obj_11space_torus_6cmodel_Material *p = (struct __pyx_obj_11space_torus_6cmodel_Material *)o;
  PyObject_GC_UnTrack(o);
  Py_CLEAR(p->name);
  Py_CLEAR(p->texture);
  Py_CLEAR(p->Ka);
  Py_CLEAR(p->Kd);
  Py_CLEAR(p->Ks);
  (*Py_TYPE(o)->tp_free)(o);
}

static int __pyx_tp_traverse_11space_torus_6cmodel_Material(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_11space_torus_6cmodel_Material *p = (struct __pyx_obj_11space_torus_6cmodel_Material *)o;
  if (p->name) {
    e = (*v)(p->name, a); if (e) return e;
  }
  if (p->texture) {
    e = (*v)(p->texture, a); if (e) return e;
  }
  if (p->Ka) {
    e = (*v)(p->Ka, a); if (e) return e;
  }
  if (p->Kd) {
    e = (*v)(p->Kd, a); if (e) return e;
  }
  if (p->Ks) {
    e = (*v)(p->Ks, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_11space_torus_6cmodel_Material(PyObject *o) {
  struct __pyx_obj_11space_torus_6cmodel_Material *p = (struct __pyx_obj_11space_torus_6cmodel_Material *)o;
  PyObject* tmp;
  tmp = ((PyObject*)p->name);
  p->name = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->texture);
  p->texture = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->Ka);
  p->Ka = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->Kd);
  p->Kd = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  tmp = ((PyObject*)p->Ks);
  p->Ks = ((PyObject*)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(tmp);
  return 0;
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_8Material_name(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_8Material_4name_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_8Material_name(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_8Material_4name_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_8Material_4name_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_8Material_texture(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_8Material_7texture_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_8Material_texture(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_8Material_7texture_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_8Material_7texture_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_8Material_Ka(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_8Material_2Ka_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_8Material_Ka(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_8Material_2Ka_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_8Material_2Ka_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_8Material_Kd(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_8Material_2Kd_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_8Material_Kd(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_8Material_2Kd_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_8Material_2Kd_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_8Material_Ks(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_8Material_2Ks_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_8Material_Ks(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_8Material_2Ks_3__set__(o, v);
  }
  else {
    return __pyx_pw_11space_torus_6cmodel_8Material_2Ks_5__del__(o);
  }
}

static PyObject *__pyx_getprop_11space_torus_6cmodel_8Material_shininess(PyObject *o, CYTHON_UNUSED void *x) {
  return __pyx_pw_11space_torus_6cmodel_8Material_9shininess_1__get__(o);
}

static int __pyx_setprop_11space_torus_6cmodel_8Material_shininess(PyObject *o, PyObject *v, CYTHON_UNUSED void *x) {
  if (v) {
    return __pyx_pw_11space_torus_6cmodel_8Material_9shininess_3__set__(o, v);
  }
  else {
    PyErr_SetString(PyExc_NotImplementedError, "__del__");
    return -1;
  }
}

static PyMethodDef __pyx_methods_11space_torus_6cmodel_Material[] = {
  {0, 0, 0, 0}
};

static struct PyGetSetDef __pyx_getsets_11space_torus_6cmodel_Material[] = {
  {(char *)"name", __pyx_getprop_11space_torus_6cmodel_8Material_name, __pyx_setprop_11space_torus_6cmodel_8Material_name, 0, 0},
  {(char *)"texture", __pyx_getprop_11space_torus_6cmodel_8Material_texture, __pyx_setprop_11space_torus_6cmodel_8Material_texture, 0, 0},
  {(char *)"Ka", __pyx_getprop_11space_torus_6cmodel_8Material_Ka, __pyx_setprop_11space_torus_6cmodel_8Material_Ka, 0, 0},
  {(char *)"Kd", __pyx_getprop_11space_torus_6cmodel_8Material_Kd, __pyx_setprop_11space_torus_6cmodel_8Material_Kd, 0, 0},
  {(char *)"Ks", __pyx_getprop_11space_torus_6cmodel_8Material_Ks, __pyx_setprop_11space_torus_6cmodel_8Material_Ks, 0, 0},
  {(char *)"shininess", __pyx_getprop_11space_torus_6cmodel_8Material_shininess, __pyx_setprop_11space_torus_6cmodel_8Material_shininess, 0, 0},
  {0, 0, 0, 0, 0}
};

static PyTypeObject __pyx_type_11space_torus_6cmodel_Material = {
  PyVarObject_HEAD_INIT(0, 0)
  __Pyx_NAMESTR("space_torus.cmodel.Material"), /*tp_name*/
  sizeof(struct __pyx_obj_11space_torus_6cmodel_Material), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_11space_torus_6cmodel_Material, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  #if PY_MAJOR_VERSION < 3
  0, /*tp_compare*/
  #else
  0, /*reserved*/
  #endif
  0, /*tp_repr*/
  0, /*tp_as_number*/
  0, /*tp_as_sequence*/
  0, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  0, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_HAVE_VERSION_TAG|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_NEWBUFFER|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, /*tp_flags*/
  0, /*tp_doc*/
  __pyx_tp_traverse_11space_torus_6cmodel_Material, /*tp_traverse*/
  __pyx_tp_clear_11space_torus_6cmodel_Material, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_11space_torus_6cmodel_Material, /*tp_methods*/
  0, /*tp_members*/
  __pyx_getsets_11space_torus_6cmodel_Material, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_pw_11space_torus_6cmodel_8Material_1__init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_11space_torus_6cmodel_Material, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
  0, /*tp_del*/
  #if PY_VERSION_HEX >= 0x02060000
  0, /*tp_version_tag*/
  #endif
  #if PY_VERSION_HEX >= 0x030400a1 && defined(Py_TPFLAGS_HAVE_FINALIZE)
  0, /*tp_finalize*/
  #endif
};

static PyMethodDef __pyx_methods[] = {
  {__Pyx_NAMESTR("model_list"), (PyCFunction)__pyx_pw_11space_torus_6cmodel_1model_list, METH_VARARGS|METH_KEYWORDS, __Pyx_DOCSTR(0)},
  {0, 0, 0, 0}
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef __pyx_moduledef = {
  #if PY_VERSION_HEX < 0x03020000
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL },
  #else
    PyModuleDef_HEAD_INIT,
  #endif
    __Pyx_NAMESTR("cmodel"),
    0, /* m_doc */
    -1, /* m_size */
    __pyx_methods /* m_methods */,
    NULL, /* m_reload */
    NULL, /* m_traverse */
    NULL, /* m_clear */
    NULL /* m_free */
};
#endif

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_n_s_12, __pyx_k_12, sizeof(__pyx_k_12), 0, 0, 1, 1},
  {&__pyx_n_s_13, __pyx_k_13, sizeof(__pyx_k_13), 0, 0, 1, 1},
  {&__pyx_kp_s_16, __pyx_k_16, sizeof(__pyx_k_16), 0, 0, 1, 0},
  {&__pyx_n_s_17, __pyx_k_17, sizeof(__pyx_k_17), 0, 0, 1, 1},
  {&__pyx_kp_s_3, __pyx_k_3, sizeof(__pyx_k_3), 0, 0, 1, 0},
  {&__pyx_kp_s_4, __pyx_k_4, sizeof(__pyx_k_4), 0, 0, 1, 0},
  {&__pyx_kp_s_6, __pyx_k_6, sizeof(__pyx_k_6), 0, 0, 1, 0},
  {&__pyx_kp_s_8, __pyx_k_8, sizeof(__pyx_k_8), 0, 0, 1, 0},
  {&__pyx_n_s__Ka, __pyx_k__Ka, sizeof(__pyx_k__Ka), 0, 0, 1, 1},
  {&__pyx_n_s__Kd, __pyx_k__Kd, sizeof(__pyx_k__Kd), 0, 0, 1, 1},
  {&__pyx_n_s__Ks, __pyx_k__Ks, sizeof(__pyx_k__Ks), 0, 0, 1, 1},
  {&__pyx_n_s____enter__, __pyx_k____enter__, sizeof(__pyx_k____enter__), 0, 0, 1, 1},
  {&__pyx_n_s____exit__, __pyx_k____exit__, sizeof(__pyx_k____exit__), 0, 0, 1, 1},
  {&__pyx_n_s____file__, __pyx_k____file__, sizeof(__pyx_k____file__), 0, 0, 1, 1},
  {&__pyx_n_s____import__, __pyx_k____import__, sizeof(__pyx_k____import__), 0, 0, 1, 1},
  {&__pyx_n_s____main__, __pyx_k____main__, sizeof(__pyx_k____main__), 0, 0, 1, 1},
  {&__pyx_n_s____pyx_vtable__, __pyx_k____pyx_vtable__, sizeof(__pyx_k____pyx_vtable__), 0, 0, 1, 1},
  {&__pyx_n_s____test__, __pyx_k____test__, sizeof(__pyx_k____test__), 0, 0, 1, 1},
  {&__pyx_n_s__append, __pyx_k__append, sizeof(__pyx_k__append), 0, 0, 1, 1},
  {&__pyx_n_s__assets, __pyx_k__assets, sizeof(__pyx_k__assets), 0, 0, 1, 1},
  {&__pyx_n_s__clock, __pyx_k__clock, sizeof(__pyx_k__clock), 0, 0, 1, 1},
  {&__pyx_n_s__dirname, __pyx_k__dirname, sizeof(__pyx_k__dirname), 0, 0, 1, 1},
  {&__pyx_n_s__end, __pyx_k__end, sizeof(__pyx_k__end), 0, 0, 1, 1},
  {&__pyx_n_s__faces, __pyx_k__faces, sizeof(__pyx_k__faces), 0, 0, 1, 1},
  {&__pyx_n_s__file, __pyx_k__file, sizeof(__pyx_k__file), 0, 0, 1, 1},
  {&__pyx_n_s__idx_count, __pyx_k__idx_count, sizeof(__pyx_k__idx_count), 0, 0, 1, 1},
  {&__pyx_n_s__indices, __pyx_k__indices, sizeof(__pyx_k__indices), 0, 0, 1, 1},
  {&__pyx_n_s__iteritems, __pyx_k__iteritems, sizeof(__pyx_k__iteritems), 0, 0, 1, 1},
  {&__pyx_n_s__join, __pyx_k__join, sizeof(__pyx_k__join), 0, 0, 1, 1},
  {&__pyx_n_s__load_model, __pyx_k__load_model, sizeof(__pyx_k__load_model), 0, 0, 1, 1},
  {&__pyx_n_s__load_texture, __pyx_k__load_texture, sizeof(__pyx_k__load_texture), 0, 0, 1, 1},
  {&__pyx_n_s__material, __pyx_k__material, sizeof(__pyx_k__material), 0, 0, 1, 1},
  {&__pyx_n_s__model, __pyx_k__model, sizeof(__pyx_k__model), 0, 0, 1, 1},
  {&__pyx_n_s__models, __pyx_k__models, sizeof(__pyx_k__models), 0, 0, 1, 1},
  {&__pyx_n_s__name, __pyx_k__name, sizeof(__pyx_k__name), 0, 0, 1, 1},
  {&__pyx_n_s__normals, __pyx_k__normals, sizeof(__pyx_k__normals), 0, 0, 1, 1},
  {&__pyx_n_s__norms, __pyx_k__norms, sizeof(__pyx_k__norms), 0, 0, 1, 1},
  {&__pyx_n_s__open, __pyx_k__open, sizeof(__pyx_k__open), 0, 0, 1, 1},
  {&__pyx_n_s__os, __pyx_k__os, sizeof(__pyx_k__os), 0, 0, 1, 1},
  {&__pyx_n_s__path, __pyx_k__path, sizeof(__pyx_k__path), 0, 0, 1, 1},
  {&__pyx_n_s__print, __pyx_k__print, sizeof(__pyx_k__print), 0, 0, 1, 1},
  {&__pyx_n_s__r, __pyx_k__r, sizeof(__pyx_k__r), 0, 0, 1, 1},
  {&__pyx_n_s__range, __pyx_k__range, sizeof(__pyx_k__range), 0, 0, 1, 1},
  {&__pyx_n_s__rotation, __pyx_k__rotation, sizeof(__pyx_k__rotation), 0, 0, 1, 1},
  {&__pyx_n_s__shininess, __pyx_k__shininess, sizeof(__pyx_k__shininess), 0, 0, 1, 1},
  {&__pyx_n_s__split, __pyx_k__split, sizeof(__pyx_k__split), 0, 0, 1, 1},
  {&__pyx_n_s__strip, __pyx_k__strip, sizeof(__pyx_k__strip), 0, 0, 1, 1},
  {&__pyx_n_s__sx, __pyx_k__sx, sizeof(__pyx_k__sx), 0, 0, 1, 1},
  {&__pyx_n_s__sy, __pyx_k__sy, sizeof(__pyx_k__sy), 0, 0, 1, 1},
  {&__pyx_n_s__sz, __pyx_k__sz, sizeof(__pyx_k__sz), 0, 0, 1, 1},
  {&__pyx_n_s__texs, __pyx_k__texs, sizeof(__pyx_k__texs), 0, 0, 1, 1},
  {&__pyx_n_s__texture, __pyx_k__texture, sizeof(__pyx_k__texture), 0, 0, 1, 1},
  {&__pyx_n_s__textures, __pyx_k__textures, sizeof(__pyx_k__textures), 0, 0, 1, 1},
  {&__pyx_n_s__time, __pyx_k__time, sizeof(__pyx_k__time), 0, 0, 1, 1},
  {&__pyx_n_s__type, __pyx_k__type, sizeof(__pyx_k__type), 0, 0, 1, 1},
  {&__pyx_n_s__vertices, __pyx_k__vertices, sizeof(__pyx_k__vertices), 0, 0, 1, 1},
  {&__pyx_n_s__verts, __pyx_k__verts, sizeof(__pyx_k__verts), 0, 0, 1, 1},
  {&__pyx_n_s__xrange, __pyx_k__xrange, sizeof(__pyx_k__xrange), 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0}
};
static int __Pyx_InitCachedBuiltins(void) {
  __pyx_builtin_open = __Pyx_GetBuiltinName(__pyx_n_s__open); if (!__pyx_builtin_open) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #if PY_MAJOR_VERSION >= 3
  __pyx_builtin_xrange = __Pyx_GetBuiltinName(__pyx_n_s__range); if (!__pyx_builtin_xrange) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #else
  __pyx_builtin_xrange = __Pyx_GetBuiltinName(__pyx_n_s__xrange); if (!__pyx_builtin_xrange) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  return 0;
  __pyx_L1_error:;
  return -1;
}

static int __Pyx_InitCachedConstants(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_InitCachedConstants", 0);

  /* "space_torus\cmodel.pyx":26
 *     glVertex3f(x * sx, y * sy, z * sz)
 * 
 * cpdef model_list(WavefrontObject model, float sx=1, float sy=1, float sz=1, tuple rotation=(0, 0, 0)):             # <<<<<<<<<<<<<<
 *     for m, text in model.materials.iteritems():
 *         if text.texture:
 */
  __pyx_k_tuple_1 = PyTuple_Pack(3, __pyx_int_0, __pyx_int_0, __pyx_int_0); if (unlikely(!__pyx_k_tuple_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_1);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_1));
  __pyx_k_tuple_2 = PyTuple_Pack(3, __pyx_int_0, __pyx_int_0, __pyx_int_0); if (unlikely(!__pyx_k_tuple_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_2);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_2));

  /* "space_torus\cmodel.pyx":116
 * 
 *     cdef inline dispatch(self, str p):
 *         with open(p, 'r') as file:             # <<<<<<<<<<<<<<
 *             for line in file:
 *                 line = line.strip()
 */
  __pyx_k_tuple_5 = PyTuple_Pack(3, Py_None, Py_None, Py_None); if (unlikely(!__pyx_k_tuple_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 116; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_5);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_5));

  /* "space_torus\cmodel.pyx":213
 * 
 *         for i in xrange(1, vertex_count + 1):
 *             raw_faces = words[i].split('/')             # <<<<<<<<<<<<<<
 *             l = len(raw_faces)
 * 
 */
  __pyx_k_tuple_7 = PyTuple_Pack(1, ((PyObject *)__pyx_kp_s_6)); if (unlikely(!__pyx_k_tuple_7)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 213; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_7);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_7));

  /* "space_torus\cmodel.pyx":308
 *     cdef public double shininess
 * 
 *     def __init__(self, str name, str texture=None, tuple Ka=(0, 0, 0), tuple Kd=(0, 0, 0), tuple Ks=(0, 0, 0),             # <<<<<<<<<<<<<<
 *                  double shininess=0.0):
 *         self.name = name
 */
  __pyx_k_tuple_9 = PyTuple_Pack(3, __pyx_int_0, __pyx_int_0, __pyx_int_0); if (unlikely(!__pyx_k_tuple_9)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_9);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_9));
  __pyx_k_tuple_10 = PyTuple_Pack(3, __pyx_int_0, __pyx_int_0, __pyx_int_0); if (unlikely(!__pyx_k_tuple_10)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_10);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_10));
  __pyx_k_tuple_11 = PyTuple_Pack(3, __pyx_int_0, __pyx_int_0, __pyx_int_0); if (unlikely(!__pyx_k_tuple_11)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 308; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_11);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_11));

  /* "space_torus\cmodel.pyx":103
 *     return display
 * 
 * def load_model(path):             # <<<<<<<<<<<<<<
 *     print "Loading model %s..." % path
 *     return WavefrontObject(os.path.join(os.path.dirname(__file__), 'assets', 'models', path))
 */
  __pyx_k_tuple_14 = PyTuple_Pack(1, ((PyObject *)__pyx_n_s__path)); if (unlikely(!__pyx_k_tuple_14)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 103; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_k_tuple_14);
  __Pyx_GIVEREF(((PyObject *)__pyx_k_tuple_14));
  __pyx_k_codeobj_15 = (PyObject*)__Pyx_PyCode_New(1, 0, 1, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_k_tuple_14, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_16, __pyx_n_s__load_model, 103, __pyx_empty_bytes); if (unlikely(!__pyx_k_codeobj_15)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 103; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_InitGlobals(void) {
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_0 = PyInt_FromLong(0); if (unlikely(!__pyx_int_0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_1 = PyInt_FromLong(1); if (unlikely(!__pyx_int_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_2 = PyInt_FromLong(2); if (unlikely(!__pyx_int_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_3 = PyInt_FromLong(3); if (unlikely(!__pyx_int_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_4 = PyInt_FromLong(4); if (unlikely(!__pyx_int_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  return 0;
  __pyx_L1_error:;
  return -1;
}

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initcmodel(void); /*proto*/
PyMODINIT_FUNC initcmodel(void)
#else
PyMODINIT_FUNC PyInit_cmodel(void); /*proto*/
PyMODINIT_FUNC PyInit_cmodel(void)
#endif
{
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannyDeclarations
  #if CYTHON_REFNANNY
  __Pyx_RefNanny = __Pyx_RefNannyImportAPI("refnanny");
  if (!__Pyx_RefNanny) {
      PyErr_Clear();
      __Pyx_RefNanny = __Pyx_RefNannyImportAPI("Cython.Runtime.refnanny");
      if (!__Pyx_RefNanny)
          Py_FatalError("failed to import 'refnanny' module");
  }
  #endif
  __Pyx_RefNannySetupContext("PyMODINIT_FUNC PyInit_cmodel(void)", 0);
  if ( __Pyx_check_binary_version() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_empty_tuple = PyTuple_New(0); if (unlikely(!__pyx_empty_tuple)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_empty_bytes = PyBytes_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_bytes)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #ifdef __Pyx_CyFunction_USED
  if (__Pyx_CyFunction_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  #ifdef __Pyx_FusedFunction_USED
  if (__pyx_FusedFunction_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  #ifdef __Pyx_Generator_USED
  if (__pyx_Generator_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  /*--- Library function declarations ---*/
  /*--- Threads initialization code ---*/
  #if defined(__PYX_FORCE_INIT_THREADS) && __PYX_FORCE_INIT_THREADS
  #ifdef WITH_THREAD /* Python build with threading support? */
  PyEval_InitThreads();
  #endif
  #endif
  /*--- Module creation code ---*/
  #if PY_MAJOR_VERSION < 3
  __pyx_m = Py_InitModule4(__Pyx_NAMESTR("cmodel"), __pyx_methods, 0, 0, PYTHON_API_VERSION); Py_XINCREF(__pyx_m);
  #else
  __pyx_m = PyModule_Create(&__pyx_moduledef);
  #endif
  if (unlikely(!__pyx_m)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_d = PyModule_GetDict(__pyx_m); if (unlikely(!__pyx_d)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  Py_INCREF(__pyx_d);
  #if PY_MAJOR_VERSION >= 3
  {
    PyObject *modules = PyImport_GetModuleDict(); if (unlikely(!modules)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    if (!PyDict_GetItemString(modules, "space_torus.cmodel")) {
      if (unlikely(PyDict_SetItemString(modules, "space_torus.cmodel", __pyx_m) < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
  }
  #endif
  __pyx_b = PyImport_AddModule(__Pyx_NAMESTR(__Pyx_BUILTIN_MODULE_NAME)); if (unlikely(!__pyx_b)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #if CYTHON_COMPILING_IN_PYPY
  Py_INCREF(__pyx_b);
  #endif
  if (__Pyx_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  /*--- Initialize various global constants etc. ---*/
  if (unlikely(__Pyx_InitGlobals() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #if PY_MAJOR_VERSION < 3 && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
  if (__Pyx_init_sys_getdefaultencoding_params() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  if (__pyx_module_is_main_space_torus__cmodel) {
    if (__Pyx_SetAttrString(__pyx_m, "__name__", __pyx_n_s____main__) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  }
  /*--- Builtin init code ---*/
  if (unlikely(__Pyx_InitCachedBuiltins() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  /*--- Constants init code ---*/
  if (unlikely(__Pyx_InitCachedConstants() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  /*--- Global init code ---*/
  /*--- Variable export code ---*/
  /*--- Function export code ---*/
  /*--- Type init code ---*/
  if (PyType_Ready(&__pyx_type_11space_torus_6cmodel_Group) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 271; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_SetAttrString(__pyx_m, "Group", (PyObject *)&__pyx_type_11space_torus_6cmodel_Group) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 271; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_ptype_11space_torus_6cmodel_Group = &__pyx_type_11space_torus_6cmodel_Group;
  __pyx_vtabptr_11space_torus_6cmodel_WavefrontObject = &__pyx_vtable_11space_torus_6cmodel_WavefrontObject;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.dispatch = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_dispatch;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.newmtl = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_newmtl;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.Ka = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_Ka;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.Kd = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_Kd;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.Ks = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_Ks;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.Ns = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_Ns;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.map_Kd = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_map_Kd;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.v = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_v;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.vn = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_vn;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.vt = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_vt;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.f = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_f;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.mtllib = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_mtllib;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.usemtl = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_usemtl;
  __pyx_vtable_11space_torus_6cmodel_WavefrontObject.g = (PyObject *(*)(struct __pyx_obj_11space_torus_6cmodel_WavefrontObject *, PyObject *))__pyx_f_11space_torus_6cmodel_15WavefrontObject_g;
  if (PyType_Ready(&__pyx_type_11space_torus_6cmodel_WavefrontObject) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 107; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_SetVtable(__pyx_type_11space_torus_6cmodel_WavefrontObject.tp_dict, __pyx_vtabptr_11space_torus_6cmodel_WavefrontObject) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 107; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_SetAttrString(__pyx_m, "WavefrontObject", (PyObject *)&__pyx_type_11space_torus_6cmodel_WavefrontObject) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 107; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_ptype_11space_torus_6cmodel_WavefrontObject = &__pyx_type_11space_torus_6cmodel_WavefrontObject;
  if (PyType_Ready(&__pyx_type_11space_torus_6cmodel_Face) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 290; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_SetAttrString(__pyx_m, "Face", (PyObject *)&__pyx_type_11space_torus_6cmodel_Face) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 290; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_ptype_11space_torus_6cmodel_Face = &__pyx_type_11space_torus_6cmodel_Face;
  if (PyType_Ready(&__pyx_type_11space_torus_6cmodel_Material) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 303; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (__Pyx_SetAttrString(__pyx_m, "Material", (PyObject *)&__pyx_type_11space_torus_6cmodel_Material) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 303; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_ptype_11space_torus_6cmodel_Material = &__pyx_type_11space_torus_6cmodel_Material;
  /*--- Type import code ---*/
  /*--- Variable import code ---*/
  /*--- Function import code ---*/
  /*--- Execution code ---*/

  /* "space_torus\cmodel.pyx":1
 * from time import clock             # <<<<<<<<<<<<<<
 * import os.path
 * 
 */
  __pyx_t_1 = PyList_New(1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__clock));
  PyList_SET_ITEM(__pyx_t_1, 0, ((PyObject *)__pyx_n_s__clock));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__clock));
  __pyx_t_2 = __Pyx_Import(((PyObject *)__pyx_n_s__time), ((PyObject *)__pyx_t_1), -1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s__clock); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s__clock, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":2
 * from time import clock
 * import os.path             # <<<<<<<<<<<<<<
 * 
 * from libc.string cimport strncmp, strcmp
 */
  __pyx_t_2 = __Pyx_Import(((PyObject *)__pyx_n_s_12), 0, -1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 2; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s__os, __pyx_t_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 2; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "space_torus\cmodel.pyx":9
 * include "_cyopengl.pxi"
 * 
 * from space_torus.texture import load_texture             # <<<<<<<<<<<<<<
 * 
 * cdef enum:
 */
  __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 9; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(((PyObject *)__pyx_n_s__load_texture));
  PyList_SET_ITEM(__pyx_t_2, 0, ((PyObject *)__pyx_n_s__load_texture));
  __Pyx_GIVEREF(((PyObject *)__pyx_n_s__load_texture));
  __pyx_t_1 = __Pyx_Import(((PyObject *)__pyx_n_s_13), ((PyObject *)__pyx_t_2), -1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 9; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(((PyObject *)__pyx_t_2)); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s__load_texture); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 9; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s__load_texture, __pyx_t_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 9; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "space_torus\cmodel.pyx":103
 *     return display
 * 
 * def load_model(path):             # <<<<<<<<<<<<<<
 *     print "Loading model %s..." % path
 *     return WavefrontObject(os.path.join(os.path.dirname(__file__), 'assets', 'models', path))
 */
  __pyx_t_1 = PyCFunction_NewEx(&__pyx_mdef_11space_torus_6cmodel_3load_model, NULL, __pyx_n_s_17); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 103; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s__load_model, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 103; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "space_torus\cmodel.pyx":1
 * from time import clock             # <<<<<<<<<<<<<<
 * import os.path
 * 
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(((PyObject *)__pyx_t_1));
  if (PyDict_SetItem(__pyx_d, __pyx_n_s____test__, ((PyObject *)__pyx_t_1)) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(((PyObject *)__pyx_t_1)); __pyx_t_1 = 0;
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  if (__pyx_m) {
    __Pyx_AddTraceback("init space_torus.cmodel", __pyx_clineno, __pyx_lineno, __pyx_filename);
    Py_DECREF(__pyx_m); __pyx_m = 0;
  } else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_ImportError, "init space_torus.cmodel");
  }
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  #if PY_MAJOR_VERSION < 3
  return;
  #else
  return __pyx_m;
  #endif
}

/* Runtime support code */
#if CYTHON_REFNANNY
static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname) {
    PyObject *m = NULL, *p = NULL;
    void *r = NULL;
    m = PyImport_ImportModule((char *)modname);
    if (!m) goto end;
    p = PyObject_GetAttrString(m, (char *)"RefNannyAPI");
    if (!p) goto end;
    r = PyLong_AsVoidPtr(p);
end:
    Py_XDECREF(p);
    Py_XDECREF(m);
    return (__Pyx_RefNannyAPIStruct *)r;
}
#endif /* CYTHON_REFNANNY */

static PyObject *__Pyx_GetBuiltinName(PyObject *name) {
    PyObject* result = __Pyx_PyObject_GetAttrStr(__pyx_b, name);
    if (unlikely(!result)) {
        PyErr_Format(PyExc_NameError,
#if PY_MAJOR_VERSION >= 3
            "name '%U' is not defined", name);
#else
            "name '%s' is not defined", PyString_AS_STRING(name));
#endif
    }
    return result;
}

static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j) {
    PyObject *r;
    if (!j) return NULL;
    r = PyObject_GetItem(o, j);
    Py_DECREF(j);
    return r;
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (wraparound & unlikely(i < 0)) i += PyList_GET_SIZE(o);
    if ((!boundscheck) || likely((0 <= i) & (i < PyList_GET_SIZE(o)))) {
        PyObject *r = PyList_GET_ITEM(o, i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (wraparound & unlikely(i < 0)) i += PyTuple_GET_SIZE(o);
    if ((!boundscheck) || likely((0 <= i) & (i < PyTuple_GET_SIZE(o)))) {
        PyObject *r = PyTuple_GET_ITEM(o, i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                                     int is_list, int wraparound, int boundscheck) {
#if CYTHON_COMPILING_IN_CPYTHON
    if (is_list || PyList_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyList_GET_SIZE(o);
        if ((!boundscheck) || (likely((n >= 0) & (n < PyList_GET_SIZE(o))))) {
            PyObject *r = PyList_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    }
    else if (PyTuple_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyTuple_GET_SIZE(o);
        if ((!boundscheck) || likely((n >= 0) & (n < PyTuple_GET_SIZE(o)))) {
            PyObject *r = PyTuple_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    } else {
        PySequenceMethods *m = Py_TYPE(o)->tp_as_sequence;
        if (likely(m && m->sq_item)) {
            if (wraparound && unlikely(i < 0) && likely(m->sq_length)) {
                Py_ssize_t l = m->sq_length(o);
                if (likely(l >= 0)) {
                    i += l;
                } else {
                    if (PyErr_ExceptionMatches(PyExc_OverflowError))
                        PyErr_Clear();
                    else
                        return NULL;
                }
            }
            return m->sq_item(o, i);
        }
    }
#else
    if (is_list || PySequence_Check(o)) {
        return PySequence_GetItem(o, i);
    }
#endif
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
}

static CYTHON_INLINE void __Pyx_RaiseTooManyValuesError(Py_ssize_t expected) {
    PyErr_Format(PyExc_ValueError,
                 "too many values to unpack (expected %" CYTHON_FORMAT_SSIZE_T "d)", expected);
}

static CYTHON_INLINE void __Pyx_RaiseNeedMoreValuesError(Py_ssize_t index) {
    PyErr_Format(PyExc_ValueError,
                 "need more than %" CYTHON_FORMAT_SSIZE_T "d value%s to unpack",
                 index, (index == 1) ? "" : "s");
}

static CYTHON_INLINE int __Pyx_IterFinish(void) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyThreadState *tstate = PyThreadState_GET();
    PyObject* exc_type = tstate->curexc_type;
    if (unlikely(exc_type)) {
        if (likely(exc_type == PyExc_StopIteration) || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration)) {
            PyObject *exc_value, *exc_tb;
            exc_value = tstate->curexc_value;
            exc_tb = tstate->curexc_traceback;
            tstate->curexc_type = 0;
            tstate->curexc_value = 0;
            tstate->curexc_traceback = 0;
            Py_DECREF(exc_type);
            Py_XDECREF(exc_value);
            Py_XDECREF(exc_tb);
            return 0;
        } else {
            return -1;
        }
    }
    return 0;
#else
    if (unlikely(PyErr_Occurred())) {
        if (likely(PyErr_ExceptionMatches(PyExc_StopIteration))) {
            PyErr_Clear();
            return 0;
        } else {
            return -1;
        }
    }
    return 0;
#endif
}

static int __Pyx_IternextUnpackEndCheck(PyObject *retval, Py_ssize_t expected) {
    if (unlikely(retval)) {
        Py_DECREF(retval);
        __Pyx_RaiseTooManyValuesError(expected);
        return -1;
    } else {
        return __Pyx_IterFinish();
    }
    return 0;
}

static CYTHON_INLINE void __Pyx_RaiseNoneNotIterableError(void) {
    PyErr_SetString(PyExc_TypeError, "'NoneType' object is not iterable");
}

static void __Pyx_UnpackTupleError(PyObject *t, Py_ssize_t index) {
    if (t == Py_None) {
      __Pyx_RaiseNoneNotIterableError();
    } else if (PyTuple_GET_SIZE(t) < index) {
      __Pyx_RaiseNeedMoreValuesError(PyTuple_GET_SIZE(t));
    } else {
      __Pyx_RaiseTooManyValuesError(index);
    }
}

static CYTHON_INLINE int __Pyx_unpack_tuple2(PyObject* tuple, PyObject** pvalue1, PyObject** pvalue2,
                                             int is_tuple, int has_known_size, int decref_tuple) {
    Py_ssize_t index;
    PyObject *value1 = NULL, *value2 = NULL, *iter = NULL;
    if (!is_tuple && unlikely(!PyTuple_Check(tuple))) {
        iternextfunc iternext;
        iter = PyObject_GetIter(tuple);
        if (unlikely(!iter)) goto bad;
        if (decref_tuple) { Py_DECREF(tuple); tuple = NULL; }
        iternext = Py_TYPE(iter)->tp_iternext;
        value1 = iternext(iter); if (unlikely(!value1)) { index = 0; goto unpacking_failed; }
        value2 = iternext(iter); if (unlikely(!value2)) { index = 1; goto unpacking_failed; }
        if (!has_known_size && unlikely(__Pyx_IternextUnpackEndCheck(iternext(iter), 2))) goto bad;
        Py_DECREF(iter);
    } else {
        if (!has_known_size && unlikely(PyTuple_GET_SIZE(tuple) != 2)) {
            __Pyx_UnpackTupleError(tuple, 2);
            goto bad;
        }
#if CYTHON_COMPILING_IN_PYPY
        value1 = PySequence_ITEM(tuple, 0);
        if (unlikely(!value1)) goto bad;
        value2 = PySequence_ITEM(tuple, 1);
        if (unlikely(!value2)) goto bad;
#else
        value1 = PyTuple_GET_ITEM(tuple, 0);
        value2 = PyTuple_GET_ITEM(tuple, 1);
        Py_INCREF(value1);
        Py_INCREF(value2);
#endif
        if (decref_tuple) { Py_DECREF(tuple); }
    }
    *pvalue1 = value1;
    *pvalue2 = value2;
    return 0;
unpacking_failed:
    if (!has_known_size && __Pyx_IterFinish() == 0)
        __Pyx_RaiseNeedMoreValuesError(index);
bad:
    Py_XDECREF(iter);
    Py_XDECREF(value1);
    Py_XDECREF(value2);
    if (decref_tuple) { Py_XDECREF(tuple); }
    return -1;
}

static CYTHON_INLINE PyObject* __Pyx_dict_iterator(PyObject* iterable, int is_dict, PyObject* method_name,
                                                   Py_ssize_t* p_orig_length, int* p_source_is_dict) {
    is_dict = is_dict || likely(PyDict_CheckExact(iterable));
    *p_source_is_dict = is_dict;
#if !CYTHON_COMPILING_IN_PYPY
    if (is_dict) {
        *p_orig_length = PyDict_Size(iterable);
        Py_INCREF(iterable);
        return iterable;
    }
#endif
    *p_orig_length = 0;
    if (method_name) {
        PyObject* iter;
        iterable = __Pyx_PyObject_CallMethod0(iterable, method_name);
        if (!iterable)
            return NULL;
#if !CYTHON_COMPILING_IN_PYPY
        if (PyTuple_CheckExact(iterable) || PyList_CheckExact(iterable))
            return iterable;
#endif
        iter = PyObject_GetIter(iterable);
        Py_DECREF(iterable);
        return iter;
    }
    return PyObject_GetIter(iterable);
}
static CYTHON_INLINE int __Pyx_dict_iter_next(PyObject* iter_obj, Py_ssize_t orig_length, Py_ssize_t* ppos,
                                              PyObject** pkey, PyObject** pvalue, PyObject** pitem, int source_is_dict) {
    PyObject* next_item;
#if !CYTHON_COMPILING_IN_PYPY
    if (source_is_dict) {
        PyObject *key, *value;
        if (unlikely(orig_length != PyDict_Size(iter_obj))) {
            PyErr_SetString(PyExc_RuntimeError, "dictionary changed size during iteration");
            return -1;
        }
        if (unlikely(!PyDict_Next(iter_obj, ppos, &key, &value))) {
            return 0;
        }
        if (pitem) {
            PyObject* tuple = PyTuple_New(2);
            if (unlikely(!tuple)) {
                return -1;
            }
            Py_INCREF(key);
            Py_INCREF(value);
            PyTuple_SET_ITEM(tuple, 0, key);
            PyTuple_SET_ITEM(tuple, 1, value);
            *pitem = tuple;
        } else {
            if (pkey) {
                Py_INCREF(key);
                *pkey = key;
            }
            if (pvalue) {
                Py_INCREF(value);
                *pvalue = value;
            }
        }
        return 1;
    } else if (PyTuple_CheckExact(iter_obj)) {
        Py_ssize_t pos = *ppos;
        if (unlikely(pos >= PyTuple_GET_SIZE(iter_obj))) return 0;
        *ppos = pos + 1;
        next_item = PyTuple_GET_ITEM(iter_obj, pos);
        Py_INCREF(next_item);
    } else if (PyList_CheckExact(iter_obj)) {
        Py_ssize_t pos = *ppos;
        if (unlikely(pos >= PyList_GET_SIZE(iter_obj))) return 0;
        *ppos = pos + 1;
        next_item = PyList_GET_ITEM(iter_obj, pos);
        Py_INCREF(next_item);
    } else
#endif
    {
        next_item = PyIter_Next(iter_obj);
        if (unlikely(!next_item)) {
            return __Pyx_IterFinish();
        }
    }
    if (pitem) {
        *pitem = next_item;
    } else if (pkey && pvalue) {
        if (__Pyx_unpack_tuple2(next_item, pkey, pvalue, source_is_dict, source_is_dict, 1))
            return -1;
    } else if (pkey) {
        *pkey = next_item;
    } else {
        *pvalue = next_item;
    }
    return 1;
}

static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name) {
    PyObject *result;
#if CYTHON_COMPILING_IN_CPYTHON
    result = PyDict_GetItem(__pyx_d, name);
    if (result) {
        Py_INCREF(result);
    } else {
#else
    result = PyObject_GetItem(__pyx_d, name);
    if (!result) {
        PyErr_Clear();
#endif
        result = __Pyx_GetBuiltinName(name);
    }
    return result;
}

static CYTHON_INLINE int __Pyx_TypeTest(PyObject *obj, PyTypeObject *type) {
    if (unlikely(!type)) {
        PyErr_Format(PyExc_SystemError, "Missing type object");
        return 0;
    }
    if (likely(PyObject_TypeCheck(obj, type)))
        return 1;
    PyErr_Format(PyExc_TypeError, "Cannot convert %.200s to %.200s",
                 Py_TYPE(obj)->tp_name, type->tp_name);
    return 0;
}

static void __Pyx_RaiseDoubleKeywordsError(
    const char* func_name,
    PyObject* kw_name)
{
    PyErr_Format(PyExc_TypeError,
        #if PY_MAJOR_VERSION >= 3
        "%s() got multiple values for keyword argument '%U'", func_name, kw_name);
        #else
        "%s() got multiple values for keyword argument '%s'", func_name,
        PyString_AsString(kw_name));
        #endif
}

static int __Pyx_ParseOptionalKeywords(
    PyObject *kwds,
    PyObject **argnames[],
    PyObject *kwds2,
    PyObject *values[],
    Py_ssize_t num_pos_args,
    const char* function_name)
{
    PyObject *key = 0, *value = 0;
    Py_ssize_t pos = 0;
    PyObject*** name;
    PyObject*** first_kw_arg = argnames + num_pos_args;
    while (PyDict_Next(kwds, &pos, &key, &value)) {
        name = first_kw_arg;
        while (*name && (**name != key)) name++;
        if (*name) {
            values[name-argnames] = value;
            continue;
        }
        name = first_kw_arg;
        #if PY_MAJOR_VERSION < 3
        if (likely(PyString_CheckExact(key)) || likely(PyString_Check(key))) {
            while (*name) {
                if ((CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**name) == PyString_GET_SIZE(key))
                        && _PyString_Eq(**name, key)) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    if ((**argname == key) || (
                            (CYTHON_COMPILING_IN_PYPY || PyString_GET_SIZE(**argname) == PyString_GET_SIZE(key))
                             && _PyString_Eq(**argname, key))) {
                        goto arg_passed_twice;
                    }
                    argname++;
                }
            }
        } else
        #endif
        if (likely(PyUnicode_Check(key))) {
            while (*name) {
                int cmp = (**name == key) ? 0 :
                #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                    (PyUnicode_GET_SIZE(**name) != PyUnicode_GET_SIZE(key)) ? 1 :
                #endif
                    PyUnicode_Compare(**name, key);
                if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                if (cmp == 0) {
                    values[name-argnames] = value;
                    break;
                }
                name++;
            }
            if (*name) continue;
            else {
                PyObject*** argname = argnames;
                while (argname != first_kw_arg) {
                    int cmp = (**argname == key) ? 0 :
                    #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION >= 3
                        (PyUnicode_GET_SIZE(**argname) != PyUnicode_GET_SIZE(key)) ? 1 :
                    #endif
                        PyUnicode_Compare(**argname, key);
                    if (cmp < 0 && unlikely(PyErr_Occurred())) goto bad;
                    if (cmp == 0) goto arg_passed_twice;
                    argname++;
                }
            }
        } else
            goto invalid_keyword_type;
        if (kwds2) {
            if (unlikely(PyDict_SetItem(kwds2, key, value))) goto bad;
        } else {
            goto invalid_keyword;
        }
    }
    return 0;
arg_passed_twice:
    __Pyx_RaiseDoubleKeywordsError(function_name, key);
    goto bad;
invalid_keyword_type:
    PyErr_Format(PyExc_TypeError,
        "%s() keywords must be strings", function_name);
    goto bad;
invalid_keyword:
    PyErr_Format(PyExc_TypeError,
    #if PY_MAJOR_VERSION < 3
        "%s() got an unexpected keyword argument '%s'",
        function_name, PyString_AsString(key));
    #else
        "%s() got an unexpected keyword argument '%U'",
        function_name, key);
    #endif
bad:
    return -1;
}

static void __Pyx_RaiseArgtupleInvalid(
    const char* func_name,
    int exact,
    Py_ssize_t num_min,
    Py_ssize_t num_max,
    Py_ssize_t num_found)
{
    Py_ssize_t num_expected;
    const char *more_or_less;
    if (num_found < num_min) {
        num_expected = num_min;
        more_or_less = "at least";
    } else {
        num_expected = num_max;
        more_or_less = "at most";
    }
    if (exact) {
        more_or_less = "exactly";
    }
    PyErr_Format(PyExc_TypeError,
                 "%s() takes %s %" CYTHON_FORMAT_SSIZE_T "d positional argument%s (%" CYTHON_FORMAT_SSIZE_T "d given)",
                 func_name, more_or_less, num_expected,
                 (num_expected == 1) ? "" : "s", num_found);
}

static int __Pyx_ArgTypeTest(PyObject *obj, PyTypeObject *type, int none_allowed,
    const char *name, int exact)
{
    if (!type) {
        PyErr_Format(PyExc_SystemError, "Missing type object");
        return 0;
    }
    if (none_allowed && obj == Py_None) return 1;
    else if (exact) {
        if (Py_TYPE(obj) == type) return 1;
    }
    else {
        if (PyObject_TypeCheck(obj, type)) return 1;
    }
    PyErr_Format(PyExc_TypeError,
        "Argument '%s' has incorrect type (expected %s, got %s)",
        name, type->tp_name, Py_TYPE(obj)->tp_name);
    return 0;
}

static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb) {
    PyObject *local_type, *local_value, *local_tb;
#if CYTHON_COMPILING_IN_CPYTHON
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    PyThreadState *tstate = PyThreadState_GET();
    local_type = tstate->curexc_type;
    local_value = tstate->curexc_value;
    local_tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
#else
    PyErr_Fetch(&local_type, &local_value, &local_tb);
#endif
    PyErr_NormalizeException(&local_type, &local_value, &local_tb);
#if CYTHON_COMPILING_IN_CPYTHON
    if (unlikely(tstate->curexc_type))
#else
    if (unlikely(PyErr_Occurred()))
#endif
        goto bad;
    #if PY_MAJOR_VERSION >= 3
    if (unlikely(PyException_SetTraceback(local_value, local_tb) < 0))
        goto bad;
    #endif
    Py_INCREF(local_type);
    Py_INCREF(local_value);
    Py_INCREF(local_tb);
    *type = local_type;
    *value = local_value;
    *tb = local_tb;
#if CYTHON_COMPILING_IN_CPYTHON
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = local_type;
    tstate->exc_value = local_value;
    tstate->exc_traceback = local_tb;
    /* Make sure tstate is in a consistent state when we XDECREF
       these objects (DECREF may run arbitrary code). */
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
#else
    PyErr_SetExcInfo(local_type, local_value, local_tb);
#endif
    return 0;
bad:
    *type = 0;
    *value = 0;
    *tb = 0;
    Py_XDECREF(local_type);
    Py_XDECREF(local_value);
    Py_XDECREF(local_tb);
    return -1;
}

static CYTHON_INLINE void __Pyx_ErrRestore(PyObject *type, PyObject *value, PyObject *tb) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    PyThreadState *tstate = PyThreadState_GET();
    tmp_type = tstate->curexc_type;
    tmp_value = tstate->curexc_value;
    tmp_tb = tstate->curexc_traceback;
    tstate->curexc_type = type;
    tstate->curexc_value = value;
    tstate->curexc_traceback = tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
#else
    PyErr_Restore(type, value, tb);
#endif
}
static CYTHON_INLINE void __Pyx_ErrFetch(PyObject **type, PyObject **value, PyObject **tb) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyThreadState *tstate = PyThreadState_GET();
    *type = tstate->curexc_type;
    *value = tstate->curexc_value;
    *tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
#else
    PyErr_Fetch(type, value, tb);
#endif
}

static double __Pyx__PyObject_AsDouble(PyObject* obj) {
    PyObject* float_value;
#if CYTHON_COMPILING_IN_PYPY
    float_value = PyNumber_Float(obj);
#else
    PyNumberMethods *nb = Py_TYPE(obj)->tp_as_number;
    if (likely(nb) && likely(nb->nb_float)) {
        float_value = nb->nb_float(obj);
        if (likely(float_value) && unlikely(!PyFloat_Check(float_value))) {
            PyErr_Format(PyExc_TypeError,
                "__float__ returned non-float (type %.200s)",
                Py_TYPE(float_value)->tp_name);
            Py_DECREF(float_value);
            goto bad;
        }
    } else if (PyUnicode_CheckExact(obj) || PyBytes_CheckExact(obj)) {
#if PY_MAJOR_VERSION >= 3
        float_value = PyFloat_FromString(obj);
#else
        float_value = PyFloat_FromString(obj, 0);
#endif
    } else {
        PyObject* args = PyTuple_New(1);
        if (unlikely(!args)) goto bad;
        PyTuple_SET_ITEM(args, 0, obj);
        float_value = PyObject_Call((PyObject*)&PyFloat_Type, args, 0);
        PyTuple_SET_ITEM(args, 0, 0);
        Py_DECREF(args);
    }
#endif
    if (likely(float_value)) {
        double value = PyFloat_AS_DOUBLE(float_value);
        Py_DECREF(float_value);
        return value;
    }
bad:
    return (double)-1;
}

static CYTHON_INLINE PyObject* __Pyx_PyObject_Append(PyObject* L, PyObject* x) {
    if (likely(PyList_CheckExact(L))) {
        if (unlikely(__Pyx_PyList_Append(L, x) < 0)) return NULL;
        Py_INCREF(Py_None);
        return Py_None; /* this is just to have an accurate signature */
    } else {
        return __Pyx_PyObject_CallMethod1(L, __pyx_n_s__append, x);
    }
}

static int __Pyx_SetVtable(PyObject *dict, void *vtable) {
#if PY_VERSION_HEX >= 0x02070000 && !(PY_MAJOR_VERSION==3&&PY_MINOR_VERSION==0)
    PyObject *ob = PyCapsule_New(vtable, 0, 0);
#else
    PyObject *ob = PyCObject_FromVoidPtr(vtable, 0);
#endif
    if (!ob)
        goto bad;
    if (PyDict_SetItem(dict, __pyx_n_s____pyx_vtable__, ob) < 0)
        goto bad;
    Py_DECREF(ob);
    return 0;
bad:
    Py_XDECREF(ob);
    return -1;
}

static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name) {
    PyObject* value = __Pyx_PyObject_GetAttrStr(module, name);
    if (unlikely(!value) && PyErr_ExceptionMatches(PyExc_AttributeError)) {
        PyErr_Format(PyExc_ImportError,
        #if PY_MAJOR_VERSION < 3
            "cannot import name %.230s", PyString_AS_STRING(name));
        #else
            "cannot import name %S", name);
        #endif
    }
    return value;
}

static CYTHON_INLINE void __Pyx_ExceptionSave(PyObject **type, PyObject **value, PyObject **tb) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyThreadState *tstate = PyThreadState_GET();
    *type = tstate->exc_type;
    *value = tstate->exc_value;
    *tb = tstate->exc_traceback;
    Py_XINCREF(*type);
    Py_XINCREF(*value);
    Py_XINCREF(*tb);
#else
    PyErr_GetExcInfo(type, value, tb);
#endif
}
static void __Pyx_ExceptionReset(PyObject *type, PyObject *value, PyObject *tb) {
#if CYTHON_COMPILING_IN_CPYTHON
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    PyThreadState *tstate = PyThreadState_GET();
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = type;
    tstate->exc_value = value;
    tstate->exc_traceback = tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
#else
    PyErr_SetExcInfo(type, value, tb);
#endif
}

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level) {
    PyObject *empty_list = 0;
    PyObject *module = 0;
    PyObject *global_dict = 0;
    PyObject *empty_dict = 0;
    PyObject *list;
    #if PY_VERSION_HEX < 0x03030000
    PyObject *py_import;
    py_import = __Pyx_PyObject_GetAttrStr(__pyx_b, __pyx_n_s____import__);
    if (!py_import)
        goto bad;
    #endif
    if (from_list)
        list = from_list;
    else {
        empty_list = PyList_New(0);
        if (!empty_list)
            goto bad;
        list = empty_list;
    }
    global_dict = PyModule_GetDict(__pyx_m);
    if (!global_dict)
        goto bad;
    empty_dict = PyDict_New();
    if (!empty_dict)
        goto bad;
    #if PY_VERSION_HEX >= 0x02050000
    {
        #if PY_MAJOR_VERSION >= 3
        if (level == -1) {
            if (strchr(__Pyx_MODULE_NAME, '.')) {
                #if PY_VERSION_HEX < 0x03030000
                PyObject *py_level = PyInt_FromLong(1);
                if (!py_level)
                    goto bad;
                module = PyObject_CallFunctionObjArgs(py_import,
                    name, global_dict, empty_dict, list, py_level, NULL);
                Py_DECREF(py_level);
                #else
                module = PyImport_ImportModuleLevelObject(
                    name, global_dict, empty_dict, list, 1);
                #endif
                if (!module) {
                    if (!PyErr_ExceptionMatches(PyExc_ImportError))
                        goto bad;
                    PyErr_Clear();
                }
            }
            level = 0; /* try absolute import on failure */
        }
        #endif
        if (!module) {
            #if PY_VERSION_HEX < 0x03030000
            PyObject *py_level = PyInt_FromLong(level);
            if (!py_level)
                goto bad;
            module = PyObject_CallFunctionObjArgs(py_import,
                name, global_dict, empty_dict, list, py_level, NULL);
            Py_DECREF(py_level);
            #else
            module = PyImport_ImportModuleLevelObject(
                name, global_dict, empty_dict, list, level);
            #endif
        }
    }
    #else
    if (level>0) {
        PyErr_SetString(PyExc_RuntimeError, "Relative import is not supported for Python <=2.4.");
        goto bad;
    }
    module = PyObject_CallFunctionObjArgs(py_import,
        name, global_dict, empty_dict, list, NULL);
    #endif
bad:
    #if PY_VERSION_HEX < 0x03030000
    Py_XDECREF(py_import);
    #endif
    Py_XDECREF(empty_list);
    Py_XDECREF(empty_dict);
    return module;
}

static CYTHON_INLINE GLuint __Pyx_PyInt_from_py_GLuint(PyObject* x) {
    const GLuint neg_one = (GLuint)-1, const_zero = (GLuint)0;
    const int is_unsigned = const_zero < neg_one;
    if (sizeof(GLuint) == sizeof(char)) {
        if (is_unsigned)
            return (GLuint)__Pyx_PyInt_AsUnsignedChar(x);
        else
            return (GLuint)__Pyx_PyInt_AsSignedChar(x);
    } else if (sizeof(GLuint) == sizeof(short)) {
        if (is_unsigned)
            return (GLuint)__Pyx_PyInt_AsUnsignedShort(x);
        else
            return (GLuint)__Pyx_PyInt_AsSignedShort(x);
    } else if (sizeof(GLuint) == sizeof(int)) {
        if (is_unsigned)
            return (GLuint)__Pyx_PyInt_AsUnsignedInt(x);
        else
            return (GLuint)__Pyx_PyInt_AsSignedInt(x);
    } else if (sizeof(GLuint) == sizeof(long)) {
        if (is_unsigned)
            return (GLuint)__Pyx_PyInt_AsUnsignedLong(x);
        else
            return (GLuint)__Pyx_PyInt_AsSignedLong(x);
    } else if (sizeof(GLuint) == sizeof(PY_LONG_LONG)) {
        if (is_unsigned)
            return (GLuint)__Pyx_PyInt_AsUnsignedLongLong(x);
        else
            return (GLuint)__Pyx_PyInt_AsSignedLongLong(x);
    }  else {
        #if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
        PyErr_SetString(PyExc_RuntimeError,
                        "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
        #else
        GLuint val;
        PyObject *v = __Pyx_PyNumber_Int(x);
        #if PY_MAJOR_VERSION < 3
        if (likely(v) && !PyLong_Check(v)) {
            PyObject *tmp = v;
            v = PyNumber_Long(tmp);
            Py_DECREF(tmp);
        }
        #endif
        if (likely(v)) {
            int one = 1; int is_little = (int)*(unsigned char *)&one;
            unsigned char *bytes = (unsigned char *)&val;
            int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                          bytes, sizeof(val),
                                          is_little, !is_unsigned);
            Py_DECREF(v);
            if (likely(!ret))
                return val;
        }
        #endif
        return (GLuint)-1;
    }
}

static CYTHON_INLINE PyObject *__Pyx_PyInt_to_py_GLuint(GLuint val) {
    const GLuint neg_one = (GLuint)-1, const_zero = (GLuint)0;
    const int is_unsigned = const_zero < neg_one;
    if ((sizeof(GLuint) == sizeof(char))  ||
        (sizeof(GLuint) == sizeof(short))) {
        return PyInt_FromLong((long)val);
    } else if ((sizeof(GLuint) == sizeof(int)) ||
               (sizeof(GLuint) == sizeof(long))) {
        if (is_unsigned)
            return PyLong_FromUnsignedLong((unsigned long)val);
        else
            return PyInt_FromLong((long)val);
    } else if (sizeof(GLuint) == sizeof(PY_LONG_LONG)) {
        if (is_unsigned)
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG)val);
        else
            return PyLong_FromLongLong((PY_LONG_LONG)val);
    } else {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&val;
        return _PyLong_FromByteArray(bytes, sizeof(GLuint),
                                     little, !is_unsigned);
    }
}

#if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION < 3
static PyObject *__Pyx_GetStdout(void) {
    PyObject *f = PySys_GetObject((char *)"stdout");
    if (!f) {
        PyErr_SetString(PyExc_RuntimeError, "lost sys.stdout");
    }
    return f;
}
static int __Pyx_Print(PyObject* f, PyObject *arg_tuple, int newline) {
    int i;
    if (!f) {
        if (!(f = __Pyx_GetStdout()))
            return -1;
    }
    Py_INCREF(f);
    for (i=0; i < PyTuple_GET_SIZE(arg_tuple); i++) {
        PyObject* v;
        if (PyFile_SoftSpace(f, 1)) {
            if (PyFile_WriteString(" ", f) < 0)
                goto error;
        }
        v = PyTuple_GET_ITEM(arg_tuple, i);
        if (PyFile_WriteObject(v, f, Py_PRINT_RAW) < 0)
            goto error;
        if (PyString_Check(v)) {
            char *s = PyString_AsString(v);
            Py_ssize_t len = PyString_Size(v);
            if (len > 0 &&
                isspace(Py_CHARMASK(s[len-1])) &&
                s[len-1] != ' ')
                    PyFile_SoftSpace(f, 0);
        }
    }
    if (newline) {
        if (PyFile_WriteString("\n", f) < 0)
            goto error;
        PyFile_SoftSpace(f, 0);
    }
    Py_DECREF(f);
    return 0;
error:
    Py_DECREF(f);
    return -1;
}
#else /* Python 3 has a print function */
static int __Pyx_Print(PyObject* stream, PyObject *arg_tuple, int newline) {
    PyObject* kwargs = 0;
    PyObject* result = 0;
    PyObject* end_string;
    if (unlikely(!__pyx_print)) {
        __pyx_print = PyObject_GetAttr(__pyx_b, __pyx_n_s__print);
        if (!__pyx_print)
            return -1;
    }
    if (stream) {
        kwargs = PyDict_New();
        if (unlikely(!kwargs))
            return -1;
        if (unlikely(PyDict_SetItem(kwargs, __pyx_n_s__file, stream) < 0))
            goto bad;
        if (!newline) {
            end_string = PyUnicode_FromStringAndSize(" ", 1);
            if (unlikely(!end_string))
                goto bad;
            if (PyDict_SetItem(kwargs, __pyx_n_s__end, end_string) < 0) {
                Py_DECREF(end_string);
                goto bad;
            }
            Py_DECREF(end_string);
        }
    } else if (!newline) {
        if (unlikely(!__pyx_print_kwargs)) {
            __pyx_print_kwargs = PyDict_New();
            if (unlikely(!__pyx_print_kwargs))
                return -1;
            end_string = PyUnicode_FromStringAndSize(" ", 1);
            if (unlikely(!end_string))
                return -1;
            if (PyDict_SetItem(__pyx_print_kwargs, __pyx_n_s__end, end_string) < 0) {
                Py_DECREF(end_string);
                return -1;
            }
            Py_DECREF(end_string);
        }
        kwargs = __pyx_print_kwargs;
    }
    result = PyObject_Call(__pyx_print, arg_tuple, kwargs);
    if (unlikely(kwargs) && (kwargs != __pyx_print_kwargs))
        Py_DECREF(kwargs);
    if (!result)
        return -1;
    Py_DECREF(result);
    return 0;
bad:
    if (kwargs != __pyx_print_kwargs)
        Py_XDECREF(kwargs);
    return -1;
}
#endif

#if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION < 3
static int __Pyx_PrintOne(PyObject* f, PyObject *o) {
    if (!f) {
        if (!(f = __Pyx_GetStdout()))
            return -1;
    }
    Py_INCREF(f);
    if (PyFile_SoftSpace(f, 0)) {
        if (PyFile_WriteString(" ", f) < 0)
            goto error;
    }
    if (PyFile_WriteObject(o, f, Py_PRINT_RAW) < 0)
        goto error;
    if (PyFile_WriteString("\n", f) < 0)
        goto error;
    Py_DECREF(f);
    return 0;
error:
    Py_DECREF(f);
    return -1;
    /* the line below is just to avoid C compiler
     * warnings about unused functions */
    return __Pyx_Print(f, NULL, 0);
}
#else /* Python 3 has a print function */
static int __Pyx_PrintOne(PyObject* stream, PyObject *o) {
    int res;
    PyObject* arg_tuple = PyTuple_Pack(1, o);
    if (unlikely(!arg_tuple))
        return -1;
    res = __Pyx_Print(stream, arg_tuple, 1);
    Py_DECREF(arg_tuple);
    return res;
}
#endif

static CYTHON_INLINE unsigned char __Pyx_PyInt_AsUnsignedChar(PyObject* x) {
    const unsigned char neg_one = (unsigned char)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(unsigned char) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(unsigned char)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to unsigned char" :
                    "value too large to convert to unsigned char");
            }
            return (unsigned char)-1;
        }
        return (unsigned char)val;
    }
    return (unsigned char)__Pyx_PyInt_AsUnsignedLong(x);
}

static CYTHON_INLINE unsigned short __Pyx_PyInt_AsUnsignedShort(PyObject* x) {
    const unsigned short neg_one = (unsigned short)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(unsigned short) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(unsigned short)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to unsigned short" :
                    "value too large to convert to unsigned short");
            }
            return (unsigned short)-1;
        }
        return (unsigned short)val;
    }
    return (unsigned short)__Pyx_PyInt_AsUnsignedLong(x);
}

static CYTHON_INLINE unsigned int __Pyx_PyInt_AsUnsignedInt(PyObject* x) {
    const unsigned int neg_one = (unsigned int)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(unsigned int) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(unsigned int)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to unsigned int" :
                    "value too large to convert to unsigned int");
            }
            return (unsigned int)-1;
        }
        return (unsigned int)val;
    }
    return (unsigned int)__Pyx_PyInt_AsUnsignedLong(x);
}

static CYTHON_INLINE char __Pyx_PyInt_AsChar(PyObject* x) {
    const char neg_one = (char)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(char) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(char)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to char" :
                    "value too large to convert to char");
            }
            return (char)-1;
        }
        return (char)val;
    }
    return (char)__Pyx_PyInt_AsLong(x);
}

static CYTHON_INLINE short __Pyx_PyInt_AsShort(PyObject* x) {
    const short neg_one = (short)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(short) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(short)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to short" :
                    "value too large to convert to short");
            }
            return (short)-1;
        }
        return (short)val;
    }
    return (short)__Pyx_PyInt_AsLong(x);
}

static CYTHON_INLINE int __Pyx_PyInt_AsInt(PyObject* x) {
    const int neg_one = (int)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(int) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(int)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to int" :
                    "value too large to convert to int");
            }
            return (int)-1;
        }
        return (int)val;
    }
    return (int)__Pyx_PyInt_AsLong(x);
}

static CYTHON_INLINE signed char __Pyx_PyInt_AsSignedChar(PyObject* x) {
    const signed char neg_one = (signed char)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(signed char) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(signed char)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to signed char" :
                    "value too large to convert to signed char");
            }
            return (signed char)-1;
        }
        return (signed char)val;
    }
    return (signed char)__Pyx_PyInt_AsSignedLong(x);
}

static CYTHON_INLINE signed short __Pyx_PyInt_AsSignedShort(PyObject* x) {
    const signed short neg_one = (signed short)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(signed short) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(signed short)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to signed short" :
                    "value too large to convert to signed short");
            }
            return (signed short)-1;
        }
        return (signed short)val;
    }
    return (signed short)__Pyx_PyInt_AsSignedLong(x);
}

static CYTHON_INLINE signed int __Pyx_PyInt_AsSignedInt(PyObject* x) {
    const signed int neg_one = (signed int)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(signed int) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(signed int)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to signed int" :
                    "value too large to convert to signed int");
            }
            return (signed int)-1;
        }
        return (signed int)val;
    }
    return (signed int)__Pyx_PyInt_AsSignedLong(x);
}

static CYTHON_INLINE int __Pyx_PyInt_AsLongDouble(PyObject* x) {
    const int neg_one = (int)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (sizeof(int) < sizeof(long)) {
        long val = __Pyx_PyInt_AsLong(x);
        if (unlikely(val != (long)(int)val)) {
            if (!unlikely(val == -1 && PyErr_Occurred())) {
                PyErr_SetString(PyExc_OverflowError,
                    (is_unsigned && unlikely(val < 0)) ?
                    "can't convert negative value to int" :
                    "value too large to convert to int");
            }
            return (int)-1;
        }
        return (int)val;
    }
    return (int)__Pyx_PyInt_AsLong(x);
}

#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
#include "longintrepr.h"
#endif
#endif
static CYTHON_INLINE unsigned long __Pyx_PyInt_AsUnsignedLong(PyObject* x) {
    const unsigned long neg_one = (unsigned long)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        long val = PyInt_AS_LONG(x);
        if (is_unsigned && unlikely(val < 0)) {
            PyErr_SetString(PyExc_OverflowError,
                            "can't convert negative value to unsigned long");
            return (unsigned long)-1;
        }
        return (unsigned long)val;
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(unsigned long)) {
                switch (Py_SIZE(x)) {
                    case  0: return 0;
                    case  1: return (unsigned long) ((PyLongObject*)x)->ob_digit[0];
                }
            }
#endif
#endif
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to unsigned long");
                return (unsigned long)-1;
            }
            return (unsigned long)PyLong_AsUnsignedLong(x);
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(unsigned long)) {
                switch (Py_SIZE(x)) {
                    case  0: return 0;
                    case  1: return +(unsigned long) ((PyLongObject*)x)->ob_digit[0];
                    case -1: return -(unsigned long) ((PyLongObject*)x)->ob_digit[0];
                }
            }
#endif
#endif
            return (unsigned long)PyLong_AsLong(x);
        }
    } else {
        unsigned long val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (unsigned long)-1;
        val = __Pyx_PyInt_AsUnsignedLong(tmp);
        Py_DECREF(tmp);
        return val;
    }
}

#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
#include "longintrepr.h"
#endif
#endif
static CYTHON_INLINE unsigned PY_LONG_LONG __Pyx_PyInt_AsUnsignedLongLong(PyObject* x) {
    const unsigned PY_LONG_LONG neg_one = (unsigned PY_LONG_LONG)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        long val = PyInt_AS_LONG(x);
        if (is_unsigned && unlikely(val < 0)) {
            PyErr_SetString(PyExc_OverflowError,
                            "can't convert negative value to unsigned PY_LONG_LONG");
            return (unsigned PY_LONG_LONG)-1;
        }
        return (unsigned PY_LONG_LONG)val;
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(unsigned PY_LONG_LONG)) {
                switch (Py_SIZE(x)) {
                    case  0: return 0;
                    case  1: return (unsigned PY_LONG_LONG) ((PyLongObject*)x)->ob_digit[0];
                }
            }
#endif
#endif
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to unsigned PY_LONG_LONG");
                return (unsigned PY_LONG_LONG)-1;
            }
            return (unsigned PY_LONG_LONG)PyLong_AsUnsignedLongLong(x);
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(unsigned PY_LONG_LONG)) {
                switch (Py_SIZE(x)) {
                    case  0: return 0;
                    case  1: return +(unsigned PY_LONG_LONG) ((PyLongObject*)x)->ob_digit[0];
                    case -1: return -(unsigned PY_LONG_LONG) ((PyLongObject*)x)->ob_digit[0];
                }
            }
#endif
#endif
            return (unsigned PY_LONG_LONG)PyLong_AsLongLong(x);
        }
    } else {
        unsigned PY_LONG_LONG val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (unsigned PY_LONG_LONG)-1;
        val = __Pyx_PyInt_AsUnsignedLongLong(tmp);
        Py_DECREF(tmp);
        return val;
    }
}

#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
#include "longintrepr.h"
#endif
#endif
static CYTHON_INLINE long __Pyx_PyInt_AsLong(PyObject* x) {
    const long neg_one = (long)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        long val = PyInt_AS_LONG(x);
        if (is_unsigned && unlikely(val < 0)) {
            PyErr_SetString(PyExc_OverflowError,
                            "can't convert negative value to long");
            return (long)-1;
        }
        return (long)val;
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(long)) {
                switch (Py_SIZE(x)) {
                    case  0: return 0;
                    case  1: return (long) ((PyLongObject*)x)->ob_digit[0];
                }
            }
#endif
#endif
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to long");
                return (long)-1;
            }
            return (long)PyLong_AsUnsignedLong(x);
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(long)) {
                switch (Py_SIZE(x)) {
                    case  0: return 0;
                    case  1: return +(long) ((PyLongObject*)x)->ob_digit[0];
                    case -1: return -(long) ((PyLongObject*)x)->ob_digit[0];
                }
            }
#endif
#endif
            return (long)PyLong_AsLong(x);
        }
    } else {
        long val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (long)-1;
        val = __Pyx_PyInt_AsLong(tmp);
        Py_DECREF(tmp);
        return val;
    }
}

#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
#include "longintrepr.h"
#endif
#endif
static CYTHON_INLINE PY_LONG_LONG __Pyx_PyInt_AsLongLong(PyObject* x) {
    const PY_LONG_LONG neg_one = (PY_LONG_LONG)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        long val = PyInt_AS_LONG(x);
        if (is_unsigned && unlikely(val < 0)) {
            PyErr_SetString(PyExc_OverflowError,
                            "can't convert negative value to PY_LONG_LONG");
            return (PY_LONG_LONG)-1;
        }
        return (PY_LONG_LONG)val;
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(PY_LONG_LONG)) {
                switch (Py_SIZE(x)) {
                    case  0: return 0;
                    case  1: return (PY_LONG_LONG) ((PyLongObject*)x)->ob_digit[0];
                }
            }
#endif
#endif
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to PY_LONG_LONG");
                return (PY_LONG_LONG)-1;
            }
            return (PY_LONG_LONG)PyLong_AsUnsignedLongLong(x);
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(PY_LONG_LONG)) {
                switch (Py_SIZE(x)) {
                    case  0: return 0;
                    case  1: return +(PY_LONG_LONG) ((PyLongObject*)x)->ob_digit[0];
                    case -1: return -(PY_LONG_LONG) ((PyLongObject*)x)->ob_digit[0];
                }
            }
#endif
#endif
            return (PY_LONG_LONG)PyLong_AsLongLong(x);
        }
    } else {
        PY_LONG_LONG val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (PY_LONG_LONG)-1;
        val = __Pyx_PyInt_AsLongLong(tmp);
        Py_DECREF(tmp);
        return val;
    }
}

#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
#include "longintrepr.h"
#endif
#endif
static CYTHON_INLINE signed long __Pyx_PyInt_AsSignedLong(PyObject* x) {
    const signed long neg_one = (signed long)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        long val = PyInt_AS_LONG(x);
        if (is_unsigned && unlikely(val < 0)) {
            PyErr_SetString(PyExc_OverflowError,
                            "can't convert negative value to signed long");
            return (signed long)-1;
        }
        return (signed long)val;
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(signed long)) {
                switch (Py_SIZE(x)) {
                    case  0: return 0;
                    case  1: return (signed long) ((PyLongObject*)x)->ob_digit[0];
                }
            }
#endif
#endif
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to signed long");
                return (signed long)-1;
            }
            return (signed long)PyLong_AsUnsignedLong(x);
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(signed long)) {
                switch (Py_SIZE(x)) {
                    case  0: return 0;
                    case  1: return +(signed long) ((PyLongObject*)x)->ob_digit[0];
                    case -1: return -(signed long) ((PyLongObject*)x)->ob_digit[0];
                }
            }
#endif
#endif
            return (signed long)PyLong_AsLong(x);
        }
    } else {
        signed long val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (signed long)-1;
        val = __Pyx_PyInt_AsSignedLong(tmp);
        Py_DECREF(tmp);
        return val;
    }
}

#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
#include "longintrepr.h"
#endif
#endif
static CYTHON_INLINE signed PY_LONG_LONG __Pyx_PyInt_AsSignedLongLong(PyObject* x) {
    const signed PY_LONG_LONG neg_one = (signed PY_LONG_LONG)-1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        long val = PyInt_AS_LONG(x);
        if (is_unsigned && unlikely(val < 0)) {
            PyErr_SetString(PyExc_OverflowError,
                            "can't convert negative value to signed PY_LONG_LONG");
            return (signed PY_LONG_LONG)-1;
        }
        return (signed PY_LONG_LONG)val;
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(signed PY_LONG_LONG)) {
                switch (Py_SIZE(x)) {
                    case  0: return 0;
                    case  1: return (signed PY_LONG_LONG) ((PyLongObject*)x)->ob_digit[0];
                }
            }
#endif
#endif
            if (unlikely(Py_SIZE(x) < 0)) {
                PyErr_SetString(PyExc_OverflowError,
                                "can't convert negative value to signed PY_LONG_LONG");
                return (signed PY_LONG_LONG)-1;
            }
            return (signed PY_LONG_LONG)PyLong_AsUnsignedLongLong(x);
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
#if CYTHON_USE_PYLONG_INTERNALS
            if (sizeof(digit) <= sizeof(signed PY_LONG_LONG)) {
                switch (Py_SIZE(x)) {
                    case  0: return 0;
                    case  1: return +(signed PY_LONG_LONG) ((PyLongObject*)x)->ob_digit[0];
                    case -1: return -(signed PY_LONG_LONG) ((PyLongObject*)x)->ob_digit[0];
                }
            }
#endif
#endif
            return (signed PY_LONG_LONG)PyLong_AsLongLong(x);
        }
    } else {
        signed PY_LONG_LONG val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (signed PY_LONG_LONG)-1;
        val = __Pyx_PyInt_AsSignedLongLong(tmp);
        Py_DECREF(tmp);
        return val;
    }
}

static int __Pyx_check_binary_version(void) {
    char ctversion[4], rtversion[4];
    PyOS_snprintf(ctversion, 4, "%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
    PyOS_snprintf(rtversion, 4, "%s", Py_GetVersion());
    if (ctversion[0] != rtversion[0] || ctversion[2] != rtversion[2]) {
        char message[200];
        PyOS_snprintf(message, sizeof(message),
                      "compiletime version %s of module '%.100s' "
                      "does not match runtime version %s",
                      ctversion, __Pyx_MODULE_NAME, rtversion);
        #if PY_VERSION_HEX < 0x02050000
        return PyErr_Warn(NULL, message);
        #else
        return PyErr_WarnEx(NULL, message, 1);
        #endif
    }
    return 0;
}

static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line) {
    int start = 0, mid = 0, end = count - 1;
    if (end >= 0 && code_line > entries[end].code_line) {
        return count;
    }
    while (start < end) {
        mid = (start + end) / 2;
        if (code_line < entries[mid].code_line) {
            end = mid;
        } else if (code_line > entries[mid].code_line) {
             start = mid + 1;
        } else {
            return mid;
        }
    }
    if (code_line <= entries[mid].code_line) {
        return mid;
    } else {
        return mid + 1;
    }
}
static PyCodeObject *__pyx_find_code_object(int code_line) {
    PyCodeObject* code_object;
    int pos;
    if (unlikely(!code_line) || unlikely(!__pyx_code_cache.entries)) {
        return NULL;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if (unlikely(pos >= __pyx_code_cache.count) || unlikely(__pyx_code_cache.entries[pos].code_line != code_line)) {
        return NULL;
    }
    code_object = __pyx_code_cache.entries[pos].code_object;
    Py_INCREF(code_object);
    return code_object;
}
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object) {
    int pos, i;
    __Pyx_CodeObjectCacheEntry* entries = __pyx_code_cache.entries;
    if (unlikely(!code_line)) {
        return;
    }
    if (unlikely(!entries)) {
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Malloc(64*sizeof(__Pyx_CodeObjectCacheEntry));
        if (likely(entries)) {
            __pyx_code_cache.entries = entries;
            __pyx_code_cache.max_count = 64;
            __pyx_code_cache.count = 1;
            entries[0].code_line = code_line;
            entries[0].code_object = code_object;
            Py_INCREF(code_object);
        }
        return;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if ((pos < __pyx_code_cache.count) && unlikely(__pyx_code_cache.entries[pos].code_line == code_line)) {
        PyCodeObject* tmp = entries[pos].code_object;
        entries[pos].code_object = code_object;
        Py_DECREF(tmp);
        return;
    }
    if (__pyx_code_cache.count == __pyx_code_cache.max_count) {
        int new_max = __pyx_code_cache.max_count + 64;
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Realloc(
            __pyx_code_cache.entries, new_max*sizeof(__Pyx_CodeObjectCacheEntry));
        if (unlikely(!entries)) {
            return;
        }
        __pyx_code_cache.entries = entries;
        __pyx_code_cache.max_count = new_max;
    }
    for (i=__pyx_code_cache.count; i>pos; i--) {
        entries[i] = entries[i-1];
    }
    entries[pos].code_line = code_line;
    entries[pos].code_object = code_object;
    __pyx_code_cache.count++;
    Py_INCREF(code_object);
}

#include "compile.h"
#include "frameobject.h"
#include "traceback.h"
static PyCodeObject* __Pyx_CreateCodeObjectForTraceback(
            const char *funcname, int c_line,
            int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyObject *py_srcfile = 0;
    PyObject *py_funcname = 0;
    #if PY_MAJOR_VERSION < 3
    py_srcfile = PyString_FromString(filename);
    #else
    py_srcfile = PyUnicode_FromString(filename);
    #endif
    if (!py_srcfile) goto bad;
    if (c_line) {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #else
        py_funcname = PyUnicode_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #endif
    }
    else {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromString(funcname);
        #else
        py_funcname = PyUnicode_FromString(funcname);
        #endif
    }
    if (!py_funcname) goto bad;
    py_code = __Pyx_PyCode_New(
        0,            /*int argcount,*/
        0,            /*int kwonlyargcount,*/
        0,            /*int nlocals,*/
        0,            /*int stacksize,*/
        0,            /*int flags,*/
        __pyx_empty_bytes, /*PyObject *code,*/
        __pyx_empty_tuple, /*PyObject *consts,*/
        __pyx_empty_tuple, /*PyObject *names,*/
        __pyx_empty_tuple, /*PyObject *varnames,*/
        __pyx_empty_tuple, /*PyObject *freevars,*/
        __pyx_empty_tuple, /*PyObject *cellvars,*/
        py_srcfile,   /*PyObject *filename,*/
        py_funcname,  /*PyObject *name,*/
        py_line,      /*int firstlineno,*/
        __pyx_empty_bytes  /*PyObject *lnotab*/
    );
    Py_DECREF(py_srcfile);
    Py_DECREF(py_funcname);
    return py_code;
bad:
    Py_XDECREF(py_srcfile);
    Py_XDECREF(py_funcname);
    return NULL;
}
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyObject *py_globals = 0;
    PyFrameObject *py_frame = 0;
    py_code = __pyx_find_code_object(c_line ? c_line : py_line);
    if (!py_code) {
        py_code = __Pyx_CreateCodeObjectForTraceback(
            funcname, c_line, py_line, filename);
        if (!py_code) goto bad;
        __pyx_insert_code_object(c_line ? c_line : py_line, py_code);
    }
    py_globals = PyModule_GetDict(__pyx_m);
    if (!py_globals) goto bad;
    py_frame = PyFrame_New(
        PyThreadState_GET(), /*PyThreadState *tstate,*/
        py_code,             /*PyCodeObject *code,*/
        py_globals,          /*PyObject *globals,*/
        0                    /*PyObject *locals*/
    );
    if (!py_frame) goto bad;
    py_frame->f_lineno = py_line;
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        #if PY_MAJOR_VERSION < 3
        if (t->is_unicode) {
            *t->p = PyUnicode_DecodeUTF8(t->s, t->n - 1, NULL);
        } else if (t->intern) {
            *t->p = PyString_InternFromString(t->s);
        } else {
            *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        }
        #else  /* Python 3+ has unicode identifiers */
        if (t->is_unicode | t->is_str) {
            if (t->intern) {
                *t->p = PyUnicode_InternFromString(t->s);
            } else if (t->encoding) {
                *t->p = PyUnicode_Decode(t->s, t->n - 1, t->encoding, NULL);
            } else {
                *t->p = PyUnicode_FromStringAndSize(t->s, t->n - 1);
            }
        } else {
            *t->p = PyBytes_FromStringAndSize(t->s, t->n - 1);
        }
        #endif
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}

static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(char* c_str) {
    return __Pyx_PyUnicode_FromStringAndSize(c_str, strlen(c_str));
}
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject* o) {
    Py_ssize_t ignore;
    return __Pyx_PyObject_AsStringAndSize(o, &ignore);
}
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
    if (
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
            __Pyx_sys_getdefaultencoding_not_ascii &&
#endif
            PyUnicode_Check(o)) {
#if PY_VERSION_HEX < 0x03030000
        char* defenc_c;
        PyObject* defenc = _PyUnicode_AsDefaultEncodedString(o, NULL);
        if (!defenc) return NULL;
        defenc_c = PyBytes_AS_STRING(defenc);
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        {
            char* end = defenc_c + PyBytes_GET_SIZE(defenc);
            char* c;
            for (c = defenc_c; c < end; c++) {
                if ((unsigned char) (*c) >= 128) {
                    PyUnicode_AsASCIIString(o);
                    return NULL;
                }
            }
        }
#endif /*__PYX_DEFAULT_STRING_ENCODING_IS_ASCII*/
        *length = PyBytes_GET_SIZE(defenc);
        return defenc_c;
#else /* PY_VERSION_HEX < 0x03030000 */
        if (PyUnicode_READY(o) == -1) return NULL;
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        if (PyUnicode_IS_ASCII(o)) {
            *length = PyUnicode_GET_DATA_SIZE(o);
            return PyUnicode_AsUTF8(o);
        } else {
            PyUnicode_AsASCIIString(o);
            return NULL;
        }
#else /* __PYX_DEFAULT_STRING_ENCODING_IS_ASCII */
        return PyUnicode_AsUTF8AndSize(o, length);
#endif /* __PYX_DEFAULT_STRING_ENCODING_IS_ASCII */
#endif /* PY_VERSION_HEX < 0x03030000 */
    } else
#endif /* __PYX_DEFAULT_STRING_ENCODING_IS_ASCII  || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT */
    {
        char* result;
        int r = PyBytes_AsStringAndSize(o, &result, length);
        if (r < 0) {
            return NULL;
        } else {
            return result;
        }
    }
}
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject* x) {
   int is_true = x == Py_True;
   if (is_true | (x == Py_False) | (x == Py_None)) return is_true;
   else return PyObject_IsTrue(x);
}
static CYTHON_INLINE PyObject* __Pyx_PyNumber_Int(PyObject* x) {
  PyNumberMethods *m;
  const char *name = NULL;
  PyObject *res = NULL;
#if PY_MAJOR_VERSION < 3
  if (PyInt_Check(x) || PyLong_Check(x))
#else
  if (PyLong_Check(x))
#endif
    return Py_INCREF(x), x;
  m = Py_TYPE(x)->tp_as_number;
#if PY_MAJOR_VERSION < 3
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Int(x);
  }
  else if (m && m->nb_long) {
    name = "long";
    res = PyNumber_Long(x);
  }
#else
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Long(x);
  }
#endif
  if (res) {
#if PY_MAJOR_VERSION < 3
    if (!PyInt_Check(res) && !PyLong_Check(res)) {
#else
    if (!PyLong_Check(res)) {
#endif
      PyErr_Format(PyExc_TypeError,
                   "__%s__ returned non-%s (type %.200s)",
                   name, name, Py_TYPE(res)->tp_name);
      Py_DECREF(res);
      return NULL;
    }
  }
  else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_TypeError,
                    "an integer is required");
  }
  return res;
}
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject* b) {
  Py_ssize_t ival;
  PyObject* x = PyNumber_Index(b);
  if (!x) return -1;
  ival = PyInt_AsSsize_t(x);
  Py_DECREF(x);
  return ival;
}
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t ival) {
#if PY_VERSION_HEX < 0x02050000
   if (ival <= LONG_MAX)
       return PyInt_FromLong((long)ival);
   else {
       unsigned char *bytes = (unsigned char *) &ival;
       int one = 1; int little = (int)*(unsigned char*)&one;
       return _PyLong_FromByteArray(bytes, sizeof(size_t), little, 0);
   }
#else
   return PyInt_FromSize_t(ival);
#endif
}
static CYTHON_INLINE size_t __Pyx_PyInt_AsSize_t(PyObject* x) {
   unsigned PY_LONG_LONG val = __Pyx_PyInt_AsUnsignedLongLong(x);
   if (unlikely(val != (unsigned PY_LONG_LONG)(size_t)val)) {
       if ((val != (unsigned PY_LONG_LONG)-1) || !PyErr_Occurred())
           PyErr_SetString(PyExc_OverflowError,
                           "value too large to convert to size_t");
       return (size_t)-1;
   }
   return (size_t)val;
}


#endif /* Py_PYTHON_H */
