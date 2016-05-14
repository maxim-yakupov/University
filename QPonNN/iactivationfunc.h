#ifndef ACTIVATIONFUNC_H
#define ACTIVATIONFUNC_H

#define UNUSED_VAR(x) (void)x;

namespace QPonNN {
    class IActivationFunc
    {
    public:
        virtual ~IActivationFunc() {}
        virtual double eval(double x);
        virtual double derivative(double x);
        virtual IActivationFunc* clone();
    };
}

#endif // ACTIVATIONFUNC_H
