#ifndef OMR_OWL_INCLUDE
#define OMR_OWL_INCLUDE

#include "optimizer/Optimization.hpp"



class TR_OWL: public TR::Optimization
{
    public:
    TR_OWL(TR::OptimizationManager *manager);
    static TR::Optimization *create(TR::OptimizationManager *manager);

    virtual int32_t perform();
    virtual const char* optDetailString() const throw();
};
    

    





#endif