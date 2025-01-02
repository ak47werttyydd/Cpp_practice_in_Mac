cmake_minimum_required(VERSION 3.28)
project(Cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(Cpp main.cpp
        TrieTree.h
        StringComp_KMP.h
        AC_AutoMachine.h
        FileSystem.h
        HuffmanCode.h
        MeetingRoom.h
        Inversion.h
        2D_ClosestPair.h
        minimalNumberOfPackages.h
        CanBeConnected.h
        FlipShift.h
        SlidingWindows.h
        2DMatMul_1DMemory.h
        AllPathsFromSourceToTarget.h
        UnionFind_SimilarSentence.h
        OperatorOrder.h
        OperatorOrder_GPT_PostOrder.h
        CopyTwoTrees.h
        uomap_equality_hashfun.h
        AsynPubSub.h)
