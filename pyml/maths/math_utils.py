from collections import Counter
from pyml.maths.CMaths import quick_sort, Cargmax, Cargmin
from pyml.maths.Clinear_algebra import Cmean, Cstd, Cvariance, Ccovariance
from math import exp


def sort(array, axis=0):
    """
    sort array elements in ascending order using the quicksort algorithm

    :type array: list
    :type axis: int

    :param array: list of lists (matrix) or list (vector)
    :param axis: if array is a matrix this is used to determine whether to order array column or row wise

    :rtype: list or list of lists with same shape as input array
    :return: sorted array in ascending order

    Example:
    --------

    >>> from pyml.maths import sort
    >>> a = [-5, 3, 10, 2, 1, -1]
    >>> print(sort(a))
    [-5.0, -1.0, 1.0, 2.0, 3.0, 10.0]
    """
    return quick_sort(array, axis)[0]


def argsort(array, axis=0):
    """
    calculate order of elements in array

    :type array: list
    :type axis: int

    :param array: list of lists (matrix) or list (vector)
    :param axis: if array is a matrix this is used to determine whether to order array column or row wise

    :rtype: list or list of lists with same shape as input array
    :return: sorted array in ascending order

    Example:
    --------

    >>> from pyml.maths import argsort
    >>> a = [-5, 3, 10, 2, 1, -1]
    >>> print(argsort(a))
    [0, 5, 4, 3, 1, 2]
    """
    return quick_sort(array, axis)[1]


def argmin(array, axis=0):
    """
    Returns index of smallest element in a vector, with numpy style column and row wise behaviour for matrices

    :type array: list
    :type axis: axis

    :param array: list of lists (matrix) or list (vector)
    :param axis: if array is a matrix this is used to determine whether to order array column or row wise

    :rtype: list
    :return: vector with argmin for each vector

    Example:
    --------

    >>> from pyml.maths import argmin
    >>> a = [-5, 3, 10, 2, 1, -1]
    >>> print(argmin(a))
    [0]
    """
    return Cargmin(array, axis)


def argmax(array, axis=0):
    """
    Returns index of largest element in a vector, with numpy style column and row wise behaviour for matrices

    :type array: list
    :type axis: axis

    :param array: list of lists (matrix) or list (vector)
    :param axis: if array is a matrix this is used to determine whether to order array column or row wise

    :rtype: list
    :return: vector with argmax for each vector

    Example:
    --------

    >>> from pyml.maths import argmax
    >>> a = [-5, 3, 10, 2, 1, -1]
    >>> print(argmax(a))
    [2]
    """
    return Cargmax(array, axis)


def max_occurence(array):
    """
    find the element with highest occurrence in an array

    :type array: list

    :param array: a vector

    :rtype: int/float
    :return: element with highest occurence

    Example:
    --------

    >>> from pyml.maths import max_occurence
    >>> a = [-5, 3, 10, 2, 1, -1, -5, 2, 2]
    >>> print(max_occurence(a))
    2
    """
    count = Counter(array)
    return max(count, key=count.get)


def mean(array, axis=None):
    """
    numpy style mean of array

    :type array: list
    :type axis: int

    :param array: list of lists (matrix) or list (vector)
    :param axis: if array is a matrix this is used to determine whether to calculate mean of array column or row wise

    :rtype: list or int
    :return: list with row/column mean(s) or int of overall mean

    Example:
    --------

    >>> from pyml.maths import mean
    >>> a = [-5, 3, 10, 2, 5, 0]
    >>> print(mean(a))
    2.5
    """
    if isinstance(array, list):

        if len(array) > 0:
            if isinstance(array[0], list) and isinstance(array[0][0], (float, int)):
                # in this case we have a 2D matrix
                if axis == 1 or axis == 0:
                    return Cmean(array, axis)
                else:
                    return Cmean(Cmean(array, 0), 0)

            elif isinstance(array[0], (int, float)):
                # in this case we have a vector
                return Cmean(array, 0)

            else:
                raise TypeError("Expected a list of lists or a list of int/floats")
        else:
            raise ValueError("Empty list")
    else:
        raise TypeError("Expected a list")


def std(array, degrees_of_freedom=0, axis=None):

    """
    numpy style standard deviation of array

    :type array: list
    :type axis: int

    :param array: list of lists (matrix) or list (vector)
    :param axis: if array is a matrix this is used to determine whether to calculate standard deviation of array column or row wise

    :rtype: list or int
    :return: list with row/column standard deviation(s) or int of overall standard deviation

    Example:
    --------

    >>> from pyml.maths import std
    >>> a = [-5, 3, 8, 2, 0, -1]
    >>> print(std(a))
    3.9756201472921875
    """
    if isinstance(array, list):

        if len(array) > 0:
            if isinstance(array[0], list) and isinstance(array[0][0], (float, int)):
                # in this case we have a 2D matrix
                if axis == 1 or axis == 0:
                    return Cstd(array, degrees_of_freedom, axis)
                else:
                    raise NotImplementedError("This is not the code you are looking for.")

            elif isinstance(array[0], (int, float)):
                # in this case we have a vector
                return Cstd(array, degrees_of_freedom, 0)

            else:
                raise TypeError("Expected a list of lists or a list of int/floats")

        else:
            raise ValueError("Empty list")
    else:
        raise TypeError("Expected a list")


def variance(array, degrees_of_freedom=0, axis=None):

    """
    numpy style standard deviation of array

    :type array: list
    :type axis: int

    :param array: list of lists (matrix) or list (vector)
    :param axis: if array is a matrix this is used to determine whether to calculate variance of array column or row wise

    :rtype: list or int
    :return: list with row/column standard deviation(s) or int of overall variance
    """
    if isinstance(array, list):

        if len(array) > 0:
            if isinstance(array[0], list) and isinstance(array[0][0], (float, int)):
                # in this case we have a 2D matrix
                if axis == 1 or axis == 0:
                    return Cvariance(array, degrees_of_freedom, axis)
                else:
                    raise NotImplementedError("This is not the code you are looking for.")

            elif isinstance(array[0], (int, float)):
                # in this case we have a vector
                return Cvariance(array, degrees_of_freedom, 0)

            else:
                raise TypeError("Expected a list of lists or a list of int/floats")

        else:
            raise ValueError("Empty list")
    else:
        raise TypeError("Expected a list")


def covariance(array):

    """
    Calculates covariance matrix.

    :type array: list

    :param array: list of lists representing a matrix

    :rtype: list
    :return: list of lists representing the covariance matrix of array

    Example:
    --------

    >>> from pyml.datasets import load_iris
    >>> X, y = load_iris()
    >>> print(*covariance(X), sep="\n")
    [0.6811222222222222, -0.039006666666669076, 1.2651911111111005, 0.5134577777777753]
    [-0.039006666666669076, 0.1867506666666667, -0.31956800000001273, -0.11719466666666767]
    [1.2651911111111005, -0.31956800000001273, 3.0924248888888854, 1.2877448888888843]
    [0.5134577777777753, -0.11719466666666767, 1.2877448888888843, 0.5785315555555559]
    """

    return Ccovariance(array)


def sigmoid(array):
    """
    Python implementation of element wise sigmoid of a vector

    :type array: list
    :param array: list representing a vector

    :rtype: list
    :return: list of same size as array
    """
    return [1 / (1 + exp(-el)) for el in array]
