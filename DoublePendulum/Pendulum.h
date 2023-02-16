#ifndef _PENDULUM_H_
#define _PENDULUM_H_

#include <eigen3/Eigen/Dense>
#include <tuple>

typedef Eigen::Vector4d State;

constexpr double g = 9.81;

class Pendulum
{
private:
    double m1, m2, l1, l2;  //mass1, mass2, legth1, length2
    State state;            //theta, phi, generalized momentum, generalized momentum

    State RungeKutta4(const State& s, double timestep)
        //because Derivative is member function, you can`t put this function out of class 
        //in this class structure. 
    {
        State k1, k2, k3, k4;

        k1 = Derivative(s) * timestep;
        k2 = Derivative(k1 * 0.5 + s) * timestep;
        k3 = Derivative(k2 * 0.5 + s) * timestep;
        k4 = Derivative(k3 + s) * timestep;

        return (k1 + k2 * 2.0 + k3 * 2.0 + k4) / 6 + s;
    }

    State Derivative(const State& s)
    {
        State deriv;

        double u = m2 / m1;
        double dTheta = s(0) - s(1);

        double sinT = std::sin(dTheta);
        double cosT = std::cos(dTheta);

        double A1 = (s(2) * s(3) * sinT) / (m1 * std::pow(l1, 2) *
            (1 + u * sinT * sinT));

        double A2 = ((s(2) * s(2) * u - 2 * s(2) * s(3) * u * cosT +
            s(3) * s(3) * (1 + u)) * std::sin(2.0 * dTheta)) /
            (2 * m1 * l1 * l1 * (1 + (u * sinT * sinT)) * (1 + (u * sinT * sinT)));

        deriv(2) = -m1 * (1 + u) * g * l1 * std::sin(s(0)) - A1 + A2;
        deriv(3) = -m1 * u * g * l1 * std::sin(s(1)) + A1 - A2;

        deriv(0) = (s(2) - (s(3) * cosT)) /
            (m1 * l1 * l1 * (1 + u * sinT * sinT));
        deriv(1) = (s(3) * (1 + u) - s(2) * u * cosT) /
            (m1 * l1 * l1 * (1 + u * sinT * sinT));

        return deriv;
    }

public:
    Pendulum(double m1, double m2, double l1, double l2, State s)   //L2 is not working, L1 == L2
        : m1(m1), m2(m2), l1(l1), l2(l2), state(std::move(s))
    {};

    std::tuple<double, double> getTwoAngles()
    {
        return std::make_tuple(this->state(0), this->state(1));
    }

    void CalculateMove(double timestep)
    {
        State temp = RungeKutta4(this->state, timestep);
        this->state = temp;
    }
};

#endif // !_PENDULUM_H
