#ifndef PDE_HPP
#define PDE_HPP

// A better name would be PDEModel
class PDE
{
   public:
       // Entity semantic:
      PDE() = default;
      virtual ~PDE() = default;
      PDE(const PDE&) = delete;
      PDE& operator=(const PDE&) = delete;
      PDE(PDE&&) = delete;
      PDE& operator=(PDE&&) = delete;

      double T,xl,xu;

      // Performance improvement: ask the coefficients
      // for the whole grid. This would avoid call of
      // virtual method in loops (when you build the
      // matrix system). Indeed, virtual methods cannot
      // be inlined by the compiler, this prevents a lot
      // of optimizations
      virtual double a(double t, double x)=0;
      virtual double b(double t, double x)=0;
      virtual double c(double t, double x)=0;
      virtual double d(double t, double x)=0;

      virtual double f(double x)=0;
      virtual double fu(double t)=0;
      virtual double fl(double t)=0;
};

#endif


