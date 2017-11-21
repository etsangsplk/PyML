//
// Created by Gil Ferreira Hoben on 07/11/17.
//
// This file provides the Python API for
// the linear algebra code written in C++


#include <Python.h>
#include <linearalgebramodule.h>
#include "pythonconverters.h"
#include <iostream>
#include "../../utils/include/exceptionClasses.h"

static PyObject* dot_product(PyObject* self, PyObject *args) {

    // variable instantiation
    // A is a list of lists (matrix)
    // V is a list (vector)
    auto A = new flatArray;
    auto V = new flatArray;
    flatArray * result = nullptr;

    // pointers to python lists
    PyObject * pAArray;
    PyObject * pVVector;

    // return error if we don't get all the arguments
    if (!PyArg_ParseTuple(args, "O!O!", &PyList_Type, &pAArray, &PyList_Type, &pVVector)) {
        PyErr_SetString(PyExc_TypeError, "Expected two lists!");
        return nullptr;
    }

    A->readFromPythonList(pAArray);
    V->readFromPythonList(pVVector);


    // calculate dot product
    try {
        result = A->dot(V);
    }
    catch (flatArrayDimensionMismatch &e) {
        PyErr_SetString(PyExc_ValueError, e.what());
    }
    catch (flatArrayColumnMismatch &e) {
        PyErr_SetString(PyExc_ValueError, e.what());
    }

    // convert result to python list
    PyObject* result_py_list = ConvertFlatArray_PyList(result, "float");

    // build python object
    PyObject *FinalResult = Py_BuildValue("O", result_py_list);

    delete result;
    delete A;
    delete V;

    Py_DECREF(result_py_list);

    return FinalResult;
}


static PyObject* power(PyObject* self, PyObject *args) {

    // variable declaration
    auto A = new flatArray;
    int p;

    // pointers to python lists
    PyObject * pAArray;


    // return error if we don't get all the arguments
    if(!PyArg_ParseTuple(args, "O!i", &PyList_Type, &pAArray, &p)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list and an integer!");
        return nullptr;
    }

    // read in python list
    A->readFromPythonList(pAArray);

    // calculate the power elementwise
    flatArray *result = A->power(p);

    // convert vector to python list
    PyObject* result_py_list = ConvertFlatArray_PyList(result, "float");

    // build python object
    PyObject *FinalResult = Py_BuildValue("O", result_py_list);

    // deallocate memory
    delete A;

    Py_DECREF(result_py_list);

    return FinalResult;
}


static PyObject* subtract(PyObject* self, PyObject *args) {

    // variable instantiation
    auto A = new flatArray;
    auto B = new flatArray;
    flatArray *result = nullptr;

    PyObject *pA;
    PyObject *pB;
    PyObject *result_py_list;
    PyObject *FinalResult;

    // return error if we don't get all the arguments
    if(!PyArg_ParseTuple(args, "O!O!", &PyList_Type, &pA, &PyList_Type, &pB)) {
        PyErr_SetString(PyExc_TypeError, "Expected two lists!");
        return nullptr;
    }

    // get python lists
    A->readFromPythonList(pA);
    B->readFromPythonList(pB);

    // subtraction
    try {
        result = A->subtract(B);
    }

    catch (flatArrayDimensionMismatch &e) {
        PyErr_SetString(PyExc_ValueError, e.what());
        return nullptr;
    }

    catch (flatArrayColumnMismatch &e) {
        PyErr_SetString(PyExc_ValueError, e.what());
        return nullptr;
    }

    catch (flatArrayRowMismatch &e) {
        PyErr_SetString(PyExc_ValueError, e.what());
        return nullptr;
    }

    result_py_list = ConvertFlatArray_PyList(result, "float");
    FinalResult = Py_BuildValue("O", result_py_list);

    // memory deallocation
    delete result;
    delete A;
    delete B;

    Py_DECREF(result_py_list);

    return FinalResult;
}


static PyObject* divide(PyObject* self, PyObject *args) {

    // variable declaration
    auto A = new flatArray;
    double n;

    // pointers to python lists
    PyObject * pAArray;

    // return error if we don't get all the arguments
    if(!PyArg_ParseTuple(args, "O!d", &PyList_Type, &pAArray, &n)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list and a float!");
        return nullptr;
    }

    // read in python list
    A->readFromPythonList(pAArray);

    // calculate elementwise division by n
    flatArray *result = A->divide(n);

    // convert vector to python list
    PyObject* result_py_list = ConvertFlatArray_PyList(result, "float");

    // build python object
    PyObject *FinalResult = Py_BuildValue("O", result_py_list);

    // deallocate memory
    delete A;
    delete result;

    Py_DECREF(result_py_list);

    return FinalResult;
}


