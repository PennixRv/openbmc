SUMMARY = "Generic XKB keymap library"
DESCRIPTION = "libxkbcommon is a keymap compiler and support library which \
processes a reduced subset of keymaps as defined by the XKB specification."
HOMEPAGE = "http://www.xkbcommon.org"
LIC_FILES_CHKSUM = "file://LICENSE;md5=e525ed9809e1f8a07cf4bce8b09e8b87"
LICENSE = "MIT & MIT"

DEPENDS = "flex-native bison-native"

SRC_URI = "http://xkbcommon.org/download/${BPN}-${PV}.tar.xz"

SRC_URI[sha256sum] = "0edc14eccdd391514458bc5f5a4b99863ed2d651e4dd761a90abf4f46ef99c2b"

UPSTREAM_CHECK_URI = "http://xkbcommon.org/"

inherit meson pkgconfig bash-completion

PACKAGECONFIG ?= "${@bb.utils.filter('DISTRO_FEATURES', 'x11 wayland', d)} xkbregistry"

PACKAGECONFIG[docs] = "-Denable-docs=true,-Denable-docs=false,doxygen-native"
PACKAGECONFIG[wayland] = "-Denable-wayland=true,-Denable-wayland=false,wayland-native wayland wayland-protocols,"
PACKAGECONFIG[x11] = "-Denable-x11=true,-Denable-x11=false,libxcb xkeyboard-config,"
PACKAGECONFIG[xkbregistry] = "-Denable-xkbregistry=true,-Denable-xkbregistry=false,libxml2"

PACKAGE_BEFORE_PN += "xkbcli"
FILES:${PN} = ""
FILES:xkbcli = "${bindir}/xkbcli ${libexecdir}/xkbcommon/xkbcli-*"

python populate_packages:prepend () {
    # Put the libraries into separate packages to avoid dependency creep
    do_split_packages(d, d.expand('${libdir}'), r'^(lib.*)\.so\.*', '%s', '%s library', extra_depends='', allow_links=True)
}

# Fix a following runtime error:
# xkbcommon: ERROR: couldn't find a Compose file for locale "C"
RDEPENDS:${PN} = "${@bb.utils.contains('DISTRO_FEATURES', 'x11', 'libx11-locale', 'libx11-compose-data', d)}"

BBCLASSEXTEND += "native"

CVE_PRODUCT += "xkbcommon:libxkbcommon"
