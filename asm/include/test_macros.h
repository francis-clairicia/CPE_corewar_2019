/*
** EPITECH PROJECT, 2019
** asm
** File description:
** test_macros.h
*/

#ifndef TEST_MACROS_H_
#define TEST_MACROS_H_

#define PTR_FIELD(type, ...) (type []){(type){__VA_ARGS__}}

#endif