/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Chunk.h
 * Author: pavel
 *
 * Created on 14 марта 2018 г., 20:18
 */

#ifndef CHUNK_H
#define CHUNK_H

class Chunk {
public:
    Chunk(long size, int index);
    long size;
    int index;
};

#endif /* CHUNK_H */