static PyObject* sum(PyObject* self, PyObject *args) {

    // sum of all elements in a matrix/vector

    // variable declaration
    auto A = new flatArray;
    PyObject *pAArray;

    // return error if we don't get all the arguments
    if(!PyArg_ParseTuple(args, "O!", &PyList_Type, &pAArray)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list and an integer!");
        return nullptr;
    }

    // use PyList_Size to get size of vector
    A->readFromPythonList(pAArray);

    double result = A->sum();

    PyObject *FinalResult = Py_BuildValue("d", result);

    return FinalResult;
}


static PyObject* pyTranspose(PyObject* self, PyObject *args) {

    // declarations
    auto A = new flatArray;
    PyObject* pyResult;
    PyObject* pArray;

    // return error if we don't get all the arguments
    if(!PyArg_ParseTuple(args, "O!", &PyList_Type, &pArray)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list!");
        return nullptr;
    }

    A->readFromPythonList(pArray);

    flatArray *result = A->transpose();

    pyResult = ConvertFlatArray_PyList(result, "float");

    PyObject* FinalResult = Py_BuildValue("O", pyResult);

    delete result;
    delete A;

    Py_DECREF(pyResult);

    return FinalResult;
}


static PyObject* least_squares(PyObject* self, PyObject *args) {

    // variable declaration
    auto X = new flatArray;
    auto y = new flatArray;

    PyObject *pX;
    PyObject *py;
    PyObject *result_py_list;

    // return error if we don't get all the arguments
    if(!PyArg_ParseTuple(args, "O!O!", &PyList_Type, &pX, &PyList_Type, &py)) {
        PyErr_SetString(PyExc_TypeError, "Expected two lists!");
        return nullptr;
    }


    // read in python lists
    X->readFromPythonList(pX);
    y->readFromPythonList(py);


    // sanity check
    if (X->getRows() != y->getCols()){
        PyErr_SetString(PyExc_ValueError, "Number of rows of X must be the same as the number of training examples");
        return nullptr;
    }

    // memory allocation of theta
//    theta->startEmptyArray(1, X->getCols());
    auto theta = new double [X->getCols()];

    leastSquares(X, y, theta);
//    flatArray *result = leastSquares(X, y, theta);

    result_py_list = Convert_1DArray(theta, X->getCols());
//    result_py_list = ConvertFlatArray_PyList(A);

    PyObject *FinalResult = Py_BuildValue("O", result_py_list);

    // memory deallocation
    delete theta;
    delete X;
    delete y;

    Py_DECREF(result_py_list);

    return FinalResult;
}


static PyObject* mean(PyObject* self, PyObject *args) {

    // variable declaration
    int axis;
    PyObject *pX;
    auto X = new flatArray;
    PyObject *FinalResult = nullptr;

    // return error if we don't get all the arguments
    if (!PyArg_ParseTuple(args, "O!i", &PyList_Type, &pX, &axis)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list and one integer!");
        return nullptr;
    }

    X->readFromPythonList(pX);

    flatArray *result = X->mean(axis);

    if (X->getRows() == 1) {

        FinalResult = Py_BuildValue("d", result->getNElement(0));

    }

    else {

        PyObject *result_py_list = ConvertFlatArray_PyList(result, "float");

        FinalResult = Py_BuildValue("O", result_py_list);

        Py_DECREF(result_py_list);
    }

    delete X;
    delete result;

    return FinalResult;
}


static PyObject* standardDeviation(PyObject* self, PyObject *args) {

    // variable declaration
    int axis, degreesOfFreedom;
    PyObject *pX;
    auto X = new flatArray;
    PyObject *FinalResult = nullptr;

    // return error if we don't get all the arguments
    if (!PyArg_ParseTuple(args, "O!ii", &PyList_Type, &pX, &degreesOfFreedom, &axis)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list and one integer!");
        return nullptr;
    }

    X->readFromPythonList(pX);

    flatArray *result = X->std(degreesOfFreedom, axis);

    if (X->getRows() == 1) {

        FinalResult = Py_BuildValue("d", result->getNElement(0));

    }

    else {

        PyObject *result_py_list = ConvertFlatArray_PyList(result, "float");

        FinalResult = Py_BuildValue("O", result_py_list);

        Py_DECREF(result_py_list);
    }

    delete X;
    delete result;

    return FinalResult;
}


