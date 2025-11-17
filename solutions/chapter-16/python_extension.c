// Chapter 16: C in Modern Development - Python C Extension
// Solution to Exercise 16.1: Create a C extension for Python

#include <Python.h>
#include <math.h>

// Fast mathematical operations in C
static PyObject* c_fast_power(PyObject* self, PyObject* args) {
    double base;
    int exponent;

    if (!PyArg_ParseTuple(args, "di", &base, &exponent)) {
        return NULL;
    }

    // Handle negative exponents
    if (exponent < 0) {
        return PyFloat_FromDouble(1.0 / pow(base, -exponent));
    }

    // Fast integer exponentiation
    double result = 1.0;
    double power = base;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= power;
        }
        power *= power;
        exponent /= 2;
    }

    return PyFloat_FromDouble(result);
}

// String processing function
static PyObject* c_reverse_string(PyObject* self, PyObject* args) {
    const char* input;
    int length;

    if (!PyArg_ParseTuple(args, "s#", &input, &length)) {
        return NULL;
    }

    // Create new string buffer
    char* reversed = (char*)malloc(length + 1);
    if (reversed == NULL) {
        return PyErr_NoMemory();
    }

    // Reverse the string
    for (int i = 0; i < length; i++) {
        reversed[i] = input[length - 1 - i];
    }
    reversed[length] = '\0';

    PyObject* result = PyUnicode_FromString(reversed);
    free(reversed);
    return result;
}

// Array statistics function
static PyObject* c_array_stats(PyObject* self, PyObject* args) {
    PyObject* list;

    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &list)) {
        return NULL;
    }

    Py_ssize_t length = PyList_Size(list);
    if (length == 0) {
        return PyErr_SetString(PyExc_ValueError, "Empty list provided");
    }

    double sum = 0.0;
    double min_val, max_val;

    // Initialize min and max with first element
    PyObject* first_item = PyList_GetItem(list, 0);
    min_val = max_val = PyFloat_AsDouble(first_item);
    sum += min_val;

    // Process remaining elements
    for (Py_ssize_t i = 1; i < length; i++) {
        PyObject* item = PyList_GetItem(list, i);
        double value = PyFloat_AsDouble(item);

        if (value < min_val) min_val = value;
        if (value > max_val) max_val = value;
        sum += value;
    }

    double mean = sum / length;

    // Create result dictionary
    PyObject* result = PyDict_New();
    PyDict_SetItemString(result, "count", PyLong_FromSsize_t(length));
    PyDict_SetItemString(result, "sum", PyFloat_FromDouble(sum));
    PyDict_SetItemString(result, "mean", PyFloat_FromDouble(mean));
    PyDict_SetItemString(result, "min", PyFloat_FromDouble(min_val));
    PyDict_SetItemString(result, "max", PyFloat_FromDouble(max_val));

    return result;
}

// Prime number checker
static PyObject* c_is_prime(PyObject* self, PyObject* args) {
    int number;

    if (!PyArg_ParseTuple(args, "i", &number)) {
        return NULL;
    }

    if (number <= 1) {
        Py_RETURN_FALSE;
    }
    if (number <= 3) {
        Py_RETURN_TRUE;
    }
    if (number % 2 == 0 || number % 3 == 0) {
        Py_RETURN_FALSE;
    }

    // Check divisors up to sqrt(number)
    int sqrt_num = (int)sqrt(number);
    for (int i = 5; i <= sqrt_num; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            Py_RETURN_FALSE;
        }
    }

    Py_RETURN_TRUE;
}

// Generate Fibonacci sequence
static PyObject* c_fibonacci(PyObject* self, PyObject* args) {
    int count;

    if (!PyArg_ParseTuple(args, "i", &count)) {
        return NULL;
    }

    if (count < 0) {
        return PyErr_SetString(PyExc_ValueError, "Count must be non-negative");
    }

    PyObject* result = PyList_New(count);
    if (result == NULL) {
        return NULL;
    }

    if (count >= 1) {
        PyList_SetItem(result, 0, PyLong_FromLong(0));
    }
    if (count >= 2) {
        PyList_SetItem(result, 1, PyLong_FromLong(1));
    }

    for (int i = 2; i < count; i++) {
        PyObject* prev1 = PyList_GetItem(result, i - 1);
        PyObject* prev2 = PyList_GetItem(result, i - 2);

        long val1 = PyLong_AsLong(prev1);
        long val2 = PyLong_AsLong(prev2);

        PyList_SetItem(result, i, PyLong_FromLong(val1 + val2));
    }

    return result;
}

// Method definition table
static PyMethodDef CExtensionMethods[] = {
    {"fast_power", c_fast_power, METH_VARARGS, "Fast exponentiation using C"},
    {"reverse_string", c_reverse_string, METH_VARARGS, "Reverse a string using C"},
    {"array_stats", c_array_stats, METH_VARARGS, "Calculate array statistics in C"},
    {"is_prime", c_is_prime, METH_VARARGS, "Check if a number is prime"},
    {"fibonacci", c_fibonacci, METH_VARARGS, "Generate Fibonacci sequence"},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Module definition
static struct PyModuleDef c_extension_module = {
    PyModuleDef_HEAD_INIT,
    "c_extension",                   // Module name
    "C extension demonstrating performance optimization",  // Module documentation
    -1,                             // Size of per-interpreter state (-1 = global)
    CExtensionMethods                // Method table
};

// Module initialization
PyMODINIT_FUNC PyInit_c_extension(void) {
    return PyModule_Create(&c_extension_module);
}