SUMMARY = "Miscellaneous host interface communication manager"
DESCRIPTION = "Daemon exposes Miscellaneous host interface communications like \
               platform reset, mail box & scratch pad"

PV = "1.0+git"

S = "${WORKDIR}/git"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=e3fc50a88d0a364313df4b21ef20c29e"

SRC_URI = " \
	git://github.com/Intel-BMC/host-misc-comm-manager;protocol=http;branch=master \
	file://0001-Patch-for-C-20.patch \
	"

SRCREV = "470facc6e94ecbd01ca9c3f0749ae603dffff0e9"

inherit cmake systemd pkgconfig
SYSTEMD_SERVICE:${PN} = "xyz.openbmc_project.Host.Misc.Manager.service"

DEPENDS = "boost sdbusplus phosphor-logging"
