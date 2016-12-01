cmake_minimum_required(VERSION 3.6)
project(NeiroNets)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

set(SOURCE_FILES main.cpp DataSource.h NPoint.h Neuron.h NeuralNet.h Gnuplot.h)
add_executable(NeiroNets ${SOURCE_FILES})