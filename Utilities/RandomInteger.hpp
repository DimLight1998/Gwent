//
// Created on 2017/09/10 at 14:28.
//

#ifndef GWENT_RANDOMINTERGER_HPP
#define GWENT_RANDOMINTERGER_HPP


class RandomInteger
{
public:
    /// \brief get a random integer based on API of random.org
    /// \param min min should be greater than -1e9
    /// \param max max should be less than 1e9
    /// \return the random integer
    /// \note need network, if failed, use local qrand and qsrand
    static int GetRandomInteger(int min, int max);

    /// \brief get a random integer based on API of random.org
    /// \return the random integer
    /// \note equals to GetRandmInteger(-100000000, 100000000)
    static int GetRandomInteger();
};


#endif //GWENT_RANDOMINTERGER_HPP
