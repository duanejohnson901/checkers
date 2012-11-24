/* 
 * File:   Random.h
 * Author: Shariath
 *
 * Created on 15 de Novembro de 2012, 15:42
 */

#ifndef RANDOM_H
#define	RANDOM_H

#include <cstdlib>
#include <ctime>

/**
 * Random class
 * Simple utility for generating random numbers
 * Singleton
 */
class Random {
public:
    //Singleton instance
    static Random instance;
    
    /**
     * Gets a random from min to maxa
     * @param min
     * @param max
     * @return 
     */
    static int get(int min, int max) {
        return min + rand() % (max + 1);
    }
    /**
     * Gets a random from 1 to max
     * @param max
     * @return 
     */
    static int get(int max) {
        return rand()%(max+1);
    }
private:
    /**
     * Inline constructor that only provides a seed for the random numbers
     */
    Random() { srand(time(NULL)); } 
} ;



#endif	/* RANDOM_H */