static PyObject* variance(PyObject* self, PyObject *args) {

    // variable declaration
    int axis, degreesOfFreedom;
    PyObject *pX;
    auto X = new flatArray;
    PyObject *FinalResult = nullptr;

    // return error if we don't get all the arguments
    if (!PyArg_ParseTuple(args, "O!ii", &PyList_Type, &pX, &degreesOfFreedom, &axis)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list and two integers!");
        return nullptr;
    }

    X->readFromPythonList(pX);

    flatArray *result = X->var(degreesOfFreedom, axis);

    if (X->getRows() == 1) {

        FinalResult = Py_BuildValue("d", result->getNElement(0));

    }

    else {

        PyObject *result_py_list = ConvertFlatArray_PyList(result, "float");

        FinalResult = Py_BuildValue("O", result_py_list);

        Py_DECREF(result_py_list);
    }

    delete X;
    delete result;

    return FinalResult;
}


static PyObject* cov(PyObject* self, PyObject *args) {

    // variable declaration
    PyObject *pX;
    auto X = new flatArray;
    PyObject *FinalResult = nullptr;

    // return error if we don't get all the arguments
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &pX)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list!");
        return nullptr;
    }

    X->readFromPythonList(pX);

    flatArray *result = covariance(X);

    PyObject *result_py_list = ConvertFlatArray_PyList(result, "float");

    FinalResult = Py_BuildValue("O", result_py_list);

    Py_DECREF(result_py_list);

    delete X;
    delete result;

    return FinalResult;
}


static PyObject* eigenSolve(PyObject* self, PyObject *args) {

    // variable declaration
    int maxIterations;
    double tolerance;
    auto X = new flatArray;
    auto eigFArray = new flatArray;

    PyObject *pX = nullptr;
    PyObject *FinalResult = nullptr;

    // return error if we don't get all the arguments
    if (!PyArg_ParseTuple(args, "O!di", &PyList_Type, &pX, &tolerance, &maxIterations)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list, a float and an integer!");
        return nullptr;
    }

    X->readFromPythonList(pX);

    flatArray *result = jacobiEigenDecomposition(X, tolerance, maxIterations);

    PyObject *eigV = Convert_1DArray(result->getRow(0), result->getCols());

    eigFArray->startEmptyArray(result->getCols(), result->getCols());
    for (int i = 1; i < result->getRows(); ++i) {
        double *rowResult = result->getRow(i);
        eigFArray->setRow(rowResult, i - 1);
        delete [] rowResult;
    }

    PyObject *eigE = ConvertFlatArray_PyList(eigFArray, "float");

    FinalResult = Py_BuildValue("OO", eigV, eigE);

    Py_DECREF(eigE);
    Py_DECREF(eigV);

    delete X;
    delete result;
    delete eigFArray;

    return FinalResult;
}


static PyObject* version(PyObject* self) {
    return Py_BuildValue("s", "Version 0.2");
}


static PyMethodDef linearAlgebraMethods[] = {
        // Python name    C function              argument representation  description
        {"dot_product",   dot_product,            METH_VARARGS,            "Calculate the dot product of two vectors"},
        {"power",         power,                  METH_VARARGS,            "Calculate element wise power"},
        {"subtract",      subtract,               METH_VARARGS,            "Calculate element wise subtraction"},
        {"divide",        divide,                 METH_VARARGS,            "Calculate element wise division"},
        {"sum",           sum,                    METH_VARARGS,            "Calculate the total sum of a vector"},
        {"transpose",     pyTranspose,            METH_VARARGS,            "Transpose a 2D matrix"},
        {"least_squares", least_squares,          METH_VARARGS,            "Perform least squares"},
        {"Cmean",         mean,                   METH_VARARGS,            "Numpy style array mean"},
        {"Cstd",          standardDeviation,      METH_VARARGS,            "Numpy style array standard deviation"},
        {"Cvariance",     variance,               METH_VARARGS,            "Numpy style array variance"},
        {"Ccovariance",   cov,                    METH_VARARGS,            "Calculate covariance matrix"},
        {"eigen_solve",   eigenSolve,             METH_VARARGS,            "Eigendecomposition of symmetric matrix"},
        {"version",       (PyCFunction)version,   METH_NOARGS,             "Returns version."},
        {nullptr, nullptr, 0, nullptr}
};


static struct PyModuleDef linearAlgebraModule = {
        PyModuleDef_HEAD_INIT,
        "linearAlgebra", // module name
        "Collection of linear algebra functions in C to be used in Python", // documentation of module
        -1, // global state
        linearAlgebraMethods // method defs
};


PyMODINIT_FUNC PyInit_Clinear_algebra(void) {
    return PyModule_Create(&linearAlgebraModule);
}
