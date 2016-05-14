#pragma once
#include <QString>

template<class T, unsigned int dim, T zero>
/**
 * @brief The Vector class
 */
class Vector
{
public:
    Vector();
    Vector(T coordinate, ...);
    Vector(const Vector<T, dim, zero> &v);
    ~Vector();
    /**
     * @brief operator + Summ this vector with another
     * @param v Second vector
     * @return Vector-summ
     */
    Vector<T, dim, zero> operator+(const Vector<T, dim, zero> &v) const;
    /**
     * @brief operator - Difference this vector with another
     * @param v Second vector
     * @return Vector-difference
     */
    Vector<T, dim, zero> operator-(const Vector<T, dim, zero> &v) const;
    /**
     * @brief operator * Multiplicates this vector with another
     * @param v Second vector
     * @return Scalar multiplication of vectors
     */
    T operator*(const Vector<T, dim, zero> &v) const;
    /**
     * @brief operator == Checks equality of this vector and another vector
     * @param v Second vector
     * @return true if equal, false if not
     */
    bool operator ==(const Vector<T, dim, zero> &v) const;
    /**
     * @brief isNullVector Checks if this vector is null-vector
     * @return true if null-vector, false if not
     */
    bool isNullVector() const;
    /**
     * @brief toQString Returns a QString representation of vector
     * @return QString representation of vector
     */
    QString toQString() const;
private:
    T* coords;
};

template<class T, unsigned int dim, T zero>
Vector<T, dim, zero>::Vector()
{
    coords = new T[dim];
    for (unsigned int i = 0; i < dim; i++)
    {
        coords[i] = zero;
    }
}

template<class T, unsigned int dim, T zero>
Vector<T, dim, zero>::Vector(T coordinate, ...)
{
    coords = new T[dim];
    T* iter = &coordinate;
    for (unsigned int i = 0; i < dim; i++)
    {
        coords[i] = *iter;
        iter++;
    }
    iter = nullptr;
}

template<class T, unsigned int dim, T zero>
Vector<T, dim, zero>::Vector(const Vector<T, dim, zero> &v)
{
    coords = new T[dim];
    for (unsigned int i = 0; i < dim; i++)
    {
        coords[i] = v.coords[i];
    }
}

template<class T, unsigned int dim, T zero>
Vector<T, dim, zero>::~Vector()
{
    delete [] coords;
}

template<class T, unsigned int dim, T zero>
Vector<T, dim, zero> Vector<T, dim, zero>::operator+(const Vector<T, dim, zero> &v) const
{
    Vector<T, dim, zero> result;
    for (unsigned int i = 0; i < dim; i++)
    {
        result.coords[i] = coords[i] + v.coords[i];
    }
    return result;
}

template<class T, unsigned int dim, T zero>
Vector<T, dim, zero> Vector<T, dim, zero>::operator-(const Vector<T, dim, zero> &v) const
{
    Vector<T, dim, zero> result;
    for (unsigned int i = 0; i < dim; i++)
    {
        result.coords[i] = coords[i] - v.coords[i];
    }
    return result;
}

template<class T, unsigned int dim, T zero>
T Vector<T, dim, zero>::operator*(const Vector<T, dim, zero> &v) const
{
    T result = zero;
    for (unsigned int i = 0; i < dim; i++)
    {
        result += coords[i] * v.coords[i];
    }
    return result;
}

template<class T, unsigned int dim, T zero>
bool Vector<T, dim, zero>::operator ==(const Vector<T, dim, zero> &v) const
{
    bool result = true;
    for (unsigned int i = 0; i < dim; i++)
    {
        if (coords[i] != v.coords[i])
        {
            result = false;
            break;
        }
    }
    return result;
}

template<class T, unsigned int dim, T zero>
bool Vector<T, dim, zero>::isNullVector() const
{
    bool result = true;
    for (unsigned int i = 0; i < dim; i++)
    {
        if (coords[i] != zero)
        {
            result = false;
            break;
        }
    }
    return result;
}

template<class T, unsigned int dim, T zero>
QString Vector<T, dim, zero>::toQString() const
{
    QString res;
    res.clear();
    if (!dim)
    {
        return res;
    }
    res.append('{');
    for (unsigned int i = 0; i < dim - 1; i++)
    {
        res.append(QString::number(coords[i]));
        res.append(", ");
    }
    res.append(QString::number(coords[dim - 1]));
    res.append('}');
    return res;
}
