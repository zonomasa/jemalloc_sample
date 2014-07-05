#!/bin/bash

if [ ! -e jemalloc ] ; then
    echo "jemalloc : Symbolic link to jemalloc-source-tree does not exist"
    exit 1
fi

NORMAL=(
    "how_to_link/direct_link"
    "how_to_link/ld_preload"
    "bad_usage"
)

PREFIX=(
    "how_to_link/direct_link_with_prefix"
)


build_rel() {
    pushd jemalloc
    autoconf
    ./configure --disable-fill
    make
    popd
    mkdir -p ./lib/rel
    cp jemalloc/lib/libjemalloc.so* ./lib/rel
    mkdir -p ./include/rel/jemalloc
    cp jemalloc/include/jemalloc/jemalloc.h ./include/rel/jemalloc
    pushd jemalloc
    make relclean # clean objs & binaries
    popd

}


build_prof() {
    pushd jemalloc
    autoconf
    ./configure --enable-prof
    make
    popd
    mkdir -p ./lib/prof
    cp jemalloc/lib/libjemalloc.so* ./lib/prof
    mkdir -p ./include/prof/jemalloc
    cp jemalloc/include/jemalloc/jemalloc.h ./include/prof/jemalloc
    pushd jemalloc
    make relclean # clean objs & binaries
    popd

}


build_debug() {
    pushd jemalloc
    autoconf
    ./configure --enable-prof --enable-debug
    make
    popd
    mkdir -p ./lib/debug
    cp jemalloc/lib/libjemalloc.so* ./lib/debug
    mkdir -p ./include/debug/jemalloc
    cp jemalloc/include/jemalloc/jemalloc.h ./include/debug/jemalloc
    pushd jemalloc
    make relclean # clean objs & binaries
    popd

}


build_prefix() {
    pushd jemalloc
    autoconf
    ./configure --enable-debug --enable-prof --with-jemalloc-prefix=hoge_
    make
    popd
    mkdir -p ./lib/prefix
    cp jemalloc/lib/libjemalloc.so* ./lib/prefix
    mkdir -p ./include/prefix/jemalloc
    cp jemalloc/include/jemalloc/jemalloc.h ./include/prefix/jemalloc
    pushd jemalloc
    make relclean # clean objs & binaries
    popd

}


uninstall() {
    pushd jemalloc
    if [ -e Makefile ] ; then
        make relclean # clean objs & binaries
    fi
    popd
    rm -rf lib/* include/*
}

install() {
    build_rel
    build_prof
    build_debug
    build_prefix
}

if [ $# -eq 1 ] ; then
    if [ "clean" == $1 ] ; then
        echo "Clean mode"
        uninstall
    else
        echo "Unknown option:"$1
        exit 1
    fi
else
    echo "Install mode"
    install
fi
