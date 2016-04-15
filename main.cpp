#include <iostream>
#include <math.h>

using namespace std;

class Integral{
    protected: //вне класса поля недоступны, но доступны производным классам
        int a; // начало отрезка интегрирования
        int b; // конец
        int N; // количество отрезков разбиения
    public:
        Integral(int a1, int b1, int N1) {a=a1; b=b1; N=N1;} //конструктор
       // ~Integral();
        //виртуальная ф-я - ф-я, объявленная в базовом классе и переопределенная в производном
        // чисто виртуальная ф-я - виртуальная ф-я, не имеющая определения в базовом классе
        virtual double* integral_value(double (*func)(double))=0; //в аргументе передаем указатель на подинтегр ф-ю

};

class Rectangle: public Integral{
    public:
        //вызов конструктора производного класса
        Rectangle(int a1, int b1, int N1):Integral(a1,b1,N1)
            {a=a1; b=b1; N=N1;}

        ~Rectangle(){};
        //разбиение фигуры под графиком подинтегральной функции
        double* integral_value(double (*func)(double)){
            double h;
            double x;
            double *f = new double[N];
            h=(b-a)/(double)N;
            for(int i=1; i<N+1; i++)
            {
                x=a+(i-0.5)*h; //x_(i-1)+h/2
                f[i-1]=(func(x));
               // cout<<f[i-1]<<endl;
            }

            cout<<"Интеграл из класса Rectangle. \n";
            return f;
        }

        double Square(double* f){
            double h;
            h=(b-a)/(double)N;

            double s=0.0;
            for(int i=1; i<N+1; i++)
            {
                s=s+f[i-1];
            }
            s=s*h;
            return s;
        }


};

class Trapeze: public Integral{
    public:
        Trapeze(int a1, int b1, int N1):Integral(a1,b1,N1)
            {a=a1; b=b1; N=N1;}
        ~Trapeze(){};
        //разбиение фигуры под графиком подинтегральной функции
        double * integral_value(double (*func)(double)){
            double h;
            double x;
            double *f = new double[N+1];
            h=(b-a)/(double)N;
            for(int i=0; i<N+1; i++)
            {
                x=a+i*h;
                f[i]=(func(x));
                //cout<<f[i]<<endl;
            }

            cout<<"Интеграл из класса Trapeze.\n";
            return f;
        }

        double Square(double* f){
            double h;
            h=(b-a)/(double)N;

            double s=0.0;
            for(int i=1; i<N; i++)
            {
                s=s+f[i];
            }
            s=0.5*h*(f[0]+2*s+f[N]);
            return s;
        }

};

double func(double x)
{
    return x*sin(x);
}

int main()
{
    cout << "Hello world!" << endl;

    double (*fnc)(double)=&func; //создаем переменную

    // указатель *p ссылается на объекты разных типов, при этом вызываются разные виртуальные функции
    Integral *p;
    Rectangle obj1(4,9,10);
    Trapeze obj2(4,9,10);

    p=&obj1;
   // p->integral_value();

    p=&obj2;
    //p->integral_value();


    return 0;
}
