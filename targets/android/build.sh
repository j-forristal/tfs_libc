#!/bin/sh

RELEASE_DIR=../../build/release/android/
INTERNAL_DIR=../../build/internal/android/
LIBNOM=libtfs_libc
MODNOM=tfs_libc

HEADERS="jni/src/platform.libc.h jni/src/platform.linux.h jni/src/platform.android.h"

build()
{
        ARCH=$1
        TOOLCHAIN=$2

        ${NDK_PATH}ndk-build APP_ABI=${ARCH} NDK_TOOLCHAIN=${TOOLCHAIN} APP_CFLAGS="${APP_CFLAGS}"
        if [ $? -ne 0 ]; then
                echo ERROR building, aborting
                exit 1
        fi

        mkdir -p ${INTERNAL_DIR}/lib/$ARCH/
        mkdir -p ${INTERNAL_DIR}/obj/$ARCH/
        cp obj/local/${ARCH}/${LIBNOM}.a ${INTERNAL_DIR}/lib/$ARCH/
	cp -r obj/local/${ARCH}/objs/${MODNOM}/ ${INTERNAL_DIR}/obj/${ARCH}/
}

rm -rf obj/
rm -rf libs/
rm -rf ${INTERNAL_DIR}
#${NDK_PATH}ndk-build clean

build "armeabi" "arm-linux-androideabi-clang"
build "armeabi-v7a" "arm-linux-androideabi-clang"
build "arm64-v8a" "aarch64-linux-android-clang"
build "x86" "x86-clang"
build "x86_64" "x86_64-clang"

mkdir -p ${INTERNAL_DIR}/include/
cp ${HEADERS} ${INTERNAL_DIR}/include/

