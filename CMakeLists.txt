cmake_minimum_required(VERSION 3.20)
project(RomaAeternaModularCore LANGUAGES CXX)

option(ROMA_AETERNA_ENABLE_SANITIZERS "Abilita AddressSanitizer e UndefinedBehaviorSanitizer se supportati" OFF)

include(CTest)

add_subdirectory(Source/RomaAeternaCore)
