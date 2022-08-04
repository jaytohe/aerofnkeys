#!/bin/bash -
### NAME
###     sign_module.sh
###
### SYNOPSIS
###     sign_module.sh [options]
###
### DESCRIPTION
###
### REQUIREMENTS
###
### AUTHOR
###     Ding-Yi Chen (definite), dingyichen@gmail.com
###     Created in 2019-02-26 11:01:11
###
set -eu         # Exit when returns non-zero, Error when variable is unset.
LOGGER_TAG=dkms-sign
KEY_DIR=/var/lib/shim-signed/mok
MODULE_NAME=$(sed -n -e '/PACKAGE_NAME/ s/.*=//p' dkms.conf)
: ${PACKAGE_VERSION:=$(sed -n -e '/PACKAGE_VERSION/ s/.*=//p' dkms.conf)}
: ${KERNEL_RELEASE:=$(uname -r)}
KO_FILE=$(echo /var/lib/dkms/$MODULE_NAME/$PACKAGE_VERSION/$KERNEL_RELEASE/x86_64/module/$MODULE_NAME.ko | tr -d '"')
xz -d $KO_FILE.xz
#/usr/src/kernels/$KERNEL_RELEASE/scripts/sign-file sha512 $KEY_DIR/MOK.priv $KEY_DIR/MOK.der $KO_FILE
kmodsign sha512 $KEY_DIR/MOK.priv $KEY_DIR/MOK.der $KO_FILE
xz -z $KO_FILE
