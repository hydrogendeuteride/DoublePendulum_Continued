#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include <vector>
#include <SFML/Graphics.hpp>

namespace Object
{
    class Pendulum
    {

        /*
         * ------------------------
         *             |*
         *      theta  |  *
         *             |   *
         *                  Ball1
         *                       *
         *          phi                 *
         *                                     *
         *                                    Ball2
         */

    private:
        sf::CircleShape Ball_Up;
        sf::CircleShape Ball_Down;

        sf::Vertex Line1[2];
        sf::Vertex Line2[2];

        float BallSize, Length, PosX, PosY;

        sf::VertexArray curve;

    public:
        Pendulum(float BallSize, float Length, float PosX, float PosY, double Theta1, double Theta2, sf::Color Color)
            : BallSize(BallSize), Length(Length), PosX(PosX), PosY(PosY)
        {
            Ball_Up.setRadius(this->BallSize);
            Ball_Down.setRadius(this->BallSize);

            Ball_Up.setFillColor(Color);
            Ball_Down.setFillColor(Color);


            float x_ref_up, x_ref_down, y_ref_up, y_ref_down;

            x_ref_up = static_cast<float>(std::sin(Theta1)) * this->Length;
            y_ref_up = static_cast<float>(std::cos(Theta1)) * this->Length;

            x_ref_down = static_cast<float>(std::sin(Theta2)) * this->Length;
            y_ref_down = static_cast<float>(std::cos(Theta2)) * this->Length;

            Line1[0] = sf::Vertex(
                sf::Vector2f(this->PosX, this->PosY));
            Line1[1] = sf::Vertex(
                sf::Vector2f(x_ref_up + this->PosX, y_ref_up + this->PosY));


            Ball_Up.setPosition(
                sf::Vector2f(x_ref_up + this->PosX - BallSize,
                    y_ref_up + this->PosY - BallSize));


            Line2[0] = sf::Vertex(sf::Vector2f(x_ref_up + this->PosX,
                y_ref_up + this->PosY));
            Line2[1] = sf::Vertex(
                sf::Vector2f(x_ref_up + x_ref_down + this->PosX,
                    y_ref_up + y_ref_down + this->PosY));

            Ball_Down.setPosition(
                sf::Vector2f(x_ref_up + x_ref_down + this->PosX - BallSize,
                    y_ref_up + y_ref_down + this->PosY - BallSize));
        }

        void Move(double Theta1, double Theta2)
        {
            float x_ref_up, x_ref_down, y_ref_up, y_ref_down;

            x_ref_up = static_cast<float>(std::sin(Theta1)) * this->Length;
            y_ref_up = static_cast<float>(std::cos(Theta1)) * this->Length;

            x_ref_down = static_cast<float>(std::sin(Theta2)) * this->Length;
            y_ref_down = static_cast<float>(std::cos(Theta2)) * this->Length;

            Line1[0] = sf::Vertex(
                sf::Vector2f(this->PosX, this->PosY));
            Line1[1] = sf::Vertex(
                sf::Vector2f(x_ref_up + this->PosX, y_ref_up + this->PosY));


            Ball_Up.setPosition(
                sf::Vector2f(x_ref_up + this->PosX - BallSize,
                    y_ref_up + this->PosY - BallSize));


            Line2[0] = sf::Vertex(sf::Vector2f(x_ref_up + this->PosX,
                y_ref_up + this->PosY));
            Line2[1] = sf::Vertex(
                sf::Vector2f(x_ref_up + x_ref_down + this->PosX,
                    y_ref_up + y_ref_down + this->PosY));

            Ball_Down.setPosition(
                sf::Vector2f(x_ref_up + x_ref_down + this->PosX - BallSize,
                    y_ref_up + y_ref_down + this->PosY - BallSize));

            curve.append(sf::Vertex(
                sf::Vector2f(x_ref_up + x_ref_down + this->PosX - BallSize,
                    y_ref_up + y_ref_down + this->PosY - BallSize)));
        }

        void Draw(sf::RenderWindow* window)
        {
            window->draw(Line1, 2, sf::Lines);
            window->draw(Line2, 2, sf::Lines);

            window->draw(Ball_Up);
            window->draw(Ball_Down);

            window->draw(curve);
        }
    };
}

#endif // !_DRAWABLE_H_