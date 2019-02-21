#!/bin/sh

RELEASE_DIR=../../build/release/esp8266/
INTERNAL_DIR=../../build/internal/esp8266/

rm -rf ${INTERNAL_DIR}
mkdir -p ${INTERNAL_DIR}/lib/
mkdir -p ${INTERNAL_DIR}/include/

cp src/*.h ${INTERNAL_DIR}/include/

