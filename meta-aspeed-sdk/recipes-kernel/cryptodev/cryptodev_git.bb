SUMMARY = "A /dev/crypto device driver kernel module"
DESCRIPTION = "A /dev/crypto device driver kernel module, \
equivalent to those in OpenBSD or FreeBSD. The main idea is \
to access of existing ciphers in kernel space from userspace, \
thus enabling the re-use of a hardware implementation of a cipher."
SECTION = "kernel/modules"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263"

PR = "r0"
PV = "1.12+git"

DEPENDS = "virtual/kernel"

S = "${WORKDIR}/git"

BRANCH="aspeed-dev-v1.12"
SRC_URI = "git://gerrit.aspeed.com:29418/cryptodev.git;protocol=ssh;branch=${BRANCH}"
SRCREV = "${AUTOREV}"

inherit module

EXTRA_OEMAKE = 'KERNEL_DIR="${STAGING_KERNEL_DIR}" DESTDIR="${D}"'
CLEANBROKEN = "1"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.

RPROVIDES:${PN} += "kernel-module-cryptodev"
